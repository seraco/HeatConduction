/*!
 * @file CMaterial.cpp
 * @brief The main subroutines for defining material properties.
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

#ifndef __CMATRIX_CPP
#define __CMATRIX_CPP

#include "../include/CMatrix.hpp"
#include "../include/CMaterial.hpp"

CMaterial::CMaterial() {
    /*--- Initialize properties. ---*/
    conducXX = 0.0;
    conducXY = 0.0;
    conducYY = 0.0;
}

CMaterial::CMaterial(const double kXX, const double kXY, const double kYY) {
    /*--- Initialize properties. ---*/
    conducXX = kXX;
    conducXY = kXY;
    conducYY = kYY;
}

CMaterial::~CMaterial() {}

CMatrix CMaterial::getConductivityMatrix() const {
    /*--- Initialize conductivity matrix with zeroes. ---*/
    CMatrix res = CMatrix(2, 2, 0.0);

    /*--- Build conductivity matrix. ---*/
    res(0, 0) = conducXX;
    res(0, 1) = conducXY;
    res(1, 0) = conducXY;
    res(1, 1) = conducYY;

    return res;
}

double CMaterial::getKXX() const {
    return conducXX;
}

double CMaterial::getKXY() const {
    return conducXY;
}

double CMaterial::getKYY() const {
    return conducYY;
}

#endif
