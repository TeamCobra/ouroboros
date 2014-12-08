include ../vars.mk

PROG = server
CFLAGS = $(CORE_FLAGS) $(INCLUDE) $(CFLAGS_EXTRA) -std=c99
CXXFLAGS = $(CORE_FLAGS) $(INCLUDE) $(CXXFLAGS_EXTRA) -std=c++11
SOURCES = $(PROG).cpp mongoose.c

$(PROG): mongoose.o server.o
	$(CXX) -o $(PROG) $^ $(CFLAGS)

clean:
	rm -rf $(PROG) *.exe *.dSYM *.obj *.exp .*o *.lib
