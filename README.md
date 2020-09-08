# XYFDPlus

## Pre-requisites :
1. g++ or clang compiler (c++1x compatible);
2. [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) for linear algebra; 
3. (Optional) [Gmsh](https://gmsh.info/#Download) to visualize .msh files.

## Build :
1. go to the project folder :
```
cd path/to/XYFDPlus/
```
2. make a copy of main.cpp, name it local_main.cpp :
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
1. using command line :
```
./main >out
```
and basic grid info will be logged in "out", note the "out" file is git-ignored.

2. when "Enter .msh file name (without extension) :" appears in the terminal,
enter a grid file name (without .msh extension).
Two Gmsh .msh files "square.msh" and "ugly.msh" are provided as examples.
