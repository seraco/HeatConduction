/*!
 * @file CMatrix.cpp
 * @brief The main subroutines for defining matrices and their operations.
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

#include <iostream>
#include <cmath>

#include "../include/CMatrix.hpp"

CMatrix::CMatrix() {
    /*--- Initialize properties. ---*/
    nRows = 0;
    nCols = 0;

    /*--- Allocate memory for the entries. ---*/
    mtx = new double[0];
}

CMatrix::CMatrix(unsigned rows, unsigned cols, const double initValue) {
    /*--- Initialize properties. ---*/
    nRows = rows;
    nCols = cols;

    /*--- Allocate memory for the entries. ---*/
    mtx = new double[cols*rows];

    /*--- Initialize entries with initValue. ---*/
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            mtx[j*nRows+i] = initValue;
        }
    }
}

CMatrix::CMatrix(const CMatrix& rhs) {
    /*--- Initialize properties. ---*/
    nRows = rhs.nRows;
    nCols = rhs.nCols;

    /*--- Allocate memory for the entries. ---*/
    mtx = new double[nCols*nRows];

    /*--- Initialize entries with the same entries in rhs. ---*/
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            mtx[j*nRows+i] = rhs.mtx[j*nRows+i];
        }
    }
}

CMatrix::~CMatrix() {
    /*--- Release the memory allocated for the entries. ---*/
    delete[] mtx;
}

unsigned CMatrix::getRows() const {
    return nRows;
}

unsigned CMatrix::getCols() const {
    return nCols;
}

CMatrix CMatrix::transpose() {
    CMatrix res(nCols, nRows, 0.0);

    /*--- Change the i-j indices to obtain the transpose. ---*/
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            res(j, i) = mtx[j*nRows+i];
        }
    }

    return res;
}

CMatrix CMatrix::linspace(const double left, const double right,
                                 const unsigned nNode) {
    CMatrix res = CMatrix(1, nNode, 0.0);

    /*--- Space separation between adjacent nodes. ---*/
    double deltaX = (right - left) / (nNode - 1);

    /*--- Construct the linspace. ---*/
    for (unsigned i = 0; i < nNode; i++) {
        res(i, 0) = left + i*deltaX;
    }

    return res;
}

double CMatrix::determinant() {
    /*--- Initialize variables to use in the subroutine. ---*/
    double res = 1.0;
    int info = 0;
    CMatrix A = CMatrix(*this);
    int* vPivPtr = new int[nCols];
    double* APtr = A.getMtxAddress();

    /*--- LU decomposition of the matrix. ---*/
    F77NAME(dgetrf)(nCols, nCols, APtr, nCols, vPivPtr, info);

    /*--- The determinant will be the product of the diagonal of U. ---*/
    for (unsigned j = 0; j < nCols; j++) {
        res *= A(j, j);
        if (j != vPivPtr[j]) {
            res *= -1.0;
        }
    }

    /*--- Release allocated memory. ---*/
    delete[] vPivPtr;

    return res;
}

CMatrix CMatrix::inverse() {
    /*--- Initialize variables to use in the subroutine. ---*/
    int info = 0;
    CMatrix A = CMatrix(*this);
    int* vPivPtr = new int[nCols];
    double* APtr = A.getMtxAddress();
    int nWorkspace = nCols * nCols;
    double* workspace = new double[nWorkspace];

    /*--- LU decomposition of the matrix. ---*/
    F77NAME(dgetrf)(nCols, nCols, APtr, nCols, vPivPtr, info);

    /*--- LAPACK subroutine to compute the inverse. ---*/
    F77NAME(dgetri)(nCols, APtr, nCols, vPivPtr, workspace, nWorkspace, info);

    /*--- Release allocated memory. ---*/
    delete[] vPivPtr;
    delete[] workspace;

    return A;
}

double* CMatrix::getMtxAddress() {
    return &mtx[0];
}

void CMatrix::printMtx() {
    for (unsigned i = 0; i < nRows; i++) {
        for (unsigned j = 0; j < nCols; j++) {
            std::cout.width(10);
            std::cout << mtx[j*nRows+i] << " ";
        }
        std::cout << std::endl;
    }
}

double& CMatrix::operator()(const unsigned i, const unsigned j) {
    return mtx[j*nRows+i];
}

const double& CMatrix::operator()(const unsigned i, const unsigned j) const {
    return mtx[j*nRows+i];
}

CMatrix& CMatrix::operator=(const CMatrix& rhs) {
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
        for (unsigned i = 0; i < nRows; i++) {
            mtx[j*nRows+i] = rhs.mtx[j*nRows+i];
        }
    }

    return *this;
}

CMatrix CMatrix::operator+(const CMatrix& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    /*--- Sum every entry. ---*/
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            res(i, j) = mtx[j*nRows+i] + rhs(i, j);
        }
    }

    return res;
}

CMatrix& CMatrix::operator+=(const CMatrix& rhs) {
    /*--- Use the + overloaded sign to compute +=. ---*/
    CMatrix res = (*this) + rhs;
    (*this) = res;
    return *this;
}

CMatrix CMatrix::operator-(const CMatrix& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    /*--- Substract every entry. ---*/
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            res(i, j) = mtx[j*nRows+i] - rhs(i, j);
        }
    }

    return res;
}

CMatrix& CMatrix::operator-=(const CMatrix& rhs) {
    /*--- Use the - overloaded sign to compute -=. ---*/
    CMatrix res = (*this) - rhs;
    (*this) = res;
    return *this;
}

CMatrix CMatrix::operator*(const CMatrix& rhs) {
    unsigned rhsCols = rhs.getCols();
    CMatrix res(nRows, rhsCols, 0.0);

    /*--- Compute the product of matrices. ---*/
    for (unsigned j = 0; j < rhsCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            for (unsigned k = 0; k < nCols; k++) {
                res(i, j) += mtx[k*nRows+i] * rhs(k, j);
            }
        }
    }

    return res;
}

CMatrix& CMatrix::operator*=(const CMatrix& rhs) {
    /*--- Use the * overloaded sign to compute *=. ---*/
    CMatrix res = (*this) * rhs;
    (*this) = res;
    return *this;
}

CMatrix CMatrix::operator+(const double& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    /*--- Sum every entry with the constant. ---*/
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            res(i, j) = mtx[j*nRows+i] + rhs;
        }
    }

    return res;
}


CMatrix CMatrix::operator-(const double& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    /*--- Substract every entry with the constant. ---*/
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            res(i, j) = mtx[j*nRows+i] - rhs;
        }
    }

    return res;
}


CMatrix CMatrix::operator*(const double& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    /*--- Multiply every entry with the constant. ---*/
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            res(i, j) = mtx[j*nRows+i] * rhs;
        }
    }

    return res;
}


CMatrix CMatrix::operator/(const double& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    /*--- Divide every entry with the constant. ---*/
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            res(i, j) = mtx[j*nRows+i] / rhs;
        }
    }

    return res;
}

CMatrix CMatrix::operator^(const double& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    /*--- Take the power of every entry with the constant. ---*/
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            res(i, j) = pow(mtx[j*nRows+i], rhs);
        }
    }

    return res;
}

#endif
