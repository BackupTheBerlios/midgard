// $Id: midgard_CG.cc,v 1.226 2002/05/17 10:24:28 thoma Exp $
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

#include "midgard_CG.hh"
#include "Window_hilfe.hh"
#include "Window_Geld_eingeben.hh"
#include "Window_ruestung.hh"
#include "Window_Waffenbesitz.hh"
#include <gtk--/notebook.h>
#include <gtk--/main.h>
#include "Midgard_Info.hh"
#include "Fertigkeiten.hh"
#include <unistd.h>
#ifdef __MINGW32__
#include <time.h>
#endif

midgard_CG::midgard_CG(const string &datei)
: InfoFenster(0),wizard(0), MOptionen(0),menu(0),menu_gradanstieg(0),
  Database(Midgard_Info),fire_enabled(true)
{
  ansicht_menu = manage(new Gtk::MenuItem("Ansicht"));
  region_menu = manage(new Gtk::MenuItem("Regionen"));
  main_menubar->append(*ansicht_menu);
  main_menubar->append(*region_menu);
  ansicht_menu->show();
  region_menu->show();
  
  set_sensitive(true);  
//  notebook_main->set_sensitive(true); // solange die Datenbank nicht geladen ist
                                      // stürzt das Programm ab
  srand(time(0));
  Typ.resize(2);
  InfoFenster = manage(new WindowInfo(this));
  MOptionen = new Midgard_Optionen(this); 
  table_optionen->set_Hauptfenster(this);

  set_tree_titles();
//  optionmenu_init();  
  MOptionen->load_options();
//  Midgard_Info->database_hide();
  on_neuer_charakter_clicked();

  if (!datei.empty()) xml_import(datei); // Charakter laden
  else if(MOptionen->OptionenCheck(Midgard_Optionen::Wizard_immer_starten).active) on_wizard_starten_activate();
  // für die NEWS
  Gtk::OStream os(list_news);
  os << 
#include"NEWS.h" 
   <<'\n';
}

midgard_CG::~midgard_CG()
{  cout << "~midgard_CG()\n";
   delete MOptionen;
   if (menu) delete menu;
   if (menu_gradanstieg) delete menu_gradanstieg;
//   InfoFenster->destroy(); 
   if(wizard) delete wizard;
}

/*
void midgard_CG::optionmenu_init()
{
  Vkido.resize(4);
  Vkido[0]="TECHNIK";
  Vkido[1]="Sanfte Techniken";
  Vkido[2]="Harte Techniken";
  Vkido[3]="Gemischte Techniken";
}
*/

gint midgard_CG::on_eventbox_MCG_button_press_event(GdkEventButton *event) 
{ 
   if (event->button == 3) 
   {  menu->popup(event->button,event->time);
      return true;
   }
   return false;
}

gint midgard_CG::on_button_menu_button_release_event(GdkEventButton *event)
{
  menu->popup(event->button,event->time);
  return true;
}
 

void midgard_CG::set_tree_titles()
{
 std::vector<string> preis;
 preis.push_back("Art");
 preis.push_back("");
 preis.push_back("Kategorie");
 preis.push_back("Eigenschaft");
 preis.push_back("Kostenfaktor");
 preise_tree->setTitles(preis);
}


