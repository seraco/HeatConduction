#ifndef __CLINEARSYSTEM_H
#define __CLINEARSYSTEM_H

#define F77NAME(x) x##_
extern "C" {
    void F77NAME(dgesv)(const int& n, const int& nrhs, const double* A,
                        const int& lda, int* ipiv, double* B,
                        const int& ldb, int& info);
    // void F77NAME(dgemv) (const char& trans, const int& m,
    //                      const int& n, const double& alpha,
    //                      const double* A, const int& lda,
    //                      const double* x, const int& incx,
    //                      const double& beta, double* y,
    //                      const int& incy);
}

class CLinearSystem {
    private:
        CMatrix lhsMatrix;
        CMatrix rhsVector;

    public:
        CLinearSystem(const CMatrix& A, const CMatrix& b);
        virtual ~CLinearSystem();

        CMatrix getLhsMatrix();
        CMatrix getRhsVector();
        bool isSystemValid();
        CMatrix solve();
};

#endif
