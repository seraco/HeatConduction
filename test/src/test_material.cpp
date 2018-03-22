#include "gtest/gtest.h"
#include "../../include/CMatrix.hpp"
#include "../../include/CMaterial.hpp"

namespace {
    class CMaterialTest : public ::testing::Test {};

    TEST_F(CMaterialTest, DefaultConstructor) {
        CMaterial material;
        EXPECT_EQ(0.0, material.getKXX());
        EXPECT_EQ(0.0, material.getKXY());
        EXPECT_EQ(0.0, material.getKYY());
    }

    TEST_F(CMaterialTest, CustomConstructor) {
        CMaterial material = CMaterial(1.0, 2.0, 3.0);
        EXPECT_EQ(1.0, material.getKXX());
        EXPECT_EQ(2.0, material.getKXY());
        EXPECT_EQ(3.0, material.getKYY());
    }

    TEST_F(CMaterialTest, ConductivityMatrix) {
        CMaterial material = CMaterial(1.0, 2.0, 3.0);
        CMatrix D = material.getConductivityMatrix();
        EXPECT_EQ(material.getKXX(), D(0, 0));
        EXPECT_EQ(material.getKXY(), D(0, 1));
        EXPECT_EQ(material.getKXY(), D(1, 0));
        EXPECT_EQ(material.getKYY(), D(1, 1));
        // D.printMtx();
    }
}
