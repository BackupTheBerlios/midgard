# $Id: Makefile.am,v 1.177 2002/06/24 09:00:52 christof Exp $

bin_PROGRAMS = magus
noinst_PROGRAMS = text2c

if WINDOWS
PORT_FILES=magus.rc registry.cc
#LINK_OPTIONS=-mwindows
LINK_OBJS=magus_res.o
# sigh! local installation menace
WIN_INCLUDES=-I/usr/local/mingw/mingw32/include

magus_res.o: magus.rc ; windres --include-dir /usr/local/mingw/mingw32/include  magus.rc magus_res.o

else
PORT_FILES= xml_fileselection_glade.cc
LINK_OPTIONS=
LINK_OBJS=
WIN_INCLUDES=
endif

pkgdata_DATA = midgard_document_eingabe.tex \
    drache.png schwert.png wurfbeil.png MAGUS-Logo-grey2.png

EXTRA_DIST = midgard_document_eingabe.tex.in \
      drache.png  schwert.png wurfbeil.png MAGUS-Logo-grey2.png


noinst_HEADERS = \
   customize_toolbars.h \
   class_AbenteurerListe.hh \
   Abenteurer.hh \
   LernListen.hh \
   LaTeX_drucken.hh \
   table_beschreibung.hh \
   table_beschreibung_glade.hh \
   table_grundwerte.hh \
   table_grundwerte_glade.hh \
   table_ausruestung.hh \
   table_ausruestung_glade.hh \
   Wizard.hh \
   table_optionen.hh \
   table_optionen_glade.hh \
   frame_globale_optionen.hh \
   frame_globale_optionen_glade.hh \
   frame_drucken.hh \
   frame_drucken_glade.hh \
   frame_ansicht.hh \
   frame_ansicht_glade.hh \
   Optionen.hh \
   Midgard_Undo.hh \
   Grad_anstieg.hh \
   MidgardBasicTree.hh \
   MidgardBasicElement.hh \
   Region.hh \
   Zauber.hh \
   Zauberwerk.hh \
   Beruf.hh \
   Fertigkeiten.hh \
   Fertigkeiten_angeboren.hh \
   Waffe.hh \
   KiDo.hh \
   Land.hh \
   Grundwerte.hh \
   Sinne.hh \
   Ruestung.hh \
   Spezialgebiet.hh \
   Lernschema.hh \
   Preise.hh dtos1.h \
WaffeGrund.hh Fertigkeiten_angeboren.hh zufall.h \
glademm_support.hh \
midgard_CG_glade.hh midgard_CG.hh  \
WindowInfo_glade.hh WindowInfo.hh \
   Window_hilfe_glade.hh \
   Window_hilfe.hh \
	Midgard_Info_glade.hh \
	Midgard_Info.hh \
   Tag.hh TagStream.hh \
   Window_doppelcharaktere.hh \
   Window_doppelcharaktere_glade.hh \
   xml_fileselection_glade.hh \
   xml_fileselection.hh \
   class_lernpunkte.hh \
   class_SimpleTree.hh \
   class_SimpleTree_LernschemaZusatz.hh \
   Spezies.hh \
   Typen.hh \
   ProgressBar.h \
   table_lernschema.hh \
   table_lernschema_glade.hh \
   Data_waffenbesitz.hh

BUILT_SOURCES= registry.h text2c NEWS.h

registry.h: ../win32/registry.h ; ln -sf ../win32/$@ .
registry.cc: ../win32/registry.cc ; ln -sf ../win32/$@ .
NEWS.h: ../NEWS ; ./text2c <../NEWS >NEWS.h

