/*!
 * @file CMaterial.hpp
 * @brief Headers of the main subroutines for defining material properties.
 *        The implementation is in the <i>CMaterial.cpp</i> file.
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

#ifndef __CMATERIAL_HPP
#define __CMATERIAL_HPP

#include "CMatrix.hpp"

/*!
 * @class CMaterial
 * @brief Class to define the properties of the material.
 */
class CMaterial {
    private:
        double conducXX;    /*!< @brief Conductivity in the xx direction.*/
        double conducXY;    /*!< @brief Conductivity in the xy direction.*/
        double conducYY;    /*!< @brief Conductivity in the yy direction.*/

    public:
        /*!
         * @brief Constructor of the class.
         */
        CMaterial();

        /*!
         * @brief Constructor of the class.
         * @param[in] kXX - Conductivity in the xx direction.
         * @param[in] kXY - Conductivity in the xy direction.
         * @param[in] kYY - Conductivity in the yy direction.
         */
        CMaterial(const double kXX, const double kXY, const double kYY);

        /*!
         * @brief Destructor of the class.
         */
        virtual ~CMaterial();

        /*!
         * @brief Get conductivity matrix.
         * @return Conductivity matrix.
         */
        CMatrix getConductivityMatrix() const;

        /*!
         * @brief Get conductivity in the xx direction.
         * @return Conductivity in the xx direction.
         */
        double getKXX() const;

        /*!
         * @brief Get conductivity in the xy direction.
         * @return Conductivity in the xy direction.
         */
        double getKXY() const;

        /*!
         * @brief Get conductivity in the yy direction.
         * @return Conductivity in the yy direction.
         */
        double getKYY() const;
};

#endif
