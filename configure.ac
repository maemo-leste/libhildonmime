dnl Process this file with autoconf to produce a configure script.
AC_PREREQ(2.52)
 
AC_INIT(libhildonmime, 2.1.3)
AC_CONFIG_SRCDIR(libhildonmime/hildon-uri.c)
AM_INIT_AUTOMAKE

dnl Versioning for libhildonmime

dnl Increase when changing the API (adding, removing, changing)
LIBHILDONMIME_CURRENT=1

dnl Increase when changing implementation of current API,
dnl reset to 0 when changing CURRENT. This is the revision of current
dnl API version.
LIBHILDONMIME_REVISION=3

dnl Change this only if CURRENT has been changed. Increase if API
dnl change is ABI compatible, otherwise reset to 0
LIBHILDONMIME_AGE=1

LIBHILDONMIME_VERSION_INFO="$LIBHILDONMIME_CURRENT:$LIBHILDONMIME_REVISION:$LIBHILDONMIME_AGE"
AC_SUBST(LIBHILDONMIME_VERSION_INFO)

dnl Globally define_GNU_SOURCE and therefore enable the GNU extensions
AC_DEFINE(_GNU_SOURCE, 1, [Enable GNU Extensions])

AM_MAINTAINER_MODE
AM_CONFIG_HEADER(config.h)

AM_DISABLE_STATIC
AM_PROG_LIBTOOL

AC_ISC_POSIX
AC_PROG_CC
AM_PROG_CC_STDC
AC_HEADER_STDC

AC_HEADER_TIME
AC_CHECK_HEADERS([stdlib.h string.h])

dnl Defined in acinclude.m4
IDT_COMPILE_WARNINGS

DBUS_REQUIRED=0.60
GLIB_REQUIRED=2.6.0
GTK_REQUIRED=2.6.0
LIBXML_REQUIRED=2.4

GTK_DOC_CHECK([1.14],[--flavour no-tmpl])

dnl =======================================
dnl libhildonmime
dnl =======================================
PKG_CHECK_MODULES(LIBHILDONMIME, [
        gio-2.0
        glib-2.0 >= $GLIB_REQUIRED
        dbus-glib-1 >= $DBUS_REQUIRED
])

AC_SUBST(LIBHILDONMIME_CFLAGS)
AC_SUBST(LIBHILDONMIME_LIBS)

dnl =======================================
dnl update-category-database 
dnl =======================================
PKG_CHECK_MODULES(UPDATE_CATEGORY, [
        glib-2.0 >= $GLIB_REQUIRED
        libxml-2.0 >= $LIBXML_REQUIRED
])
AC_SUBST(UPDATE_CATEGORY_CFLAGS)
AC_SUBST(UPDATE_CATEGORY_LIBS)

PKG_CHECK_MODULES(UPDATE_DESKTOP, [
        glib-2.0 >= $GLIB_REQUIRED
])
AC_SUBST(UPDATE_DESKTOP_CFLAGS)
AC_SUBST(UPDATE_DESKTOP_LIBS)

AC_ARG_ENABLE(update-categorydb,
   AC_HELP_STRING([--disable-update-categoryb],
                   [disable the update-category-database after install [default=no]]),,
    enable_update_categorydb=yes)
AM_CONDITIONAL(ENABLE_UPDATE_CATEGORYDB, test x$enable_update_categorydb = xyes)


dnl This will cause the automake generated makefiles to pass the
dnl correct flags to aclocal.
ACLOCAL_AMFLAGS="\${ACLOCAL_FLAGS}"
AC_SUBST(ACLOCAL_AMFLAGS)

AC_OUTPUT([
	Makefile 
	libhildonmime.pc
	debian/Makefile
        libhildonmime/Makefile
        tests/Makefile
        data/Makefile
	docs/Makefile
	docs/version.xml
])
