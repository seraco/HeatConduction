#ifndef __CMATERIAL_HPP
#define __CMATERIAL_HPP

#include "CMatrix.hpp"

class CMaterial {
    private:
        double conducXX;
        double conducXY;
        double conducYY;

    public:
        CMaterial();
        CMaterial(const double kXX, const double kXY, const double kYY);
        virtual ~CMaterial();

        CMatrix getConductivityMatrix() const;
        double getKXX() const;
        double getKXY() const;
        double getKYY() const;
};

#endif
