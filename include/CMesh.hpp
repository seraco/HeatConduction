/*!
 * @file CMesh.hpp
 * @brief Headers of the main subroutines for defining the mesh.
 *        The implementation is in the <i>CMesh.cpp</i> file.
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

#ifndef __CMESH_HPP
#define __CMESH_HPP

#include "CMatrix.hpp"
#include "CGeometry.hpp"

/*!
 * @class CMesh
 * @brief Class to define the mesh.
 */
class CMesh {
    private:
        unsigned nXDirElem;         /*!< @brief Number of elements in the x direction.*/
        unsigned nYDirElem;         /*!< @brief Number of elements in the y direction.*/
        unsigned nElem;             /*!< @brief Number of elements.*/
        unsigned nNode;             /*!< @brief Number of nodes.*/
        unsigned nNodePerElem;      /*!< @brief Number of nodes per element.*/
        unsigned dofPerNode;        /*!< @brief Number of DOF per node.*/
        unsigned totalDofInElem;    /*!< @brief Number of DOF in every element.*/
        unsigned nDofTotal;         /*!< @brief Number of DOF.*/
        CMatrix coorMtx;            /*!< @brief Matrix of coordinates.*/
        CMatrix topolMtx;           /*!< @brief Topology matrix to describe the node distribution.*/
        CMatrix connMtx;            /*!< @brief Connectivity matrix.*/
        CMatrix glDofMtx;           /*!< @brief Global DOF matrix.*/

        /*!
         * @brief Subroutine that builds the matrix of coordinates.
         * @param[in] geo - Geometry.
         * @return Matrix of coordinates.
         */
        CMatrix coordinateMtx(CGeometry geo);

        /*!
         * @brief Subroutine that builds the topology matrix.
         * @return Topology matrix.
         */
        CMatrix topologyMtx();

        /*!
         * @brief Subroutine that builds the connectivity matrix.
         * @param[in] topol - Topology matrix.
         * @return Connectivity matrix.
         */
        CMatrix connectivityMtx(CMatrix topol);

        /*!
         * @brief Subroutine that builds the matrix of global DOF.
         * @param[in] conn - Connectivity matrix.
         * @return Matrix of global DOF.
         */
        CMatrix globalDofMtx(CMatrix conn);

    public:
        /*!
         * @brief Constructor of the class.
         */
        CMesh();

        /*!
         * @brief Constructor of the class.
         * @param[in] NElx - Number of elements in the x direction.
         * @param[in] NEly - Number of elements in the y direction.
         * @param[in] geo - Geometry.
         */
        CMesh(const unsigned NElx, const unsigned NEly, const CGeometry geo);

        /*!
         * @brief Destructor of the class.
         */
        virtual ~CMesh();

        /*!
         * @brief Get number of elements in the x direction.
         * @return Number of elements in the x direction.
         */
        unsigned getNXDirElem() const;

        /*!
         * @brief Get number of elements in the y direction.
         * @return Number of elements in the y direction.
         */
        unsigned getNYDirElem() const;

        /*!
         * @brief Get number of elements.
         * @return Number of elements.
         */
        unsigned getNElem() const;

        /*!
         * @brief Get number of nodes.
         * @return Number of nodes.
         */
        unsigned getNNode() const;

        /*!
         * @brief Get number of nodes per element.
         * @return Number of nodes per element.
         */
        unsigned getNNodePerElem() const;

        /*!
         * @brief Get number of DOF per node.
         * @return Number of DOF per node.
         */
        unsigned getDofPerNode() const;

        /*!
         * @brief Get number of DOF in every element.
         * @return Number of DOF in every element.
         */
        unsigned getTotalDofInElem() const;

        /*!
         * @brief Get number of total DOF.
         * @return Number of total DOF.
         */
        unsigned getNDofTotal() const;

        /*!
         * @brief Get matrix of coordinates.
         * @return Matrix of coordinates.
         */
        CMatrix getCoorMtx() const;

        /*!
         * @brief Get the topology matrix.
         * @return Topology matrix.
         */
        CMatrix getTopolMtx() const;

        /*!
         * @brief Get the connectivity matrix.
         * @return Connectivity matrix.
         */
        CMatrix getConnMtx() const;

        /*!
         * @brief Get the matrix of global DOF.
         * @return Matrix of global DOF.
         */
        CMatrix getGlDofMtx() const;
};

#endif
