/*!
 * @file Analytical.cpp
 * @brief The main subroutines for calculating analytical solution and error.
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

 #ifndef __ANALYTICAL_CPP
 #define __ANALYTICAL_CPP

#include <string>
#include <iostream>
#include <cmath>
#include <mpi.h>

#include "../include/Analytical.hpp"
#include "../include/CMesh.hpp"
#include "../include/CMatrix.hpp"
#include "../include/CBoundaryConditions.hpp"
#include "../include/CMaterial.hpp"

void solveAnalytical(const CMesh& msh,
                     const CBoundaryConditions& bnd,
                     const CMaterial& mat,
                     const CMatrix& numSol) {
    /*--- Initialize variables to be used in the subroutine. ---*/
    unsigned nNod = msh.getNNode();
    CMatrix T = CMatrix(nNod, 1, 0.0);
    CMatrix coor = msh.getCoorMtx();
    std::string flLoc = bnd.getFluxBCLoc();
    std::string tpLoc = bnd.getTempBCLoc();
    double flVal = bnd.getFluxValue();
    double tpVal = bnd.getTempValue();
    double kXX = mat.getKXX();
    double kYY = mat.getKYY();

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*--- Calculate analytical solution. ---*/
    if (flLoc == "right" && tpLoc == "left") {
        for (unsigned i = 0; i < nNod; i++) {
            T(i, 0) = -flVal * coor(i, 0) / kXX + tpVal;
        }
        calculateError(T, numSol, nNod);
    } else if (flLoc == "top" && tpLoc == "bottom") {
        for (unsigned i = 0; i < nNod; i++) {
            T(i, 0) = -flVal * (coor(i, 1) + 0.5) / kYY + tpVal;
        }
        calculateError(T, numSol, nNod);
    } else {
        if (rank == 0) std::cout << "Unknown analytical solution" << std::endl;
    }
}

void calculateError(const CMatrix& sol1, const CMatrix& sol2,
                    const unsigned size) {
    /*--- Initialize variables to be used in the subroutine. ---*/
    double err = 0.0;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*--- Compute error. ---*/
    for (unsigned i = 0; i < size; i++) {
        err += abs(sol1(i, 0) - sol2(i, 0));
    }
    if (rank == 0)
        std::cout << "The error of the solution is: " << err << std::endl;
}

#endif
