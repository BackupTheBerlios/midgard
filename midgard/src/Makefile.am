# generated 2001/2/2 12:25:52 CET by thoma@ig23.
# using glademm V0.5_11c
#
# newer (non customized) versions of this file go to Makefile.am_glade
bin_PROGRAMS = midgard


pkgdata_DATA = document_eingabe.tex \
   latexwertedef.tex charakter_beschreibung.tex axt1.ps \
   drache.ps dracher.ps

EXTRA_DIST = document_eingabe.tex.in \
   latexwertedef.tex charakter_beschreibung.tex axt1.ps \
   drache.ps dracher.ps


noinst_HEADERS = itos.h zufall.h Berufe_auswahl_glade.hh Berufe_auswahl.hh \
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
	Window_Waffenbesitz.hh 

%.cc: %.pgcc ; @ECPG@ -o $*.cc $<

BUILT_SOURCES = Fertigkeiten_auswahl.cc Waffen_auswahl.cc \
   Zauber_auswahl.cc  Zauber_get_daten.cc get_standard_zauber.cc \
   get_standard_fertigkeit.cc get_standard_waffen.cc Berufe_auswahl.cc \
   save_charakter.cc  load_charakter.cc  \
   steigern_zauber.cc steigern_fertigkeiten.cc steigern_waffen.cc \
   get_typ.cc get_spezial_zauber.cc  Window_charakter_auswahl.cc \
   praxispunkte_wuerfeln.cc steigern_sprache.cc sprachen_schrift.cc \
   Sprache_auswahl.cc Window_herkunft.cc midgard_CG_ruestung.cc \
	Window_ruestung.cc Window_waffe.cc Window_Waffenbesitz.cc \
   midgard_CG_waffe_werte.cc get_berufs_vorteile.cc \
   midgard_CG_typauswahl.cc




midgard_SOURCES = \
   $(BUILT_SOURCES) \
   midgard_CG_optionen.cc \
	Window_Waffenbesitz_glade.cc \
	Window_waffe_glade.cc \
	Window_ruestung_glade.cc \
   Window_hilfe_glade.cc \
   Window_hilfe.cc \
   glademm_support.cc \
	midgard.cc \
   Sprache_auswahl_glade.cc \
   midgard_CG_attribut_check.cc \
   Window_herkunft_glade.cc \
   midgard_CG_sprachen_schriften.cc \
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
   get_erfolgswert_zaubern.cc \
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
   LaTeX_out.cc \
   LaTeX_zauber.cc \
   LaTeX_charakter_beschreibung.cc \
   grundwere_edit_setzen.cc \
   WindowInfo.cc \
   WindowInfo_glade.cc \
   itos.cc 


CXXFLAGS = @CXXFLAGS@ @GTKMM_CFLAGS@ @COMMONXX_INCLUDES@ \
           @ECPG_INCLUDES@ @COMMONGTK_INCLUDES@ \
           -DPACKAGE_DATA_DIR=\"$(pkgdatadir)/\"

midgard_LDADD = @LIBS@ @COMMONXX_LIBS@ @ECPG_LIBS@ \
               @COMMONGTK_LIBS@ @GTKMM_LIBS@
