# $Id: Makefile.am,v 1.19 2003/05/09 08:19:10 christof Exp $

AM_CPPFLAGS = @CPPFLAGS@ @COMMONXX_INCLUDES@ $(WIN_INCLUDES) -I.. \
	@SIGC_CFLAGS@ -DSIGC1_2

AM_LDFLAGS = @COMMONXX_LDFLAGS@ $(LINK_OPTIONS)

CLEANFILES = *~

EXTRA_PROGRAMS= test

test_SOURCES=test.cc

noinst_LIBRARIES=libmagus.a

libmagus_a_SOURCES=MidgardBasicElement.cc Zauber.cc KiDo.cc \
	Zauberwerk.cc Land.cc Waffe.cc WaffeGrund.cc Sinne.cc \
	Typen.cc Schrift.cc Ruestung.cc Beruf.cc Fertigkeiten_angeboren.cc \
	Fertigkeiten.cc Sprache.cc Spezies.cc Abenteurer_besitz.cc \
	Ausruestung.cc dtos1.cc Windows_Linux.cc magus_paths.cc \
	Datenbank.cc Grad_anstieg.cc \
	Grundwerte.cc LernListen.cc Lernschema.cc Preise.cc Prototyp2.cc \
	Prototyp.cc Prozente100.cc  Ruestung.cc Spezialgebiet.cc \
	xml.cc Region.cc Optionen.cc Abenteurer.cc magustrace.cc

test_LDADD = libmagus.a @COMMONXX_LIBS@ @SIGC_LIBS@
