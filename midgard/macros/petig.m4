dnl $Id: petig.m4,v 1.6 2002/02/18 13:58:49 christof Exp $

dnl Configure paths for some libraries
dnl derived from kde's acinclude.m4

dnl why not /usr/local/lib/mico-setup.sh

AC_DEFUN(EXKDE_CHECK_LIBDL,
[
AC_CHECK_LIB(dl, dlopen, [
LIBDL="-ldl"
ac_cv_have_dlfcn=yes
])

AC_CHECK_LIB(dld, shl_unload, [
LIBDL="-ldld"
ac_cv_have_shload=yes
])

AC_SUBST(LIBDL)
])

AC_DEFUN(EXKDE_CHECK_MICO,
[
AC_REQUIRE([EXKDE_CHECK_LIBDL])
AC_MSG_CHECKING(for MICO)
AC_ARG_WITH(micodir,
  [  --with-micodir=micodir  where mico is installed ],
  kde_micodir=$withval,
  kde_micodir=/usr/local
)
if test ! -r  $kde_micodir/include/CORBA.h; then
  kde_micodir=/usr
  if test ! -r  $kde_micodir/include/CORBA.h; then
    AC_MSG_ERROR([No CORBA.h found, specify another micodir])
  fi
fi
AC_MSG_RESULT($kde_micodir)

MICO_INCLUDES=-I$kde_micodir/include
AC_SUBST(MICO_INCLUDES)
MICO_CFLAGS=$MICO_INCLUDES
AC_SUBST(MICO_CFLAGS)
MICO_LDFLAGS=-L$kde_micodir/lib
AC_SUBST(MICO_LDFLAGS)

AC_MSG_CHECKING([for MICO version])
AC_CACHE_VAL(kde_cv_mico_version,
[
AC_LANG_C
cat >conftest.$ac_ext <<EOF
#include <stdio.h>
#include <mico/version.h>
int main() { 
    
   printf("MICO_VERSION=%s\n",MICO_VERSION); 
   return (0); 
}
EOF
ac_compile='${CC-gcc} $CFLAGS $MICO_INCLUDES conftest.$ac_ext -o conftest'
if AC_TRY_EVAL(ac_compile); then
  if eval `./conftest 2>&5`; then
    kde_cv_mico_version=$MICO_VERSION
  else
    AC_MSG_ERROR([your system is not able to execute a small application to
    find MICO version! Check $kde_micodir/include/mico/version.h])
  fi 
else
  AC_MSG_ERROR([your system is not able to compile a small application to
  find MICO version! Check $kde_micodir/include/mico/version.h])
fi
])

dnl installed MICO version
mico_v_maj=`echo $kde_cv_mico_version | sed -e 's/^\(.*\)\..*\..*$/\1/'`
mico_v_mid=`echo $kde_cv_mico_version | sed -e 's/^.*\.\(.*\)\..*$/\1/'`
mico_v_min=`echo $kde_cv_mico_version | sed -e 's/^.*\..*\.\(.*\)$/\1/'`

dnl required MICO version
req_v_maj=`echo $1 | sed -e 's/^\(.*\)\..*\..*$/\1/'`
req_v_mid=`echo $1 | sed -e 's/^.*\.\(.*\)\..*$/\1/'`
req_v_min=`echo $1 | sed -e 's/^.*\..*\.\(.*\)$/\1/'` 

if test "$mico_v_maj" -lt "$req_v_maj" || \
   ( test "$mico_v_maj" -eq "$req_v_maj" && \
        test "$mico_v_mid" -lt "$req_v_mid" ) || \
   ( test "$mico_v_mid" -eq "$req_v_mid" && \
        test "$mico_v_min" -lt "$req_v_min" )

then
  AC_MSG_ERROR([found MICO version $kde_cv_mico_version but version $1 \
at least is required. You should upgrade MICO.])
else
  AC_MSG_RESULT([$kde_cv_mico_version (minimum version $1, ok)])
fi

LIBMICO="-lmico$kde_cv_mico_version $LIBDL"
AC_SUBST(LIBMICO)
IDL=$kde_micodir/bin/idl
AC_SUBST(IDL)
])

