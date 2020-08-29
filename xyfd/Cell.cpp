/**
 * Cell.cpp : xyfd class for representing a grid cell.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#include "Grid.h"
#include <iostream>
#include <vector>
#include <cmath>

namespace xyfd {
    void Grid::Cell::_setType() {
        type_ = (int)nodes_.size();
    }

    void Grid::Cell::_setArea() {
        area_ = 0.;
        for (int i = 0; i < type_; i++) {
            int j = (i+1)%type_;
            area_+= nodes_[i]->getX()[0]*nodes_[j]->getX()[1] -
                    nodes_[i]->getX()[1]*nodes_[j]->getX()[0];
        }
        area_ = 0.5*std::abs(area_);
    }

    void Grid::Cell::_setCenter() {
        center_ = {0., 0.};
        for (const auto& node : nodes_) {
            center_[0] += node->getX()[0];
            center_[1] += node->getX()[1];
        }
        center_[0] /= type_;
        center_[1] /= type_;
    }

    void Grid::Cell::_setNeighbors() {
        neighbors_.resize(type_, nullptr);
        for (int i = 0; i < type_; i++) {
            if      (faces_[i]->getMaster() && !faces_[i]->getTool()) {
                neighbors_[i] = faces_[i]->getMaster();
            }
            else if (faces_[i]->getTool() && !faces_[i]->getMaster()) {
                neighbors_[i] = faces_[i]->getTool();
            }
            else if (!faces_[i]->getTool() && !faces_[i]->getMaster()) {
                std::cout << "Master and tool cells not found for Grid::Face #" << faces_[i]->getId() << std::endl;
            }
            else if (faces_[i]->getMaster()->getId() == id_) {
                neighbors_[i] = faces_[i]->getTool();
            }
            else {
                neighbors_[i] = faces_[i]->getMaster();
            }
        }
    }

    Grid::Cell::Cell(int id, std::vector<Grid::Node*> nodes, std::vector<Grid::Face*> faces) {
        id_ = id;
        nodes_ = nodes;
        faces_ = faces;
        _setType();
        _setArea();
        _setCenter();
        _setNeighbors();
    }

    int Grid::Cell::getId() const {
        return id_;
    }

    int Grid::Cell::getType() const {
        return type_;
    }

    std::vector<Grid::Node *> Grid::Cell::getNodes() const {
        return nodes_;
    }

    std::vector<Grid::Face *> Grid::Cell::getFaces() const {
        return faces_;
    }

    double Grid::Cell::getArea() const {
        return area_;
    }
    std::vector<double> Grid::Cell::getCenter() const {
        return center_;
    }
}