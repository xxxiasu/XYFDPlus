/**
 * Grid.cpp : xyfd class for representing a 2D unstructured grid.
 * (adjacency list implementation)
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#include "Grid.h"
#include <iostream>
#include <vector>
#include <cmath>

namespace xyfd {
    void Grid::_setNodesInGrid(const Link& link) {
        nodesInGrid = {};
        int nNodes = (int)link.getXOfNodes().size();
        for (int i = 0; i < nNodes; i++) {
            Node* node = new Node(i, link.getXOfNodes()[i]);
            nodesInGrid.push_back(node);
        }
    }

    void Grid::_setFacesCellsInGrid(const Link& link) {
        facesInGrid = {};
        cellsInGrid = {};
        int faceCount = 0;
        int nNodes = (int)link.getXOfNodes().size();
        int nCells = (int)link.getNodeIdOfCells().size();
        // initialize a nNodes by nNodes lookup table to check face repetition in O(1) time
        std::vector<std::vector<Face*>> visitedFaces(nNodes, std::vector<Face*>(nNodes, nullptr));

        for (int i = 0; i < nCells; i++) {
            int nNodesOfCell = (int)link.getNodeIdOfCells()[i].size();
            std::vector<Node*> nodesInCell;

            for (int j = 0; j < nNodesOfCell; j++) {
                int jId = link.getNodeIdOfCells()[i][j];
                nodesInCell.push_back(nodesInGrid[jId]);
            }
            Cell* cell = new Cell(i, nodesInCell, {});
            cellsInGrid.push_back(cell);

            for (int j = 0; j < nNodesOfCell; j++) {
                int k   = (j+1)%nNodesOfCell;
                int jId = nodesInCell[j]->id_;
                int kId = nodesInCell[k]->id_;
                Node* nodeJ   = nodesInGrid[jId];
                Node* nodeJp1 = nodesInGrid[kId];
                if (!visitedFaces[jId][kId] && !visitedFaces[kId][jId]) {
                    Face* face = new Face(faceCount, nodeJ, nodeJp1);
                    face->master_ = cell;
                    facesInGrid.push_back(face);
                    cell->faces_.push_back(face);
                    visitedFaces[jId][kId] = face;
                    visitedFaces[kId][jId] = face;
                    faceCount++;
                }
                else {
                    visitedFaces[jId][kId]->tool_ = cell;
                    cell->faces_.push_back(visitedFaces[jId][kId]);
                }
            }
        }

        for (const auto& cell : cellsInGrid) {
            cell->_setNeighbors();
        }

        for (const auto& face : facesInGrid) {
            face->_setNormal();
        }
    }

    Grid::Grid(const Link& link) {
        _setNodesInGrid(link);
        _setFacesCellsInGrid(link);
    }
}