// #ifndef __CMATRIX_CPP
// #define __CMATRIX_CPP
//
// #include <../include/matrix.h>
//
// template<typename T>
// CMatrix<T>::CMatrix(unsigned rows, unsigned cols, const T& initValue) {
//     nRows = rows;
//     nCols = cols;
//     mtx.resize(nRows);
//     for(unsigned i = 0; i < nRows; i++) {
//         mtx[i].resize(nCols, initValue);
//     }
// }
//
// template<typename T>
// CMatrix<T>::CMatrix(const CMatrix<T>& rhs) {
//     nRows = rhs.nRows;
//     nCols = rhs.nCols;
//     mtx = rhs.mtx;
// }
//
// template<typename T>
// CMatrix<T>::~CMatrix() {}
//
// template<typename T>
// unsigned CMatrix<T>::getRows(){
//     return nRows;
// }
//
// template<typename T>
// unsigned CMatrix<T>::getCols(){
//     return nCols;
// }
//
// #endif
