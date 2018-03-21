/*!
 * @file CBoundaryConditions.hpp
 * @brief Headers of the main subroutines for specifying boundary conditions.
 *        The implementation is in the <i>CBoundaryConditions.cpp</i> file.
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

#ifndef __CBOUNDARYCONDITIONS_HPP
#define __CBOUNDARYCONDITIONS_HPP

#include <string>

#include "CMatrix.hpp"
#include "CMesh.hpp"
#include "CGeometry.hpp"

/*!
 * @class CBoundaryConditions
 * @brief Class to specify boundary conditions.
 */
class CBoundaryConditions {
    private:
        unsigned gaussOrder;        /*!< @brief Number of Gauss points.*/
        CMatrix gaussPoints;        /*!< @brief Location of Gauss points.*/
        CMatrix gaussWeights;       /*!< @brief Gauss point weights.*/
        std::string fluxBCLoc;      /*!< @brief Location of flux boundary conditions.*/
        std::string tempBCLoc;      /*!< @brief Location of temperature boundary conditions.*/
        double fluxValue;           /*!< @brief Value of flux boundary conditions.*/
        double tempValue;           /*!< @brief Value of temperature boundary conditions.*/
        CMatrix fluxNodes;          /*!< @brief Nodes where flux BC are specified.*/
        CMatrix tempNodes;          /*!< @brief Nodes where temperature BC are specified.*/
        unsigned nFluxNodes;        /*!< @brief Number of nodes where flux BC are specified.*/
        unsigned nTempNodes;        /*!< @brief Number of nodes where temperature BC are specified.*/
        CMatrix fluxBCVector;       /*!< @brief Flux vector with flux BC set.*/
        CMatrix tempBCVector;       /*!< @brief Temperature vector with temperature BC set.*/
        CMatrix reducedDofVector;   /*!< @brief DOF where flux BC are specified.*/
        unsigned nReducedDof;       /*!< @brief Number reduced DOF.*/

        /*!
         * @brief Calculate flux BC vector.
         * @param[in] msh - Mesh.
         * @param[in] geo - Geometry.
         * @return Flux BC vector.
         */
        CMatrix computeBCFlux(const CMesh& msh, const CGeometry& geo);

        /*!
         * @brief Calculate temperature BC vector.
         * @param[in] msh - Mesh.
         * @return Temperature BC vector.
         */
        CMatrix computeBCTemp(const CMesh& msh);

    public:
        /*!
         * @brief Constructor of the class.
         */
        CBoundaryConditions();

        /*!
         * @brief Constructor of the class.
         * @param[in] flLoc - Flux BC location.
         * @param[in] flVal - Flux BC value.
         * @param[in] tpLoc - Temperature BC location.
         * @param[in] tpVal - Temperature BC value.
         * @param[in] msh - Mesh.
         * @param[in] geo - Geometry.
         */
        CBoundaryConditions(const std::string flLoc, const double flVal,
                            const std::string tpLoc, const double tpVal,
                            const CMesh& msh, const CGeometry& geo);

        /*!
         * @brief Destructor of the class.
         */
        virtual ~CBoundaryConditions();

        /*!
         * @brief Get the Gauss order.
         * @return Gauss order.
         */
        unsigned getGaussOrder() const;

        /*!
         * @brief Get Gauss points.
         * @return Gauss points.
         */
        CMatrix getGaussPoints() const;

        /*!
         * @brief Get Gauss weights.
         * @return Gauss weights.
         */
        CMatrix getGaussWeights() const;

        /*!
         * @brief Get flux BC location.
         * @return Flux BC location.
         */
        std::string getFluxBCLoc() const;

        /*!
         * @brief Get temperature BC location.
         * @return Temperature BC location.
         */
        std::string getTempBCLoc() const;

        /*!
         * @brief Get flux BC value.
         * @return Flux BC value.
         */
        double getFluxValue() const;

        /*!
         * @brief Get temperature BC value.
         * @return Temperature BC value.
         */
        double getTempValue() const;

        /*!
         * @brief Get flux BC nodes.
         * @return Flux BC nodes.
         */
        CMatrix getFluxNodes() const;

        /*!
         * @brief Get temperature BC nodes.
         * @return Temperature BC nodes.
         */
        CMatrix getTempNodes() const;

        /*!
         * @brief Get number of flux BC nodes.
         * @return Number of flux BC nodes.
         */
        unsigned getNFluxNodes() const;

        /*!
         * @brief Get number of temperature BC nodes.
         * @return Number of temperature BC nodes.
         */
        unsigned getNTempNodes() const;

        /*!
         * @brief Get flux BC vector.
         * @return Flux BC vector.
         */
        CMatrix getFluxBCVector() const;

        /*!
         * @brief Get temperature BC vector.
         * @return Temperature BC vector.
         */
        CMatrix getTempBCVector() const;

        /*!
         * @brief Get reduced DOF vector.
         * @return Reduced DOF vector.
         */
        CMatrix getReducedDofVector() const;

        /*!
         * @brief Get number of reduced DOF.
         * @return Number of reduced DOF.
         */
        unsigned getNReducedDof() const;
};

#endif
