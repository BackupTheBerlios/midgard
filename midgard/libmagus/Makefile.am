# $Id: Makefile.am,v 1.9 2003/05/07 09:24:53 christof Exp $

AM_CPPFLAGS = @CPPFLAGS@ @COMMONXX_INCLUDES@ $(WIN_INCLUDES) -I.. \
	@COMMONGTK2_INCLUDES@

AM_LDFLAGS = @COMMONXX_LDFLAGS@ $(LINK_OPTIONS)

CLEANFILES = *~

EXTRA_PROGRAMS= test

test_SOURCES=test.cc

noinst_LIBRARIES=libmagus.a

libmagus_a_SOURCES=MidgardBasicElement.cc Zauber.cc KiDo.cc \
	Zauberwerk.cc Land.cc Waffe.cc WaffeGrund.cc Sinne.cc \
	Typen.cc Schrift.cc Ruestung.cc Beruf.cc Fertigkeiten_angeboren.cc \
	Fertigkeiten.cc
