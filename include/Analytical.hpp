/*!
 * @file Analytical.hpp
 * @brief Headers of the main subroutines for calculating analytical solution and error.
 *        The implementation is in the <i>Analytical.cpp</i> file.
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

 #ifndef __ANALYTICAL_HPP
 #define __ANALYTICAL_HPP

 #include <string>

 #include "CMatrix.hpp"
 #include "CMesh.hpp"
 #include "CBoundaryConditions.hpp"
 #include "CMaterial.hpp"

/*!
 * @brief Solve the heat problem with the analytical solution.
 * @param[in] msh - Mesh.
 * @param[in] bnd - Boundary conditions.
 * @param[in] mat - Material.
 * @param[in] numSol - Numerical solution.
 */
void solveAnalytical(const CMesh& msh,
                     const CBoundaryConditions& bnd,
                     const CMaterial& mat,
                     const CMatrix& numSol);

/*!
 * @brief Calculates the error of numerical with analytical solution.
 * @param[in] sol1 - First solution.
 * @param[in] sol2 - Second solution.
 * @param[in] size - Size of the solutions.
 */
void calculateError(const CMatrix& sol1, const CMatrix& sol2,
                    const unsigned size);

#endif
