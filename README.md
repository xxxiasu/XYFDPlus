# XYFDPlus
XYFDPlus is a C++ CFD project for solving 2D compressible Navier-Stokes equations on polygonal unstructured grid.

This project contains a C++ namespace `xyfd` which allows manipulation and computation on grid.

Grids can be created manually or loaded from external grid generators like Gmsh via a
[well-formatted .msh file](https://gmsh.info/doc/texinfo/gmsh.html#MSH-file-format-version-2-_0028Legacy_0029).

@author : [Xiasu Yang](mailto:yangxiasu75@gmail.com)

## Pre-requisites :
1. g++ or clang compiler (c++1x compatible);

2. [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) for linear algebra;

3. (Optional) [Gmsh](https://gmsh.info/#Download) to visualize .msh files.

## Build :
1. go to the project folder :
```
cd path/to/XYFDPlus/
```
2. make a copy of main.cpp and name it local_main.cpp :
```
cp main.cpp local_main.cpp
```
3. build project using
  - terminal : 
  ```
  make
  ```
  - VS Code :
  ```
  Ctrl+Shift+B
  ```
4. clean-up :
```
make clean
```

## Run :
1. using the command below and basic grid info will be written in `out`, note the `out` file is git-ignored :
```
./main >out
```

2. when `Enter .msh file name (without extension) :` appears in terminal, enter a grid file name (without .msh extension).
Two Gmsh .msh files `square.msh` and `ugly.msh` are provided as examples. To check .msh file content, go to `XYFDPlus/grids/` :
```
cd path/to/XYFDPlus/grids/
vi *.msh
```
