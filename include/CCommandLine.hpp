/*!
 * @file CCommandLine.hpp
 * @brief Headers of the main subroutines for handling command line input and
 *        output. The implementation is in the <i>CCommandLine.cpp</i> file.
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

#ifndef __CCOMMANDLINE_HPP
#define __CCOMMANDLINE_HPP

#include <string>

/*!
 * @class CCommandLine
 * @brief Class to handle command line.
 */
class CCommandLine {
    private:
        double aConst;              /*!< @brief Constant a to define geometry.*/
        double leftHeight;          /*!< @brief Left height of the plate.*/
        double rightHeight;         /*!< @brief Right height of the plate.*/
        double length;              /*!< @brief Length of the plate.*/
        double thickness;           /*!< @brief Thickness of the plate.*/
        double kXX;                 /*!< @brief Conductivity in the xx direction.*/
        double kXY;                 /*!< @brief Conductivity in the xy direction.*/
        double kYY;                 /*!< @brief Conductivity in the yy direction.*/
        unsigned Nx;                /*!< @brief Number of elements in the x direction.*/
        unsigned Ny;                /*!< @brief Number of elements in the y direction.*/
        std::string fluxLocation;   /*!< @brief Flux BC location.*/
        double fluxValue;           /*!< @brief Flux BC value.*/
        std::string tempLocation;   /*!< @brief Temperature BC location.*/
        double tempValue;           /*!< @brief Temperature BC value.*/
        bool ableToRun;             /*!< @brief Boolean to control if program is able to run.*/

    public:
        /*!
         * @brief Constructor of the class.
         * @param[in] argc - Command line argc parameter from main subroutine.
         * @param[in] argv - Command line argv parameter from main subroutine.
         */
        CCommandLine(int argc, char *argv[]);

        /*!
         * @brief Destructor of the class.
         */
        virtual ~CCommandLine();

        /*!
         * @brief Get the a constant.
         * @return A constant.
         */
        double getAConst() const;

        /*!
         * @brief Get left height.
         * @return Left height.
         */
        double getLeftHeight() const;

        /*!
         * @brief Get right height.
         * @return Right height.
         */
        double getRightHeight() const;

        /*!
         * @brief Get length of the plate.
         * @return Length of the plate.
         */
        double getLength() const;

        /*!
         * @brief Get thickness of the plate.
         * @return Thickness of the plate.
         */
        double getThickness() const;

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

        /*!
         * @brief Get number of elements in the x direction.
         * @return Number of elements in the x direction.
         */
        unsigned getNx() const;

        /*!
         * @brief Get number of elements in the y direction.
         * @return Number of elements in the y direction.
         */
        unsigned getNy() const;

        /*!
         * @brief Get flux BC location.
         * @return Flux BC location.
         */
        std::string getFluxLocation() const;

        /*!
         * @brief Get flux BC value.
         * @return Flux BC value.
         */
        double getFluxValue() const;

        /*!
         * @brief Get temperature BC location.
         * @return Temperature BC location.
         */
        std::string getTempLocation() const;

        /*!
         * @brief Get temperature BC value.
         * @return Temperature BC value.
         */
        double getTempValue() const;

        /*!
         * @brief Get boolean that controlls if program can run.
         * @return Boolean that controlls if program can run.
         */
        bool getAbleToRun() const;
};

#endif
