#
# This is a generic Makefile designed to compile a sample directory of code.
# This file depends on variables having been set before calling:
#   EXE: The name of the result file
#   MAIN: Driver object file (.o) to be generated
#   SRC_DIR: Source files directory
#   OBJS: Array of objects files (.o) to be generated
#   CLEAN_RM: Optional list of additional files to delete on `make clean`
#   LIB: Static library (lib*.a) to be generated (optional)
#
# @author Wade Fagen-Ulmschneider, <waf@illinois.edu>
# @author Jeffrey Tolar
# @author Xiasu Yang (edits made for XYFDPlus project)
#


# Compiler/linker config and object/depfile directory:
CXX = g++
LD  = g++
OBJS_DIR = .objs

# Library directory:
LIBS_DIR = .libs

# Colorful text:
GREEN = \033[0;32m
NC = \033[0m # No Color

# -MMD and -MP asks clang++ to generate a .d file listing the headers used in the source code for use in the Make process.
#   -MMD: "Write a depfile containing user headers"
#   -MP : "Create phony target for each dependency (other than main file)"
#   (https://clang.llvm.org/docs/ClangCommandLineReference.html)
DEPFILE_FLAGS = -MMD -MP

# Provide lots of helpful warning/errors:
# (Switching from clang++ to g++ caused some trouble here. Not all flags are identically between the compilers.)
#WARNINGS_AS_ERRORS = -Werror # Un-commenting this line makes compilation much more strict.
GCC_EXCLUSIVE_WARNING_OPTIONS =  # -Wno-unused-but-set-variable
CLANG_EXCLUSIVE_WARNING_OPTIONS =  # -Wno-unused-parameter -Wno-unused-variable
ifeq ($(CXX),g++)
EXCLUSIVE_WARNING_OPTIONS = $(GCC_EXCLUSIVE_WARNING_OPTIONS)
else
EXCLUSIVE_WARNING_OPTIONS = $(CLANG_EXCLUSIVE_WARNING_OPTIONS)
endif
# ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer # for debugging, if supported on the OS
WARNINGS = -pedantic -Wall $(WARNINGS_AS_ERRORS) -Wfatal-errors -Wextra $(EXCLUSIVE_WARNING_OPTIONS)

# Flags for compile:
CXXFLAGS += -std=c++17 -O0 $(WARNINGS) $(DEPFILE_FLAGS) -g -c $(ASANFLAGS)

# Flags for linking:
LDFLAGS += -std=c++17 $(ASANFLAGS)

# Rule for `all` (first/default rule):
all: $(EXE) $(T_EXE)

# Rule for linking the final executable:
# - $(EXE) depends on all object files in $(OBJS)
# - ifndef LIB : `patsubst` function adds the directory name $(OBJS_DIR) before every object file
# - ifdef  LIB : $(EXE) depends on the static library lib$(LIB).a
ifdef LIB
$(EXE): $(LIBS_DIR)/$(LIB)
	@echo
	@echo Linking executable $(EXE) against static library $(LIBS_DIR)/$(LIB) ...
	$(LD) $(LDFLAGS) -o $@ $(OBJS_DIR)/$(MAIN) -L$(LIBS_DIR) $(patsubst lib%.a, -l%, $(LIB))
	@echo $(EXE) executable linked with success !
	@echo
	@echo "$(GREEN)============================== $(EXE) SUCCESSFULLY BUILT ==============================$(NC)"
	@echo
	@echo
else
$(EXE): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	@echo
	@echo Linking executable $(EXE) ...
	$(LD) $^ $(LDFLAGS) -o $@
	@echo $(EXE) executable linked with success !
	@echo
	@echo "$(GREEN)============================== $(EXE) SUCCESSFULLY BUILT ==============================$(NC)"
	@echo
	@echo
endif

# Same rule for other executables if multiple present:
ifdef T_LIB
$(T_EXE): $(LIBS_DIR)/$(T_LIB)
	@echo
	@echo Linking executable $(T_EXE) against static library $(LIBS_DIR)/$(T_LIB) ...
	$(LD) $(LDFLAGS) -o $@ $(OBJS_DIR)/$(T_MAIN) -L$(LIBS_DIR) $(patsubst lib%.a, -l%, $(T_LIB))
	@echo $(T_EXE) executable linked with success !
	@echo
	@echo "$(GREEN)============================== $(T_EXE) SUCCESSFULLY BUILT ==============================$(NC)"
	@echo
	@echo
else
$(T_EXE): $(patsubst %.o, $(OBJS_DIR)/%.o, $(T_OBJS))
	@echo
	@echo Linking executable $(T_EXE) ...
	$(LD) $^ $(LDFLAGS) -o $@
	@echo $(T_EXE) executable linked with success !
	@echo
	@echo "$(GREEN)============================== $(T_EXE) SUCCESSFULLY BUILT ==============================$(NC)"
	@echo
	@echo
endif

# Ensure .objs/ exists:
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/$(SRC_DIR)
	@mkdir -p $(OBJS_DIR)/$(T_SRC_DIR)

# Ensure .libs/ exists if any LIB variable is defined:
ifdef LIB
$(LIBS_DIR):
	@mkdir -p $(LIBS_DIR)
else ifdef T_LIB
$(LIBS_DIR):
	@mkdir -p $(LIBS_DIR)
endif

# Rules for compiling source code.
# - Every object file is required by $(EXE)
# - Generates the rule requiring the .cpp file of the same name
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Rule for building static library lib$(SRC_DIR).a in $(LIBS_DIR) folder.
# - Every object file in $(SRC_DIR)/ folder required by $(EXE)
# - make a Headers folder containing all header files in $(SRC_DIR)
ifdef LIB
$(LIBS_DIR)/$(LIB): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS)) | $(LIBS_DIR)
	@echo
	@echo Packing static library $(LIBS_DIR)/$(LIB) ...
	ar rcs $@ $(patsubst %.o, $(OBJS_DIR)/%.o, $(filter $(SRC_DIR)/%, $(OBJS)))
	@echo $(LIBS_DIR)/$(LIB) library packed with success !
	@echo
endif

# Same rule for other executables if multiple present:
ifdef T_LIB
$(LIBS_DIR)/$(T_LIB): $(patsubst %.o, $(OBJS_DIR)/%.o, $(T_OBJS)) | $(LIBS_DIR)
	@echo
	@echo Packing static library $(LIBS_DIR)/$(T_LIB) ...
	ar rcs $@ $(patsubst %.o, $(OBJS_DIR)/%.o, $(filter $(T_SRC_DIR)/%, $(T_OBJS)))
	@echo $(LIBS_DIR)/$(T_LIB) library packed with success !
	@echo
endif

headers:
	@mkdir -p $(LIBS_DIR)/Headers
	@cp $(SRC_DIR)/*.h* $(LIBS_DIR)/Headers
	@echo $(LIBS_DIR)/Headers/ folder created, to be exported with the static library in $(LIBS_DIR)


# Additional dependencies for object files are included in the clang++
# generated .d files (from $(DEPFILE_FLAGS)):
-include $(OBJS_DIR)/*.d
-include $(OBJS_DIR)/$(SRC_DIR)/*.d
-include $(OBJS_DIR)/$(T_SRC_DIR)/*.d


# Standard C++ Makefile rules:
clean:
	rm -rf $(EXE) $(T_EXE) $(OBJS_DIR) $(LIBS_DIR) $(CLEAN_RM) *.o *.d *.a

tidy: clean
	rm -rf doc

.PHONY: all tidy clean
