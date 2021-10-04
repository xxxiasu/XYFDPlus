/**
 * BoundaryCurve.cpp : xyfd class for representing parametric curve associated with boundary.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

/*------------------------------------------------------------------*\
    Dependencies
\*------------------------------------------------------------------*/
#include "BoundaryCurve.h"
#include <iostream>
#include <vector>
#include <array>

/*------------------------------------------------------------------*\
    Aliases
\*------------------------------------------------------------------*/
using StdArray2d = std::array<double, 2>;

//-More comments in BoundaryCurve.h
//
namespace xyfd
{
    BoundaryCurve::BoundaryCurve(
        int objBcId,
        StdArray2d (*objParamFuncPtr) (double),
        /*equivalently : StdArray2d (objParamFuncPtr) (double). objParamFuncPtr is converted to function pointer automatically*/
        StdArray2d (*objParamDFuncPtr) (double))
        /*equivalently : StdArray2d (objParamDFuncPtr) (double). objParamDFuncPtr is converted to function pointer automatically*/

    //-Remark : use member initializer list when possible
    // to limit parameter copying
        : bcId(objBcId),
          paramFuncPtr(objParamFuncPtr),
          paramDFuncPtr(objParamDFuncPtr) {}

    BoundaryCurve::BoundaryCurve(const BoundaryCurve &obj)
        : bcId(obj.bcId),
          paramFuncPtr(obj.paramFuncPtr),
          paramDFuncPtr(obj.paramDFuncPtr) {}

    BoundaryCurve &BoundaryCurve::operator=(const BoundaryCurve &obj)
    {
        bcId = obj.bcId;
        paramFuncPtr = obj.paramFuncPtr;
        paramDFuncPtr = obj.paramDFuncPtr;
        return *this;
    }
} // namespace xyfd