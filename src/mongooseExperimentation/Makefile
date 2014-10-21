CFLAGS=-Wall -Wextra -Wpedantic -ggdb -std=c99
LDFLAGS=-lpthread
MONGOOSE_LIB=../../lib/mongoose/

.PHONY = all clean

all: Server

Server: server.o mongoose.o
	${CC} ${LDFLAGS} $^ -o $@

mongoose.o: mongoose.c mongoose.h

server.o: server.c mongoose.h

mongoose.c:
	cp ${MONGOOSE_LIB}/$@ ./

mongoose.h:
	cp ${MONGOOSE_LIB}/$@ ./

