#ifndef __CMATRIX_H
#define __CMATRIX_H

#define F77NAME(x) x##_
extern "C" {
    void F77NAME(dgetrf)(const int& m, const int& n, const double* A,
                         const int& lda, int* ipiv, int& info);
}

class CMatrix {
    private:
        unsigned nRows;
        unsigned nCols;
        double* mtx;

    public:
        CMatrix();
        CMatrix(unsigned rows, unsigned cols, const double initValue);
        CMatrix(const CMatrix& rhs);
        virtual ~CMatrix();

        unsigned getRows() const;
        unsigned getCols() const;
        // unsigned isErrWithMtxSize();
        void printMtx();
        CMatrix transpose();
        // bool isLowerTriangular();
        // bool isUpperTriangular();
        double* getMtxAddress();
        static CMatrix linspace(const double left, const double right,
                                const unsigned nNode);
        double determinant();

        // Adress operator after type T is to be able to assign values when
        // there is an assignment like A(i, j) = 3
        double& operator()(const unsigned i, const unsigned j);
        const double& operator()(const unsigned i, const unsigned j) const;
        CMatrix& operator=(const CMatrix& rhs);
        // TODO: Throw error if matrices are of different size!
        CMatrix operator+(const CMatrix& rhs);
        // TODO: Throw error if matrices are of different size!
        CMatrix& operator+=(const CMatrix& rhs);
        // TODO: Throw error if matrices are of different size!
        CMatrix operator-(const CMatrix& rhs);
        // TODO: Throw error if matrices are of different size!
        CMatrix& operator-=(const CMatrix& rhs);
        // TODO: Throw error if matrices are of incorrect size!
        CMatrix operator*(const CMatrix& rhs);
        CMatrix& operator*=(const CMatrix& rhs);
        CMatrix operator+(const double& rhs);
        CMatrix operator-(const double& rhs);
        CMatrix operator*(const double& rhs);
        CMatrix operator/(const double& rhs);
        CMatrix operator^(const double& rhs);
};

#endif
