# $Id: Makefile.am,v 1.25 2003/07/18 06:38:01 christof Exp $

AM_CPPFLAGS = @CPPFLAGS@ @COMMONXX_INCLUDES@ $(WIN_INCLUDES) -I.. \
	@SIGC_CFLAGS@ -DSIGC1_2 @XMLPP_CFLAGS@

AM_LDFLAGS = @COMMONXX_LDFLAGS@ 

CLEANFILES = *~

EXTRA_PROGRAMS= test readxml readxml2

registry.h: ../win32/registry.h ; ln -sf ../win32/$@ .
registry.cc: ../win32/registry.cc ; ln -sf ../win32/$@ .

if WINDOWS
PORT_FILES=registry.cc
else
PORT_FILES=
endif

test_SOURCES=test.cc
readxml_SOURCES=readxml.cc
readxml2_SOURCES=readxml2.cc

noinst_LIBRARIES=libmagus.a

EXTRA_QUELLEN=Abenteurer_steigern.cc LernListen_steigern.cc KI.cc \
	LaTeX_drucken_ausruestung.cc LaTeX_drucken.cc \
	LaTeX_drucken_beschreibung.cc LaTeX_drucken_spielleiterbogen.cc \
	Zufall.cc Zufall_Lernschema.cc Zufall_Spezies_Typ.cc \
	spielleiter_export.cc 

libmagus_a_SOURCES=MidgardBasicElement.cc Zauber.cc KiDo.cc \
	Zauberwerk.cc Land.cc Waffe.cc WaffeGrund.cc Sinne.cc \
	Typen.cc Schrift.cc Ruestung.cc Beruf.cc Fertigkeiten_angeboren.cc \
	Fertigkeiten.cc Sprache.cc Spezies.cc Abenteurer_besitz.cc \
	Ausruestung.cc dtos1.cc Windows_Linux.cc magus_paths.cc \
	Datenbank.cc Grad_anstieg.cc \
	Grundwerte.cc LernListen.cc Preise.cc Prototyp2.cc \
	Prototyp.cc Prozente100.cc  Ruestung.cc Spezialgebiet.cc \
	xml.cc Region.cc Optionen.cc Abenteurer.cc magustrace.cc \
	Lernschema.cc Ausgabe.cc snprintf.c $(PORT_FILES) \
	$(EXTRA_QUELLEN)

test_LDADD = libmagus.a @COMMONXX_LIBS@ @SIGC_LIBS@
readxml_LDADD = @COMMONXX_LIBS@ @SIGC_LIBS@
readxml2_LDADD = @XMLPP_LIBS@

BUILT_SOURCES= registry.h
