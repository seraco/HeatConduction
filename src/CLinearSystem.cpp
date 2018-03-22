/*!
 * @file CLinearSystem.cpp
 * @brief The main subroutines for solving linear systems of equations.
 * @author S.Ramon (seraco)
 * @version 0.0.1
 *
 * Copyright 2018 S.Ramon
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __CLINEARSYSTEM_CPP
#define __CLINEARSYSTEM_CPP

#include <iostream>
#include <mpi.h>
#include <stdexcept>

#include "../include/CMatrix.hpp"
#include "../include/CLinearSystem.hpp"

CLinearSystem::CLinearSystem(const CMatrix& A, const CMatrix& b) {
    /*--- Initialize properties. ---*/
    lhsMatrix = CMatrix(A);
    rhsVector = CMatrix(b);

    /*--- Check if the system is valid. ---*/
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

CMatrix CLinearSystem::directSolve() {
    /*--- Initialize variables to be used in the subroutine. ---*/
    const unsigned size = lhsMatrix.getRows();
    const unsigned nRhs = 1;
    int info = 0;
    CMatrix A = lhsMatrix;
    CMatrix b = rhsVector;
    int* vPivPtr = new int[size];
    double* APtr = A.getMtxAddress();
    double* bPtr = b.getMtxAddress();

    /*--- Solve system with LAPACK subroutine. ---*/
    F77NAME(dgesv)(size, nRhs, APtr, size, vPivPtr, bPtr, size, info);

    /*--- Release allocated memory. ---*/
    delete[] vPivPtr;

    return b;
}

CMatrix CLinearSystem::iterativeSolve() {
    /*--- Initialize variables to be used in the subroutine. ---*/
    const unsigned n = lhsMatrix.getRows();
    double* r = new double[n];
    double* p = new double[n];
    double* t = new double[n];
    int k;
    double alpha;
    double beta;
    double eps;
    double tol = 0.00001;
    CMatrix A = lhsMatrix;
    CMatrix b = rhsVector;
    CMatrix x = rhsVector;
    double* APtr = A.getMtxAddress();
    double* bPtr = b.getMtxAddress();
    double* xPtr = x.getMtxAddress();

    /*--- CG method algorithm. ---*/
    F77NAME(dcopy)(n, bPtr, 1, r, 1);
    F77NAME(dgemv)('N', n, n, -1.0, APtr, n, xPtr, 1, 1.0, r, 1);
    F77NAME(dcopy)(n, r, 1, p, 1);
    k = 0;
    do {
        F77NAME(dgemv)('N', n, n, 1.0, APtr, n, p, 1, 0.0, t, 1);
        alpha = parallelDot(t, p, n);
        alpha = parallelDot(r, r, n) / alpha;
        beta = parallelDot(r, r, n);

        F77NAME(daxpy)(n, alpha, p, 1, xPtr, 1);
        F77NAME(daxpy)(n, -alpha, t, 1, r, 1);

        eps = F77NAME(dnrm2)(n, r, 1);
        if (eps < tol*tol) {
            break;
        }
        beta = parallelDot(r, r, n) / beta;

        F77NAME(dcopy)(n, r, 1, t, 1);
        F77NAME(daxpy)(n, beta, p, 1, t, 1);
        F77NAME(dcopy)(n, t, 1, p, 1);

        k++;
    } while (k < 5000);

    /*--- Release allocated memory. ---*/
    delete[] r;
    delete[] p;
    delete[] t;

    return x;
}

double CLinearSystem::parallelDot(double* x, double* y, unsigned n) {
    /*--- Initialize variables to be used in the subroutine. ---*/
    double dot = 0.0, res = 0.0;
    unsigned size;
    int rank;
    int nRanks;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nRanks);
    double* xInit = x;
    double* yInit = y;

    /*--- Divide dot product between ranks 0 and 1. ---*/
    if (rank == 0) {
        size = n / nRanks;
        dot = F77NAME(ddot)(size, xInit, 1, yInit, 1);
    } else {
        size = n / nRanks + n % nRanks;
        xInit += n / nRanks;
        yInit += n / nRanks;
        dot = F77NAME(ddot)(size, xInit, 1, yInit, 1);
    }

    /*--- Combine the results from ranks 0 and 1. ---*/
    MPI_Allreduce(&dot, &res, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    return res;
}

// void CLinearSystem::parallelMul(double* A, double* x, double* y, unsigned n) {
//     for (unsigned i = 0; i < n; i++) {
//         y[i] = parallelDot(A[i*n], x, n);
//     }
// }

#endif
