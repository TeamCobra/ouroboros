include ../../vars.mk

INCLUDE=-isystem ${GTEST_DIR}/include -I${GTEST_DIR}

CFLAGS=${CORE_FLAGS} -std=c99
CXXFLAGS=${CORE_FLAGS} -std=c++11 ${INCLUDE}

LDFLAGS=-lpthread

.PHONY = all clean test

OBJECT_FILES= server.o mongoose.o rest.o frozen.o slre.o

all: test-all

test.o: test.cpp

${OBJ_DIR}/gtest.o: ${GTEST_DIR}/src/gtest-all.cc
	g++ ${CXXFLAGS} -pthread -c $^ -o $@

${OBJ_DIR}/libgtest.a: ${OBJ_DIR}/gtest.o
	ar -rv $@ $^

test-all: test.o ${OBJ_DIR}/libgtest.a
	${CXX} -pthread ${LDFLAGS} $^ -o $@

clean:
	rm -rf test-all ${OBJ_DIR}/gtest.o ${OBJ_DIR}/libgtest.a
