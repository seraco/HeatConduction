#ifndef __CMESH_CPP
#define __CMESH_CPP

#include "../include/CMatrix.h"
#include "../include/CMesh.h"

CMesh::CMesh() {
    nXDirElem = 0;
    nYDirElem = 0;
    nElem = 0;
    nNode = 0;
    nNodePerElem = 4;
    dofPerNode = 1;
    totalDofInElem = nNodePerElem * dofPerNode;
}

CMesh::CMesh(const unsigned NElx, const unsigned NEly, const CGeometry geo) {
    nXDirElem = NElx;
    nYDirElem = NEly;
    nElem = nXDirElem * nYDirElem;
    nNode = (nXDirElem + 1) * (nYDirElem + 1);
    nNodePerElem = 4;
    dofPerNode = 1;
    totalDofInElem = nNodePerElem * dofPerNode;
    geometry = geo;
}

CMesh::~CMesh() {}

unsigned CMesh::getNXDirElem() {
    return nXDirElem;
}

unsigned CMesh::getNYDirElem() {
    return nYDirElem;
}

unsigned CMesh::getNElem() {
    return nElem;
}

unsigned CMesh::getNNode() {
    return nNode;
}

unsigned CMesh::getNNodePerElem() {
    return nNodePerElem;
}

unsigned CMesh::getDofPerNode() {
    return dofPerNode;
}

unsigned CMesh::getTotalDofInElem() {
    return totalDofInElem;
}

CGeometry CMesh::getGeometry() {
    return geometry;
}

CMatrix CMesh::coordinateMtx() {
    CMatrix xVec, hVec, yMat, yLocVec, coorMat;
    double a = geometry.getAConst();
    double b = geometry.getBConst();
    double hLeft = geometry.getHeightLeft();
    unsigned nod;

    xVec = CMatrix::linspace(0.0, geometry.getLength(), nXDirElem + 1);
    hVec = xVec*xVec*a + xVec*b + hLeft;

    yMat = CMatrix(nYDirElem + 1, nXDirElem + 1, 0.0);
    for (unsigned j = 0; j < nXDirElem + 1; j++) {
        yLocVec = CMatrix::linspace(-hVec(j, 0) / 2.0,
                                 hVec(j, 0) / 2.0,
                                 nYDirElem + 1);
        for (unsigned i = 0; i < nYDirElem + 1; i++) {
            yMat(i, j) = yLocVec(i, 0);
        }
    }

    coorMat = CMatrix(nNode, 2, 0.0);
    nod = 0;
    for (unsigned j = 0; j < nXDirElem + 1; j++) {
        for (unsigned i = 0; i < nYDirElem + 1; i++) {
            coorMat(nod, 0) = xVec(j, 0);
            coorMat(nod, 1) = yMat(i, j);
            nod++;
        }
    }

    return coorMat;
}


#endif
