#ifndef __CHEATCONDUCTION_CPP
#define __CHEATCONDUCTION_CPP

#include "../include/CHeatConduction.h"
#include "../include/CBoundaryConditions.h"
#include "../include/CConductance.h"
#include "../include/CMesh.h"
#include "../include/CLinearSystem.h"

CHeatConduction::CHeatConduction() {}

CHeatConduction::CHeatConduction(CBoundaryConditions bnd, CConductance cnd,
                                 CMesh msh) {
    partitionMatrices(bnd, cnd);
    temp = solveTemperature(msh, bnd);
    flux = solveFlux(msh, bnd);
}

CHeatConduction::~CHeatConduction() {}

CMatrix CHeatConduction::getKee() {
    return Kee;
}

CMatrix CHeatConduction::getKff() {
    return Kff;
}

CMatrix CHeatConduction::getKef() {
    return Kef;
}

CMatrix CHeatConduction::getTe() {
    return Te;
}

CMatrix CHeatConduction::getFf() {
    return Ff;
}


CMatrix CHeatConduction::getTemp() {
    return temp;
}

CMatrix CHeatConduction::getFlux() {
    return flux;
}

void CHeatConduction::partitionMatrices(CBoundaryConditions bnd,
                                        CConductance cnd) {
    unsigned nTNod = bnd.getNTempNodes();
    CMatrix tpNod = bnd.getTempNodes();
    unsigned rDof = bnd.getNReducedDof();
    CMatrix rDofVec = bnd.getReducedDofVector();
    CMatrix T = bnd.getTempBCVector();
    CMatrix f = bnd.getFluxBCVector();
    CMatrix K = cnd.getConducMtx();

    Te = CMatrix(nTNod, 1, 0.0);
    for (unsigned i = 0; i < nTNod; i++) {
        Te(i, 0) =  T(tpNod(0, i), 0);
    }

    Ff = CMatrix(rDof, 1, 0.0);
    for (unsigned i = 0; i < rDof; i++) {
        Ff(i, 0) =  f(rDofVec(0, i), 0);
    }

    Kee = CMatrix(nTNod, nTNod, 0.0);
    for (unsigned i = 0; i < nTNod; i++) {
        for (unsigned j = 0; j < nTNod; j++) {
            Kee(i, j) = K(tpNod(0, i), tpNod(0, j));
        }
    }

    Kff = CMatrix(rDof, rDof, 0.0);
    for (unsigned i = 0; i < rDof; i++) {
        for (unsigned j = 0; j < rDof; j++) {
            Kff(i, j) = K(rDofVec(0, i), rDofVec(0, j));
        }
    }

    Kef = CMatrix(nTNod, rDof, 0.0);
    for (unsigned i = 0; i < nTNod; i++) {
        for (unsigned j = 0; j < rDof; j++) {
            Kef(i, j) = K(tpNod(0, i), rDofVec(0, j));
        }
    }
}

CMatrix CHeatConduction::solveTemperature(CMesh msh, CBoundaryConditions bnd) {
    unsigned nDof = msh.getNDofTotal();
    CMatrix T = CMatrix(nDof, 1, 0.0);
    unsigned nTNod = bnd.getNTempNodes();
    CMatrix tpNod = bnd.getTempNodes();
    unsigned rDof = bnd.getNReducedDof();
    CMatrix rDofVec = bnd.getReducedDofVector();

    CMatrix RHS = Ff - Kef.transpose() * Te;
    CLinearSystem sys = CLinearSystem(Kff, RHS);
    Tf = sys.solve();

    for (unsigned i = 0; i < nTNod; i++) {
        T(tpNod(0, i), 0) = Te(i, 0);
    }

    for (unsigned i = 0; i < rDof; i++) {
        T(rDofVec(0, i), 0) = Tf(i, 0);
    }

    return T;
}

CMatrix CHeatConduction::solveFlux(CMesh msh, CBoundaryConditions bnd) {
    unsigned nDof = msh.getNDofTotal();
    CMatrix F = CMatrix(nDof, 1, 0.0);
    unsigned nTNod = bnd.getNTempNodes();
    CMatrix tpNod = bnd.getTempNodes();
    unsigned rDof = bnd.getNReducedDof();
    CMatrix rDofVec = bnd.getReducedDofVector();

    Fe = Kee * Te + Kef * Tf;

    for (unsigned i = 0; i < nTNod; i++) {
        F(tpNod(0, i), 0) = Fe(i, 0);
    }

    for (unsigned i = 0; i < rDof; i++) {
        F(rDofVec(0, i), 0) = Ff(i, 0);
    }

    return F;
}

#endif