magus_SOURCES = $(PORT_FILES) \
   customize_toolbars.cc \
   Abenteurer.cc \
   midgard_CG_AbenteurerListe.cc \
   table_steigern_gold.cc \
   table_steigern_waffenbesitz.cc \
   table_steigern_ruestung.cc \
   table_steigern.cc \
   table_steigern_glade.hh \
   table_steigern_glade.cc \
   table_steigern.hh \
   table_steigern_EP.cc \
   table_steigern_fertigkeiten.cc \
   table_steigern_kido.cc \
   table_steigern_main.cc \
   table_steigern_sprache.cc \
   table_steigern_waffen.cc \
   table_steigern_zauber.cc \
   table_steigern_grad_anstieg.cc \
   table_ausruestung.cc \
   table_ausruestung_glade.cc \
   table_lernschema_kido.cc \
   table_lernschema_fertigkeiten.cc \
   table_lernschema_waffen.cc \
   table_lernschema_zauber.cc \
   table_lernschema.cc \
   table_lernschema_glade.cc \
   table_lernschema_zusatz.cc \
   table_lernschema_beruf.cc \
   LaTeX_drucken.cc \
   LaTeX_drucken_ausruestung.cc \
   LaTeX_drucken_beschreibung.cc \
   LaTeX_drucken_spielleiterbogen.cc \
   table_beschreibung.cc \
   table_beschreibung_glade.cc \
   midgard_CG_oberflaeche.cc \
   midgard_CG_main.cc \
   midgard_CG_new.cc \
   Wizard.cc \
   frame_globale_optionen.cc \
   Optionen.cc \
   table_optionen.cc \
   table_optionen_glade.cc \
   frame_drucken.cc \
   frame_ansicht.cc \
   frame_globale_optionen_glade.cc \
   frame_drucken_glade.cc \
   frame_ansicht_glade.cc \
   midgard_CG_undo.cc \
   midgard_CG_wizard.cc \
	load_charakter.cc  \
   save_charakter.cc \
	Fertigkeiten_angeboren.cc \
   Typen.cc \
   Spezies.cc \
   Region.cc \
   Lernschema.cc \
   Zauber.cc \
   Schrift.cc \
   Sprache.cc \
   KiDo.cc \
   Waffe.cc \
   Fertigkeiten.cc \
   Zauberwerk.cc \
   Land.cc \
   WaffeGrund.cc \
   Ruestung.cc \
   Spezialgebiet.cc \
   Grad_anstieg.cc \
   Beruf.cc \
   Preise.cc \
   Sinne.cc \
   Grundwerte.cc \
	table_grundwerte_gw_wuerfeln.cc \
   table_grundwerte.cc \
   table_grundwerte_glade.cc \
   table_grundwerte_typauswahl.cc \
   MidgardBasicTree.cc \
   MidgardBasicElement.cc \
   table_steigern_midgard_basic_elemente.cc \
   midgard_CG_menu.cc \
   xml_fileselection.cc \
   spielleiter_export.cc \
   midgard_CG_region_check.cc \
   midgard_CG_optionen.cc \
   Window_hilfe_glade.cc \
   Window_hilfe.cc \
   glademm_support.cc \
	Midgard_Info_glade.cc \
	Midgard_Info.cc \
	midgard.cc \
   midgard_CG_drucken.cc \
	midgard_CG_glade.cc \
	midgard_CG.cc \
	table_grundwerte_abge_werte.cc \
   table_grundwerte_grundwere_edit.cc \
   WindowInfo.cc \
   WindowInfo_glade.cc \
   Window_doppelcharaktere.cc \
   Window_doppelcharaktere_glade.cc \
   Datenbank.cc class_SimpleTree.cc \
   dtos1.cc snprintf.c \
   Midgard_Undo.cc \
   Tag.cc TagStream.cc xml.cc export_common.cc \
   ProgressBar.cc 

CXXFLAGS = @CXXFLAGS@ 
CPPFLAGS = @CPPFLAGS@ @KOMPONENTEN_INCLUDES@ -DUSE_XML \
           -DPACKAGE_DATA_DIR=\"$(pkgdatadir)/\" $(WIN_INCLUDES) -I..

magus_LDADD = $(LINK_OBJS) @LIBS@ @KOMPONENTEN_NODB_LIBS@

LDFLAGS = @KOMPONENTEN_LDFLAGS@ $(LINK_OPTIONS)

CLEANFILES = *~ *_new $(BUILT_SOURCES) *_old

#
# the following lines are to support UTF8 recoding while compiling
# and dependancy tracking for both automake 1.4 (.P) and
# automake 1.5 (.Po). 
#

if UTF8

# convert to utf8 between preprocessing and compilation
%.o: %.cc
	$(CXXCPP) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) \
		$(AM_CXXFLAGS) $(CXXFLAGS) -Wp,-MD,.deps/$(*F).pp $*.cc \
	| ./iso2utf8 \
	| $(CXXCOMPILE) -o $*.o -c -x c++ /dev/stdin
	@-cp .deps/$(*F).pp .deps/$(*F).P; \
	tr ' ' '\012' < .deps/$(*F).pp \
	| sed -e 's/^\\$$//' -e '/^$$/ d' -e '/:$$/ d' -e 's/$$/ :/' \
	>> .deps/$(*F).P; \
	cp .deps/$(*F).P .deps/$(*F).Po ; \
	rm .deps/$(*F).pp

endif

