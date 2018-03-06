#ifndef __CLINEARSYSTEM_H
#define __CLINEARSYSTEM_H

#include <vector>
#include <iostream>

class CLinearSystem {
    private:
        CMatrix<double> lhsMatrix;
        CMatrix<double> rhsVector;

    public:
        CLinearSystem(const CMatrix<double>& A,const CMatrix<double>& b);
        virtual ~CLinearSystem();

        CMatrix<double> getLhsMatrix();
        CMatrix<double> getRhsVector();
        bool isSystemValid();
        CMatrix<double> backwardSubstitution();
        CMatrix<double> forwardSubstitution();
};

// #include "../src/CLinearSystem.cpp"

#endif
