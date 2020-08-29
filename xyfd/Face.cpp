/**
 * Face.cpp : xyfd class for representing a face (edge).
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#include "Grid.h"
#include <iostream>
#include <vector>
#include <cmath>

namespace xyfd {
    void Grid::Face::_setLength() {
        length_ = head_->getDistanceTo(*tail_);
    }

    void Grid::Face::_setCenter() {
        center_.push_back(0.5*(head_->getX()[0] + tail_->getX()[0]));
        center_.push_back(0.5*(head_->getX()[1] + tail_->getX()[1]));
    }

    // constructor without master cell :
    Grid::Face::Face(int id, Grid::Node* head, Grid::Node* tail) {
        id_ = id;
        head_ = head;
        tail_ = tail;
        master_ = nullptr;
        tool_ = nullptr;
        _setLength();
        _setCenter();
    }

    // constructor with master & tool cells :
    Grid::Face::Face(int id, Grid::Node* head, Grid::Node* tail, Grid::Cell* master, Grid::Cell* tool) {
        id_ = id;
        head_ = head;
        tail_ = tail;
        master_ = master;
        tool_ = tool;
        _setLength();
        _setCenter();
    }

    int Grid::Face::getId() const {
        return id_;
    }

    Grid::Node* Grid::Face::getHead() const {
        return head_;
    }
    
    Grid::Node* Grid::Face::getTail() const {
        return tail_;
    }

    Grid::Cell* Grid::Face::getMaster() const {
        return master_;
    }

    Grid::Cell* Grid::Face::getTool() const {
        return tool_;
    }

    double Grid::Face::getLength() const {
        return length_;
    }

    std::vector<double> Grid::Face::getCenter() const {
        return center_;
    }
}