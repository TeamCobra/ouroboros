AM_CPPFLAGS = -I$(top_srcdir)/lib/mongoose -I$(top_srcdir)/lib/slre -I$(top_srcdir)/lib/frozen -I$(top_srcdir)/lib/googletest -I$(top_srcdir)/lib/googletest/include -I$(top_srcdir)/src/ -I$(top_srcdir)/src/server -I$(top_srcdir)/lib/
AM_CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++03 -pthread

check_PROGRAMS = test_base_string #test_data_store test_rest

test_base_string_LDADD = $(top_builddir)/src/server/libouroboros.a $(top_builddir)/src/server/data/libdata.a $(top_builddir)/src/server/data/libJSON.a $(top_builddir)/lib/libmongoose.a $(top_builddir)/lib/libslre.a $(top_builddir)/lib/libfrozen.a $(top_builddir)/lib/libgoogletest.a -ldl
test_base_string_SOURCES = test_base_string.cpp
#ouroboros_server_LDFLAGS = -export-dynamic
ouroboros_server_CXXFLAGS = $(AM_CXXFLAGS)


TESTS = $(check_PRORGRAMS)
