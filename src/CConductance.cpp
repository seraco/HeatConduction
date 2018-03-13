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

// CMatrix CConductance::conductivityMtx(CMaterial mat, CMesh msh) {
//
// }

#endif
