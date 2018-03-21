#ifndef __CLINEARSYSTEM_HPP
#define __CLINEARSYSTEM_HPP

#include "CMatrix.hpp"

#define F77NAME(x) x##_
extern "C" {
    void F77NAME(dgesv)(const int& n, const int& nrhs, const double* A,
                        const int& lda, int* ipiv, double* B,
                        const int& ldb, int& info);
    double F77NAME(ddot) (const int& n,
                          const double *x, const int& incx,
                          const double *y, const int& incy);
    double F77NAME(dnrm2) (const int& n,
                           const double *x, const int& incx);
    // void F77NAME(dgemm) (const char& transa, const char& transb,
    //                      const int& nrowsa,
    //                      const int& ncolsb,
    //                      const int& ncolsa,
    //                      const double& alpha,
    //                      const double* A, const int& lda,
    //                      const double* B, const int& ldb,
    //                      const double& beta,
    //                      double* C, const int& ldc);
    void F77NAME(dgemv) (const char& trans,
                         const int& nrowsa,
                         const int& ncolsa,
                         const double& alpha,
                         const double* A, const int& lda,
                         const double* x, const int& incx,
                         const double& beta,
                         double* y, const int& incy);
    void F77NAME(daxpy) (const int& n,
                         const double& alpha,
                         const double* x, const int& incx,
                         double* y, const int& incy);
    void F77NAME(dcopy)	(const int& n,
                         const double* x, const int& incx,
                         double* y, const int& incy);
}

class CLinearSystem {
    private:
        CMatrix lhsMatrix;
        CMatrix rhsVector;

        static double parallelDot(double* x, double* y, unsigned n);

    public:
        CLinearSystem(const CMatrix& A, const CMatrix& b);
        virtual ~CLinearSystem();

        CMatrix getLhsMatrix();
        CMatrix getRhsVector();
        bool isSystemValid();
        CMatrix directSolve();
        CMatrix iterativeSolve();
};

#endif
