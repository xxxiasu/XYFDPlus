/**
 * Face.hpp : xyfd class for representing a face (edge).
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

/*------------------------------------------------------------------*\
    Dependencies
\*------------------------------------------------------------------*/
#include "Grid.h"
#include <iostream>
#include <vector>
#include <array>
#include <cmath>

/*------------------------------------------------------------------*\
    Aliases
\*------------------------------------------------------------------*/
using StdArray2d = std::array<double, 2>;

//-More comments in Grid.h
//
// Remark : try to use getter functions to access private
// members between Node, Face, Cell classes, and use
// direct access only in Grid member functions
//
namespace xyfd
{
    template <typename T>
    void Grid<T>::Face::_setLength()
    {
        if (curve_.isLinear())
        {
            length_ = head_->getDistanceTo(*tail_);
        }
        else
        {
            //-24 is the highest order available for Gauss-Legendre rule
            length_ = curve_.length(24);
        }
    }

    //-Center is the parametric center at tMid
    // used for BOTH linear and curved faces
    //
    template <typename T>
    void Grid<T>::Face::_setCenter()
    {
        double tMid = 0.5*(curve_.getTRange()[0] + curve_.getTRange()[1]);
        center_ = curve_.paramFunc(tMid);
    }

    //-Normal vector evaluated at parametric center tMid
    // we get outward-pointing normals if nodes are indexed counter-clockwise
    // used for BOTH linear and curved faces
    //
    template <typename T>
    void Grid<T>::Face::_setNormal()
    {
        double tMid, norm;
        bool reverse;
        //-Vector pointing from master->this (face-center)
        StdArray2d directMasterThis;

        directMasterThis[0] = center_[0] - master_->getCenter()[0];
        directMasterThis[1] = center_[1] - master_->getCenter()[1];
        tMid = 0.5*(curve_.getTRange()[0] + curve_.getTRange()[1]);
        normal_ = curve_.paramNormal(tMid);
        norm = sqrt(pow(normal_[0], 2) + pow(normal_[1], 2));
        normal_[0] /= norm;
        normal_[1] /= norm;

        //-Reverse normal if the angle formed with master->this vector > Pi/2
        reverse = (directMasterThis[0]*normal_[0] + directMasterThis[1]*normal_[1]) < 0;
        if (reverse) normal_ = {-normal_[0], -normal_[1]};
    }

    template <typename T>
    Grid<T>::Face::Face(
        int id,
        Grid<T>::Node *head,
        Grid<T>::Node *tail)
        : id_(id),
          boundary_(0),
          head_(head),
          tail_(tail),
          master_(nullptr),
          tool_(nullptr),
          //-By default, PCurve associated with Face is the line segment
          // between head_ and tail_, parameter 0 <= t <= 1
          curve_(PCurve({0., 1.},
                        true,
                        [head, tail] (double t) -> StdArray2d {return {head->getX()[0] + (tail->getX()[0] - head->getX()[0])*t,
                                                                       head->getX()[1] + (tail->getX()[1] - head->getX()[1])*t};},
                        [head, tail] (double t) -> StdArray2d {return {           0.*t + (tail->getX()[0] - head->getX()[0]),
                                                                                  0.*t + (tail->getX()[1] - head->getX()[1])};}))
    {
        _setLength();
        _setCenter();
    }

    template <typename T>
    Grid<T>::Face::Face(
        int id,
        Grid<T>::Node *head,
        Grid<T>::Node *tail,
        Grid<T>::Cell *master,
        Grid<T>::Cell *tool,
        PCurve curve)
        : id_(id),
          boundary_(0),
          head_(head),
          tail_(tail),
          master_(master),
          tool_(tool),
          curve_(curve)
    {
        _setLength();
        _setCenter();
    }

    template <typename T>
    int Grid<T>::Face::getId() const
    {
        return id_;
    }

    template <typename T>
    int Grid<T>::Face::getBoundary() const
    {
        return boundary_;
    }

    template <typename T>
    typename Grid<T>::Node *Grid<T>::Face::getHead() const
    {
        return head_;
    }

    template <typename T>
    typename Grid<T>::Node *Grid<T>::Face::getTail() const
    {
        return tail_;
    }

    template <typename T>
    typename Grid<T>::Cell *Grid<T>::Face::getMaster() const
    {
        return master_;
    }

    template <typename T>
    typename Grid<T>::Cell *Grid<T>::Face::getTool() const
    {
        return tool_;
    }

    template <typename T>
    PCurve Grid<T>::Face::getCurve() const
    {
        return curve_;
    }

    template <typename T>
    double Grid<T>::Face::getLength() const
    {
        return length_;
    }

    template <typename T>
    StdArray2d Grid<T>::Face::getCenter() const
    {
        return center_;
    }

    template <typename T>
    StdArray2d Grid<T>::Face::getNormal() const
    {
        return normal_;
    }

    template <typename T>
    Grid<T>::Face::~Face() {}
} // namespace xyfd