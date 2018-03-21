/*!
 * @file CConductance.hpp
 * @brief Headers of the main subroutines for assemblying the conductance matrix.
 *        The implementation is in the <i>CConductance.cpp</i> file.
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

#ifndef __CCONDUCTANCE_HPP
#define __CCONDUCTANCE_HPP

#include "CMatrix.hpp"
#include "CMaterial.hpp"
#include "CMesh.hpp"
#include "CGeometry.hpp"

/*!
 * @class CConductance
 * @brief Class to assemble conductance matrix.
 */
class CConductance {
    private:
        unsigned gaussOrder;    /*!< @brief Number of Gauss points.*/
        CMatrix gaussPoints;    /*!< @brief Locations of Gauss points.*/
        CMatrix gaussWeights;   /*!< @brief Weights of Gauss points.*/
        CMatrix conducMtx;      /*!< @brief Conductance matrix.*/

        /*!
         * @brief Assemble global conductance matrix.
         * @param[in] geo - Geometry.
         * @param[in] mat - Material.
         * @param[in] msh - Mesh.
         * @return Conductance matrix.
         */
        CMatrix conductanceMtx(const CGeometry& geo, const CMaterial& mat,
                               const CMesh& msh);

    public:
        /*!
         * @brief Constructor of the class.
         */
        CConductance();

        /*!
         * @brief Constructor of the class.
         * @param[in] geo - Geometry.
         * @param[in] mat - Material.
         * @param[in] msh - Mesh.
         */
        CConductance(const CGeometry& geo, const CMaterial& mat,
                     const CMesh& msh);

        /*!
         * @brief Destructor of the class.
         */
        virtual ~CConductance();

        /*!
         * @brief Get the Gauss quadrature order.
         * @return Gauss quadrature order.
         */
        unsigned getGaussOrder() const;

        /*!
         * @brief Get location of Gauss points.
         * @return Location of Gauss points.
         */
        CMatrix getGaussPoints() const;

        /*!
         * @brief Get weights of Gauss points.
         * @return Weights of Gauss points.
         */
        CMatrix getGaussWeights() const;

        /*!
         * @brief Get the conductance matrix.
         * @return Conductance matrix.
         */
        CMatrix getConducMtx() const;
};

#endif
