/**
 * Link.h : xyfd class for representing node coordinates and node-cell linking.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#pragma once

/*------------------------------------------------------------------*\
    Dependencies
\*------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>

/*------------------------------------------------------------------*\
    Aliases
\*------------------------------------------------------------------*/
using std::string;
using std::vector;
using StdArray2d = std::array<double, 2>;
using StdArray3i = std::array<int, 3>;
using IntStrMap = std::unordered_map<int, string>;

namespace xyfd
{
    /*------------------------------------------------------------------*\
        Class declaration : xyfd::Link
    \*------------------------------------------------------------------*/
    class Link
    {
    private:
        //-2D Cartesian coordinates of all Nodes in a Grid
        vector<StdArray2d> xOfNodes_;

        //-Node IDs of all Cells in a Grid (in (counter)clock-wise order)
        vector<vector<int>> nodeIdOfCells_;

        //-Arrays of boundary Face info :
        // {boundary condition type ID, head Node ID, tail Node ID}
        vector<StdArray3i> boundaryFaces_;

        //-Integer to String hash table to link BC type IDs to BC names
        IntStrMap bcs_;

    public:
        //-custom constructor :
        // based on manual input
        //
        Link(
            vector<StdArray2d> xOfNodes,
            vector<vector<int>> nodeIdOfCells,
            vector<StdArray3i> boundaryFaces,
            IntStrMap bcs);

        //-custom constructor :
        // based on Gmsh .msh file input
        //
        Link(string gridFileName);

        vector<StdArray2d> getXOfNodes() const;
        vector<vector<int>> getNodeIdOfCells() const;
        vector<StdArray3i> getBoundaryFaces() const;
        IntStrMap getBcs() const;
        ~Link() {}
    };
} // namespace xyfd