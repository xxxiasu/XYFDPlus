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
#include <functional>

/*------------------------------------------------------------------*\
    Aliases
\*------------------------------------------------------------------*/
using StdArray2d = std::array<double, 2>;
using VectorFunc = std::function<StdArray2d(double)>;

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
        // StdArray2d (*paramFuncPtr) (double);
        VectorFunc paramFunc; 

        //-Tangent of parametric function POINTER
        // StdArray2d (*paramTangentPtr) (double);
        VectorFunc paramTangent;

        //-Custom constructor :
        //
        PCurve(
            StdArray2d objTRange,
            // StdArray2d (*objParamFuncPtr) (double),
            /*equivalently : StdArray2d (objParamFuncPtr) (double). objParamFuncPtr is converted to function pointer automatically*/
            VectorFunc objParamFunc,
            // StdArray2d (*objParamTangentPtr) (double));
            /*equivalently : StdArray2d (objParamTangentPtr) (double). objParamTangentPtr is converted to function pointer automatically*/
            VectorFunc objParamTangent);

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