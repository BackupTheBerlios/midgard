// $Id: midgard_CG.cc,v 1.230 2002/05/27 20:36:46 thoma Exp $
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
//#include "Window_Geld_eingeben.hh"
//#include "Window_ruestung.hh"
//#include "Window_Waffenbesitz.hh"
#include <gtk--/notebook.h>
//#include <gtk--/main.h>
#include "Midgard_Info.hh"
#include "Fertigkeiten.hh"
#include <unistd.h>
#ifdef __MINGW32__
#include <time.h>
#endif

midgard_CG::midgard_CG(const string &datei)
: InfoFenster(0), MOptionen(0),wizard(0), ansicht_menu(0),region_menu(0),menu(0),
  Database(Midgard_Info)
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
//  Typ.resize(2);
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
//   if (menu) delete menu;
//   if (table_steigern->menu_gradanstieg) table_steigern->delete menu_gradanstieg;
//   InfoFenster->destroy(); 
   if(wizard) delete wizard;
}



#include <Aux/itos.h>
void midgard_CG::WaffenBesitz_uebernehmen(const std::list<cH_MidgardBasicElement>& mbe)
{
  if(mbe.begin()==mbe.end()) return;
  if((*mbe.begin())->What()==MidgardBasicElement::WAFFEBESITZ)
      Char.List_Waffen_besitz()=mbe;
  else assert(0);
  undosave(itos(mbe.size())+" "+(*mbe.begin())->What_str()+"n übernommen");
  if(notebook_main->get_current_page_num() == PAGE_LERNEN)
     table_lernschema->show_gelerntes();
}




