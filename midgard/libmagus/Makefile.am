# $Id: Makefile.am,v 1.2 2003/05/07 00:02:03 christof Exp $

AM_CPPFLAGS = @CPPFLAGS@ @COMMONXX_INCLUDES@ $(WIN_INCLUDES) -I.. \
	@COMMONGTK2_INCLUDES@

AM_LDFLAGS = @COMMONXX_LDFLAGS@ $(LINK_OPTIONS)

CLEANFILES = *~

EXTRA_PROGRAMS= test

test_SOURCES=test.cc

noinst_LIBRARIES=libmagus.a

libmagus_a_SOURCES=MidgardBasicElement.cc Zauber.cc
