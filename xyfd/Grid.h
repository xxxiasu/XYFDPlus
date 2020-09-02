/**
 * Grid.h : xyfd class for representing a 2D unstructured grid.
 * (adjacency list implementation)
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#pragma once

#include "Link.h"
#include "LaminarV.h"
#include <vector>

namespace xyfd {
    template<typename T>
    class Grid {
    private:
        void _setNodesInGrid(const Link& link);
        void _setFacesCellsInGrid(const Link& link);

    public:        
        class Node {
        friend class Grid;
        private:
            int id_;
            std::vector<double> x_;

        public:
            Node(int id, std::vector<double> x);
            int getId() const;
            std::vector<double> getX() const;
            double getDistanceTo(const Node &other) const;

            ~Node() {}
        };
        class Cell; // forward declaration
        class Face {
        friend class Grid;
        private:
            int id_;
            Node *head_;
            Node *tail_;
            Cell *master_;
            Cell *tool_;
            double length_;
            std::vector<double> center_;
            std::vector<double> normal_;

            void _setLength();
            void _setCenter();
            void _setNormal();

        public:
            Face(int id, Node *head, Node *tail);
            Face(int id, Node *head, Node *tail, Cell *master, Cell *tool);
            int getId() const;
            Node *getHead() const;
            Node *getTail() const;
            Cell *getMaster() const;
            Cell *getTool() const;
            double getLength() const;
            std::vector<double> getCenter() const;
            std::vector<double> getNormal() const;

            ~Face() {}
        };
        class Cell {
        friend class Grid;
        private:
            int id_;
            int type_;
            std::vector<Node *> nodes_;
            std::vector<Face *> faces_;
            std::vector<Cell *> neighbors_;
            double area_;
            std::vector<double> center_;

            void _setType();
            void _setArea();
            void _setCenter();
            void _setNeighbors();

        public:
            T var;
            Cell(int id, std::vector<Node *> nodes, std::vector<Face *> faces);
            int getId() const;
            int getType() const;
            std::vector<Node *> getNodes() const;
            std::vector<Face *> getFaces() const;
            double getArea() const;
            std::vector<double> getCenter() const;
            std::vector<Cell *> getNeighbors() const;

            ~Cell() {}
        };

        std::vector<Node*> nodesInGrid;
        std::vector<Face*> facesInGrid;
        std::vector<Cell*> cellsInGrid;

        Grid(const Link& link);
        ~Grid() {}
    };

}

// Since Grid is a template class, all implementations must be visible to this Grid.h file.
// All *.hpp files below are mere extensions of the current header file.
#include "Node.hpp"
#include "Face.hpp"
#include "Cell.hpp"
#include "Grid.hpp"