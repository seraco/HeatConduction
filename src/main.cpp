#include <iostream>
#include <string>
#include <stdexcept>
#include <mpi.h>

#include "../include/CCommandLine.hpp"
#include "../include/CMaterial.hpp"
#include "../include/CGeometry.hpp"
#include "../include/CMesh.hpp"
#include "../include/CConductance.hpp"
#include "../include/CBoundaryConditions.hpp"
#include "../include/CHeatConduction.hpp"
#include "../include/WriteVTK.hpp"
#include "../include/Analytical.hpp"

int main(int argc, char *argv[]) {
    if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
        throw std::runtime_error("An error occurred initialising MPI");
    }

    int rank;
    if (MPI_Comm_rank(MPI_COMM_WORLD, &rank) == MPI_ERR_COMM) {
        throw std::runtime_error("Invalid communicator");
    }

    CCommandLine cmd = CCommandLine(argc, argv);
    bool isRunnable = int(cmd.getAbleToRun());

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

        solveAnalytical(msh, bnd, mat, heat.getTemp());

        if (rank == 0) writeVTK("disp.vtk", msh, heat);
    }

    MPI_Finalize();

    return 0;
}
