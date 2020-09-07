/**
 * Grid.h : xyfd class for representing a 2D unstructured grid.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#pragma once

#include "Link.h"
#include "LaminarV.h"
#include "TurbulentV.h"
#include <vector>
#include <array>
#include <deque>
#include <unordered_map>

using StdArray2d = std::array<double, 2>;
using IntStrMap  = std::unordered_map<int, std::string>;

namespace xyfd
{
    template <typename T>
    class Grid
    {
    private:
        void _setNodesInGrid(const Link &link);
        void _setFacesCellsInGrid(const Link &link);

    public:
        class Node
        {
            friend class Grid;

        private:
            int id_;
            StdArray2d x_;

        public:
            Node(
                int id,
                StdArray2d x);

            int getId() const;
            StdArray2d getX() const;
            double getDistanceTo(const Node &other) const;

            ~Node();
        };
        class Cell; // forward declaration
        class Face
        {
            friend class Grid;

        private:
            int id_;
            int boundary_; // 0 : interior face; 1 : Dirichlet face; 2 : Neumann face
            Node *head_;
            Node *tail_;
            Cell *master_;
            Cell *tool_;
            double length_;
            StdArray2d center_;
            StdArray2d normal_;

            void _setLength();
            void _setCenter();
            void _setNormal();

        public:
            Face(
                int id,
                Node *head,
                Node *tail);

            Face(
                int id,
                Node *head,
                Node *tail,
                Cell *master,
                Cell *tool);

            int getId() const;
            int getBoundary() const;
            Node *getHead() const;
            Node *getTail() const;
            Cell *getMaster() const;
            Cell *getTool() const;
            double getLength() const;
            StdArray2d getCenter() const;
            StdArray2d getNormal() const;

            ~Face();
        };
        class Cell
        {
            friend class Grid;

        private:
            int id_;
            int type_;
            std::vector<Node *> nodes_;
            std::vector<Face *> faces_;
            std::vector<Face *> boundaryFaces_;
            std::vector<Cell *> neighbors_;
            double area_;
            StdArray2d center_;

            void _setType();
            void _setArea();
            void _setCenter();
            void _setBoundaryFaces();
            void _setNeighbors();

        public:
            T var;
            Cell(
                int id,
                std::vector<Node *> nodes,
                std::vector<Face *> faces);

            int getId() const;
            int getType() const;
            std::vector<Node *> getNodes() const;
            std::vector<Face *> getFaces() const;
            std::vector<Face *> getBoundaryFaces() const;
            double getArea() const;
            StdArray2d getCenter() const;
            std::vector<Cell *> getNeighbors() const;

            ~Cell();
        };

        std::deque<Node> nodesInGrid;
        std::deque<Face> facesInGrid;
        std::deque<Cell> cellsInGrid;

        IntStrMap bcs;
        std::vector<Face *> boundaryFacesInGrid;

        Grid(const Link &link);
        ~Grid();
    };

} // namespace xyfd

// Since Grid is a template class, all implementations must be visible to this Grid.h file.
// All *.hpp files below are mere extensions of the current header file.
#include "Node.hpp"
#include "Face.hpp"
#include "Cell.hpp"
#include "Grid.hpp"