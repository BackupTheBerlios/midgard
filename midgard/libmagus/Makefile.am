# $Id: Makefile.am,v 1.22 2003/05/16 15:06:51 christof Exp $

AM_CPPFLAGS = @CPPFLAGS@ @COMMONXX_INCLUDES@ $(WIN_INCLUDES) -I.. \
	@SIGC_CFLAGS@ -DSIGC1_2 @XMLPP_CFLAGS@

AM_LDFLAGS = @COMMONXX_LDFLAGS@ 

CLEANFILES = *~

EXTRA_PROGRAMS= test readxml readxml2

test_SOURCES=test.cc
readxml_SOURCES=readxml.cc
readxml2_SOURCES=readxml2.cc

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
readxml_LDADD = @COMMONXX_LIBS@ @SIGC_LIBS@
readxml2_LDADD = @XMLPP_LIBS@
