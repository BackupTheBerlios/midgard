// $Id: midgard_CG.cc,v 1.179 2002/03/13 09:32:35 thoma Exp $
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
#include "Window_waffe.hh"
#include "Window_Waffenbesitz.hh"
#include <gtk--/notebook.h>
#include <gtk--/main.h>
#include "Midgard_Info.hh"
#ifdef __MINGW32__
#include <time.h>
#endif

midgard_CG::midgard_CG(const string &datei)
: InfoFenster(0), wizard(0),menu(0),menu_gradanstieg(0),
  haus_menuitem(0),Database(Midgard_Info)
{
  notebook_main->set_sensitive(true); // solange die Datenbank nicht geladen ist
                                      // stürzt das Programm ab
  srand(time(0));
  if(InfoFenster) delete(InfoFenster);
  InfoFenster = manage(new WindowInfo(this));

  set_tree_titles();
  optionmenu_init();  
  Optionen_init();
  Hausregeln_init();
  pdfViewer_init();

  load_options();
  on_neuer_charakter_clicked();
  notebook_main->set_page(PAGE_GRUNDWERTE); // muß nach 'on_neuer_charakter_clicked' kommen wg. Typ.resize(2)
  if (!datei.empty()) xml_import(datei); // Charakter laden
  else if(OptionenCheck(Wizard_immer_starten).active) wizard_starten_clicked();
  // für die NEWS
  Gtk::OStream os(list_news);
  os << 
#include"NEWS.h" 
   <<'\n';

}

void midgard_CG::optionmenu_init()
{
  Vstand.resize(5);
  Vstand[1]="Unfrei";
  Vstand[2]="Volk";
  Vstand[3]="Mittelschicht";
  Vstand[4]="Adel";

  Vhand.resize(3);
  Vhand[0]="Rechtshänder";
  Vhand[1]="Linkshänder";
  Vhand[2]="Beidhändig";

  Vkido.resize(4);
  Vkido[0]="TECHNIK";
  Vkido[1]="Sanfte Techniken";
  Vkido[2]="Harte Techniken";
  Vkido[3]="Gemischte Techniken";
}

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

 std::vector<std::string> beruf;
 beruf.push_back("Beruf"); 
 beruf.push_back("Gelernt"); 
 beruf.push_back("Fertigkeit"); 
 beruf.push_back("Kategorie"); 
 Beruf_tree->setTitles(beruf);          
}

void midgard_CG::on_radiobutton_frau_toggled()
{ on_radiobutton_mann_toggled(); }
void midgard_CG::on_radiobutton_mann_toggled()
{
  if(wizard)
   { 
     notebook_main->set_sensitive(false) ;
     wizard->next_step();
   }
  std::string oldG=Werte.Geschlecht();
  if (radiobutton_mann->get_active()) Werte.setGeschlecht("m");
  else Werte.setGeschlecht("w");
  if(oldG!=Werte.Geschlecht() && Werte.Groesse() && Werte.Spezies()->Name()=="Mensch")
   {
     if( Werte.Geschlecht()=="w") Werte.setGroesse(Werte.Groesse()-10);
     if( Werte.Geschlecht()=="m") Werte.setGroesse(Werte.Groesse()+10);
   }
  if(oldG!=Werte.Geschlecht() && Werte.Gewicht() && Werte.Spezies()->Name()=="Mensch")
   {
     if( Werte.Geschlecht()=="w") Werte.setGewicht(Werte.Gewicht()-4);
     if( Werte.Geschlecht()=="m") Werte.setGewicht(Werte.Gewicht()+4);
   }

  fill_typauswahl();
  fill_typauswahl_2();
  zeige_werte();
}

