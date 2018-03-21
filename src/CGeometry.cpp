/*!
 * @file CGeometry.cpp
 * @brief The main subroutines for the definition of the geometry.
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

#ifndef __CGEOMETRY_CPP
#define __CGEOMETRY_CPP

#include "../include/CGeometry.hpp"

CGeometry::CGeometry() {
    /*--- Initialize properties. ---*/
    aConst = 0.0;
    bConst = 0.0;
    heightLeft = 0.0;
    heightRight = 0.0;
    length = 0.0;
    thickness = 0.0;
}

CGeometry::CGeometry(const double a, const double h1, const double h2,
                     const double L, const double th) {
    /*--- Initialize properties. ---*/
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
    /*--- Compute height. ---*/
    return aConst*x*x + bConst*x + heightLeft;
}

#endif
