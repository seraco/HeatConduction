#ifndef __CGEOMETRY_CPP
#define __CGEOMETRY_CPP

#include "../include/CGeometry.h"

CGeometry::CGeometry() {
    aConst = 0.0;
    bConst = 0.0;
    heightLeft = 0.0;
    heightRight = 0.0;
    length = 0.0;
    thickness = 0.0;
}

CGeometry::CGeometry(const double a, const double h1, const double h2,
                     const double L, const double th) {
    aConst = a;
    heightLeft = h1;
    heightRight = h2;
    length = L;
    thickness = th;
    bConst = -a * L + (h2 - h1) / L;
}

CGeometry::~CGeometry() {}

double CGeometry::getAConst() const {
    return aConst;
}

double CGeometry::getBConst() const {
    return bConst;
}

double CGeometry::getHeightLeft() const {
    return heightLeft;
}

double CGeometry::getHeightRight() const {
    return heightRight;
}

double CGeometry::getLength() const {
    return length;
}

double CGeometry::getThickness() const {
    return thickness;
}

double CGeometry::getHeight(const double x) const {
    return aConst*x*x + bConst*x + heightLeft;
}

#endif
