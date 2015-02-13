SUBDIRS = data
LDADD = $(top_builddir)/src/server/data/libJSON.a $(top_builddir)/src/server/data/libdata.a $(top_builddir)/lib/libmongoose.a $(top_builddir)/lib/libslre.a $(top_builddir)/lib/libfrozen.a
AM_CPPFLAGS = -I$(top_srcdir)/lib/mongoose -I$(top_srcdir)/lib/slre -I$(top_srcdir)/lib/frozen -I$(top_srcdir)/lib/googletest -I$(top_srcdir)/src/ -I$(top_srcdir)/lib/
AM_CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++03 -pthread

bin_PROGRAMS = ouroboros-server
ouroboros_server_SOURCES = device_tree.cpp  device_tree.hpp  device_tree.ipp  device_tree.tpp rest.cpp  rest.h  rest_handlers.cpp  rest_handlers.h  server.cpp
