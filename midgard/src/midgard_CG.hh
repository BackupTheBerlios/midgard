// $Id: midgard_CG.hh,v 1.122 2002/01/08 17:14:48 thoma Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

// generated 2001/2/2 11:29:18 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to midgard_CG.hh_glade

// you might replace
//    class Foo : public Foo_glade { ... };
// by
//    typedef Foo_glade Foo;
// if you didn't make any modifications to the widget

#ifndef _MIDGARD_CG_HH
#  include "midgard_CG_glade.hh"
#  define _MIDGARD_CG_HH
#include "glademm_support.hh"
#include "WindowInfo.hh"


#include <fstream>
#include <string>
#include <stdio.h>
#include <gtk--/main.h>
#include <gtk--/menu.h>
#include <gtk--/menuitem.h>
#include <gtk--/ctree.h>

#include <vector>
#include <list>
#include "zufall.h"
#include "Zauber.hh"
#include "Zauberwerk.hh"
#include "Fertigkeiten.hh"
#include "Waffe.hh"
#include "WaffeGrund.hh"
#include "KiDo.hh"
#include "Ruestung.hh"
#include "Fertigkeiten_angeboren.hh"
//#include "class_berufe.hh"
#include "class_lernpunkte.hh"
#include "Grundwerte.hh"
#include "Land.hh"
#include "Pflicht.hh"
#include "Spezies.hh"
#include "Typen.hh"
#include "Grad_anstieg.hh"
#include "Lernschema.hh"
#include "Beruf.hh"
#include "Preise.hh"
#include "Ausruestung.hh"
class Random;

extern bool Originalbool;
extern bool Infobool;
extern bool steigern_bool;

extern bool Escharbool;//E
extern bool Rawindrabool;//R
extern bool KanThaiPanbool;//K
extern bool Nahuatlanbool;//N
extern bool Waelandbool;//W
extern bool Albabool;//A
extern bool HDbool;//H&D
extern bool BRbool;//B&R
extern bool Gildenbriefbool;//G
extern bool Kuestenstaatenbool;//S


class midgard_CG : public midgard_CG_glade
{   
        Random random;   
        enum enum_notebook_main{PAGE_GRUNDWERTE,PAGE_LERNEN,PAGE_STEIGERN,
                                  PAGE_AUSRUESTUNG};
        enum enum_notebook_lernen{PAGE_FERTIGKEITEN,PAGE_WAFFEN,PAGE_ZAUBER,
                                  PAGE_KIDO,PAGE_SPRACHE};
   public:
        struct st_Database { std::vector<cH_Land> Laender;
                             std::vector<cH_Ruestung> Ruestung;
                             Lernschema lernschema;
                             std::list<cH_MidgardBasicElement> Beruf;
                             std::list<cH_MidgardBasicElement> Fertigkeit_ang;
                             std::list<cH_MidgardBasicElement> Fertigkeit;
                             std::list<cH_MidgardBasicElement> WaffeGrund;
                             std::list<cH_MidgardBasicElement> Waffe;
                             std::map<std::string,std::string> Waffe_from_Alias;
                             std::list<cH_MidgardBasicElement> Zauber;
                             std::list<cH_MidgardBasicElement> Zauberwerk;
                             std::list<cH_MidgardBasicElement> Kido;
                             std::list<cH_MidgardBasicElement> Sprache;
                             std::list<cH_MidgardBasicElement> Schrift;
                             Pflicht pflicht;
                             Ausnahmen ausnahmen;
                             std::vector<cH_Spezies> Spezies;
                             std::vector<cH_Typen> Typen;
                             Grad_anstieg GradAnstieg;
                             std::vector<cH_Spezialgebiet> Spezialgebiet;
                             std::list<cH_Preise> preise;
                             std::list<cH_PreiseMod> preisemod;
               st_Database(){}
               st_Database(std::vector<cH_Land> L,
                           std::vector<cH_Ruestung> R,
                           Lernschema l,
                           std::list<cH_MidgardBasicElement> B,
                           std::list<cH_MidgardBasicElement> Fa,
                           std::list<cH_MidgardBasicElement> F,
                           std::list<cH_MidgardBasicElement> WG,
                           std::list<cH_MidgardBasicElement> W,
                           std::map<std::string,std::string> WfA,
                           std::list<cH_MidgardBasicElement> Z,
                           std::list<cH_MidgardBasicElement> Zw,
                           std::list<cH_MidgardBasicElement> K,
                           std::list<cH_MidgardBasicElement> Sp,
                           std::list<cH_MidgardBasicElement> Sc,
                           Pflicht p,
                           Ausnahmen a,
                           std::vector<cH_Spezies> S,
                           std::vector<cH_Typen> T,
                           Grad_anstieg GA,
                           std::vector<cH_Spezialgebiet> SP,
                           std::list<cH_Preise> pr,
                           std::list<cH_PreiseMod> prm )
                           : Laender(L),Ruestung(R),lernschema(l),
                             Beruf(B),Fertigkeit_ang(Fa),
                             Fertigkeit(F),WaffeGrund(WG),Waffe(W),
                             Waffe_from_Alias(WfA),
                             Zauber(Z),Zauberwerk(Zw),
                             Kido(K),Sprache(Sp),Schrift(Sc),
                             pflicht(p),ausnahmen(a),Spezies(S),
                             Typen(T),GradAnstieg(GA),
                             Spezialgebiet(SP),
                             preise(pr),preisemod(prm) {}
                           };
   private:
        friend class midgard_CG_glade;
        Gtk::Menu *menu;
        void menu_init();
        gint on_eventbox_MCG_button_press_event(GdkEventButton *event);
        Gtk::CheckMenuItem *menu_original;
        Gtk::CheckMenuItem *menu_info;
        Gtk::CheckMenuItem *menu_Eschar;
        Gtk::CheckMenuItem *menu_Rawindra;
        Gtk::CheckMenuItem *menu_KanThaiPan;
        Gtk::CheckMenuItem *menu_Nahuatlan;
        Gtk::CheckMenuItem *menu_Waeland;
        Gtk::CheckMenuItem *menu_Alba;
        Gtk::CheckMenuItem *menu_HD;
        Gtk::CheckMenuItem *menu_BR;
        Gtk::CheckMenuItem *menu_Gildenbrief;
        Gtk::CheckMenuItem *menu_Kuestenstaaten;

