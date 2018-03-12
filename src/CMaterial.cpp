#ifndef __CMATRIX_CPP
#define __CMATRIX_CPP

#include <iostream>

#include "../include/CMatrix.h"
#include "../include/CMaterial.h"

CMaterial::CMaterial() {
    conducXX = 0.0;
    conducXY = 0.0;
    conducYY = 0.0;
}

CMaterial::CMaterial(const double kXX, const double kXY, const double kYY) {
    conducXX = kXX;
    conducXY = kXY;
    conducYY = kYY;
}

CMaterial::~CMaterial() {}

CMatrix CMaterial::getConductivityMatrix() {
    CMatrix res = CMatrix(2, 2, 0.0);

    res(0, 0) = conducXX;
    res(0, 1) = conducXY;
    res(1, 0) = conducXY;
    res(1, 1) = conducYY;

    return res;
}

double CMaterial::getKXX() {
    return conducXX;
}

double CMaterial::getKXY() {
    return conducXY;
}

double CMaterial::getKYY() {
    return conducYY;
}

#endif
