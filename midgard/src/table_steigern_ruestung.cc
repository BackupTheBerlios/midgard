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
#include "table_steigern.hh"
#include <Misc/itos.h>
#include <LernListen.hh>
#include <libmagus/Ausgabe.hh>

void table_steigern::on_button_ruestung_1_toggled()
{
 if(!button_ruestung_1->get_active()) 
   { RuestungStore->clear();
     clist_ruestung->set_sensitive(false);
     return;
   }
 button_ruestung_2->set_active(false);
 fill_ruestung();
 show_label();
}

void table_steigern::on_button_ruestung_2_toggled()
{
 if(!button_ruestung_2->get_active())
   { RuestungStore->clear();
     clist_ruestung->set_sensitive(false);
     return;
   }
 button_ruestung_1->set_active(false);
 fill_ruestung();
}
                

void table_steigern::on_ruestung_selection_changed()
{ Gtk::TreeIter actual=clist_ruestung->get_selection()->get_selected();
  if (!actual || actual==RuestungStore->children().end()) return;
  
  cH_Ruestung R=(*actual)[ruestung_columns.ruestung];

  if(R->Min_Staerke()<=hauptfenster->getAben().St())
   {
     if(button_ruestung_1->get_active())
      {
        hauptfenster->getAben().setRuestung1(R->Name());
        button_ruestung_1->set_active(false);
      }
     else if(button_ruestung_2->get_active())
      {
        hauptfenster->getAben().setRuestung2(R->Name());
        button_ruestung_2->set_active(false);
      }
     show_label();
     clist_ruestung->set_sensitive(false);
   }
  else 
   Ausgabe(Ausgabe::Error,"Nicht stark genug.");
}

void table_steigern::fill_ruestung() 
{
// show_label();
 RuestungStore->clear();
 std::vector<cH_Ruestung> VR=LernListen::getRuestung(hauptfenster->getAben());
 for(std::vector<cH_Ruestung>::const_iterator i=VR.begin();i!=VR.end();++i)
   { cH_Ruestung r(*i);
     Gtk::TreeModel::iterator iter = RuestungStore->append();

     (*iter)[ruestung_columns.name]=r->Long();
     (*iter)[ruestung_columns.abkz]=r->Name();
     (*iter)[ruestung_columns.lp_verlust]=r->LP_Verlust();
     (*iter)[ruestung_columns.min_staerke]=r->Min_Staerke();
     (*iter)[ruestung_columns.rw_verlust]=r->RW_Verlust();
     bool dummy;
     (*iter)[ruestung_columns.b_verlust]=r->B_Verlust(0,hauptfenster->getAben(),dummy);
     (*iter)[ruestung_columns.ruestung]=r;
   } 
 clist_ruestung->set_sensitive(true);
}

void table_steigern::show_label()
{
// std::string sru=itos(count+1)+"te Rüstung auswählen. Bisherige Rüstungen: ("+ 
//   Werte.Ruestung()->Long() +"/"+Werte.Ruestung(1)->Long()+")";
// label_ruestung->set_text(sru.c_str());
  label_ruestung_1->set_text(hauptfenster->getAben().Ruestung()->Long());
  label_ruestung_2->set_text(hauptfenster->getAben().Ruestung(1)->Long());
}

table_steigern::RuestungColumns::RuestungColumns()
{  add(name); add(abkz); add(lp_verlust); 
   add(min_staerke); add(rw_verlust); add(b_verlust);
   add(ruestung);
}
