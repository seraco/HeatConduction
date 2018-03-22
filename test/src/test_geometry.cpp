#include "gtest/gtest.h"
#include "../../include/CGeometry.hpp"

namespace {
    class CGeometryTest : public ::testing::Test {};

    TEST_F(CGeometryTest, DefaultConstructor) {
        CGeometry geo;
        EXPECT_EQ(0.0, geo.getAConst());
        EXPECT_EQ(0.0, geo.getBConst());
        EXPECT_EQ(0.0, geo.getHeightLeft());
        EXPECT_EQ(0.0, geo.getHeightRight());
        EXPECT_EQ(0.0, geo.getLength());
        EXPECT_EQ(0.0, geo.getThickness());
    }

    TEST_F(CGeometryTest, CustomConstructor) {
        CGeometry geo = CGeometry(1.0, 2.0, 3.0, 4.0, 5.0);
        EXPECT_EQ(1.0, geo.getAConst());
        EXPECT_EQ(2.0, geo.getHeightLeft());
        EXPECT_EQ(3.0, geo.getHeightRight());
        EXPECT_EQ(4.0, geo.getLength());
        EXPECT_EQ(5.0, geo.getThickness());
        EXPECT_EQ(-3.75, geo.getBConst());
    }

    TEST_F(CGeometryTest, HeightCalculation) {
        CGeometry geo = CGeometry(0.25, 1.0, 1.3, 3.0, 0.2);
        EXPECT_NEAR(1.0, geo.getHeight(0.0), 0.0001);
        EXPECT_NEAR(0.6, geo.getHeight(1.0), 0.0001);
        EXPECT_NEAR(0.7, geo.getHeight(2.0), 0.0001);
        EXPECT_NEAR(1.3, geo.getHeight(3.0), 0.0001);
    }
}
