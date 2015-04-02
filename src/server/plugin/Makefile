CXXFLAGS=-Wall -Wextra -pedantic -I. -I../ -I../data -I../../ -std=c++11 -I../../../lib/ -g

.PHONY: clean all

OUTPUT=sample_cpp.plugin python_inline.plugin python_file.plugin
PYTHON_VERSION ?= 2.7

all: $(OUTPUT)

python_inline.plugin: sample_python_inline.cpp
	g++ $(CXXFLAGS) $(shell pkg-config --cflags --libs python-$(PYTHON_VERSION)) -fPIC -shared $< -o $@

python_file.plugin: sample_python_file.cpp
	g++ $(CXXFLAGS) $(shell pkg-config --cflags --libs python-$(PYTHON_VERSION)) -fPIC -shared $< -o $@


sample_cpp.plugin: sample_cpp.cpp
	g++ $(CXXFLAGS) -fPIC -shared $< -o $@

clean:
	rm -rf $(OUTPUT) *.o
