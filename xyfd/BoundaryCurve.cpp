/**
 * BoundaryCurve.cpp : xyfd class for representing parametric curve associated with boundary.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

/*------------------------------------------------------------------*\
    Dependencies
\*------------------------------------------------------------------*/
#include "GaussLegendreQuad.h"
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
        StdArray2d objTRange,
        StdArray2d (*objParamFuncPtr) (double),
        /*equivalently : StdArray2d (objParamFuncPtr) (double). objParamFuncPtr is converted to function pointer automatically*/
        StdArray2d (*objParamDFuncPtr) (double))
        /*equivalently : StdArray2d (objParamDFuncPtr) (double). objParamDFuncPtr is converted to function pointer automatically*/

    //-Remark : use member initializer list when possible
    // to limit parameter copying
        : bcId_(objBcId),
          tRange_(objTRange),
          paramFuncPtr(objParamFuncPtr),
          paramDFuncPtr(objParamDFuncPtr) {}

    BoundaryCurve::BoundaryCurve(const BoundaryCurve &obj)
        : bcId_(obj.bcId_),
          tRange_(obj.tRange_),
          paramFuncPtr(obj.paramFuncPtr),
          paramDFuncPtr(obj.paramDFuncPtr) {}

    BoundaryCurve &BoundaryCurve::operator=(const BoundaryCurve &obj)
    {
        bcId_ = obj.bcId_;
        tRange_ = obj.tRange_;
        paramFuncPtr = obj.paramFuncPtr;
        paramDFuncPtr = obj.paramDFuncPtr;
        return *this;
    }

    //-Get private members :
    //
    int BoundaryCurve::getBcId() const
    {
        return bcId_;
    }

    StdArray2d BoundaryCurve::getTRange() const
    {
        return tRange_;
    }

    //-Compute curve length :
    //
    double BoundaryCurve::length(double order) const
    {
        GaussLegendreQuad quadRule(order);
        int nGps;
        double t, w, length = 0.;

        nGps = quadRule.getX().size();

        for (int i = 0; i < nGps; ++i)
        {
            t = (tRange_[0] + tRange_[1])/2. + quadRule.getX()[i]*(tRange_[1] - tRange_[0])/2.;
            w = quadRule.getW()[i];
            length += w*sqrt(pow(paramDFuncPtr(t)[0], 2.) + pow(paramDFuncPtr(t)[1], 2.));
        }
        length *= (tRange_[1] - tRange_[0])/2.;

        return length;
    }

    //-Compute line integral of function func(x,y) :
    //
    double BoundaryCurve::lineInt(double order, double (*func) (StdArray2d)) const
    {
        GaussLegendreQuad quadRule(order);
        int nGps;
        double t, w, integral = 0.;
        StdArray2d loc;

        nGps = quadRule.getX().size();

        for (int i = 0; i < nGps; ++i)
        {
            t = (tRange_[0] + tRange_[1])/2. + quadRule.getX()[i]*(tRange_[1] - tRange_[0])/2.;
            loc = paramFuncPtr(t);
            w = quadRule.getW()[i];
            integral += w*func(loc)*sqrt(pow(paramDFuncPtr(t)[0], 2.) + pow(paramDFuncPtr(t)[1], 2.));
        }
        integral *= (tRange_[1] - tRange_[0])/2.;

        return integral;
    }
} // namespace xyfd