#include <cmath>

#include "../include/gtest/gtest.h"
#include "../../include/CConductance.h"
#include "../../include/CMatrix.h"

namespace {
    class CConductanceTest : public ::testing::Test {};

    TEST_F(CConductanceTest, DefaultConstructor) {
        CConductance con;
        CMatrix gaussPnt = con.getGaussPoints();
        CMatrix gaussWght = con.getGaussWeights();
        EXPECT_EQ(2, con.getGaussOrder());
        EXPECT_EQ(-1.0 / sqrt(3.0), gaussPnt(0, 0));
        EXPECT_EQ(1.0 / sqrt(3.0), gaussPnt(0, 1));
        EXPECT_EQ(1, gaussWght(0, 0));
        EXPECT_EQ(1, gaussWght(0, 1));
    }

    TEST_F(CConductanceTest, CustomConstructor) {
        CMaterial mat = CMaterial(250.0, 0.0, 250.0);
        CGeometry geo = CGeometry(0.25, 1.0, 1.3, 3.0, 0.2);
        CMesh msh = CMesh(2, 1, geo);
        CConductance con = CConductance(mat, msh);
        CMatrix gaussPnt = con.getGaussPoints();
        CMatrix gaussWght = con.getGaussWeights();
        EXPECT_EQ(2, con.getGaussOrder());
        EXPECT_EQ(-1.0 / sqrt(3.0), gaussPnt(0, 0));
        EXPECT_EQ(1.0 / sqrt(3.0), gaussPnt(0, 1));
        EXPECT_EQ(1, gaussWght(0, 0));
        EXPECT_EQ(1, gaussWght(0, 1));

        CMaterial matFromProperty = con.getMaterial();
        CMesh mshFromProperty = con.getMesh();
        EXPECT_EQ(250.0, matFromProperty.getKXX());
        EXPECT_EQ(0.0, matFromProperty.getKXY());
        EXPECT_EQ(250.0, matFromProperty.getKYY());
        EXPECT_EQ(2, mshFromProperty.getNXDirElem());
        EXPECT_EQ(1, mshFromProperty.getNYDirElem());
    }

    TEST_F(CConductanceTest, ConductanceMatrix) {
        CMaterial mat = CMaterial(250.0, 0.0, 250.0);
        CGeometry geo = CGeometry(0.25, 1.0, 1.3, 3.0, 0.2);
        CMesh msh = CMesh(2, 1, geo);
        CConductance con = CConductance(mat, msh);
        CMatrix K = con.getConducMtx();
        K.printMtx();
    }
}
