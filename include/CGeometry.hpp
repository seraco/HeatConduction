#ifndef __CGEOMETRY_H
#define __CGEOMETRY_H

class CGeometry {
    private:
        double aConst;
        double bConst;
        double heightLeft;
        double heightRight;
        double length;
        double thickness;

    public:
        CGeometry();
        CGeometry(const double a, const double h1, const double h2,
                  const double L, const double th);
        virtual ~CGeometry();

        double getAConst() const;
        double getBConst() const;
        double getHeightLeft() const;
        double getHeightRight() const;
        double getLength() const;
        double getThickness() const;
        double getHeight(double const x) const;
};

#endif
