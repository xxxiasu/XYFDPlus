EXE = main
OBJS = local_main.o \
       xyfd/Link.o \
	   xyfd/LaminarV.o \
	   xyfd/TurbulentV.o \
	   xyfd/Node.o \
	   xyfd/Face.o \
	   xyfd/Cell.o \
	   xyfd/Grid.o
CLEAN_RM =

include generic.mk