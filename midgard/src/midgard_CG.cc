// $Id: midgard_CG.cc,v 1.141 2002/02/06 14:25:22 thoma Exp $
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
#include "Window_charakter_beschreibung.hh"
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

//midgard_CG::midgard_CG(int argc,char **argv)
midgard_CG::midgard_CG(Datenbank& _Database, const string &datei)
: menu(0),menu_gradanstieg(0),haus_menuitem(0),Database(_Database)
{
  srand(time(0));
  optionmenu_init();  
  Optionen_init();
  Hausregeln_init();

  on_neuer_charakter_clicked();
  set_tree_titles();

  if (!datei.empty()) xml_import(datei);
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
}

void midgard_CG::on_radiobutton_frau_toggled()
{ on_radiobutton_mann_toggled(); }
void midgard_CG::on_radiobutton_mann_toggled()
{
  if (radiobutton_mann->get_active()) Werte.setGeschlecht("m");
  else Werte.setGeschlecht("w");
  fill_typauswahl();
  fill_typauswahl_2();
}

void midgard_CG::show_gtk()
{
//  typauswahl->set_history(Typ[0]->Nr());
  if (Typ[1]->Short()=="") typauswahl_2->hide();
  else
   { typauswahl_2->show(); 
//     typauswahl_2->set_history(Typ[1]->Nr());
   }
//cout << "Geschlecht = " <<Werte.Geschlecht()<<'\n';
 fertig_typ->set_text(Typ[0]->Name(Werte.Geschlecht()));     // Abenteurerklasse im Lernfenster
 if (Typ[1]->Name(Werte.Geschlecht())!="") 
   fertig_typ->set_text(Typ[0]->Name(Werte.Geschlecht())+"/"+Typ[1]->Name(Werte.Geschlecht()));
 steigern_typ->set_text(Typ[0]->Name(Werte.Geschlecht()));     // Abenteurerklasse im Lernfenster
 if (Typ[1]->Name(Werte.Geschlecht())!="") 
   steigern_typ->set_text(Typ[0]->Name(Werte.Geschlecht())+"/"+Typ[1]->Name(Werte.Geschlecht()));
 
 zeige_werte(Werte);
 show_gelerntes();
 EP_uebernehmen();
 Geld_uebernehmen();
 steigern_gtk();

 // Spezialwaffe anzeigen?
 if (Typ[0]->Zaubern()=="n" || Typ[0]->Short() == "Ord") label_spezialwaffe->set_text("Spezialwaffe durch \nSelektieren auswählen");
 else label_spezialwaffe->set_text("");

 // Magie anzeigen?
 if (Typ[0]->Zaubern()=="j" || Typ[0]->Zaubern() == "z" || magie_bool) 
   { if (Typ[0]->Short()=="Ma" || Typ[0]->Short() == "eBe") magier_spezialgebiet("show");
     else 
     button_zauber->set_sensitive(true);
     table_magier_steigern->show();
   }
 else 
   { 
     magier_spezialgebiet("hide");
     button_zauber->set_sensitive(false);
     table_magier_steigern->hide();
   }
 // KiDo anzeigen?
 if (kido_bool) 
   { optionmenu_KiDo_Stile->show();
     table_kido_lernschema->show();     
     table_kido_steigern->show();
   }
 else 
   { optionmenu_KiDo_Stile->hide();
     table_kido_lernschema->hide();     
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
//    checkbutton_KanThaiPan->set_active(true);
//    KanThaiPanbool=true;
  }
}


void midgard_CG::on_charakter_beschreibung_clicked()
{   
  manage(new Window_charakter_beschreibung(this,Werte.Beschreibung())); 
}   
void midgard_CG::charakter_beschreibung_uebernehmen(const std::string& b,bool drucken)
{
  Werte.setBeschreibung(b);
#ifndef USE_XML  
  on_speichern_clicked();
#else
   steigern_aktivieren();
#endif
  if(drucken) latex_beschreibung_drucken();
}

void midgard_CG::on_button_hilfe_clicked()
{
  manage(new Window_hilfe()); 
}
void midgard_CG::on_button_info_clicked()
{
  Midgard_Info *MI = manage(new Midgard_Info());
  MI->set_Regionen(Database.Regionen);  
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
  manage (new Window_Waffenbesitz(this,Database,list_Waffen,list_Waffen_besitz,Werte,Typ));
}



/*****************************************************************/

void midgard_CG::clear_listen()
{
   list_Fertigkeit.clear();
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
   tree_gelerntes->clear();
   tree_lernschema->clear();
   label_lernschma_titel->set_text("");

   button_abg_werte->set_sensitive(false);
   button_beschreibung->set_sensitive(false);
   frame_steigern->set_sensitive(false); // das wirkt nicht ?
   frame_lernschema->set_sensitive(false);

   button_lernpunkte->set_sensitive(false);
   togglebutton_lernpunkte_edit->set_sensitive(false);
   button_geld_waffen->set_sensitive(false);
   button_ruestung->set_sensitive(false);

   edit_lernpunkte(false);

   button_fachkenntnisse->set_sensitive(false);
   button_allgemeinwissen->set_sensitive(false);
   button_untyp_fertigkeiten->set_sensitive(false);
   button_waffen->set_sensitive(false);
   button_zauber->set_sensitive(false);
   table_berufswahl->set_sensitive(false);
      
   scrolledwindow_landauswahl->hide();
   table_werte_wuerfeln->hide();
   table_bw_wurf->hide();
   spinbutton_pp_eingeben->hide();
   vbox_praxispunkte->hide();
   table_gruppe->hide();
   table_artikel->hide();
   togglebutton_gruppe_neu->hide(); // nicht implementiert

   table_berufwahl->hide();
   button_kido_auswahl->set_sensitive(false);       

   Werte.clear();
   lernpunkte.clear();
   Typ.clear();
   Typ.resize(2);
   zeige_lernpunkte();
   zeige_werte(Werte);
//   OptionBool.reset(); 
   for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
      (*i)->setActive(false);
   menu_init();
//   menu_gradanstieg_init();
//cout << "HausregelCheck(EPsteigern).active "<<HausregelCheck(EPsteigern).active<<'\n';
//   checkbutton_EP_Geld->set_active(HausregelCheck(EPsteigern).active);
   checkbutton_EP_Geld->set_active(true);
   

   Database.GradAnstieg.set_Grad_Basiswerte(1);
//   vscale_EP_Gold->set_digits(Database.GradAnstieg.get_Steigern_EP_Prozent());
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
  system("rm midgard_tmp_*");
  Gtk::Main::instance()->quit();
}

