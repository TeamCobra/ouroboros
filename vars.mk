mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
CURRENT_DIR := $(patsubst %/,%,$(dir $(mkfile_path)))

export LIB_DIR=${CURRENT_DIR}/lib
export SRC_DIR=${CURRENT_DIR}/src
export BUILD_DIR=${CURRENT_DIR}/target
export OBJ_DIR=${BUILD_DIR}

export INCLUDE=-I. -I${SRC_DIR} -I${SRC_DIR}/templates -I${SRC_DIR}/test -I${SRC_DIR}/server -I${LIB_DIR}

export SLRE_DIR=${LIB_DIR}/slre
export FROZEN_DIR=${LIB_DIR}/frozen
export MONGOOSE_DIR=${LIB_DIR}/mongoose
export GTEST_DIR=${LIB_DIR}/googletest

export CORE_FLAGS=-Wall -Wextra -Wpedantic -ggdb

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
    
$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