        void set_tree_titles();

        st_Database Database;
        std::list<cH_MidgardBasicElement> list_Beruf;
        std::list<cH_MidgardBasicElement> list_Fertigkeit_ang;
        std::list<cH_MidgardBasicElement> list_Fertigkeit;
        std::list<cH_MidgardBasicElement> list_Fertigkeit_neu;
        std::list<cH_MidgardBasicElement> list_Fertigkeit_universal;
        std::list<cH_MidgardBasicElement> list_WaffenGrund;
        std::list<cH_MidgardBasicElement> list_WaffenGrund_neu;
        std::list<cH_MidgardBasicElement> list_Waffen;
        std::list<cH_MidgardBasicElement> list_Waffen_neu;
        std::list<cH_MidgardBasicElement> list_Waffen_besitz;
        std::list<cH_MidgardBasicElement> list_Zauber;
        std::list<cH_MidgardBasicElement> list_Zauber_neu;
        std::list<cH_MidgardBasicElement> list_Zauberwerk;
        std::list<cH_MidgardBasicElement> list_Zauberwerk_neu;
        std::list<cH_MidgardBasicElement> list_Kido;
        std::list<cH_MidgardBasicElement> list_Kido_neu;
        std::list<cH_MidgardBasicElement> list_Sprache;
        std::list<cH_MidgardBasicElement> list_Sprache_neu;
        std::list<cH_MidgardBasicElement> list_Schrift;
        std::list<cH_MidgardBasicElement> list_Schrift_neu;

        bool kido_bool;
        int maxkido;
        bool magie_bool;

        vector<cH_Typen> Typ;
        Lernpunkte lernpunkte;
   
