/*!
 * @file WriteVTK.hpp
 * @brief Headers of the main subroutines for writing VTK files.
 *        The implementation is in the <i>WriteVTK.cpp</i> file.
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

#ifndef __CWRITEVTK_HPP
#define __CWRITEVTK_HPP

#include <string>

#include "CMatrix.hpp"
#include "CMesh.hpp"
#include "CHeatConduction.hpp"

/*!
 * @brief Subroutine that writes VTK files.
 * @param[in] fname - Filename.
 * @param[in] msh - Mesh.
 * @param[in] heat - Heat conduction with results.
 */
void writeVTK(std::string fname, const CMesh& msh, const CHeatConduction& heat);

#endif
