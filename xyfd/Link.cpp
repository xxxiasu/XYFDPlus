/**
 * Link.cpp : xyfd class for representing node coordinates and node-cell linking.
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

/*------------------------------------------------------------------*\
    Dependencies
\*------------------------------------------------------------------*/
#include "Link.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <unordered_map>

/*------------------------------------------------------------------*\
    Aliases
\*------------------------------------------------------------------*/
using std::string;
using std::vector;
using IntStrMap = std::unordered_map<int, string>;
using StdArray2d = std::array<double, 2>;
using StdArray3i = std::array<int, 3>;

//-More comments in Link.h
//
namespace xyfd
{
    Link::Link(
        vector<StdArray2d> xOfNodes,
        vector<vector<int>> nodeIdOfCells,
        vector<StdArray3i> boundaryFaces,
        IntStrMap bcs)
        : xOfNodes_(xOfNodes),
          nodeIdOfCells_(nodeIdOfCells),
          boundaryFaces_(boundaryFaces),
          bcs_(bcs) {}

    Link::Link(string gridFileName)
    {
        int maxIgnore = 10000;
        string loc = "grids/"; // grid file location
        string ext = ".msh";   // grid file extension
        string fullName;

        fullName += loc;
        fullName += gridFileName;
        fullName += ext;

        std::ifstream gridFile;
        gridFile.open(fullName);

        if (gridFile.is_open())
        {
            //-Skip 4 header lines
            for (int i = 0; i < 4; i++)
                gridFile.ignore(maxIgnore, '\n');

            //-Extract the number of boundary condition types
            int nBcs;
            gridFile >> nBcs >> std::ws;

            //-Store BC names in a hash table
            for (int i = 0; i < nBcs; i++)
            {
                int tag1, bcId;
                string bcName;
                gridFile >> tag1 >> bcId >> bcName;
                bcs_.insert({bcId, bcName});
            }

            //-Skip 2 next lines
            for (int i = 0; i < 3; i++)
                gridFile.ignore(maxIgnore, '\n');

            //-Extract the number of Nodes
            int nNodes;
            gridFile >> nNodes >> std::ws;

            //-Store xOfNodes
            for (int i = 0; i < nNodes; i++)
            {
                int id;
                double x, y, z;
                gridFile >> id >> x >> y >> z;
                xOfNodes_.push_back({x, y});
            }

            //-Skip 2 next lines
            for (int i = 0; i < 3; i++)
                gridFile.ignore(maxIgnore, '\n');

            //-Extract number of elements (including boundary faces)
            int nElems;
            gridFile >> nElems >> std::ws;

            //-Store boundaryFaces, nodeIdOfCells
            for (int i = 0; i < nElems; i++)
            {
                int id, type, tag1;
                gridFile >> id >> type >> tag1;
                if (type == 1) // 1 denotes boundary line element in Gmsh notation
                {
                    int bcType, tag2, headId, tailId;
                    gridFile >> bcType >> tag2 >> headId >> tailId;
                    boundaryFaces_.push_back({bcType, headId - 1, tailId - 1});
                }
                else if (type == 2) // 2 denotes triangular cell element in Gmsh notation
                {
                    int bcType, tag2, node1Id, node2Id, node3Id;
                    gridFile >> bcType >> tag2 >> node1Id >> node2Id >> node3Id;
                    nodeIdOfCells_.push_back({node1Id - 1, node2Id - 1, node3Id - 1});
                }
                else if (type == 3) // 3 denotes quadrilateral cell element in Gmsh notation
                {
                    int bcType, tag2, node1Id, node2Id, node3Id, node4Id;
                    gridFile >> bcType >> tag2 >> node1Id >> node2Id >> node3Id >> node4Id;
                    nodeIdOfCells_.push_back({node1Id - 1, node2Id - 1, node3Id - 1, node4Id - 1});
                }
            }
            gridFile.close();
        }
        //-Throw exception if grid file not open
        else
        {
            throw std::runtime_error("Failed to open grid file " + fullName + " !!!");
        }
    }

    vector<StdArray2d> Link::getXOfNodes() const
    {
        return xOfNodes_;
    }

    vector<vector<int>> Link::getNodeIdOfCells() const
    {
        return nodeIdOfCells_;
    }

    vector<StdArray3i> Link::getBoundaryFaces() const
    {
        return boundaryFaces_;
    }

    IntStrMap Link::getBcs() const
    {
        return bcs_;
    }
} // namespace xyfd