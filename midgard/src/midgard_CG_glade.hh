// generated 2001/5/13 13:24:00 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gra_mygen/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.5
//
// Please modify the corresponding derived classes in ./src/midgard_CG.hh and./src/midgard_CG.cc

#ifndef _MIDGARD_CG_GLADE_HH
#  define _MIDGARD_CG_GLADE_HH

#include <gtk--/window.h>
#include <gtk--/tooltips.h>
#include <gtk--/label.h>
#include <gtk--/checkbutton.h>
#include <gtk--/optionmenu.h>
#include <gtk--/radiobutton.h>
#include <gtk--/clist.h>
#include <gtk--/table.h>
#include <gtk--/togglebutton.h>

class midgard_CG_glade : public Gtk::Window
{   
        
        Gtk::Tooltips _tooltips;
protected:
        class Gtk::Label *ap;
        class Gtk::Label *lp;
        class Gtk::Label *psyZR_wert;
        class Gtk::Label *phsZR_wert;
        class Gtk::Label *phkZR_wert;
        class Gtk::Label *gift_wert;
        class Gtk::Label *abwehr_wert;
        class Gtk::Label *zaubern_wert;
        class Gtk::Label *bo_au;
        class Gtk::Label *bo_sc;
        class Gtk::Label *bo_an;
        class Gtk::Label *bo_ab;
        class Gtk::Label *bo_za;
        class Gtk::Label *bo_gi;
        class Gtk::Label *bo_phk;
        class Gtk::Label *bo_phs;
        class Gtk::Label *bo_psy;
        class Gtk::Label *pa;
        class Gtk::Label *kaw;
        class Gtk::Label *sb;
        class Gtk::Label *wlw;
        class Gtk::Label *rw;
        class Gtk::Label *hgw;
        class Gtk::Label *lpbasis;
        class Gtk::Label *au;
        class Gtk::Label *b;
        class Gtk::Label *ge;
        class Gtk::Label *ko;
        class Gtk::Label *in;
        class Gtk::Label *zt;
        class Gtk::Label *st;
        class Gtk::Label *herkunft;
        class Gtk::Label *spezialisierung;
        class Gtk::Label *glaube;
        class Gtk::Label *alter;
        class Gtk::Label *groesse;
        class Gtk::Label *gewicht;
        class Gtk::Label *grad;
        class Gtk::Label *stand;
        class Gtk::Label *name_charakter;
        class Gtk::Label *gestalt;
        class Gtk::Label *name_spieler;
        class Gtk::CheckButton *checkbutton_Nahuatlan;
        class Gtk::CheckButton *checkbutton_Eschar;
        class Gtk::CheckButton *checkbutton_Alba;
        class Gtk::CheckButton *checkbutton_Rawindra;
        class Gtk::CheckButton *checkbutton_KanThaiPan;
        class Gtk::CheckButton *checkbutton_Waeland;
        class Gtk::CheckButton *checkbutton_HD;
public:
        class Gtk::CheckButton *checkbutton_info_fenster;
protected:
        class Gtk::OptionMenu *typauswahl;
        struct typauswahl
        {   enum enum_t 
	   {   Charakterklassen, 
	   };
        };
        class Gtk::OptionMenu *optionmenu_spezies;
        struct optionmenu_spezies
        {   enum enum_t 
	   {   Spezies, 
	   };
        };
        class Gtk::RadioButton *radiobutton_mann;
        class Gtk::RadioButton *radiobutton_frau;
        class Gtk::OptionMenu *typauswahl_2;
        struct typauswahl_2
        {   enum enum_t 
	   {   ___Charakterklasse, 
	   };
        };
        class Gtk::CList *berufe_clist;
        class Gtk::CList *fertigkeiten_clist;
        class Gtk::Label *label_spezialwaffe;
        class Gtk::CList *waffen_clist;
        class Gtk::CList *zauber_clist;
        class Gtk::OptionMenu *option_magier_spezialgebiet;
        struct option_magier_spezialgebiet
        {   enum enum_t 
	   {   SPEZIAL, 
	   };
        };
        class Gtk::Table *table_magier_lernen;
        class Gtk::CList *clist_kido;
        class Gtk::OptionMenu *optionmenu_KiDo_Stile;
        struct optionmenu_KiDo_Stile
        {   enum enum_t 
	   {   STIL, hart, sanft, gemischt, 
	   };
        };
        class Gtk::Table *table_kido_lernen;
        class Gtk::Label *lernpunkte_b;
        class Gtk::Label *lernpunkte_f;
        class Gtk::Label *lernpunkte_w;
        class Gtk::Label *lernpunkte_z;
        class Gtk::Label *fertig_typ;
        class Gtk::RadioButton *radio_fert_reduzieren;
        class Gtk::RadioButton *radio_fert_verlernen;
        class Gtk::RadioButton *radio_fert_steigern;
        class Gtk::RadioButton *radiobutton_praxis_wuerfeln_fertigkeiten;
        class Gtk::ToggleButton *togglebutton_praxispunkte_fertigkeiten;
        class Gtk::RadioButton *radiobutton_praxis_auto_fertigkeiten;
        class Gtk::CList *steigern_fert_clist_alt;
        class Gtk::CList *steigern_fert_clist_neu;
        class Gtk::RadioButton *radio_waffen_steigern;
        class Gtk::RadioButton *radio_waffen_reduzieren;
        class Gtk::ToggleButton *togglebutton_praxispunkte_waffen;
        class Gtk::RadioButton *radiobutton_praxis_wuerfeln_waffen;
        class Gtk::RadioButton *radiobutton_praxis_auto_waffen;
        class Gtk::CList *steigern_waffen_clist_alt;
        class Gtk::CList *steigern_waffen_clist_neu;
        class Gtk::CList *grundkenntnisse_clist_alt;
        class Gtk::CList *grundkenntnisse_clist_neu;
        class Gtk::RadioButton *radiobutton_grundkenntnisse_verlernen;
        class Gtk::ToggleButton *spruchrolle;
        class Gtk::RadioButton *radio_spruchrolle_wuerfeln;
        class Gtk::RadioButton *radio_spruchrolle_auto;
        class Gtk::CheckButton *checkbutton_alle_zauber;
        class Gtk::CheckButton *checkbutton_zaubersalze;
        class Gtk::CheckButton *checkbutton_beschwoerungen;
        class Gtk::CheckButton *checkbutton_zaubermittel;
        class Gtk::CList *steigern_zauber_clist_alt;
        class Gtk::CList *steigern_zauber_clist_neu;
        class Gtk::CList *clist_zaubermittel_alt;
        class Gtk::CList *clist_zaubermittel_neu;
        class Gtk::Table *table_magier_steigern;
        class Gtk::CList *steigern_kido_clist_alt;
        class Gtk::CList *steigern_kido_clist_neu;
        class Gtk::Table *table_kido_steigern;
        class Gtk::CList *clist_steigern_sprachen_alt;
        class Gtk::CList *clist_steigern_sprachen_neu;
        class Gtk::CList *clist_steigern_schrift_alt;
        class Gtk::CList *clist_steigern_schrift_neu;
        class Gtk::RadioButton *radio_sprache_steigern;
        class Gtk::RadioButton *radio_sprache_reduzieren;
        class Gtk::RadioButton *radio_sprache_verlernen;
        class Gtk::Label *gfp;
        class Gtk::Label *steigern_typ;
        
        midgard_CG_glade();
        
        ~midgard_CG_glade();
};
#define GMM_CHECKBUTTON_INFO_FENSTER (glademm_get<Gtk::CheckButton >("checkbutton_info_fenster"))
#endif
