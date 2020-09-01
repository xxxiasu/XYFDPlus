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
#include <Eigen/Dense>

using namespace Eigen;

namespace xyfd {
    void Grid::Face::_setLength() {
        length_ = head_->getDistanceTo(*tail_);
    }

    void Grid::Face::_setCenter() {
        center_.push_back(0.5*(head_->getX()[0] + tail_->getX()[0]));
        center_.push_back(0.5*(head_->getX()[1] + tail_->getX()[1]));
    }

    void Grid::Face::_setNormal() {
        Vector2d directMasterThis;
        Vector2d directHeadTail;
        Vector2d normal;
        Matrix2d rotate;
        rotate << 0., -1.,
                  1.,  0.;
        directMasterThis(0) = center_[0]       - master_->getCenter()[0];
        directMasterThis(1) = center_[1]       - master_->getCenter()[1];
        directHeadTail(0)   = tail_->getX()[0] - head_->getX()[0];
        directHeadTail(1)   = tail_->getX()[1] - head_->getX()[1];
        directHeadTail     /= length_;
        normal              = rotate*directHeadTail;
        if (normal.dot(directMasterThis) < 0) normal *= -1.;
        normal_ = {normal(0), normal(1)};
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

    std::vector<double> Grid::Face::getNormal() const {
        return normal_;
    }
}