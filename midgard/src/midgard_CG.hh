// $Id: midgard_CG.hh,v 1.63 2001/09/03 08:11:00 thoma Exp $
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
#include <vector>
#include <map>
#include "class_zauber.hh"
#include "class_fertigkeiten.hh"
#include "class_berufe.hh"
#include "class_waffen.hh"
#include "class_kido.hh"
#include "class_sprache_schrift.hh"
#include "class_lernpunkte.hh"
#include "class_typen.hh"
#include "class_Grundwerte.hh"
#include "class_spezies.hh"
#include "class_grad_anstieg.hh"

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

extern grad_anstieg Grad_Anstieg;

class midgard_CG : public midgard_CG_glade
{   
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

        std::vector<cH_Data_typen> vec_Typen;
        std::vector<cH_Data_typen> vec_Typen_2;
        std::vector<std::string> vec_spezialgebiet;
        std::vector<std::string> spezies_vector;
        std::vector<H_Data_fert> vec_Fertigkeiten;
        std::vector<H_Data_fert> vec_an_Fertigkeit;
        std::vector<H_Data_waffen> vec_Waffen;
        std::vector<H_Data_waffen> vec_Waffen_besitz;
        std::vector<H_Data_beruf> vec_Beruf;
        std::vector<H_Data_zauber> vec_Zauber;
        std::vector<H_Data_zaubermittel> vec_Zaubermittel;
        std::vector<H_Data_kido> vec_Kido;

        bool kido_bool;
        int maxkido;
        int steigern_EP_prozent;
        int grad_basiswerte;
//        int grad_abwehr;
//        int grad_resistenz;
        bool magie_bool;
        grad_anstieg Grad_Anstieg;



        std::vector<H_Data_sprache> vec_Sprachen;
        std::vector<H_Data_schrift> vec_Schriften;
        map<std::string,string> waffen_grundkenntnisse;
        Data_typen Typ;
        Data_typen Typ2;
        Lernpunkte lernpunkte;
        Data_spezies Spezies_constraint;
   
        void regnot(std::string sadd);
        void fill_typauswahl();
        void fill_typauswahl_2();
        void fill_typauswahl_fill(int typ_1_2);
        void fill_spezies();
        void typauswahl_button();
        void typauswahl_2_button();
        void angeborene_zauber();
        void on_radiobutton_frau_toggled();
        void on_radiobutton_mann_toggled();
        void spezieswahl_button();
        void on_herkunftsland_clicked();
        void on_muttersprache_clicked();
        void gw_wuerfeln();
        void get_spezies_constraint();
        int  constraint_gw(Random& random,int constraint);
        int  constraint_aw(Random& random,int constraint);
        int  wuerfeln_best_of_two(Random& random);
        void werte_editieren();
        void on_abge_werte_setzen_clicked();
        void original_midgard_check();
        void grundwerte_boni_setzen();
        void on_neuer_charakter_clicked();
        void on_button_hilfe_clicked();
        void on_charakter_beschreibung_clicked();
        void charakter_db_anlegen();
        void on_laden_clicked();
        void load_charakter();
        void on_latex_clicked(bool values=true);
        void LaTeX_write_values();
        void LaTeX_write_empty_values();
        gint on_latex_release_event(GdkEventButton *ev);
        void spielleiter_export();
        void latex_beschreibung_drucken();
        void on_button_info_clicked();
        void LaTeX_zauber_main();
        std::string LaTeX_scale(const std::string& is, unsigned int maxlength, const std::string& scale, const H_Data_waffen& waffe=new Data_waffen());
        void LaTeX_zauber();
        void LaTeX_zaubermittel();
        void LaTeX_kido_main();
        void LaTeX_kido();
        std::string LaTeX_string(int i);
        void on_schliessen_CG_clicked();
        void on_lernpunkte_wuerfeln_clicked();
        void on_lernpunkte_editieren_clicked();
        void on_button_ruestung_clicked();
        void on_button_geld_waffen_clicked();
        void on_button_geld_s_clicked();
        void on_button_ruestung_s_clicked();
        void on_button_waffen_s_clicked();
        std::string ruestung(const std::string& mod);
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
        void get_kido(std::vector<H_Data_kido>& vec_Kido);
        int get_erfolgswert_kido();
        int maxkidostil(const std::string& stufe);
        void show_kido();
        void stil_optionmenue();
        int  get_erfolgswert_zaubern(const Data_typen& Typ,const Data_typen& Typ2,const std::string& name);
        int get_spezial_zauber(const std::string& typ,const std::string& name);
        void show_berufe();
        void show_waffen();
        void show_zauber();
        void zeige_lernpunkte();
        void zeige_notebook();
        void Zauber_get_Daten(std::vector<H_Data_zauber>& zauber);
        void on_beruf_erfolgswert_clicked();
        gint on_beruf_erfolgswert_release_event(GdkEventButton *ev);
        void on_spinbutton_beruferfolgesert_activate();
        gint on_angeborene_fertigkeit_button_release_event(GdkEventButton *ev);
        void on_angeborene_fertigkeit_clicked();
        void on_angeborene_fertigkeit_right_clicked();
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
        void on_button_grad_azr_clicked();
        void on_button_grad_clicked();
        void get_grad(int gfp);
        void get_ausdauer(int grad);
//        void get_resistenz_wert(int grad);
//        void get_abwehr_wert(int grad);
        void get_zauber(int grad);
        void get_grundwerte();
        void get_abwehr_resistenz(const string& was);
         
