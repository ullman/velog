AC_INIT([velog], [1.1.0], [henrik@ullman.com])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_PROG_CC
AC_PROG_LIBTOOL

AM_CFLAGS="-Wall -Werror -O2"

AC_CHECK_LIB([cunit], [CU_initialize_registry])

AC_SEARCH_LIBS([prom_gauge_new], [prom], [], [
  AC_MSG_ERROR([required library libprom not found])
])

AC_SEARCH_LIBS([promhttp_start_daemon], [promhttp], [], [
  AC_MSG_ERROR([required library libpromhttp not found])
])

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
