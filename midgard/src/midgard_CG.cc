// $Id: midgard_CG.cc,v 1.227 2002/05/20 20:44:09 thoma Exp $
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
//#include "Window_hilfe.hh"
#include "Window_Geld_eingeben.hh"
#include "Window_ruestung.hh"
#include "Window_Waffenbesitz.hh"
#include <gtk--/notebook.h>
//#include <gtk--/main.h>
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




