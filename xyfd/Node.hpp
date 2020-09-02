/**
 * Node.hpp : xyfd class for representing a grid node.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#include "Grid.h"
#include <iostream>
#include <vector>
#include <array>
#include <cmath>

using StdArray2d = std::array<double, 2>;

namespace xyfd {
    template<typename T>
    Grid<T>::Node::Node(int id, StdArray2d x) : id_(id), x_(x) {}

    template<typename T>
    int Grid<T>::Node::getId() const {
        return id_;
    }

    template<typename T>
    StdArray2d Grid<T>::Node::getX() const {
        return x_;
    }

    template<typename T>
    double Grid<T>::Node::getDistanceTo(const Grid<T>::Node& other) const {
        double accum = 0.;
        for (int i = 0; i < 2; i++) {
            accum += std::pow((x_[i] - other.getX()[i]), 2);
        }
        return std::sqrt(accum);
    }
}