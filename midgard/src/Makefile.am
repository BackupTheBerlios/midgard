# $Id: Makefile.am,v 1.139 2002/04/14 15:32:14 thoma Exp $

bin_PROGRAMS = midgard 
noinst_PROGRAMS = text2c

# völlig veraltet!!!
EXTRA_PROGRAMS = midgard_xmlexport

pkgdata_DATA = midgard_document_eingabe.tex \
    drache.png dracher.png schwert.png wurfbeil.png MAGUS-Logo-grey2.png

EXTRA_DIST = midgard_document_eingabe.tex.in \
      drache.png  dracher.png schwert.png wurfbeil.png MAGUS-Logo-grey2.png


noinst_HEADERS = \
   frame_drucken.hh \
   frame_drucken_glade.hh \
   Optionen.hh \
   Wizard_window.hh \
   Wizard_window_glade.hh \
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
	Window_waffe_glade.hh \
	Window_waffe.hh \
	Window_Waffenbesitz_glade.hh \
	Window_Waffenbesitz.hh \
	Midgard_Info_glade.hh \
	Midgard_Info.hh \
   KiDo_auswahl.hh \
   KiDo_auswahl_glade.hh \
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

BUILT_SOURCES= export_common.h text2c NEWS.h

export_common.cc: ../xml/export_common.cc ; ln -sf ../xml/$@ .
export_common.h: ../xml/export_common.h ; ln -sf ../xml/$@ .
NEWS.h: ../NEWS ; ./text2c <../NEWS >NEWS.h

midgard_xmlexport_SOURCES= xmlexport.cc export_common.cc

midgard_SOURCES = \
   frame_drucken.cc \
   frame_drucken_glade.cc \
   Optionen.cc \
   midgard_CG_undo.cc \
   Wizard_window.cc \
   Wizard_window_glade.cc \
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
	KiDo_auswahl.cc \
	Window_Waffenbesitz.cc \
   Window_waffe.cc \
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
   xml_fileselection_glade.cc \
   LaTeX_header.cc \
	LaTeX_out.cc \
   LaTeX_zauber.cc \
   LaTeX_kido.cc \
   LaTeX_charakter_beschreibung.cc \
   spielleiter_export.cc \
   midgard_CG_kido.cc \
   KiDo_auswahl_glade.cc \
   midgard_CG_region_check.cc \
   midgard_CG_optionen.cc \
	Window_Waffenbesitz_glade.cc \
	Window_waffe_glade.cc \
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
           -DPACKAGE_DATA_DIR=\"$(pkgdatadir)/\"

midgard_LDADD = @LIBS@ @KOMPONENTEN_NODB_LIBS@

midgard_xmlexport_LDADD = @LIBS@ @COMMONXX_LIBS@

LDFLAGS = @KOMPONENTEN_LDFLAGS@

CLEANFILES = *~ *_new $(BUILT_SOURCES) *_old

midgard_CG_glade_o_DEPS=midgard_CG_glade.cc ../config.h midgard_CG.hh \
	midgard_CG_glade.hh 
	# und vieles mehr !!!

if UTF8

# convert to utf8 between preprocessing and compilation
%.o: %.cc
	$(CXXCPP) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS) $*.cc \
	| ./iso2utf8 \
	| $(CXXCOMPILE) -o $*.o -c -x c++ /dev/stdin
	echo > .deps/$(*F).P
midgard_CG_glade.o: $(midgard_CG_glade_o_DEPS)
	$(CXXCPP) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS) $*.cc \
	| ./iso2utf8 \
	| $(CXXCOMPILE) -o $*.o -O0 -c -x c++ /dev/stdin
	echo > .deps/$(*F).P

# libtool does not work when cross compiling, so link directly
#midgard$(EXEEXT): $(midgard_OBJECTS) $(midgard_DEPENDENCIES)
#	@rm -f midgard$(EXEEXT)
#	$(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) $(LDFLAGS) \
#	  -o $@ $(midgard_LDFLAGS) $(midgard_OBJECTS) $(midgard_LDADD)

else

# midgard_CG_glade.cc nicht optimieren, sonst explodiert der
# Speicherverbrauch (>344MB am 2002-1-31)
midgard_CG_glade.o: $(midgard_CG_glade_o_DEPS)
	$(CXXCOMPILE) -O0 -c $<
	echo > .deps/$(*F).P

endif
