AM_CPPFLAGS = -I$(top_srcdir)/lib/mongoose -I$(top_srcdir)/lib/slre -I$(top_srcdir)/lib/frozen -I$(top_srcdir)/lib/googletest -I$(top_srcdir)/lib/googletest/include -I$(top_srcdir)/src/ -I$(top_srcdir)/src/server -I$(top_srcdir)/lib/
AM_CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++03 -pthread

check_PROGRAMS = base_string_test data_store_test #test_rest

_shared_ldadd =  $(top_builddir)/src/server/libouroboros.a $(top_builddir)/src/server/data/libdata.a $(top_builddir)/src/server/data/libJSON.a $(top_builddir)/lib/libmongoose.a $(top_builddir)/lib/libslre.a $(top_builddir)/lib/libfrozen.a $(top_builddir)/lib/libgoogletest.a -ldl

base_string_test_LDADD = $(_shared_ldadd)
base_string_test_SOURCES = base_string_test.cpp

data_store_test_LDADD = $(_shared_ldadd)
data_store_test_SOURCES = data_store_test.cpp

TESTS = $(check_PROGRAMS)

