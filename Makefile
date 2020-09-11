# Specify the name of executable
EXE  = main
# Specify the name of driver object file (recommended : local_main.o)
MAIN = local_main.o
# Specify the folder where ALL depending source files is contained
SRC_DIR = xyfd
# List of all object files, append after $(MAIN)
OBJS = $(MAIN) $(patsubst %.cpp, %.o, $(wildcard $(SRC_DIR)/*.cpp))
# Specify the name of static library if needed (recommended : libxyfd.a)
LIB  =

# Add multiple executables if needed
# This test example uses only LaminarV and TurbulentV types
T_EXE  = test
T_MAIN = local_test.o
T_SRC_DIR = xyfd
T_OBJS = $(T_MAIN) $(patsubst %.cpp, %.o, $(wildcard $(T_SRC_DIR)/*V.cpp))
T_LIB  =

# Additional files to clean up
CLEAN_RM = *out

include make/generic.mk
