# $Id: Makefile.am,v 1.15 2003/05/07 13:12:44 christof Exp $

AM_CPPFLAGS = @CPPFLAGS@ @COMMONXX_INCLUDES@ $(WIN_INCLUDES) -I.. \
	@COMMONGTK2_INCLUDES@

AM_LDFLAGS = @COMMONXX_LDFLAGS@ $(LINK_OPTIONS)

CLEANFILES = *~

EXTRA_PROGRAMS= test dummy

test_SOURCES=test.cc

noinst_LIBRARIES=libmagus.a

libmagus_a_SOURCES=MidgardBasicElement.cc Zauber.cc KiDo.cc \
	Zauberwerk.cc Land.cc Waffe.cc WaffeGrund.cc Sinne.cc \
	Typen.cc Schrift.cc Ruestung.cc Beruf.cc Fertigkeiten_angeboren.cc \
	Fertigkeiten.cc Sprache.cc Spezies.cc Abenteurer_besitz.cc \
	Ausruestung.cc dtos1.cc Windows_Linux.cc magus_paths.cc \
	Datenbank.cc Grad_anstieg.cc \
	Grundwerte.cc LernListen.cc Lernschema.cc Preise.cc Prototyp2.cc \
	Prototyp.cc Prozente100.cc  Ruestung.cc Spezialgebiet.cc 

dummy_SOURCES=xml.cc Abenteurer.cc Region.cc 
