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
    }

    TEST_F(CMeshTest, CoordinateMatrix) {
        CGeometry geoFirst = CGeometry(0.0, 1.0, 1.0, 2.0, 0.2);
        CMesh mshFirst = CMesh(2, 1, geoFirst);
        CMatrix coorFirst = mshFirst.getCoorMtx();
        EXPECT_EQ(0.0, coorFirst(0, 0));
        EXPECT_EQ(-.5, coorFirst(0, 1));
        EXPECT_EQ(0.0, coorFirst(1, 0));
        EXPECT_EQ(0.5, coorFirst(1, 1));
        EXPECT_EQ(1.0, coorFirst(2, 0));
        EXPECT_EQ(-.5, coorFirst(2, 1));
        EXPECT_EQ(1.0, coorFirst(3, 0));
        EXPECT_EQ(0.5, coorFirst(3, 1));
        EXPECT_EQ(2.0, coorFirst(4, 0));
        EXPECT_EQ(-.5, coorFirst(4, 1));
        EXPECT_EQ(2.0, coorFirst(5, 0));
        EXPECT_EQ(0.5, coorFirst(5, 1));
        CGeometry geoSecond = CGeometry(0.25, 1.0, 1.3, 3.0, 0.2);
        CMesh mshSecond = CMesh(2, 1, geoSecond);
        CMatrix coorSecond = mshSecond.getCoorMtx();
        EXPECT_NEAR(0.0, coorSecond(0, 0), 0.0001);
        EXPECT_NEAR(-.5, coorSecond(0, 1), 0.0001);
        EXPECT_NEAR(0.0, coorSecond(1, 0), 0.0001);
        EXPECT_NEAR(0.5, coorSecond(1, 1), 0.0001);
        EXPECT_NEAR(1.5, coorSecond(2, 0), 0.0001);
        EXPECT_NEAR(-.2937, coorSecond(2, 1), 0.0001);
        EXPECT_NEAR(1.5, coorSecond(3, 0), 0.0001);
        EXPECT_NEAR(0.2937, coorSecond(3, 1), 0.0001);
        EXPECT_NEAR(3.0, coorSecond(4, 0), 0.0001);
        EXPECT_NEAR(-.65, coorSecond(4, 1), 0.0001);
        EXPECT_NEAR(3.0, coorSecond(5, 0), 0.0001);
        EXPECT_NEAR(0.65, coorSecond(5, 1), 0.0001);
    }

    TEST_F(CMeshTest, TopologyMatrix) {
        CGeometry geo = CGeometry(0.25, 1.0, 1.3, 3.0, 0.2);
        CMesh msh = CMesh(2, 1, geo);
        CMatrix topol = msh.getTopolMtx();
        EXPECT_EQ(0, topol(0, 0));
        EXPECT_EQ(1, topol(1, 0));
        EXPECT_EQ(2, topol(0, 1));
        EXPECT_EQ(3, topol(1, 1));
        EXPECT_EQ(4, topol(0, 2));
        EXPECT_EQ(5, topol(1, 2));
    }

    TEST_F(CMeshTest, ConnectivityMatrix) {
        CGeometry geo = CGeometry(0.25, 1.0, 1.3, 3.0, 0.2);
        CMesh msh = CMesh(2, 1, geo);
        CMatrix conn = msh.getConnMtx();
        EXPECT_EQ(0, conn(0, 0));
        EXPECT_EQ(0, conn(0, 1));
        EXPECT_EQ(2, conn(0, 2));
        EXPECT_EQ(3, conn(0, 3));
        EXPECT_EQ(1, conn(0, 4));
        EXPECT_EQ(1, conn(1, 0));
        EXPECT_EQ(2, conn(1, 1));
        EXPECT_EQ(4, conn(1, 2));
        EXPECT_EQ(5, conn(1, 3));
        EXPECT_EQ(3, conn(1, 4));
    }

    TEST_F(CMeshTest, GlobalDofMatrix) {
        CGeometry geo = CGeometry(0.25, 1.0, 1.3, 3.0, 0.2);
        CMesh msh = CMesh(2, 1, geo);
        CMatrix glDof = msh.getGlDofMtx();
        EXPECT_EQ(1, glDof(0, 0));
        EXPECT_EQ(1, glDof(1, 0));
        EXPECT_EQ(1, glDof(2, 0));
        EXPECT_EQ(1, glDof(3, 0));
        EXPECT_EQ(1, glDof(4, 0));
        EXPECT_EQ(1, glDof(5, 0));
        EXPECT_EQ(0, glDof(0, 1));
        EXPECT_EQ(1, glDof(1, 1));
        EXPECT_EQ(2, glDof(2, 1));
        EXPECT_EQ(3, glDof(3, 1));
        EXPECT_EQ(4, glDof(4, 1));
        EXPECT_EQ(5, glDof(5, 1));
        EXPECT_EQ(6, msh.getNDofTotal());
    }
}
