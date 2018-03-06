#include <iostream>

#include "../include/gtest/gtest.h"
#include "../../include/CMatrix.h"
#include "../../include/CLinearSystem.h"

namespace {
    class CLinearSystemTest : public ::testing::Test {
        protected:
            virtual void SetUp() {
                unsigned size = 4;
                A = new CMatrix<double>(size, size, 0.0);
                AUpper = new CMatrix<double>(size, size, 0.0);
                ALower = new CMatrix<double>(size, size, 0.0);
                b = new CMatrix<double>(size, 1, 0.0);
                x = new CMatrix<double>(size, 1, 0.0);
                xUpper = new CMatrix<double>(size, 1, 0.0);
                xLower = new CMatrix<double>(size, 1, 0.0);
                for(unsigned i = 0; i < size; i++) {
                    for(unsigned j = 0; j < size; j++) {
                        (*A)(i, j) = double(i + j);
                    }
                    (*b)(i, 0) = 1.0;
                }
                for(unsigned i = 0; i < size; i++) {
                    for(unsigned j = i; j < size; j++) {
                        (*AUpper)(i, j) = double(i + j + 1);
                    }
                }
                (*ALower) = (*AUpper).transpose();
                (*x)(0, 0) = -3.5333;
                (*x)(1, 0) = 4.2;
                (*x)(2, 0) = 1.2;
                (*x)(3, 0) = -1.8667;
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
                delete x;
                delete xUpper;
                delete xLower;
            }

            CMatrix<double>* A;
            CMatrix<double>* AUpper;
            CMatrix<double>* ALower;
            CMatrix<double>* b;
            CMatrix<double>* x;
            CMatrix<double>* xUpper;
            CMatrix<double>* xLower;
    };

    TEST_F(CLinearSystemTest, CopyConstructor) {
        CMatrix<double> lhs = *A;
        CMatrix<double> rhs = *b;
        CLinearSystem sys = CLinearSystem(lhs, rhs);
        CMatrix<double> lhsInSystem = CMatrix<double>(sys.getLhsMatrix());
        CMatrix<double> rhsInSystem = CMatrix<double>(sys.getRhsVector());
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

    TEST_F(CLinearSystemTest, BackwardSubstitution) {
        unsigned size = (*b).getRows();
        CLinearSystem sys = CLinearSystem(*AUpper, *b);
        CMatrix<double> sol = sys.backwardSubstitution();
        for(unsigned i = 0; i < size; i++) {
            EXPECT_NEAR((*xUpper)(i, 0), sol(i, 0), 0.0001);
        }
    }

    TEST_F(CLinearSystemTest, ForwardSubstitution) {
        unsigned size = (*b).getRows();
        CLinearSystem sys = CLinearSystem(*ALower, *b);
        CMatrix<double> sol = sys.forwardSubstitution();
        for(unsigned i = 0; i < size; i++) {
            EXPECT_NEAR((*xLower)(i, 0), sol(i, 0), 0.0001);
        }
    }

}
