# $Id: Makefile.am,v 1.63 2001/11/03 17:18:38 thoma Exp $

bin_PROGRAMS = midgard midgard_xmlexport midgard_xmlimport


pkgdata_DATA = document_eingabe.tex \
   latexwertedef.tex charakter_beschreibung.tex axt1.ps \
   drache.ps dracher.ps

EXTRA_DIST = document_eingabe.tex.in \
   latexwertedef.tex charakter_beschreibung.tex axt1.ps \
   drache.ps dracher.ps


noinst_HEADERS = \
   MidgardBasicElement.hh \
   Zauber.hh \
   Zauberwerk.hh \
   Fertigkeiten.hh \
   Waffe.hh \
   KiDo.hh \
   Ausnahmen.hh \
   Land.hh \
   Grundwerte.hh \
WaffeGrund.hh Fertigkeiten_angeboren.hh Pflicht.hh itos.h zufall.h Berufe_auswahl_glade.hh Berufe_auswahl.hh \
Fertigkeiten_auswahl_glade.hh Fertigkeiten_auswahl.hh glademm_support.hh \
midgard_CG_glade.hh midgard_CG.hh Waffen_auswahl_glade.hh Waffen_auswahl.hh   \
Window_charakter_auswahl_glade.hh Window_charakter_auswahl.hh  \
Window_charakter_beschreibung_glade.hh Window_charakter_beschreibung.hh \
WindowInfo_glade.hh WindowInfo.hh Window_lernpunkte_editieren_glade.hh  \
Window_lernpunkte_editieren.hh Window_werte_editieren_glade.hh \
Window_werte_editieren.hh Zauber_auswahl_glade.hh Zauber_auswahl.hh \
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
   class_kido.hh \
   class_waffen.hh \
   class_berufe.hh \
   class_lernpunkte.hh \
   class_zauber.hh \
   class_fertigkeiten.hh \
   class_sprache_schrift.hh \
   class_spezies.hh \
   class_typen.hh \
   Window_Erfahrungspunkte.hh \
   Window_Erfahrungspunkte_glade.hh

%.cc: %.pgcc ; @ECPG@ -o $*.cc $<

BUILT_SOURCES_CG =  \
   Zauber.cc \
   Zauberwerk.cc \
   Fertigkeiten.cc \
   Waffe.cc \
   KiDo.cc \
   Sprache.cc \
   Schrift.cc \
   MidgardBasicElement_sql.cc \
   Pflicht.cc \
   Ausnahmen.cc \
   Land.cc \
   WaffeGrund.cc Fertigkeiten_angeboren.cc \
   steigern_waffen.cc \
   get_spezies_constraint.cc Fertigkeiten_auswahl.cc Waffen_auswahl.cc \
   Zauber_auswahl.cc  \
   Berufe_auswahl.cc \
   save_charakter.cc  load_charakter.cc  \
   get_typ.cc  Window_charakter_auswahl.cc \
   praxispunkte_wuerfeln.cc sprachen_schrift.cc \
   Sprache_auswahl.cc midgard_CG_ruestung.cc \
	Window_ruestung.cc Window_waffe.cc Window_Waffenbesitz.cc \
   get_berufs_vorteile.cc \
   midgard_CG_typauswahl.cc \
	KiDo_auswahl.cc \
   midgard_CG_magier_spezialgebiet.cc \
   steigern_EP_sql.cc \
   midgard_CG_grad_anstieg_sql.cc \
   class_grad_anstieg_sql.cc

BUILT_SOUCES_XMLE=xmlexport.cc
BUILT_SOUCES_XMLI=xmlimport.cc

BUILT_SOURCES= $(BUILT_SOURCES_CG) $(BUILT_SOUCES_XMLE) $(BUILT_SOUCES_XMLI)

midgard_xmlexport_SOURCES= $(BUILT_SOUCES_XMLE)
midgard_xmlimport_SOURCES= $(BUILT_SOUCES_XMLI) Tag.cc TagStream.cc


midgard_SOURCES = \
   MidgardBasicElement.cc \
   midgard_CG_basic_elemente.cc \
   $(BUILT_SOURCES_CG) \
   Window_herkunft.cc \
   steigern_fertigkeiten.cc  \
   steigern_sprache.cc  \
   steigern_zauber.cc  \
   steigern_kido.cc  \
   midgard_CG_menu.cc \
   Window_angeb_fert.cc \
   Window_Erfahrungspunkte.cc \
   Window_Erfahrungspunkte_glade.cc \
   steigern_EP.cc \
   midgard_CG_standard.cc \
   xml_fileselection.cc \
   xml_fileselection_glade.cc \
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
   midgard_CG_attribut_check.cc \
   Window_herkunft_glade.cc \
   midgard_CG_lernen.cc \
   Window_charakter_auswahl_glade.cc \
   Window_charakter_beschreibung_glade.cc \
   Window_charakter_beschreibung.cc \
   Fertigkeiten_auswahl_glade.cc \
   Waffen_auswahl_glade.cc \
   Zauber_auswahl_glade.cc \
   Berufe_auswahl_glade.cc \
   midgard_CG_grad_anstieg.cc \
	midgard_CG_glade.cc \
	midgard_CG.cc \
	Window_werte_editieren_glade.cc \
	Window_werte_editieren.cc \
	abge_werte_setzen.cc \
	gw_wuerfeln.cc \
   zeige_werte.cc \
   midgard_CG_fertigkeiten.cc\
   midgard_CG_waffen.cc\
   midgard_CG_zauber.cc\
   midgard_CG_beruf.cc\
	Window_lernpunkte_editieren_glade.cc \
	Window_lernpunkte_editieren.cc \
	Window_Waffe_Geld_glade.cc \
	Window_Waffe_Geld.cc \
	Window_Geld_eingeben_glade.cc \
	Window_Geld_eingeben.cc \
   grundwere_edit_setzen.cc \
   WindowInfo.cc \
   WindowInfo_glade.cc \
   itos.cc \
   Window_doppelcharaktere.cc \
   Window_doppelcharaktere_glade.cc


CXXFLAGS = @CXXFLAGS@ @KOMPONENTEN_INCLUDES@ \
           -DPACKAGE_DATA_DIR=\"$(pkgdatadir)/\"

midgard_LDADD = @LIBS@ @KOMPONENTEN_LIBS@


midgard_xmlexport_LDADD = @LIBS@ @COMMONXX_LIBS@
midgard_xmlimport_LDADD = @LIBS@ @COMMONXX_LIBS@

LDFLAGS = @KOMPONENTEN_LDFLAGS@

CLEANFILES = *~ *_new $(BUILT_SOURCES) *_old

# midgard_CG_glade.cc nicht optimieren, sonst explodiert der
# Speicherverbrauch
midgard_CG_glade.o: midgard_CG_glade.cc
	$(CXXCOMPILE) -O0 -c $<
