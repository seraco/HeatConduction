#include <iostream>

#include "../include/gtest/gtest.h"
#include "../../include/CMatrix.h"
#include "../../include/CLinearSystem.h"

namespace {
    class CLinearSystemTest : public ::testing::Test {
        protected:
            virtual void SetUp() {
                unsigned size = 4;
                A = new CMatrix(size, size, 0.0);
                AUpper = new CMatrix(size, size, 0.0);
                ALower = new CMatrix(size, size, 0.0);
                b = new CMatrix(size, 1, 0.0);
                bUpLow = new CMatrix(size, 1, 1.0);
                x = new CMatrix(size, 1, 0.0);
                xUpper = new CMatrix(size, 1, 0.0);
                xLower = new CMatrix(size, 1, 0.0);
                (*A)(0, 0) = 5.0;
                (*A)(0, 1) = 6.0;
                (*A)(0, 2) = 7.0;
                (*A)(0, 3) = 5.0;
                (*A)(1, 0) = 8.0;
                (*A)(1, 1) = -4.;
                (*A)(1, 2) = -1.;
                (*A)(1, 3) = 0.0;
                (*A)(2, 0) = 2.0;
                (*A)(2, 1) = 1.0;
                (*A)(2, 2) = -1.;
                (*A)(2, 3) = 3.0;
                (*A)(3, 0) = -9.;
                (*A)(3, 1) = 10.;
                (*A)(3, 2) = 1.0;
                (*A)(3, 3) = -4.;
                (*b)(0, 0) = -3.;
                (*b)(1, 0) = 5.0;
                (*b)(2, 0) = 2.0;
                (*b)(3, 0) = 9.0;
                for(unsigned i = 0; i < size; i++) {
                    for(unsigned j = i; j < size; j++) {
                        (*AUpper)(i, j) = double(i + j + 1);
                    }
                }
                (*ALower) = (*AUpper).transpose();
                (*x)(0, 0) = 1.2326;
                (*x)(1, 0) = 1.6652;
                (*x)(2, 0) = -1.8004;
                (*x)(3, 0) = -1.3103;
                (*xUpper)(0, 0) = 0.2286;
                (*xUpper)(1, 0) = 0.0571;
                (*xUpper)(2, 0) = 0.0286;
                (*xUpper)(3, 0) = 0.1429;
                (*xLower)(0, 0) = 1.0000;
                (*xLower)(1, 0) = -.3333;
                (*xLower)(2, 0) = -.1333;
                (*xLower)(3, 0) = -.0762;
            }
            virtual void TearDown() {
                delete A;
                delete AUpper;
                delete ALower;
                delete b;
                delete bUpLow;
                delete x;
                delete xUpper;
                delete xLower;
            }

            CMatrix* A;
            CMatrix* AUpper;
            CMatrix* ALower;
            CMatrix* b;
            CMatrix* bUpLow;
            CMatrix* x;
            CMatrix* xUpper;
            CMatrix* xLower;
    };

    TEST_F(CLinearSystemTest, CopyConstructor) {
        CMatrix lhs = *A;
        CMatrix rhs = *b;
        CLinearSystem sys = CLinearSystem(lhs, rhs);
        CMatrix lhsInSystem = CMatrix(sys.getLhsMatrix());
        CMatrix rhsInSystem = CMatrix(sys.getRhsVector());
        EXPECT_EQ((*A).getRows(), lhsInSystem.getRows());
        EXPECT_EQ((*A).getCols(), lhsInSystem.getCols());
        EXPECT_EQ((*b).getRows(), rhsInSystem.getRows());
        EXPECT_EQ((*b).getCols(), rhsInSystem.getCols());
        for(unsigned i = 0; i < (*A).getRows(); i++) {
            for(unsigned j = 0; j < (*A).getCols(); j++) {
                EXPECT_EQ((*A)(i, j), lhsInSystem(i, j));
            }
        }
        for(unsigned i = 0; i < (*b).getRows(); i++) {
            EXPECT_EQ((*b)(i, 0), rhsInSystem(i, 0));
        }
    }

    TEST_F(CLinearSystemTest, UpperSolve) {
        unsigned size = (*bUpLow).getRows();
        CLinearSystem sys = CLinearSystem(*AUpper, *bUpLow);
        CMatrix sol = sys.solve();
        for(unsigned i = 0; i < size; i++) {
            EXPECT_NEAR((*xUpper)(i, 0), sol(i, 0), 0.0001);
        }
    }

    TEST_F(CLinearSystemTest, LowerSolve) {
        unsigned size = (*bUpLow).getRows();
        CLinearSystem sys = CLinearSystem(*ALower, *bUpLow);
        CMatrix sol = sys.solve();
        for(unsigned i = 0; i < size; i++) {
            EXPECT_NEAR((*xLower)(i, 0), sol(i, 0), 0.0001);
        }
    }

    TEST_F(CLinearSystemTest, Solve) {
        unsigned size = (*b).getRows();
        CLinearSystem sys = CLinearSystem(*A, *b);
        CMatrix sol = sys.solve();
        for(unsigned i = 0; i < size; i++) {
            EXPECT_NEAR((*x)(i, 0), sol(i, 0), 0.0001);
        }
    }

}
