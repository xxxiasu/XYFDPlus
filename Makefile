# Specify the name of executable
EXE  = main
# Specify the name of driver object file (recommended : local_main.o)
MAIN = local_main.o
# Specify the folder where ALL depending source files is contained
# All source files of xyfd namespace are in folder xyfd/
SRC_DIR = xyfd
# List of all object files, append after $(MAIN)
OBJS = $(MAIN) $(patsubst %.cpp, %.o, $(wildcard $(SRC_DIR)/*.cpp))
# Specify the name of static library to be generated if needed (recommended : libxyfd.a)
LIB  =

# Add multiple executables below if needed, but also change make/generic.mk if you do
# This test example uses only LaminarV and TurbulentV types
T_EXE  = test
T_MAIN = local_test.o
T_SRC_DIR = xyfd
T_OBJS = $(T_MAIN) $(patsubst %.cpp, %.o, $(wildcard $(T_SRC_DIR)/*V.cpp))
T_LIB  =

# Additional files to clean up
CLEAN_RM = *out

include make/generic.mk
