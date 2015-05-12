CXXFLAGS=-Wall -Wextra -pedantic -I. -I../ -I../data -I../../ -std=c++14 -I../../../lib/ -g

.PHONY: clean all

OUTPUT=sample_cpp.plugin python_inline.plugin python_file.plugin
PYTHON_VERSION ?= 2.7

all: $(OUTPUT)

python_inline.plugin: sample_python_inline.cpp
	g++ $(CXXFLAGS)  -fPIC -shared $< -o $@ $(shell pkg-config --cflags --libs python-$(PYTHON_VERSION))

python_file.plugin: sample_python_file.cpp
	g++ $(CXXFLAGS)  -fPIC -shared $< -o $@ $(shell pkg-config --cflags --libs python-$(PYTHON_VERSION))


sample_cpp.plugin: sample_cpp.cpp
	g++ $(CXXFLAGS) -fPIC -shared $< -o $@

demo.plugin: demo.cpp
	g++ $(CXXFLAGS) -I./wiringPi/wiringPi -fPIC -shared $< -o $@ -lwiringPi -lwiringPiDev

clean:
	rm -rf $(OUTPUT) *.o
