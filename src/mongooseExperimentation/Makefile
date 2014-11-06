CFLAGS=-Wall -Wextra -Wpedantic -ggdb -std=c99
LDFLAGS=-lpthread
LIB_FOLDER=../../lib
MONGOOSE_LIB=${LIB_FOLDER}/mongoose/
FROZEN_LIB=${LIB_FOLDER}/frozen/
LUASP_LIB=${LIB_FOLDER}/luasp/

.PHONY = all clean

all: Server

Server: server.o mongoose.o
	${CC} ${LDFLAGS} $^ -o $@

mongoose.o: mongoose.c mongoose.h

server.o: server.c mongoose.h

frozen.o: frozen.c frozen.h

lualsp.so:
	make -C ${LUASP_LIB}
	cp ${LUASP_LIB}/lualsp.so ./

frozen.c:
	cp ${FROZEN_LIB}/$@ ./

frozen.h:
	cp ${FROZEN_LIB}/$@ ./

mongoose.c:
	cp ${MONGOOSE_LIB}/$@ ./

mongoose.h:
	cp ${MONGOOSE_LIB}/$@ ./

clean:
	rm -rf server.o Server mongoose.o frozen.c frozen.h mongoose.h mongoose.c lualsp.so
