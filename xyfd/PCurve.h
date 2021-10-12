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
//-Choose std::function over raw function pointer to enable passing capturing lambda functions
//
//-Function class F : R --> R^2
using RToR2Func  = std::function<StdArray2d(double)>;
//-Function class F : R^2 --> R
using R2ToRFunc  = std::function<double(StdArray2d)>;

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

        //-If curve is linear?
        bool linear_;

    public:
        //-Parametric function as std::function
        RToR2Func paramFunc; 

        //-Tangent of parametric function as std::function
        RToR2Func paramTangent;

        //-Normal of parametric function as std::function
        RToR2Func paramNormal;

        //-Custom constructor :
        // Based on complete input data
        //
        PCurve(
            StdArray2d objTRange,
            bool objLinear,
            const RToR2Func &objParamFunc,
            const RToR2Func &objParamTangent);

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
        bool isLinear() const;

        //-Compute curve length :
        //
        double length(double order) const;

        //-Compute line integral of function func(x,y) :
        //
        double lineInt(double order, R2ToRFunc func) const;
    };
} // namespace xyfd