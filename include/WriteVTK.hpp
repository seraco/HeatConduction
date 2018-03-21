#ifndef __CWRITEVTK_H
#define __CWRITEVTK_H

#include <string>

#include "CMatrix.hpp"
#include "CMesh.hpp"
#include "CHeatConduction.hpp"

void writeVTK(std::string fname, const CMesh& msh, const CHeatConduction& heat);
template <typename T> void swapEnd(T& var);

#endif
