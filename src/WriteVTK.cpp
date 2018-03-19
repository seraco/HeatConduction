#ifndef __CWRITEVTK_CPP
#define __CWRITEVTK_CPP

#include <string>
#include <fstream>
#include <iostream>

#include "../include/WriteVTK.h"
#include "../include/CMesh.h"
#include "../include/CMatrix.h"
#include "../include/CHeatConduction.h"

// TODO: Write in binary format!!
void writeVTK(std::string fname, const CMesh& msh, const CHeatConduction& heat) {
    unsigned nNod = msh.getNNode();
    unsigned nEle = msh.getNElem();
    unsigned nNodPerEle = msh.getNNodePerElem();
    CMatrix coor = msh.getCoorMtx();
    CMatrix conn = msh.getConnMtx();
    CMatrix temp = heat.getTemp();
    double zero = 0.0;
    std::ofstream vtk;
    vtk.open(fname, std::ios::out | std::ios::binary);
    if (vtk) {
        std::cout << "\nWriting VTK file...\n\n";
        vtk << "# vtk DataFile Version 2.0" << "\n";
        vtk << "vtk output" << "\n";
        vtk << "ASCII" << "\n";
        vtk << "DATASET UNSTRUCTURED_GRID" << "\n";
        vtk << "POINTS " << nNod <<" double" << "\n";
        for (unsigned int i = 0; i < nNod; i++) {
            vtk << coor(i, 0) << " " << coor(i, 1) << " " << zero << "\n";
            // swapEnd(coor(i, 0));
            // vtk.write((char*)&coor(i, 0), sizeof(double));
            // swapEnd(coor(i, 1));
            // vtk.write((char*)&coor(i, 1), sizeof(double));
            // swapEnd(zero);
            // vtk.write((char*)&zero, sizeof(double));
        }
        // vtk << "\n";
        vtk << "CELLS " << nEle <<" " << nEle * (nNodPerEle + 1) << "\n";
        for (unsigned int i = 0; i < nEle; i++) {
            vtk << nNodPerEle;
            for (unsigned int j = 1; j < nNodPerEle + 1; j++) {
                 vtk << " " << conn(i, j);
            }
            vtk << "\n";
        }
        vtk << "CELL_TYPES " << nEle << "\n";
        for (unsigned int i = 0; i < nEle; i++) {
            vtk << 9 << "\n";
        }
        vtk << "POINT_DATA " << nNod << "\n";
        vtk << "FIELD FieldData 1\n";
        vtk << "disp 1 "<< nNod << " double\n";
        for (unsigned int i = 0; i < nNod; i++) {
            vtk << temp(i, 0) << "\n";
        }
    vtk.close();
    } else {
        throw std::runtime_error("Problem writing VTK file");
    }
}

template <typename T>
void swapEnd(T& var) {
    char* varArray = reinterpret_cast<char*>(&var);

    for (long i = 0; i < static_cast<long>(sizeof(var) / 2); i++) {
        std::swap(varArray[sizeof(var) - 1 - i], varArray[i]);
    }
}

#endif
