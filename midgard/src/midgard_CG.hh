// $Id: midgard_CG.hh,v 1.327 2003/09/01 16:57:04 christof Exp $
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

// hier muss noch viel raus !!!
#include <iostream>
#include <string>
#include <gtkmm/menu.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/image.h>

#include <vector>
#include <list>
#include "Datenbank.hh"
#include <fstream>
#include "WindowInfo.hh"
#include "Wizard.hh"
#include "Midgard_Undo.hh"
#include "Optionen.hh"
#include "Waffe.hh"
#include "Abenteurer.hh"
#include "Region_GUI.hh"
#include <TreeViewUtility.h>
#include <config.h>
#include "Magus_Optionen.hh"

#include <libmagus/VAbenteurer.hh>
#include <Misc/compiler_ports.h>

class midgard_CG : public midgard_CG_glade
{   
        VAbenteurer Char;

//        bool in_dtor;
/////////////////////////////////////////////////////////////////////////////
        // Drucken
   public:        
        void on_auch_unsichtbares_drucken();
        void on_beschreibung_drucken();
   private:
        void on_alles_drucken();
        void on_abenteurerdokument_drucken();
        void on_leeres_abenteurerdokument_drucken();
        void on_latex();
        void on_nur_sichtbares_drucken();
        void on_spielleiterbogen_drucken_activate();
        void spielleiter_export_save_zauber(std::ostream& fout,const bool full);
        void spielleiter_export_save_ausruestung(std::ostream& fout);
        
        
        // Info Fenster
   private: 
        __deprecated WindowInfo *InfoFenster; // weg damit! jetzt �ber Ausgabe gehen!
        
        TreeViewUtility::CListEmulator news_columns;
   protected:
#warning Noch in Ausgabe packen ...
        __deprecated void set_info(const std::string& sadd);

        // Optionen
   private:
        void OptionenExecute_setzen_from_menu(Magus_Optionen::OptionenExecuteIndex index);
        void Ober_element_activate(gpointer gp,Magus_Optionen::OberIndex index);
        void autoshrink(bool b);
        void show_Pics(bool b);
        void show_Menueleiste(bool b);
        void show_Knopfleiste(bool b);
        void show_Statusleiste(bool b);
        void show_Icons(bool b);
        void show_Beschriftungen(bool b);
        void show_3_Tasten_Maus(bool b);
        void show_NSC_active(bool b);
        void show_Hausregeln_active();

#if 0
        enum e_icon {iNew,iOpen,iClose,iPrint,iBack,iForward,iMenu,iInfo,
                     iInstruction,iExit,iJa,iNein,iOK,iErase,
                     iEigenschaften,iAbgeleitet,
                     iEditGrund,iHerkunft,
                     iAngeFert,iLernpunkte,iLernEdit,iBeruf,
                     iGeld,iWaffen,
                     iRuestung,iAusruestung,iEigenschaft,iBildeinfuegen,
                     iDeleteA,iDeleteAusr,
                     iStatusWizard,iStatusNPC,iStatusHaus,
                     iButtonReduce,iButtonSteigern,
                     iButtonVerlernen,
                     iNotebookCredit,iNotebookGrundwerte,iNotebookLernen,
                     iNotebookSteigern,iNotebookBeschreibung,
                     iNotebookAusruestung,iNotebookOptionen,
                     iNotebookNEWS,iNotebookZufall};
                     
        struct st_icons{std::string text;Glib::RefPtr<Gdk::Pixbuf> icon;
               st_icons(std::string t,Glib::RefPtr<Gdk::Pixbuf> i):text(t),icon(i){}};
        struct st_buttons{Gtk::Widget *widget; e_icon icon;
               st_buttons(Gtk::Widget *w, e_icon i)
                  : widget(w),icon(i) {}};                  

        std::vector<st_buttons> IconVec;    // Für Gtk::Box
        std::vector<st_buttons> IconVecBin; // Für Gtk::Bin
        void fill_IconVec();
        st_icons StyleIcon(e_icon typ) const;
        void Icons_setzen();
        void Box_setzen(Gtk::Widget *child,st_icons I);
        void Bin_setzen(Gtk::Widget *child,st_icons I);
#endif        
   protected:
//        Magus_Optionen* getOptionen() const {return MOptionen;};
//        const Magus_Optionen* getCOptionen() const {return MOptionen;};

        // Wizard
   private:
        void on_neuer_abenteurer_mit_wizard_activate();
        void on_wizard_beenden_activate();
        void on_wizard_starten_activate();
        void wizard_do_something();
        void set_wizard(std::string s);
        void show_wizard_active(bool b);

        // Load & Save
   private:
        void on_exportieren_activate();
        void on_kompletter_export_activate();
        void on_exportieren_ranas_pdf_dokumente_activate();
        void on_speichern();
        void on_laden();
        void save_existing_filename();
        void xml_import_history(const std::string datei);
        void xml_export_auswahl();
   public:
        void xml_import_auswahl();
         void xml_export(const std::string& datei);
         void xml_import(const std::string& datei);
         void spielleiter_export_save(const std::string& dateiname,const bool full);

