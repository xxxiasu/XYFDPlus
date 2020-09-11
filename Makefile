# specify the name of executable
EXE  = main
# specify the name of driver object file (recommended : local_main.o)
MAIN = local_main.o
# specify the folder where xyfd namespace is contained
SRC_DIR = xyfd
# list of all object files
OBJS = $(MAIN) $(patsubst %.cpp, %.o, $(wildcard $(SRC_DIR)/*.cpp))
# specify the name of static library if needed (recommended : libxyfd.a)
LIB  =

# add multiple executable if needed
T_EXE  = test
T_MAIN = local_test.o
T_SRC_DIR = xyfd
T_OBJS = $(T_MAIN) $(patsubst %.cpp, %.o, $(wildcard $(T_SRC_DIR)/*V.cpp))
T_LIB  =

# additional files to clean up
CLEAN_RM = *out

include make/generic.mk
