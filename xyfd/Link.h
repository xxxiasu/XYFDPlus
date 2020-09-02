/**
 * Link.h : xyfd class for representing node coordinates and node-cell linking.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#pragma once

#include <vector>
#include <array>

using StdArray2d = std::array<double, 2>;

using std::vector;

namespace xyfd {
    class Link {
    private:
        vector<StdArray2d> xOfNodes_;
        vector<vector<int>> nodeIdOfCells_;

    public:
        Link(vector<StdArray2d> xOfNodes, vector<vector<int>> nodeIdOfCells);
        vector<StdArray2d> getXOfNodes() const;
        vector<vector<int>> getNodeIdOfCells() const;
        ~Link() {}
    };
}