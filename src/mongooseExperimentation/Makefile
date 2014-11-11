CFLAGS=-Wall -Wextra -Wpedantic -ggdb -std=c99
LDFLAGS=-lpthread
LIB_FOLDER=../../lib
MONGOOSE_LIB=${LIB_FOLDER}/mongoose/
FROZEN_LIB=${LIB_FOLDER}/frozen/
SLRE_LIB=${LIB_FOLDER}/slre/

.PHONY = all clean

all: Server

Server: server.o mongoose.o slre.o REST.o
	${CC} ${LDFLAGS} $^ -o $@

mongoose.o: mongoose.c mongoose.h

REST.o: REST.c REST.h

server.o: server.c mongoose.h frozen.h slre.h

frozen.o: frozen.c frozen.h

slre.o: slre.c slre.h

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
	rm -rf server.o Server mongoose.o frozen.c frozen.h mongoose.h mongoose.c slre.o slre.h slre.c frozen.o 
