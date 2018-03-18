#ifndef __CCOMMANDLINE_CPP
#define __CCOMMANDLINE_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <boost/program_options.hpp>

#include "../include/CCommandLine.h"

CCommandLine::CCommandLine(int argc, char const *argv[]) {
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
    if (vm.count("help")) {
        std::cout << desc;
        ableToRun = false;
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
    } else {
        std::cout << "All the command line arguments should be specified\n\n";
        std::cout << desc;
        ableToRun = false;
    }
}

CCommandLine::~CCommandLine() {}

double CCommandLine::getAConst() {
    return aConst;
}

double CCommandLine::getLeftHeight() {
    return leftHeight;
}

double CCommandLine::getRightHeight() {
    return rightHeight;
}

double CCommandLine::getLength() {
    return length;
}

double CCommandLine::getThickness() {
    return thickness;
}

double CCommandLine::getKXX() {
    return kXX;
}

double CCommandLine::getKXY() {
    return kXY;
}

double CCommandLine::getKYY() {
    return kYY;
}

unsigned CCommandLine::getNx() {
    return Nx;
}

unsigned CCommandLine::getNy() {
    return Ny;
}

std::string CCommandLine::getFluxLocation() {
    return fluxLocation;
}

double CCommandLine::getFluxValue() {
    return fluxValue;
}

std::string CCommandLine::getTempLocation() {
    return tempLocation;
}

double CCommandLine::getTempValue() {
    return tempValue;
}

bool CCommandLine::getAbleToRun() {
    return ableToRun;
}

#endif
