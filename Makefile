# specify the name of executable
EXE  = main
# specify the name of driver file object (recommended : local_main.o)
MAIN = local_main.o
# specify the folder where xyfd namespace is contained
SRC_DIR = xyfd
# list of all object files
OBJS = $(MAIN) $(patsubst %.cpp, %.o, $(wildcard $(SRC_DIR)/*.cpp))
# additional files to clean up
CLEAN_RM = *out
# specify the name of static library if needed (recommended : libxyfd.a)
LIB  =

include make/generic.mk
