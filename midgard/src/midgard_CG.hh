// $Id: midgard_CG.hh,v 1.245 2002/05/24 14:06:52 thoma Exp $
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

/*
class GeldFenster 
{public:
    virtual void Geld_uebernehmen()=0;
};
*/
class midgard_CG : public midgard_CG_glade //, public GeldFenster
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
        friend class table_steigern;
        friend class table_ausruestung;
        friend class Window_Erfahrungspunkte;
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
        Abenteurer Char;

        Gtk::MenuItem *ansicht_menu,*region_menu;
        Gtk::Menu *menu;
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
        gint on_eventbox_MCG_button_press_event(GdkEventButton *event);

        Datenbank Database;
   public:
        void setWindowPosition(int x,int y);
        void setWindowSize(int width,int height);
   private:
        std::list<cH_MidgardBasicElement> list_Fertigkeit_universal;

    public:
        bool fire_enabled;
    private:

    private:
        bool modify_bool;

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
//        void get_spezial_from_spezialgebiet();
//        void on_spezialwaffe_clicked();
        void checkbutton_original(bool active);
        void lernschema_sensitive(bool active);
   private:
        void on_checkbutton_Regionen_menu(Gtk::CheckMenuItem *menu_item,cH_Region region);

        void on_notebook_main_switch_page(Gtk::Notebook_Helpers::Page* page,guint pagenr);
        gint on_eventbox_ausruestung_button_release_event(GdkEventButton *event);
        gint on_eventbox_credits_button_release_event(GdkEventButton *event);
        gint on_eventbox_geschichte_button_release_event(GdkEventButton *event);
        gint on_eventbox_optionen_button_release_event(GdkEventButton *event);
        gint on_eventbox_beschreibung_button_release_event(GdkEventButton *event);
        gint on_eventbox_steigern_button_release_event(GdkEventButton *event);
        gint on_eventbox_lernen_button_release_event(GdkEventButton *event);
        gint on_eventbox_grundwerte_button_release_event(GdkEventButton *event);


        void menu_geschichte_selected();
        void menu_einstellungen_aendern();
        void load_for_mainpage(guint pagenr);


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
         
         // Werte in der Oberfläche setzen (z.B. nach laden)
         void Typ_Geschlecht_Spezies_setzen(); // uvm.

         bool nsc_check(bool nsc_only);
         

   public:
         midgard_CG(const string &datei="");
         ~midgard_CG();

	// werden von anderen Fenstern aufgerufen
         void zeige_werte();
 
         void xml_export(const std::string& datei);
         void xml_import(const std::string& datei);
         void xml_import_stream(istream &datei);
         const std::string get_filename() const { return filename; }
         void spielleiter_export_save(const std::string& dateiname);
         bool region_check(const std::string& region);
};
#endif