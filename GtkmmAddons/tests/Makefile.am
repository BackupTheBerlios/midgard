# $Id: Makefile.am,v 1.8 2002/01/21 08:32:02 christof Exp $

SUBDIRS=close_window

CXXFLAGS=-I$(top_srcdir)/searchcombo/src -I$(top_srcdir)/src @CFLAGS@

noinst_PROGRAMS = clist os_list tclist tree nsc_test sccont_test optionmenu

clist_SOURCES = clist.cc

sccont_test_SOURCES = sccont_test.cc
sccont_test_LDADD = $(top_srcdir)/src/lib@LIBNAME@.a

nsc_test_SOURCES = nsc_test.cc
nsc_test_LDADD = $(top_srcdir)/src/lib@LIBNAME@.a

os_list_SOURCES = os_list.cc
os_list_LDADD = $(top_srcdir)/src/lib@LIBNAME@.a

tclist_SOURCES = tclist.cc
tclist_LDADD = $(top_srcdir)/src/lib@LIBNAME@.a

tree_SOURCES = tree.cc
tree_LDADD = $(top_srcdir)/src/lib@LIBNAME@.a

optionmenu_SOURCES = optionmenu.cc
optionmenu_LDADD = $(top_srcdir)/src/lib@LIBNAME@.a

INCLUDES = -I$(top_srcdir)/searchcombo/src -I$(top_srcdir)/src @GTKMM_CFLAGS@ 
LDFLAGS = @GTKMM_LIBS@

