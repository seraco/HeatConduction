#include <iostream>

#include "../include/gtest/gtest.h"
#include "../../include/matrix.h"

namespace {
    class CMatrixTest : public ::testing::Test {
        protected:
            virtual void SetUp() {
                Aint = new CMatrix<int>(4, 4, 2);
                Bint = new CMatrix<int>(4, 4, 1);
                Adbl = new CMatrix<double>(4, 4, 2.0);
                Bdbl = new CMatrix<double>(4, 4, 1.0);
            }
            virtual void TearDown() {
                delete Aint;
                delete Bint;
                delete Adbl;
                delete Bdbl;
            }

            CMatrix<int>* Aint;
            CMatrix<int>* Bint;
            CMatrix<double>* Adbl;
            CMatrix<double>* Bdbl;
    };

    TEST_F(CMatrixTest, DefaultConstructor) {
        CMatrix<int> matInt;
        CMatrix<double> matDbl;
        ASSERT_FALSE(matInt.isErrWithMtxSize());
        ASSERT_FALSE(matDbl.isErrWithMtxSize());
        EXPECT_EQ(0, matInt.getRows());
        EXPECT_EQ(0, matInt.getCols());
        EXPECT_EQ(0, matDbl.getRows());
        EXPECT_EQ(0, matDbl.getCols());
    }

    TEST_F(CMatrixTest, CustomConstructor) {
        unsigned size = 8;
        int intVal = 0;
        double dblVal = 0.0;
        CMatrix<int> matInt = CMatrix<int>(size, size, intVal);
        CMatrix<double> matDbl = CMatrix<double>(size, size, dblVal);
        ASSERT_FALSE(matInt.isErrWithMtxSize());
        ASSERT_FALSE(matDbl.isErrWithMtxSize());
        EXPECT_EQ(size, matInt.getRows());
        EXPECT_EQ(size, matInt.getCols());
        EXPECT_EQ(size, matDbl.getRows());
        EXPECT_EQ(size, matDbl.getCols());
        // TODO: Here access operator is from another test. Think about the
        // correctness of using it here.
        for(unsigned i = 0; i < matInt.getRows(); i++) {
            for(unsigned j = 0; j < matInt.getCols(); j++) {
                EXPECT_EQ(intVal, matInt(i, j));
            }
        }
        for(unsigned i = 0; i < matDbl.getRows(); i++) {
            for(unsigned j = 0; j < matDbl.getCols(); j++) {
                EXPECT_EQ(dblVal, matDbl(i, j));
            }
        }
    }

    TEST_F(CMatrixTest, CopyConstructor) {
        CMatrix<int> matInt = *Aint;
        CMatrix<double> matDbl = *Bdbl;
        ASSERT_FALSE(matInt.isErrWithMtxSize());
        ASSERT_FALSE(matDbl.isErrWithMtxSize());
        EXPECT_EQ(Aint->getRows(), matInt.getRows());
        EXPECT_EQ(Aint->getCols(), matInt.getCols());
        EXPECT_EQ(Bdbl->getRows(), matDbl.getRows());
        EXPECT_EQ(Bdbl->getCols(), matDbl.getCols());
        // TODO: Here access operator is from another test. Think about the
        // correctness of using it here.
        for(unsigned i = 0; i < Aint->getRows(); i++) {
            for(unsigned j = 0; j < Aint->getCols(); j++) {
                EXPECT_EQ((*Aint)(i, j), matInt(i, j));
            }
        }
        for(unsigned i = 0; i < Bdbl->getRows(); i++) {
            for(unsigned j = 0; j < Bdbl->getCols(); j++) {
                EXPECT_EQ((*Bdbl)(i, j), matDbl(i, j));
            }
        }
        // (*Aint)(2, 2) = 6;
        // std::cout << "Row: " << 2 << " Col: " << 2 << ": " << (*Aint)(2, 2) << std::endl;
    }

    TEST_F(CMatrixTest, AccessOperator) {
        unsigned size = 4;
        CMatrix<int> matInt = CMatrix<int>(size, size, 0);
        CMatrix<double> matDbl = CMatrix<double>(size, size, 0.0);
        const CMatrix<int> ConstMatInt = CMatrix<int>(size, size, 0);
        const CMatrix<double> ConstMatDbl = CMatrix<double>(size, size, 0.0);
        for(unsigned i = 0; i < size; i++) {
            for(unsigned j = 0; j < size; j++) {
                matInt(i, j) = i * j;
            }
        }
        for(unsigned i = 0; i < size; i++) {
            for(unsigned j = 0; j < size; j++) {
                EXPECT_EQ(i * j, matInt(i, j));
            }
        }
        for(unsigned i = 0; i < size; i++) {
            for(unsigned j = 0; j < size; j++) {
                matDbl(i, j) = i * j;
            }
        }
        for(unsigned i = 0; i < size; i++) {
            for(unsigned j = 0; j < size; j++) {
                EXPECT_EQ(i * j, matDbl(i, j));
            }
        }
        // ConstMatInt(0, 0) = 2;
        std::cout << ConstMatInt(0, 0) << std::endl;
    }

    // TEST_F(CMatrixTest, ConstAccessOperator) {
    //     unsigned size = 4;
    //     const CMatrix<int> ConstMatInt = CMatrix<int>(size, size, 0);
    //     const CMatrix<double> ConstMatDbl = CMatrix<double>(size, size, 0.0);
    //     ConstMatInt(0, 0) = 2;
    //     std::cout << ConstMatInt(0, 0) << std::endl;
    // }

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
