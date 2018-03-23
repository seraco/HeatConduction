/*!
 * @file CHeatConduction.cpp
 * @brief The main subroutines for solving the heat conduction problem.
 * @author S.Ramon (seraco)
 * @version 0.0.1
 *
 * Copyright 2018 S.Ramon
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __CHEATCONDUCTION_CPP
#define __CHEATCONDUCTION_CPP

#include <string>
#include <iostream>

#include "../include/CHeatConduction.hpp"
#include "../include/CBoundaryConditions.hpp"
#include "../include/CConductance.hpp"
#include "../include/CMesh.hpp"
#include "../include/CLinearSystem.hpp"
#include "../include/CMaterial.hpp"

CHeatConduction::CHeatConduction() {}

CHeatConduction::CHeatConduction(const CBoundaryConditions& bnd,
                                 const CConductance& cnd,
                                 const CMesh& msh) {
    /*--- Solve heat conduction problem. ---*/
    partitionMatrices(bnd, cnd);
    temp = solveTemperature(msh, bnd);
    flux = solveFlux(msh, bnd);
}

CHeatConduction::~CHeatConduction() {}

CMatrix CHeatConduction::getKee() const {
    return Kee;
}

CMatrix CHeatConduction::getKff() const {
    return Kff;
}

CMatrix CHeatConduction::getKef() const {
    return Kef;
}

CMatrix CHeatConduction::getTe() const {
    return Te;
}

CMatrix CHeatConduction::getFf() const {
    return Ff;
}


CMatrix CHeatConduction::getTemp() const {
    return temp;
}

CMatrix CHeatConduction::getFlux() const {
    return flux;
}

void CHeatConduction::partitionMatrices(const CBoundaryConditions& bnd,
                                        const CConductance& cnd) {
    /*--- Initialize variables to be used in the subroutine. ---*/
    unsigned nTNod = bnd.getNTempNodes();
    CMatrix tpNod = bnd.getTempNodes();
    unsigned rDof = bnd.getNReducedDof();
    CMatrix rDofVec = bnd.getReducedDofVector();
    CMatrix T = bnd.getTempBCVector();
    CMatrix f = bnd.getFluxBCVector();
    CMatrix K = cnd.getConducMtx();

    /*--- Te subvector. ---*/
    Te = CMatrix(nTNod, 1, 0.0);
    for (unsigned i = 0; i < nTNod; i++) {
        Te(i, 0) =  T(tpNod(0, i), 0);
    }

    /*--- Ff subvector. ---*/
    Ff = CMatrix(rDof, 1, 0.0);
    for (unsigned i = 0; i < rDof; i++) {
        Ff(i, 0) =  f(rDofVec(0, i), 0);
    }

    /*--- Kee submatrix. ---*/
    Kee = CMatrix(nTNod, nTNod, 0.0);
    for (unsigned i = 0; i < nTNod; i++) {
        for (unsigned j = 0; j < nTNod; j++) {
            Kee(i, j) = K(tpNod(0, i), tpNod(0, j));
        }
    }

    /*--- Kff submatrix. ---*/
    Kff = CMatrix(rDof, rDof, 0.0);
    for (unsigned i = 0; i < rDof; i++) {
        for (unsigned j = 0; j < rDof; j++) {
            Kff(i, j) = K(rDofVec(0, i), rDofVec(0, j));
        }
    }

    /*--- Kef submatrix. ---*/
    Kef = CMatrix(nTNod, rDof, 0.0);
    for (unsigned i = 0; i < nTNod; i++) {
        for (unsigned j = 0; j < rDof; j++) {
            Kef(i, j) = K(tpNod(0, i), rDofVec(0, j));
        }
    }
}

CMatrix CHeatConduction::solveTemperature(const CMesh& msh,
                                          const CBoundaryConditions& bnd) {
    /*--- Initialize variables to be used in the subroutine. ---*/
    unsigned nDof = msh.getNDofTotal();
    CMatrix T = CMatrix(nDof, 1, 0.0);
    unsigned nTNod = bnd.getNTempNodes();
    CMatrix tpNod = bnd.getTempNodes();
    unsigned rDof = bnd.getNReducedDof();
    CMatrix rDofVec = bnd.getReducedDofVector();

    /*--- Solve the linear system of equations. ---*/
    CMatrix RHS = Ff - Kef.transpose() * Te;
    CMatrixSymmetric KffSym = Kff.toSymmetricStorage();
    CLinearSystem<CMatrixSymmetric> sys =
        CLinearSystem<CMatrixSymmetric>(KffSym, RHS);
    Tf = sys.iterativeSolve();

    /*--- Build global temperature vector combining Te and Tf. ---*/
    for (unsigned i = 0; i < nTNod; i++) {
        T(tpNod(0, i), 0) = Te(i, 0);
    }
    for (unsigned i = 0; i < rDof; i++) {
        T(rDofVec(0, i), 0) = Tf(i, 0);
    }

    return T;
}

CMatrix CHeatConduction::solveFlux(const CMesh& msh,
                                   const CBoundaryConditions& bnd) {
    /*--- Initialize variables to be used in the subroutine. ---*/
    unsigned nDof = msh.getNDofTotal();
    CMatrix F = CMatrix(nDof, 1, 0.0);
    unsigned nTNod = bnd.getNTempNodes();
    CMatrix tpNod = bnd.getTempNodes();
    unsigned rDof = bnd.getNReducedDof();
    CMatrix rDofVec = bnd.getReducedDofVector();

    Fe = Kee * Te + Kef * Tf;

    /*--- Build global flux vector combining Fe and Ff. ---*/
    for (unsigned i = 0; i < nTNod; i++) {
        F(tpNod(0, i), 0) = Fe(i, 0);
    }
    for (unsigned i = 0; i < rDof; i++) {
        F(rDofVec(0, i), 0) = Ff(i, 0);
    }

    return F;
}

#endif
