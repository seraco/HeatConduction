/*!
 * @file CMatrixSymmetric.cpp
 * @brief The main subroutines for defining symmetric matrices and their operations.
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

#ifndef __CMATRIXSYMMETRIC_CPP
#define __CMATRIXSYMMETRIC_CPP

#include <iostream>
#include <cmath>

#include "../include/CMatrixSymmetric.hpp"

CMatrixSymmetric::CMatrixSymmetric() {
    /*--- Initialize properties. ---*/
    nRows = 0;
    nCols = 0;

    /*--- Allocate memory for the entries. ---*/
    mtx = new double[0];
}

CMatrixSymmetric::CMatrixSymmetric(unsigned rows, unsigned cols, const double initValue) {
    /*--- Initialize properties. ---*/
    nRows = rows;
    nCols = cols;

    /*--- Allocate memory for the entries. ---*/
    mtx = new double[cols*rows];

    /*--- Initialize entries with initValue. ---*/
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = j; i < nRows; i++) {
            mtx[j*nRows-(j-1)*j/2+i-j] = initValue;
        }
    }
}

CMatrixSymmetric::CMatrixSymmetric(const CMatrixSymmetric& rhs) {
    /*--- Initialize properties. ---*/
    nRows = rhs.nRows;
    nCols = rhs.nCols;

    /*--- Allocate memory for the entries. ---*/
    mtx = new double[nCols*nRows];

    /*--- Initialize entries with the same entries in rhs. ---*/
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = j; i < nRows; i++) {
            mtx[j*nRows-(j-1)*j/2+i-j] = rhs.mtx[j*nRows-(j-1)*j/2+i-j];
        }
    }
}

CMatrixSymmetric::~CMatrixSymmetric() {
    /*--- Release the memory allocated for the entries. ---*/
    delete[] mtx;
}

unsigned CMatrixSymmetric::getRows() const {
    return nRows;
}

unsigned CMatrixSymmetric::getCols() const {
    return nCols;
}

double* CMatrixSymmetric::getMtxAddress() const {
    return &mtx[0];
}

void CMatrixSymmetric::printMtx() {
    for (unsigned i = 0; i < nRows; i++) {
        for (unsigned j = 0; j < i; j++) {
            std::cout.width(10);
            std::cout << "*" << " ";
        }
        for (unsigned j = i; j < nCols; j++) {
            std::cout.width(10);
            std::cout << mtx[i*nRows-(i-1)*i/2+j-i] << " ";
        }
        std::cout << std::endl;
    }
}

double& CMatrixSymmetric::operator()(const unsigned i, const unsigned j) {
    if (i < j) return mtx[i*nRows-(i-1)*i/2+j-i];
    return mtx[j*nRows-(j-1)*j/2+i-j];
}

const double& CMatrixSymmetric::operator()(const unsigned i, const unsigned j) const {
    if (i < j) return mtx[i*nRows-(i-1)*i/2+j-i];
    return mtx[j*nRows-(j-1)*j/2+i-j];
}

CMatrixSymmetric& CMatrixSymmetric::operator=(const CMatrixSymmetric& rhs) {
    /*--- If the matrix is the same, simply return the same matrix. ---*/
    if (&rhs == this) return *this;

    /*--- Release allocated memory for entries in order to allocate new space for
          different nRows and nCols. ---*/
    delete mtx;
    nRows = rhs.getRows();
    nCols = rhs.getCols();

    /*--- Allocated memory for the new entries. ---*/
    mtx = new double[nCols*nRows];

    /*--- Copy entries from the rhs to the current matrix. ---*/
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = j; i < nRows; i++) {
            mtx[j*nRows-(j-1)*j/2+i-j] = rhs.mtx[j*nRows-(j-1)*j/2+i-j];
        }
    }

    return *this;
}

CMatrixSymmetric CMatrixSymmetric::operator+(const CMatrixSymmetric& rhs) {
    CMatrixSymmetric res(nRows, nCols, 0.0);

    /*--- Sum every entry. ---*/
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = j; i < nRows; i++) {
            res(i, j) = mtx[j*nRows-(j-1)*j/2+i-j] + rhs(i, j);
        }
    }

    return res;
}

CMatrixSymmetric& CMatrixSymmetric::operator+=(const CMatrixSymmetric& rhs) {
    /*--- Use the + overloaded sign to compute +=. ---*/
    CMatrixSymmetric res = (*this) + rhs;
    (*this) = res;
    return *this;
}

#endif
