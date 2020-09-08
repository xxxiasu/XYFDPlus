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

namespace xyfd
{
    class LaminarV
    {
    public:
        //-Density (kg.m^-3)
        double r;
        //-Static pressure (Pa)
        double p;
        //-Temperature (K)
        double t;
        //-Specific total energy (m^2.s^-2)
        double e;
        //-2D velocity vector (m.s^-1)
        StdArray2d v;

        //-Custom constructor :
        // based on user input, default set to 0
        //
        LaminarV(
            double objR = 0.,
            double objP = 0.,
            double objT = 0.,
            double objE = 0.,
            StdArray2d objV = {0., 0.});

        //-Copy constructor :
        //
        LaminarV(const LaminarV &obj);

        //-Destructor :
        //
        virtual ~LaminarV() {}

        //
        //-Operator overloading :
        // All operators declared here are virtual to allow polymorphism
        //----------------------------------------------------------v
        //

        //-Assignment operator :
        // chaining enabled
        //
        virtual LaminarV &operator=(const LaminarV &obj);

        virtual LaminarV operator+(const LaminarV &obj) const;
        virtual LaminarV &operator+=(const LaminarV &obj);
        virtual LaminarV operator-(const LaminarV &obj) const;
        virtual LaminarV &operator-=(const LaminarV &obj);
        virtual bool operator==(const LaminarV &obj) const;
        virtual bool operator!=(const LaminarV &obj) const;

        //
        //----------------------------------------------------------^
        //

        //-Virtual show function to be used inside operator<<
        // for inheritance, since friend operator cannot be
        // inherited directly
        //
        virtual std::ostream &show(std::ostream &out) const;

        //-operator<< is a friend operator
        // declared only once here, NOT in derived class header TurbulentV.h
        //
        friend std::ostream &operator<<(
            std::ostream &out,
            const LaminarV &obj);
    };
} // namespace xyfd