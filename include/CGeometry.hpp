/*!
 * @file CGeometry.hpp
 * @brief Headers of the main subroutines for the definition of the geometry.
 *        The implementation is in the <i>CGeometry.cpp</i> file.
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

#ifndef __CGEOMETRY_HPP
#define __CGEOMETRY_HPP

/*!
 * @class CGeometry
 * @brief Class to define the geometry of the flat plate.
 */
class CGeometry {
    private:
        double aConst;          /*!< @brief Constant a to define geometry.*/
        double bConst;          /*!< @brief Constant b to define geometry.*/
        double heightLeft;      /*!< @brief Left height of the plate.*/
        double heightRight;     /*!< @brief Right height of the plate.*/
        double length;          /*!< @brief Length of the plate.*/
        double thickness;       /*!< @brief Thickness of the plate.*/

    public:
        /*!
         * @brief Constructor of the class.
         */
        CGeometry();

        /*!
         * @brief Constructor of the class.
         * @param[in] a - Constant a.
         * @param[in] h1 - Left height.
         * @param[in] h2 - Right height.
         * @param[in] L - Length.
         * @param[in] th - Thickness.
         */
        CGeometry(const double a, const double h1, const double h2,
                  const double L, const double th);

        /*!
         * @brief Destructor of the class.
         */
        virtual ~CGeometry();

        /*!
         * @brief Get the a constant.
         * @return Constant a.
         */
        double getAConst() const;

        /*!
         * @brief Get the b constant.
         * @return Constant b.
         */
        double getBConst() const;

        /*!
         * @brief Get the left height.
         * @return Left height.
         */
        double getHeightLeft() const;

        /*!
         * @brief Get the right height.
         * @return Right height.
         */
        double getHeightRight() const;

        /*!
         * @brief Get the length.
         * @return Length.
         */
        double getLength() const;

        /*!
         * @brief Get the thickness.
         * @return Thickness.
         */
        double getThickness() const;

        /*!
         * @brief Get the height at x location.
         * @param[in] x - x location on the plate.
         * @return Height.
         */
        double getHeight(double const x) const;
};

#endif
