/**
 * Cell.h : xyfd class for representing a grid cell.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#pragma once

#include "Node.h"
#include <vector>

namespace xyfd {
    class Face;

    class Cell {
    private:
        int id_;
        int type_;
        std::vector<Node*> nodes_;
        std::vector<Face*> faces_;
        std::vector<Cell*> neighbors_;
        double area_;
        std::vector<double> center_;

        void _setType();
        void _setArea();
        void _setCenter();
        void _setNeighbors();
    public:
        Cell(int id, std::vector<Node*> nodes, std::vector<Face*> faces);
        int getId() const;
        int getType() const;
        std::vector<Node*> getNodes() const;
        std::vector<Face*> getFaces() const;
        double getArea() const;
        std::vector<double> getCenter() const;

        ~Cell() {}
    };
}

