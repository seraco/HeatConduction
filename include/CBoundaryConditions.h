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

        CMatrix computeBCFlux(const CMesh& msh, const CGeometry& geo);
        CMatrix computeBCTemp(const CMesh& msh);

    public:
        CBoundaryConditions();
        CBoundaryConditions(const std::string flLoc, const double flVal,
                            const std::string tpLoc, const double tpVal,
                            const CMesh& msh, const CGeometry& geo);
        virtual ~CBoundaryConditions();

        unsigned getGaussOrder() const;
        CMatrix getGaussPoints() const;
        CMatrix getGaussWeights() const;
        std::string getFluxBCLoc() const;
        std::string getTempBCLoc() const;
        double getFluxValue() const;
        double getTempValue() const;
        CMatrix getFluxNodes() const;
        CMatrix getTempNodes() const;
        unsigned getNFluxNodes() const;
        unsigned getNTempNodes() const;
        CMatrix getFluxBCVector() const;
        CMatrix getTempBCVector() const;
        CMatrix getReducedDofVector() const;
        unsigned getNReducedDof() const;
};

#endif