void midgard_CG::show_gtk()
{
  if (Typ[1]->Short()=="") typauswahl_2->hide();
  else
   { typauswahl_2->show(); 
   }
 fertig_typ->set_text(Typ[0]->Name(Werte.Geschlecht()));     // Abenteurerklasse im Lernfenster
 if (Typ[1]->Name(Werte.Geschlecht())!="") 
   fertig_typ->set_text(Typ[0]->Name(Werte.Geschlecht())+"/"+Typ[1]->Name(Werte.Geschlecht()));
 steigern_typ->set_text(Typ[0]->Name(Werte.Geschlecht()));     // Abenteurerklasse im Lernfenster
 if (Typ[1]->Name(Werte.Geschlecht())!="") 
   steigern_typ->set_text(Typ[0]->Name(Werte.Geschlecht())+"/"+Typ[1]->Name(Werte.Geschlecht()));
 
 zeige_werte();
 show_gelerntes();
 EP_uebernehmen();
 Geld_uebernehmen();
 steigern_gtk();

 // Spezialwaffe anzeigen?
 if (Typ[0]->Spezialwaffe() || Typ[1]->Spezialwaffe()) 
    togglebutton_spezialwaffe->show(); 
 else 
   { togglebutton_spezialwaffe->set_active(false);
     togglebutton_spezialwaffe->hide(); }


 // Magie anzeigen?
 if (Typ[0]->is_mage() || Typ[1]->is_mage() || magie_bool) 
   { if (Typ[0]->Spezialgebiet() || Typ[1]->Spezialgebiet()) show_magier_spezialgebiet(true);
     else show_magier_spezialgebiet(false);
     button_zauber->set_sensitive(true);
     table_magier_steigern->show();
   }
 else 
   { 
     show_magier_spezialgebiet(false);
     button_zauber->set_sensitive(false);
     table_magier_steigern->hide();
   }
 // KiDo anzeigen?
 if (kido_bool) 
   { optionmenu_KiDo_Stile->show();
     frame_KiDo_lernschema->show();     
     table_kido_steigern->show();
   }
 else 
   { optionmenu_KiDo_Stile->hide();
     frame_KiDo_lernschema->hide();     
     table_kido_steigern->hide();
   }
 // KiDo Stil setzen
 int kido_stil_nr=0;
 if (Werte.Spezialisierung()==Vkido[2]) kido_stil_nr = 1;
 if (Werte.Spezialisierung()==Vkido[1]) kido_stil_nr = 2;
 if (Werte.Spezialisierung()==Vkido[3]) kido_stil_nr = 3;
 if (kido_stil_nr!=0)
  {   
    optionmenu_KiDo_Stile->set_history(kido_stil_nr);
  }
}


void midgard_CG::on_button_hilfe_clicked()
{
  manage(new Window_hilfe()); 
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



/*****************************************************************/

void midgard_CG::clear_listen()
{
   list_Fertigkeit.clear();
   list_FertigkeitZusaetze.clear();
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
   tree_gelerntes->clear();
   tree_lernschema->clear();

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
  
   togglebutton_edit_werte->set_active(false);
   on_togglebutton_edit_werte_toggled();
}

void midgard_CG::on_neuer_charakter_clicked()
{
   modify_bool=false;
   label_lernschma_titel->set_text("");

   button_grundwerte->set_sensitive(true);
   button_abg_werte->set_sensitive(false);
   frame_steigern->set_sensitive(false); // das wirkt nicht ?
   frame_lernschema->set_sensitive(false);
   togglebutton_lernpunkte_edit->set_active(false);

   button_lernpunkte->set_sensitive(false);
   togglebutton_lernpunkte_edit->set_sensitive(false);
   button_lernschema_geld->set_sensitive(false);
   button_lernschema_waffen->set_sensitive(false);
   button_ruestung->set_sensitive(false);

   edit_lernpunkte(false);
   frame_lernschema_zusatz->hide();

   button_fachkenntnisse->set_sensitive(false);
   button_allgemeinwissen->set_sensitive(false);
   button_untyp_fertigkeiten->set_sensitive(false);
   button_waffen->set_sensitive(false);
   button_zauber->set_sensitive(false);
   table_berufswahl->set_sensitive(false);
   scrolledwindow_beruf->hide();
   scrolledwindow_ange_fert->hide();
   label_berufskategorie->hide();
   label_berufsstern_erklaerung->hide();
   togglebutton_spezialwaffe->set_active(false);
   togglebutton_spezialwaffe->hide();
      
   scrolledwindow_landauswahl->hide();
   table_werte_wuerfeln->hide();
   table_bw_wurf->hide();
   spinbutton_pp_eingeben->hide();
   vbox_praxispunkte->hide();
   table_gruppe->hide();
   table_artikel->hide();
   togglebutton_gruppe_neu->hide(); // nicht implementiert


   if(Werte.Stadt_Land()=="Land")  radiobutton_land->set_active(true);
   if(Werte.Stadt_Land()=="Stadt")  radiobutton_stadt->set_active(true);
  

   vbox_berufsname->hide();
   button_kido_auswahl->set_sensitive(false);       
   button_angeborene_fert->set_sensitive(false);

   Werte.clear();

   lernpunkte.clear();
   Typ.clear();
   Typ.resize(2);
   zeige_lernpunkte();
   zeige_werte();
   for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
      (*i)->setActive(false);
   menu_init();
   steigern_mit_EP_bool=true;
   checkbutton_EP_Geld->set_active(steigern_mit_EP_bool);
   

   Database.GradAnstieg.set_Grad_Basiswerte(1);
   label_EP->set_text("50%");
   label_Gold->set_text("50%");

  kido_bool=false;
  magie_bool=false;
  fill_typauswahl();
  fill_spezies();
  spezieswahl_button();
  typauswahl_button(); // ruft clear_listen() und clear_gtk() auf
  show_gtk();
}

void midgard_CG::on_schliessen_CG_clicked()
{
  if(modify_bool)
   {
     save_options();
     xml_export_auswahl();
     return;
   }
  system("rm midgard_tmp_*");
  Gtk::Main::instance()->quit();
}

gint midgard_CG::on_midgard_CG_delete_event(GdkEventAny* event)
{
  on_schliessen_CG_clicked();
  return true;
}

