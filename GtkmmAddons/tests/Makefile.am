# $Id: Makefile.am,v 1.10 2002/09/24 15:46:21 christof Exp $

SUBDIRS=close_window

CXXFLAGS=-I$(top_srcdir)/searchcombo/src -I$(top_srcdir)/src @CFLAGS@

noinst_PROGRAMS = nsc_test sccont_test optionmenu

sccont_test_SOURCES = sccont_test.cc
sccont_test_LDADD = $(top_srcdir)/src/libGtkmmAddons.a

nsc_test_SOURCES = nsc_test.cc
nsc_test_LDADD = $(top_srcdir)/src/libGtkmmAddons.a

optionmenu_SOURCES = optionmenu.cc
optionmenu_LDADD = $(top_srcdir)/src/libGtkmmAddons.a

INCLUDES = -I$(top_srcdir)/searchcombo/src -I$(top_srcdir)/src @GTKMM_CFLAGS@ 
LDFLAGS = @GTKMM_LIBS@

