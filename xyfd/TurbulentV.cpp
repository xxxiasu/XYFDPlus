/**
 * TurbulentV.cpp : xyfd class for representing the primitive variable in turbulent flow.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#include "TurbulentV.h"
#include <iostream>
#include <vector>
#include <array>

using StdArray2d = std::array<double, 2>;
using StdArray4d = std::array<double, 4>;

namespace xyfd
{
    TurbulentV::TurbulentV(
        double objR,
        double objP,
        double objT,
        double objE,
        StdArray2d objV,
        StdArray4d objRij,
        double objEps)
        : LaminarV(objR,
                   objP,
                   objT,
                   objE,
                   objV),
          rij(objRij),
          eps(objEps) {}

    TurbulentV::TurbulentV(const TurbulentV &obj)
        : LaminarV(obj),
          rij(obj.rij),
          eps(obj.eps) {}

    TurbulentV &TurbulentV::operator=(const TurbulentV &obj)
    {
        LaminarV::operator=(obj);
        rij[0] = obj.rij[0];
        rij[1] = obj.rij[1];
        rij[2] = obj.rij[2];
        rij[3] = obj.rij[3];
        eps = obj.eps;
        return *this;
    }

    TurbulentV TurbulentV::operator+(const TurbulentV &obj) const
    {
        TurbulentV res;
        res.r = r + obj.r;
        res.p = p + obj.p;
        res.t = t + obj.t;
        res.e = e + obj.e;
        res.v[0] = v[0] + obj.v[0];
        res.v[1] = v[1] + obj.v[1];
        res.rij[0] = rij[0] + obj.rij[0];
        res.rij[1] = rij[1] + obj.rij[1];
        res.rij[2] = rij[2] + obj.rij[2];
        res.rij[3] = rij[3] + obj.rij[3];
        res.eps = eps + obj.eps;
        return res;
    }

    TurbulentV &TurbulentV::operator+=(const TurbulentV &obj)
    {
        LaminarV::operator+=(obj);
        rij[0] += obj.rij[0];
        rij[1] += obj.rij[1];
        rij[2] += obj.rij[2];
        rij[3] += obj.rij[3];
        eps += obj.eps;
        return *this;
    }

    TurbulentV TurbulentV::operator-(const TurbulentV &obj) const
    {
        TurbulentV res;
        res.r = r - obj.r;
        res.p = p - obj.p;
        res.t = t - obj.t;
        res.e = e - obj.e;
        res.v[0] = v[0] - obj.v[0];
        res.v[1] = v[1] - obj.v[1];
        res.rij[0] = rij[0] - obj.rij[0];
        res.rij[1] = rij[1] - obj.rij[1];
        res.rij[2] = rij[2] - obj.rij[2];
        res.rij[3] = rij[3] - obj.rij[3];
        res.eps = eps - obj.eps;
        return res;
    }

    TurbulentV &TurbulentV::operator-=(const TurbulentV &obj)
    {
        LaminarV::operator-=(obj);
        rij[0] -= obj.rij[0];
        rij[1] -= obj.rij[1];
        rij[2] -= obj.rij[2];
        rij[3] -= obj.rij[3];
        eps -= obj.eps;
        return *this;
    }

    bool TurbulentV::operator==(const TurbulentV &obj) const
    {
        return LaminarV::operator==(obj) &&
               rij[0] == obj.rij[0] && rij[1] == obj.rij[1] && rij[2] == obj.rij[2] && rij[3] == obj.rij[3] && eps == obj.eps;
    }

    bool TurbulentV::operator!=(const TurbulentV &obj) const
    {
        return LaminarV::operator!=(obj) ||
               rij[0] != obj.rij[0] || rij[1] != obj.rij[1] || rij[2] != obj.rij[2] || rij[3] != obj.rij[3] || eps != obj.eps;
    }

    std::ostream &TurbulentV::show(std::ostream &out) const
    {
        out << "[ ";
        out << r << ", " << p << ", " << t << ", " << e << ", (" << v[0] << ", " << v[1] << ") , ("
            << rij[0] << ", " << rij[1] << ", " << rij[2] << ", " << rij[3] << "), " << eps << "]";
        return out;
    }
} // namespace xyfd