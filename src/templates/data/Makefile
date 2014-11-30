include ../../../vars.mk

CFLAGS=${CORE_FLAGS} -std=c99
CXXFLAGS=${CORE_FLAGS} -std=c++11

.PHONY: all clean

OBJECT_FILES = ${OBJ_DIR}/faux_dstore.o ${OBJ_DIR}/base.o

all: ${OBJ_DIR}/base.o ${OBJ_DIR}/faux_dstore.o

clean:
	rm -rf ${OBJECT_FILES}

${OBJ_DIR}/base.o: base.cpp base.hpp base.ipp

${OBJ_DIR}/faux_dstore.o: faux_dstore.cpp faux_dstore.hpp base.hpp base.ipp
