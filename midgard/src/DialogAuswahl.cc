/*  MAGuS: Midgard Abenteurer Generieren Und Steigern
 *  Copyright (C) 2006 Christof Petig
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

#include "DialogAuswahl.hh"

void DialogAuswahl::clicked(cH_RowDataBase const& row,int idx,bool &handled)
{ result=row;
  response(Gtk::RESPONSE_OK);
  handled=true;
}

DialogAuswahl::DialogAuswahl(Gtk::Window *parent,int spalten,std::string const& text)
  : MagusDialog(parent), tree(spalten)
{ set_text(text);
  vbox->pack_start(tree);
  set_style(b_Close);
  tree.signal_clicked().connect(sigc::mem_fun(*this,&DialogAuswahl::clicked));
}

cH_ValueBase DialogAuswahl::run()
{ int response=MagusDialog::run();
  return result;
}

void DialogZusatz::einschraenkung_anwenden()
{ std::vector<cH_RowDataBase> datavec;
  for(std::vector<cH_RowDataBase>::const_iterator i=alles.begin();i!=alles.end();++i)
   {
        Handle<const Data_Zusatz> dt=i->cast_dynamic<const Data_Zusatz>();
        if(!!dt) 
        {  if(cb.get_active() || dt->Erlaubt())
              datavec.push_back(*i);
        }
        else
        {  Handle<const Data_Herkunft>dt2=i->cast_dynamic<const Data_Herkunft>();
           if(cb.get_active() || dt2->Erlaubt())
              datavec.push_back(*i);
        }
   }
  get_tree()=datavec;
}

DialogZusatz::DialogZusatz(Gtk::Window *parent,int spalten,std::string const& text)
 : DialogAuswahl(parent,spalten,text), cb("Beschränkung aufheben")
{ vbox->pack_start(cb);
  cb.signal_toggled().connect(sigc::mem_fun(*this,&DialogZusatz::einschraenkung_anwenden));
  einschraenkung_anwenden();
}
