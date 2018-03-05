#include <iostream>

#include "../include/gtest/gtest.h"
#include "../../include/matrix.h"

namespace {
    class CMatrixTest : public ::testing::Test {
        protected:
            virtual void SetUp() {
                unsigned size = 4;
                Aint = new CMatrix<int>(size, size, 2);
                Bint = new CMatrix<int>(size, size, 1);
                Cint = new CMatrix<int>(size, size, 3);
                Dint = new CMatrix<int>(size, size, 4);
                Eint = new CMatrix<int>(size, 1, 1);
                Fint = new CMatrix<int>(size, 1, 4);
                Gint = new CMatrix<int>(size, size, 8);
                Adbl = new CMatrix<double>(size, size, 2.0);
                Bdbl = new CMatrix<double>(size, size, 1.0);
                Cdbl = new CMatrix<double>(size, size, 3.0);
                Ddbl = new CMatrix<double>(size, size, 4.0);
                Edbl = new CMatrix<double>(size, 1, 1.0);
                Fdbl = new CMatrix<double>(size, 1, 4.0);
                Gdbl = new CMatrix<double>(size, size, 8.0);
            }
            virtual void TearDown() {
                delete Aint;
                delete Bint;
                delete Cint;
                delete Dint;
                delete Eint;
                delete Fint;
                delete Gint;
                delete Adbl;
                delete Bdbl;
                delete Cdbl;
                delete Ddbl;
                delete Edbl;
                delete Fdbl;
                delete Gdbl;
            }

            CMatrix<int>* Aint;
            CMatrix<int>* Bint;
            CMatrix<int>* Cint;
            CMatrix<int>* Dint;
            CMatrix<int>* Eint;
            CMatrix<int>* Fint;
            CMatrix<int>* Gint;
            CMatrix<double>* Adbl;
            CMatrix<double>* Bdbl;
            CMatrix<double>* Cdbl;
            CMatrix<double>* Ddbl;
            CMatrix<double>* Edbl;
            CMatrix<double>* Fdbl;
            CMatrix<double>* Gdbl;
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
    }

    TEST_F(CMatrixTest, ConstAccessOperator) {
        unsigned size = 4;
        int intVal = 0;
        int dblVal = 0.0;
        const CMatrix<int> ConstMatInt = CMatrix<int>(size, size, intVal);
        const CMatrix<double> ConstMatDbl = CMatrix<double>(size, size, dblVal);
        EXPECT_EQ(intVal, ConstMatInt(0, 0));
        EXPECT_EQ(dblVal, ConstMatDbl(0, 0));
        EXPECT_EQ(intVal, ConstMatInt(size - 1, size - 1));
        EXPECT_EQ(dblVal, ConstMatDbl(size - 1, size - 1));
    }

    TEST_F(CMatrixTest, AdditionOperators) {
        CMatrix<int> matInt;
        CMatrix<int> matIntForConst;
        CMatrix<double> matDbl;
        CMatrix<double> matDblForConst;
        const int constInt = 2;
        const double constDbl = 2.0;
        matInt = (*Aint) + (*Bint);
        matDbl = (*Adbl) + (*Bdbl);
        (*Bint) += (*Bint);
        (*Bdbl) += (*Bdbl);
        matIntForConst = (*Aint) + constInt;
        matDblForConst = (*Adbl) + constDbl;
        for(unsigned i = 0; i < matInt.getRows(); i++) {
            for(unsigned j = 0; j < matInt.getCols(); j++) {
                EXPECT_EQ((*Cint)(i, j), matInt(i, j));
                EXPECT_EQ((*Aint)(i, j), (*Bint)(i, j));
                EXPECT_EQ((*Dint)(i, j), matIntForConst(i, j));
            }
        }
        for(unsigned i = 0; i < matDbl.getRows(); i++) {
            for(unsigned j = 0; j < matDbl.getCols(); j++) {
                EXPECT_EQ((*Cdbl)(i, j), matDbl(i, j));
                EXPECT_EQ((*Adbl)(i, j), (*Bdbl)(i, j));
                EXPECT_EQ((*Ddbl)(i, j), matDblForConst(i, j));
            }
        }
    }

