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
//#include <Aux/Transaction.h>
//#include <Aux/SQLerror.h>
#include "Window_doppelcharaktere.hh"
#include <Gtk_OStream.h>
//exec sql include sqlca;

void midgard_CG::fill_typauswahl()
{
//  vec_Typen.clear();
  fill_typauswahl_fill(1);
  typauswahl->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::typauswahl_button));
}

void midgard_CG::fill_typauswahl_2()
{
//  vec_Typen_2.clear();
  fill_typauswahl_fill(2);
  typauswahl_2->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::typauswahl_2_button));
}

void midgard_CG::fill_typauswahl_fill(int typ_1_2)
{
  Gtk::OStream t_((typ_1_2==1) ? typauswahl : typauswahl_2 ); 

//cout << "Typen = "<<Database.Typen.size()<<'\n';
   for(std::vector<cH_Typen>::iterator i=Database.Typen.begin();i!=Database.Typen.end();++i)
    {
     if (Werte.Spezies()->Name()=="Mensch" || Werte.Spezies()->Typ_erlaubt((*i)->Short()))
       if (region_check((*i)->Region()))
         {
           t_ << (*i)->Name(Werte.Geschlecht());
           t_.flush((gpointer)&*i);
         }
   }
//cout << "FERTIG\n";
}


void midgard_CG::typauswahl_button()
{
 cH_Typen *ptr = static_cast<cH_Typen*>(typauswahl->get_menu()->get_active()->get_user_data());

 Typ[0]=*ptr;

// int ityp = int(typauswahl->get_menu()->get_active()->get_user_data());
// Typ[0] = vec_Typen[ityp];
//cout << "Typ1"<<"\t"<<ityp<<"\t"<<Typ.Name()<<"\n";
 show_gtk();
 Database.ausnahmen.set_Typ(Typ);
 if (Typ[0]->Short()=="dBe" || Typ[0]->Short()=="eBe") angeborene_zauber();
}

void midgard_CG::typauswahl_2_button()
{
 cH_Typen *ptr = static_cast<cH_Typen*>(typauswahl_2->get_menu()->get_active()->get_user_data());
 Typ[1]=*ptr;

// int ityp = int(typauswahl_2->get_menu()->get_active()->get_user_data());
// Typ[1] = vec_Typen_2[ityp];
//cout << "Typ1"<<"\t"<<ityp<<"\t"<<Typ.Name()<<"\n";
 Database.ausnahmen.set_Typ(Typ);
 show_gtk();
 if (Typ[1]->Short()=="dBe" || Typ[1]->Short()=="eBe") angeborene_zauber();
}


void midgard_CG::fill_spezies()
{
//  spezies_vector.clear();
//  exec sql begin declare section;
//   char db_spezies[50];
//   int db_nr;
//  exec sql end declare section;
//  Transaction tr;
//  exec sql declare ein_r cursor for 
//      select nr,spezies from spezies order by nr ;
//  exec sql open ein_r;
//  SQLerror::test(__FILELINE__);
  Gtk::Menu *_m(manage(new Gtk::Menu()));
  Gtk::MenuItem *_mi;
//  while (true)
  for(vector<cH_Spezies>::iterator i=Database.Spezies.begin();i!=Database.Spezies.end();++i)
   {
//      exec sql fetch ein_r into :db_nr, :db_spezies;
//      SQLerror::test(__FILELINE__,100);
//      if (sqlca.sqlcode) break;   
//      spezies_vector.push_back(db_spezies);
//      _mi = manage(new Gtk::MenuItem(db_spezies));
      _mi = manage(new Gtk::MenuItem((*i)->Name()));
      _m->append(*_mi);
      _mi->show();
//      _mi->set_user_data((gpointer)db_nr);
//      _mi->set_user_data((gpointer)(*(*i)->Name()));
//kann ich nicht wiederhohlen :-(   
      _mi->set_user_data((gpointer)&*i);
    }
  optionmenu_spezies->set_menu(*_m);
  optionmenu_spezies->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::spezieswahl_button));
}

void midgard_CG::spezieswahl_button()
{
// int ityp = int(optionmenu_spezies->get_menu()->get_active()->get_user_data());
   cH_Spezies *ptr = static_cast<cH_Spezies*>(optionmenu_spezies->get_menu()->get_active()->get_user_data());
   Werte.set_Spezies(*ptr);

//s.o.  Werte.set_Spezies(cH_Spezies(optionmenu_spezies->get_menu()->get_active()->get_user_data()));
///*   Werte.set_Spezies*/(std::string(optionmenu_spezies->get_menu()->get_active()->get_user_data()));
// Werte.set_Spezies(spezies_vector[ityp]);

//cout << "Spezies"<<"\t"<<ityp<<"\t"<<Werte.Spezies()<<"\n";


 fill_typauswahl();
 typauswahl_button();

 if (Werte.Spezies()->Name()=="Elf")
   { manage (new Window_doppelcharaktere(this));
     angeborene_zauber();
   }
}

void midgard_CG::doppelcharaktere()
{
   fill_typauswahl_2();
   typauswahl_2->show();
   typauswahl_2_button();
   magie_bool=true;
}
