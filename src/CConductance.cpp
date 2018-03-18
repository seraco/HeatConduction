#ifndef __CCONDUCTANCE_CPP
#define __CCONDUCTANCE_CPP

#include <iostream>
#include <cmath>

#include "../include/CConductance.h"
#include "../include/CMaterial.h"
#include "../include/CMesh.h"
#include "../include/CGeometry.h"

CConductance::CConductance() {
    gaussOrder = 2;
    gaussPoints = CMatrix(1, 2, 0.0);
    gaussPoints(0, 0) = -1.0 / sqrt(3.0);
    gaussPoints(0, 1) = 1.0 / sqrt(3.0);
    gaussWeights = CMatrix(1, 2, 1.0);
}

CConductance::CConductance(const CGeometry& geo, const CMaterial& mat,
                           const CMesh& msh) {
    gaussOrder = 2;
    gaussPoints = CMatrix(1, 2, 0.0);
    gaussPoints(0, 0) = -1.0 / sqrt(3.0);
    gaussPoints(0, 1) = 1.0 / sqrt(3.0);
    gaussWeights = CMatrix(1, 2, 1.0);

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

    for (unsigned e = 0; e < nEl; e++) {
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

        for (unsigned i = 0; i < nNodPerEl; i++) {
            for (unsigned j = 0; j < nNodPerEl; j++) {
                int iDof, jDof;
                iDof = gDf(0, i);
                jDof = gDf(0, j);
                K(iDof, jDof) = K(iDof, jDof) + Ke(i, j);
            }
        }
    }

    return K;
}

#endif