void midgard_CG::show_gtk()
{
 steigern_typ->set_text(Typ[0]->Name(Werte.Geschlecht()));     // Abenteurerklasse im Lernfenster
 if (Typ[1]->Name(Werte.Geschlecht())!="") 
   steigern_typ->set_text(Typ[0]->Name(Werte.Geschlecht())+"/"+Typ[1]->Name(Werte.Geschlecht()));
 
 
 zeige_werte();
// show_gelerntes();
 EP_uebernehmen();
 Geld_uebernehmen();
 steigern_gtk();

/*
 // Spezialwaffe anzeigen?
 if (Typ[0]->Spezialwaffe() || Typ[1]->Spezialwaffe()) 
    togglebutton_spezialwaffe->show(); 
 else 
   { togglebutton_spezialwaffe->set_active(false);
     togglebutton_spezialwaffe->hide(); }
*/

 // Magie anzeigen?
 if (Typ[0]->is_mage() || Typ[1]->is_mage() )//|| magie_bool) 
   { 
//   if (Typ[0]->Spezialgebiet() || Typ[1]->Spezialgebiet()) show_magier_spezialgebiet(true);
//     else show_magier_spezialgebiet(false);
//     button_zauber->set_sensitive(true);
     table_magier_steigern->show();
   }
 else 
   { 
//     show_magier_spezialgebiet(false);
//     button_zauber->set_sensitive(false);
     table_magier_steigern->hide();
   }
 // KiDo anzeigen?
 if(cH_Fertigkeit("KiDo")->ist_gelernt(list_Fertigkeit))
   {
//     optionmenu_KiDo_Stile->show();
//     frame_KiDo_lernschema->show();     
     table_kido_steigern->show();
   }
 else 
   { 
//     optionmenu_KiDo_Stile->hide();
//     frame_KiDo_lernschema->hide();     
     table_kido_steigern->hide();
   }
/*
 // KiDo Stil setzen
 int kido_stil_nr=0;
 if (Werte.Spezialisierung()==Vkido[2]) kido_stil_nr = 1;
 if (Werte.Spezialisierung()==Vkido[1]) kido_stil_nr = 2;
 if (Werte.Spezialisierung()==Vkido[3]) kido_stil_nr = 3;
 if (kido_stil_nr!=0)
  {   
    optionmenu_KiDo_Stile->set_history(kido_stil_nr);
  }
*/
}


void midgard_CG::on_button_hilfe_clicked()
{
  manage(new Window_hilfe()); 
}

void midgard_CG::on_button_html_hilfe_clicked()
{
  std::string pfad;
  if(!access("../docs/index.html",R_OK))  pfad="$PWD/../docs/index.html";
  else pfad=PACKAGE_DATA_DIR"/docs/index.html";
  std::string s =MOptionen->getString(Midgard_Optionen::html_viewer)+" "+pfad+" &";
  system(s.c_str());
}

void midgard_CG::on_button_info_clicked()
{
  notebook_main->set_page(PAGE_INFO);
}


void midgard_CG::on_button_geld_s_clicked()
{
  manage (new  Window_Geld_eingeben(this, Werte));
}
void midgard_CG::on_button_ruestung_s_clicked()
{
  manage (new Window_ruestung(Werte,this,Database));
}
void midgard_CG::on_button_waffen_s_clicked()
{
  manage (new Window_Waffenbesitz(this,list_Waffen,list_Waffen_besitz));
}


void midgard_CG::set_wizard(std::string s)
{
  label_wizard->show();
  label_wizard->set_text(s);
}

void midgard_CG::set_status(std::string s,bool autoclean)
{
  label_status->set_text(s);
  if(autoclean)
     connection_status=Gtk::Main::timeout.connect(slot(this,&midgard_CG::timeout_status),7000);
}

gint midgard_CG::timeout_status()
{
  label_status->set_text("");
  return 0;
}



/*****************************************************************/

void midgard_CG::clear_listen()
{
   list_Fertigkeit.clear();
   table_lernschema->list_FertigkeitZusaetze.clear();
   list_Fertigkeit_neu.clear();
   list_Fertigkeit_ang.clear();
   list_Waffen.clear();
   list_Waffen_neu.clear();
   list_WaffenGrund.clear();
   list_WaffenGrund_neu.clear();
   list_Waffen_besitz.clear();
   list_Kido.clear();
   list_Kido_neu.clear();
   list_Beruf.clear();
   list_Sprache.clear();
   list_Schrift.clear();
   list_Sprache_neu.clear();
   list_Schrift_neu.clear();
   list_Zauber.clear();
   list_Zauberwerk.clear();
   list_Zauber_neu.clear();
   list_Zauberwerk_neu.clear();
   besitz.clear();
}

