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
#include <SelectMatching.h>

void midgard_CG::fill_typauswahl()
{
  fill_typauswahl_fill(1);
  typauswahl->get_menu()->deactivate.connect(SigC::slot(this, &midgard_CG::typauswahl_button));
  Gtk::Menu_Helpers::SelectMatching(*typauswahl,Typ[0]);
}

void midgard_CG::fill_typauswahl_2()
{
  fill_typauswahl_fill(2);
  typauswahl_2->get_menu()->deactivate.connect(SigC::slot(this, &midgard_CG::typauswahl_2_button));
  Gtk::Menu_Helpers::SelectMatching(*typauswahl_2,Typ[1]);
}

void midgard_CG::fill_typauswahl_fill(int typ_1_2)
{
  Gtk::OStream t_((typ_1_2==1) ? typauswahl : typauswahl_2 ); 
  for(std::vector<cH_Typen>::iterator i=Database.Typen.begin();i!=Database.Typen.end();++i)
    {
     if (Werte.Spezies()->Name()=="Mensch" || Werte.Spezies()->Typ_erlaubt((*i)->Short()))
       if (region_check((*i)->Region()))
         {
           t_ << (*i)->Name(Werte.Geschlecht());
           t_.flush((*i)->ref(),&HandleContent::unref);
         }
   }
}


void midgard_CG::typauswahl_button()
{
 if(wizard) {notebook_main->set_sensitive(false) ;
             wizard->next_step();
             /*typauswahl->set_sensitive(false) ;*/  }
 cH_Typen ptr = static_cast<Typen*>(typauswahl->get_menu()->get_active()->get_user_data());
 Typ[0]=ptr;
 clear_listen();
 clear_gtk();
 show_gtk();
// if (Typ[0]->Short()=="dBe" || Typ[0]->Short()=="eBe") angeborene_zauber();

 if(Werte.Spezies()->Land()) 
   {
     radiobutton_land->set_active(true);
     radiobutton_stadt->set_sensitive(false);
     radiobutton_land->set_sensitive(true);
   }
 else if(!Typ[0]->Stadt())
   {
     radiobutton_land->set_active(true);
     radiobutton_land->set_sensitive(true);
     radiobutton_stadt->set_sensitive(false);
   }
 else if(!Typ[0]->Land())
   {
     radiobutton_stadt->set_active(true);
     radiobutton_stadt->set_sensitive(true);
     radiobutton_land->set_sensitive(false);
   }
 else
   {
     radiobutton_stadt->set_sensitive(true);
     radiobutton_land->set_sensitive(true);
   }
}
void midgard_CG::typauswahl_2_button()
{
 cH_Typen ptr = static_cast<Typen*>(typauswahl_2->get_menu()->get_active()->get_user_data());
 Typ[1]=ptr;
 show_gtk();
// if (Typ[1]->Short()=="dBe" || Typ[1]->Short()=="eBe") angeborene_zauber();
}


void midgard_CG::fill_spezies()
{
  { Gtk::OStream t_(optionmenu_spezies);
    for(vector<cH_Spezies>::iterator i=Database.Spezies.begin();i!=Database.Spezies.end();++i)
     {
       t_ << (*i)->Name();
       t_.flush((*i)->ref(),&HandleContent::unref);
     }
  }
  optionmenu_spezies->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::spezieswahl_button));
  Gtk::Menu_Helpers::SelectMatching(*optionmenu_spezies,Werte.Spezies());
}

void midgard_CG::spezieswahl_button()
{
 Werte.clear();
 if(wizard) { 
               notebook_main->set_sensitive(false) ;
               wizard->next_step();
//               optionmenu_spezies->set_sensitive(false) ; 
            }
 cH_Spezies ptr = static_cast<Spezies*>(optionmenu_spezies->get_menu()->get_active()->get_user_data());
 Werte.setSpezies(ptr);

 fill_typauswahl();
 typauswahl_button();

 if (Werte.Spezies()->Name()=="Elf")
   manage (new Window_doppelcharaktere(this));

 typauswahl_2->hide();
 magie_bool=false;
 Typ[1]=cH_Typen();
 
}

void midgard_CG::on_radiobutton_stadt_land_toggled()
{
  if(wizard) { notebook_main->set_sensitive(false) ; wizard->next_step() ;}

  if(radiobutton_stadt->get_active()) Werte.setStadt_Land("Stadt");   
  else                                Werte.setStadt_Land("Land");   
}


void midgard_CG::doppelcharaktere()
{
   fill_typauswahl_2();
   typauswahl_2->show();
   typauswahl_2_button();
   magie_bool=true;
}
