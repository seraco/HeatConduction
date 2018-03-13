#ifndef __CMATRIX_CPP
#define __CMATRIX_CPP

#include <iostream>
#include <cmath>

#include "../include/CMatrix.h"

CMatrix::CMatrix() {
    nRows = 0;
    nCols = 0;
    mtx = new double[0];
}

CMatrix::CMatrix(unsigned rows, unsigned cols, const double initValue) {
    nRows = rows;
    nCols = cols;
    mtx = new double[cols*rows];
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            mtx[j*nRows+i] = initValue;
        }
    }
}

CMatrix::CMatrix(const CMatrix& rhs) {
    nRows = rhs.nRows;
    nCols = rhs.nCols;
    mtx = new double[nCols*nRows];
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            mtx[j*nRows+i] = rhs.mtx[j*nRows+i];
        }
    }
}

CMatrix::~CMatrix() {
    delete[] mtx;
}

unsigned CMatrix::getRows() const {
    return nRows;
}

unsigned CMatrix::getCols() const {
    return nCols;
}

// template<typename T>
// unsigned CMatrix<T>::isErrWithMtxSize() {
//     return (mtx.size()!=nCols && mtx[0].size()!=nRows);
// }

CMatrix CMatrix::transpose() {
    CMatrix res(nCols, nRows, 0.0);

    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            res(i, j) = mtx[i*nRows+j];
        }
    }

    return res;
}

CMatrix CMatrix::linspace(const double left, const double right,
                                 const unsigned nNode) {
    CMatrix res = CMatrix(1, nNode, 0.0);
    double deltaX = (right - left) / (nNode - 1);

    for (unsigned i = 0; i < nNode; i++) {
        res(i, 0) = left + i*deltaX;
    }

    return res;
}

// template<typename T>
// bool CMatrix<T>::isLowerTriangular() {
//     for (unsigned j = 0; j < nCols; j++) {
//         for (unsigned i = i+1; i < nRows; i++) {
//             if(mtx[j][i] != 0.0) {
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// template<typename T>
// bool CMatrix<T>::isUpperTriangular() {
//     for (unsigned j = 1; j < nCols; j++) {
//         for (unsigned i = 0; i < j; i++) {
//             if(mtx[j][i] != 0.0) return false;
//         }
//     }
//     return true;
// }

double* CMatrix::getMtxAddress() {
    return &mtx[0];
}

void CMatrix::printMtx() {
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            std::cout << mtx[j*nRows+i] << " ";
        }
        std::cout << std::endl;
    }
}

double& CMatrix::operator()(const unsigned i, const unsigned j) {
    // std::cout << "Row: " << i << " Col: " << j << ": " << &mtx[i][j] << std::endl;
    return mtx[j*nRows+i];
}

const double& CMatrix::operator()(const unsigned i, const unsigned j) const {
    return mtx[j*nRows+i];
}

CMatrix& CMatrix::operator=(const CMatrix& rhs) {
    if (&rhs == this) return *this;

    delete mtx;
    nRows = rhs.getRows();
    nCols = rhs.getCols();
    mtx = new double[nCols*nRows];
    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            mtx[j*nRows+i] = rhs.mtx[j*nRows+i];
        }
    }

    return *this;
}

// TODO: Throw error if matrices are of different size!
CMatrix CMatrix::operator+(const CMatrix& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            res(i, j) = mtx[j*nRows+i] + rhs(i, j);
        }
    }

    return res;
}

// TODO: Throw error if matrices are of different size!
CMatrix& CMatrix::operator+=(const CMatrix& rhs) {
    CMatrix res = (*this) + rhs;
    (*this) = res;
    return *this;
}

// TODO: Throw error if matrices are of different size!
CMatrix CMatrix::operator-(const CMatrix& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            res(i, j) = mtx[j*nRows+i] - rhs(i, j);
        }
    }

    return res;
}

// TODO: Throw error if matrices are of different size!
CMatrix& CMatrix::operator-=(const CMatrix& rhs) {
    CMatrix res = (*this) - rhs;
    (*this) = res;
    return *this;
}

CMatrix CMatrix::operator*(const CMatrix& rhs) {
    // unsigned rhsRows = rhs.getCols();
    unsigned rhsCols = rhs.getCols();
    CMatrix res(nRows, rhsCols, 0.0);

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
    CMatrix res = (*this) * rhs;
    (*this) = res;
    return *this;
}

CMatrix CMatrix::operator+(const double& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            res(i, j) = mtx[j*nRows+i] + rhs;
        }
    }

    return res;
}


CMatrix CMatrix::operator-(const double& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            res(i, j) = mtx[j*nRows+i] - rhs;
        }
    }

    return res;
}


CMatrix CMatrix::operator*(const double& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            res(i, j) = mtx[j*nRows+i] * rhs;
        }
    }

    return res;
}


CMatrix CMatrix::operator/(const double& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            res(i, j) = mtx[j*nRows+i] / rhs;
        }
    }

    return res;
}

CMatrix CMatrix::operator^(const double& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    for (unsigned j = 0; j < nCols; j++) {
        for (unsigned i = 0; i < nRows; i++) {
            res(i, j) = pow(mtx[j*nRows+i], rhs);
        }
    }

    return res;
}

#endif
