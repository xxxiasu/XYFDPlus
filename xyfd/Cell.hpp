/**
 * Cell.hpp : xyfd class for representing a grid cell.
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
namespace xyfd
{
    //-Remark : try to use getter functions to access private
    // members between Node, Face, Cell classes, and use
    // direct access only in Grid member functions
    //
    template <typename T>
    void Grid<T>::Cell::_setType()
    {
        type_ = (int)nodes_.size();
    }

    template <typename T>
    void Grid<T>::Cell::_setArea()
    {
        area_ = 0.;
        for (int i = 0; i < type_; i++)
        {
            int j = (i + 1) % type_;
            area_ += nodes_[i]->getX()[0] * nodes_[j]->getX()[1] -
                     nodes_[i]->getX()[1] * nodes_[j]->getX()[0];
        }
        area_ = 0.5 * std::abs(area_);
    }

    template <typename T>
    void Grid<T>::Cell::_setCenter()
    {
        center_ = {0., 0.};
        for (const auto &node : nodes_)
        {
            center_[0] += node->getX()[0];
            center_[1] += node->getX()[1];
        }
        center_[0] /= type_;
        center_[1] /= type_;
    }

    template <typename T>
    void Grid<T>::Cell::_setBoundaryFaces()
    {
        boundaryFaces_ = {};
        for (const auto &face : faces_)
        {
            if (face->boundary_ != 0)
                boundaryFaces_.push_back(face);
        }
    }

    template <typename T>
    void Grid<T>::Cell::_setNeighbors()
    {
        neighbors_ = {};
        for (const auto &face : faces_)
        {
            if (face->getMaster() == this && face->getTool())
            {
                neighbors_.push_back(face->getTool());
            }
            else if (face->getTool() == this && face->getMaster())
            {
                neighbors_.push_back(face->getMaster());
            }
        }
    }

    template <typename T>
    Grid<T>::Cell::Cell(
        int id,
        std::vector<Grid<T>::Node *> nodes,
        std::vector<Grid<T>::Face *> faces)
        : id_(id),
          nodes_(nodes),
          faces_(faces)
    {
        _setType();
        _setArea();
        _setCenter();
    }

    template <typename T>
    int Grid<T>::Cell::getId() const
    {
        return id_;
    }

    template <typename T>
    int Grid<T>::Cell::getType() const
    {
        return type_;
    }

    template <typename T>
    std::vector<typename Grid<T>::Node *> Grid<T>::Cell::getNodes() const
    {
        return nodes_;
    }

    template <typename T>
    std::vector<typename Grid<T>::Face *> Grid<T>::Cell::getFaces() const
    {
        return faces_;
    }

    template <typename T>
    std::vector<typename Grid<T>::Face *> Grid<T>::Cell::getBoundaryFaces() const
    {
        return boundaryFaces_;
    }

    template <typename T>
    double Grid<T>::Cell::getArea() const
    {
        return area_;
    }

    template <typename T>
    StdArray2d Grid<T>::Cell::getCenter() const
    {
        return center_;
    }

    template <typename T>
    std::vector<typename Grid<T>::Cell *> Grid<T>::Cell::getNeighbors() const
    {
        return neighbors_;
    }

    template <typename T>
    Grid<T>::Cell::~Cell() {}
} // namespace xyfd