// $Id: midgard_CG.hh,v 1.244 2002/05/22 17:00:44 thoma Exp $
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

#include <vector>
#include <list>
#include "zufall.h"
#include "Datenbank.hh"
class Random;
#include <fstream>
#include "WindowInfo.hh"
#include "Wizard.hh"
#include "Midgard_Undo.hh"
#include "Optionen.hh"
#include "Waffe.hh"
#include "Abenteurer.hh"

class GeldFenster 
{public:
    virtual void Geld_uebernehmen()=0;
};

class midgard_CG : public midgard_CG_glade, public GeldFenster
{   
/////////////////////////////////////////////////////////////////////////////
        friend class LaTeX_drucken;
        friend class Window_Waffenbesitz;
        friend class Data_waffenbesitz;
        friend class Data_SimpleTree;
        friend class WindowInfo;      
        friend class xml_fileselection;
        friend class frame_globale_optionen;
        friend class frame_ansicht;
        friend class table_optionen;
        friend class table_beschreibung;
        friend class table_grundwerte;
        friend class table_lernschema;
        friend class table_ausruestung;
   private:
        // Drucken
        void on_alles_drucken();
        void on_abenteurerdokument_drucken();
        void on_leeres_abenteurerdokument_drucken();
        gint on_latex_release_event(GdkEventButton *ev);
        void on_beschreibung_drucken();
        void on_nur_sichtbares_drucken();
        void on_auch_unsichtbares_drucken();
   protected:
        Random random;   

        void undosave(std::string s); 
        void WaffenBesitz_uebernehmen(const std::list<cH_MidgardBasicElement>& mbe);

        const Datenbank &getCDatabase() const {return Database;}
        Datenbank &getDatabase() {return Database;}
        Grundwerte &getWerte() {return Char.getWerte();}
        const Grundwerte &getCWerte() const {return Char.getCWerte();}
        Midgard_Optionen* getOptionen() const {return MOptionen;};
        const Abenteurer &getCChar() const {return Char;}
        Abenteurer &getChar() {return Char;}
   public:
        void show_beschreibung() {table_beschreibung->init(this);}


//////////////////////////////////////////////////////////


   public:
        WindowInfo *InfoFenster;
   private:

        enum enum_notebook_main{PAGE_INFO,PAGE_GRUNDWERTE,PAGE_LERNEN,PAGE_STEIGERN,
                                PAGE_BESCHREIBUNG,PAGE_AUSRUESTUNG,PAGE_OPTIONEN,
                                PAGE_NEWS};
        enum enum_notebook_lernen{PAGE_FERTIGKEITEN,PAGE_WAFFEN,PAGE_ZAUBER,
                                  PAGE_KIDO,PAGE_SPRACHE};
        enum enum_lernschema_zusatz{LZHERKUNFT,LZGEHEIMZEICHEN,LZABRICHTEN,
                                 LZTIERSPRACHE,LZMUSIZIEREN,LZSCHARFSCHIESSEN,
                                 LZLAND};


        friend class midgard_CG_glade;
        friend class Wizard;
        friend class Midgard_Optionen;
        friend class Midgard_Info;
        friend class frame_drucken;
        Midgard_Undo MidgardUndo;
        Wizard *wizard;
        Midgard_Optionen *MOptionen;
//        Grundwerte Werte;
        Abenteurer Char;

        Gtk::Menu *menu, *menu_gradanstieg;
        Gtk::MenuItem *ansicht_menu,*region_menu;
        void menu_init();
        void autoshrink(bool b);
        void show_Pics(bool b);
        void show_Menueleiste(bool b);
        void show_Knopfleiste(bool b);
        void show_Statusleiste(bool b);
        void show_Icons(bool b);
        void show_Beschriftungen(bool b);
        void show_NIcons(bool b);
        void show_NBeschriftungen(bool b);
        void show_gw_wuerfeln(bool b);

        void menubar_init();
        void menu_gradanstieg_init();
        gint on_eventbox_MCG_button_press_event(GdkEventButton *event);

        Datenbank Database;
//        std::list<cH_MidgardBasicElement> list_Beruf;
//        std::list<cH_MidgardBasicElement> list_Fertigkeit_ang;
//        std::list<cH_MidgardBasicElement> list_Fertigkeit;
   public:
        void setWindowPosition(int x,int y);
        void setWindowSize(int width,int height);
   private:
        std::list<cH_MidgardBasicElement> list_Fertigkeit_neu;
        std::list<cH_MidgardBasicElement> list_Fertigkeit_universal;
//        std::list<cH_MidgardBasicElement> list_WaffenGrund;
        std::list<cH_MidgardBasicElement> list_WaffenGrund_neu;
//        std::list<cH_MidgardBasicElement> list_Waffen;
        std::list<cH_MidgardBasicElement> list_Waffen_neu;
//        std::list<cH_MidgardBasicElement> list_Waffen_besitz;
//        std::list<cH_MidgardBasicElement> list_Zauber;
        std::list<cH_MidgardBasicElement> list_Zauber_neu;
//        std::list<cH_MidgardBasicElement> list_Zauberwerk;
        std::list<cH_MidgardBasicElement> list_Zauberwerk_neu;
//        std::list<cH_MidgardBasicElement> list_Kido;
        std::list<cH_MidgardBasicElement> list_Kido_neu;
//        std::list<cH_MidgardBasicElement> list_Sprache;
        std::list<cH_MidgardBasicElement> list_Sprache_neu;
//        std::list<cH_MidgardBasicElement> list_Schrift;
        std::list<cH_MidgardBasicElement> list_Schrift_neu;

