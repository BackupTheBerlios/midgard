# $Id: Makefile.am,v 1.2 2001/02/26 14:17:04 christof Exp $

CLEANFILES = *~

INCLUDES = @GTK_CFLAGS@ 

lib_lib=
inc_hea=

if INSTALL_WIDGET
  lib_lib+=libGtkmmAddonsWidgets.a
  inc_hea+=gtksearchcombo.h
endif

lib_LIBRARIES = $(lib_lib)
noinst_LIBRARIES = libGtkmmAddonsWidgets.a

include_HEADERS = $(inc_hea)
noinst_HEADERS = gtksearchcombo.h

libGtkmmAddonsWidgets_a_SOURCES = gtksearchcombo.c
