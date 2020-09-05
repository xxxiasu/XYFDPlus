/**
 * Grid.hpp : xyfd class for representing a 2D unstructured grid.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#include "Grid.h"
#include <iostream>
#include <vector>
#include <cmath>

namespace xyfd {
    template<typename T>
    void Grid<T>::_setNodesInGrid(const Link& link) {
        nodesInGrid = {};
        int nNodes = (int)link.getXOfNodes().size();
        for (int i = 0; i < nNodes; i++) {
            nodesInGrid.emplace_back(i, link.getXOfNodes()[i]);
        }
    }

    template<typename T>
    void Grid<T>::_setFacesCellsInGrid(const Link& link) {
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
            std::vector<Face*> facesInCell = {};

            for (int j = 0; j < nNodesOfCell; j++) {
                int jId = link.getNodeIdOfCells()[i][j];
                nodesInCell.push_back(&nodesInGrid[jId]);
            }
            cellsInGrid.emplace_back(i, nodesInCell, facesInCell);
            Cell& cell = cellsInGrid.back();

            for (int j = 0; j < nNodesOfCell; j++) {
                int k   = (j+1)%nNodesOfCell;
                int jId = nodesInCell[j]->id_;
                int kId = nodesInCell[k]->id_;
                Node* nodeJ   = &nodesInGrid[jId];
                Node* nodeJp1 = &nodesInGrid[kId];
                if (!visitedFaces[jId][kId] && !visitedFaces[kId][jId]) {
                    facesInGrid.emplace_back(faceCount, nodeJ, nodeJp1);
                    Face& face = facesInGrid.back();
                    face.master_ = &cell;
                    cell.faces_.push_back(&face);
                    visitedFaces[jId][kId] = &face;
                    visitedFaces[kId][jId] = &face;
                    faceCount++;
                }
                else {
                    visitedFaces[jId][kId]->tool_ = &cell;
                    cell.faces_.push_back(visitedFaces[jId][kId]);
                }
            }
        }

        for (auto& cell : cellsInGrid) {
            cell._setNeighbors();
        }

        for (auto& face : facesInGrid) {
            face._setNormal();
        }
    }

    template<typename T>
    Grid<T>::Grid(const Link& link) {
        _setNodesInGrid(link);
        _setFacesCellsInGrid(link);
    }

    template<typename T>
    Grid<T>::~Grid() {
        std::cout << "Deleting Grid Object ..." << std::endl;
    }
}