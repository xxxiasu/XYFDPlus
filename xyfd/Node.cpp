/**
 * Node.cpp : xyfd class for representing a grid node.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#include "Grid.h"
#include <iostream>
#include <vector>
#include <cmath>

namespace xyfd {
    Grid::Node::Node(int id, std::vector<double> x) {
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

    int Grid::Node::getId() const {
        return id_;
    }

    std::vector<double> Grid::Node::getX() const {
        return x_;
    }

    double Grid::Node::getDistanceTo(const Grid::Node& other) const {
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