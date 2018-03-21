/*!
 * @file CCommandLine.cpp
 * @brief The main subroutines for handling command line input and output.
 * @author S.Ramon (seraco)
 * @version 0.0.1
 *
 * Copyright 2018 S.Ramon
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __CCOMMANDLINE_CPP
#define __CCOMMANDLINE_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <boost/program_options.hpp>
#include <mpi.h>

#include "../include/CCommandLine.hpp"

CCommandLine::CCommandLine(int argc, char *argv[]) {
    int rank;
    int nRanks;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nRanks);

    /*--- Print solver logo and version. ---*/
    if (rank == 0) {
        std::cout << R"(
             _       _    _            _                 _
            / /\    / /\ /\ \         / /\              /\ \         _          _
           / / /   / / //  \ \       / /  \             \_\ \       /\ \       /\ \
          / /_/   / / // /\ \ \     / / /\ \            /\__ \   ___\ \_\   ___\ \_\
         / /\ \__/ / // / /\ \_\   / / /\ \ \          / /_ \ \ /___/\/_/_ /___/\/_/_
        / /\ \___\/ // /_/_ \/_/  / / /  \ \ \        / / /\ \ \\__ \/___/\\__ \/___/\
       / / /\/___/ // /____/\    / / /___/ /\ \      / / /  \/_/  /\/____\/  /\/____\/
      / / /   / / // /\____\/   / / /_____/ /\ \    / / /         \ \_\      \ \_\
     / / /   / / // / /______  / /_________/\ \ \  / / /           \/_/       \/_/
    / / /   / / // / /_______\/ / /_       __\ \_\/_/ /
    \/_/    \/_/ \/__________/\_\___\     /____/_/\_\/

        )" << "\n";
        std::cout << "Version 0.0.1\n\n";
    }

    /*--- Controll command line parameters with boost library. ---*/
    namespace po = boost::program_options;
    po::options_description desc("Program options");
    desc.add_options()
        ("help", "produce this help message")
        ("a-constant,A", po::value<double>(), "a constant for height distribution")
        ("left-height", po::value<double>(), "height at the left edge")
        ("right-height", po::value<double>(), "height at the right edge")
        ("length,L", po::value<double>(), "length of the plate")
        ("thickness,T", po::value<double>(), "thickness of the plate")
        ("k-xx", po::value<double>(), "conductivity in the xx direction")
        ("k-xy", po::value<double>(), "conductivity in the xy direction")
        ("k-yy", po::value<double>(), "conductivity in the yy direction")
        ("n-x", po::value<unsigned>(), "number of elements in x direction")
        ("n-y", po::value<unsigned>(), "number of elements in y direction")
        ("flux-location", po::value<std::string>(), "location of flux BC")
        ("flux-value", po::value<double>(), "value of flux BC")
        ("temp-location", po::value<std::string>(), "location of temperature BC")
        ("temp-value", po::value<double>(), "value of temperature BC");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    /*--- If help parameter is passed show help information. ---*/
    if (vm.count("help")) {
        if (rank == 0) std::cout << desc;
        ableToRun = false;

    /*--- If all the parameters required are specified, the program is able to
          run. ---*/
    } else if (
        vm.count("a-constant") &&
        vm.count("left-height") &&
        vm.count("right-height") &&
        vm.count("length") &&
        vm.count("thickness") &&
        vm.count("k-xx") &&
        vm.count("k-xy") &&
        vm.count("k-yy") &&
        vm.count("n-x") &&
        vm.count("n-y") &&
        vm.count("flux-location") &&
        vm.count("flux-value") &&
        vm.count("temp-location") &&
        vm.count("temp-value")
    ) {
        aConst = vm["a-constant"].as<double>();
        leftHeight = vm["left-height"].as<double>();
        rightHeight = vm["right-height"].as<double>();
        length = vm["length"].as<double>();
        thickness = vm["thickness"].as<double>();
        kXX = vm["k-xx"].as<double>();
        kXY = vm["k-xy"].as<double>();
        kYY = vm["k-yy"].as<double>();
        Nx = vm["n-x"].as<unsigned>();
        Ny = vm["n-y"].as<unsigned>();
        fluxLocation = vm["flux-location"].as<std::string>();
        fluxValue = vm["flux-value"].as<double>();
        tempLocation = vm["temp-location"].as<std::string>();
        tempValue = vm["temp-value"].as<double>();
        ableToRun = true;

    /*--- If not all the required parameters are specified, show the help
          information. ---*/
    } else {
        if (rank == 0) {
            std::cout << "All the command line arguments should be specified\n\n";
            std::cout << desc;
        }
        ableToRun = false;
    }
}

CCommandLine::~CCommandLine() {}

double CCommandLine::getAConst() const {
    return aConst;
}

double CCommandLine::getLeftHeight() const {
    return leftHeight;
}

double CCommandLine::getRightHeight() const {
    return rightHeight;
}

double CCommandLine::getLength() const {
    return length;
}

double CCommandLine::getThickness() const {
    return thickness;
}

double CCommandLine::getKXX() const {
    return kXX;
}

double CCommandLine::getKXY() const {
    return kXY;
}

double CCommandLine::getKYY() const {
    return kYY;
}

unsigned CCommandLine::getNx() const {
    return Nx;
}

unsigned CCommandLine::getNy() const {
    return Ny;
}

std::string CCommandLine::getFluxLocation() const {
    return fluxLocation;
}

double CCommandLine::getFluxValue() const {
    return fluxValue;
}

std::string CCommandLine::getTempLocation() const {
    return tempLocation;
}

double CCommandLine::getTempValue() const {
    return tempValue;
}

bool CCommandLine::getAbleToRun() const {
    return ableToRun;
}

#endif
