# $Id: Makefile.am,v 1.37 2003/09/04 07:41:32 christof Exp $

AM_CPPFLAGS = @COMMONXX_INCLUDES@ $(WIN_INCLUDES) -I.. \
	@XMLPP_CFLAGS@ @COMMONGTK2_INCLUDES@

AM_LDFLAGS = @COMMONXX_LDFLAGS@ @COMMONGTK2_LDFLAGS@

CLEANFILES = *~

EXTRA_PROGRAMS= test readxml readxml2 Zufallscharakter

registry.h: ../win32/registry.h ; ln -sf ../win32/$@ .
registry.cc: ../win32/registry.cc ; ln -sf ../win32/$@ .

if WINDOWS
PORT_FILES=registry.cc
else
PORT_FILES=
endif

test_SOURCES=test.cc
Zufallscharakter_SOURCES=Zufallscharakter.cc
readxml_SOURCES=readxml.cc
readxml2_SOURCES=readxml2.cc

lib_LTLIBRARIES=libmagus.la

EXTRA_QUELLEN=Abenteurer_steigern.cc LernListen_steigern.cc KI.cc \
	LaTeX_drucken_ausruestung.cc LaTeX_drucken.cc \
	LaTeX_drucken_beschreibung.cc LaTeX_drucken_spielleiterbogen.cc \
	grundwerte_abge_werte.cc grundwerte_gw_wuerfeln.cc \
	Zufall.cc Zufall_Lernschema.cc Zufall_Spezies_Typ.cc \
	spielleiter_export.cc Magus_Optionen.cc AbenteurerLernpunkte.cc \
	Undo.cc VAbenteurer.cc zufall_steigern.cc VAbentModelProxy.cc

libmagus_la_SOURCES=MidgardBasicElement.cc Zauber.cc KiDo.cc \
	Zauberwerk.cc Land.cc Waffe.cc WaffeGrund.cc Sinne.cc \
	Typen.cc Schrift.cc Ruestung.cc Beruf.cc Fertigkeiten_angeboren.cc \
	Fertigkeiten.cc Sprache.cc Spezies.cc Abenteurer_besitz.cc \
	Ausruestung.cc dtos1.cc Windows_Linux.cc magus_paths.cc \
	Datenbank.cc Grad_anstieg.cc \
	Grundwerte.cc LernListen.cc Preise.cc Prototyp2.cc \
	Prototyp.cc Prozente100.cc  Spezialgebiet.cc \
	xml.cc Region.cc Optionen.cc Abenteurer.cc magustrace.cc \
	Lernschema.cc Ausgabe.cc snprintf.c $(PORT_FILES) \
	$(EXTRA_QUELLEN) Random.cc libmagus.cc

test_LDADD = libmagus.la @COMMONXX_LIBS@ @SIGC_LIBS@
Zufallscharakter_LDADD = libmagus.la @COMMONGTK2_ONLY@ @COMMONXX_LIBS@ @SIGC_LIBS@ 
readxml_LDADD = @COMMONXX_LIBS@ @SIGC_LIBS@
readxml2_LDADD = @XMLPP_LIBS@

BUILT_SOURCES= registry.h
