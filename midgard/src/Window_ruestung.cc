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

#include "config.h"
#include "Window_ruestung.hh"
//#include <Aux/Transaction.h>
//#include <Aux/SQLerror.h>
//exec sql include sqlca;
#include <Gtk_OStream.h>
#include "midgard_CG.hh"
#include "WindowInfo.hh"

void Window_ruestung::on_clist_ruestung_select_row(gint row, gint column, GdkEvent *event)
{   
  cH_Ruestung R=static_cast<Ruestung*>(clist_ruestung->selection().begin()->get_data());
//  Werte.set_Ruestung(clist_ruestung->get_text(row,1));
  if(R->Min_Staerke()<=Werte.St())
   {
     Werte.setRuestung(R);
     destroy();
   }
  else 
   manage (new WindowInfo("Nicht stark genug."));
}

Window_ruestung::Window_ruestung(Grundwerte& W,midgard_CG* h, const Datenbank& Database) 
: Werte(W), hauptfenster(h)
{
 std::string sru="Rüstung auswählen. Bisherige Rüstung: ("+ Werte.Ruestung()->Long() +")";
 label_ruestung->set_text(sru.c_str());
 Gtk::OStream os(clist_ruestung);
 for(std::vector<cH_Ruestung>::const_iterator i=Database.Ruestung.begin();i!=Database.Ruestung.end();++i)
   { cH_Ruestung r(*i);
     if (hauptfenster->region_check(r->Region()))
        os << r->Long() <<"\t"<<r->Name()<<"\t"<<r->LP_Verlust()<<"\t"
            <<r->Min_Staerke()<<"\t"<<r->RW_Verlust()<<"\t"<<r->B_Verlust()<<"\n";
     os.flush(r->ref());
   } 
 for (unsigned int i=0;i<clist_ruestung->columns().size();++i)
   clist_ruestung->set_column_auto_resize(i,true);  
}

