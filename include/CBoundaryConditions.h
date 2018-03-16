#ifndef __CBOUNDARYCONDITIONS_H
#define __CBOUNDARYCONDITIONS_H

#include <string>

#include "CMatrix.h"
#include "CMesh.h"
#include "CGeometry.h"

class CBoundaryConditions {
    private:
        unsigned gaussOrder;
        CMatrix gaussPoints;
        CMatrix gaussWeights;
        std::string fluxBCLoc;
        std::string tempBCLoc;
        double fluxValue;
        double tempValue;
        CMatrix fluxNodes;
        CMatrix tempNodes;
        unsigned nFluxNodes;
        unsigned nTempNodes;
        CMatrix fluxBCVector;
        CMatrix tempBCVector;
        CMatrix reducedDofVector;
        unsigned nReducedDof;

        CMatrix computeBCFlux(CMesh msh, CGeometry geo);
        CMatrix computeBCTemp(CMesh msh);

    public:
        CBoundaryConditions();
        CBoundaryConditions(std::string flLoc, double flVal,
                            std::string tpLoc, double tpVal,
                            CMesh msh, CGeometry geo);
        virtual ~CBoundaryConditions();

        unsigned getGaussOrder();
        CMatrix getGaussPoints();
        CMatrix getGaussWeights();
        std::string getFluxBCLoc();
        std::string getTempBCLoc();
        double getFluxValue();
        double getTempValue();
        CMatrix getFluxNodes();
        CMatrix getTempNodes();
        unsigned getNFluxNodes();
        unsigned getNTempNodes();
        CMatrix getFluxBCVector();
        CMatrix getTempBCVector();
        CMatrix getReducedDofVector();
        unsigned getNReducedDof();
};

#endif