        void on_button_EP_clicked();
        gint vscale_value_changed(GdkEventButton *ev);
        bool steigern(unsigned int kosten,const std::string& fert);
        void desteigern(unsigned int kosten);
        void on_checkbutton_EP_Geld_toggled();
        void steigern_gtk();
        int steigern_womit(const std::string& fert);

        void on_fertigkeiten_laden_clicked();
        void on_steigern_fert_tree_alt_select(const std::string& fertigkeit, int wert, int steigern, int reduzieren, int verlernen);
        void on_steigern_fert_tree_neu_select(const std::string& fertigkeit, int wert, int lernkosten);
        void show_alte_fertigkeiten();
        void on_leaf_selected_alte_fert(cH_RowDataBase d);
        void show_neue_fertigkeiten();
        void on_leaf_selected_neue_fert(cH_RowDataBase d);
        void on_button_fertigkeiten_sort_clicked();
        void on_radio_fert_steigern_toggled();
        void on_radio_fert_reduzieren_toggled();
        void on_radio_fert_verlernen_toggled();
        void on_togglebutton_praxispunkte_fertigkeiten_toggled();
        void on_radiobutton_praxis_wuerfeln_fertigkeiten_toggled();
        void on_radiobutton_praxis_auto_fertigkeiten_toggled();
        int praxispunkte_wuerfeln(const std::string& fert,int alter_wert, const std::string& art,bool wuerfeln);
        int attribut_check(std::string atr);
        bool kido_steigern_check(int wert);
   
        void on_waffen_laden_clicked();
        void show_alte_grund();
        void show_neue_grund();
        void show_alte_waffen();
        void show_neue_waffen();
        void on_steigern_grund_tree_alt_select(const std::string& name);
        void on_steigern_grund_tree_neu_select(const std::string& name,int kosten);
        void on_leaf_selected_alte_grund(cH_RowDataBase d);
        void on_leaf_selected_neue_grund(cH_RowDataBase d);
        void on_leaf_selected_alte_waffen(cH_RowDataBase d);
        void on_leaf_selected_neue_waffen(cH_RowDataBase d);
        void on_steigern_waffen_tree_alt_select(const std::string& waffe, int erfolgswert, int steigern, int reduzieren);
        void on_steigern_waffen_tree_neu_select(const std::string&  name, int erfolgswert);
        void on_button_waffen_sort_clicked();
        void on_radio_waffen_steigern_toggled();
        void on_radio_waffen_reduzieren_toggled();
        void on_togglebutton_praxispunkte_waffen_toggled();
        void on_radiobutton_praxis_wuerfeln_waffen_toggled();
        void on_radiobutton_praxis_auto_waffen_toggled();
        std::string get_Verteidigungswaffe(int ohne_waffe);


        void on_zauber_laden_clicked();
        void on_spruchrolle_toggled();
        void on_checkbutton_zaubersalze_toggled();
        void on_checkbutton_beschwoerungen_toggled();
        void on_checkbutton_alle_zauber_toggled();
        void on_checkbutton_zaubermittel_toggled();
        int spruchrolle_wuerfeln(int istufe, std::string art, std::string zauber);
        void on_leaf_selected_alte_zauber(cH_RowDataBase d);
        void on_steigern_zauber_tree_alt_select(const std::string& zauber, int kosten);
        void on_leaf_selected_neue_zauber(cH_RowDataBase d);
        void on_steigern_zauber_tree_neu_select(const std::string& zauber, int kosten, const std::string& stufe, const std::string& art);
        void show_alte_zauber();
        void show_neue_zauber();
        void on_steigern_zaubermittel_tree_alt_select(const std::string& name, int kosten);
        void on_steigern_zaubermittel_tree_neu_select(const std::string& name, const std::string& stufe, int kosten);
        void on_leaf_selected_alte_zaubermittel(cH_RowDataBase d);
        void on_leaf_selected_neue_zaubermittel(cH_RowDataBase d);
        void show_alte_zaubermittel();
        void show_neue_zaubermittel();
        void get_Zaubermittel(std::vector<H_Data_zaubermittel>& vec_Zaubermittel);
        float get_standard_zaubermittel(const Data_typen& Typ,const Data_typen& Typ2,const std::string& name);
        bool zauberwerk_voraussetzung(const std::string& name);
        void on_button_zauber_sort_clicked();
        void on_button_zaubermittel_sort_clicked();

