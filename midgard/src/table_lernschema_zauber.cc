// $Id: table_lernschema_zauber.cc,v 1.6 2002/09/23 06:34:08 thoma Exp $
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
#include "LernListen.hh"

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
 std::vector<std::string> L=LernListen(hauptfenster->getDatabase()).getSpezialgebiet(hauptfenster->getChar());
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

