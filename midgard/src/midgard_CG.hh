// $Id: midgard_CG.hh,v 1.277 2002/09/13 07:34:35 thoma Exp $
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
#include <gtk--/pixmap.h>

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
//#include "Region.hh"

class midgard_CG : public midgard_CG_glade
{   
        std::string argv0; // Dateiname
        std::string magus_verzeichnis;
        bool in_dtor;
/////////////////////////////////////////////////////////////////////////////
        friend class Zufall;
        friend class LernListen;
        friend class LaTeX_drucken;
        friend class Window_Waffenbesitz;
        friend class Data_waffenbesitz;
        friend class Data_SimpleTree;
        friend class WindowInfo;      
        friend class xml_fileselection;
        friend class frame_globale_optionen;
        friend class frame_ansicht;
        friend class frame_icons;
        friend class table_optionen;
        friend class table_zufall;
        friend class table_beschreibung;
        friend class table_grundwerte;
        friend class table_lernschema;
        friend class table_steigern;
        friend class table_ausruestung;
        friend class Window_Erfahrungspunkte;
        friend class Fertigkeit;
        friend class midgard_CG_glade;
        friend class Wizard;
        friend class Midgard_Optionen;
        friend class Midgard_Info;
        friend class frame_drucken;
        friend class Abenteurer;

        // Drucken
   private:
        void on_alles_drucken();
        void on_abenteurerdokument_drucken();
        void on_leeres_abenteurerdokument_drucken();
        gint on_latex_release_event(GdkEventButton *ev);
        void on_beschreibung_drucken();
        void on_nur_sichtbares_drucken();
        void on_auch_unsichtbares_drucken();
        void on_spielleiterbogen_drucken_activate();
        
        // Info Fenster
   private: 
        WindowInfo *InfoFenster;
   protected:
        void set_info(const std::string& sadd);

        // Optionen
   private:
        Midgard_Optionen *MOptionen;
        void OptionenExecute_setzen_from_menu(Midgard_Optionen::OptionenExecuteIndex index);
        void Ober_setzen_from_menu(Gtk::CheckMenuItem *mi,Midgard_Optionen::OberIndex index);
        void autoshrink(bool b);
        void show_Pics(bool b);
        void show_Menueleiste(bool b);
        void show_Knopfleiste(bool b);
        void show_Statusleiste(bool b);
        void show_Icons(bool b);
        void show_Beschriftungen(bool b);
        void show_3_Tasten_Maus(bool b);
        void show_NSC_active(bool b);
        void show_Hausregeln_active(bool b);

        enum e_icon {iNew,iOpen,iClose,iPrint,iBack,iForward,iMenu,iInfo,iHelp,
                     iInstruction,iExit,iJa,iNein,iEigenschaften,iAbgeleitet,
                     iEditGrund,iLernpunkte,iLernEdit,iBeruf,iGeld,iWaffen,
                     iRuestung,iAusruestung,iEigenschaft};
        struct st_icons{std::string text;char **icon;
               st_icons(std::string t,char **i):text(t),icon(i){}};
        struct st_buttons{Gtk::Widget *widget; e_icon icon;
               st_buttons(Gtk::Widget *w, e_icon i)
                  : widget(w),icon(i) {}};

        std::vector<st_buttons> IconVec;
        void fill_IconVec();
        st_icons StyleIcon(e_icon typ) const;
        void Icons_setzen();
        void Box_setzen(Gtk::Widget *child,st_icons I);
   protected:
        Midgard_Optionen* getOptionen() const {return MOptionen;};
        const Midgard_Optionen* getCOptionen() const {return MOptionen;};

        // Wizard
   private:
        Wizard *wizard;
        void on_neuer_abenteurer_mit_wizard_activate();
        void on_wizard_beenden_activate();
        void on_wizard_starten_activate();
        void wizard_do_something();
        void set_wizard(std::string s);
        void show_wizard_active(bool b);

        // Load & Save
   private:
        void on_exportieren_activate();
        gint on_speichern_release_event(GdkEventButton *ev);
        gint on_laden_release_event(GdkEventButton *ev);
        void xml_export_auswahl();
        void save_existing_filename();
        void xml_import_auswahl();
        void xml_import_history(const std::string datei);
   public:
         void xml_export(const std::string& datei);
         void xml_import(const std::string& datei);
         void spielleiter_export_save(const std::string& dateiname);

