#include <iostream>

#include "../include/gtest/gtest.h"
#include "../../include/CMatrix.hpp"

namespace {
    class CMatrixTest : public ::testing::Test {
        protected:
            virtual void SetUp() {
                unsigned size = 4;
                A = new CMatrix(size, size, 2.0);
                B = new CMatrix(size, size, 1.0);
                C = new CMatrix(size, size, 3.0);
                D = new CMatrix(size, size, 4.0);
                E = new CMatrix(size, 1, 1.0);
                F = new CMatrix(size, 1, 4.0);
                G = new CMatrix(size, size, 8.0);
            }
            virtual void TearDown() {
                delete A;
                delete B;
                delete C;
                delete D;
                delete E;
                delete F;
                delete G;
            }

            CMatrix* A;
            CMatrix* B;
            CMatrix* C;
            CMatrix* D;
            CMatrix* E;
            CMatrix* F;
            CMatrix* G;
    };

    TEST_F(CMatrixTest, DefaultConstructor) {
        CMatrix mat;
        EXPECT_EQ(0, mat.getRows());
        EXPECT_EQ(0, mat.getCols());
    }

    TEST_F(CMatrixTest, CustomConstructor) {
        unsigned size = 8;
        double val = 0.0;
        CMatrix mat = CMatrix(size, size, val);
        EXPECT_EQ(size, mat.getRows());
        EXPECT_EQ(size, mat.getCols());
        // TODO: Here access operator is from another test. Think about the
        // correctness of using it here.
        for(unsigned j = 0; j < mat.getCols(); j++) {
            for(unsigned i = 0; i < mat.getRows(); i++) {
                EXPECT_EQ(val, mat(i, j));
            }
        }
    }

    TEST_F(CMatrixTest, CopyConstructor) {
        CMatrix mat = CMatrix(*B);
        EXPECT_EQ(B->getRows(), mat.getRows());
        EXPECT_EQ(B->getCols(), mat.getCols());
        // TODO: Here access operator is from another test. Think about the
        // correctness of using it here.
        for(unsigned j = 0; j < B->getCols(); j++) {
            for(unsigned i = 0; i < B->getRows(); i++) {
                EXPECT_EQ((*B)(i, j), mat(i, j));
            }
        }
    }

    TEST_F(CMatrixTest, AssignmentOperator) {
        unsigned size = 4;
        CMatrix matOne(size, size, 2.0);
        CMatrix matTwo(size, size, 3.0);
        matTwo = matOne;
        for(unsigned j = 0; j < size; j++) {
            for(unsigned i = 0; i < size; i++) {
                EXPECT_EQ(matOne(i, j), matTwo(i, j));
            }
        }
    }

    TEST_F(CMatrixTest, Transpose) {
        unsigned size = 4;
        CMatrix mat(size, size, 0.0);
        CMatrix matTranspose(size, size, 0.0);
        for (int j = 0; j < size; j++) {
            for (int i = 0; i < size; i++) {
                mat(i, j) = double(i - j);
            }
        }
        matTranspose = mat.transpose();
        for (int j = 0; j < size; j++) {
            for (int i = 0; i < size; i++) {
                EXPECT_EQ(mat(i, j), matTranspose(j, i));
            }
        }
    }

    // // TEST_F(CMatrixTest, UpperTriangular) {
    // //     unsigned size = 4;
    // //     CMatrix<int> matInt(size, size, 0);
    // //     CMatrix<double> matDbl(size, size, 0.0);
    // //     for (unsigned i = 0; i < size; i++) {
    // //         for (unsigned j = i; j < size; j++) {
    // //             matInt(i, j) = i + j;
    // //         }
    // //     }
    // //     for (unsigned i = 0; i < size; i++) {
    // //         for (unsigned j = i; j < size; j++) {
    // //             matDbl(i, j) = double(i + j);
    // //         }
    // //     }
    // //     EXPECT_TRUE(matInt.isUpperTriangular());
    // //     EXPECT_TRUE(matDbl.isUpperTriangular());
    // // }
    //
    // // TEST_F(CMatrixTest, LowerTriangular) {
    // //     unsigned size = 4;
    // //     CMatrix<int> matInt(size, size, 0);
    // //     CMatrix<double> matDbl(size, size, 0.0);
    // //     for (unsigned i = 0; i < size; i++) {
    // //         for (unsigned j = 0; j <= i; j++) {
    // //             matInt(i, j) = i + j;
    // //         }
    // //     }
    // //     for (unsigned i = 0; i < size; i++) {
    // //         for (unsigned j = 0; j <= i; j++) {
    // //             matDbl(i, j) = double(i + j);
    // //         }
    // //     }
    // //     EXPECT_TRUE(matInt.isLowerTriangular());
    // //     EXPECT_TRUE(matDbl.isLowerTriangular());
    // // }

    TEST_F(CMatrixTest, AccessOperator) {
        unsigned size = 4;
        CMatrix mat = CMatrix(size, size, 0.0);
        for (unsigned j = 0; j < size; j++) {
            for (unsigned i = 0; i < size; i++) {
                mat(i, j) = i * j;
            }
        }
        for (unsigned j = 0; j < size; j++) {
            for (unsigned i = 0; i < size; i++) {
                EXPECT_EQ(i * j, mat(i, j));
            }
        }
    }

    TEST_F(CMatrixTest, ConstAccessOperator) {
        unsigned size = 4;
        int val = 0.0;
        const CMatrix constMat = CMatrix(size, size, val);
        EXPECT_EQ(val, constMat(0, 0));
        EXPECT_EQ(val, constMat(size - 1, size - 1));
    }

