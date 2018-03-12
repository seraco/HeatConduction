#ifndef __CMATERIAL_H
#define __CMATERIAL_H

#include "CMatrix.h"

class CMaterial {
    private:
        double conducXX;
        double conducXY;
        double conducYY;

    public:
        CMaterial();
        CMaterial(const double kXX, const double kXY, const double kYY);
        virtual ~CMaterial();

        CMatrix getConductivityMatrix();
        double getKXX();
        double getKXY();
        double getKYY();
};

#endif
