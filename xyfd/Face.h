/**
 * Face.h : xyfd class for representing a face (edge).
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#pragma once

#include "Node.h"
#include <vector>

namespace xyfd {
    class Cell;

    class Face {
    private:
        int id_;
        Node* head_;
        Node* tail_;
        Cell* master_;
        Cell* tool_;
        double length_;
        std::vector<double> center_;
        // std::vector<double> normal_;

        void _setLength();
        void _setCenter();
        // void _setNormal();
    public:
        Face(int id, Node* head, Node* tail);
        Face(int id, Node* head, Node* tail, Cell* master, Cell* tool);
        int getId() const;
        Node* getHead() const;
        Node* getTail() const;
        Cell* getMaster() const;
        Cell* getTool() const;
        double getLength() const;
        std::vector<double> getCenter() const;
        // std::vector<double> getNormal() const;

        ~Face() {}
    };
}