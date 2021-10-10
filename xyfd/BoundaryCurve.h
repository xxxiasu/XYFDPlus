/**
 * BoundaryCurve.h : xyfd class for representing parametric curve associated with boundary.
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
        Class declaration : xyfd::BoundaryCurve
    \*------------------------------------------------------------------*/
    class BoundaryCurve
    {
    private:
        //-Boundary ID
        int bcId_;

        //-Parameter range [t0, t1]
        StdArray2d tRange_;
    public:
        //-Parametric function POINTER
        StdArray2d (*paramFuncPtr) (double);

        //-First derivative of parametric function POINTER
        StdArray2d (*paramDFuncPtr) (double);

        //-Custom constructor :
        //
        BoundaryCurve(
            //-Boundary is interior type by default
            int objBcId,
            StdArray2d objTRange,
            StdArray2d (*objParamFuncPtr) (double),
            /*equivalently : StdArray2d (objParamFuncPtr) (double). objParamFuncPtr is converted to function pointer automatically*/
            StdArray2d (*objParamDFuncPtr) (double));
            /*equivalently : StdArray2d (objParamDFuncPtr) (double). objParamDFuncPtr is converted to function pointer automatically*/

        //-Copy constructor :
        //
        BoundaryCurve(const BoundaryCurve &obj);

        //-Destructor :
        //
        ~BoundaryCurve() {}


        //-Assignment operator :
        // chaining enabled
        //
        BoundaryCurve &operator=(const BoundaryCurve &obj);

        //-Get private members :
        //
        int getBcId() const;
        StdArray2d getTRange() const;

        //-Compute curve length :
        //
        double length(double order) const;

        //-Compute line integral of function func(x,y) :
        //
        double lineInt(double order, double (*func) (StdArray2d)) const;
    };
} // namespace xyfd