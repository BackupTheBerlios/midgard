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
#include "Window_doppelcharaktere.hh"
#include <Gtk_OStream.h>

void midgard_CG::fill_typauswahl()
{
  fill_typauswahl_fill(1);
  typauswahl->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::typauswahl_button));
}

void midgard_CG::fill_typauswahl_2()
{
  fill_typauswahl_fill(2);
  typauswahl_2->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::typauswahl_2_button));
}

void midgard_CG::fill_typauswahl_fill(int typ_1_2)
{
  Gtk::OStream t_((typ_1_2==1) ? typauswahl : typauswahl_2 ); 
  int count=0;
  for(std::vector<cH_Typen>::iterator i=Database.Typen.begin();i!=Database.Typen.end();++i)
    {
     if (Werte.Spezies()->Name()=="Mensch" || Werte.Spezies()->Typ_erlaubt((*i)->Short()))
       if (region_check((*i)->Region()))
         {
           t_ << (*i)->Name(Werte.Geschlecht());
           t_.flush((gpointer)&*i);
           (*i)->set_opionmenu_nr(count++);
         }
   }
}


void midgard_CG::typauswahl_button()
{
 cH_Typen *ptr = static_cast<cH_Typen*>(typauswahl->get_menu()->get_active()->get_user_data());
 Typ[0]=*ptr;
 clear_listen();
 clear_gtk();
 show_gtk();
 Database.ausnahmen.set_Typ(Typ);
 if (Typ[0]->Short()=="dBe" || Typ[0]->Short()=="eBe") angeborene_zauber();
}
void midgard_CG::typauswahl_2_button()
{
 cH_Typen *ptr = static_cast<cH_Typen*>(typauswahl_2->get_menu()->get_active()->get_user_data());
 Typ[1]=*ptr;
 show_gtk();
 Database.ausnahmen.set_Typ(Typ);
 if (Typ[1]->Short()=="dBe" || Typ[1]->Short()=="eBe") angeborene_zauber();
}


void midgard_CG::fill_spezies()
{
  Gtk::Menu *_m(manage(new Gtk::Menu()));
  Gtk::MenuItem *_mi;
  for(vector<cH_Spezies>::iterator i=Database.Spezies.begin();i!=Database.Spezies.end();++i)
   {
      _mi = manage(new Gtk::MenuItem((*i)->Name()));
      _m->append(*_mi);
      _mi->show();
      _mi->set_user_data((gpointer)&*i);
    }
  optionmenu_spezies->set_menu(*_m);
  optionmenu_spezies->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::spezieswahl_button));
}

void midgard_CG::spezieswahl_button()
{
 cH_Spezies *ptr = static_cast<cH_Spezies*>(optionmenu_spezies->get_menu()->get_active()->get_user_data());
 Werte.set_Spezies(*ptr);

 fill_typauswahl();
 typauswahl_button();

 if (Werte.Spezies()->Name()=="Elf")
   { manage (new Window_doppelcharaktere(this));
     angeborene_zauber();
   }
 else
   {
     typauswahl_2->hide();
     magie_bool=false;
     Typ[1]=cH_Typen();
   }
}

void midgard_CG::doppelcharaktere()
{
   fill_typauswahl_2();
   typauswahl_2->show();
   typauswahl_2_button();
   magie_bool=true;
}
