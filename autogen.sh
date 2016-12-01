#!/bin/sh

PACKAGE="libhildonmime"

have_libtool=false
have_autoconf=false
have_automake=false
need_configure_in=false

if libtool --version < /dev/null > /dev/null 2>&1 ; then
	libtool_version=`libtoolize --version | sed 's/^[^0-9]*\([0-9.][0-9.]*\).*/\1/'`
	have_libtool=true
fi

if $have_libtool ; then : ; else
	echo;
	echo "You must have libtool >= 1.3 installed to compile $PACKAGE";
	echo;
	exit;
fi

echo "Generating configuration files for $PACKAGE, please wait...."
echo;

aclocal $ACLOCAL_FLAGS
libtoolize --force
autoheader
automake --add-missing
autoconf

if test x$NOCONFIGURE = x; then
  echo Running $srcdir/configure "$@" ...
  ./configure "$@" --enable-maintainer-mode \
  && echo Now type \`make\' to compile $PROJECT  || exit 1
else
  echo Skipping configure process.
fi

