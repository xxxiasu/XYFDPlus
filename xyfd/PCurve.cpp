/**
 * PCurve.cpp : xyfd class for representing parametric curve.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

/*------------------------------------------------------------------*\
    Dependencies
\*------------------------------------------------------------------*/
#include "GaussLegendreQuad.h"
#include "PCurve.h"
#include <iostream>
#include <vector>
#include <array>

/*------------------------------------------------------------------*\
    Aliases
\*------------------------------------------------------------------*/
using StdArray2d = std::array<double, 2>;

//-More comments in PCurve.h
//
namespace xyfd
{
    PCurve::PCurve(
        StdArray2d objTRange,
        StdArray2d (*objParamFuncPtr) (double),
        /*equivalently : StdArray2d (objParamFuncPtr) (double). objParamFuncPtr is converted to function pointer automatically*/
        StdArray2d (*objParamTangentPtr) (double))
        /*equivalently : StdArray2d (objParamTangentPtr) (double). objParamTangentPtr is converted to function pointer automatically*/

    //-Remark : use member initializer list when possible
    // to limit parameter copying
        : tRange_(objTRange),
          paramFuncPtr(objParamFuncPtr),
          paramTangentPtr(objParamTangentPtr) {}

    PCurve::PCurve(const PCurve &obj)
        : tRange_(obj.tRange_),
          paramFuncPtr(obj.paramFuncPtr),
          paramTangentPtr(obj.paramTangentPtr) {}

    PCurve &PCurve::operator=(const PCurve &obj)
    {
        tRange_ = obj.tRange_;
        paramFuncPtr = obj.paramFuncPtr;
        paramTangentPtr = obj.paramTangentPtr;
        return *this;
    }

    //-Get private members :
    //
    StdArray2d PCurve::getTRange() const
    {
        return tRange_;
    }

    //-Compute curve length :
    //
    double PCurve::length(double order) const
    {
        GaussLegendreQuad quadRule(order);
        int nGps;
        double t, w, len = 0.;

        nGps = quadRule.getX().size();

        for (int i = 0; i < nGps; ++i)
        {
            t = (tRange_[0] + tRange_[1])/2. + quadRule.getX()[i]*(tRange_[1] - tRange_[0])/2.;
            w = quadRule.getW()[i];
            len += w*sqrt(pow(paramTangentPtr(t)[0], 2.)
                        + pow(paramTangentPtr(t)[1], 2.));
        }
        len *= (tRange_[1] - tRange_[0])/2.;

        return len;
    }

    //-Compute line integral of function func(x,y) :
    //
    double PCurve::lineInt(double order, double (*func) (StdArray2d)) const
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
            integral += w*func(loc)*sqrt(pow(paramTangentPtr(t)[0], 2.)
                                       + pow(paramTangentPtr(t)[1], 2.));
        }
        integral *= (tRange_[1] - tRange_[0])/2.;

        return integral;
    }
} // namespace xyfd