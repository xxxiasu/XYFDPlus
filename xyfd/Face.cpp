/**
 * Face.cpp : xyfd class for representing a face (edge).
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#include "Face.h"
#include "Cell.h"
#include <iostream>
#include <vector>
#include <cmath>

namespace xyfd {
    void Face::_setLength() {
        length_ = head_->getDistanceTo(*tail_);
    }

    void Face::_setCenter() {
        center_.push_back(0.5*(head_->getX()[0] + tail_->getX()[0]));
        center_.push_back(0.5*(head_->getX()[1] + tail_->getX()[1]));
    }

    // constructor without master cell :
    Face::Face(int id, Node* head, Node* tail) {
        id_ = id;
        head_ = head;
        tail_ = tail;
        master_ = nullptr;
        tool_ = nullptr;
        _setLength();
        _setCenter();
    }

    // constructor with master & tool cells :
    Face::Face(int id, Node* head, Node* tail, Cell* master, Cell* tool) {
        id_ = id;
        head_ = head;
        tail_ = tail;
        master_ = master;
        tool_ = tool;
        _setLength();
        _setCenter();
    }

    int Face::getId() const {
        return id_;
    }

    Node* Face::getHead() const {
        return head_;
    }
    
    Node* Face::getTail() const {
        return tail_;
    }

    Cell* Face::getMaster() const {
        return master_;
    }

    Cell* Face::getTool() const {
        return tool_;
    }

    double Face::getLength() const {
        return length_;
    }

    std::vector<double> Face::getCenter() const {
        return center_;
    }
}