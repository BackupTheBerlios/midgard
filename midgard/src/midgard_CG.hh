// $Id: midgard_CG.hh,v 1.183 2002/02/25 10:04:26 thoma Exp $
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
#include "WindowInfo.hh"
#include "Wizard_window.hh"

class GeldFenster 
{public:
    virtual void Geld_uebernehmen()=0;
};

class midgard_CG : public midgard_CG_glade, public GeldFenster
{   
   public:
        WindowInfo *InfoFenster;
   private:

        Random random;   
        enum enum_notebook_main{PAGE_INFO,PAGE_GRUNDWERTE,PAGE_LERNEN,PAGE_STEIGERN,
                                  PAGE_AUSRUESTUNG,PAGE_NEWS};
        enum enum_notebook_lernen{PAGE_FERTIGKEITEN,PAGE_WAFFEN,PAGE_ZAUBER,
                                  PAGE_KIDO,PAGE_SPRACHE};
        enum enum_lernschema_zusatz{LZHERKUNFT,LZGEHEIMZEICHEN,LZABRICHTEN,
                                 LZTIERSPRACHE,LZMUSIZIEREN,LZSCHARFSCHIESSEN,
                                 LZLAND};


        std::vector<std::string> Vstand, Vhand, Vkido;

        friend class midgard_CG_glade;
        friend class Wizard_window;
        friend class Midgard_Info;
        Wizard_window *wizard;

        Gtk::Menu *menu, *menu_gradanstieg;
        void menu_init();
        void menu_gradanstieg_init();
        void Optionen_init();
        void Hausregeln_init();
        void pdfViewer_init();
        gint on_eventbox_MCG_button_press_event(GdkEventButton *event);

     
        enum pdfViewerIndex {gv,acroread};
        struct st_pdfViewer {pdfViewerIndex index; 
                             Gtk::RadioMenuItem *radio_menu_item;
                             std::string text;
                             bool active;
               st_pdfViewer(pdfViewerIndex i,Gtk::RadioMenuItem *r,
                            std::string t, bool a) 
                  : index(i),radio_menu_item(r),text(t),active(a) {} };

        enum OptionenIndex {Original,Info,showPics,LernschemaSensitive,
                            WizardStarten,Wizard_immer_starten,gw_wuerfeln,
                            LernschemaZusaetzeLoeschen};
        enum HausIndex {Gold};


        struct st_OptionenM{OptionenIndex index;
                           Gtk::MenuItem *menuitem; 
                           std::string text;
                           const char * const *bild;
               st_OptionenM(OptionenIndex i,
                           Gtk::MenuItem *m,
                           std::string t,
                           const char * const * const b)
                  :index(i),menuitem(m),text(t),bild(b)
                    {}};
        struct st_Optionen{OptionenIndex index;
                           Gtk::CheckMenuItem *checkmenuitem; 
                           std::string text;
                           bool active;const char * const *bild;
               st_Optionen(OptionenIndex i,
                           Gtk::CheckMenuItem *cm,
                           std::string t,
                           bool a, const char * const * const b)
                  :index(i),checkmenuitem(cm),text(t),active(a),bild(b) 
                  {}};
        

        Gtk::MenuItem *haus_menuitem;
        struct st_Haus{HausIndex index; Gtk::CheckMenuItem *menu;std::string text;bool active;
               st_Haus(HausIndex i,Gtk::CheckMenuItem *m,std::string t,bool a)
                      :index(i),menu(m),text(t),active(a) {}
                      };

        void set_tree_titles();

        struct st_BKategorie{bool kat_I; bool kat_II; bool kat_III; bool kat_IV;
             st_BKategorie(): kat_I(false),kat_II(false),kat_III(false),kat_IV(false) {}
             st_BKategorie(bool a,bool b, bool c, bool d)
               : kat_I(a),kat_II(b),kat_III(c),kat_IV(d) {}
             };
        st_BKategorie BKategorie;


        Datenbank Database;
        std::list<cH_MidgardBasicElement> list_Beruf;
        std::list<cH_MidgardBasicElement> list_Fertigkeit_ang;
        std::list<cH_MidgardBasicElement> list_Fertigkeit;
        std::list<std::string>            list_FertigkeitZusaetze;
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

