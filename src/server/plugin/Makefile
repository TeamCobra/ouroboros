CXXFLAGS=-Wall -Wextra -pedantic -I. -I../ -I../data -I../../ -std=c++11 -I../../../lib/

.PHONY: clean all

all: libtest.so.1

libtest.so.1.0: test.cpp test.h
	g++ $(CXXFLAGS) -fPIC -g -c test.cpp
	g++ -Wall -shared -g -Wl,-soname,libtest.so.1 -o libtest.so.1.0 test.o

libtest.so.1: libtest.so.1.0
	rm -rf $@
	ln -s $^ $@

clean:
	rm -rf libtest.so libtest.so.1.0 *.o
