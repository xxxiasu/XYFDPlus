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
        LaminarV(const LaminarV& obj);
        virtual ~LaminarV() {}
        virtual LaminarV& operator=(const LaminarV& obj);
        virtual LaminarV operator+(const LaminarV& obj) const;
        virtual LaminarV& operator+=(const LaminarV& obj);
        virtual LaminarV operator-(const LaminarV& obj) const;
        virtual LaminarV& operator-=(const LaminarV& obj);
        virtual bool operator==(const LaminarV& obj) const;
        virtual bool operator!=(const LaminarV& obj) const;
        virtual std::ostream& show(std::ostream& out) const;
        
        friend std::ostream& operator<<(std::ostream& out, const LaminarV& obj);
    };
}