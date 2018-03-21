/*!
 * @file CMatrix.hpp
 * @brief Headers of the main subroutines for defining matrices and their operations.
 *        The implementation is in the <i>CMatrix.cpp</i> file.
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

#ifndef __CMATRIX_HPP
#define __CMATRIX_HPP

#define F77NAME(x) x##_
extern "C" {
    void F77NAME(dgetrf)(const int& m, const int& n, const double* A,
                         const int& lda, int* ipiv, int& info);
    void F77NAME(dgetri)(const int& n, const double* A,
                         const int& lda, int* ipiv,
                         double* work, const int& lwork, int& info);
}

/*!
 * @class CMatrix
 * @brief Class to define matrices and their operations.
 */
class CMatrix {
    private:
        unsigned nRows;     /*!< @brief Number of rows.*/
        unsigned nCols;     /*!< @brief Number of columns.*/
        double* mtx;        /*!< @brief Pointer at the beginning of matrix entries.*/

    public:
        /*!
         * @brief Constructor of the class.
         */
        CMatrix();

        /*!
         * @brief Constructor of the class.
         * @param[in] rows - Number of rows.
         * @param[in] cols - Number of columns.
         * @param[in] initValue - Initial value to populate matrix.
         */
        CMatrix(unsigned rows, unsigned cols, const double initValue);

        /*!
         * @brief Copy constructor of the class.
         * @param[in] rhs - Matrix to copy.
         */
        CMatrix(const CMatrix& rhs);

        /*!
         * @brief Destructor of the class.
         */
        virtual ~CMatrix();

        /*!
         * @brief Get number of rows.
         * @return Number of rows.
         */
        unsigned getRows() const;

        /*!
         * @brief Get number of columns.
         * @return Number of columns.
         */
        unsigned getCols() const;

        /*!
         * @brief Print matrix to the console.
         */
        void printMtx();

        /*!
         * @brief Compute the transpose.
         * @return Transpose of the matrix.
         */
        CMatrix transpose();

        /*!
         * @brief Get the pointer at the beginning of the entries.
         * @return Pointer at the beginning of the entries.
         */
        double* getMtxAddress();

        /*!
         * @brief Construct a linear space between left and right.
         * @param[in] left - Initial left node.
         * @param[in] right - Final right node.
         * @param[in] nNode - Number of nodes in the linspace.
         * @return Linspace.
         */
        static CMatrix linspace(const double left, const double right,
                                const unsigned nNode);

        /*!
         * @brief Compute the determinant of the matrix.
         * @return Determinant.
         */
        double determinant();

        /*!
         * @brief Compute the inverse of the matrix.
         * @return Inverse matrix.
         */
        CMatrix inverse();

        /*!
         * @brief Operator overloading of parenthesis to access entries.
         * @param[in] i - Row number.
         * @param[in] j - Column number.
         * @return Entry of the matrix at row i and column j.
         */
        double& operator()(const unsigned i, const unsigned j);

        /*!
         * @brief Operator overloading of parenthesis to access entries.
         * @param[in] i - Row number.
         * @param[in] j - Column number.
         * @return Entry of the matrix at row i and column j.
         */
        const double& operator()(const unsigned i, const unsigned j) const;

        /*!
         * @brief Operator overloading of equal sign.
         * @param[in] rhs - RHS matrix to copy.
         * @return Matrix with copied entries from rhs.
         */
        CMatrix& operator=(const CMatrix& rhs);

        /*!
         * @brief Operator overloading of plus sign to sum matrices.
         * @param[in] rhs - RHS matrix to sum.
         * @return Matrix with summed entries.
         */
        CMatrix operator+(const CMatrix& rhs);

        /*!
         * @brief Operator overloading of plus-equal sign to sum matrices.
         * @param[in] rhs - RHS matrix to sum.
         * @return Matrix with summed entries.
         */
        CMatrix& operator+=(const CMatrix& rhs);

        /*!
         * @brief Operator overloading of minus sign to substract matrices.
         * @param[in] rhs - RHS matrix to substract.
         * @return Matrix with substracted entries.
         */
        CMatrix operator-(const CMatrix& rhs);

        /*!
         * @brief Operator overloading of minus-equal sign to substract matrices.
         * @param[in] rhs - RHS matrix to substract.
         * @return Matrix with substracted entries.
         */
        CMatrix& operator-=(const CMatrix& rhs);

        /*!
         * @brief Operator overloading of asterisk sign to multiply matrices.
         * @param[in] rhs - RHS matrix to multiply.
         * @return Product of the two matrices.
         */
        CMatrix operator*(const CMatrix& rhs);

        /*!
         * @brief Operator overloading of asterisk-equal sign to multiply matrices.
         * @param[in] rhs - RHS matrix to multiply.
         * @return Product of the two matrices.
         */
        CMatrix& operator*=(const CMatrix& rhs);

        /*!
         * @brief Operator overloading of plus sign to sum a constant to a matrix.
         * @param[in] rhs - RHS constant to sum.
         * @return Matrix with the constant summed.
         */
        CMatrix operator+(const double& rhs);

        /*!
         * @brief Operator overloading of minus sign to substract a constant from
         *        a matrix.
         * @param[in] rhs - RHS constant to substract.
         * @return Matrix with the constant substracted.
         */
        CMatrix operator-(const double& rhs);

        /*!
         * @brief Operator overloading of asterisk sign to multiply a constant
         *        with a matrix.
         * @param[in] rhs - RHS constant to multiply.
         * @return Matrix with the constant multiplied.
         */
        CMatrix operator*(const double& rhs);

        /*!
         * @brief Operator overloading of slash sign to divide a constant with
         *        a matrix.
         * @param[in] rhs - RHS constant to divide.
         * @return Matrix with the constant divided.
         */
        CMatrix operator/(const double& rhs);

        /*!
         * @brief Operator overloading of power sign to take the power of each
         *        matrix entry with the constant.
         * @param[in] rhs - RHS constant to take the power.
         * @return Matrix with each entry to the power of the constant.
         */
        CMatrix operator^(const double& rhs);
};

#endif
