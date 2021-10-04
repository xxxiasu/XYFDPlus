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
    public:
        //-Boundary ID
        int bcId;

        //-Parametric function POINTER
        StdArray2d (*paramFuncPtr) (double);

        //-First derivative of parametric function POINTER
        StdArray2d (*paramDFuncPtr) (double);

        //-Custom constructor :
        //
        BoundaryCurve(
            //-Boundary is Dirichlet type by default
            int objBcId,
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
    };
} // namespace xyfd