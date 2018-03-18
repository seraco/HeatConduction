#ifndef __CCONDUCTANCE_H
#define __CCONDUCTANCE_H

#include "CMatrix.h"
#include "CMaterial.h"
#include "CMesh.h"
#include "CGeometry.h"

class CConductance {
    private:
        unsigned gaussOrder;
        CMatrix gaussPoints;
        CMatrix gaussWeights;
        CMatrix conducMtx;

        CMatrix conductanceMtx(const CGeometry& geo, const CMaterial& mat,
                               const CMesh& msh);

    public:
        CConductance();
        CConductance(const CGeometry& geo, const CMaterial& mat,
                     const CMesh& msh);
        virtual ~CConductance();

        unsigned getGaussOrder() const;
        CMatrix getGaussPoints() const;
        CMatrix getGaussWeights() const;
        CMatrix getConducMtx() const;
};

#endif
