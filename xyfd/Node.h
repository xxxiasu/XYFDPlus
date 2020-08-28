/**
 * Node.h : xyfd class for representing a grid node.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#pragma once

#include <vector>

namespace xyfd {
    class Node {
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
}