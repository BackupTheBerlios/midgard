// $Id: midgard_CG.hh,v 1.338 2003/10/13 06:33:03 christof Exp $
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

#include <config.h>
#include <gtkmm/menu.h>
#include <gtkmm/image.h>
#include <list>
#include "Region_GUI.hh"
#include <TreeViewUtility.h>
#include <libmagus/VAbenteurer.hh>
#include <Misc/compiler_ports.h>

class midgard_CG : public midgard_CG_glade
{public:
        // Oberfläche Notebook 
        enum enum_notebook_main{NOPAGE=-1,PAGE_GRUNDWERTE,PAGE_LERNEN,PAGE_STEIGERN,
                                PAGE_BESCHREIBUNG,PAGE_AUSRUESTUNG,PAGE_OPTIONEN,
                                PAGE_INFO,PAGE_NEWS,PAGE_ZUFALL};
private:
        VAbenteurer Char;

        TreeViewUtility::CListEmulator news_columns;
        Gtk::Menu *undo_menu;
        Gtk::Menu *menu_kontext;

        Model<bool> schummeln;

        SigC::Connection connection_status;

/////////////////////////////////////////////////////////////////////////////
        // Drucken
private:
        void on_alles_drucken();
        void on_abenteurerdokument_drucken();
        void on_leeres_abenteurerdokument_drucken();
        void on_latex();
        void on_nur_sichtbares_drucken();
        void on_spielleiterbogen_drucken_activate();
        void spielleiter_export_save_zauber(std::ostream& fout,const bool full);
        void spielleiter_export_save_ausruestung(std::ostream& fout);
        
        // Optionen
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

        // Wizard
        void set_wizard(std::string s);
        void on_neuer_abenteurer_mit_wizard_activate();
        void on_wizard_beenden_activate();
        void on_wizard_starten_activate();
        void show_wizard_active(bool b);

        // Load & Save
        void on_exportieren_activate();
        void on_kompletter_export_activate();
        void on_exportieren_ranas_pdf_dokumente_activate();
        void on_speichern();
        void on_laden();
        void save_existing_filename();
        void xml_import_history(const std::string datei);
        void xml_export_auswahl();

        // Undo
        void show_undo_tree();
        void on_undo_leaf_selected(cH_RowDataBase d);
        void on_button_redo_clicked();
        void on_button_undo_clicked();
        void on_undo_secondpressed(int);
        void on_redo_secondpressed(int);
        void undosave(std::string s); 

        // Charaktere
        void on_neuer_charakter();
        void fill_AbenteurerListe();
        void on_AbenteurerListe_leaf(cH_RowDataBase d);
        void set_AbenteurerListe_Title();
        void on_button_quit_confirm_clicked();
        void on_togglebutton_delete_abenteurer_aus_liste_toggled();
        void on_schlie__en1_activate();
        
        void Eigenschaften_variante(int i);
        void on_neuer_charakter_clicked();

        // Oberfläche
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
        void push_back_LDateien(std::string s);
        void Schummeln();

        // Oberfläche Statusbar
        void init_statusbar();
        void set_region_statusbar(RegionenPic_enum::epic pic,bool active);

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
//        SigC::signal_Connection().connection_status;
        bool timeout_status();

        void set_status(const std::string &s,bool autoclean=true);
        
        void grundwerte_background(); // on_realize

// besser in Einzelfunktionen zerlegen
	void Ober_setzen_from_menu(gpointer x,Magus_Optionen::OberIndex index);

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
        
        // Im/Export
        void xml_import_auswahl();
         void xml_export(const std::string& datei);
         void xml_import(const std::string& datei);
         void spielleiter_export_save(const std::string& dateiname,const bool full);

        const VAbenteurer &getChar() const {return Char;}
        VAbenteurer &getChar() {return Char;}
	const Abenteurer &getAben() const {return Char.getAbenteurer();}
        Abenteurer &getAben() {return Char.getAbenteurer();}

        void on_auch_unsichtbares_drucken();
        void on_beschreibung_drucken();

	// wird von Wizard verwendet
        void wizard_do_something(int page,const std::string &text);
        
//        Wizard &getWizard() { return wizard; }
};
#endif
