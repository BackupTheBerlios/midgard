// generated 2001/12/21 0:20:41 CET by thoma@Tiger.
// using glademm V0.6.2c_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gcc_3.0/midgard/midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.5
//
// Please modify the corresponding derived classes in ./src/midgard_CG.hh and./src/midgard_CG.cc

#ifndef _MIDGARD_CG_GLADE_HH
#  define _MIDGARD_CG_GLADE_HH

#include <gtk--/window.h>
#include <gtk--/tooltips.h>
#include <gtk--/label.h>
#include <gtk--/button.h>
#include <gtk--/table.h>
#include <gtk--/optionmenu.h>
#include <gtk--/radiobutton.h>
#include <gtk--/checkbutton.h>
#include <gtk--/clist.h>
#include <gtk--/box.h>
#include <gtk--/spinbutton.h>
#include <gtk--/frame.h>
#include <gtk--/scale.h>
#include <gtk--/togglebutton.h>
#include "SimpleTree.hh"
#include <gtk--/scrolledwindow.h>
#include <gtk--/viewport.h>

class midgard_CG_glade : public Gtk::Window
{   
        
        Gtk::Tooltips _tooltips;
protected:
        class Gtk::Label *name_charakter;
        class Gtk::Label *spezialisierung;
        class Gtk::Label *glaube;
        class Gtk::Label *alter;
        class Gtk::Label *name_spieler;
        class Gtk::Label *stand;
        class Gtk::Label *gestalt;
        class Gtk::Label *groesse;
        class Gtk::Label *grad;
        class Gtk::Label *herkunft;
        class Gtk::Label *gewicht;
        class Gtk::Label *lp;
        class Gtk::Label *ap;
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
        class Gtk::Label *gs;
        class Gtk::Label *ko;
        class Gtk::Label *in;
        class Gtk::Label *zt;
        class Gtk::Label *st;
        class Gtk::Label *gw;
        class Gtk::Label *resistenz;
        class Gtk::Label *gift_wert;
        class Gtk::Label *abwehr_wert;
        class Gtk::Label *zaubern_wert;
        class Gtk::Label *bo_sc;
        class Gtk::Label *bo_an;
        class Gtk::Label *bo_ab;
        class Gtk::Label *bo_za;
        class Gtk::Label *bo_phk;
        class Gtk::Label *bo_phs;
        class Gtk::Label *bo_psy;
        class Gtk::Label *bo_au;
        class Gtk::Label *pa;
        class Gtk::Label *kaw;
        class Gtk::Label *sb;
        class Gtk::Label *wlw;
        class Gtk::Label *au;
        class Gtk::Label *b;
        class Gtk::Label *wk;
        class Gtk::OptionMenu *typauswahl;
        struct typauswahl
        {   enum enum_t 
	   {   Charakterklassen, 
	   };
        };
        class Gtk::OptionMenu *typauswahl_2;
        struct typauswahl_2
        {   enum enum_t 
	   {   ___Charakterklasse, 
	   };
        };
        class Gtk::OptionMenu *optionmenu_spezies;
        struct optionmenu_spezies
        {   enum enum_t 
	   {   Spezies, 
	   };
        };
        class Gtk::RadioButton *radiobutton_frau;
        class Gtk::RadioButton *radiobutton_mann;
        class Gtk::OptionMenu *optionmenu_land;
        struct optionmenu_land
        {   enum enum_t 
	   {   Stadt, Land, 
	   };
        };
        class Gtk::CheckButton *checkbutton_Eschar;
        class Gtk::CheckButton *checkbutton_Gildenbrief;
        class Gtk::CheckButton *checkbutton_Alba;
        class Gtk::CheckButton *checkbutton_Nahuatlan;
        class Gtk::CheckButton *checkbutton_Kuestenstaaten;
        class Gtk::CheckButton *checkbutton_BR;
        class Gtk::CheckButton *checkbutton_Rawindra;
        class Gtk::CheckButton *checkbutton_Waeland;
        class Gtk::CheckButton *checkbutton_HD;
        class Gtk::CheckButton *checkbutton_KanThaiPan;
public:
        class Gtk::CheckButton *checkbutton_info_fenster;
protected:
        class Gtk::CheckButton *checkbutton_original;
        class Gtk::Button *button_grundwerte;
        class Gtk::Button *button_abg_werte;
        class Gtk::Button *button_herkunft;
        class Gtk::Button *button_sprache;
        class Gtk::Button *button_beschreibung;
        class Gtk::Label *lernpunkte_fach;
        class Gtk::Label *lernpunkte_allgemein;
        class Gtk::Label *lernpunkte_w;
        class Gtk::Label *lernpunkte_z;
        class Gtk::Label *lernpunkte_unge;
        class Gtk::Button *button_geld_waffen;
        class Gtk::Button *button_ruestung;
        class Gtk::Label *fertig_typ;
        class Gtk::CList *fertigkeiten_clist;
        class Gtk::CList *clist_sinne;
        class Gtk::Button *button_fertigkeiten;
        class Gtk::Table *table_fertigkeit;
        class Gtk::HBox *hbox_fertigkeit;
        class Gtk::Label *label_spezialwaffe;
        class Gtk::CList *waffen_clist;
        class Gtk::Table *table_waffen;
        class Gtk::HBox *hbox_waffen;
        class Gtk::CList *zauber_clist;
        class Gtk::OptionMenu *option_magier_spezialgebiet;
        struct option_magier_spezialgebiet
        {   enum enum_t 
	   {   SPEZIAL, 
	   };
        };
        class Gtk::Table *table_magier_lernen;
        class Gtk::HBox *hbox_zauber;
        class Gtk::CList *clist_kido;
        class Gtk::Button *button_kido_auswahl;
        class Gtk::OptionMenu *optionmenu_KiDo_Stile;
        struct optionmenu_KiDo_Stile
        {   enum enum_t 
	   {   STIL, hart, sanft, gemischt, 
	   };
        };
        class Gtk::Table *table_kido_lernen;
        class Gtk::HBox *hbox_kido;
        class Gtk::CList *berufe_clist;
        class Gtk::Button *button_beruf_erfolgswert;
        class Gtk::Label *label_beruf_ew;
        class Gtk::SpinButton *spinbutton_beruferfolgesert;
        class Gtk::VBox *vbox_beruferfolgswert;
        class Gtk::Table *table_beruf;
        class Gtk::HBox *hbox_beruf;
        class Gtk::Frame *frame_lernschema;
        class Gtk::Label *fertigkeiten;
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
        class Gtk::Label *steigern_typ;
        class Gtk::Label *label_s_ap;
        class Gtk::Label *label_s_resistenz;
        class Gtk::Label *label_s_zaubern;
        class Gtk::Label *label_s_abwehr;
        class Gtk::Label *label_s_grad;
        class Gtk::RadioButton *radio_fert_reduzieren;
        class Gtk::RadioButton *radio_fert_verlernen;
        class Gtk::RadioButton *radio_fert_steigern;
        class Gtk::RadioButton *radiobutton_praxis_wuerfeln_fertigkeiten;
        class Gtk::ToggleButton *togglebutton_praxispunkte_fertigkeiten;
        class Gtk::RadioButton *radiobutton_praxis_auto_fertigkeiten;
        class SimpleTree *alte_fert_tree;
        class SimpleTree *neue_fert_tree;
        class Gtk::CList *clist_landauswahl;
        class Gtk::ScrolledWindow *scrolledwindow_landauswahl;
        class Gtk::RadioButton *radio_waffen_steigern;
        class Gtk::RadioButton *radio_waffen_reduzieren;
        class Gtk::ToggleButton *togglebutton_praxispunkte_waffen;
        class Gtk::RadioButton *radiobutton_praxis_wuerfeln_waffen;
        class Gtk::RadioButton *radiobutton_praxis_auto_waffen;
        class Gtk::RadioButton *radiobutton_grundkenntnisse_verlernen;
        class SimpleTree *alte_waffen_tree;
        class SimpleTree *neue_waffen_tree;
        class SimpleTree *alte_grund_tree;
        class SimpleTree *neue_grund_tree;
        class Gtk::ToggleButton *spruchrolle;
        class Gtk::RadioButton *radio_spruchrolle_wuerfeln;
        class Gtk::RadioButton *radio_spruchrolle_auto;
        class Gtk::CheckButton *checkbutton_alle_zauber;
        class Gtk::CheckButton *checkbutton_beschwoerungen;
        class Gtk::CheckButton *checkbutton_zaubermittel;
        class Gtk::CheckButton *checkbutton_zaubersalze;
        class SimpleTree *alte_zauber_tree;
        class SimpleTree *neue_zauber_tree;
        class SimpleTree *alte_zaubermittel_tree;
        class SimpleTree *neue_zaubermittel_tree;
        class Gtk::Table *table_magier_steigern;
        class SimpleTree *alte_kido_tree;
        class SimpleTree *neue_kido_tree;
        class Gtk::Table *table_kido_steigern;
        class Gtk::RadioButton *radio_sprache_steigern;
        class Gtk::RadioButton *radio_sprache_reduzieren;
        class Gtk::RadioButton *radio_sprache_verlernen;
        class SimpleTree *alte_sprache_tree;
        class SimpleTree *neue_sprache_tree;
        class SimpleTree *alte_schrift_tree;
        class SimpleTree *neue_schrift_tree;
        class Gtk::Frame *frame_steigern;
        class Gtk::Label *steigern;
        class Gtk::Viewport *viewport_modi;
        class Gtk::Label *label_golda;
        class Gtk::Label *label_silbera;
        class Gtk::Label *label_kupfera;
        class SimpleTree *preise_tree;
        class Gtk::CList *clist_preisliste;
        class Gtk::Viewport *viewport_ausruestung;
        class Gtk::CheckButton *checkbutton_sichtbar;
        class Gtk::Button *button_ausruestung_loeschen;
        
        midgard_CG_glade();
        
        ~midgard_CG_glade();
};
#define GMM_CHECKBUTTON_INFO_FENSTER (glademm_get<Gtk::CheckButton >("checkbutton_info_fenster"))
#endif