        std::list<st_Haus> list_Hausregeln;
        std::list<st_Optionen>  list_Optionen;
        std::list<st_OptionenM> list_OptionenM;
        std::list<st_pdfViewer> list_pdfViewer;

        st_Optionen OptionenCheck(OptionenIndex oi);
        st_Haus HausregelCheck(HausIndex hi);
        st_pdfViewer pdfViewerCheck(pdfViewerIndex pi);

        void setOption(std::string os,bool b);
        void setHausregeln(std::string hs,bool b);
        void setpdfViewer(std::string is,bool b);
        void setAllHausregeln(bool b);

        void Hausregeln_setzen_from_menu(HausIndex index);
        void Optionen_setzen_from_menu(OptionenIndex index);
        void OptionenM_setzen_from_menu(OptionenIndex index);
        void pdfViewer_setzen_from_menu(pdfViewerIndex index);

        bool modify_bool;
        bool kido_bool;
        int maxkido;
        bool magie_bool;
        bool steigern_mit_EP_bool;

        vector<cH_Typen> Typ;
        Lernpunkte lernpunkte;
     
     	  std::string filename;
   
        // Wizard
        bool wizard_starten_bool;
        void on_button_close_wizard_clicked();
//        void on_button_wizard_weiter_clicked();
//        void on_button_wizard_wiederholen_clicked();
        void wizard_do_nothing();
        void wizard_do_something();
        void wizard_starten_clicked();

        void optionmenu_init();
        void optionmenu_stand_deactivate();
        void optionmenu_hand_deactivate();
        void pdf_viewer();
        void regnot(const std::string& sadd);
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
        void check_350(const std::vector<int>& a);
        gint on_button_grundwerte_button_release_event(GdkEventButton *ev);
        void Eigenschaften_variante(int i);
        void grundwerte_wuerfeln();
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
        void on_button_grda1setzen_clicked();
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
        gint on_entry_nameC_focus_out_event(GdkEventFocus *ev);
        gint on_entry_nameS_focus_out_event(GdkEventFocus *ev);
        gint on_entry_version_focus_out_event(GdkEventFocus *ev);
        gint on_entry_spezialisierung_focus_out_event(GdkEventFocus *ev);
        gint on_entry_glaube_focus_out_event(GdkEventFocus *ev);
        gint on_entry_herkunft_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_grad_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_lp_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_ap_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_Cgewicht_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_groesse_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_alter_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_gfp_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_tage_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_gg_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_sg_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_st_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_gw_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_gs_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_ko_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_in_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_zt_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_sb_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_wk_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_au_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_pa_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_b_focus_out_event(GdkEventFocus *ev);

        void edit_sensitive(bool b);
        void on_abge_werte_setzen_clicked();
        void original_midgard_check();
        void on_neuer_charakter_clicked();
        void clear_gtk();
        void clear_listen();
        void on_button_hilfe_clicked();
        void on_charakter_beschreibung_clicked();
//        void charakter_db_anlegen();
//        void on_laden_clicked();
//        void load_charakter(std::string name, std::string version);
        void load_fertigkeiten(IF_XML(const Tag *tag, const Tag *waffen_b, int xml_version));
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
        void LaTeX_kopfzeile(ostream &fout,bool landscape,bool newdoc=true);
        void LaTeX_footer(ostream &fout);
        std::string LaTeX_string(int i);
        void on_schliessen_CG_clicked();
        gint on_midgard_CG_delete_event(GdkEventAny* event);


