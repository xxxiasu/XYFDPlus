/**
 * Face.hpp : xyfd class for representing a face (edge).
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#include "Grid.h"
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <Eigen/Dense>

using StdArray2d = std::array<double, 2>;
using namespace Eigen;

//-More comments in Grid.h
//
namespace xyfd
{
    template <typename T>
    void Grid<T>::Face::_setLength()
    {
        length_ = head_->getDistanceTo(*tail_);
    }

    template <typename T>
    void Grid<T>::Face::_setCenter()
    {
        center_[0] = 0.5 * (head_->getX()[0] + tail_->getX()[0]);
        center_[1] = 0.5 * (head_->getX()[1] + tail_->getX()[1]);
    }

    template <typename T>
    void Grid<T>::Face::_setNormal()
    {
        Vector2d directMasterThis;
        Vector2d directHeadTail;
        Vector2d normal;
        Matrix2d rotate;
        rotate << 0., -1.,
                  1., 0.;
        directMasterThis(0) = center_[0] - master_->getCenter()[0];
        directMasterThis(1) = center_[1] - master_->getCenter()[1];
        directHeadTail(0) = tail_->getX()[0] - head_->getX()[0];
        directHeadTail(1) = tail_->getX()[1] - head_->getX()[1];
        directHeadTail /= length_;
        normal = rotate * directHeadTail;
        if (normal.dot(directMasterThis) < 0)
            normal *= -1.;
        normal_ = {normal(0), normal(1)};
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
          tool_(nullptr)
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
        Grid<T>::Cell *tool)
        : id_(id),
          boundary_(0),
          head_(head),
          tail_(tail),
          master_(master),
          tool_(tool)
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