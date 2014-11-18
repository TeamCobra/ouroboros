
CFLAGS=-Wall -Wextra -Wpedantic -ggdb -std=c99
CXXFLAGS=-Wall -Wextra -Wpedantic -ggdb -std=c++11

LDFLAGS=-lpthread
LIB_FOLDER=../../lib
MONGOOSE_LIB=${LIB_FOLDER}/mongoose/
FROZEN_LIB=${LIB_FOLDER}/frozen/
SLRE_LIB=${LIB_FOLDER}/slre/

.PHONY = all clean

OBJECT_FILES= server.o mongoose.o rest.o frozen.o slre.o base.o data.o

all: Server

Server: server.o mongoose.o slre.o rest.o base.o
	${CXX} ${LDFLAGS} $^ -o $@

mongoose.o: mongoose.c mongoose.h

rest.o: rest.c rest.h

server.o: server.cpp mongoose.h frozen.h slre.h

frozen.o: frozen.c frozen.h

slre.o: slre.c slre.h

base.o: base.cpp base.hpp

data.o: data.cpp data.hpp

slre.c:
	cp ${SLRE_LIB}/$@ ./

slre.h:
	cp ${SLRE_LIB}/$@ ./

frozen.c:
	cp ${FROZEN_LIB}/$@ ./

frozen.h:
	cp ${FROZEN_LIB}/$@ ./

mongoose.c:
	cp ${MONGOOSE_LIB}/$@ ./

mongoose.h:
	cp ${MONGOOSE_LIB}/$@ ./

clean:
	rm -rf server.o Server frozen.c frozen.h mongoose.h mongoose.c slre.h slre.c ${OBJECT_FILES}
