#ifndef __CHEATCONDUCTION_H
#define __CHEATCONDUCTION_H

#include <string>

#include "CConductance.h"
#include "CBoundaryConditions.h"
#include "CMatrix.h"

class CHeatConduction {
    private:
        CMatrix Kee;
        CMatrix Kff;
        CMatrix Kef;
        CMatrix Te;
        CMatrix Ff;

        void partitionMatrices(CBoundaryConditions bnd, CConductance cnd);

    public:
        CHeatConduction();
        CHeatConduction(CBoundaryConditions bnd, CConductance cnd);
        virtual ~CHeatConduction();

        CMatrix getKee();
        CMatrix getKff();
        CMatrix getKef();
        CMatrix getTe();
        CMatrix getFf();
};

#endif
