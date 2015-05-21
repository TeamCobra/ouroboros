AC_INIT([ouroboros], [1.0], [])
AC_CONFIG_SRCDIR([src/ouroboros/callback.hpp])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign -Wall -Werror subdir-objects])

#General project requirements
	# Checks for programs.
	AC_PROG_CXX
	AC_PROG_CC
	AC_PROG_MAKE_SET
	AM_PROG_AR

	# Checks for libraries.
	AC_CHECK_LIB([dl], [dlopen])
	AC_CHECK_LIB([pthread], [pthread_create])

	# Checks for header files.
	AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

	# Checks for typedefs, structures, and compiler characteristics.
	AC_CHECK_HEADER_STDBOOL
	AC_TYPE_SIZE_T

	LT_INIT
	AC_CONFIG_FILES([Makefile src/Makefile lib/Makefile src/ouroboros/Makefile \
		src/ouroboros/data/Makefile src/test/Makefile])

#Requirements imposed by frozen
	#AC_CHECK_HEADERS([stdlib.h string.h]) #Headers required earlier

	# Checks for typedefs, structures, and compiler characteristics.
	AC_TYPE_SIZE_T

	# Checks for library functions.
	AC_CHECK_FUNCS([memset])
	
#Requirements imposed by Mongoose
	# Checks for libraries.
	# AC_CHECK_LIB([dl], [main]) # check required earlier
	AC_CHECK_LIB([ssl], [SSL_version])

	# Checks for header files.
	#AC_CHECK_HEADERS([arpa/inet.h fcntl.h inttypes.h limits.h netdb.h
	#	netinet/in.h stddef.h stdlib.h string.h sys/socket.h unistd.h])
	#	original list

	AC_CHECK_HEADERS([arpa/inet.h fcntl.h inttypes.h limits.h netdb.h \
		netinet/in.h stddef.h stdlib.h string.h sys/socket.h])
	
	# Checks for typedefs, structures, and compiler characteristics.
	AC_TYPE_INT64_T
	AC_TYPE_PID_T
	AC_TYPE_SIZE_T
	AC_TYPE_UINT16_T
	AC_TYPE_UINT32_T
	AC_TYPE_UINT64_T
	AC_TYPE_UINT8_T

	# Checks for library functions.
	AC_FUNC_FORK
	AC_FUNC_MALLOC
	AC_FUNC_MMAP
	AC_FUNC_REALLOC
	AC_FUNC_STRTOD
	AC_CHECK_FUNCS([dup2 getcwd gethostbyname inet_ntoa memchr memmove memset \
		mkdir munmap rmdir select socket strchr strcspn strdup strerror strrchr\
		strspn strstr])

#Requirements imposed by slr
	# Checks for header files.
	# AC_CHECK_HEADERS([stdlib.h string.h]) #Headers required earlier

	# Checks for library functions.
	AC_FUNC_REALLOC
	AC_CHECK_FUNCS([strchr])

#Requirements imposed by googletest
	# Checks for libraries.
	AC_CHECK_LIB([pthread], [pthread_create])

	# Checks for header files.
	
	#AC_CHECK_HEADERS([arpa/inet.h fcntl.h float.h limits.h netdb.h stddef.h
	#	stdlib.h string.h strings.h sys/time.h sys/timeb.h unistd.h wchar.h
	#	wctype.h]) # original list of headers
	
	AC_CHECK_HEADERS([float.h strings.h sys/time.h sys/timeb.h wchar.h \
		wctype.h])

	# Checks for typedefs, structures, and compiler characteristics.
	AC_CHECK_HEADER_STDBOOL
	AC_C_INLINE
	AC_TYPE_PID_T
	AC_TYPE_SIZE_T
	AC_TYPE_SSIZE_T
	AC_CHECK_TYPES([ptrdiff_t])

	# Checks for library functions.
	AC_FUNC_FORK
	AC_FUNC_MALLOC
	AC_FUNC_MMAP
	AC_FUNC_STRERROR_R

	#AC_CHECK_FUNCS([dup2 fchdir getcwd getpagesize gettimeofday localtime_r
	#	memset mkdir munmap putenv regcomp rmdir setenv socket strcasecmp strchr
	#	strdup strerror strrchr strstr strtol strtoull tzset]) # Original list
	
	AC_CHECK_FUNCS([fchdir getpagesize gettimeofday localtime_r	putenv regcomp \
		setenv strcasecmp strtol strtoull tzset])

AC_OUTPUT