        void on_lernpunkte_wuerfeln_clicked();
        void on_tree_gelerntes_leaf_selected(cH_RowDataBase d);
        void on_tree_lernschema_leaf_selected(cH_RowDataBase d);
        void show_gelerntes();
        void show_lernschema(const MidgardBasicElement::MBEE& what,const std::string& fert="");
        void setTitels_for_Lernschema(const MidgardBasicElement::MBEE& what,const std::string& fert);
        void on_spinbutton_fach_activate();
        void on_spinbutton_allgemein_activate();
        void on_spinbutton_unge_activate();
        void on_spinbutton_waffen_activate();
        void on_spinbutton_zaubern_activate();
        gint on_spinbutton_fach_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_allgemein_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_unge_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_waffen_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_zaubern_focus_out_event(GdkEventFocus *ev);
        void on_togglebutton_lernpunkte_edit_toggled();
        void edit_lernpunkte(bool b);
        void set_lernpunkte();
        void on_button_fach_trans_clicked();
        void on_button_waffe_trans_clicked();
        gint on_button_ruestung_button_release_event(GdkEventButton *ev);
        void on_button_ruestung_clicked();
        gint on_button_lernschema_geld_button_release_event(GdkEventButton *ev);
        gint on_button_lernschema_waffen_button_release_event(GdkEventButton *ev);
        void lernschema_geld_wuerfeln();
        void on_button_geld_s_clicked();
        void on_button_ruestung_s_clicked();
        void on_button_waffen_s_clicked();
        void on_lernliste_wahl_toggled();
        void spezialgebiet_button();
        void spezialgebiet_button_fill();
        void magier_spezialgebiet(const std::string& whattodo);
        void get_spezial_from_spezialgebiet();
        gint on_button_beruf_release_event(GdkEventButton *ev);
        void on_entry_berufsname_activate();
        void on_spinbutton_beruf_activate();
        void on_beruf_tree_leaf_selected(cH_RowDataBase d);
        void deleteBerufsFertigekeit();
        void showBerufsLernList();
        void beruf_gewuerfelt(int wurf);
        void on_kido_wahl_clicked();
        void stil_optionmenue();
        void zeige_lernpunkte();
        gint on_angeborene_fertigkeit_button_release_event(GdkEventButton *ev);
        void on_angeborene_fertigkeit_clicked();
        void on_angeborene_fertigkeit_right_clicked();
        void universal_Fertigkeiten();
        void on_spezialwaffe_clicked();
        void checkbutton_original(bool active);
        void lernschema_sensitive(bool active);
        void Pics(bool b);
        void show_gw_wuerfeln(bool b);
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
        void set_lernzeit(int kosten);
        bool steigern_usp(int kosten,const cH_MidgardBasicElement *MBE,e_was_steigern was=Nichts);
        void desteigern(unsigned int kosten);
        void on_checkbutton_EP_Geld_toggled();
        void steigern_gtk();
        int steigern_womit(const std::string& fert);

        void on_notebook_main_switch_page(Gtk::Notebook_Helpers::Page* page,guint pagenr);
        gint on_eventbox_ausruestung_button_release_event(GdkEventButton *event);
        gint on_eventbox_steigern_button_release_event(GdkEventButton *event);
        gint on_eventbox_lernen_button_release_event(GdkEventButton *event);
        gint on_eventbox_grundwerte_button_release_event(GdkEventButton *event);

        gint on_button_kurz_steigern_release_event(GdkEventButton *event);

        void on_notebook_lernen_switch_page(Gtk::Notebook_Helpers::Page* page,guint pagenr);
        void load_for_page(guint pagenr);
        void on_radio_steigern_toggled();
        void on_radio_reduzieren_toggled();
        void on_radio_verlernen_toggled();
        void on_radio_steigern_all();
        void on_togglebutton_praxispunkte_toggled();
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
        void lernen_zusatz(MidgardBasicElement::eZusatz was,const cH_MidgardBasicElement& _MBE);
        void lernen_zusatz_titel(MidgardBasicElement::eZusatz was,const cH_MidgardBasicElement& MBE);
        void on_herkunft_leaf_selected(cH_RowDataBase d);
        void on_zusatz_leaf_selected(cH_RowDataBase d);
        void on_zusatz_leaf_sprache_selected(cH_RowDataBase d);
        void on_zusatz_leaf_schrift_selected(cH_RowDataBase d);

        void on_fertigkeiten_laden_clicked();
        void fertigkeiten_zeigen();
        void show_alte_fertigkeiten();
        void on_leaf_selected_alte_fert(cH_RowDataBase d);
        void show_neue_fertigkeiten();
        void on_leaf_selected_neue_fert(cH_RowDataBase d);
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

