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

namespace xyfd
{
    class TurbulentV : public LaminarV
    {
    public:
        //-2D vector of Reynolds stresses (m^2.s^-2)
        StdArray4d rij;
        //-Dissipation of turbulent kinetic energy (m^2.s^-3)
        double eps;

        //-Custom constructor :
        // based on user input, default set to 0
        //
        TurbulentV(
            double objR = 0.,
            double objP = 0.,
            double objT = 0.,
            double objE = 0.,
            StdArray2d objV = {0., 0.},
            StdArray4d objRij = {0., 0., 0., 0.},
            double objEps = 0.);

        //-Copy constructor :
        //
        TurbulentV(const TurbulentV &obj);

        //-Destructor :
        //
        ~TurbulentV() {}

        //
        //-Operator overloading :
        // All operators declared here are virtual in LaminarV.h
        // to allow polymorphism
        //----------------------------------------------------------v
        //

        //-Assignment operator :
        // chaining enabled
        //
        TurbulentV &operator=(const TurbulentV &obj);

        TurbulentV operator+(const TurbulentV &obj) const;
        TurbulentV &operator+=(const TurbulentV &obj);
        TurbulentV operator-(const TurbulentV &obj) const;
        TurbulentV &operator-=(const TurbulentV &obj);
        bool operator==(const TurbulentV &obj) const;
        bool operator!=(const TurbulentV &obj) const;

        //
        //----------------------------------------------------------^
        //

        //-To be used inside friend operator<< declared in
        // LaminarV.h
        //
        std::ostream &show(std::ostream &out) const;
    };
} // namespace xyfd