        void get_Database();
        void regnot(std::string sadd);
        void fill_typauswahl();
        void fill_typauswahl_2();
        void fill_typauswahl_fill(int typ_1_2);
        void fill_spezies();
        void typauswahl_button();
        void typauswahl_2_button();
        void on_radiobutton_stadt_land_toggled();
        void angeborene_zauber();
        void angeborene_fertigkeiten();
        void on_radiobutton_frau_toggled();
        void on_radiobutton_mann_toggled();
        void spezieswahl_button();
        void on_herkunftsland_clicked();
        gint on_button_menu_button_release_event(GdkEventButton *ev);
        void gw_wuerfeln_2x();
        gint on_button_grundwerte_button_release_event(GdkEventButton *ev);
        void on_button_wert_1_clicked();
        void on_button_wert_2_clicked();
        void on_button_wert_3_clicked();
        void on_button_wert_4_clicked();
        void on_button_wert_5_clicked();
        void on_button_wert_6_clicked();
        int werte_label_count;
        void set_werte_label_2();
        void set_werte_label_3(Gtk::Label *L=0);
        void gw_setzen(Gtk::Label *L=0,int button=0);
        int  constraint_gw(Random& random,int constraint);
        int  constraint_aw(Random& random,int constraint);
        int  wuerfeln_best_of_two(Random& random);
        void werte_editieren();
        void on_abge_werte_setzen_clicked();
        void original_midgard_check();
        void grundwerte_boni_setzen();
        void on_neuer_charakter_clicked();
        void clear_gtk();
        void clear_listen();
        void on_button_hilfe_clicked();
        void on_charakter_beschreibung_clicked();
        void charakter_db_anlegen();
        void on_laden_clicked();
        void load_charakter();
        void load_fertigkeiten();
        void on_latex_clicked(bool values=true);
        void LaTeX_write_values();
        void LaTeX_write_empty_values();
        gint on_latex_release_event(GdkEventButton *ev);
        void spielleiter_export();
        void latex_beschreibung_drucken();
        void on_button_info_clicked();
        void LaTeX_zauber_main();
        std::string LaTeX_scale(const std::string& is, unsigned int maxlength, const std::string& scale);
        std::string LaTeX_scalemag(const std::string& is, unsigned int maxlength, const std::string& scale,
            const std::string& magisch,const std::string& reichweite);
        void LaTeX_zauber();
        void LaTeX_zaubermittel();
        void LaTeX_kido_main();
        void LaTeX_kido();
        void LaTeX_header(ofstream &fout,bool landscape=true);
        void LaTeX_footer(ofstream &fout);
        std::string LaTeX_string(int i);
        void on_schliessen_CG_clicked();
        void on_lernpunkte_wuerfeln_clicked();
        void on_lernpunkte_editieren_clicked();
        void on_button_fach_trans_clicked();
        void on_button_waffe_trans_clicked();
        void on_button_ruestung_clicked();
        void on_button_geld_waffen_clicked();
        void on_button_geld_s_clicked();
        void on_button_ruestung_s_clicked();
        void on_button_waffen_s_clicked();
        void on_waffen_clist_select_row(gint row, gint column, GdkEvent *event);   
        void on_waffen_clist_unselect_row(gint row, gint column, GdkEvent *event);
        void on_fertigkeiten_wahl_clicked();
        void on_waffen_wahl_clicked();
        void spezialgebiet_button();
        void spezialgebiet_button_fill();
        void magier_spezialgebiet(const std::string& whattodo);
        void get_spezial_from_spezialgebiet();
        void on_zauber_wahl_clicked();
        void on_berufe_wahl_clicked();
        void on_kido_wahl_clicked();
        void show_kido();
        void stil_optionmenue();
        void show_berufe();
        void show_waffen();
        void show_zauber();
        void zeige_lernpunkte();
        void zeige_notebook();
        gint on_beruf_erfolgswert_release_event(GdkEventButton *ev);
        void on_spinbutton_beruferfolgesert_activate();
        gint on_angeborene_fertigkeit_button_release_event(GdkEventButton *ev);
        void on_angeborene_fertigkeit_clicked();
        void on_angeborene_fertigkeit_right_clicked();
        void universal_Fertigkeiten();
        void on_spezialwaffe_clicked();
        void on_checkbutton_original_menu();
        void on_checkbutton_original_toggled();
        void on_checkbutton_info_fenster_menu();
        void on_checkbutton_info_fenster_toggled();
        void on_checkbutton_Eschar_menu();
        void on_checkbutton_Eschar_toggled();
        void on_checkbutton_Rawindra_menu();
        void on_checkbutton_Rawindra_toggled();
        void on_checkbutton_KanThaiPan_menu();
        void on_checkbutton_KanThaiPan_toggled();
        void on_checkbutton_Nahuatlan_menu();
        void on_checkbutton_Nahuatlan_toggled();
        void on_checkbutton_Waeland_menu();
        void on_checkbutton_Waeland_toggled();
        void on_checkbutton_Alba_menu();
        void on_checkbutton_Alba_toggled();
        void on_checkbutton_HD_menu();
        void on_checkbutton_HD_toggled();
        void on_checkbutton_BR_menu();
        void on_checkbutton_BR_toggled();
        void on_checkbutton_Gildenbrief_menu();
        void on_checkbutton_Gildenbrief_toggled();
        void on_checkbutton_Kuestenstaaten_menu();
        void on_checkbutton_Kuestenstaaten_toggled();

