#ifndef __CHEATCONDUCTION_H
#define __CHEATCONDUCTION_H

#include "CConductance.h"
#include "CBoundaryConditions.h"
#include "CMatrix.h"
#include "CMesh.h"

class CHeatConduction {
    private:
        CMatrix Kee;
        CMatrix Kff;
        CMatrix Kef;
        CMatrix Te;
        CMatrix Tf;
        CMatrix Fe;
        CMatrix Ff;
        CMatrix temp;
        CMatrix flux;

        void partitionMatrices(const CBoundaryConditions& bnd,
                               const CConductance& cnd);
        CMatrix solveTemperature(const CMesh& msh,
                                 const CBoundaryConditions& bnd);
        CMatrix solveFlux(const CMesh& msh, const CBoundaryConditions& bnd);

    public:
        CHeatConduction();
        CHeatConduction(const CBoundaryConditions& bnd, const CConductance& cnd,
                        const CMesh& msh);
        virtual ~CHeatConduction();

        CMatrix getKee() const;
        CMatrix getKff() const;
        CMatrix getKef() const;
        CMatrix getTe() const;
        CMatrix getTf() const;
        CMatrix getFe() const;
        CMatrix getFf() const;
        CMatrix getTemp() const;
        CMatrix getFlux() const;
};

#endif
