#include <cmath>

#include "../include/gtest/gtest.h"
#include "../../include/CHeatConduction.h"

namespace {
    class CHeatConductionTest : public ::testing::Test {};

    TEST_F(CHeatConductionTest, DefaultConstructor) {
        CMaterial mat = CMaterial(250.0, 0.0, 250.0);
        CGeometry geo = CGeometry(0.25, 1.0, 1.3, 3.0, 0.2);
        CMesh msh = CMesh(2, 1, geo);
        CConductance con = CConductance(geo, mat, msh);
        CBoundaryConditions bnd = CBoundaryConditions("bottom", -5000.0,
                                                      "left", -20.0, msh, geo);
        CHeatConduction heat = CHeatConduction(bnd, con, msh);
    }

    TEST_F(CHeatConductionTest, PartitionMatrices) {
        CMaterial mat = CMaterial(250.0, 0.0, 250.0);
        CGeometry geo = CGeometry(0.25, 1.0, 1.3, 3.0, 0.2);
        CMesh msh = CMesh(2, 1, geo);
        CConductance con = CConductance(geo, mat, msh);
        CBoundaryConditions bnd = CBoundaryConditions("bottom", -5000.0,
                                                      "left", -20.0, msh, geo);
        CHeatConduction heat = CHeatConduction(bnd, con, msh);

        CMatrix Te = heat.getTe();
        EXPECT_EQ(-20.0, Te(0, 0));
        EXPECT_EQ(-20.0, Te(1, 0));

        CMatrix Ff = heat.getFf();
        EXPECT_NEAR(1527.9188, Ff(0, 0), 0.0001);
        EXPECT_NEAR(0.0, Ff(1, 0), 0.0001);
        EXPECT_NEAR(770.8622, Ff(2, 0), 0.0001);
        EXPECT_NEAR(0.0, Ff(3, 0), 0.0001);

        CMatrix Kee = heat.getKee();
        EXPECT_NEAR(35.8853, Kee(0, 0), 0.0001);
        EXPECT_NEAR(-22.6561, Kee(0, 1), 0.0001);
        EXPECT_NEAR(-22.6561, Kee(1, 0), 0.0001);
        EXPECT_NEAR(35.8853, Kee(1, 1), 0.0001);

        CMatrix Kff = heat.getKff();
        EXPECT_NEAR(92.7492, Kff(0, 0), 0.0001);
        EXPECT_NEAR(-63.7909, Kff(0, 1), 0.0001);
        EXPECT_NEAR(3.6809, Kff(0, 2), 0.0001);
        EXPECT_NEAR(-19.41, Kff(0, 3), 0.0001);
        EXPECT_NEAR(-63.7909, Kff(1, 0), 0.0001);
        EXPECT_NEAR(92.7492, Kff(1, 1), 0.0001);
        EXPECT_NEAR(-19.41, Kff(1, 2), 0.0001);
        EXPECT_NEAR(3.6809, Kff(1, 3), 0.0001);
        EXPECT_NEAR(3.6809, Kff(2, 0), 0.0001);
        EXPECT_NEAR(-19.41, Kff(2, 1), 0.0001);
        EXPECT_NEAR(31.4931, Kff(2, 2), 0.0001);
        EXPECT_NEAR(-15.7639, Kff(2, 3), 0.0001);
        EXPECT_NEAR(-19.41, Kff(3, 0), 0.0001);
        EXPECT_NEAR(3.6809, Kff(3, 1), 0.0001);
        EXPECT_NEAR(-15.7639, Kff(3, 2), 0.0001);
        EXPECT_NEAR(31.4931, Kff(3, 3), 0.0001);

        CMatrix Kef = heat.getKef();
        EXPECT_NEAR(7.3927, Kef(0, 0), 0.0001);
        EXPECT_NEAR(-20.6219, Kef(0, 1), 0.0001);
        EXPECT_NEAR(0.0, Kef(0, 2), 0.0001);
        EXPECT_NEAR(0.0, Kef(0, 3), 0.0001);
        EXPECT_NEAR(-20.6219, Kef(1, 0), 0.0001);
        EXPECT_NEAR(7.3927, Kef(1, 1), 0.0001);
        EXPECT_NEAR(0.0, Kef(1, 2), 0.0001);
        EXPECT_NEAR(0.0, Kef(1, 3), 0.0001);
    }

    TEST_F(CHeatConductionTest, TemperatureSolution) {
        CMaterial mat = CMaterial(250.0, 0.0, 250.0);
        CGeometry geo = CGeometry(0.25, 1.0, 1.3, 3.0, 0.2);
        CMesh msh = CMesh(2, 1, geo);
        CConductance con = CConductance(geo, mat, msh);
        CBoundaryConditions bnd = CBoundaryConditions("bottom", -5000.0,
                                                      "left", -20.0, msh, geo);
        CHeatConduction heat = CHeatConduction(bnd, con, msh);

        CMatrix T = heat.getTemp();
        EXPECT_NEAR(-20.0, T(0, 0), 0.0001);
        EXPECT_NEAR(-20.0, T(1, 0), 0.0001);
        EXPECT_NEAR(70.8459, T(2, 0), 0.0001);
        EXPECT_NEAR(62.9202, T(3, 0), 0.0001);
        EXPECT_NEAR(97.607, T(4, 0), 0.0001);
        EXPECT_NEAR(85.1676, T(5, 0), 0.0001);
    }
}
