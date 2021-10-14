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

//-More comments in PCurve.h
//
namespace xyfd
{
    PCurve::PCurve(
        StdArray2d objTRange,
        bool objLinear,
        const RToR2Func &objParamFunc,
        const RToR2Func &objParamTangent)

    //-Remark : use member initializer list when possible
    // to limit parameter copying
        : tRange_(objTRange),
          linear_(objLinear),
          paramFunc(objParamFunc),
          paramTangent(objParamTangent),
          paramNormal(objParamTangent)
          {
              //-Normal vector is obtained by rotating tangent vector by -Pi/2
              paramNormal = [this](double t) -> StdArray2d
                            {return {paramTangent(t)[1], -paramTangent(t)[0]};};
          }

    PCurve::PCurve(const PCurve &obj)
        : tRange_(obj.tRange_),
          linear_(obj.linear_),
          paramFunc(obj.paramFunc),
          paramTangent(obj.paramTangent),
          paramNormal(obj.paramNormal) {}

    PCurve &PCurve::operator=(const PCurve &obj)
    {
        tRange_ = obj.tRange_;
        linear_ = obj.linear_;
        paramFunc = obj.paramFunc;
        paramTangent = obj.paramTangent;
        paramNormal = obj.paramNormal;
        return *this;
    }

    //-Get private members :
    //
    StdArray2d PCurve::getTRange() const
    {
        return tRange_;
    }

    bool PCurve::isLinear() const
    {
        return linear_;
    }

    //-Compute curve length :
    //
    double PCurve::length(double order) const
    {
        GaussLegendreQuad quadRule(order);
        int nGps;
        double t, w, len = 0.;

        nGps = quadRule.getX().size();

        for (int i = 0; i < nGps; i++)
        {
            t = (tRange_[0] + tRange_[1])/2. + quadRule.getX()[i]*abs(tRange_[1] - tRange_[0])/2.;
            w = quadRule.getW()[i];
            len += w*sqrt(pow(paramTangent(t)[0], 2.)
                        + pow(paramTangent(t)[1], 2.));
        }
        len *= abs(tRange_[1] - tRange_[0])/2.;

        return len;
    }

    //-Compute line integral of function func(x,y) :
    //
    double PCurve::lineInt(double order, R2ToRFunc func) const
    {
        GaussLegendreQuad quadRule(order);
        int nGps;
        double t, w, integral = 0.;
        StdArray2d loc;

        nGps = quadRule.getX().size();

        for (int i = 0; i < nGps; i++)
        {
            t = (tRange_[0] + tRange_[1])/2. + quadRule.getX()[i]*abs(tRange_[1] - tRange_[0])/2.;
            loc = paramFunc(t);
            w = quadRule.getW()[i];
            integral += w*func(loc)*sqrt(pow(paramTangent(t)[0], 2.)
                                       + pow(paramTangent(t)[1], 2.));
        }
        integral *= abs(tRange_[1] - tRange_[0])/2.;

        return integral;
    }
} // namespace xyfd