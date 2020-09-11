/**
 * test.cpp : example driver program for variable types testing.
 * 
 * (please make a local copy of this file called local_test.cpp
 *  and add to .gitignore for actual testing)
 * 
 * @author
 *   Xiasu Yang <xiasu.yang@sorbonne-universite.fr>
 */

/*------------------------------------------------------------------*\
    Dependencies
\*------------------------------------------------------------------*/
#include "xyfd/LaminarV.h"
#include "xyfd/TurbulentV.h"
#include <iostream>

/*------------------------------------------------------------------*\
    Aliases
\*------------------------------------------------------------------*/
using std::cout;
using std::endl;
using namespace xyfd;

int main()
{
    TurbulentV var1(1., 1., 1., 1., {1., 1.}, {1., 1., 1., 1.}, 1.);
    TurbulentV var2(1., 1., 1., 1., {1., 1.}, {1., 1., 1., 1.}, 2.);

    if (var1 != var2) var1 += var2;

    cout << var1 << endl;

    return 0;
}
