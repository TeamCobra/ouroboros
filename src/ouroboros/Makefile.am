SUBDIRS = data
AM_CPPFLAGS = -I$(top_srcdir)/lib/ -I$(top_srcdir)/src/
AM_CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++03 -pthread

noinst_LIBRARIES = libouroboros.a
libouroboros_a_SOURCES = ouroboros_server.h device_tree.cpp device_tree.hpp \
	device_tree.ipp device_tree.tpp rest.cpp rest.h ouroboros_server.cpp \
	plugin_manager.h plugin_manager.cpp callback.hpp callback.ipp \
	callback_manager.h callback_manager.cpp function_manager.cpp \
	function_manager.h

bin_PROGRAMS = ouroboros_server
ouroboros_server_LDADD = libouroboros.a data/libJSON.a data/libdata.a \
	$(top_builddir)/lib/libmongoose.a $(top_builddir)/lib/libslre.a \
	$(top_builddir)/lib/libfrozen.a -ldl
	
ouroboros_server_SOURCES = main.cpp
ouroboros_server_LDFLAGS = -export-dynamic
ouroboros_server_CXXFLAGS = $(AM_CXXFLAGS)
