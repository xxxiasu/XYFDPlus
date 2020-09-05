/**
 * LaminarV.h : xyfd class for representing the primitive variable in laminar flow.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#pragma once
#include <iostream>
#include <vector>
#include <array>

using StdArray2d = std::array<double, 2>;

namespace xyfd {
    class LaminarV {
    public:
        double r;
        double p;
        double t;
        double e;
        StdArray2d v;

        LaminarV(double objR = 0., double objP = 0., double objT = 0., double objE = 0., StdArray2d objV = {0., 0.});
        LaminarV(const LaminarV &obj);
        ~LaminarV() {}
        LaminarV operator+(const LaminarV &obj) const;
        LaminarV& operator+=(const LaminarV &obj);
        LaminarV operator-(const LaminarV &obj) const;
        LaminarV& operator-=(const LaminarV &obj);
        bool operator==(const LaminarV &obj) const;
        bool operator=(const LaminarV &obj);
        double operator*(const LaminarV &obj) const;
        friend std::ostream &operator<<(std::ostream &out, const LaminarV &obj);
    };
}