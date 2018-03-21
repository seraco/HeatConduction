#ifndef __CBOUNDARYCONDITIONS_CPP
#define __CBOUNDARYCONDITIONS_CPP

#include <string>
#include <iostream>
#include <cmath>

#include "../include/CBoundaryConditions.hpp"
#include "../include/CMesh.hpp"
#include "../include/CGeometry.hpp"

CBoundaryConditions::CBoundaryConditions() {
    gaussOrder = 2;
    gaussPoints = CMatrix(1, 2, 0.0);
    gaussPoints(0, 0) = -1.0 / sqrt(3.0);
    gaussPoints(0, 1) = 1.0 / sqrt(3.0);
    gaussWeights = CMatrix(1, 2, 1.0);
    fluxBCLoc = "";
    tempBCLoc = "";
    fluxValue = 0.0;
    tempValue = 0.0;
    nFluxNodes = 0;
    nTempNodes = 0;
}

CBoundaryConditions::CBoundaryConditions(const std::string flLoc,
                                         const double flVal,
                                         const std::string tpLoc,
                                         const double tpVal,
                                         const CMesh& msh,
                                         const CGeometry& geo) {
    gaussOrder = 2;
    gaussPoints = CMatrix(1, 2, 0.0);
    gaussPoints(0, 0) = -1.0 / sqrt(3.0);
    gaussPoints(0, 1) = 1.0 / sqrt(3.0);
    gaussWeights = CMatrix(1, 2, 1.0);

    fluxBCLoc = flLoc;
    tempBCLoc = tpLoc;
    fluxValue = flVal;
    tempValue = tpVal;

    fluxBCVector = computeBCFlux(msh, geo);
    tempBCVector = computeBCTemp(msh);
}

CBoundaryConditions::~CBoundaryConditions() {}

unsigned CBoundaryConditions::getGaussOrder() const {
    return gaussOrder;
}

CMatrix CBoundaryConditions::getGaussPoints() const {
    return gaussPoints;
}

CMatrix CBoundaryConditions::getGaussWeights() const {
    return gaussWeights;
}

std::string CBoundaryConditions::getFluxBCLoc() const {
    return fluxBCLoc;
}

std::string CBoundaryConditions::getTempBCLoc() const {
    return tempBCLoc;
}

double CBoundaryConditions::getFluxValue() const {
    return fluxValue;
}

double CBoundaryConditions::getTempValue() const {
    return tempValue;
}

CMatrix CBoundaryConditions::getFluxNodes() const {
    return fluxNodes;
}

CMatrix CBoundaryConditions::getTempNodes() const {
    return tempNodes;
}

unsigned CBoundaryConditions::getNFluxNodes() const {
    return nFluxNodes;
}

unsigned CBoundaryConditions::getNTempNodes() const {
    return nTempNodes;
}

CMatrix CBoundaryConditions::getFluxBCVector() const {
    return fluxBCVector;
}

CMatrix CBoundaryConditions::getTempBCVector() const {
    return tempBCVector;
}

CMatrix CBoundaryConditions::getReducedDofVector() const {
    return reducedDofVector;
}

unsigned CBoundaryConditions::getNReducedDof() const {
    return nReducedDof;
}