void midgard_CG::clear_gtk()
{
   table_lernschema->tree_gelerntes->clear();

   alte_fert_tree->clear();
   neue_fert_tree->clear();
   alte_waffen_tree->clear();
   neue_waffen_tree->clear();
   alte_grund_tree->clear();
   neue_grund_tree->clear();
   alte_zauber_tree->clear();
   neue_zauber_tree->clear();
   alte_zaubermittel_tree->clear();
   neue_zaubermittel_tree->clear();
   alte_kido_tree->clear();
   neue_kido_tree->clear();
   alte_sprache_tree->clear();
   neue_sprache_tree->clear();
   alte_schrift_tree->clear();
   neue_schrift_tree->clear();
  
}

gint midgard_CG::on_neuer_charakter_release_event(GdkEventButton *ev)
{
   on_neuer_charakter_clicked();
   if (ev->button==1)  on_wizard_starten_activate();
   return false;
}

void midgard_CG::on_neuer_charakter_clicked()
{
  notebook_main->set_page(PAGE_GRUNDWERTE);
   if(modify_bool)
     {
       MOptionen->save_options(InfoFenster);
       xml_export_auswahl();
     }               
   filename="";
  table_grundwerte->neuer_charakter();

   table_lernschema->label_lernschma_titel->set_text("");
   frame_steigern->set_sensitive(false); // das wirkt nicht ?
   frame_lernschema->set_sensitive(false);
   table_lernschema->togglebutton_lernpunkte_edit->set_active(false);
   table_lernschema->button_beruf->set_sensitive(false);

   table_lernschema->button_lernpunkte->set_sensitive(false);
   table_lernschema->togglebutton_lernpunkte_edit->set_sensitive(false);
   table_lernschema->button_lernschema_geld->set_sensitive(false);
   table_lernschema->button_lernschema_waffen->set_sensitive(false);
   table_lernschema->button_ruestung->set_sensitive(false);
   label_wizard->hide();

   table_lernschema->edit_lernpunkte(false);
   table_lernschema->frame_lernschema_zusatz->hide();

   table_lernschema->button_fachkenntnisse->set_sensitive(false);
   table_lernschema->button_allgemeinwissen->set_sensitive(false);
   table_lernschema->button_untyp_fertigkeiten->set_sensitive(false);
   table_lernschema->button_waffen->set_sensitive(false);
   table_lernschema->button_zauber->set_sensitive(false);
   table_lernschema->togglebutton_spezialwaffe->set_active(false);
   table_lernschema->togglebutton_spezialwaffe->hide();
      
   scrolledwindow_landauswahl->hide();
   spinbutton_pp_eingeben->hide();
   vbox_praxispunkte->hide();
   table_gruppe->hide();
   table_artikel->hide();
   togglebutton_gruppe_neu->hide(); // nicht implementiert

   togglebutton_praxispunkte->set_active(false);


   table_lernschema->vbox_berufsname->hide();
   table_lernschema->button_kido_auswahl->set_sensitive(false);       
   table_lernschema->button_angeborene_fert->set_sensitive(false);


   table_lernschema->lernpunkte.clear();
   Typ.clear();
   Typ.resize(2);
   for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
      (*i)->setActive(false);
   steigern_mit_EP_bool=true;
   checkbutton_EP_Geld->set_active(steigern_mit_EP_bool);

   Werte.set_Grad_Basiswerte(1);
   label_EP->set_text("50%");
   label_Gold->set_text("50%");

  menu_init();
//  zeige_lernpunkte();
  table_grundwerte->neuer_charakter();
}

void midgard_CG::on_schliessen_CG_clicked()
{
     MOptionen->save_options(InfoFenster);
  if(modify_bool)
   {
     MOptionen->save_options(InfoFenster);
     xml_export_auswahl();
     return;
   }
  connection_status.disconnect();
  Gtk::Main::instance()->quit();
}

gint midgard_CG::on_midgard_CG_delete_event(GdkEventAny* event)
{
  on_schliessen_CG_clicked();
  return true;
}
