#ifndef __CMATRIX_CPP
#define __CMATRIX_CPP

#include <iostream>

#include "../include/CMatrix.h"

template<typename T>
CMatrix<T>::CMatrix() {
    nRows = 0;
    nCols = 0;
}

template<typename T>
CMatrix<T>::CMatrix(unsigned rows, unsigned cols, const T& initValue) {
    nRows = rows;
    nCols = cols;
    mtx.resize(nRows);
    for(unsigned i = 0; i < nRows; i++) {
        mtx[i].resize(nCols, initValue);
    }
}

// TODO: Not needed¿?
// template<typename T>
// CMatrix<T>::CMatrix(const CMatrix<T>& rhs) {
//     nRows = rhs.nRows;
//     nCols = rhs.nCols;
//     mtx = rhs.mtx;
// }

template<typename T>
CMatrix<T>::~CMatrix() {}

template<typename T>
unsigned CMatrix<T>::getRows() const {
    return nRows;
}

template<typename T>
unsigned CMatrix<T>::getCols() const {
    return nCols;
}

template<typename T>
unsigned CMatrix<T>::isErrWithMtxSize() {
    return (mtx.size()!=nRows && mtx[0].size()!=nCols);
}

template<typename T>
CMatrix<T> CMatrix<T>::transpose() {
    CMatrix<T> res(nRows, nCols, 0.0);

    for (unsigned i = 0; i < nRows; i++) {
        for (unsigned j = 0; j < nCols; j++) {
            res(i, j) = mtx[j][i];
        }
    }

    return res;
}

template<typename T>
bool CMatrix<T>::isLowerTriangular() {
    for (unsigned i = 0; i < nRows; i++) {
        for (unsigned j = i+1; j < nCols; j++) {
            if(mtx[i][j] != 0.0) {
                return false;
            }
        }
    }
    return true;
}

template<typename T>
bool CMatrix<T>::isUpperTriangular() {
    for (unsigned i = 1; i < nRows; i++) {
        for (unsigned j = 0; j < i; j++) {
            if(mtx[i][j] != 0.0) return false;
        }
    }
    return true;
}

template<typename T>
void CMatrix<T>::printMtx() {
    for (unsigned i = 0; i < nRows; i++) {
        for (unsigned j = 0; j < nCols; j++) {
            std::cout << mtx[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template<typename T>
T& CMatrix<T>::operator()(const unsigned i, const unsigned j) {
    // std::cout << "Row: " << i << " Col: " << j << ": " << &mtx[i][j] << std::endl;
    return mtx[i][j];
}

template<typename T>
const T& CMatrix<T>::operator()(const unsigned i, const unsigned j) const {
    return mtx[i][j];
}

// TODO: Not needed¿?
// template<typename T>
// CMatrix<T>& CMatrix<T>::operator=(CMatrix<T>& rhs) {
//     if (&rhs == this) return *this;
//
//     nRows = rhs.getRows();
//     nCols = rhs.getCols();
//     mtx = rhs.mtx;
//
//     return *this;
// }

// TODO: Throw error if matrices are of different size!
template<typename T>
CMatrix<T> CMatrix<T>::operator+(const CMatrix<T>& rhs) {
    CMatrix<T> res(nRows, nCols, 0.0);

    for (unsigned i = 0; i < nRows; i++) {
        for (unsigned j = 0; j < nCols; j++) {
            res(i,j) = mtx[i][j] + rhs(i,j);
        }
    }

    return res;
}

// TODO: Throw error if matrices are of different size!
template<typename T>
CMatrix<T>& CMatrix<T>::operator+=(const CMatrix<T>& rhs) {
    CMatrix res = (*this) + rhs;
    (*this) = res;
    return *this;
}

// TODO: Throw error if matrices are of different size!
template<typename T>
CMatrix<T> CMatrix<T>::operator-(const CMatrix<T>& rhs) {
    CMatrix<T> res(nRows, nCols, 0.0);

    for (unsigned i = 0; i < nRows; i++) {
        for (unsigned j = 0; j < nCols; j++) {
            res(i,j) = mtx[i][j] - rhs(i,j);
        }
    }

    return res;
}

// TODO: Throw error if matrices are of different size!
template<typename T>
CMatrix<T>& CMatrix<T>::operator-=(const CMatrix<T>& rhs) {
    CMatrix res = (*this) - rhs;
    (*this) = res;
    return *this;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator*(const CMatrix<T>& rhs) {
    // unsigned rhsRows = rhs.getCols();
    unsigned rhsCols = rhs.getCols();
    CMatrix res(nRows, rhsCols, 0.0);

    for (unsigned i = 0; i < nRows; i++) {
        for (unsigned j = 0; j < rhsCols; j++) {
            for (unsigned k = 0; k < nCols; k++) {
                res(i, j) += mtx[i][k] * rhs(k, j);
            }
        }
    }

    return res;
}

template<typename T>
CMatrix<T>& CMatrix<T>::operator*=(const CMatrix& rhs) {
    CMatrix res = (*this) * rhs;
    (*this) = res;
    return *this;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator+(const T& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    for (unsigned i = 0; i < nRows; i++) {
        for (unsigned j = 0; j < nCols; j++) {
            res(i, j) = mtx[i][j] + rhs;
        }
    }

    return res;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator-(const T& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    for (unsigned i = 0; i < nRows; i++) {
        for (unsigned j = 0; j < nCols; j++) {
            res(i, j) = mtx[i][j] - rhs;
        }
    }

    return res;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator*(const T& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    for (unsigned i = 0; i < nRows; i++) {
        for (unsigned j = 0; j < nCols; j++) {
            res(i, j) = mtx[i][j] * rhs;
        }
    }

    return res;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator/(const T& rhs) {
    CMatrix res(nRows, nCols, 0.0);

    for (unsigned i = 0; i < nRows; i++) {
        for (unsigned j = 0; j < nCols; j++) {
            res(i, j) = mtx[i][j] / rhs;
        }
    }

    return res;
}

#endif