AC_DEFUN(EXKDE_CHECK_MINI_STL,
[
AC_REQUIRE([EXKDE_CHECK_MICO])

AC_MSG_CHECKING(if we use mico's mini-STL)
AC_CACHE_VAL(kde_cv_have_mini_stl,
[
AC_LANG_CPLUSPLUS
kde_save_cxxflags="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS $MICO_INCLUDES"
AC_TRY_COMPILE(
[
#include <mico/config.h>
],
[
#ifdef HAVE_MINI_STL
#error "nothing"
#endif
],
kde_cv_have_mini_stl=no,
kde_cv_have_mini_stl=yes)
CXXFLAGS="$kde_save_cxxflags"
])

AC_MSG_RESULT($kde_cv_have_mini_stl)
if test "$kde_cv_have_mini_stl" = "yes"; then
  AC_DEFINE_UNQUOTED(HAVE_MINI_STL)
fi
])

AC_DEFUN(PETIG_CHECK_MICO,
[
EXKDE_CHECK_MICO([2.3.3])
AC_REQUIRE([EXKDE_CHECK_MINI_STL])
MICO_IDLFLAGS="-I$kde_micodir/include/mico -I$kde_micodir/include"
AC_SUBST(MICO_IDLFLAGS)
MICO_LIBS="-lmicocoss$kde_cv_mico_version $LIBMICO"
AC_SUBST(MICO_LIBS)
MICO_GTKLIBS="-lmicogtk$kde_cv_mico_version"
AC_SUBST(MICO_GTKLIBS)
])

AC_DEFUN(PETIG_CHECK_ECPG,
[
if test "x$ECPG_INCLUDES" == "x"
then
  AC_MSG_CHECKING(for PostgreSQL ECPG)
  AC_ARG_WITH(postgresdir,
    [  --with-postgresdir=postgresdir  where PostgreSQL is installed ],
    petig_postgresdir=$withval,
    petig_postgresdir=`which ecpg | sed s+/bin/ecpg++`
  )
  ECPG="$petig_postgresdir/bin/ecpg"
  if test ! -x  $ECPG; then
     AC_MSG_ERROR([ecpg not found ($ECPG), please specify --with-postgresdir=PATH])
  fi
  AC_MSG_RESULT($ECPG)
  
  AC_MSG_CHECKING(for ECPG include files)
  ECPG_PATH=`$ECPG -v 2>&1 | fgrep -v 'ecpg - ' | fgrep -v 'ecpg, the' | fgrep -v 'search starts here:' | fgrep -v 'nd of search list'`
  ECPG_PATH_OK=0
  for i in $ECPG_PATH
  do
    if test -r $i/ecpgerrno.h ; then ECPG_PATH_OK=1 ; fi
    if (echo $i | fgrep -q include )
    then
      LDIR=`echo $i | sed s+/include+/lib+`
      if test -d $LDIR
      then
      	 dnl perhaps test for libpq etc.
         ECPG_LDFLAGS="$ECPG_LDFLAGS -L$LDIR"
      fi
    fi
    ECPG_INCLUDES="$ECPG_INCLUDES -I$i"
  done
  if test $ECPG_PATH_OK = 0
  then
    AC_MSG_ERROR([No ecpgerrno.h found. Please report. ($ECPG_PATH)])
  else
    AC_MSG_RESULT($ECPG_INCLUDES)
  fi
  
  AC_SUBST(ECPG)
  AC_SUBST(ECPG_INCLUDES)
  ECPG_CFLAGS=$ECPG_INCLUDES
  AC_SUBST(ECPG_CFLAGS)
  AC_SUBST(ECPG_LDFLAGS)
  ECPG_LIBS='-lecpg -lpq -lcrypt'
  AC_SUBST(ECPG_LIBS)
  ECPG_NODB_LIBS=""
  AC_SUBST(ECPG_NODB_LIBS)
fi
])

dnl this name not that consistent
AC_DEFUN(PETIG_CHECK_POSTGRES,
[ PETIG_CHECK_ECPG
])

dnl PETIG_CHECK_LIB(lib name,dir name,define name,alt.lib+dir name,dep1,dep2)

AC_DEFUN(PETIG_CHECK_LIB,
[
dnl only if not already checked
if test "x$$3_INCLUDES" == "x" 
then
  dnl dependancies
  if test "x$5" != "x" -a "x$$5_INCLUDES" == "x"
  then
    PETIG_CHECK_$5
  fi
  if test "x$6" != "x" -a "x$$6_INCLUDES" == "x"
  then
    PETIG_CHECK_$6
  fi
  
  AC_MSG_CHECKING(for $1 library)
  if test -r "../$2/lib$1.a"
  then
    TEMP=`cd ../$2 ; pwd` 
    $3_INCLUDES="-I$TEMP"
    $3_LDFLAGS=""
    $3_LIBS="$TEMP/lib$1.a"
    AC_MSG_RESULT($$3_INCLUDES)
  elif test -r "../$2/src/lib$1.a"
  then 
    TEMP=`cd ../$2/src ; pwd` 
    $3_INCLUDES="-I$TEMP"
    $3_LDFLAGS=""
    $3_LIBS="$TEMP/lib$1.a"
    AC_MSG_RESULT($$3_INCLUDES)
  elif test -r "../$4/lib$4.a"
  then 
    TEMP=`cd ../$4 ; pwd` 
    $3_INCLUDES="-I$TEMP"
    $3_LDFLAGS="-L$TEMP"
    $3_LIBS="-l$4"
    AC_MSG_RESULT($$3_INCLUDES)
  elif test -r "../$4/src/lib$4.a"
  then 
    TEMP=`cd ../$4/src ; pwd` 
    $3_INCLUDES="-I$TEMP"
    $3_LDFLAGS="-L$TEMP"
    $3_LIBS="-l$4"
    AC_MSG_RESULT($$3_INCLUDES)
  else
    if test "x$prefix" = "xNONE" 
    then mytmp="$ac_default_prefix"
    else mytmp="$prefix"
    fi
    if test "(" "x$4" != "x" -a -d $mytmp/include/$4 ")" -a -r $mytmp/lib/lib$4.a
    then
      $3_INCLUDES="-I$mytmp/include/$4"
      AC_MSG_RESULT($$3_INCLUDES)
      $3_LIBS="-L$mytmp/lib -l$4"
      $3_LDFLAGS=""
    else 
      AC_MSG_ERROR([not found])
    fi
  fi
  $3_NODB_LIBS="$$3_LIBS"

  dnl dependancies
  if test "x$5" != "x"
  then
    $3_INCLUDES="$$5_INCLUDES $$3_INCLUDES"
    $3_LIBS="$$3_LIBS $$5_LIBS"
    $3_NODB_LIBS="$$3_NODB_LIBS $$5_NODB_LIBS"
    $3_LDFLAGS="$$3_LDFLAGS $$5_LDFLAGS" 
  fi
  if test "x$6" != "x"
  then
    $3_INCLUDES="$$6_INCLUDES $$3_INCLUDES"
    $3_LIBS="$$3_LIBS $$6_LIBS"
    $3_NODB_LIBS="$$3_NODB_LIBS $$6_NODB_LIBS"
    $3_LDFLAGS="$$3_LDFLAGS $$6_LDFLAGS"
  fi

  $3_CFLAGS=$$3_INCLUDES
  AC_SUBST($3_INCLUDES)
  AC_SUBST($3_CFLAGS)
  AC_SUBST($3_LIBS)
  AC_SUBST($3_NODB_LIBS)
  AC_SUBST($3_LDFLAGS)
fi
])

AC_DEFUN(PETIG_CHECK_GTKMM,
[
if test "x$GTKMM_CFLAGS" == "x"
then
  AM_PATH_GTKMM(1.2.0,,AC_MSG_ERROR(Cannot find Gtk-- Version 1.2.x))
fi
GTKMM_INCLUDES=$GTKMM_CFLAGS
AC_SUBST(GTKMM_INCLUDES)
GTKMM_NODB_LIBS=$GTKMM_LIBS
AC_SUBST(GTKMM_NODB_LIBS)
])

AC_DEFUN(PETIG_CHECK_COMMONXX,
[
PETIG_CHECK_LIB(common++,c++,COMMONXX,ManuProC_Base,ECPG)
])

AC_DEFUN(PETIG_CHECK_KOMPONENTEN,
[
PETIG_CHECK_LIB(Komponenten,Komponenten,KOMPONENTEN,ManuProC_Widgets,COMMONXX,COMMONGTK)
])

AC_DEFUN(PETIG_CHECK_COMMONGTK,
[
PETIG_CHECK_LIB(commongtk,gtk,COMMONGTK,GtkmmAddons,GTKMM)
])

AC_DEFUN(PETIG_CHECK_BARCOLIB,
[
PETIG_CHECK_LIB(barco,barcolib,BARCOLIB) 
])
