# $Id: Makefile.am,v 1.3 2006/01/08 08:46:50 christof Exp $

AM_CPPFLAGS=@COMMONXX_INCLUDES@ -I../..

AM_LDFLAGS=@COMMONXX_LDFLAGS@ @COMMONGTK2_LDFLAGS@ -L..

CLEANFILES = *~ test*.magus

EXTRA_PROGRAMS= test1 test2 test3

test1_LDADD=@COMMONXX_LIBS@ -lmagus @COMMONGTK2_ONLY@
test1_SOURCES=test1.cc
test2_LDADD=$(test1_LDADD)
test2_SOURCES=test2.cc
test3_LDADD=$(test1_LDADD)
test3_SOURCES=test3.cc
