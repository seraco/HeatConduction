#include <iostream>

#include "gtest/gtest.h"
#include "../../include/CMatrixSymmetric.hpp"

namespace {
    class CMatrixSymmetricTest : public ::testing::Test {
        protected:
            virtual void SetUp() {
                unsigned size = 4;
                A = new CMatrixSymmetric(size, size, 2.0);
                B = new CMatrixSymmetric(size, size, 1.0);
                C = new CMatrixSymmetric(size, size, 3.0);
                D = new CMatrixSymmetric(size, size, 4.0);
                E = new CMatrixSymmetric(size, 1, 1.0);
                F = new CMatrixSymmetric(size, 1, 4.0);
                G = new CMatrixSymmetric(size, size, 8.0);
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

            CMatrixSymmetric* A;
            CMatrixSymmetric* B;
            CMatrixSymmetric* C;
            CMatrixSymmetric* D;
            CMatrixSymmetric* E;
            CMatrixSymmetric* F;
            CMatrixSymmetric* G;
    };

    TEST_F(CMatrixSymmetricTest, DefaultConstructor) {
        CMatrixSymmetric mat;
        EXPECT_EQ(0, mat.getRows());
        EXPECT_EQ(0, mat.getCols());
    }

    TEST_F(CMatrixSymmetricTest, CustomConstructor) {
        unsigned size = 8;
        double val = 0.0;
        CMatrixSymmetric mat = CMatrixSymmetric(size, size, val);
        EXPECT_EQ(size, mat.getRows());
        EXPECT_EQ(size, mat.getCols());
        for(unsigned j = 0; j < mat.getCols(); j++) {
            for(unsigned i = 0; i < mat.getRows(); i++) {
                EXPECT_EQ(val, mat(i, j));
            }
        }
    }

    TEST_F(CMatrixSymmetricTest, CopyConstructor) {
        CMatrixSymmetric mat = CMatrixSymmetric(*B);
        EXPECT_EQ(B->getRows(), mat.getRows());
        EXPECT_EQ(B->getCols(), mat.getCols());
        for(unsigned j = 0; j < B->getCols(); j++) {
            for(unsigned i = 0; i < B->getRows(); i++) {
                EXPECT_EQ((*B)(i, j), mat(i, j));
            }
        }
    }

    TEST_F(CMatrixSymmetricTest, AssignmentOperator) {
        unsigned size = 4;
        CMatrixSymmetric matOne(size, size, 2.0);
        CMatrixSymmetric matTwo(size, size, 3.0);
        matTwo = matOne;
        for(unsigned j = 0; j < size; j++) {
            for(unsigned i = j; i < size; i++) {
                EXPECT_EQ(matOne(i, j), matTwo(i, j));
            }
        }
    }

    TEST_F(CMatrixSymmetricTest, AccessOperator) {
        unsigned size = 4;
        CMatrixSymmetric mat = CMatrixSymmetric(size, size, 0.0);
        for (unsigned j = 0; j < size; j++) {
            for (unsigned i = j; i < size; i++) {
                mat(i, j) = i * j;
            }
        }
        for (unsigned j = 0; j < size; j++) {
            for (unsigned i = j; i < size; i++) {
                EXPECT_EQ(i * j, mat(i, j));
            }
        }
    }

    TEST_F(CMatrixSymmetricTest, ConstAccessOperator) {
        unsigned size = 4;
        int val = 0.0;
        const CMatrixSymmetric constMat = CMatrixSymmetric(size, size, val);
        EXPECT_EQ(val, constMat(0, 0));
        EXPECT_EQ(val, constMat(size - 1, size - 1));
    }

    TEST_F(CMatrixSymmetricTest, AdditionOperators) {
        CMatrixSymmetric mat;
        // CMatrixSymmetric matForConst;
        // const double constVal = 2.0;
        mat = (*A) + (*B);
        (*B) += (*B);
        // matForConst = (*A) + constVal;
        for (unsigned j = 0; j < mat.getCols(); j++) {
            for (unsigned i = j; i < mat.getRows(); i++) {
                EXPECT_EQ((*C)(i, j), mat(i, j));
                EXPECT_EQ((*A)(i, j), (*B)(i, j));
                // EXPECT_EQ((*D)(i, j), matForConst(i, j));
            }
        }
    }

    // TEST_F(CMatrixSymmetricTest, SubstractionOperators) {
    //     CMatrixSymmetric mat;
    //     CMatrixSymmetric matForConst;
    //     const double constVal = 2.0;
    //     mat = (*C) - (*B);
    //     (*C) -= (*B);
    //     matForConst = (*D) - constVal;
    //     for (unsigned j = 0; j < mat.getCols(); j++) {
    //         for (unsigned i = 0; i < mat.getRows(); i++) {
    //             EXPECT_EQ((*A)(i, j), mat(i, j));
    //             EXPECT_EQ((*A)(i, j), (*C)(i, j));
    //             EXPECT_EQ((*A)(i, j), matForConst(i, j));
    //         }
    //     }
    // }
    //
    // TEST_F(CMatrixSymmetricTest, ProductOperators) {
    //     CMatrixSymmetric mat;
    //     CMatrixSymmetric matForConst;
    //     CMatrixSymmetric vec;
    //     const double constVal = 2.0;
    //     mat = (*B) * (*B);
    //     vec = (*B) * (*E);
    //     (*B) *= (*B);
    //     matForConst = (*A) * constVal;
    //     for(unsigned i = 0; i < mat.getRows(); i++) {
    //         for(unsigned j = 0; j < mat.getCols(); j++) {
    //             EXPECT_EQ((*D)(i, j), mat(i, j));
    //             EXPECT_EQ((*D)(i, j), matForConst(i, j));
    //         }
    //     }
    //     for(unsigned i = 0; i < vec.getRows(); i++) {
    //         EXPECT_EQ((*F)(i, 0), vec(i, 0));
    //     }
    // }
    //
    // TEST_F(CMatrixSymmetricTest, DivisionOperators) {
    //     CMatrixSymmetric matForConst;
    //     const double constVal = 2.0;
    //     matForConst = (*A) / constVal;
    //     for(unsigned i = 0; i < matForConst.getRows(); i++) {
    //         for(unsigned j = 0; j < matForConst.getCols(); j++) {
    //             EXPECT_EQ((*B)(i, j), matForConst(i, j));
    //         }
    //     }
    // }
    //
    // TEST_F(CMatrixSymmetricTest, PowerOperator) {
    //     CMatrixSymmetric matForConst;
    //     const double constVal = 2.0;
    //     matForConst = (*A) ^ constVal;
    //     for(unsigned i = 0; i < matForConst.getRows(); i++) {
    //         for(unsigned j = 0; j < matForConst.getCols(); j++) {
    //             EXPECT_EQ((*D)(i, j), matForConst(i, j));
    //         }
    //     }
    // }
}
