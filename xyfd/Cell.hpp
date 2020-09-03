/**
 * Cell.hpp : xyfd class for representing a grid cell.
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
    void Grid<T>::Cell::_setType() {
        type_ = (int)nodes_.size();
    }

    template<typename T>
    void Grid<T>::Cell::_setArea() {
        area_ = 0.;
        for (int i = 0; i < type_; i++) {
            int j = (i+1)%type_;
            area_+= nodes_[i]->getX()[0]*nodes_[j]->getX()[1] -
                    nodes_[i]->getX()[1]*nodes_[j]->getX()[0];
        }
        area_ = 0.5*std::abs(area_);
    }

    template<typename T>
    void Grid<T>::Cell::_setCenter() {
        center_ = {0., 0.};
        for (const auto& node : nodes_) {
            center_[0] += node->getX()[0];
            center_[1] += node->getX()[1];
        }
        center_[0] /= type_;
        center_[1] /= type_;
    }

    template<typename T>
    void Grid<T>::Cell::_setNeighbors() {
        neighbors_ = {};
        for (const auto& face : faces_) {
            if (face->master_ == this && face->tool_) {
                neighbors_.push_back(face->tool_);
            }
            else if (face->tool_ == this && face->master_) {
                neighbors_.push_back(face->master_);
            }
        }
    }

    template<typename T>
    Grid<T>::Cell::Cell(int id, std::vector<Grid<T>::Node*> nodes, std::vector<Grid<T>::Face*> faces) {
        id_ = id;
        nodes_ = nodes;
        faces_ = faces;
        _setType();
        _setArea();
        _setCenter();
    }

    template<typename T>
    int Grid<T>::Cell::getId() const {
        return id_;
    }

    template<typename T>
    int Grid<T>::Cell::getType() const {
        return type_;
    }

    template<typename T>
    std::vector<typename Grid<T>::Node *> Grid<T>::Cell::getNodes() const {
        return nodes_;
    }

    template<typename T>
    std::vector<typename Grid<T>::Face *> Grid<T>::Cell::getFaces() const {
        return faces_;
    }

    template<typename T>
    double Grid<T>::Cell::getArea() const {
        return area_;
    }

    template<typename T>
    StdArray2d Grid<T>::Cell::getCenter() const {
        return center_;
    }

    template<typename T>
    std::vector<typename Grid<T>::Cell *> Grid<T>::Cell::getNeighbors() const {
        return neighbors_;
    }

    template<typename T>
    Grid<T>::Cell::~Cell() {
        std::cout << "Cell # " << id_ << " deleted !" << std::endl;
    }
}