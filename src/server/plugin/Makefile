CXXFLAGS=-Wall -Wextra -pedantic -I. -I../ -I../data -I../../ -std=c++11 -I../../../lib/ -g

.PHONY: clean all

OUTPUT=sample_cpp.plugin python.plugin
PYTHON_VERSION ?= 2.7

all: $(OUTPUT)

python.plugin: python.cpp
	g++ $(CXXFLAGS) $(shell pkg-config --cflags --libs python-$(PYTHON_VERSION)) -fPIC -shared $< -o $@

sample_cpp.plugin: sample_cpp.cpp
	g++ $(CXXFLAGS) -fPIC -shared $< -o $@

clean:
	rm -rf $(OUTPUT) *.o
