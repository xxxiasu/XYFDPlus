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

namespace xyfd {
    class LaminarV {
    public:
        double r;
        double p;
        double t;
        double e;
        std::array<double, 2> v;

        LaminarV(double objR = 0., double objP = 0., double objT = 0., double objE = 0., std::array<double, 2> objV = {0., 0.});
        LaminarV(const LaminarV &obj);
        ~LaminarV() {}
        LaminarV operator+(const LaminarV &obj) const;
        LaminarV& operator+=(const LaminarV &obj);
        LaminarV operator-(const LaminarV &obj) const;
        LaminarV& operator-=(const LaminarV &obj);
        bool operator=(const LaminarV &obj);
        double operator*(const LaminarV &obj) const;
        friend std::ostream &operator<<(std::ostream &out, const LaminarV &obj);
    };
}