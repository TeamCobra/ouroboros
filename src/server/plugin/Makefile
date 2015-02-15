CXXFLAGS=-Wall -Wextra -pedantic -I. -I../ -I../data -I../../ -std=c++11 -I../../../lib/

libtest.so: test.cpp test.h
	g++ $(CXXFLAGS) -fPIC -c test.cpp
	g++ -Wall -shared -Wl,-soname,libtest.so.1 -o libtest.so.1.0 test.o
	rm -rf $@
	ln -s libtest.so.1.0 $@
