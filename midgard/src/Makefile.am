# $Id: Makefile.am,v 1.235 2004/07/06 06:37:51 christof Exp $

bin_PROGRAMS = magus$(EXEEXT)
noinst_PROGRAMS = text2c$(EXEEXT)

if WINDOWS
PORT_FILES=magus.rc 
LINK_OPTIONS=-mwindows -Wl,--enable-runtime-pseudo-reloc
LINK_OBJS=magus_res.o 
# -lcomdlg32
# sigh! local installation menace
WIN_INCLUDES=
#-I/usr/local/mingw/mingw32/include -I/usr/local/mingw/local/include/gdk

#magus_res.o: magus.rc ; i586-mingw32msvc-windres --include-dir /usr/local/mingw2/include  magus.rc magus_res.o
magus_res.o: magus.rc
	WINDRES=i586-mingw32msvc-windres $(top_srcdir)/../ManuProC_Base/build/win32/compile-resource $< $@

else
PORT_FILES= xml_fileselection_glade.cc
LINK_OPTIONS=
LINK_OBJS=
WIN_INCLUDES=
endif

pkgdata_DATA = magus_document_eingabe.tex \
    drache.png schwert.png wurfbeil.png MAGUS-Logo-grey2.png \
   Alba-grey.png Letter-Feather-grey.png

EXTRA_DIST = midgard_document_eingabe.tex.in \
      drache.png  schwert.png wurfbeil.png MAGUS-Logo-grey2.png \
      Alba-grey.png Letter-Feather-grey.png 


noinst_HEADERS = \
   BegruessungsWindow_glade.hh \
   BegruessungsWindow.hh \
   customize_toolbars.h \
   class_AbenteurerListe.hh \
   table_beschreibung.hh \
   table_beschreibung_glade.hh \
   table_zufall.hh \
   table_zufall_glade.hh \
   table_grundwerte.hh \
   table_grundwerte_glade.hh \
   table_ausruestung.hh \
   table_ausruestung_glade.hh \
   table_optionen.hh \
   table_optionen_glade.hh \
   frame_globale_optionen.hh \
   frame_globale_optionen_glade.hh \
   frame_drucken.hh \
   frame_drucken_glade.hh \
   frame_ansicht.hh \
   frame_ansicht_glade.hh \
   frame_icons.hh \
   frame_icons_glade.hh \
   Midgard_Undo.hh \
   MidgardBasicTree.hh \
midgard_CG_glade.hh midgard_CG.hh  \
WindowInfo_glade.hh WindowInfo.hh \
	Midgard_Info.hh \
   Midgard_Info_glade.hh \
   xml_fileselection_glade.hh \
   xml_fileselection.hh \
   class_lernpunkte.hh \
   class_SimpleTree.hh \
   class_SimpleTree_LernschemaZusatz.hh \
   ProgressBar.h \
   table_lernschema.hh \
   table_lernschema_glade.hh \
   Data_waffenbesitz.hh \
   Data_NewPreis.hh

BUILT_SOURCES= text2c$(EXEEXT) NEWS.h

NEWS.h: ../NEWS ../TODO text2c$(EXEEXT)
	csplit --prefix tmp_news. ../NEWS '/<<<TODO>>>/'
	cat tmp_news.00 ../TODO tmp_news.0[1-9] | ./text2c | ./iso2utf8 >NEWS.h
	rm tmp_news.??

magus_SOURCES = $(PORT_FILES) \
   BegruessungsWindow.cc \
   BegruessungsWindow_glade.cc \
   table_zufall.cc \
   table_zufall_steigern.cc \
   table_zufall_lernschema.cc \
   table_zufall_glade.cc \
   customize_toolbars.cc \
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
   table_ausruestung_new_tree.cc \
   table_ausruestung_drag_and_drop.cc \
   table_ausruestung_glade.cc \
   table_lernschema_kido.cc \
   table_lernschema_fertigkeiten.cc \
   table_lernschema_waffen.cc \
   table_lernschema_zauber.cc \
   table_lernschema.cc \
   table_lernschema_glade.cc \
   table_lernschema_zusatz.cc \
   table_lernschema_beruf.cc \
   table_beschreibung.cc \
   table_beschreibung_glade.cc \
   midgard_CG_oberflaeche.cc \
   midgard_CG_main.cc \
   midgard_CG_new.cc \
   frame_globale_optionen.cc \
   Optionen_GUI.cc \
   table_optionen.cc \
   table_optionen_glade.cc \
   frame_icons.cc \
   frame_icons_glade.cc \
   frame_drucken.cc \
   frame_ansicht.cc \
   frame_globale_optionen_glade.cc \
   frame_drucken_glade.cc \
   frame_ansicht_glade.cc \
   midgard_CG_undo.cc \
   midgard_CG_wizard.cc \
	load_charakter.cc  \
   save_charakter.cc \
	table_grundwerte_gw_wuerfeln.cc \
   table_grundwerte.cc \
   table_grundwerte_glade.cc \
   table_grundwerte_typauswahl.cc \
   MidgardBasicTree.cc \
   table_steigern_midgard_basic_elemente.cc \
   midgard_CG_menu.cc \
   xml_fileselection.cc \
   midgard_CG_region_check.cc \
   midgard_CG_optionen.cc \
   midgard_CG_optionen_icons.cc \
	Midgard_Info.cc \
   Midgard_Info_glade.cc \
	midgard.cc \
   midgard_CG_drucken.cc \
	midgard_CG_glade.cc \
	midgard_CG.cc \
	table_grundwerte_abge_werte.cc \
   table_grundwerte_grundwere_edit.cc \
   WindowInfo.cc \
   WindowInfo_glade.cc \
   class_SimpleTree.cc \
   Midgard_Undo.cc \
   ProgressBar.cc \
   MagusDialog.cc MagusDialog_glade.cc \
   Region_GUI.cc MagusAusgabe.cc prop-editor.c

#AM_CXXFLAGS = @CXXFLAGS@ 
AM_CPPFLAGS = @KOMPONENTEN2_INCLUDES@ -DUSE_XML $(WIN_INCLUDES) \
	-I.. -I../libmagus

magus_LDADD = $(LINK_OBJS) -lmagusicons -lmagus @LIBS@ @KOMPONENTEN2_NODB_LIBS@

AM_LDFLAGS = @KOMPONENTEN2_LDFLAGS@ $(LINK_OPTIONS) -L../libmagusicons \
	-L../libmagus

CLEANFILES = *~ *_new $(BUILT_SOURCES) *_old

#AM_CXXFLAGS= -g -Wall
