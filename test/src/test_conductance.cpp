#include <cmath>

#include "../include/gtest/gtest.h"
#include "../../include/CConductance.hpp"
#include "../../include/CMatrix.hpp"

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
        CConductance con = CConductance(geo, mat, msh);
        CMatrix gaussPnt = con.getGaussPoints();
        CMatrix gaussWght = con.getGaussWeights();
        EXPECT_EQ(2, con.getGaussOrder());
        EXPECT_EQ(-1.0 / sqrt(3.0), gaussPnt(0, 0));
        EXPECT_EQ(1.0 / sqrt(3.0), gaussPnt(0, 1));
        EXPECT_EQ(1, gaussWght(0, 0));
        EXPECT_EQ(1, gaussWght(0, 1));
    }

    TEST_F(CConductanceTest, ConductanceMatrix) {
        CMaterial mat = CMaterial(250.0, 0.0, 250.0);
        CGeometry geo = CGeometry(0.25, 1.0, 1.3, 3.0, 0.2);
        CMesh msh = CMesh(2, 1, geo);
        CConductance con = CConductance(geo, mat, msh);
        CMatrix K = con.getConducMtx();
        EXPECT_NEAR(35.8853, K(0, 0), 0.0001);
        EXPECT_NEAR(-22.6561, K(0, 1), 0.0001);
        EXPECT_NEAR(7.3927, K(0, 2), 0.0001);
        EXPECT_NEAR(-20.6219, K(0, 3), 0.0001);
        EXPECT_NEAR(0.0, K(0, 4), 0.0001);
        EXPECT_NEAR(0.0, K(0, 5), 0.0001);
        EXPECT_NEAR(35.8853, K(1, 1), 0.0001);
        EXPECT_NEAR(-20.6219, K(1, 2), 0.0001);
        EXPECT_NEAR(7.3927, K(1, 3), 0.0001);
        EXPECT_NEAR(0.0, K(1, 4), 0.0001);
        EXPECT_NEAR(0.0, K(1, 5), 0.0001);
        EXPECT_NEAR(92.7492, K(2, 2), 0.0001);
        EXPECT_NEAR(-63.7909, K(2, 3), 0.0001);
        EXPECT_NEAR(3.6809, K(2, 4), 0.0001);
        EXPECT_NEAR(-19.41, K(2, 5), 0.0001);
        EXPECT_NEAR(92.7492, K(3, 3), 0.0001);
        EXPECT_NEAR(-19.41, K(3, 4), 0.0001);
        EXPECT_NEAR(3.6809, K(3, 5), 0.0001);
        EXPECT_NEAR(31.4931, K(4, 4), 0.0001);
        EXPECT_NEAR(-15.7639, K(4, 5), 0.0001);
        EXPECT_NEAR(31.4931, K(5, 5), 0.0001);
    }
}
