/*!
 * @file CMesh.cpp
 * @brief The main subroutines for defining matrices and their operations.
 * @author S.Ramon (seraco)
 * @version 0.0.1
 *
 * Copyright 2018 S.Ramon
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __CMESH_CPP
#define __CMESH_CPP

#include "../include/CMatrix.hpp"
#include "../include/CGeometry.hpp"
#include "../include/CMesh.hpp"

CMesh::CMesh() {
    /*--- Initialize properties. ---*/
    nXDirElem = 0;
    nYDirElem = 0;
    nElem = 0;
    nNode = 0;
    nNodePerElem = 4;
    dofPerNode = 1;
    totalDofInElem = nNodePerElem * dofPerNode;
}

CMesh::CMesh(const unsigned NElx, const unsigned NEly, const CGeometry geo) {
    /*--- Initialize properties. ---*/
    nXDirElem = NElx;
    nYDirElem = NEly;
    nElem = nXDirElem * nYDirElem;
    nNode = (nXDirElem + 1) * (nYDirElem + 1);
    nNodePerElem = 4;
    dofPerNode = 1;
    totalDofInElem = nNodePerElem * dofPerNode;

    /*--- Compute main matrices of the mesh. ---*/
    coorMtx = coordinateMtx(geo);
    topolMtx = topologyMtx();
    connMtx = connectivityMtx(topolMtx);
    glDofMtx = globalDofMtx(connMtx);
}

CMesh::~CMesh() {}

unsigned CMesh::getNXDirElem() const {
    return nXDirElem;
}

unsigned CMesh::getNYDirElem() const {
    return nYDirElem;
}

unsigned CMesh::getNElem() const {
    return nElem;
}

unsigned CMesh::getNNode() const {
    return nNode;
}

unsigned CMesh::getNNodePerElem() const {
    return nNodePerElem;
}

unsigned CMesh::getDofPerNode() const {
    return dofPerNode;
}

unsigned CMesh::getTotalDofInElem() const {
    return totalDofInElem;
}

unsigned CMesh::getNDofTotal() const {
    return nDofTotal;
}

CMatrix CMesh::getCoorMtx() const {
    return coorMtx;
}

CMatrix CMesh::getTopolMtx() const {
    return topolMtx;
}

CMatrix CMesh::getConnMtx() const {
    return connMtx;
}

CMatrix CMesh::getGlDofMtx() const {
    return glDofMtx;
}

CMatrix CMesh::coordinateMtx(CGeometry geo) {
    /*--- Initialize variables to be used in the subroutine. ---*/
    CMatrix xVec, hVec, yMat, yLocVec, coorMat;
    double a = geo.getAConst();
    double b = geo.getBConst();
    double hLeft = geo.getHeightLeft();
    unsigned nod;

    /*--- Build x coordinates and height distribution. ---*/
    xVec = CMatrix::linspace(0.0, geo.getLength(), nXDirElem + 1);
    hVec = (xVec^2)*a + xVec*b + hLeft;

    /*--- Build y coordinates. ---*/
    yMat = CMatrix(nYDirElem + 1, nXDirElem + 1, 0.0);
    for (unsigned j = 0; j < nXDirElem + 1; j++) {
        yLocVec = CMatrix::linspace(-hVec(j, 0) / 2.0,
                                 hVec(j, 0) / 2.0,
                                 nYDirElem + 1);
        for (unsigned i = 0; i < nYDirElem + 1; i++) {
            yMat(i, j) = yLocVec(i, 0);
        }
    }

    /*--- Build coordinate matrix from xVec and yMat. ---*/
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

CMatrix CMesh::topologyMtx() {
    CMatrix topol = CMatrix(nYDirElem + 1, nXDirElem + 1, 0.0);

    /*--- Node numbers increase from bottom to top and left to right. ---*/
    unsigned nod = 0;
    for (unsigned j = 0; j < nXDirElem + 1; j++) {
        for (unsigned i = 0; i < nYDirElem + 1; i++) {
            topol(i, j) = nod;
            nod++;
        }
    }

    return topol;
}

CMatrix CMesh::connectivityMtx(CMatrix topol) {
    CMatrix conn = CMatrix(nElem, nNodePerElem + 1, 0.0);

    /*--- First column is element number. The other columns are the nodes in the
          element. ---*/
    unsigned elem = 0;
    for (unsigned j = 0; j < nXDirElem; j++) {
        for (unsigned i = 0; i < nYDirElem; i++) {
            conn(elem, 0) = elem;
            conn(elem, 1) = topol(i, j);
            conn(elem, 2) = topol(i, j + 1);
            conn(elem, 3) = topol(i + 1, j + 1);
            conn(elem, 4) = topol(i + 1, j);
            elem++;
        }
    }

    return conn;
}

CMatrix CMesh::globalDofMtx(CMatrix conn) {
    CMatrix glDof = CMatrix(nNode, 2, 0.0);
    unsigned nod, elemNDof;

    /*--- Populate first column of glDof with the number of DOF per node. ---*/
    for (unsigned i = 0; i < nElem; i++) {
        for (unsigned j = 0; j < nNodePerElem; j++) {
            nod = conn(i, j + 1);
            if (glDof(nod, 0) < dofPerNode) glDof(nod, 0) = dofPerNode;
        }
    }

    /*--- Calculate the total number of DOF and populate the other columns of
          glDof with the DOF numbers. ---*/
    nDofTotal = 0;
    for (unsigned i = 0; i < nNode; i++) {
        elemNDof = glDof(i, 0);
        for (unsigned j = 0; j < elemNDof; j++) {
            glDof(i, j + 1) = nDofTotal;
            nDofTotal++;
        }
    }

    return glDof;
}

#endif
