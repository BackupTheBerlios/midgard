# $Id: Makefile.am,v 1.157 2002/05/09 10:37:55 christof Exp $

bin_PROGRAMS = magus
noinst_PROGRAMS = text2c

# völlig veraltet!!!
EXTRA_PROGRAMS = midgard_xmlexport

if WINDOWS
PORT_FILES=magus.rc registry.cc
LINK_OPTIONS=-mwindows
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
    drache.png dracher.png schwert.png wurfbeil.png MAGUS-Logo-grey2.png

EXTRA_DIST = midgard_document_eingabe.tex.in \
      drache.png  dracher.png schwert.png wurfbeil.png MAGUS-Logo-grey2.png


noinst_HEADERS = \
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
	Window_Geld_eingeben_glade.hh \
	Window_Geld_eingeben.hh \
	Window_ruestung_glade.hh \
	Window_ruestung.hh \
	Window_Waffenbesitz_glade.hh \
	Window_Waffenbesitz.hh \
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
   Window_Erfahrungspunkte.hh \
   Window_Erfahrungspunkte_glade.hh \
   ProgressBar.h

BUILT_SOURCES= export_common.h registry.h text2c NEWS.h

export_common.cc: ../xml/export_common.cc ; ln -sf ../xml/$@ .
export_common.h: ../xml/export_common.h ; ln -sf ../xml/$@ .
registry.h: ../win32/registry.h ; ln -sf ../win32/$@ .
registry.cc: ../win32/registry.cc ; ln -sf ../win32/$@ .
NEWS.h: ../NEWS ; ./text2c <../NEWS >NEWS.h

midgard_xmlexport_SOURCES= xmlexport.cc export_common.cc

magus_SOURCES = $(PORT_FILES) \
   midgard_CG_oberflaeche.cc \
   midgard_CG_waffen.cc \
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
	gw_wuerfeln.cc \
   midgard_CG_Ausruestung.cc \
	Window_Waffenbesitz.cc \
   midgard_CG_typauswahl.cc \
   MidgardBasicTree.cc \
   MidgardBasicElement.cc \
   midgard_CG_basic_elemente.cc \
   Window_ruestung.cc \
   steigern_fertigkeiten.cc  \
   steigern_waffen.cc \
   steigern_sprache.cc  \
   steigern_zauber.cc  \
   steigern_kido.cc  \
   midgard_CG_menu.cc \
   Window_Erfahrungspunkte.cc \
   Window_Erfahrungspunkte_glade.cc \
   steigern_main.cc \
   steigern_EP.cc \
   xml_fileselection.cc \
   LaTeX_header.cc \
	LaTeX_out.cc \
   LaTeX_zauber.cc \
   LaTeX_kido.cc \
   LaTeX_charakter_beschreibung.cc \
   spielleiter_export.cc \
   midgard_CG_kido.cc \
   midgard_CG_region_check.cc \
   midgard_CG_optionen.cc \
	Window_Waffenbesitz_glade.cc \
	Window_ruestung_glade.cc \
   Window_hilfe_glade.cc \
   Window_hilfe.cc \
   glademm_support.cc \
	Midgard_Info_glade.cc \
	Midgard_Info.cc \
	midgard.cc \
   midgard_CG_lernen.cc \
   midgard_CG_lernen_zusatz.cc \
   midgard_CG_beschreibung.cc \
   midgard_CG_grad_anstieg.cc \
	midgard_CG_glade.cc \
	midgard_CG.cc \
	abge_werte_setzen.cc \
   zeige_werte.cc \
   midgard_CG_fertigkeiten.cc\
   midgard_CG_zauber.cc\
   midgard_CG_beruf.cc\
	Window_Geld_eingeben_glade.cc \
	Window_Geld_eingeben.cc \
   grundwere_edit_setzen.cc \
   WindowInfo.cc \
   WindowInfo_glade.cc \
   Window_doppelcharaktere.cc \
   Window_doppelcharaktere_glade.cc \
   Datenbank.cc class_SimpleTree.cc \
   dtos1.cc snprintf.c \
   Midgard_Undo.cc \
   Tag.cc TagStream.cc xml.cc export_common.cc \
   ProgressBar.cc 

CXXFLAGS = @CXXFLAGS@ @KOMPONENTEN_INCLUDES@ -DUSE_XML \
           -DPACKAGE_DATA_DIR=\"$(pkgdatadir)/\" $(WIN_INCLUDES)

magus_LDADD = $(LINK_OBJS) @LIBS@ @KOMPONENTEN_NODB_LIBS@

midgard_xmlexport_LDADD = @LIBS@ @COMMONXX_LIBS@

LDFLAGS = @KOMPONENTEN_LDFLAGS@ $(LINK_OPTIONS)

CLEANFILES = *~ *_new $(BUILT_SOURCES) *_old

midgard_CG_glade_o_DEPS=midgard_CG_glade.cc ../config.h midgard_CG.hh \
	midgard_CG_glade.hh 

# und vieles mehr !!!

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
	rm .deps/$(*F).pp

midgard_CG_glade.o: $(midgard_CG_glade_o_DEPS)
	$(CXXCPP) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) \
		$(AM_CXXFLAGS) $(CXXFLAGS) -Wp,-MD,.deps/$(*F).pp $*.cc \
	| ./iso2utf8 \
	| $(CXXCOMPILE) -o $*.o -O0 -c -x c++ /dev/stdin
	@-cp .deps/$(*F).pp .deps/$(*F).P; \
	tr ' ' '\012' < .deps/$(*F).pp \
	| sed -e 's/^\\$$//' -e '/^$$/ d' -e '/:$$/ d' -e 's/$$/ :/' \
	>> .deps/$(*F).P; \
	rm .deps/$(*F).pp

else

# midgard_CG_glade.cc nicht optimieren, sonst explodiert der
# Speicherverbrauch (>344MB am 2002-1-31)
midgard_CG_glade.o: $(midgard_CG_glade_o_DEPS)
	$(CXXCOMPILE) -Wp,-MD,.deps/$(*F).pp -O0 -c $<
	@-cp .deps/$(*F).pp .deps/$(*F).P; \
	tr ' ' '\012' < .deps/$(*F).pp \
	| sed -e 's/^\\$$//' -e '/^$$/ d' -e '/:$$/ d' -e 's/$$/ :/' \
	>> .deps/$(*F).P; \
	rm .deps/$(*F).pp

endif

