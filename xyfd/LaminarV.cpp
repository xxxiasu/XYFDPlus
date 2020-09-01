/**
 * LaminarV.cpp : xyfd class for representing the primitive variable in laminar flow.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#include "LaminarV.h"
#include <iostream>
#include <vector>
#include <array>

namespace xyfd {
    LaminarV::LaminarV(double objR, double objP, double objT, double objE, std::array<double, 2> objV) {
        r = objR;
        p = objP;
        t = objT;
        e = objE;
        v = objV;
    }

    LaminarV::LaminarV(const LaminarV &obj) {
        r = obj.r;
        p = obj.p;
        t = obj.t;
        e = obj.e;
        v = obj.v;
    }

    LaminarV LaminarV::operator+(const LaminarV &obj) const {
        LaminarV res;
        res.r = r + obj.r;
        res.p = p + obj.p;
        res.t = t + obj.t;
        res.e = e + obj.e;
        res.v[0] = v[0] + obj.v[0];
        res.v[1] = v[1] + obj.v[1];
        return res;
    }

    LaminarV& LaminarV::operator+=(const LaminarV &obj) {
        r += obj.r;
        p += obj.p;
        t += obj.t;
        e += obj.e;
        v[0] += obj.v[0];
        v[1] += obj.v[1];
        return *this;
    }

    LaminarV LaminarV::operator-(const LaminarV &obj) const {
        LaminarV res;
        res.r = r - obj.r;
        res.p = p - obj.p;
        res.t = t - obj.t;
        res.e = e - obj.e;
        res.v[0] = v[0] - obj.v[0];
        res.v[1] = v[1] - obj.v[1];
        return res;
    }

    LaminarV& LaminarV::operator-=(const LaminarV &obj) {
        r -= obj.r;
        p -= obj.p;
        t -= obj.t;
        e -= obj.e;
        v[0] -= obj.v[0];
        v[1] -= obj.v[1];
        return *this;
    }

    bool LaminarV::operator=(const LaminarV &obj) {
        if (this == &obj) return 1; // avoid self-assignment
        r = obj.r;
        p = obj.p;
        t = obj.t;
        e = obj.e;
        v[0] = obj.v[0];
        v[1] = obj.v[1];
        return 1;
    }

    std::ostream &operator<<(std::ostream &out, const LaminarV &obj) {
        out << "{ ";
        out << obj.r << ", " << obj.p << ", " << obj.t << ", " << obj.e << ", (" << obj.v[0] << ", " << obj.v[1] << ") " << "}";
        return out;
    }
}