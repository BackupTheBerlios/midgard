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
#include <Gtk_OStream.h>
#include <Aux/itos.h>

void table_steigern::on_button_ruestung_1_toggled()
{
 if(!button_ruestung_1->get_active()) return;
// hauptfenster->getWerte().clearRuestung();
 fill_ruestung();
 show_label();
}

void table_steigern::on_button_ruestung_2_toggled()
{
 if(!button_ruestung_2->get_active()) return;
 fill_ruestung();
}
                

void table_steigern::on_clist_ruestung_select_row(gint row, gint column, GdkEvent *event)
{   
  cH_Ruestung R=static_cast<Ruestung*>(clist_ruestung->selection().begin()->get_data());
//  Werte.set_Ruestung(clist_ruestung->get_text(row,1));
  if(R->Min_Staerke()<=hauptfenster->getCWerte().St())
   {
     if(button_ruestung_1->get_active())
      {
        hauptfenster->getWerte().setRuestung1(R);
        button_ruestung_1->set_active(false);
      }
     else if(button_ruestung_2->get_active())
      {
        hauptfenster->getWerte().setRuestung2(R);
        button_ruestung_2->set_active(false);
      }
     show_label();
     clist_ruestung->set_sensitive(false);
   }
  else 
   hauptfenster->set_status("Nicht stark genug.");
}

void table_steigern::fill_ruestung() 
{
// show_label();
 Gtk::OStream os(clist_ruestung);
 for(std::vector<cH_Ruestung>::const_iterator i=hauptfenster->getCDatabase().Ruestung.begin();i!=hauptfenster->getCDatabase().Ruestung.end();++i)
   { cH_Ruestung r(*i);
     if (hauptfenster->region_check(r->Region()))
        os << r->Long() <<"\t"<<r->Name()<<"\t"<<r->LP_Verlust()<<"\t"
            <<r->Min_Staerke()<<"\t"<<r->RW_Verlust()<<"\t"<<r->B_Verlust()<<"\n";
     os.flush(r->ref());
   } 
 for (unsigned int i=0;i<clist_ruestung->columns().size();++i)
   clist_ruestung->set_column_auto_resize(i,true);  
 clist_ruestung->set_sensitive(true);
}

void table_steigern::show_label()
{
// std::string sru=itos(count+1)+"te Rüstung auswählen. Bisherige Rüstungen: ("+ 
//   Werte.Ruestung()->Long() +"/"+Werte.Ruestung(1)->Long()+")";
// label_ruestung->set_text(sru.c_str());
 label_ruestung_1->set_text(hauptfenster->getCWerte().Ruestung()->Long());
 label_ruestung_2->set_text(hauptfenster->getCWerte().Ruestung(1)->Long());
}

