include ../vars.mk

PROG = server
CFLAGS = -pthread $(CORE_FLAGS) $(INCLUDE) $(CFLAGS_EXTRA) -std=c99
CXXFLAGS = -pthread $(CORE_FLAGS) $(INCLUDE) $(CXXFLAGS_EXTRA) -std=c++11
SOURCES = $(PROG).cpp mongoose.c

OBJECT_FILES= ${OBJ_DIR}/rest.o ${OBJ_DIR}/frozen.o ${OBJ_DIR}/slre.o ${OBJ_DIR}/base.o ${OBJ_DIR}/misc.o ${OBJ_DIR}/rest_handlers.o ${OBJ_DIR}/device_tree.o ${OBJ_DIR}/base_string.o ${OBJ_DIR}/base_integer.o ${OBJ_DIR}/JSON.o

all:
	make -C ../
	make ${PROG}

$(PROG): mongoose.o server.o ${OBJECT_FILES}
	make -C ../
	$(CXX) -o $(PROG) $^ $(CFLAGS)


clean:
	rm -rf $(PROG) *.exe *.dSYM *.obj *.exp *.o *.lib