        // Undo
   private:
        Gtk::Menu *undo_menu;
        void show_undo_tree();
        void on_undo_leaf_selected(cH_RowDataBase d);
        void on_button_redo_clicked();
        void on_button_undo_clicked();
        void on_undo_secondpressed(int);
        void on_redo_secondpressed(int);
   protected:
        void undosave(std::string s); 

        // Charaktere
   private:
        void on_neuer_charakter();
        void fill_AbenteurerListe();
        void on_AbenteurerListe_leaf(cH_RowDataBase d);
        void set_AbenteurerListe_Title();
        void on_button_quit_confirm_clicked();
        void on_togglebutton_delete_abenteurer_aus_liste_toggled();
        
   protected:
//        Grundwerte &getWerte() {return Char->getWerte();}
//        const Grundwerte &getWerte() const {return Char->getWerte();}
public:
        const VAbenteurer &getChar() const {return Char;}
        VAbenteurer &getChar() {return Char;}
protected:
//        const Abenteurer &getAben() const {return Char.getCAbenteurer();}
//        Abenteurer &getAben() {return Char.getAbenteurer();}
        void Eigenschaften_variante(int i);
        void on_neuer_charakter_clicked();
        // Oberfläche
   public:
        // Oberfläche Notebook 
        enum enum_notebook_main{NOPAGE=-1,PAGE_INFO=0,PAGE_GRUNDWERTE,PAGE_LERNEN,PAGE_STEIGERN,
                                PAGE_BESCHREIBUNG,PAGE_AUSRUESTUNG,PAGE_OPTIONEN,
                                PAGE_NEWS,PAGE_ZUFALL};
   private:
        void on_notebook_main_switch_page(GtkNotebookPage *page,guint pagenr);
        bool on_eventbox_ausruestung_button_release_event(GdkEventButton *event);
        bool on_eventbox_credits_button_release_event(GdkEventButton *event);
        bool on_eventbox_geschichte_button_release_event(GdkEventButton *event);
        bool on_eventbox_optionen_button_release_event(GdkEventButton *event);
        bool on_eventbox_zufall_button_release_event(GdkEventButton *event);
        bool on_eventbox_beschreibung_button_release_event(GdkEventButton *event);
        bool on_eventbox_steigern_button_release_event(GdkEventButton *event);
        bool on_eventbox_lernen_button_release_event(GdkEventButton *event);
        bool on_eventbox_grundwerte_button_release_event(GdkEventButton *event);

        // Oberfläche Menü
        Gtk::Menu *menu_kontext;
        void on_button_menu();
        void on_checkbutton_Regionen_menu_(Gtk::CheckMenuItem *menu_item,cH_Region region);
        void on_checkbutton_Regionen_menu(gpointer gp,cH_Region region);
        void menubar_init();
        void menu_init();
        void menu_history_init(int oldsize);
        void menu_geschichte_selected();
        void menu_einstellungen_aendern();
        void on_anleitung_menu_activate();
        void on_info_credits_menu_activate();
        void on_news_menu_activate();
        std::list<std::string> LDateien;
        void push_back_LDateien(std::string s);
        Model<bool> schummeln;
        void Schummeln();

        // Oberfläche Statusbar
        void init_statusbar();
        struct st_reg_status{RegionenPic::epic name; Gtk::Image *pix;
               st_reg_status(RegionenPic::epic n, Gtk::Image *p):name(n),pix(p){}};
        std::vector<st_reg_status> vec_region_status;
        void set_region_statusbar(RegionenPic::epic pic,bool active);

        // Oberfläche Diverses
        void setWindowPosition(int x,int y);
        void setWindowSize(int width,int height);
        bool on_eventbox_MCG_button_press_event(GdkEventButton *event);
        void pdf_viewer(const std::string& file);
        void on_button_html_hilfe_clicked();
        void on_button_info_clicked();
        void on_schliessen_CG_clicked();
        bool on_midgard_CG_delete_event(GdkEventAny* event);

        void checkbutton_original(bool active);
        void lernschema_sensitive(bool active);


       // Diverses
   private:
//        SigC::signal_Connection().connection_status;
        bool timeout_status();
   protected:
        void set_status(const std::string &s,bool autoclean=true);
   public:
        midgard_CG(const std::vector<std::string> &dateien);
         ~midgard_CG();
         
         // neue klarere Methoden
         void WizardBeenden();
         void AndererAbenteurer();
         void LernschemaSteigern(bool l,bool s);
         void NamenEingeben() { table_grundwerte->NamenEingeben(); }

	// Nettigkeiten ?
        static Gtk::Box &make_gtk_box(Glib::RefPtr<Gdk::Pixbuf> data,const std::string &label,const bool text_vor_bild=true,const bool hbox=true);
        void load_for_mainpage(guint pagenr);
        Wizard *wizard;
};
#endif
