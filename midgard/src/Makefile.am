# $Id: Makefile.am,v 1.116 2002/02/12 11:22:44 thoma Exp $

bin_PROGRAMS = midgard 


# völlig veraltet!!!
EXTRA_PROGRAMS = midgard_xmlexport

pkgdata_DATA = document_eingabe.tex document_eingabe4.tex \
   charakter_beschreibung.tex axt1.ps \
   drache.ps drache.ps

EXTRA_DIST = document_eingabe.tex.in document_eingabe4.tex.in \
    charakter_beschreibung.tex axt1.ps \
   drache.ps


noinst_HEADERS = \
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
   Ausnahmen.hh \
   Land.hh \
   Grundwerte.hh \
   Ruestung.hh \
   Spezialgebiet.hh \
   Lernschema.hh \
   Preise.hh dtos1.h \
WaffeGrund.hh Fertigkeiten_angeboren.hh Pflicht.hh zufall.h Berufe_auswahl_glade.hh Berufe_auswahl.hh \
glademm_support.hh \
midgard_CG_glade.hh midgard_CG.hh  \
Window_charakter_beschreibung_glade.hh Window_charakter_beschreibung.hh \
WindowInfo_glade.hh WindowInfo.hh \
Sprache_auswahl.hh Sprache_auswahl_glade.hh \
   Window_herkunft_glade.hh \
   Window_herkunft.hh \
   Window_hilfe_glade.hh \
   Window_hilfe.hh \
	Window_Waffe_Geld_glade.hh \
	Window_Waffe_Geld.hh \
	Window_Geld_eingeben_glade.hh \
	Window_Geld_eingeben.hh \
	Window_ruestung_glade.hh \
	Window_ruestung.hh \
	Window_waffe_glade.hh \
	Window_waffe.hh \
	Window_Waffenbesitz_glade.hh \
	Window_Waffenbesitz.hh \
	Window_angeb_fert_glade.hh \
	Window_angeb_fert.hh \
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
   Spezies.hh \
   Typen.hh \
   Window_Erfahrungspunkte.hh \
   Window_Erfahrungspunkte_glade.hh \
   ProgressBar.h

BUILT_SOURCES= export_common.h

export_common.cc: ../xml/export_common.cc ; ln -sf ../xml/$@ .
export_common.h: ../xml/export_common.h ; ln -sf ../xml/$@ .

midgard_xmlexport_SOURCES= xmlexport.cc export_common.cc

midgard_SOURCES = \
	load_charakter.cc  \
   save_charakter.cc \
	Fertigkeiten_angeboren.cc \
   Ausnahmen.cc \
   Pflicht.cc \
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
   Grundwerte.cc \
	gw_wuerfeln.cc \
   midgard_CG_Ausruestung.cc \
   Berufe_auswahl.cc \
	KiDo_auswahl.cc \
	Window_Waffenbesitz.cc \
   Window_waffe.cc \
   midgard_CG_typauswahl.cc \
   MidgardBasicTree.cc \
   MidgardBasicElement.cc \
   midgard_CG_basic_elemente.cc \
   Window_herkunft.cc \
   Window_ruestung.cc \
   Sprache_auswahl.cc \
   steigern_fertigkeiten.cc  \
   steigern_waffen.cc \
   steigern_sprache.cc  \
   steigern_zauber.cc  \
   steigern_kido.cc  \
   midgard_CG_menu.cc \
   Window_angeb_fert.cc \
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
	Window_angeb_fert_glade.cc \
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
   Sprache_auswahl_glade.cc \
   Window_herkunft_glade.cc \
   midgard_CG_lernen.cc \
   Window_charakter_auswahl_glade.cc \
   Window_charakter_beschreibung_glade.cc \
   Window_charakter_beschreibung.cc \
   Berufe_auswahl_glade.cc \
   midgard_CG_grad_anstieg.cc \
	midgard_CG_glade.cc \
	midgard_CG.cc \
	abge_werte_setzen.cc \
   zeige_werte.cc \
   midgard_CG_fertigkeiten.cc\
   midgard_CG_zauber.cc\
   midgard_CG_beruf.cc\
	Window_Waffe_Geld_glade.cc \
	Window_Waffe_Geld.cc \
	Window_Geld_eingeben_glade.cc \
	Window_Geld_eingeben.cc \
   grundwere_edit_setzen.cc \
   WindowInfo.cc \
   WindowInfo_glade.cc \
   Window_doppelcharaktere.cc \
   Window_doppelcharaktere_glade.cc \
   Datenbank.cc class_SimpleTree.cc \
   dtos1.cc snprintf.c \
   Tag.cc TagStream.cc xml.cc export_common.cc \
   ProgressBar.cc

CXXFLAGS = @CXXFLAGS@ @KOMPONENTEN_INCLUDES@ -DUSE_XML \
           -DPACKAGE_DATA_DIR=\"$(pkgdatadir)/\"

midgard_LDADD = @LIBS@ @KOMPONENTEN_LIBS@

midgard_xmlexport_LDADD = @LIBS@ @COMMONXX_LIBS@

LDFLAGS = @KOMPONENTEN_LDFLAGS@

CLEANFILES = *~ *_new $(BUILT_SOURCES) *_old

midgard_CG_glade_o_DEPS=midgard_CG_glade.cc ../config.h midgard_CG.hh \
	midgard_CG_glade.hh 
	# und vieles mehr !!!

if UTF8

%.o: %.cc
	$(CPP) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) \
	$(AM_CXXFLAGS) $(CXXFLAGS) $*.cc | ./iso2utf8 | \
	$(CXXCOMPILE) -o $*.o -c -x c++ /dev/stdin
midgard_CG_glade.o: $(midgard_CG_glade_o_DEPS)
	$(CPP) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) \
	$(AM_CXXFLAGS) $(CXXFLAGS) $*.cc | ./iso2utf8 | \
	$(CXXCOMPILE) -o $*.o -O0 -c -x c++ /dev/stdin

#black magic to make it cross compile with MinGW under Linux

midgard_exe_LIBS=-lManuProC_Widgets -lManuProC_Base -lGtkmmAddons \
	 -lgtkmm -lgdkmm -lsigc \
	 -lgtk-1.3 -lgdk-1.3 -lglib-1.3 -lgmodule-1.3 -lgobject-1.3
	
midgard_LDFLAGS=-L../../ManuProC_Base/src -L../../GtkmmAddons/src \
	-L../../ManuProc_Widgets/src -L/usr/local/mingw/local/lib


midgard.exe: $(midgard_OBJECTS) $(midgard_DEPENDENCIES)
	@rm -f midgard$(EXEEXT)
	$(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) $(LDFLAGS) \
	  -o $@ $(midgard_LDFLAGS) $(midgard_OBJECTS) $(midgard_exe_LIBS)

else

# midgard_CG_glade.cc nicht optimieren, sonst explodiert der
# Speicherverbrauch (>344MB am 2002-1-31)
midgard_CG_glade.o: $(midgard_CG_glade_o_DEPS)
	$(CXXCOMPILE) -O0 -c $<
	echo > .deps/$(*F).P

endif