        // Undo
   private:
        Midgard_Undo MidgardUndo;
        void show_undo_tree();
        void on_undo_leaf_selected(cH_RowDataBase d);
        void on_button_redo_clicked();
        void on_button_undo_clicked();
   protected:
        void undosave(std::string s); 

        // Charaktere
   private:
        VAbenteurer Char;
        Datenbank Database;
        gint on_neuer_charakter_release_event(GdkEventButton *ev);
        void fill_AbenteurerListe();
        void on_AbenteurerListe_leaf(cH_RowDataBase d);
        void set_AbenteurerListe_Title();
        void on_button_quit_confirm_clicked();
        void on_togglebutton_delete_abenteurer_aus_liste_toggled();
        
   protected:
        const Datenbank &getCDatabase() const {return Database;}
        Datenbank &getDatabase() {return Database;}
        Grundwerte &getWerte() {return Char.getWerte();}
        const Grundwerte &getWerte() const {return Char.getWerte();}
        const VAbenteurer &getChar() const {return Char;}
        VAbenteurer &getChar() {return Char;}
        void Eigenschaften_variante(int i);
        void on_neuer_charakter_clicked();
        bool nsc_check(bool nsc_only);
        bool region_check(const std::string& region) const;

        // Oberfläche
   private:
        // Oberfläche Notebook 
        enum enum_notebook_main{PAGE_INFO,PAGE_GRUNDWERTE,PAGE_LERNEN,PAGE_STEIGERN,
                                PAGE_BESCHREIBUNG,PAGE_AUSRUESTUNG,PAGE_OPTIONEN,
                                PAGE_NEWS,PAGE_ZUFALL};
        void on_notebook_main_switch_page(Gtk::Notebook_Helpers::Page* page,guint pagenr);
        gint on_eventbox_ausruestung_button_release_event(GdkEventButton *event);
        gint on_eventbox_credits_button_release_event(GdkEventButton *event);
        gint on_eventbox_geschichte_button_release_event(GdkEventButton *event);
        gint on_eventbox_optionen_button_release_event(GdkEventButton *event);
        gint on_eventbox_zufall_button_release_event(GdkEventButton *event);
        gint on_eventbox_beschreibung_button_release_event(GdkEventButton *event);
        gint on_eventbox_steigern_button_release_event(GdkEventButton *event);
        gint on_eventbox_lernen_button_release_event(GdkEventButton *event);
        gint on_eventbox_grundwerte_button_release_event(GdkEventButton *event);
        void load_for_mainpage(guint pagenr);

        // Oberfläche Menü
//        Gtk::MenuItem *ansicht_menu,*region_menu;
        Gtk::Menu *menu_kontext;
        gint on_button_menu_button_release_event(GdkEventButton *ev);
        void on_checkbutton_Regionen_menu(Gtk::CheckMenuItem *menu_item,cH_Region region);
        void menubar_init();
        void menu_init();
        void menu_history_init(int oldsize);
        void menu_geschichte_selected();
        void menu_einstellungen_aendern();
        std::list<std::string> LDateien;
        void push_back_LDateien(std::string s);

        // Oberfläche Statusbar
        void init_statusbar();
        struct st_reg_status{RegionenPic::epic name; Gtk::Pixmap *pix;
               st_reg_status(RegionenPic::epic n, Gtk::Pixmap *p):name(n),pix(p){}};
        std::vector<st_reg_status> vec_region_status;
        void set_region_statusbar(RegionenPic::epic pic,bool active);

        // Oberfläche Diverses
        void setWindowPosition(int x,int y);
        void setWindowSize(int width,int height);
        gint on_eventbox_MCG_button_press_event(GdkEventButton *event);
        void pdf_viewer(const std::string& file);
        void on_button_hilfe_clicked();
        void on_button_html_hilfe_clicked();
        void on_button_info_clicked();
        void on_schliessen_CG_clicked();
        gint on_midgard_CG_delete_event(GdkEventAny* event);

        void checkbutton_original(bool active);
        void lernschema_sensitive(bool active);


       // Diverses
   private:
        SigC::Connection connection_status;
        gint timeout_status();
   protected:
        Random random;   

        void set_status(const std::string &s,bool autoclean=true);
   public:
         midgard_CG(const string &argv0,const string &_magus_verzeichnis,
                    const string &datei="");
         std::string MagusVerzeichnis() const {return magus_verzeichnis;}
         std::string BinaryVerzeichnis() const;
        std::string with_path(const std::string &name,bool path_only=false,bool noexit=false) const ;
         ~midgard_CG();
};
#endif
