/**
 * Link.cpp : xyfd class for representing node coordinates and node-cell linking.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#include "Link.h"
#include <vector>

using std::vector;

namespace xyfd {
    Link::Link(vector<vector<double>> xOfNodes, vector<vector<int>> nodeIdOfCells) {
        xOfNodes_ = xOfNodes;
        nodeIdOfCells_ = nodeIdOfCells;
    }

    vector<vector<double>> Link::getXOfNodes() const {
        return xOfNodes_;
    }

    vector<vector<int>> Link::getNodeIdOfCells() const {
        return nodeIdOfCells_;
    }
} // namespace xyfd