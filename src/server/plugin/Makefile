CXXFLAGS=-Wall -Wextra -pedantic -I. -I../ -I../data -I../../ -std=c++11 -I../../../lib/ -g

.PHONY: clean all

all: libtest.so

libtest.so: test.cpp test.h
	g++ $(CXXFLAGS) -fPIC -shared $< -o $@

clean:
	rm -rf libtest.so *.o
