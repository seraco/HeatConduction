#ifndef __CLINEARSYSTEM_CPP
#define __CLINEARSYSTEM_CPP

#include <iostream>

#include "../include/CMatrix.h"
#include "../include/CLinearSystem.h"

CLinearSystem::CLinearSystem(const CMatrix& A, const CMatrix& b) {
    lhsMatrix = CMatrix(A);
    rhsVector = CMatrix(b);
    if(!isSystemValid())
        throw std::runtime_error("LHS matrix and RHS vector incompatible");
}

CLinearSystem::~CLinearSystem() {}

CMatrix CLinearSystem::getLhsMatrix() {
    CMatrix res = CMatrix(lhsMatrix);
    return res;
}

CMatrix CLinearSystem::getRhsVector() {
    CMatrix res = rhsVector;
    return res;
}

bool CLinearSystem::isSystemValid() {
    bool isSquareMatrix = lhsMatrix.getRows() == lhsMatrix.getCols();
    bool isCompleteVector = lhsMatrix.getRows() == rhsVector.getRows();
    if(!isSquareMatrix || !isCompleteVector) return false;
    return true;
}

CMatrix CLinearSystem::solve() {
    const unsigned size = lhsMatrix.getRows();
    const unsigned nRhs = 1;
    int info = 0;
    CMatrix A = lhsMatrix;
    CMatrix b = rhsVector;
    int* vPivPtr = new int[size];
    // A.printMtx();
    // b.printMtx();
    // vPiv.printMtx();
    double* APtr = A.getMtxAddress();
    double* bPtr = b.getMtxAddress();
    // std::cout << *(bPtr+3) << std::endl;
    // std::cout << *(vPivPtr+3) << std::endl;
    F77NAME(dgesv)(size, nRhs, APtr, size, vPivPtr, bPtr, size, info);
    // std::cout << info << std::endl;
    delete[] vPivPtr;
    return b;
}

#endif
