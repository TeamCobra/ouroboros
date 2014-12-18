include ../../vars.mk

CFLAGS=${CORE_FLAGS} -std=c99
CXXFLAGS=${CORE_FLAGS} -std=c++11

.PHONY: all clean

OBJECT_FILES = ${OBJ_DIR}/base.o ${OBJ_DIR}/misc.o ${OBJ_DIR}/JSON.o ${OBJ_DIR}/base_integer.o ${OBJ_DIR}/base_string.o

all: ${OBJ_DIR}/base.o ${OBJ_DIR}/misc.o ${OBJ_DIR}/JSON.o ${OBJ_DIR}/base_integer.o ${OBJ_DIR}/base_string.o

clean:
	rm -rf ${OBJECT_FILES}

${OBJ_DIR}/base.o: base.cpp base.hpp base.ipp

${OBJ_DIR}/misc.o: misc.cpp misc.h

${OBJ_DIR}/JSON.o: JSON.cpp JSON.h

${OBJ_DIR}/base_integer.o: base_integer.cpp base_integer.h

${OBJ_DIR}/base_string.o:base_string.cpp base_string.h
