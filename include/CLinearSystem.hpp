/*!
 * @file CLinearSystem.hpp
 * @brief Headers of the main subroutines for solving linear systems of equations.
 *        The implementation is in the <i>CLinearSystem.cpp</i> file.
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

/*!
 * @class CLinearSystem
 * @brief Class to solve linear systems of equations.
 */
class CLinearSystem {
    private:
        CMatrix lhsMatrix;  /*!< @brief A matrix of the system.*/
        CMatrix rhsVector;  /*!< @brief b vector of the system.*/

        /*!
         * @brief Subroutine to know if the system is valid to solve.
         * @return Boolean to know if the system is valid to solve.
         */
        bool isSystemValid();

        /*!
         * @brief Parallel dot product of two vectors.
         * @param[in] x - First vector.
         * @param[in] y - Second vector.
         * @param[in] n - Size of the vectors.
         */
        static double parallelDot(double* x, double* y, unsigned n);

    public:
        /*!
         * @brief Constructor of the class.
         * @param[in] A - LHS matrix of coefficients.
         * @param[in] b - RHS vector.
         */
        CLinearSystem(const CMatrix& A, const CMatrix& b);

        /*!
         * @brief Destructor of the class.
         */
        virtual ~CLinearSystem();

        /*!
         * @brief Get LHS matrix of coefficients.
         * @return LHS matrix of coefficients.
         */
        CMatrix getLhsMatrix();

        /*!
         * @brief Get RHS vector.
         * @return RHS vector.
         */
        CMatrix getRhsVector();

        /*!
         * @brief Direct solution of the system with LU decomposition.
         * @return Vector of unknowns.
         */
        CMatrix directSolve();

        /*!
         * @brief Iterative solution of the system with CG method.
         * @return Vector of unknowns.
         */
        CMatrix iterativeSolve();
};

#endif