CMatrix CBoundaryConditions::computeBCFlux(const CMesh& msh,
                                           const CGeometry& geo) {
    unsigned nElX = msh.getNXDirElem();
    unsigned nElY = msh.getNYDirElem();
    CMatrix topol = msh.getTopolMtx();
    unsigned nDof = msh.getNDofTotal();
    CMatrix f = CMatrix(nDof, 1, 0.0);
    CMatrix coor = msh.getCoorMtx();
    double thick = geo.getThickness();

    if (fluxBCLoc == "bottom") {
        fluxNodes = CMatrix(1, nElX + 1, 0.0);
        for (unsigned j = 0; j < nElX + 1; j++) {
            fluxNodes(0, j) = topol(0, j);
        }
        nFluxNodes = nElX + 1;
    } else if (fluxBCLoc == "top") {
        fluxNodes = CMatrix(1, nElX + 1, 0.0);
        for (unsigned j = 0; j < nElX + 1; j++) {
            fluxNodes(0, j) = topol(nElY, j);
        }
        nFluxNodes = nElX + 1;
    } else if (fluxBCLoc == "left") {
        fluxNodes = CMatrix(1, nElY + 1, 0.0);
        for (unsigned i = 0; i < nElY + 1; i++) {
            fluxNodes(0, i) = topol(i, 0);
        }
        nFluxNodes = nElY + 1;
    } else if (fluxBCLoc == "right") {
        fluxNodes = CMatrix(1, nElY + 1, 0.0);
        for (unsigned i = 0; i < nElY + 1; i++) {
            fluxNodes(0, i) = topol(i, nElX);
        }
        nFluxNodes = nElY + 1;
    } else {
        throw std::runtime_error("Unknown flux location");
    }

    unsigned nbe = nFluxNodes - 1;
    CMatrix n_bc = CMatrix(4, nbe, 0.0);
    for (unsigned j = 0; j < nbe; j++) {
        n_bc(0, j) = fluxNodes(0, j);
        n_bc(1, j) = fluxNodes(0, j + 1);
        n_bc(2, j) = fluxValue;
        n_bc(3, j) = fluxValue;
    }

    for (unsigned e = 0; e < nbe; e++) {
        CMatrix fq = CMatrix(2, 1, 0.0);
        unsigned node1 = n_bc(0, e);
        unsigned node2 = n_bc(1, e);
        CMatrix n_bce = CMatrix(1, 2, 0.0);
        n_bce(0, 0) = n_bc(2, e);
        n_bce(0, 1) = n_bc(3, e);
        double x1 = coor(node1, 0);
        double x2 = coor(node2, 0);
        double y1 = coor(node1, 1);
        double y2 = coor(node2, 1);
        double detJ = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)) / 2.0;

        for (unsigned i = 0; i < gaussOrder; i++) {
            double xi = gaussPoints(0, i);
            CMatrix N = CMatrix(1, 2, 0.0);
            N(0, 0) = 0.5 * (1 - xi);
            N(0, 1) = 0.5 * (1 + xi);
            CMatrix flux = N * n_bce.transpose();
            fq = fq + (N.transpose() * detJ * thick * flux * gaussWeights(0, i));
        }
        fq = fq * (-1.0);
        f(node1, 0) = f(node1, 0) + fq(0, 0);
        f(node2, 0) = f(node2, 0) + fq(1, 0);
    }

    return f;
}

CMatrix CBoundaryConditions::computeBCTemp(const CMesh& msh) {
        unsigned nElX = msh.getNXDirElem();
        unsigned nElY = msh.getNYDirElem();
        unsigned nDof = msh.getNDofTotal();
        CMatrix topol = msh.getTopolMtx();

        if (tempBCLoc == "bottom") {
            tempNodes = CMatrix(1, nElX + 1, 0.0);
            for (unsigned j = 0; j < nElX + 1; j++) {
                tempNodes(0, j) = topol(0, j);
            }
            nTempNodes = nElX + 1;
        } else if (tempBCLoc == "top") {
            tempNodes = CMatrix(1, nElX + 1, 0.0);
            for (unsigned j = 0; j < nElX + 1; j++) {
                tempNodes(0, j) = topol(nElY, j);
            }
            nTempNodes = nElX + 1;
        } else if (tempBCLoc == "left") {
            tempNodes = CMatrix(1, nElY + 1, 0.0);
            for (unsigned i = 0; i < nElY + 1; i++) {
                tempNodes(0, i) = topol(i, 0);
            }
            nTempNodes = nElY + 1;
        } else if (tempBCLoc == "right") {
            tempNodes = CMatrix(1, nElY + 1, 0.0);
            for (unsigned i = 0; i < nElY + 1; i++) {
                tempNodes(0, i) = topol(i, nElX);
            }
            nTempNodes = nElY + 1;
        } else {
            throw std::runtime_error("Unknown flux location");
        }

        CMatrix tempBC = CMatrix(nTempNodes, 2, 0.0);
        for (unsigned i = 0; i < nTempNodes; i++) {
            tempBC(i, 0) = tempNodes(0, i);
            tempBC(i, 1) = tempValue;
        }

        CMatrix T = CMatrix(nDof, 1, 0.0);
        for (unsigned i = 0; i < nTempNodes; i++) {
            T(tempBC(i, 0), 0) = tempBC(i, 1);
        }

        CMatrix OrgDof = CMatrix(1, nDof, 0.0);
        for (unsigned i = 0; i < nTempNodes; i++) {
            OrgDof(0, tempBC(i, 0)) = -1.0;
        }

        nReducedDof = nDof - nTempNodes;
        CMatrix RedDof = CMatrix(1, nReducedDof, 0.0);
        unsigned count = 0;
        for (unsigned i = 0; i < nDof; i++) {
            if (OrgDof(0, i) == 0.0) {
                OrgDof(0, i) = count;
                RedDof(0, count) = i;
                count++;
            }
        }
        reducedDofVector = RedDof;

        return T;
}

#endif