        void on_zauber_laden_clicked();
        void on_alte_zauber_reorder();
        void zauber_zeigen();
        void on_spruchrolle_toggled();
        void on_togglebutton_zaubersalze_toggled();
        void on_togglebutton_alle_zauber_toggled();
        bool spruchrolle_wuerfeln(const cH_MidgardBasicElement& zauber);
        void on_leaf_selected_alte_zauber(cH_RowDataBase d);
        void on_leaf_selected_neue_zauber(cH_RowDataBase d);
        void on_leaf_selected_alte_zauberwerk(cH_RowDataBase d);
        void on_leaf_selected_neue_zauberwerk(cH_RowDataBase d);
        void zauberwerk_laden();
        void zauberwerk_zeigen();
        void on_alte_zaubermittel_reorder();

        void on_kido_laden_clicked();
        void kido_zeigen();
        void on_leaf_selected_alte_kido(cH_RowDataBase d);
        void on_leaf_selected_neue_kido(cH_RowDataBase d);
        void on_alte_kido_reorder();

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
        gint on_button_ausruestung_druck_release_event(GdkEventButton *event);
        void on_ausruestung_druck(bool unsichtbar);
        void ausruestung_druck(ostream &fout,bool unsichtbar,const list<AusruestungBaum> &AB,int deep);
        void on_clist_preisliste_select_row(gint row, gint column, GdkEvent *event);
        void on_preise_leaf_selected(cH_RowDataBase d);        
        void on_button_modi_clicked();
        void show_modi();
        void setStandardAusruestung();
        void setFertigkeitenAusruestung(AusruestungBaum *Rucksack);
        void InfoFensterAusruestung(std::string name,int wurf,int noetig);
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

         gint on_speichern_release_event(GdkEventButton *ev);
         void save_options();
         void load_options();
         void grundwerte_speichern(ostream &);
         void save_ausruestung(ostream &datei,const list<AusruestungBaum> &AB,const int indent=4);
         void load_ausruestung(const Tag *tag, AusruestungBaum *AB);
         gint on_laden_release_event(GdkEventButton *ev);
         void xml_export_auswahl();
         void xml_import_auswahl();
         void zeige_werte(const Grundwerte& w);
         void show_sinne();
         bool MidgardBasicElement_leaf_alt(const cH_RowDataBase &d);
         void MidgardBasicElement_leaf_neu(const cH_RowDataBase &d);
         // Werte in der Oberfläche setzen (z.B. nach laden)
         void Typ_Geschlecht_Spezies_setzen(); // uvm.

   public:
         midgard_CG(const string &datei="");
         Grundwerte Werte;

	// werden von anderen Fenstern aufgerufen
        bool SpracheSchrift(const cH_MidgardBasicElement& MBE,int wert=0,bool auswahl=false);
         void kaempfer_lernt_zaubern(cH_MidgardBasicElement);
         void doppelcharaktere();
         void xml_export(const std::string& datei);
         void xml_import(const std::string& datei);
         void spielleiter_export_save(const std::string& dateiname);
         void charakter_beschreibung_uebernehmen(const std::string& b,bool drucken);
//         void waffe_besitz_uebernehmen(const std::list<cH_MidgardBasicElement>& wbu);
         void MidgardBasicElement_uebernehmen(const std::list<cH_MidgardBasicElement>& mbe,
                                              const std::list<cH_MidgardBasicElement>& mbe2=std::list<cH_MidgardBasicElement>());
         void MidgardBasicElement_uebernehmen(const cH_MidgardBasicElement& mbe,bool beruf=false);
         bool region_check(const std::string& region);
         void EP_uebernehmen();
         void Geld_uebernehmen();

	 // diese Funktion sorgt für klare Verhältnisse beim Steigern,
	 // wurde früher mittels on_speichern_clicked() aufgerufen
         void steigern_aktivieren()
         {  frame_steigern->set_sensitive(true);
            on_radio_steigern_all();
            modify_bool=false;
         }
//         void on_speichern_clicked();
};
#endif
