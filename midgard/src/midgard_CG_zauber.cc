// $Id: midgard_CG_zauber.cc,v 1.35 2001/11/08 10:15:43 thoma Exp $
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
#include "Zauber_auswahl.hh"
#include <Gtk_OStream.h>

void midgard_CG::on_zauber_wahl_clicked()
{
  zauber_clist->clear();
  if (Werte.Spezialgebiet()->Spezial2()=="" && Typ[0]->Short()=="eBe")
   {
      std::string strinfo="Erst Prim�r- und Sekund�relement w�hlen\n";
      manage(new WindowInfo(strinfo));
      return;
   }
  manage(new Zauber_auswahl(this,Werte,Database,vec_Beruf,Typ,lernpunkte.Zauber()));
}

void midgard_CG::show_zauber()
{
   zauber_clist->clear();
   Gtk::OStream os(zauber_clist);
   for(std::list<cH_MidgardBasicElement>::const_iterator i=list_Zauber.begin();i!=list_Zauber.end();++i)
      {
         cH_Zauber z(*i);
         os << z->Name()<<"\t"<<z->Erfolgswert_Z(Typ,Werte,Database.ausnahmen)<<"\n";
      }
   for (unsigned int i=0;i<zauber_clist->columns().size();++i)
      zauber_clist->set_column_auto_resize(i,true);
   zauber_clist->set_reorderable(true);
}


void midgard_CG::angeborene_zauber()
{
 if (Typ[0]->Short()=="eBe" || Typ[1]->Short()=="eBe" || Typ[0]->Short()=="dBe" || Typ[1]->Short()=="dBe" ) 
    list_Zauber.push_back(new Zauber("Lehrersuche"));
 if (Werte.Spezies()->Name()=="Elf") 
    list_Zauber.push_back(new Zauber("Erkennen der Aura"));
}

void midgard_CG::magier_spezialgebiet(const std::string& whattodo)
{
 if (whattodo=="show")
   { spezialgebiet_button_fill();
     option_magier_spezialgebiet->show();
   }
 if (whattodo=="hide") option_magier_spezialgebiet->hide();
}

void midgard_CG::spezialgebiet_button_fill()
{
  Gtk::Menu *_m(manage(new Gtk::Menu()));
  Gtk::MenuItem *_mi;
//  while (true)
  for(std::vector<cH_Spezialgebiet>::iterator i=Database.Spezialgebiet.begin();i!=Database.Spezialgebiet.end();++i)
   {
//      exec sql fetch ein into :db_nr, :db_spezialgebiet, :db_spezial, :db_spezi
//      SQLerror::test(__FILELINE__,100);
//      if (sqlca.sqlcode) break;   
//      vec_spezialgebiet.push_back(db_spezialgebiet);
      if((*i)->Typ() != Typ[0]->Short() || (*i)->Typ() != Typ[1]->Short() ) continue;
      _mi = manage(new Gtk::MenuItem((*i)->Name()));
      _m->append(*_mi);
      _mi->show();
//      _mi->set_user_data((gpointer)db_nr);
      _mi->set_user_data((gpointer)&*i);
//      _mi->set_user_data((gpointer)&vec_spezialgebiet[db_nr]);
    }
  option_magier_spezialgebiet->set_menu(*_m);
  option_magier_spezialgebiet->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::spezialgebiet_button));
}

void midgard_CG::spezialgebiet_button()
{
// int i = int(option_magier_spezialgebiet->get_menu()->get_active()->get_user_da
// if (i==0) return ;
 cH_Spezialgebiet *ptr = static_cast<cH_Spezialgebiet*>(optionmenu_spezies->get_menu()->get_active()->get_user_data());

// string s = *static_cast<const std::string*>(option_magier_spezialgebiet->get
// if (s=="Spezialgebiet" || s == "Prim�r- und Sekund�relement") return ;
// Werte.set_Spezialisierung(s);
// Werte.set_Spezialisierung(vec_spezialgebiet[i]);
 Werte.set_Spezialgebiet(*ptr);

// get_spezial_from_spezialgebiet();
//cout << Werte.Spezialisierung()<<"\t"<<Werte.Spezial()<<"\t"<<Werte.Spezial2(
} 

              