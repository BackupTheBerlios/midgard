// $Id: table_lernschema_zauber.cc,v 1.21 2003/12/10 07:30:25 christof Exp $
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
#include <libmagus/LernListen.hh>
#include <libmagus/Datenbank.hh>

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
 std::vector<std::string> L=LernListen::getSpezialgebiet(hauptfenster->getAben());
 combo_magier_spezialgebiet->set_popdown_strings(L);
}

void table_lernschema::on_combo_magier_spezialgebiet_activate()
{
 button_zauber->grab_focus();
}

bool table_lernschema::on_combo_magier_spezialgebiet_focus_out_event(GdkEventFocus *ev)
{
  for(std::vector<cH_Spezialgebiet>::const_iterator i=Datenbank.Spezialgebiet.begin();i!=Datenbank.Spezialgebiet.end();++i)
   {
     if((*i)->Name()==combo_magier_spezialgebiet->get_entry()->get_text())
      {
        hauptfenster->getAben().setSpezialgebiet(*i);
        if(hauptfenster->getAben().Spezialisierung().empty())
            hauptfenster->getAben().setSpezialisierung((*i)->Name());
// if (s=="Spezialgebiet" || s == "Primär- und Sekundärelement") return ;
        hauptfenster->getChar().getWizard().done(Wizard::SPEZIALGEBIET,hauptfenster->getAben());
        break;
      }
   }
  return false;
}

void table_lernschema::on_combo_magier_changed()
{
}
