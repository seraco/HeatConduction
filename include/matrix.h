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
        CMatrix() {
            nRows = 0;
            nCols = 0;
        }
        CMatrix(unsigned rows, unsigned cols, const T& initValue) {
            nRows = rows;
            nCols = cols;
            mtx.resize(nRows);
            for(unsigned i = 0; i < nRows; i++) {
                mtx[i].resize(nCols, initValue);
            }
        }
        CMatrix(const CMatrix<T>& rhs) {
            nRows = rhs.nRows;
            nCols = rhs.nCols;
            mtx = rhs.mtx;
        }
        virtual ~CMatrix() {}

        unsigned getRows() {
            return nRows;
        }
        unsigned getCols() {
            return nCols;
        }
        unsigned isErrWithMtxSize() {
            return (mtx.size()!=nRows && mtx[0].size()!=nCols);
        }
        T getEntry(unsigned i, unsigned j) {
            return mtx[i][j];
        }
        // Adress operator after type T is to be able to assign values when
        // there is an assignment like A(i, j) = 3
        T& operator()(const unsigned i, const unsigned j) {
            // std::cout << "Row: " << i << " Col: " << j << ": " << &mtx[i][j] << std::endl;
            return mtx[i][j];
        }
        // const T operator()(const unsigned i, const unsigned j) const {
        //     return mtx[i][j];
        // }
};

#endif
