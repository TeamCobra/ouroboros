mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
CURRENT_DIR := $(patsubst %/,%,$(dir $(mkfile_path)))

export LIB_DIR=${CURRENT_DIR}/lib
export SRC_DIR=${CURRENT_DIR}/src
export BUILD_DIR=${CURRENT_DIR}/build
export OBJ_DIR=${BUILD_DIR}/obj

export SLRE_DIR=${LIB_DIR}/slre
export FROZEN_DIR=${LIB_DIR}/frozen
export MONGOOSE_DIR=${LIB_DIR}/mongoose

export CORE_FLAGS=-Wall -Wextra -Wpedantic -ggdb

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
    
$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
