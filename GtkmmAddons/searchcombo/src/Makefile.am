# $Id: Makefile.am,v 1.3 2002/08/01 10:55:13 christof Exp $

CLEANFILES = *~

INCLUDES = @GTK_CFLAGS@ 

if INSTALL_WIDGET
  lib_lib=libGtkmmAddonsWidgets.a
  inc_hea=gtksearchcombo.h
else
  lib_lib=
  inc_hea=
endif

lib_LIBRARIES = $(lib_lib)
noinst_LIBRARIES = libGtkmmAddonsWidgets.a

include_HEADERS = $(inc_hea)
noinst_HEADERS = gtksearchcombo.h

libGtkmmAddonsWidgets_a_SOURCES = gtksearchcombo.c
