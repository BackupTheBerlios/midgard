// generated 2002/5/5 22:30:25 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gcc_3.0/midgard/midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.8
//
// Please modify the corresponding derived classes in ./src/midgard_CG.hh and./src/midgard_CG.cc

#ifndef _MIDGARD_CG_GLADE_HH
#  define _MIDGARD_CG_GLADE_HH


#if !defined(GLADEMM_DATA)
#define GLADEMM_DATA 
#include <gtk--/accelgroup.h>

class GlademmData
{  
        
        Gtk::AccelGroup *accgrp;
public:
        
        GlademmData(Gtk::AccelGroup *ag) : accgrp(ag)
        {  
        }
        
        Gtk::AccelGroup * getAccelGroup()
        {  return accgrp;
        }
};
#endif //GLADEMM_DATA

#include <gtk--/window.h>
#include <gtk--/tooltips.h>
#include "Midgard_Info.hh"
#include <gtk--/pixmap.h>
#include <gtk--/label.h>
#include <gtk--/button.h>
#include <gtk--/table.h>
#include <gtk--/spinbutton.h>
#include <gtk--/entry.h>
#include <gtk--/optionmenu.h>
#include <gtk--/radiobutton.h>
#include <gtk--/box.h>
#include <gtk--/togglebutton.h>
#include <gtk--/frame.h>
#include "MidgardBasicTree.hh"
#include <gtk--/viewport.h>
#include <gtk--/scrolledwindow.h>
#include <gtk--/notebook.h>
#include <gtk--/scale.h>
#include <gtk--/checkbutton.h>
#include <gtk--/clist.h>
#include <gtk--/toolbar.h>
#include <gtk--/text.h>
#include "SimpleTree.hh"
#include "table_optionen.hh"
#include <gtk--/list.h>
#include <gtk--/handlebox.h>
#include <gtk--/menubar.h>

class midgard_CG_glade : public Gtk::Window
{  
        
