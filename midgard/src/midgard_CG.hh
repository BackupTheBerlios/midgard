// $Id: midgard_CG.hh,v 1.134 2002/01/20 19:09:36 christof Exp $
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

#ifndef _MIDGARD_CG_HH
#  include "midgard_CG_glade.hh"
#  define _MIDGARD_CG_HH
#include "glademm_support.hh"
#include "WindowInfo.hh"


#include <iostream>
#include <string>
#include <gtk--/menu.h>
#include <gtk--/menuitem.h>
#include <gtk--/ctree.h>

#include <vector>
#include <list>
#include "zufall.h"
#include "Datenbank.hh"
#include "class_lernpunkte.hh"
#include "Ausruestung.hh"
class Random;

class GeldFenster 
{public:
    virtual void Geld_uebernehmen()=0;
};

class midgard_CG : public midgard_CG_glade, public GeldFenster
{   
        Random random;   
        enum enum_notebook_main{PAGE_GRUNDWERTE,PAGE_LERNEN,PAGE_STEIGERN,
                                  PAGE_AUSRUESTUNG};
        enum enum_notebook_lernen{PAGE_FERTIGKEITEN,PAGE_WAFFEN,PAGE_ZAUBER,
                                  PAGE_KIDO,PAGE_SPRACHE};


        std::vector<std::string> Vstand, Vhand, Vkido;

   private:
        friend class midgard_CG_glade;
        Gtk::Menu *menu;
        void menu_init();
        gint on_eventbox_MCG_button_press_event(GdkEventButton *event);

        struct st_OptionBool{bool Original; bool Info; bool Pics; 
                     bool steigern;bool version;
               void reset() {*this=st_OptionBool();}
               st_OptionBool() : Original(true), Info(true),
                                 Pics(true), steigern(true),
                                  version(true) {}};
        st_OptionBool OptionBool;
        struct st_OptionMenu{Gtk::CheckMenuItem *menu_original;
                             Gtk::CheckMenuItem *menu_info;
                             Gtk::CheckMenuItem *menu_pics;
                             Gtk::CheckMenuItem *menu_version;};
        st_OptionMenu OptionMenu;

        void set_tree_titles();

//        st_Database Database;
        Datenbank Database;
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
#ifdef USE_XML
	std::string filename;
#endif
   
//        void get_Database();
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
//        void werte_editieren();
        void on_togglebutton_edit_werte_toggled();
        void set_all_entrys();
        void on_entry_nameC_activate();
        void on_entry_nameS_activate();
        void on_entry_version_activate();
        void on_entry_spezialisierung_activate();
        void on_entry_glaube_activate();
        void on_entry_herkunft_activate();
        void on_spinbutton_grad_activate();
        void on_spinbutton_lp_activate();
        void on_spinbutton_ap_activate();
        void on_spinbutton_Cgewicht_activate();
        void on_spinbutton_groesse_activate();
        void on_spinbutton_alter_activate();
        void on_spinbutton_gfp_activate();
        void on_spinbutton_tage_activate();
        void on_spinbutton_gg_activate();
        void on_spinbutton_sg_activate();
        void on_spinbutton_st_activate();
        void on_spinbutton_gw_activate();
        void on_spinbutton_gs_activate();
        void on_spinbutton_ko_activate();
        void on_spinbutton_in_activate();
        void on_spinbutton_zt_activate();
        void on_spinbutton_sb_activate();
        void on_spinbutton_wk_activate();
        void on_spinbutton_au_activate();
        void on_spinbutton_pa_activate();
        void on_spinbutton_b_activate();

        void edit_sensitive(bool b);
        void on_abge_werte_setzen_clicked();
        void original_midgard_check();
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
        void LaTeX_header(ostream &fout,bool landscape=true);
        void LaTeX_footer(ostream &fout);
        std::string LaTeX_string(int i);
        void on_schliessen_CG_clicked();
        void on_lernpunkte_wuerfeln_clicked();
        void on_spinbutton_fach_activate();
        void on_spinbutton_allgemein_activate();
        void on_spinbutton_unge_activate();
        void on_spinbutton_waffen_activate();
        void on_spinbutton_zaubern_activate();
        void on_togglebutton_lernpunkte_edit_toggled();
        void edit_lernpunkte(bool b);
        void on_entry_Cname_activate();
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
//        void on_checkbutton_original_toggled();
        void on_checkbutton_info_fenster_menu();
        void on_checkbutton_pics_menu();
        void on_checkbutton_version_menu();
        void Pics(bool b);
//        void on_checkbutton_info_fenster_toggled();
        void on_checkbutton_Regionen_menu(Gtk::CheckMenuItem *menu_item,cH_Region region);

        void on_grad_anstieg_clicked();
        void on_button_grad_ausdauer_clicked();
        void on_button_grad_basiswerte_clicked();
        void on_button_grad_abwehr_clicked();
        void on_button_grad_zaubern_clicked();
        void on_button_grad_resistenz_clicked();
        void on_button_grad_clicked();
        void get_ausdauer(int grad);
        void get_grundwerte();
        enum e_was_steigern{Nichts,Ausdauer,Abwehr,Zaubern,Resistenz};
        void get_ab_re_za(e_was_steigern was);
         
        void on_button_EP_clicked();
        gint vscale_value_changed(GdkEventButton *ev);
        void set_lernzeit(unsigned int kosten);
        bool steigern_usp(unsigned int kosten,const cH_MidgardBasicElement *MBE,e_was_steigern was=Nichts);
        void desteigern(unsigned int kosten);
        void on_checkbutton_EP_Geld_toggled();
        void steigern_gtk();
        int steigern_womit(const std::string& fert);

        void on_notebook_main_switch_page(Gtk::Notebook_Helpers::Page* page,guint pagenr);
        gint on_eventbox_ausruestung_button_release_event(GdkEventButton *event);
        gint on_eventbox_steigern_button_release_event(GdkEventButton *event);
        gint on_eventbox_lernen_button_release_event(GdkEventButton *event);
        gint on_eventbox_grundwerte_button_release_event(GdkEventButton *event);

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
        void on_button_alter_clicked();

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
        void ausruestung_druck(ostream &fout,const list<AusruestungBaum> &AB,int deep);
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
        void on_togglebutton_artikel_neu_toggled();
        void on_togglebutton_gruppe_neu_toggled();
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
//         midgard_CG(int argc,char **argv);
         midgard_CG(Datenbank& _Database);
         void doppelcharaktere();
         Grundwerte Werte;
         void on_speichern_clicked();
         gint on_speichern_release_event(GdkEventButton *ev);
         void grundwerte_speichern(IF_XML(ostream &));
         void save_ausruestung(IF_XML(ostream &));
         void save_ausruestung_C(int parent,int &self,const list<AusruestungBaum> &AB);
         void load_ausruestung(IF_XML(istream &));
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
//         void setze_lernpunkte(const Lernpunkte& _lernpunkte);
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

	 // diese Funktion sorgt für klare Verhältnisse beim Steigern,
	 // wurde früher mittels on_speichern_clicked() aufgerufen
         void steigern_aktivieren()
         {  frame_steigern->set_sensitive(true);
            on_radio_steigern_all();
         }
};
#endif
