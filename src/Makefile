.PHONY: all clean test

include ../vars.mk

all:
	make -C server/ all
	make -C templates/ all
	make -C data/ all

clean:
	make -C data/ clean
	make -C templates/ clean
	make -C server/ clean
	make -C test/ clean

test:
	make -C test/