        void on_grad_anstieg_clicked();
        void on_button_grad_ausdauer_clicked();
        void on_button_grad_basiswerte_clicked();
        void on_button_grad_abwehr_clicked();
        void on_button_grad_zaubern_clicked();
        void on_button_grad_resistenz_clicked();
        void on_button_grad_clicked();
        void get_ausdauer(int grad);
        void get_grundwerte();
        void get_ab_re_za(const string& was);
         
        void on_button_EP_clicked();
        gint vscale_value_changed(GdkEventButton *ev);
        void set_lernzeit(unsigned int kosten);
        bool steigern_usp(unsigned int kosten,const cH_MidgardBasicElement *MBE,const std::string &was="");
        void desteigern(unsigned int kosten);
        void on_checkbutton_EP_Geld_toggled();
        void steigern_gtk();
        int steigern_womit(const std::string& fert);

        void on_notebook_main_switch_page(Gtk::Notebook_Helpers::Page* page,guint pagenr);
        void on_notebook_lernen_switch_page(Gtk::Notebook_Helpers::Page* page,guint pagenr);
        void load_for_page(guint pagenr);
        void on_radio_steigern_toggled();
        void on_radio_reduzieren_toggled();
        void on_radio_verlernen_toggled();
        void on_radiobutton_pp_eingeben_toggled();
        void on_radio_steigern_all();
        void on_radio_unterweisung_toggled();
        void on_radio_selbst_toggled();
        void on_radio_praxis_toggled();
        void on_spinbutton_pp_eingeben_activate();
        void on_radiobutton_pp_fertigkeit_toggled();
        void on_radiobutton_pp_zauber_toggled();
        void on_radiobutton_pp_abwehr_toggled();
        void on_radiobutton_pp_resistenz_toggled();
        void on_radiobutton_pp_all_toggled();


        void on_fertigkeiten_laden_clicked();
        void fertigkeiten_zeigen();
        void show_alte_fertigkeiten();
        void on_leaf_selected_alte_fert(cH_RowDataBase d);
        void show_neue_fertigkeiten();
        void on_leaf_selected_neue_fert(cH_RowDataBase d);
        void on_button_fertigkeiten_sort_clicked();
        void on_alte_fert_reorder();
        bool kido_steigern_check(int wert);
        void fillClistLand(const cH_MidgardBasicElement &MBE);
        void on_clist_landauswahl_select_row(gint row, gint column, GdkEvent *event);   

        void on_waffen_laden_clicked();
        void on_alte_waffen_reorder();
        void on_waffengrund_laden_clicked();
        void waffen_zeigen();
        void on_leaf_selected_alte_grund(cH_RowDataBase d);
        void on_leaf_selected_neue_grund(cH_RowDataBase d);
        void on_leaf_selected_alte_waffen(cH_RowDataBase d);
        void on_leaf_selected_neue_waffen(cH_RowDataBase d);
        void on_button_waffen_sort_clicked();

        void on_zauber_laden_clicked();
        void on_alte_zauber_reorder();
        void zauber_zeigen();
        void on_spruchrolle_toggled();
        void on_checkbutton_zaubersalze_toggled();
        void on_checkbutton_beschwoerungen_toggled();
        void on_checkbutton_alle_zauber_toggled();
        void on_checkbutton_zaubermittel_toggled();
        bool spruchrolle_wuerfeln(const cH_MidgardBasicElement& zauber);
        void on_leaf_selected_alte_zauber(cH_RowDataBase d);
        void on_leaf_selected_neue_zauber(cH_RowDataBase d);
        void on_leaf_selected_alte_zauberwerk(cH_RowDataBase d);
        void on_leaf_selected_neue_zauberwerk(cH_RowDataBase d);
        void zauberwerk_laden();
        void zauberwerk_zeigen();
        void on_button_zauber_sort_clicked();
        void on_alte_zaubermittel_reorder();
        void on_button_zaubermittel_sort_clicked();

        void on_kido_laden_clicked();
        void kido_zeigen();
        void on_leaf_selected_alte_kido(cH_RowDataBase d);
        void on_leaf_selected_neue_kido(cH_RowDataBase d);
        void on_alte_kido_reorder();
        void on_button_kido_sort_clicked();


