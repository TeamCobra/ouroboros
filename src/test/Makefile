include ../../vars.mk

INCLUDE=-isystem ${GTEST_DIR}/include -I${GTEST_DIR} -I${SRC_DIR}/server

CFLAGS=${CORE_FLAGS} -std=c99
CXXFLAGS=${CORE_FLAGS} -std=c++11 ${INCLUDE}

LDFLAGS=-lpthread

.PHONY = all clean test test-prep

OBJECT_FILES= server.o mongoose.o rest.o frozen.o slre.o

all: test-rest
	./test-rest

${OBJ_DIR}/gtest.o: ${GTEST_DIR}/src/gtest-all.cc
	g++ ${CXXFLAGS} -pthread -c $^ -o $@

${OBJ_DIR}/libgtest.a: ${OBJ_DIR}/gtest.o
	ar -rv $@ $^

test-rest: ${OBJ_DIR}/test-rest.o ${OBJ_DIR}/slre.o ${OBJ_DIR}/rest.o ${OBJ_DIR}/libgtest.a
	${CXX} -pthread ${LDFLAGS} $^ -o $@

${OBJ_DIR}/test-rest.o: test-rest.cpp

${OBJ_DIR}/server.o:
	make -C ${SRC_DIR}/server ${OBJ_DIR}/server.o

${OBJ_DIR}/rest.o: ${OBJ_DIR}/slre.o
	make -C ${SRC_DIR}/server ${OBJ_DIR}/rest.o

${OBJ_DIR}/slre.o:
	make -C ${SRC_DIR}/server ${OBJ_DIR}/slre.o

clean:
	rm -rf test-rest ${OBJ_DIR}/gtest.o ${OBJ_DIR}/libgtest.a
	rm -rf ${OBJ_DIR}/slre.o ${OBJ_DIR}/rest.o ${OBJ_DIR}/server.o
