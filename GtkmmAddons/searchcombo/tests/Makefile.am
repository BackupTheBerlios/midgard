# $Id: Makefile.am,v 1.3 2001/04/20 07:29:20 christof Exp $

noinst_PROGRAMS = gsc_test

INCLUDES = -I../src @GTK_CFLAGS@

LDFLAGS = @GTK_LIBS@

LIBS = $(top_srcdir)/src/libGtkmmAddonsWidgets.a 

gsc_test_DEPENDENCIES = $(top_srcdir)/src/libGtkmmAddonsWidgets.a

gsc_test_SOURCES = gsc_test.c