    public:
        bool fire_enabled;
    private:

    private:
        bool modify_bool;
        bool steigern_mit_EP_bool;

//        std::vector<cH_Typen> Typ;
        
     
     	  std::string filename;
   
        // Wizard
        void on_neuer_abenteurer_mit_wizard_activate();
        void on_wizard_beenden_activate();
        void on_wizard_starten_activate();
        void wizard_do_something();
   private:

        void OptionenExecute_setzen_from_menu(Midgard_Optionen::OptionenExecuteIndex index);
        void Ober_setzen_from_menu(Gtk::CheckMenuItem *mi,Midgard_Optionen::OberIndex index);
        void pdf_viewer(const std::string& file);
        SigC::Connection connection_status;
        gint timeout_status();
   public:
        void set_info(const std::string& sadd);
        void set_status(std::string s,bool autoclean=true);
private:
        void set_wizard(std::string s);
   private:
        gint on_button_menu_button_release_event(GdkEventButton *ev);
        void Eigenschaften_variante(int i);

        void on_neuer_charakter_clicked();
        void clear_gtk();
        void clear_listen();
        void on_button_hilfe_clicked();
        void on_button_html_hilfe_clicked();

        void load_fertigkeiten(IF_XML(const Tag *tag, const Tag *waffen_b, int xml_version));
        void on_exportieren_activate();
        void on_button_info_clicked();
        void on_schliessen_CG_clicked();
        gint on_midgard_CG_delete_event(GdkEventAny* event);

   private:
        void on_button_geld_s_clicked();
        void on_button_ruestung_s_clicked();
        void on_button_waffen_s_clicked();
        void get_spezial_from_spezialgebiet();
        void on_spezialwaffe_clicked();
        void checkbutton_original(bool active);
        void lernschema_sensitive(bool active);
   private:
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
        bool steigern_usp(int kosten,cH_MidgardBasicElement *MBE,e_was_steigern was=Nichts);
        int genug_geld(const int kosten);
        int EP_kosten(const int kosten);
        int PP_vorrat(const cH_MidgardBasicElement *MBE,e_was_steigern was);
        std::string SpruecheMitPP();
        bool genug_EP(const int ep_k,const bool bkep,const bool bzep,int &aep0,int &kep0,int &zep0);
        void steigern_mit(bool &bkep,bool &bzep,const cH_MidgardBasicElement *MBE,e_was_steigern was);
        void desteigern(unsigned int kosten);
        void on_checkbutton_EP_Geld_toggled();
        void steigern_gtk();
        int steigern_womit(const std::string& fert);

        void on_notebook_main_switch_page(Gtk::Notebook_Helpers::Page* page,guint pagenr);
        gint on_eventbox_ausruestung_button_release_event(GdkEventButton *event);
        gint on_eventbox_credits_button_release_event(GdkEventButton *event);
        gint on_eventbox_geschichte_button_release_event(GdkEventButton *event);
        gint on_eventbox_optionen_button_release_event(GdkEventButton *event);
        gint on_eventbox_beschreibung_button_release_event(GdkEventButton *event);
        gint on_eventbox_steigern_button_release_event(GdkEventButton *event);
        gint on_eventbox_lernen_button_release_event(GdkEventButton *event);
        gint on_eventbox_grundwerte_button_release_event(GdkEventButton *event);

        gint on_button_kurz_steigern_release_event(GdkEventButton *event);

        void on_notebook_lernen_switch_page(Gtk::Notebook_Helpers::Page* page,guint pagenr);
        void menu_geschichte_selected();
        void menu_einstellungen_aendern();
        void load_for_mainpage(guint pagenr);
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

         gint on_neuer_charakter_release_event(GdkEventButton *ev);
         gint on_speichern_release_event(GdkEventButton *ev);
         void grundwerte_speichern(ostream &);
         void save_ausruestung(ostream &datei,const list<AusruestungBaum> &AB,const int indent=4);
         void load_ausruestung(const Tag *tag, AusruestungBaum *AB);
         gint on_laden_release_event(GdkEventButton *ev);
         void xml_export_auswahl();
         void save_existing_filename();
         void xml_import_auswahl();
         void speicherstream(ostream &datei);
         void show_undo_tree();
         void on_undo_leaf_selected(cH_RowDataBase d);
         void on_button_redo_clicked();
         void on_button_undo_clicked();
         
         bool MidgardBasicElement_leaf_alt(const cH_RowDataBase &d);
         void MidgardBasicElement_leaf_neu(const cH_RowDataBase &d);
         // Werte in der Oberfläche setzen (z.B. nach laden)
         void Typ_Geschlecht_Spezies_setzen(); // uvm.

         bool nsc_check(bool nsc_only);
         

   public:
         midgard_CG(const string &datei="");
         ~midgard_CG();

	// werden von anderen Fenstern aufgerufen
//         const vector<cH_Typen> &getVTyp() const {return Typ;}
         void zeige_werte();
 
         cH_MidgardBasicElement getSelectedNotebookLernen();
         void PraxisPunkt_to_AEP(cH_MidgardBasicElement& MBE,bool verfallen,bool alle_pp);
         int stufen_auf_einmal_steigern_fuer_aep(bool info,cH_MidgardBasicElement& MBE,int &kosten,int &aep);
         void xml_export(const std::string& datei);
         void xml_import(const std::string& datei);
         void xml_import_stream(istream &datei);
         const std::string get_filename() const { return filename; }
         void spielleiter_export_save(const std::string& dateiname);
         bool region_check(const std::string& region);
         void EP_uebernehmen();
         void Geld_uebernehmen();
};
#endif
