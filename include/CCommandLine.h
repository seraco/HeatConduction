#ifndef __CCOMMANDLINE_H
#define __CCOMMANDLINE_H

#include <string>

class CCommandLine {
    private:
        double aConst;
        double leftHeight;
        double rightHeight;
        double length;
        double thickness;
        double kXX;
        double kXY;
        double kYY;
        unsigned Nx;
        unsigned Ny;
        std::string fluxLocation;
        double fluxValue;
        std::string tempLocation;
        double tempValue;
        bool ableToRun;

    public:
        CCommandLine(int argc, char const *argv[]);
        virtual ~CCommandLine();

        double getAConst() const;
        double getLeftHeight() const;
        double getRightHeight() const;
        double getLength() const;
        double getThickness() const;
        double getKXX() const;
        double getKXY() const;
        double getKYY() const;
        unsigned getNx() const;
        unsigned getNy() const;
        std::string getFluxLocation() const;
        double getFluxValue() const;
        std::string getTempLocation() const;
        double getTempValue() const;
        bool getAbleToRun() const;
};

#endif
