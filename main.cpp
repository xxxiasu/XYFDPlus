/**
 * main.cpp : example driver program for code testing.
 * 
 * (please make a local copy of this file called local_main.cpp
 *  and add to .gitignore for actual testing)
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

#include "xyfd/Grid.h"
#include <vector>
#include <unordered_map>
#include <cmath>
#include <memory>
#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using xyfd::Grid;
using xyfd::LaminarV;
using xyfd::Link;
using xyfd::TurbulentV;
using StdArray2d = std::array<double, 2>;
using IntVec = std::vector<int>;
using IntStrMap = std::unordered_map<int, std::string>;

int main()
{
     /* Manually constructing Link object :

     //-xOfNodes :
     StdArray2d x0 = {0., 0.};
     StdArray2d x1 = {1., 0.};
     StdArray2d x2 = {1., 1.};
     StdArray2d x3 = {0., 1.};
     std::vector<StdArray2d> xOfNodes = {x0, x1, x2, x3};

     //-nodeIdOfCells :
     IntVec c0 = {3, 0, 1};
     IntVec c1 = {1, 2, 3};
     std::vector<IntVec> nodeIdOfCells = {c0, c1};

     //-boundaryFaces :
     std::vector<StdArray3d> boundaryFaces = {{1, 0, 1}, {1, 3, 0}, {2, 1, 2}};
     IntStrMap bcs = {{1, "Dirichlet"}, {2, "Neumann"}};

     Link myLink(xOfNodes, nodeIdOfCells, boundaryFaces, bcs);
     */

     try
     {
          //-The following line doesn't go into output file if ./main>out is used
          std::cerr << "Enter .msh file name (without extension) :" << endl;

          //-Enter grid name and remove whitespaces
          std::string gridName;
          std::getline(cin, gridName);
          gridName.erase(remove(gridName.begin(), gridName.end(), ' '), gridName.end());

          //-Construct Link object from .msh file
          Link myLink(gridName);

          //-Grid object is supposed to exist only inside this scope :
          {
               // Grid<double> myGrid(myLink);
               // Grid<LaminarV> myGrid(myLink);
               Grid<TurbulentV> myGrid(myLink);

               // double myVar = 2.;
               // LaminarV myVar(1., 1., 1., 2., {1., 1.});
               TurbulentV myVar(1., 1., 1., 1., {1., 1.}, {1., 1., 1., 1.}, 2.);

               //-Print out basic Grid info :
               for (auto &cell : myGrid.cellsInGrid)
               {
                    cout << "cell Id = " << cell.getId() << " -----------------------------------" << endl;
                    //-Check if operators work fine
                    // cell.var = 1.;
                    // cell.var = {1., 1., 1., 1., {1., 1.}};
                    cell.var = {1., 1., 1., 1., {1., 1.}, {1., 1., 1., 1.}, 1.};
                    if (cell.var != myVar)
                         cell.var += myVar;

                    for (const auto &face : cell.getFaces())
                    {
                         cout << "face Id = " << face->getId()
                              << ", face center = (" << face->getCenter()[0] << ", " << face->getCenter()[1]
                              << "), normal vector = " << face->getNormal()[0] << ", " << face->getNormal()[1] << ")" << endl;
                    }
                    cout << "" << endl;
                    for (const auto &nei : cell.getNeighbors())
                    {
                         cout << "neighbor cell ID: " << nei->getId() << endl;
                    }
                    cout << "" << endl;
                    for (const auto &bFace : cell.getBoundaryFaces())
                    {
                         cout << "boundary face ID: " << bFace->getId()
                              << ", BC type is " << myGrid.bcs[bFace->getBoundary()] << endl;
                    }
                    cout << "" << endl;
                    cout << "var = " << cell.var << endl;
                    cout << "" << endl;
               }

               cout << "" << endl;
               cout << "==================== Grid statistics : =====================================================" << endl;
               cout << "Grid object contains " << myGrid.nodesInGrid.size() << " nodes;" << endl;
               cout << "                     " << myGrid.facesInGrid.size() << " faces;" << endl;
               cout << "                     " << myGrid.cellsInGrid.size() << " cells;" << endl;
               cout << "                     " << myGrid.boundaryFacesInGrid.size() << " boundary faces." << endl;
               cout << "============================================================================================" << endl;
               cout << "" << endl;
          }
     }
     //-Catch exception
     catch (const std::exception &e)
     {
          std::cerr << "Exception occured : " << e.what() << std::endl;
     }

     return 0;
}