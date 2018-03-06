#ifndef __CLINEARSYSTEM_CPP
#define __CLINEARSYSTEM_CPP

#include <iostream>

#include "../include/CMatrix.h"
#include "../include/CLinearSystem.h"

CLinearSystem::CLinearSystem(const CMatrix<double>& A,const CMatrix<double>& b) {
    lhsMatrix = CMatrix<double>(A);
    rhsVector = CMatrix<double>(b);
    if(!isSystemValid())
        throw std::runtime_error("LHS matrix and RHS vector incompatible");
}

CLinearSystem::~CLinearSystem() {}

CMatrix<double> CLinearSystem::getLhsMatrix() {
    CMatrix<double> res = CMatrix<double>(lhsMatrix);
    return res;
}

CMatrix<double> CLinearSystem::getRhsVector() {
    CMatrix<double> res = rhsVector;
    return res;
}

bool CLinearSystem::isSystemValid() {
    bool isSquareMatrix = lhsMatrix.getRows() == lhsMatrix.getCols();
    bool isCompleteVector = lhsMatrix.getRows() == rhsVector.getRows();
    if(!isSquareMatrix || !isCompleteVector) return false;
    return true;
}

CMatrix<double> CLinearSystem::backwardSubstitution() {
    if(!lhsMatrix.isUpperTriangular())
        throw std::runtime_error("LHS matrix should be upper triangular");
    CMatrix<double> res = CMatrix<double>(rhsVector.getRows(), 1, 0.0);
    for (int i = rhsVector.getRows()-1; i >= 0; i--) {
        for (int j = rhsVector.getRows()-1; j >= i+1; j--) {
            res(i, 0) = res(i, 0) + lhsMatrix(i, j)*res(j, 0);
        }
        res(i, 0) = (rhsVector(i, 0)-res(i, 0)) / lhsMatrix(i, i);
    }
    return res;
}

CMatrix<double> CLinearSystem::forwardSubstitution() {
    if(!lhsMatrix.isLowerTriangular())
        throw std::runtime_error("LHS matrix should be lower triangular");
    CMatrix<double> res = CMatrix<double>(rhsVector.getRows(), 1, 0.0);
    for (unsigned i = 0; i < rhsVector.getRows(); i++) {
        for (unsigned j = 0; j < i; j++) {
            res(i, 0) = res(i, 0) + lhsMatrix(i, j)*res(j, 0);
        }
        res(i, 0) = (rhsVector(i, 0)-res(i, 0)) / lhsMatrix(i, i);
    }
    return res;
}

#endif
