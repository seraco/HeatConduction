/*!
 * @file CHeatConduction.hpp
 * @brief Headers of the main subroutines for solving the heat conduction problem.
 *        The implementation is in the <i>CHeatConduction.cpp</i> file.
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

#ifndef __CHEATCONDUCTION_HPP
#define __CHEATCONDUCTION_HPP

#include "CConductance.hpp"
#include "CBoundaryConditions.hpp"
#include "CMatrix.hpp"
#include "CMesh.hpp"

/*!
 * @class CHeatConduction
 * @brief Class to solve the heat conduction problem on a plate.
 */
class CHeatConduction {
    private:
        CMatrix Kee;    /*!< @brief Conductance submatrix at known temperatures.*/
        CMatrix Kff;    /*!< @brief Conductance submatrix at known fluxes.*/
        CMatrix Kef;    /*!< @brief Conductance submatrix at known temperatures and fluxes.*/
        CMatrix Te;     /*!< @brief Temperature subvector at known temperatures.*/
        CMatrix Tf;     /*!< @brief Temperature subvector at known fluxes.*/
        CMatrix Fe;     /*!< @brief Flux subvector at known temperatures.*/
        CMatrix Ff;     /*!< @brief Flux subvector at known fluxes.*/
        CMatrix temp;   /*!< @brief Temperature vector.*/
        CMatrix flux;   /*!< @brief Flux vector.*/

        /*!
         * @brief Subroutine to subdivide matrices and vecors, Kee, Kff, Kef, Te, Tf.
         * @param[in] bnd - Boundary conditions.
         * @param[in] cnd - Conductance.
         */
        void partitionMatrices(const CBoundaryConditions& bnd,
                               const CConductance& cnd);

        /*!
         * @brief Solve the heat problem returning the temperature vector.
         * @param[in] msh - Mesh.
         * @param[in] bnd - Boundary conditions.
         * @return Temperature vector.
         */
        CMatrix solveTemperature(const CMesh& msh,
                                 const CBoundaryConditions& bnd);

        /*!
         * @brief Solve the heat problem returning the flux vector.
         * @param[in] msh - Mesh.
         * @param[in] bnd - Boundary conditions.
         * @return Flux vector.
         */
        CMatrix solveFlux(const CMesh& msh, const CBoundaryConditions& bnd);

    public:
        /*!
         * @brief Constructor of the class.
         */
        CHeatConduction();

        /*!
         * @brief Constructor of the class.
         * @param[in] bnd - Boundary conditions.
         * @param[in] cnd - Conductance.
         * @param[in] msh - Mesh.
         */
        CHeatConduction(const CBoundaryConditions& bnd, const CConductance& cnd,
                        const CMesh& msh);

        /*!
         * @brief Destructor of the class.
         */
        virtual ~CHeatConduction();

        /*!
         * @brief Get Kee submatrix.
         * @return Kee submatrix.
         */
        CMatrix getKee() const;

        /*!
         * @brief Get Kff submatrix.
         * @return Kff submatrix.
         */
        CMatrix getKff() const;

        /*!
         * @brief Get Kef submatrix.
         * @return Kef submatrix.
         */
        CMatrix getKef() const;

        /*!
         * @brief Get Te subvector.
         * @return Te subvector.
         */
        CMatrix getTe() const;

        /*!
         * @brief Get Tf subvector.
         * @return Tf subvector.
         */
        CMatrix getTf() const;

        /*!
         * @brief Get Fe subvector.
         * @return Fe subvector.
         */
        CMatrix getFe() const;

        /*!
         * @brief Get Ff subvector.
         * @return Ff subvector.
         */
        CMatrix getFf() const;

        /*!
         * @brief Get temperature vector.
         * @return Temperature vector.
         */
        CMatrix getTemp() const;

        /*!
         * @brief Get flux vector.
         * @return Flux vector.
         */
        CMatrix getFlux() const;
};

#endif
