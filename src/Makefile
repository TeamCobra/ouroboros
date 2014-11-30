.PHONY: all clean test

include ../vars.mk

all:
	make -C server/

clean:
	make -C server/ clean
	make -C test/ clean

test:
	make -C test/
