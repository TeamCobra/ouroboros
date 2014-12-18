include ../../vars.mk

INCLUDE+=-isystem ${GTEST_DIR}/include -I${GTEST_DIR}

CFLAGS=${CORE_FLAGS} -std=c99
CXXFLAGS=${CORE_FLAGS} -std=c++11 ${INCLUDE} -ggdb

LDFLAGS=-lpthread

.PHONY = all clean test test-prep

OBJECT_FILES= ${OBJ_DIR}/server.o ${OBJ_DIR}/mongoose.o ${OBJ_DIR}/rest.o ${OBJ_DIR}/frozen.o ${OBJ_DIR}/slre.o ${OBJ_DIR}/base.o ${OBJ_DIR}/test-data_store.o ${OBJ_DIR}/test-rest.o ${OBJ_DIR}/misc.o

all: test-rest test-data_store
	./test-rest
	./test-data_store

${OBJ_DIR}/gtest.o: ${GTEST_DIR}/src/gtest-all.cc
	g++ ${CXXFLAGS} -pthread -c $^ -o $@

${OBJ_DIR}/libgtest.a: ${OBJ_DIR}/gtest.o
	ar -rv $@ $^

test-rest: ${OBJ_DIR}/test-rest.o ${OBJ_DIR}/slre.o ${OBJ_DIR}/rest.o ${OBJ_DIR}/libgtest.a
	${CXX} -pthread ${LDFLAGS} $^ -o $@

test-data_store: ${OBJ_DIR}/test-data_store.o ${OBJ_DIR}/base.o ${OBJ_DIR}/libgtest.a ${OBJ_DIR}/misc.o
	${CXX} -pthread ${LDFLAGS} $^ -o $@

${OBJ_DIR}/test-rest.o: test-rest.cpp

${OBJ_DIR}/test-data_store.o: test-data_store.cpp

${OBJ_DIR}/server.o:
	make -C ${SRC_DIR}/server ${OBJ_DIR}/server.o

${OBJ_DIR}/rest.o: ${OBJ_DIR}/slre.o
	make -C ${SRC_DIR}/server ${OBJ_DIR}/rest.o

${OBJ_DIR}/slre.o:
	make -C ${SRC_DIR}/server ${OBJ_DIR}/slre.o

${OBJ_DIR}/base.o:
	make -C ${SRC_DIR}/data ${OBJ_DIR}/base.o

${OBJ_DIR}/misc.o:
	make -C ${SRC_DIR}/data ${OBJ_DIR}/misc.o

clean:
	rm -rf test-rest ${OBJ_DIR}/gtest.o ${OBJ_DIR}/libgtest.a
	rm -rf ${OBJECT_FILES}