        void on_sprache_laden_clicked();
        void on_leaf_selected_alte_sprache(cH_RowDataBase d);
        void on_leaf_selected_neue_sprache(cH_RowDataBase d);
        void on_schrift_laden_clicked();
        void on_leaf_selected_alte_schrift(cH_RowDataBase d);
        void on_leaf_selected_neue_schrift(cH_RowDataBase d);
        void schriften_zeigen();
        void sprachen_zeigen();
        void on_alte_sprache_reorder();
        void on_button_sprache_sort_clicked();
        void neue_schrift_wegen_sprache();
        int andereSprache_gleicheSchriftart(std::string art);

        void show_gtk();

        void ausruestung_laden();
        void fill_preisliste();
        void on_button_ausruestung_druck_clicked();
        void ausruestung_druck(ofstream &fout,const list<AusruestungBaum> &AB,int deep);
        void on_clist_preisliste_select_row(gint row, gint column, GdkEvent *event);
        void on_preise_leaf_selected(cH_RowDataBase d);        
        void on_button_modi_clicked();
        void show_modi();
        void setStandardAusruestung();
        void setFertigkeitenAusruestung(AusruestungBaum *Rucksack);
        void InfoFenster(std::string name,int wurf,int noetig);
        void showAusruestung();
        void showChildren(Gtk::CTree_Helpers::RowList::iterator r,const std::list<AusruestungBaum> &AB);
        Gtk::CTree *Ausruestung_tree;
        AusruestungBaum besitz;
        struct st_modimap_index{std::string art;std::string art2;std::string typ;
            st_modimap_index(std::string a,std::string a2,std::string t)
               :art(a),art2(a2),typ(t) {}
            bool operator <(const st_modimap_index b) const 
            {return art<b.art || (art==b.art && art2<b.art2) ||
                    (art==b.art && art2==b.art2 && typ<b.typ);} };
        std::map<st_modimap_index,PreiseMod::st_payload> modimap;
        void on_checkbutton_sichtbar_toggled();
        SigC::Connection sichtbarConnection;
        void on_ausruestung_loeschen_clicked();
        void on_Ausruestung_tree_select_row(Gtk::CTree::Row row,gint column);
        void on_Ausruestung_tree_unselect_row(Gtk::CTree::Row row,gint column);
        bool tree_valid(Gtk::CTree_Helpers::SelectionList &selectionList) ;
        void on_button_artikel_neu_clicked();
        void on_button_gruppe_neu_clicked();
        void on_entry_art_activate();
        void on_entry_typ_activate();
        void on_entry_eigenschaft_activate();
        void on_entry_artikel_art_activate();
        void on_entry_artikel_art2_activate();
        void on_entry_name_activate();
        void on_spinbutton_preis_activate();
        void on_optionmenu_einheit_deactivate();
        void on_spinbutton_gewicht_activate();
        void on_checkbutton_ausruestung_geld_toggled();
   
   public:
         midgard_CG(int argc,char **argv);
         void doppelcharaktere();
         Grundwerte Werte;
         void on_speichern_clicked();
         gint on_speichern_release_event(GdkEventButton *ev);
         void grundwerte_speichern();
         void save_ausruestung();
         void save_ausruestung_C(int parent,int &self,const list<AusruestungBaum> &AB);
         void load_ausruestung();
         void load_ausruestung_C(int parent, AusruestungBaum *AB);
         gint on_laden_release_event(GdkEventButton *ev);
         void xml_export(const std::string& datei);
         void xml_import(const std::string& datei);
         void xml_export_auswahl();
         void xml_import_auswahl();
         void charakter_beschreibung_uebernehmen(const std::string& b);
         void charakter_beschreibung_drucken(const std::string& b);
         void select_charakter(const std::string& name, const std::string& version);
         void zeige_werte(const Grundwerte& w);
         void setze_lernpunkte(const Lernpunkte& _lernpunkte);
         void show_fertigkeiten();
         void show_sinne();
         void waffe_besitz_uebernehmen(const std::list<cH_MidgardBasicElement>& wbu);
         void MidgardBasicElement_uebernehmen(const std::list<cH_MidgardBasicElement>& mbe,
                                              const std::list<cH_MidgardBasicElement>& mbe2=std::list<cH_MidgardBasicElement>());
         void MidgardBasicElement_uebernehmen(const cH_MidgardBasicElement& mbe);
         bool MidgardBasicElement_leaf_alt(const cH_RowDataBase &d);
         void MidgardBasicElement_leaf_neu(const cH_RowDataBase &d);
         void herkunft_uebernehmen(const cH_Land& s);
         bool region_check(const std::string& region);
         void EP_uebernehmen();
         void Geld_uebernehmen();
};
#endif
