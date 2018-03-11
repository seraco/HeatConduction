// #ifndef __CLINEARSYSTEM_H
// #define __CLINEARSYSTEM_H
//
// #include <vector>
// #include <iostream>
//
// #define F77NAME(x) x##_
// extern "C" {
//     void F77NAME(dgesv)(const int& n, const int& nrhs, const double* A,
//                         const int& lda, int* ipiv, double* B,
//                         const int& ldb, int& info);
//     // void F77NAME(dgemv) (const char& trans, const int& m,
//     //                      const int& n, const double& alpha,
//     //                      const double* A, const int& lda,
//     //                      const double* x, const int& incx,
//     //                      const double& beta, double* y,
//     //                      const int& incy);
// }
//
// class CLinearSystem {
//     private:
//         CMatrix<double> lhsMatrix;
//         CMatrix<double> rhsVector;
//
//     public:
//         CLinearSystem(const CMatrix<double>& A,const CMatrix<double>& b);
//         virtual ~CLinearSystem();
//
//         CMatrix<double> getLhsMatrix();
//         CMatrix<double> getRhsVector();
//         bool isSystemValid();
//         // CMatrix<double> backwardSubstitution();
//         // CMatrix<double> forwardSubstitution();
//         CMatrix<double> solve();
// };
//
// // #include "../src/CLinearSystem.cpp"
//
// #endif