        void on_kido_laden_clicked();
        void on_leaf_selected_alte_kido(cH_RowDataBase d);
        void on_leaf_selected_neue_kido(cH_RowDataBase d);
        void on_steigern_kido_tree_alt_select(const std::string& name,int kosten);
        void on_steigern_kido_tree_neu_select(const std::string& name,int kosten);
        void show_alte_kido();
        void show_neue_kido();
        void on_button_kido_sort_clicked();


        void on_sprache_laden_clicked();
        void on_leaf_selected_alte_sprache(cH_RowDataBase d);
        void on_leaf_selected_neue_sprache(cH_RowDataBase d);
        void on_steigern_sprache_tree_alt_select(const std::string& name,int steigern,int reduzieren,int verlernen);
        void on_steigern_sprache_tree_neu_select(const std::string& name,int kosten);
        void on_radio_sprache_steigern_toggled();
        void on_radio_sprache_reduzieren_toggled();
        void on_radio_sprache_verlernen_toggled();
        void on_leaf_selected_alte_schrift(cH_RowDataBase d);
        void on_leaf_selected_neue_schrift(cH_RowDataBase d);
        void on_steigern_schrift_tree_alt_select(const std::string& name, int kosten);
        void on_steigern_schrift_tree_neu_select(const std::string& name, const std::string& art, int kosten);
        void show_alte_schriften();
        void show_neue_schriften();
        void show_alte_sprachen();
        void show_neue_sprachen();
        void sprachen_schrift();
        void on_button_sprache_sort_clicked();
        void on_button_schrift_sort_clicked();
        void show_gtk();
        void get_typ_after_load();
        void get_optionmenu_typ_nr();
        bool get_typ_s(const std::string& mod,const Data_typen& t);
   
   public:
         midgard_CG();
         void doppelcharaktere();
         Grundwerte Werte;
         void on_speichern_clicked();
         gint on_speichern_release_event(GdkEventButton *ev);
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
         void fertigkeiten_uebernehmen(const std::vector<H_Data_fert>& saf);
         void show_fertigkeiten();
         void waffen_uebernehmen(const std::vector<H_Data_waffen>& saw,map<std::string,string> wg);
         void waffe_besitz_uebernehmen(const std::vector<H_Data_waffen>& wbu);
         void zauber_uebernehmen(const std::vector<H_Data_zauber>& saz);
         void berufe_uebernehmen(std::vector<H_Data_beruf>& sab);
         void kido_uebernehmen(std::vector<string>& technik);
         double get_standard_zauber(const Data_typen& typ,const Data_typen& typ2, const std::string& zauber);
         double get_standard_zauber_(const std::string& ergebnis, const std::string& ergebnis2, const std::string& p_element, const std::string& s_element, const std::string& zauber);
         double get_standard_waffen(const std::string& typ, const std::string& typ2,const std::string& waffe);
         double get_standard_fertigkeit(const std::string& typ, const std::string& typ_2,const std::string& fertigkeit);
         double get_standard_fertigkeit_(const std::string& ergebnis,const std::string& ergebnis2,const std::string& fertigkeiten);
         std::string get_region_waffen(const std::string& waffe, const std::string& region,int mod);
         void sprache_uebernehmen(const std::string& s, int wert);
         void schrift_uebernehmen(const std::string& s, const std::string& t);
         void herkunft_uebernehmen(const std::string& s);
         std::string waffe_werte(const H_Data_waffen& waffe,const Grundwerte& Werte, const std::string& mod);
         std::vector<string> Berufs_Vorteile();
         bool Fertigkeiten_Voraussetzung(const std::string& fertigkeit);
         bool Waffen_Voraussetzung(const std::string& waffe);
         bool region_check(const std::string& region);
         void clear_Ausnahmen();
         void EP_uebernehmen();
         void Geld_uebernehmen();

};
#endif
