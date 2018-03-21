#ifndef __CCONDUCTANCE_HPP
#define __CCONDUCTANCE_HPP

#include "CMatrix.hpp"
#include "CMaterial.hpp"
#include "CMesh.hpp"
#include "CGeometry.hpp"

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
