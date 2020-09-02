/**
 * Node.hpp : xyfd class for representing a grid node.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#include "Grid.h"
#include <iostream>
#include <vector>
#include <cmath>

namespace xyfd {
    template<typename T>
    Grid<T>::Node::Node(int id, std::vector<double> x) {
        id_ = id;
        if (x.size() == 2) {
            x_ = x;
        }
        else {
            std::cout << "xyfd::Node constructor error : Node dimension mismatch ! "
                          "x_ set to zero vector [0., 0.] at Node #" << id_ << std::endl;
            x_ = {0., 0.};
        }
    }

    template<typename T>
    int Grid<T>::Node::getId() const {
        return id_;
    }

    template<typename T>
    std::vector<double> Grid<T>::Node::getX() const {
        return x_;
    }

    template<typename T>
    double Grid<T>::Node::getDistanceTo(const Grid<T>::Node& other) const {
        if (x_.size() == other.getX().size()) {
            double accum = 0.;
            for (int i = 0; i <= (int)x_.size()-1; i++) {
                accum += std::pow((x_[i] - other.getX()[i]), 2);
            }
            return std::sqrt(accum);
        }
        else {
            std::cout << "xyfd::Node getDistanceTo() error : Node dimension mismatch ! "
                         "Output set to zero." << std::endl;
            return 0.;
        }
    }
}