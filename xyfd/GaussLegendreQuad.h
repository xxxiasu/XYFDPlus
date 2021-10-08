/**
 * GaussLegendreQuad.h : xyfd class for representing Gauss-Legendre quadrature rules.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#pragma once

/*------------------------------------------------------------------*\
    Dependencies
\*------------------------------------------------------------------*/
#include <iostream>
#include <cmath>
#include <vector>
#include <array>

/*------------------------------------------------------------------*\
    Aliases
\*------------------------------------------------------------------*/
using StdArray2d = std::array<double, 2>;
using DoubleVec  = std::vector<double>;

namespace xyfd
{
    /*------------------------------------------------------------------*\
        Class declaration : xyfd::GaussLegendreQuad
    \*------------------------------------------------------------------*/
    class GaussLegendreQuad
    {
    private:
        //-Order of quadrature rule
        int order_;

        //-Vector of quadrature locations [-1, 1]
        DoubleVec x_;

        //-Vector of quadrature weights
        DoubleVec w_;

        void _setX();
        void _setW();
    public:
        //-Custom constructor :
        //
        GaussLegendreQuad(int order);

        //-Copy constructor :
        //
        GaussLegendreQuad(const GaussLegendreQuad &obj);

        //-Destructor :
        //
        ~GaussLegendreQuad() {}

        //-Assignment operator :
        // chaining enabled
        //
        GaussLegendreQuad &operator=(const GaussLegendreQuad &obj);

        //-Get private members :
        //
        int getOrder() const;
        DoubleVec getX() const;
        DoubleVec getW() const;
    };
} // namespace xyfd