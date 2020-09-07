/**
 * Link.h : xyfd class for representing node coordinates and node-cell linking.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>

using std::string;
using std::vector;
using StdArray2d = std::array<double, 2>;
using StdArray3i = std::array<int, 3>;
using IntStrMap  = std::unordered_map<int, string>;

namespace xyfd
{
    class Link
    {
    private:
        vector<StdArray2d> xOfNodes_;
        vector<vector<int>> nodeIdOfCells_;
        vector<StdArray3i> boundaryFaces_;
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