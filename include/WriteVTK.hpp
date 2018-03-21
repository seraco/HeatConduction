#ifndef __CWRITEVTK_HPP
#define __CWRITEVTK_HPP

#include <string>

#include "CMatrix.hpp"
#include "CMesh.hpp"
#include "CHeatConduction.hpp"

void writeVTK(std::string fname, const CMesh& msh, const CHeatConduction& heat);
template <typename T> void swapEnd(T& var);

#endif
