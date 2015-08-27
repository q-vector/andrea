dnl Process this file with autoconf to produce a configure script.
AC_INIT([andrea], [0.1.0])
AC_CONFIG_SRCDIR([andrea])
AM_INIT_AUTOMAKE

dnl Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_C_BIGENDIAN
AC_LANG(C++)
AC_CHECK_LIBM

dnl Checks for libraries.
PKG_CHECK_MODULES([DENISE], [denise])
ANDREA_REQUIRES="$ANDREA_REQUIRES denise"
ANDREA_CFLAGS="$ANDREA_CFLAGS $DENISE_CFLAGS"
ANDREA_LIBS="$ANDREA_LIBS $DENISE_LIBS"

dnl Checks for header files.
AC_CHECK_HEADERS(readline/readline.h)
AC_CHECK_LIB(ncurses, main, [DENISE_LIBS="-lncurses $DENISE_LIBS"],
   AC_MSG_ERROR(ncurses not found), )
AC_CHECK_LIB(readline, readline, [DENISE_LIBS="-lreadline $DENISE_LIBS"],
   AC_MSG_ERROR(readline not found), -lncurses)

dnl Checks for typedefs, structures, and compiler characteristics.

dnl Checks for library functions.

CPPFLAGS="$ANDREA_CFLAGS $CPPFLAGS"
LIBS="$ANDREA_LIBS $LIBS"

AC_SUBST(ANDREA_REQUIRES)
AC_SUBST(ANDREA_CFLAGS)
AC_SUBST(ANDREA_LIBS)

AC_CONFIG_FILES([andrea.pc Makefile andrea/Makefile src/Makefile])
AC_OUTPUT
