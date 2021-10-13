/**
 * Grid.h : xyfd class for representing a 2D unstructured grid.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#pragma once

/*------------------------------------------------------------------*\
    Dependencies
\*------------------------------------------------------------------*/
#include "Link.h"
#include "PCurve.h"
#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <unordered_map>

/*------------------------------------------------------------------*\
    Aliases
\*------------------------------------------------------------------*/
using StdArray2d = std::array<double, 2>;
using IntStrMap = std::unordered_map<int, std::string>;

namespace xyfd
{
    /*------------------------------------------------------------------*\
        Class declaration : xyfd::Grid
    \*------------------------------------------------------------------*/
    //-Grid is declared as a template class since it contains
    // inner class Cell which has a generic member var
    template <typename T>
    class Grid
    {
    private:
        //-Private member function :
        // Setting up nodesInGrid with coordinates in link
        //
        void _setNodesInGrid(const Link &link);

        //-Private member function :
        // Setting up facesInGrid and cellsInGrid,
        // identifying boundary faces
        //
        void _setFacesCellsInGrid(const Link &link);

    public:

        /*------------------------------------------------------------------*\
            Class declaration : xyfd::Grid::Node
        \*------------------------------------------------------------------*/
        class Node
        {
            friend class Grid;

        private:
            int id_;

            //-2D Cartesian coordinates of Node
            // using fixed-size std::array<double,2>
            StdArray2d x_;

        public:
            //-Custom constructor :
            // based on Node ID and 2D coordinates
            //
            Node(
                int id,
                StdArray2d x);

            int getId() const;

            StdArray2d getX() const;

            //-Public member function :
            // return Euclidean distance to a target Node
            //
            double getDistanceTo(const Node &other) const;

            //-Destructor
            //
            ~Node();
        };
        //-Forward declaration of Cell class
        // used in Face class
        class Cell;

        /*------------------------------------------------------------------*\
            Class declaration : xyfd::Grid::Face
        \*------------------------------------------------------------------*/
        class Face
        {
            friend class Grid;

        private:
            int id_;

            //-integer tag of boundary condition :
            // 0 : interior face; (default)
            // 1 : Dirichlet boundary face;
            // 2 : Neumann boundary face;
            // (to be continued)
            int boundary_;

            //-Head Node pointer to object in Grid::nodesInGrid
            Node *head_;

            //-Tail Node pointer to object in Grid::nodesInGrid
            Node *tail_;

            //-Master cell pointer to object in Grid::cellsInGrid
            Cell *master_;

            //-Tool cell pointer to object in Grid::cellsInGrid
            Cell *tool_;

            //-Associated parametric curve
            PCurve curve_;

            //-Euclidean distance between head and tail Nodes
            double length_;

            //-Average of head and tail Nodes
            StdArray2d center_;

            //-Unit face normal vector pointing from master to tool
            StdArray2d normal_;

            void _setLength();
            void _setCenter();
            void _setNormal();

        public:
            //-Custom constructor :
            // based on Face ID, head Node pointer, tail Node pointer
            //
            Face(
                int id,
                Node *head,
                Node *tail);

            //-Custom constructor :
            // based on Face ID, head Node pointer, tail Node pointer
            // master Cell pointer, tool Cell pointer
            //
            Face(
                int id,
                Node *head,
                Node *tail,
                Cell *master,
                Cell *tool,
                PCurve curve);

            int getId() const;
            int getBoundary() const;
            Node *getHead() const;
            Node *getTail() const;
            Cell *getMaster() const;
            Cell *getTool() const;
            PCurve getCurve() const;
            double getLength() const;
            StdArray2d getCenter() const;
            StdArray2d getNormal() const;

            //-Compute line integral of R2ToRFunc
            // call lineInt method of PCurve class
            //
            double lineInt(int order, R2ToRFunc func) const;

            //-Destructor
            //
            ~Face();
        };

        /*------------------------------------------------------------------*\
            Class declaration : xyfd::Grid::Cell
        \*------------------------------------------------------------------*/
        class Cell
        {
            friend class Grid;

        private:
            int id_;

            //-Defined by the number of Nodes, ex. triangle has type_ 3
            int type_;

            //-Vector of Node pointers to constituent Nodes in Grid::nodesInGrid
            std::vector<Node *> nodes_;

            //-Vector of Face pointers to constituent Faces in Grid::facesInGrid
            std::vector<Face *> faces_;

            //-Vector of Face pointers to constituent boundary Faces (if any) in Grid::facesInGrid
            std::vector<Face *> boundaryFaces_;

            //-Vector of Cell pointers to face-neighboring Cells in Grid::cellsInGrid
            std::vector<Cell *> neighbors_;

            //-Surface area
            double area_;

            //-Average of all constituent Nodes
            StdArray2d center_;

            void _setType();
            //-Compute area with Shoelace method
            void _setArea();
            void _setCenter();
            void _setBoundaryFaces();
            void _setNeighbors();

        public:
            //-Generic class member :
            // cell-averaged variable which can take various types
            // ex. LaminarV, TurbulentV, or c++ built-in types
            T var;

            //-Custom constructor :
            // based on Cell ID, vector of constituent Node pointers,
            // vector of constituent Face pointers
            //
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

            //-Destructor
            //
            ~Cell();
        };

        //
        //-Every object created during Grid manipulation is either
        // a pointer or a reference to element(s) of the 3 following members :
        // nodesInGrid, facesInGrid, cellsInGrid 
        //----------------------------------------------------------v
        //

        //-The only container of Node objects in Grid
        // deque used to avoid address shuffling
        std::deque<Node> nodesInGrid;

        //-The only container of Face objects in Grid
        std::deque<Face> facesInGrid;

        //-The only container of Cell objects in Grid
        std::deque<Cell> cellsInGrid;

        //
        //----------------------------------------------------------^
        //

        //-Hash table for boundary conditions, ex. {1, "Dirichlet"}
        IntStrMap bcs;

        //-Vector of Face pointers pointing to objects in facesInGrid
        std::vector<Face *> boundaryFacesInGrid;

        //-Grid needs to be constructed from a Link object
        // a Link object contains geometric info of Grid
        //
        Grid(const Link &link);

        //-Destructor
        // automatically cleans up all containing deques and vecotrs
        // and calls Node, Face and Cell destructors
        // when Grid object goes out of scope
        //
        ~Grid();
    };

} // namespace xyfd

//-Since Grid is a template class, all implementations must be visible to this Grid.h file.
// All *.hpp files below are mere extensions of the current header file.
#include "Node.hpp"
#include "Face.hpp"
#include "Cell.hpp"
#include "Grid.hpp"