CXXFLAGS=-Wall -Wextra -pedantic -I. -I../ -I../data -I../../ -std=c++11 -I../../../lib/ -g

.PHONY: clean all

OUTPUT=libtest.so python.plugin

all: libtest.so python.plugin

python.plugin: python.cpp
	g++ $(CXXFLAGS) $(shell pkg-config --cflags --libs python-3.3) -fPIC -shared $< -o $@

libtest.so: test.cpp test.h
	g++ $(CXXFLAGS) -fPIC -shared $< -o $@

clean:
	rm -rf $(OUTPUT) *.o
