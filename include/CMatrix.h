#ifndef __CMATRIX_H
#define __CMATRIX_H

#include <vector>
#include <iostream>

template <typename T> class CMatrix {
    private:
        unsigned nRows;
        unsigned nCols;
        std::vector< std::vector<T> > mtx;

    public:
        CMatrix();
        CMatrix(unsigned rows, unsigned cols, const T& initValue);
        // TODO: Not needed¿?
        // CMatrix(const CMatrix<T>& rhs);
        virtual ~CMatrix();

        unsigned getRows() const;
        unsigned getCols() const;
        unsigned isErrWithMtxSize();
        void printMtx();

        // Adress operator after type T is to be able to assign values when
        // there is an assignment like A(i, j) = 3
        T& operator()(const unsigned i, const unsigned j);
        const T& operator()(const unsigned i, const unsigned j) const;
        // TODO: Not needed¿?
        // CMatrix<T>& operator=(CMatrix<T>& rhs);
        // TODO: Throw error if matrices are of different size!
        CMatrix<T> operator+(const CMatrix<T>& rhs);
        // TODO: Throw error if matrices are of different size!
        CMatrix<T>& operator+=(const CMatrix<T>& rhs);
        // TODO: Throw error if matrices are of different size!
        CMatrix<T> operator-(const CMatrix<T>& rhs);
        // TODO: Throw error if matrices are of different size!
        CMatrix<T>& operator-=(const CMatrix<T>& rhs);
        // TODO: Throw error if matrices are of incorrect size!
        CMatrix<T> operator*(const CMatrix<T>& rhs);
        CMatrix<T>& operator*=(const CMatrix& rhs);
        CMatrix<T> operator+(const T& rhs);
        CMatrix<T> operator-(const T& rhs);
        CMatrix<T> operator*(const T& rhs);
        CMatrix<T> operator/(const T& rhs);
};

#include "../src/CMatrix.cpp"

#endif
