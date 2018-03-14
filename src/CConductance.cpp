#ifndef __CCONDUCTANCE_CPP
#define __CCONDUCTANCE_CPP

#include <cmath>

#include "../include/CConductance.h"
#include "../include/CMaterial.h"
#include "../include/CMesh.h"

CConductance::CConductance() {
    gaussOrder = 2;
    gaussPoints = CMatrix(1, 2, 0.0);
    gaussPoints(0, 0) = -1.0 / sqrt(3.0);
    gaussPoints(0, 1) = 1.0 / sqrt(3.0);
    gaussWeights = CMatrix(1, 2, 1.0);
}

CConductance::CConductance(const CMaterial mat, const CMesh msh) {
    gaussOrder = 2;
    gaussPoints = CMatrix(1, 2, 0.0);
    gaussPoints(0, 0) = -1.0 / sqrt(3.0);
    gaussPoints(0, 1) = 1.0 / sqrt(3.0);
    gaussWeights = CMatrix(1, 2, 1.0);

    mater = mat;
    mesh = msh;

    conducMtx = conductanceMtx(mat, msh);
}

CConductance::~CConductance() {}

unsigned CConductance::getGaussOrder() {
    return gaussOrder;
}

CMatrix CConductance::getGaussPoints() {
    return gaussPoints;
}

CMatrix CConductance::getGaussWeights() {
    return gaussWeights;
}

CMaterial CConductance::getMaterial() {
    return mater;
}

CMatrix CConductance::getConducMtx() {
    return conducMtx;
}

CMesh CConductance::getMesh() {
    return mesh;
}

CMatrix CConductance::conductanceMtx(CMaterial mat, CMesh msh) {
    unsigned nDof = msh.getNDofTotal();
    unsigned nEl = msh.getNElem();
    unsigned nNodPerEl = msh.getNNodePerElem();
    CMatrix D = mat.getConductivityMatrix();
    CMatrix K = CMatrix(nDof, nDof, 0.0);
    CMatrix Ke = CMatrix(nNodPerEl, nNodPerEl, 0.0);
    CMatrix conn = msh.getConnMtx();
    CMatrix coor = msh.getCoorMtx();
    CMatrix glDof = msh.getGlDofMtx();
    CMatrix eNodes = CMatrix(1, nNodPerEl, 0.0);
    CMatrix eCoord = CMatrix(nNodPerEl, 2, 0.0);
    CMatrix X = CMatrix(nNodPerEl, 1, 0.0);
    CMatrix Y = CMatrix(nNodPerEl, 1, 0.0);
    CMatrix J;
    CMatrix DetJ = CMatrix(gaussOrder, gaussOrder, 0.0);
    double eta;
    double xi;
    CMatrix N = CMatrix(1, nNodPerEl, 0.0);
    CMatrix GN = CMatrix(2, nNodPerEl, 0.0);

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
            }
        }
    }

    return K;
}

#endif