    TEST_F(CMatrixTest, SubstractionOperators) {
        CMatrix<int> matInt;
        CMatrix<int> matIntForConst;
        CMatrix<double> matDbl;
        CMatrix<double> matDblForConst;
        const int constInt = 2;
        const double constDbl = 2.0;
        matInt = (*Cint) - (*Bint);
        matDbl = (*Cdbl) - (*Bdbl);
        (*Cint) -= (*Bint);
        (*Cdbl) -= (*Bdbl);
        matIntForConst = (*Dint) - constInt;
        matDblForConst = (*Ddbl) - constDbl;
        for(unsigned i = 0; i < matInt.getRows(); i++) {
            for(unsigned j = 0; j < matInt.getCols(); j++) {
                EXPECT_EQ((*Aint)(i, j), matInt(i, j));
                EXPECT_EQ((*Aint)(i, j), (*Cint)(i, j));
                EXPECT_EQ((*Aint)(i, j), matIntForConst(i, j));
            }
        }
        for(unsigned i = 0; i < matDbl.getRows(); i++) {
            for(unsigned j = 0; j < matDbl.getCols(); j++) {
                EXPECT_EQ((*Adbl)(i, j), matDbl(i, j));
                EXPECT_EQ((*Adbl)(i, j), (*Cdbl)(i, j));
                EXPECT_EQ((*Adbl)(i, j), matDblForConst(i, j));
            }
        }
    }

    TEST_F(CMatrixTest, ProductOperators) {
        CMatrix<int> matInt;
        CMatrix<int> matIntForConst;
        CMatrix<double> matDbl;
        CMatrix<double> matDblForConst;
        CMatrix<int> vecInt;
        CMatrix<double> vecDbl;
        const int constInt = 2;
        const double constDbl = 2.0;
        matInt = (*Bint) * (*Bint);
        matDbl = (*Bdbl) * (*Bdbl);
        vecInt = (*Bint) * (*Eint);
        vecDbl = (*Bdbl) * (*Edbl);
        (*Bint) *= (*Bint);
        (*Bdbl) *= (*Bdbl);
        matIntForConst = (*Aint) * constInt;
        matDblForConst = (*Adbl) * constDbl;
        for(unsigned i = 0; i < matInt.getRows(); i++) {
            for(unsigned j = 0; j < matInt.getCols(); j++) {
                EXPECT_EQ((*Dint)(i, j), matInt(i, j));
                EXPECT_EQ((*Dint)(i, j), matIntForConst(i, j));
            }
        }
        for(unsigned i = 0; i < vecInt.getRows(); i++) {
            EXPECT_EQ((*Fint)(i, 1), vecInt(i, 1));
        }
        for(unsigned i = 0; i < matDbl.getRows(); i++) {
            for(unsigned j = 0; j < matDbl.getCols(); j++) {
                EXPECT_EQ((*Ddbl)(i, j), matDbl(i, j));
                EXPECT_EQ((*Ddbl)(i, j), matDblForConst(i, j));
            }
        }
        for(unsigned i = 0; i < vecDbl.getRows(); i++) {
            EXPECT_EQ((*Fdbl)(i, 1), vecDbl(i, 1));
        }
    }

    TEST_F(CMatrixTest, DivisionOperators) {
        CMatrix<int> matIntForConst;
        CMatrix<double> matDblForConst;
        const int constInt = 2;
        const double constDbl = 2.0;
        matIntForConst = (*Aint) / constInt;
        matDblForConst = (*Adbl) / constDbl;
        for(unsigned i = 0; i < matIntForConst.getRows(); i++) {
            for(unsigned j = 0; j < matIntForConst.getCols(); j++) {
                EXPECT_EQ((*Bint)(i, j), matIntForConst(i, j));
            }
        }
        for(unsigned i = 0; i < matDblForConst.getRows(); i++) {
            for(unsigned j = 0; j < matDblForConst.getCols(); j++) {
                EXPECT_EQ((*Bdbl)(i, j), matDblForConst(i, j));
            }
        }
    }

}
