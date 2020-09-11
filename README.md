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

2. make a copy of `main.cpp` and name it `local_main.cpp` (git-ignored) :
```
cp main.cpp local_main.cpp
```

3. make a copy of `test.cpp` and name it `local_test.cpp` (git-ignored) :
```
cp test.cpp local_test.cpp
```

4. build project using
  - make : 
  make options :
    - default : make all programs
    ```
    make
    ```
    - main : make main program
    ```
    make main
    ```
    - test : make test program or any other program you choose to put in `local_test.cpp`
    ```
    make test
    ```
    
  - VS Code :
  all build options of make exist also in VS Code. Open folder in VS Code and in the toolbar, click
  ```
  Terminal -> Run Task ...
  ```
  and select one of the tasks above to run, ex. `buildAll` task corresponds to `make`.
  
5. collect header files for external usage (with library) using
  - make :
  ```
  make headers
  ```
  - VS Code :
  ```
  Terminal -> Run Task ... -> buildHeaders
  ```
  
6. clean-up using
  - make :
  ```
  make clean
  ```
  - VS Code :
  ```
  Terminal -> Run Task ... -> buildClean
  ```


## Run :
1. run main program and basic grid info will be written in `out`, note the `out` file is git-ignored
  - command line :
  ```
  ./main >out
  ```
  - VS Code :
  ```
  Terminal -> Run Task ... -> runMain
  ```

2. when `Enter .msh file name (without extension) :` appears in terminal, enter a grid file name (without .msh extension).
Two Gmsh .msh files `square.msh` and `ugly.msh` are provided as examples. To check .msh file content, go to `XYFDPlus/grids/` :
```
cd path/to/XYFDPlus/grids/
vi *.msh
```

3. to run other tests in `local_test.cpp` :
  - command line :
  ```
  ./test
  ```
  - VS Code :
  ```
  Terminal -> Run Task ... -> runTest
  ```
