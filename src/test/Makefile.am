AM_CPPFLAGS = -I$(top_srcdir)/lib/googletest \
	-I$(top_srcdir)/lib/googletest/include -I$(top_srcdir)/src/ \
	-I$(top_srcdir)/lib/

AM_CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++03 -pthread

check_PROGRAMS = base_string_test data_store_test
check_LIBRARIES= libgoogletest.a

libgoogletest_a_SOURCES =  ../../lib/googletest/src/gtest-all.cc
libgoogletest_a_CXXFLAGS = -I$(top_srcdir)/lib/googletest

_shared_ldadd =  $(top_builddir)/src/ouroboros/libouroboros.a \
	$(top_builddir)/src/ouroboros/data/libdata.a \
	$(top_builddir)/src/ouroboros/data/libJSON.a \
	$(top_builddir)/lib/libmongoose.a \
	$(top_builddir)/lib/libslre.a \
	$(top_builddir)/lib/libfrozen.a libgoogletest.a \
	-ldl

base_string_test_LDADD = $(_shared_ldadd)
base_string_test_SOURCES = base_string_test.cpp

data_store_test_LDADD = $(_shared_ldadd)
data_store_test_SOURCES = data_store_test.cpp

TESTS = $(check_PROGRAMS)
