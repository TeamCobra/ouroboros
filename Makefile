include vars.mk

.PHONY: test clean all

all:
	mkdir -p build/obj
	make -C ${SRC_DIR} all

test:
	make -C ${SRC_DIR} test

clean:
	make -C ${SRC_DIR} clean
