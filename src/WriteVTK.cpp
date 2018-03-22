/*!
 * @file WriteVTK.cpp
 * @brief The main subroutines for defining matrices and their operations.
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

#ifndef __CWRITEVTK_CPP
#define __CWRITEVTK_CPP

#include <string>
#include <fstream>
#include <iostream>

#include "../include/WriteVTK.hpp"
#include "../include/CMesh.hpp"
#include "../include/CMatrix.hpp"
#include "../include/CHeatConduction.hpp"

void writeVTK(std::string fname, const CMesh& msh, const CHeatConduction& heat) {
    /*--- Initialize variable to be used in the subroutine. ---*/
    unsigned nNod = msh.getNNode();
    unsigned nEle = msh.getNElem();
    unsigned nNodPerEle = msh.getNNodePerElem();
    CMatrix coor = msh.getCoorMtx();
    CMatrix conn = msh.getConnMtx();
    CMatrix temp = heat.getTemp();
    double zero = 0.0;

    /*--- Open file for writing results. ---*/
    std::ofstream vtk;
    vtk.open(fname, std::ios::out | std::ios::binary);
    if (vtk) {
        /*--- Write header. ---*/
        std::cout << "\nWriting VTK file...\n\n";
        vtk << "# vtk DataFile Version 2.0" << "\n";
        vtk << "vtk output" << "\n";
        vtk << "ASCII" << "\n";
        vtk << "DATASET UNSTRUCTURED_GRID" << "\n";

        /*--- Write coordinates of points. ---*/
        vtk << "POINTS " << nNod <<" double" << "\n";
        for (unsigned int i = 0; i < nNod; i++) {
            vtk << coor(i, 0) << " " << coor(i, 1) << " " << zero << "\n";
        }

        /*--- Write connectivity data. ---*/
        vtk << "CELLS " << nEle <<" " << nEle * (nNodPerEle + 1) << "\n";
        for (unsigned int i = 0; i < nEle; i++) {
            vtk << nNodPerEle;
            for (unsigned int j = 1; j < nNodPerEle + 1; j++) {
                 vtk << " " << conn(i, j);
            }
            vtk << "\n";
        }

        /*--- Write the type of elements. Quads (9) in this case. ---*/
        vtk << "CELL_TYPES " << nEle << "\n";
        for (unsigned int i = 0; i < nEle; i++) {
            vtk << 9 << "\n";
        }

        /*--- Write temperature results. ---*/
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

#endif
