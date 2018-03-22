#include <cmath>

#include "gtest/gtest.h"
#include "../../include/CBoundaryConditions.hpp"

namespace {
    class CBoundaryConditionsTest : public ::testing::Test {};

    TEST_F(CBoundaryConditionsTest, DefaultConstructor) {
        CBoundaryConditions bnd;
        CMatrix gaussPnt = bnd.getGaussPoints();
        CMatrix gaussWght = bnd.getGaussWeights();
        EXPECT_EQ(2, bnd.getGaussOrder());
        EXPECT_EQ(-1.0 / sqrt(3.0), gaussPnt(0, 0));
        EXPECT_EQ(1.0 / sqrt(3.0), gaussPnt(0, 1));
        EXPECT_EQ(1, gaussWght(0, 0));
        EXPECT_EQ(1, gaussWght(0, 1));
        EXPECT_EQ("", bnd.getFluxBCLoc());
        EXPECT_EQ("", bnd.getTempBCLoc());
        EXPECT_EQ(0.0, bnd.getFluxValue());
        EXPECT_EQ(0.0, bnd.getTempValue());
        EXPECT_EQ(0, bnd.getNFluxNodes());
        EXPECT_EQ(0, bnd.getNTempNodes());
    }

    TEST_F(CBoundaryConditionsTest, CustomConstructor) {
        // CMaterial mat = CMaterial(250.0, 0.0, 250.0);
        CGeometry geo = CGeometry(0.25, 1.0, 1.3, 3.0, 0.2);
        CMesh msh = CMesh(2, 1, geo);
        CBoundaryConditions bnd = CBoundaryConditions("bottom", -5000.0,
                                                      "left", -20.0, msh, geo);
        CMatrix gaussPnt = bnd.getGaussPoints();
        CMatrix gaussWght = bnd.getGaussWeights();
        EXPECT_EQ(2, bnd.getGaussOrder());
        EXPECT_EQ(-1.0 / sqrt(3.0), gaussPnt(0, 0));
        EXPECT_EQ(1.0 / sqrt(3.0), gaussPnt(0, 1));
        EXPECT_EQ(1, gaussWght(0, 0));
        EXPECT_EQ(1, gaussWght(0, 1));
        EXPECT_EQ("bottom", bnd.getFluxBCLoc());
        EXPECT_EQ("left", bnd.getTempBCLoc());
        EXPECT_EQ(-5000.0, bnd.getFluxValue());
        EXPECT_EQ(-20.0, bnd.getTempValue());
        EXPECT_EQ(3, bnd.getNFluxNodes());
        // EXPECT_EQ(2, bnd.getNTempNodes());
    }

    TEST_F(CBoundaryConditionsTest, FluxVector) {
        // CMaterial mat = CMaterial(250.0, 0.0, 250.0);
        CGeometry geo = CGeometry(0.25, 1.0, 1.3, 3.0, 0.2);
        CMesh msh = CMesh(2, 1, geo);
        CBoundaryConditions bnd = CBoundaryConditions("bottom", -5000.0,
                                                      "left", -20.0, msh, geo);
        CMatrix f = bnd.getFluxBCVector();
        EXPECT_NEAR(757.0566, f(0, 0), 0.0001);
        EXPECT_NEAR(0.0, f(1, 0), 0.0001);
        EXPECT_NEAR(1527.9188, f(2, 0), 0.0001);
        EXPECT_NEAR(0.0, f(3, 0), 0.0001);
        EXPECT_NEAR(770.8622, f(4, 0), 0.0001);
        EXPECT_NEAR(0.0, f(5, 0), 0.0001);
    }

    TEST_F(CBoundaryConditionsTest, TemperatureVector) {
        // CMaterial mat = CMaterial(250.0, 0.0, 250.0);
        CGeometry geo = CGeometry(0.25, 1.0, 1.3, 3.0, 0.2);
        CMesh msh = CMesh(2, 1, geo);
        CBoundaryConditions bnd = CBoundaryConditions("bottom", -5000.0,
                                                      "left", -20.0, msh, geo);
        CMatrix T = bnd.getTempBCVector();
        EXPECT_EQ(-20, T(0, 0));
        EXPECT_EQ(-20, T(1, 0));
        EXPECT_EQ(0.0, T(2, 0));
        EXPECT_EQ(0.0, T(3, 0));
        EXPECT_EQ(0.0, T(4, 0));
        EXPECT_EQ(0.0, T(5, 0));
        CMatrix RedDof = bnd.getReducedDofVector();
        EXPECT_EQ(2, RedDof(0, 0));
        EXPECT_EQ(3, RedDof(0, 1));
        EXPECT_EQ(4, RedDof(0, 2));
        EXPECT_EQ(5, RedDof(0, 3));
    }
}