        GlademmData *_data;
        Gtk::Tooltips _tooltips;
protected:
        class Midgard_Info *Midgard_Info;
        class Gtk::Pixmap *pixmap_logo;
        class Gtk::Pixmap *pixmap_original_tux;
        class Gtk::Label *label_werte;
        class Gtk::Button *button_wert_1;
        class Gtk::Button *button_wert_2;
        class Gtk::Button *button_wert_3;
        class Gtk::Button *button_wert_4;
        class Gtk::Button *button_wert_5;
        class Gtk::Button *button_wert_6;
        class Gtk::Button *button_wert_7;
        class Gtk::Button *button_wert_8;
        class Gtk::Button *button_wert_9;
        class Gtk::Label *label_besserer_wurf;
        class Gtk::Label *label_schlechterer_wurf;
        class Gtk::Table *table_bw_wurf;
        class Gtk::Table *table_werte_wuerfeln;
        class Gtk::Label *resistenz;
        class Gtk::Label *gift_wert;
        class Gtk::Label *abwehr_wert;
        class Gtk::Label *zaubern_wert;
        class Gtk::Button *button_grda1setzen;
        class Gtk::Label *bo_sc;
        class Gtk::Label *bo_an;
        class Gtk::Label *bo_ab;
        class Gtk::Label *bo_za;
        class Gtk::Label *bo_au;
        class Gtk::Label *bo_psy;
        class Gtk::Label *bo_phs;
        class Gtk::Label *bo_phk;
        class Gtk::Label *label_gestalt;
        class Gtk::Label *kaw;
        class Gtk::Label *wlw;
        class Gtk::SpinButton *spinbutton_b;
        class Gtk::SpinButton *spinbutton_au;
        class Gtk::SpinButton *spinbutton_pa;
        class Gtk::SpinButton *spinbutton_sb;
        class Gtk::SpinButton *spinbutton_wk;
        class Gtk::SpinButton *spinbutton_st;
        class Gtk::SpinButton *spinbutton_gs;
        class Gtk::SpinButton *spinbutton_gw;
        class Gtk::SpinButton *spinbutton_ko;
        class Gtk::SpinButton *spinbutton_in;
        class Gtk::SpinButton *spinbutton_zt;
        class Gtk::Label *label_hoeren;
        class Gtk::Label *label_schmecken;
        class Gtk::Label *label_tasten;
        class Gtk::Label *label_sehen;
        class Gtk::Label *label_riechen;
        class Gtk::Label *label_sechster_sinn;
        class Gtk::Entry *entry_nameC;
        class Gtk::SpinButton *spinbutton_ap;
        class Gtk::SpinButton *spinbutton_lp;
        class Gtk::SpinButton *spinbutton_grad;
        class Gtk::SpinButton *spinbutton_alter;
        class Gtk::SpinButton *spinbutton_Cgewicht;
        class Gtk::SpinButton *spinbutton_groesse;
        class Gtk::Entry *entry_nameS;
        class Gtk::Entry *entry_version;
        class Gtk::Entry *entry_herkunft;
        class Gtk::OptionMenu *optionmenu_stand;
        struct optionmenu_stand
        {  enum enum_t 
	   {  STAND, Unfrei, Volk, Mittelschicht, Adel, 
	   };
        };
        class Gtk::Entry *entry_glaube;
        class Gtk::Entry *entry_spezialisierung;
        class Gtk::SpinButton *spinbutton_tage;
        class Gtk::SpinButton *spinbutton_gg;
        class Gtk::SpinButton *spinbutton_sg;
        class Gtk::SpinButton *spinbutton_gfp;
        class Gtk::OptionMenu *optionmenu_hand;
        struct optionmenu_hand
        {  enum enum_t 
	   {  Rechtsh_nder, Linksh_nder, Beidh_nder, 
	   };
        };
        class Gtk::Entry *entry_bezeichnung;
        class Gtk::Pixmap *pixmap_dfr4;
        class Gtk::OptionMenu *optionmenu_spezies;
        struct optionmenu_spezies
        {  enum enum_t 
	   {  Spezies, 
	   };
        };
        class Gtk::RadioButton *radiobutton_eigenschaften_standard;
        class Gtk::RadioButton *radiobutton_eigenschaften_zuweisen;
        class Gtk::RadioButton *radiobutton_eigenschaften_69;
        class Gtk::VBox *vbox_gw_wuerfeln;
        class Gtk::RadioButton *radiobutton_mann;
        class Gtk::RadioButton *radiobutton_frau;
        class Gtk::OptionMenu *typauswahl;
        struct typauswahl
        {  enum enum_t 
	   {  Abenteurerklassen, 
	   };
        };
        class Gtk::OptionMenu *typauswahl_2;
        struct typauswahl_2
        {  enum enum_t 
	   {  ___Abenteurerklasse, 
	   };
        };
        class Gtk::RadioButton *radiobutton_stadt;
        class Gtk::RadioButton *radiobutton_land;
        class Gtk::Button *button_grundwerte;
        class Gtk::Button *button_abg_werte;
        class Gtk::ToggleButton *togglebutton_edit_werte;
        class Gtk::SpinButton *spinbutton_fach;
        class Gtk::RadioButton *button_fachkenntnisse;
        class Gtk::SpinButton *spinbutton_allgemein;
        class Gtk::RadioButton *button_allgemeinwissen;
        class Gtk::SpinButton *spinbutton_waffen;
        class Gtk::RadioButton *button_waffen;
        class Gtk::OptionMenu *option_magier_spezialgebiet;
        struct option_magier_spezialgebiet
        {  enum enum_t 
	   {  SPEZIAL, 
	   };
        };
        class Gtk::SpinButton *spinbutton_zauber;
        class Gtk::RadioButton *button_zauber;
        class Gtk::SpinButton *spinbutton_unge;
        class Gtk::RadioButton *button_untyp_fertigkeiten;
        class Gtk::OptionMenu *optionmenu_KiDo_Stile;
        struct optionmenu_KiDo_Stile
        {  enum enum_t 
	   {  STIL, hart, sanft, gemischt, 
	   };
        };
        class Gtk::RadioButton *button_kido_auswahl;
        class Gtk::Frame *frame_KiDo_lernschema;
        class MidgardBasicTree *tree_gelerntes;
        class Gtk::Label *label_lernschma_titel;
        class MidgardBasicTree *Tree_Lernschema_Zusatz;
        class Gtk::Frame *frame_lernschema_zusatz;
        class Gtk::Viewport *viewport_lernen;
        class Gtk::ScrolledWindow *scrolledwindow_lernen;
        class Gtk::Button *button_angeborene_fert;
        class Gtk::SpinButton *spinbutton_beruf;
        class Gtk::Table *table_berufsprozent;
        class Gtk::Entry *entry_berufsname;
        class Gtk::VBox *vbox_berufsname;
        class Gtk::SpinButton *spinbutton_waffen_lernschema;
        class Gtk::Table *table_waffen_lernschema_eingabe;
        class Gtk::Button *button_herkunft;
        class Gtk::Button *button_lernpunkte;
        class Gtk::ToggleButton *togglebutton_lernpunkte_edit;
        class Gtk::Button *button_beruf;
        class Gtk::Button *button_lernschema_geld;
        class Gtk::Button *button_lernschema_waffen;
        class Gtk::Button *button_ruestung;
        class Gtk::Label *fertig_typ;
        class Gtk::Label *label_ruestung_lernschema;
        class Gtk::ToggleButton *togglebutton_spezialwaffe;
        class Gtk::Label *label_herkunft_lernschema;
        class Gtk::ToggleButton *togglebutton_gelernte_anzeigen;
        class Gtk::ToggleButton *togglebutton_teure_anzeigen;
        class Gtk::Pixmap *pixmap_dfr3;
        class Gtk::ScrolledWindow *scrolledwindow_dfr3;
        class Gtk::Frame *frame_lernschema;
        class MidgardBasicTree *alte_fert_tree;
        class MidgardBasicTree *neue_fert_tree;
        class MidgardBasicTree *alte_waffen_tree;
        class MidgardBasicTree *neue_waffen_tree;
        class MidgardBasicTree *alte_grund_tree;
        class MidgardBasicTree *neue_grund_tree;
        class MidgardBasicTree *alte_zauber_tree;
        class MidgardBasicTree *neue_zauber_tree;
        class MidgardBasicTree *alte_zaubermittel_tree;
        class MidgardBasicTree *neue_zaubermittel_tree;
        class Gtk::Table *table_magier_steigern;
        class MidgardBasicTree *alte_kido_tree;
        class MidgardBasicTree *neue_kido_tree;
        class Gtk::Pixmap *pixmap_kurai;
        class Gtk::Table *table_kido_steigern;
        class MidgardBasicTree *alte_sprache_tree;
        class MidgardBasicTree *neue_sprache_tree;
        class MidgardBasicTree *alte_schrift_tree;
        class MidgardBasicTree *neue_schrift_tree;
        class Gtk::Notebook *notebook_lernen;
        class Gtk::Label *gfp;
        class Gtk::Label *label_aep;
        class Gtk::Label *label_kep;
        class Gtk::Label *label_zep;
        class Gtk::Label *label_gold;
        class Gtk::Label *label_silber;
        class Gtk::Label *label_kupfer;
        class Gtk::Label *label_EP;
        class Gtk::Label *label_Gold;
        class Gtk::VScale *vscale_EP_Gold;
        class Gtk::CheckButton *checkbutton_EP_Geld;
        class Gtk::RadioButton *radiobutton_selbst;
        class Gtk::RadioButton *radiobutton_praxis;
        class Gtk::RadioButton *radiobutton_unterweisung;
        class Gtk::Frame *frame_lernen_mit;
        class Gtk::RadioButton *radio_spruchrolle_wuerfeln;
        class Gtk::RadioButton *radio_spruchrolle_auto;
        class Gtk::ToggleButton *togglebutton_spruchrolle;
        class Gtk::ToggleButton *togglebutton_alle_zauber;
        class Gtk::ToggleButton *togglebutton_zaubersalze;
        class Gtk::Frame *frame_zauber_zusatz;
        class Gtk::RadioButton *radiobutton_reduzieren;
        class Gtk::RadioButton *radiobutton_verlernen;
        class Gtk::RadioButton *radiobutton_steigern;
        class Gtk::Frame *frame_fertigkeit;
        class Gtk::SpinButton *spinbutton_pp_eingeben;
        class Gtk::ToggleButton *togglebutton_praxispunkte;
        class Gtk::RadioButton *radiobutton_pp_fertigkeit;
        class Gtk::RadioButton *radiobutton_pp_abwehr;
        class Gtk::RadioButton *radiobutton_pp_zauber;
        class Gtk::RadioButton *radiobutton_pp_spezial;
        class Gtk::RadioButton *radiobutton_pp_resistenz;
        class Gtk::VBox *vbox_praxispunkte;
        class Gtk::Frame *frame_praxispunkte;
        class Gtk::CList *clist_landauswahl;
        class Gtk::ScrolledWindow *scrolledwindow_landauswahl;
        class Gtk::Button *button_grad_zaubern;
        class Gtk::Label *label_resistenz_GFP;
        class Gtk::Label *label_zauber_GFP;
        class Gtk::Label *label_abwehr_GFP;
        class Gtk::Label *label_ausdauer_GFP;
        class Gtk::Label *label_grad_GFP;
        class Gtk::Table *table_gradsteigern_lang;
        class Gtk::Toolbar *toolbar_steigern_kurz;
        class Gtk::Button *button_steigern_kurz;
        class Gtk::Label *label_s_grad;
        class Gtk::Label *label_s_resistenz;
        class Gtk::Label *label_s_zaubern;
        class Gtk::Label *label_s_abwehr;
        class Gtk::Label *label_alter;
        class Gtk::Label *steigern_typ;
        class Gtk::Label *label_s_ap;
        class Gtk::Label *label_steigertage;
        class Gtk::Label *label_pp_abwehr;
        class Gtk::Label *label_pp_zaubern;
        class Gtk::Frame *frame_pp_zaubern;
        class Gtk::Label *label_pp_resistenz;
        class Gtk::Label *label_pp_spezial;
        class Gtk::Frame *frame_pp_spezial;
        class Gtk::Frame *frame_steigern;
        class Gtk::Text *text_charakter_beschreibung;
        class Gtk::Label *label_grafik;
        class Gtk::SpinButton *spinbutton_pix_breite;
        class SimpleTree *preise_tree;
        class Gtk::CList *clist_preisliste;
        class Gtk::Label *label_golda;
        class Gtk::Label *label_silbera;
        class Gtk::Label *label_kupfera;
        class Gtk::CheckButton *checkbutton_ausruestung_geld;
        class Gtk::Viewport *viewport_modi;
        class Gtk::CheckButton *checkbutton_sichtbar;
        class Gtk::Button *button_ausruestung_loeschen;
        class Gtk::Viewport *viewport_ausruestung;
        class Gtk::ToggleButton *togglebutton_gruppe_neu;
        class Gtk::ToggleButton *togglebutton_artikel_neu;
        class Gtk::Entry *entry_art;
        class Gtk::Entry *entry_typ;
        class Gtk::Entry *entry_eigenschaft;
        class Gtk::Table *table_gruppe;
        class Gtk::SpinButton *spinbutton_preis;
        class Gtk::SpinButton *spinbutton_gewicht;
        class Gtk::OptionMenu *optionmenu_einheit;
        struct optionmenu_einheit
        {  enum enum_t 
	   {  GS, SS, KS, 
	   };
        };
        class Gtk::Entry *entry_name;
        class Gtk::Entry *entry_artikel_art2;
        class Gtk::Entry *entry_artikel_art;
        class Gtk::Table *table_artikel;
        class table_optionen *table_optionen;
        class Gtk::List *list_news;
        class SimpleTree *undo_tree;
        class Gtk::Notebook *notebook_main;
        class Gtk::Toolbar *toolbar_top;
        class Gtk::Button *button_undo;
        class Gtk::Button *button_redo;
        class Gtk::HandleBox *griff_toolbar_top;
        class Gtk::MenuBar *main_menubar;
        class Gtk::HandleBox *handlebox_menu;
        class Gtk::Label *label_status;
        class Gtk::Label *label_wizard;
        class Gtk::HandleBox *handlebox_status;
        
        midgard_CG_glade();
        
        ~midgard_CG_glade();
};
#endif
