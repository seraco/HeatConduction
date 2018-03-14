#ifndef __CCONDUCTANCE_H
#define __CCONDUCTANCE_H

#include "CMatrix.h"
#include "CMaterial.h"
#include "CMesh.h"

class CConductance {
    private:
        unsigned gaussOrder;
        CMatrix gaussPoints;
        CMatrix gaussWeights;
        CMaterial mater;
        CMatrix conducMtx;
        CMesh mesh;

        CMatrix conductanceMtx(CMaterial mat, CMesh msh);

    public:
        CConductance();
        CConductance(const CMaterial mat, const CMesh msh);
        virtual ~CConductance();

        unsigned getGaussOrder();
        CMatrix getGaussPoints();
        CMatrix getGaussWeights();
        CMaterial getMaterial();
        CMatrix getConducMtx();
        CMesh getMesh();
};

#endif
