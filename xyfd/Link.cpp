/**
 * Link.cpp : xyfd class for representing node coordinates and node-cell linking.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#include "Link.h"
#include <vector>
#include <array>

using std::vector;
using StdArray2d = std::array<double, 2>;

namespace xyfd {
    Link::Link(vector<StdArray2d> xOfNodes, vector<vector<int>> nodeIdOfCells) {
        xOfNodes_ = xOfNodes;
        nodeIdOfCells_ = nodeIdOfCells;
    }

    vector<StdArray2d> Link::getXOfNodes() const {
        return xOfNodes_;
    }

    vector<vector<int>> Link::getNodeIdOfCells() const {
        return nodeIdOfCells_;
    }
}