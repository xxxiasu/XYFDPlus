/**
 * Link.h : xyfd class for representing node coordinates and node-cell linking.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#pragma once

#include <vector>

using std::vector;

namespace xyfd {
    class Link {
    private:
        vector<vector<double>> xOfNodes_;
        vector<vector<int>> nodeIdOfCells_;

    public:
        Link(vector<vector<double>> xOfNodes, vector<vector<int>> nodeIdOfCells);
        vector<vector<double>> getXOfNodes() const;
        vector<vector<int>> getNodeIdOfCells() const;
        ~Link() {}
    };
} // namespace xyfd