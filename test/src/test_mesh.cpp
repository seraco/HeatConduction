#include "../include/gtest/gtest.h"
#include "../../include/CMatrix.h"
#include "../../include/CGeometry.h"
#include "../../include/CMesh.h"

namespace {
    class CMeshTest : public ::testing::Test {};

    TEST_F(CMeshTest, DefaultConstructor) {
        CMesh msh;
        EXPECT_EQ(0, msh.getNXDirElem());
        EXPECT_EQ(0, msh.getNYDirElem());
        EXPECT_EQ(0, msh.getNElem());
        EXPECT_EQ(0, msh.getNNode());
        EXPECT_EQ(4, msh.getNNodePerElem());
        EXPECT_EQ(1, msh.getDofPerNode());
        EXPECT_EQ(4, msh.getTotalDofInElem());
    }

    TEST_F(CMeshTest, CustomConstructor) {
        CGeometry geo = CGeometry(0.0, 1.0, 1.0, 2.0, 0.2);
        CGeometry geoFromMsh;
        CMesh msh = CMesh(10, 5, geo);
        EXPECT_EQ(10, msh.getNXDirElem());
        EXPECT_EQ(5, msh.getNYDirElem());
        EXPECT_EQ(50, msh.getNElem());
        EXPECT_EQ(66, msh.getNNode());
        EXPECT_EQ(4, msh.getNNodePerElem());
        EXPECT_EQ(1, msh.getDofPerNode());
        EXPECT_EQ(4, msh.getTotalDofInElem());
        geoFromMsh = msh.getGeometry();
        EXPECT_EQ(0.0, geoFromMsh.getAConst());
        EXPECT_EQ(1.0, geoFromMsh.getHeightLeft());
        EXPECT_EQ(1.0, geoFromMsh.getHeightRight());
        EXPECT_EQ(2.0, geoFromMsh.getLength());
        EXPECT_EQ(0.2, geoFromMsh.getThickness());
    }

    TEST_F(CMeshTest, CoordinateMatrix) {
        CGeometry geo = CGeometry(0.0, 1.0, 1.0, 2.0, 0.2);
        CMesh msh = CMesh(2, 1, geo);
        CMatrix coor = msh.coordinateMtx();
        EXPECT_EQ(0.0, coor(0, 0));
        EXPECT_EQ(-.5, coor(0, 1));
        EXPECT_EQ(0.0, coor(1, 0));
        EXPECT_EQ(0.5, coor(1, 1));
        EXPECT_EQ(1.0, coor(2, 0));
        EXPECT_EQ(-.5, coor(2, 1));
        EXPECT_EQ(1.0, coor(3, 0));
        EXPECT_EQ(0.5, coor(3, 1));
        EXPECT_EQ(2.0, coor(4, 0));
        EXPECT_EQ(-.5, coor(4, 1));
        EXPECT_EQ(2.0, coor(5, 0));
        EXPECT_EQ(0.5, coor(5, 1));
    }
}
