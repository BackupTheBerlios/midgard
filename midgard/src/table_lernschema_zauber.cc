// $Id: table_lernschema_zauber.cc,v 1.4 2002/06/26 14:01:18 christof Exp $
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

#include "table_lernschema.hh"
#include <Gtk_OStream.h>
#include "Zauber.hh"
#include "midgard_CG.hh"

/*
void table_lernschema::angeborene_zauber()
{
 if (Typ[0]->Short()=="eBe" || Typ[1]->Short()=="eBe" || Typ[0]->Short()=="dBe" || Typ[1]->Short()=="dBe" ) 
    list_Zauber.push_back(&*cH_Zauber("Lehrersuche"));
 if (hauptfenster->getWerte().Spezies()->Name()=="Elf") 
    list_Zauber.push_back(&*cH_Zauber("Erkennen der Aura"));
}
*/

void table_lernschema::show_magier_spezialgebiet(bool show)
{
 if (show)
   { spezialgebiet_button_fill();
     combo_magier_spezialgebiet->show();
   }
 else combo_magier_spezialgebiet->hide();
}

void table_lernschema::spezialgebiet_button_fill()
{
 vector<std::string> L;
 {
//  Gtk::OStream t_(option_magier_spezialgebiet);
  for(std::vector<cH_Spezialgebiet>::const_iterator i=hauptfenster->getDatabase().Spezialgebiet.begin();i!=hauptfenster->getDatabase().Spezialgebiet.end();++i)
   {
    if((*i)->Typ() != hauptfenster->getChar().Typ1()->Short() && 
       (*i)->Typ() != hauptfenster->getChar().Typ2()->Short() ) continue;
//    t_ << (*i)->Name();
//    t_.flush((*i)->ref(),&HandleContent::unref);
    L.push_back((*i)->Name());
   }  
 }
// option_magier_spezialgebiet->get_menu()->deactivate.connect(SigC::slot(static_cast<class table_lernschema*>(this), &table_lernschema::spezialgebiet_button));
 combo_magier_spezialgebiet->set_popdown_strings(L);
}

void table_lernschema::on_combo_magier_spezialgebiet_activate()
{
 button_zauber->grab_focus();
}

gint table_lernschema::on_combo_magier_spezialgebiet_focus_out_event(GdkEventFocus *ev)
{
  for(std::vector<cH_Spezialgebiet>::const_iterator i=hauptfenster->getDatabase().Spezialgebiet.begin();i!=hauptfenster->getDatabase().Spezialgebiet.end();++i)
   {
     if((*i)->Name()==combo_magier_spezialgebiet->get_entry()->get_text())
      {
        hauptfenster->getWerte().setSpezialgebiet(*i);
// if (s=="Spezialgebiet" || s == "Primär- und Sekundärelement") return ;
        if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::SPEZIALGEBIET);
        break;
      }
   }
  return false;
}

/*
void table_lernschema::spezialgebiet_button()
{
 gpointer user_data=option_magier_spezialgebiet->get_menu()->get_active()->get_user_data();
 cH_Spezialgebiet ptr = static_cast<Spezialgebiet*>(user_data);
// if (s=="Spezialgebiet" || s == "Primär- und Sekundärelement") return ;
 hauptfenster->getWerte().setSpezialgebiet(ptr);
//cout << hauptfenster->getWerte().Spezialisierung()<<"\t"<<hauptfenster->getWerte().Spezial()<<"\t"<<hauptfenster->getWerte().Spezial2(
 if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::SPEZIALGEBIET);
} 
*/
              