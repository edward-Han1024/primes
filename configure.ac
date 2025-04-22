AC_INIT([primes], [1.0], [Edward Han])
AM_INIT_AUTOMAKE
: ${CXXFLAGS="-O3"}
AC_PROG_CXX

dnl check for headers
AC_LANG_PUSH([C++])
AC_CHECK_HEADERS([iostream],
  [AC_DEFINE([HAVE_iostream], [1], [Define to 1 if you have the <iostream> header file.])],
  [AC_MSG_ERROR([<iostream> header not found.\nPlease make sure you are using C++ instead of a C compiler])])
AC_CHECK_HEADERS([vector],
  [AC_DEFINE([HAVE_vector], [1], [Define to 1 if you have the <vector> header file.])],
  [AC_MSG_ERROR([<vector> header not found.\nPlease make sure you are using C++ instead of a C compiler])])
AC_CHECK_HEADERS([fstream],
  [AC_DEFINE([HAVE_fstream], [1], [Define to 1 if you have the <fstream> header file.])],
  [AC_MSG_ERROR([<fstream> header not found.\nPlease make sure you are using C++ instead of a C compiler])])
AC_CHECK_HEADERS([string],
  [AC_DEFINE([HAVE_string], [1], [Define to 1 if you have the <string> header file.])],
  [AC_MSG_ERROR([<string> header not found.\nPlease make sure you are using C++ instead of a C compiler])])
AC_CHECK_HEADERS([ctime],
  [AC_DEFINE([HAVE_ctime], [1], [Define to 1 if you have the <ctime> header file.])],
  [AC_MSG_ERROR([<ctime> header not found.\nPlease make sure you are using C++ instead of a C compiler])])
AC_CHECK_HEADERS([iomanip],
  [AC_DEFINE([HAVE_iomanip], [1], [Define to 1 if you have the <iomanip> header file.])],
  [AC_MSG_ERROR([<iomanip> header not found.\nPlease make sure you are using C++ instead of a C compiler])])
AC_CHECK_HEADERS([math.h],
  [AC_DEFINE([HAVE_math_h], [1], [Define to 1 if you have the <math.h> header file.])],
  [AC_MSG_ERROR([<math.h> header not found.\nPlease make sure you are using C++ instead of a C compiler])])
AC_CHECK_HEADERS([cstdint],
  [AC_DEFINE([HAVE_cstdint], [1], [Define to 1 if you have the <cstdint> header file.])],
  [AC_MSG_ERROR([<cstdint> header not found.\nPlease make sure you are using C++ instead of a C compiler])])
AC_CHECK_HEADERS([cstdint],
  [AC_DEFINE([HAVE_cstdint], [1], [Define to 1 if you have the <cstdint> header file.])],
  [AC_MSG_ERROR([<cstdint> header not found.\nPlease make sure you are using C++ instead of a C compiler])])
AC_LANG_POP([C++])

dnl has to be at the end
AC_CONFIG_FILES([Makefile])
AC_OUTPUT