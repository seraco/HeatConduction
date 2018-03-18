#include <iostream>
#include <string>

#include "../include/CCommandLine.h"
#include "../include/CMaterial.h"
#include "../include/CGeometry.h"
#include "../include/CMesh.h"
#include "../include/CConductance.h"
#include "../include/CBoundaryConditions.h"
#include "../include/CHeatConduction.h"

int main(int argc, char const *argv[]) {
    CCommandLine cmd = CCommandLine(argc, argv);
    bool isRunnable = cmd.getAbleToRun();

    if (isRunnable) {
        double kXX = cmd.getKXX();
        double kXY = cmd.getKXY();
        double kYY = cmd.getKYY();
        double a = cmd.getAConst();
        double h1 = cmd.getLeftHeight();
        double h2 = cmd.getRightHeight();
        double L = cmd.getLength();
        double th = cmd.getThickness();
        unsigned Nx = cmd.getNx();
        unsigned Ny = cmd.getNy();
        std::string flLoc = cmd.getFluxLocation();
        double flVal = cmd.getFluxValue();
        std::string tpLoc = cmd.getTempLocation();
        double tpVal = cmd.getTempValue();

        CMaterial mat = CMaterial(kXX, kXY, kYY);
        CGeometry geo = CGeometry(a, h1, h2, L, th);
        CMesh msh = CMesh(Nx, Ny, geo);
        CConductance con = CConductance(geo, mat, msh);
        CBoundaryConditions bnd = CBoundaryConditions(flLoc, flVal,
                                                      tpLoc, tpVal, msh, geo);
        CHeatConduction heat = CHeatConduction(bnd, con, msh);

        std::cout << "The temperature is:" << std::endl;
        heat.getTemp().printMtx();

        std::cout << "The flux is:" << std::endl;
        heat.getFlux().printMtx();
    }

    return 0;
}
