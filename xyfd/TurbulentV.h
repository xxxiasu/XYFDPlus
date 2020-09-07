/**
 * TurbulentV.h : xyfd class for representing the primitive variable in turbulent flow.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#pragma once
#include "LaminarV.h"
#include <iostream>
#include <vector>
#include <array>

using StdArray2d = std::array<double, 2>;
using StdArray4d = std::array<double, 4>;

namespace xyfd {
    class TurbulentV : public LaminarV {
    public:
        StdArray4d rij;
        double eps;

        TurbulentV(double objR = 0., double objP = 0., double objT = 0., double objE = 0., StdArray2d objV = {0., 0.},
                   StdArray4d objRij = {0., 0., 0., 0.}, double objEps = 0.);
        TurbulentV(const TurbulentV& obj);
        ~TurbulentV() {}
        TurbulentV& operator=(const TurbulentV& obj);
        TurbulentV operator+(const TurbulentV& obj) const;
        TurbulentV& operator+=(const TurbulentV& obj);
        TurbulentV operator-(const TurbulentV& obj) const;
        TurbulentV& operator-=(const TurbulentV& obj);
        bool operator==(const TurbulentV& obj) const;
        bool operator!=(const TurbulentV& obj) const;
        std::ostream& show(std::ostream& out) const;
    };
}