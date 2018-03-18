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

        double getAConst();
        double getLeftHeight();
        double getRightHeight();
        double getLength();
        double getThickness();
        double getKXX();
        double getKXY();
        double getKYY();
        unsigned getNx();
        unsigned getNy();
        std::string getFluxLocation();
        double getFluxValue();
        std::string getTempLocation();
        double getTempValue();
        bool getAbleToRun();
};

#endif
