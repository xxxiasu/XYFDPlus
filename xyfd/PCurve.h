/**
 * PCurve.h : xyfd class for representing parametric curve.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#pragma once

/*------------------------------------------------------------------*\
    Dependencies
\*------------------------------------------------------------------*/
#include "GaussLegendreQuad.h"
#include <iostream>
#include <vector>
#include <array>

/*------------------------------------------------------------------*\
    Aliases
\*------------------------------------------------------------------*/
using StdArray2d = std::array<double, 2>;

namespace xyfd
{
    /*------------------------------------------------------------------*\
        Class declaration : xyfd::PCurve
    \*------------------------------------------------------------------*/
    class PCurve
    {
    private:
        //-Parameter range [t0, t1]
        StdArray2d tRange_;
    public:
        //-Parametric function POINTER
        StdArray2d (*paramFuncPtr) (double);

        //-Tangent of parametric function POINTER
        StdArray2d (*paramTangentPtr) (double);

        //-Custom constructor :
        //
        PCurve(
            StdArray2d objTRange,
            StdArray2d (*objParamFuncPtr) (double),
            /*equivalently : StdArray2d (objParamFuncPtr) (double). objParamFuncPtr is converted to function pointer automatically*/
            StdArray2d (*objParamTangentPtr) (double));
            /*equivalently : StdArray2d (objParamTangentPtr) (double). objParamTangentPtr is converted to function pointer automatically*/

        //-Copy constructor :
        //
        PCurve(const PCurve &obj);

        //-Destructor :
        //
        ~PCurve() {}


        //-Assignment operator :
        // chaining enabled
        //
        PCurve &operator=(const PCurve &obj);

        //-Get private members :
        //
        StdArray2d getTRange() const;

        //-Compute curve length :
        //
        double length(double order) const;

        //-Compute line integral of function func(x,y) :
        //
        double lineInt(double order, double (*func) (StdArray2d)) const;
    };
} // namespace xyfd