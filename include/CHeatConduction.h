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

        void partitionMatrices(CBoundaryConditions bnd, CConductance cnd);
        CMatrix solveTemperature(CMesh msh, CBoundaryConditions bnd);
        CMatrix solveFlux(CMesh msh, CBoundaryConditions bnd);

    public:
        CHeatConduction();
        CHeatConduction(CBoundaryConditions bnd, CConductance cnd, CMesh msh);
        virtual ~CHeatConduction();

        CMatrix getKee();
        CMatrix getKff();
        CMatrix getKef();
        CMatrix getTe();
        CMatrix getTf();
        CMatrix getFe();
        CMatrix getFf();
        CMatrix getTemp();
        CMatrix getFlux();
};

#endif
