# $Id: Makefile.am,v 1.1 2006/01/08 08:46:09 christof Exp $

AM_CPPFLAGS=@COMMONXX_INCLUDES@ -I../..

AM_LDFLAGS=@COMMONXX_LDFLAGS@ -L..

CLEANFILES = *~ test*.magus

EXTRA_PROGRAMS= test1

test1_LDADD=@COMMONXX_LIBS@ -lmagus
test1_SOURCES=test1.cc
