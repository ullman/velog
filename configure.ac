AC_INIT([velog], [1.1.0], [henrik@ullman.com])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([src/config.h])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_PROG_CC
AC_PROG_LIBTOOL


AC_ARG_ENABLE([prometheus],
  [AS_HELP_STRING([--disable-prometheus], [Enable Prometheus export @<:@check@:>@])],
  [:],
  [enable_prometheus=no])

AC_CHECK_LIB([cunit], [CU_initialize_registry])

AM_CONDITIONAL([ENABLE_PROMETHEUS], [test "$enable_prometheus" = "yes"])
AS_IF([test "$enable_prometheus" = "yes"],
	[AC_SEARCH_LIBS([prom_gauge_new], [prom], [], [
  	AC_MSG_ERROR([required library libprom not found])
	])

	AC_SEARCH_LIBS([promhttp_start_daemon], [promhttp], [], [
  	AC_MSG_ERROR([required library libpromhttp not found])
	])

	AC_DEFINE([PROMETHEUS], 1, [Enable Prometheus exporter])
	])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
