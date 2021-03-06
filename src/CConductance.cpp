/*!
 * @file CConductance.cpp
 * @brief The main subroutines for assemblying the conductance matrix.
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

#ifndef __CCONDUCTANCE_CPP
#define __CCONDUCTANCE_CPP

#include <iostream>
#include <cmath>
#include <mpi.h>

#include "../include/CConductance.hpp"
#include "../include/CMaterial.hpp"
#include "../include/CMesh.hpp"
#include "../include/CGeometry.hpp"

CConductance::CConductance() {
    /*--- Initialize properties. ---*/
    gaussOrder = 2;
    gaussPoints = CMatrix(1, 2, 0.0);
    gaussPoints(0, 0) = -1.0 / sqrt(3.0);
    gaussPoints(0, 1) = 1.0 / sqrt(3.0);
    gaussWeights = CMatrix(1, 2, 1.0);
}

CConductance::CConductance(const CGeometry& geo, const CMaterial& mat,
                           const CMesh& msh) {
    /*--- Initialize properties. ---*/
    gaussOrder = 2;
    gaussPoints = CMatrix(1, 2, 0.0);
    gaussPoints(0, 0) = -1.0 / sqrt(3.0);
    gaussPoints(0, 1) = 1.0 / sqrt(3.0);
    gaussWeights = CMatrix(1, 2, 1.0);

    /*--- Calculate conductance matrix. ---*/
    conducMtx = conductanceMtx(geo, mat, msh);
}

CConductance::~CConductance() {}

unsigned CConductance::getGaussOrder() const {
    return gaussOrder;
}

CMatrix CConductance::getGaussPoints() const {
    return gaussPoints;
}

CMatrix CConductance::getGaussWeights() const {
    return gaussWeights;
}

CMatrix CConductance::getConducMtx() const {
    return conducMtx;
}

CMatrix CConductance::conductanceMtx(const CGeometry& geo, const CMaterial& mat,
                                     const CMesh& msh) {
    /*--- Initialize variables to be used in the subroutine. ---*/
    double thick = geo.getThickness();
    unsigned nDof = msh.getNDofTotal();
    unsigned nEl = msh.getNElem();
    unsigned nNodPerEl = msh.getNNodePerElem();
    unsigned dfPerNod = msh.getDofPerNode();
    CMatrix D = mat.getConductivityMatrix();
    CMatrix K = CMatrix(nDof, nDof, 0.0);
    CMatrix conn = msh.getConnMtx();
    CMatrix coor = msh.getCoorMtx();
    CMatrix glDof = msh.getGlDofMtx();
    CMatrix eNodes = CMatrix(1, nNodPerEl, 0.0);
    CMatrix eCoord = CMatrix(nNodPerEl, 2, 0.0);
    CMatrix J;
    CMatrix InvJ;
    double detJ;
    double eta;
    double xi;
    CMatrix N = CMatrix(1, nNodPerEl, 0.0);
    CMatrix GN = CMatrix(2, nNodPerEl, 0.0);
    CMatrix B;

    int rank;
    int nRanks;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nRanks);
    // printf("Hello: rank %d, world: %d\n",rank, nRanks);

    /*--- Divide elements to be handled by ranks 0 and 1. ---*/
    unsigned initEl = rank * (nEl / nRanks);
    unsigned finaEl = (rank + 1) * (nEl / nRanks);
    if (rank == 1 && nEl % 2 != 0) finaEl++;

    // std::cout << initEl << finaEl << nEl << std::endl;

    /*--- Computation of elemental conductance matrix and assembly of global
          matrix. ---*/
    for (unsigned e = initEl; e < finaEl; e++) {
        eNodes(0, 0) = conn(e, 1);
        eNodes(0, 1) = conn(e, 2);
        eNodes(0, 2) = conn(e, 3);
        eNodes(0, 3) = conn(e, 4);

        eCoord(0, 0) = coor(eNodes(0, 0), 0);
        eCoord(0, 1) = coor(eNodes(0, 0), 1);
        eCoord(1, 0) = coor(eNodes(0, 1), 0);
        eCoord(1, 1) = coor(eNodes(0, 1), 1);
        eCoord(2, 0) = coor(eNodes(0, 2), 0);
        eCoord(2, 1) = coor(eNodes(0, 2), 1);
        eCoord(3, 0) = coor(eNodes(0, 3), 0);
        eCoord(3, 1) = coor(eNodes(0, 3), 1);

        CMatrix gDf = CMatrix(1, nNodPerEl, 0.0);
        for (unsigned j = 0; j < nNodPerEl; j++) {
            gDf(0, j) = glDof(eNodes(0, j), dfPerNod);
        }

        /*--- Elemental conductance with Gaussian quadrature. ---*/
        CMatrix Ke = CMatrix(nNodPerEl, nNodPerEl, 0.0);
        for (unsigned i = 0; i < gaussOrder; i++) {
            for (unsigned j = 0; j < gaussOrder; j++) {
                eta = gaussPoints(0, i);
                xi = gaussPoints(0, j);

                N(0, 0) = (1 - xi) * (1 - eta);
                N(0, 1) = (1 + xi) * (1 - eta);
                N(0, 2) = (1 + xi) * (1 + eta);
                N(0, 3) = (1 - xi) * (1 + eta);

                GN(0, 0) = 0.25 * (-(1 - eta));
                GN(0, 1) = 0.25 * (1 - eta);
                GN(0, 2) = 0.25 * (1 + eta);
                GN(0, 3) = 0.25 * (-(1 + eta));
                GN(1, 0) = 0.25 * (-(1 - xi));
                GN(1, 1) = 0.25 * (-(1 + xi));
                GN(1, 2) = 0.25 * (1 + xi);
                GN(1, 3) = 0.25 * (1 - xi);

                J = GN * eCoord;
                detJ = J.determinant();
                InvJ = J.inverse();
                B = InvJ * GN;

                Ke = Ke +
                     B.transpose() * D * B * thick * detJ *
                     gaussWeights(0, i) * gaussWeights(0, j);
            }
        }

        /*--- Assembly of global conductance. ---*/
        for (unsigned i = 0; i < nNodPerEl; i++) {
            for (unsigned j = 0; j < nNodPerEl; j++) {
                int iDof, jDof;
                iDof = gDf(0, i);
                jDof = gDf(0, j);
                K(iDof, jDof) = K(iDof, jDof) + Ke(i, j);
            }
        }
    }

    // TODO: Improve communication to be faster!
    /*--- Combine calculations from ranks 0 and 1 to obtain the final
          conductance matrix. ---*/
    if (nRanks > 1) {
        if (rank == 0) {
            CMatrix Krec = CMatrix(nDof, nDof, 0.0);
            MPI_Send(&K(0, 0), nDof * nDof, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&Krec(0, 0), nDof * nDof, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
            K += Krec;
        } else {
            CMatrix Krec = CMatrix(nDof, nDof, 0.0);
            MPI_Recv(&Krec(0, 0), nDof * nDof, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
            MPI_Send(&K(0, 0), nDof * nDof, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
            K += Krec;
        }
    }

    return K;
}

#endif