    TEST_F(CMatrixTest, AdditionOperators) {
        CMatrix mat;
        CMatrix matForConst;
        const double constVal = 2.0;
        mat = (*A) + (*B);
        (*B) += (*B);
        matForConst = (*A) + constVal;
        for (unsigned j = 0; j < mat.getCols(); j++) {
            for (unsigned i = 0; i < mat.getRows(); i++) {
                EXPECT_EQ((*C)(i, j), mat(i, j));
                EXPECT_EQ((*A)(i, j), (*B)(i, j));
                EXPECT_EQ((*D)(i, j), matForConst(i, j));
            }
        }
    }

    TEST_F(CMatrixTest, SubstractionOperators) {
        CMatrix mat;
        CMatrix matForConst;
        const double constVal = 2.0;
        mat = (*C) - (*B);
        (*C) -= (*B);
        matForConst = (*D) - constVal;
        for (unsigned j = 0; j < mat.getCols(); j++) {
            for (unsigned i = 0; i < mat.getRows(); i++) {
                EXPECT_EQ((*A)(i, j), mat(i, j));
                EXPECT_EQ((*A)(i, j), (*C)(i, j));
                EXPECT_EQ((*A)(i, j), matForConst(i, j));
            }
        }
    }

    TEST_F(CMatrixTest, ProductOperators) {
        CMatrix mat;
        CMatrix matForConst;
        CMatrix vec;
        const double constVal = 2.0;
        mat = (*B) * (*B);
        vec = (*B) * (*E);
        (*B) *= (*B);
        matForConst = (*A) * constVal;
        for(unsigned i = 0; i < mat.getRows(); i++) {
            for(unsigned j = 0; j < mat.getCols(); j++) {
                EXPECT_EQ((*D)(i, j), mat(i, j));
                EXPECT_EQ((*D)(i, j), matForConst(i, j));
            }
        }
        for(unsigned i = 0; i < vec.getRows(); i++) {
            EXPECT_EQ((*F)(i, 0), vec(i, 0));
        }
    }

    TEST_F(CMatrixTest, DivisionOperators) {
        CMatrix matForConst;
        const double constVal = 2.0;
        matForConst = (*A) / constVal;
        for(unsigned i = 0; i < matForConst.getRows(); i++) {
            for(unsigned j = 0; j < matForConst.getCols(); j++) {
                EXPECT_EQ((*B)(i, j), matForConst(i, j));
            }
        }
    }

    TEST_F(CMatrixTest, PowerOperator) {
        CMatrix matForConst;
        const double constVal = 2.0;
        matForConst = (*A) ^ constVal;
        for(unsigned i = 0; i < matForConst.getRows(); i++) {
            for(unsigned j = 0; j < matForConst.getCols(); j++) {
                EXPECT_EQ((*D)(i, j), matForConst(i, j));
            }
        }
    }

    TEST_F(CMatrixTest, Linspace) {
        CMatrix lin;
        const double left = 0.0;
        const double right = 3.0;
        const unsigned nNode = 4.0;
        lin = CMatrix::linspace(left, right, nNode);
        EXPECT_EQ(0.0, lin(0, 0));
        EXPECT_EQ(1.0, lin(1, 0));
        EXPECT_EQ(2.0, lin(2, 0));
        EXPECT_EQ(3.0, lin(3, 0));
    }

    TEST_F(CMatrixTest, Determinant) {
        CMatrix mat = CMatrix(2, 2, 0.0);
        mat(0, 0) = 1.0;
        mat(0, 1) = 2.0;
        mat(1, 0) = 3.0;
        mat(1, 1) = 4.0;
        EXPECT_NEAR(2.0, mat.determinant(), 0.0001);
        // mat.printMtx();
        mat(0, 0) = -1.0;
        mat(0, 1) = 2.0;
        mat(1, 0) = -3.0;
        mat(1, 1) = 4.0;
        EXPECT_NEAR(-2.0, mat.determinant(), 0.0001);
        // mat.printMtx();
        CMatrix matNew = CMatrix(3, 3, 1.0);
        EXPECT_NEAR(0.0, matNew.determinant(), 0.0001);
        matNew(0, 0) = 1.0;
        matNew(0, 1) = 2.0;
        matNew(0, 2) = 1.0;
        matNew(1, 0) = 4.0;
        matNew(1, 1) = 5.0;
        matNew(1, 2) = 6.0;
        matNew(2, 0) = 7.0;
        matNew(2, 1) = 8.0;
        matNew(2, 2) = 9.0;
        EXPECT_NEAR(-6.0, matNew.determinant(), 0.0001);
        // matNew.printMtx();
    }

    TEST_F(CMatrixTest, Inverse) {
        CMatrix mat = CMatrix(2, 2, 0.0);
        CMatrix inv;
        mat(0, 0) = 1.0;
        mat(0, 1) = 2.0;
        mat(1, 0) = 3.0;
        mat(1, 1) = 4.0;
        inv = mat.inverse();
        EXPECT_NEAR(-2.0, inv(0, 0), 0.0001);
        EXPECT_NEAR(1.0, inv(0, 1), 0.0001);
        EXPECT_NEAR(1.5, inv(1, 0), 0.0001);
        EXPECT_NEAR(-0.5, inv(1, 1), 0.0001);
        // mat.printMtx();
        // inv.printMtx();
    }
}
