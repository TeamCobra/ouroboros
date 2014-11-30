include ../../vars.mk

CFLAGS=${CORE_FLAGS} -std=c99
CXXFLAGS=${CORE_FLAGS} -std=c++11

LDFLAGS=-lpthread

.PHONY=all clean

OBJECT_FILES= ${OBJ_DIR}/server.o ${OBJ_DIR}/mongoose.o ${OBJ_DIR}/rest.o ${OBJ_DIR}/frozen.o ${OBJ_DIR}/slre.o

all: $(BUILD_DIR)/Server

${BUILD_DIR}/Server: ${OBJ_DIR}/server.o ${OBJ_DIR}/mongoose.o ${OBJ_DIR}/slre.o ${OBJ_DIR}/rest.o
	${CXX} ${LDFLAGS} $^ -o $@

${OBJ_DIR}/mongoose.o: mongoose.c mongoose.h

${OBJ_DIR}/rest.o: rest.cpp rest.hpp

${OBJ_DIR}/server.o: server.cpp mongoose.h frozen.h slre.h

${OBJ_DIR}/frozen.o: frozen.c frozen.h

${OBJ_DIR}/slre.o: slre.c slre.h

${OBJ_DIR}/base.o: base.cpp base.hpp

slre.c:
	cp ${SLRE_DIR}/$@ ./

slre.h:
	cp ${SLRE_DIR}/$@ ./

frozen.c:
	cp ${FROZEN_DIR}/$@ ./

frozen.h:
	cp ${FROZEN_DIR}/$@ ./

mongoose.c:
	cp ${MONGOOSE_DIR}/$@ ./

mongoose.h:
	cp ${MONGOOSE_DIR}/$@ ./

clean:
	rm -rf server.o Server frozen.c frozen.h mongoose.h mongoose.c slre.h slre.c ${OBJECT_FILES}
