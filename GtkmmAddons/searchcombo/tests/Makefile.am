# $Id: Makefile.am,v 1.4 2002/09/20 10:28:07 christof Exp $

noinst_PROGRAMS = gsc_test

INCLUDES = -I../src @GTK_CFLAGS@

#LDFLAGS = @GTK_LDFLAGS@

LIBS = $(top_srcdir)/src/libGtkmmAddonsWidgets.a @GTK_LIBS@

gsc_test_DEPENDENCIES = $(top_srcdir)/src/libGtkmmAddonsWidgets.a

gsc_test_SOURCES = gsc_test.c

