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

//-More comments in Grid.h
//
namespace xyfd
{
    template <typename T>
    void Grid<T>::_setNodesInGrid(const Link &link)
    {
        nodesInGrid = {};
        int nNodes = (int)link.getXOfNodes().size();
        for (int i = 0; i < nNodes; i++)
        {
            //-deque.emplace_back() avoids address shuffling
            // used for containers with actual objects
            nodesInGrid.emplace_back(i, link.getXOfNodes()[i]);
        }
    }

    template <typename T>
    void Grid<T>::_setFacesCellsInGrid(const Link &link)
    {
        facesInGrid = {};
        cellsInGrid = {};
        boundaryFacesInGrid = {};

        int faceCount = 0;
        int nNodes = (int)link.getXOfNodes().size();
        int nCells = (int)link.getNodeIdOfCells().size();

        //-initialize a nNodes by nNodes lookup table
        // to check face repetition in O(1) time
        std::vector<std::vector<Face *>> visitedFaces(
            nNodes,
            std::vector<Face *>(nNodes, nullptr));

        for (int i = 0; i < nCells; i++)
        {
            int nNodesOfCell = (int)link.getNodeIdOfCells()[i].size();

            //-Declaring vector of Node pointers to constituent Nodes
            // note : doesn't need to use deque since we don't care 
            // about address changes for pointers
            std::vector<Node *> nodesInCell;

            //-Declaring vector of Face pointers to constituent Faces
            std::vector<Face *> facesInCell = {};

            for (int j = 0; j < nNodesOfCell; j++)
            {
                int jId = link.getNodeIdOfCells()[i][j];
                nodesInCell.push_back(&nodesInGrid[jId]);
            }

            cellsInGrid.emplace_back(i, nodesInCell, facesInCell);
            //-Declaring a reference to the most recently emplaced Cell object
            Cell &cell = cellsInGrid.back();

            for (int j = 0; j < nNodesOfCell; j++)
            {
                int k = (j + 1) % nNodesOfCell;
                int jId = nodesInCell[j]->id_;
                int kId = nodesInCell[k]->id_;

                Node *nodeJ = &nodesInGrid[jId];
                Node *nodeK = &nodesInGrid[kId];

                //-IF -> Face object not yet constructed :
                if (!visitedFaces[jId][kId] && !visitedFaces[kId][jId])
                {
                    facesInGrid.emplace_back(faceCount, nodeJ, nodeK);
                    //-Declaring a reference to the most recently emplaced Cell object
                    Face &face = facesInGrid.back();

                    //-Set the current &cell as master cell of face
                    face.master_ = &cell;

                    //-Set face as a constituent Face of &cell
                    cell.faces_.push_back(&face);

                    //-visitedFaces must be symmetric
                    // whenever we update (jId,kId) we also
                    // update (kId, jId)
                    visitedFaces[jId][kId] = &face;
                    visitedFaces[kId][jId] = &face;

                    faceCount++;
                }
                //-ELSE -> Face object already been constructed :
                else
                {
                    //-Set the current &cell as tool cell of face
                    visitedFaces[jId][kId]->tool_ = &cell;

                    //-Set face as a constituent Face of &cell
                    cell.faces_.push_back(visitedFaces[jId][kId]);
                }
            }
        }

        //-Identifying boundary faces
        // &face is a line (std::array<int,3>) in Link.boundaryFaces
        for (const auto &face : link.getBoundaryFaces())
        {
            int jId = face[1];
            int kId = face[2];

            //-At this point, visitedFaces is fully defined
            if (visitedFaces[jId][kId] || visitedFaces[kId][jId])
            {
                visitedFaces[jId][kId]->boundary_ = face[0];
                boundaryFacesInGrid.push_back(visitedFaces[jId][kId]);
            }
        }

        //-Cell.boundaryFaces and Cell.neighbors cannot be set
        // before all connections established
        for (auto &cell : cellsInGrid)
        {
            cell._setBoundaryFaces();
            cell._setNeighbors();
        }

        //-Face normals cannot be set before
        // every Face knows both its master and tool
        for (auto &face : facesInGrid)
        {
            face._setNormal();
        }
    }

    template <typename T>
    Grid<T>::Grid(const Link &link)
        : bcs(link.getBcs())
    {
        _setNodesInGrid(link);
        _setFacesCellsInGrid(link);
    }

    template <typename T>
    Grid<T>::~Grid()
    {
        std::cout << "" << std::endl;
        std::cout << "Deleting Grid Object ..." << std::endl;
    }
} // namespace xyfd