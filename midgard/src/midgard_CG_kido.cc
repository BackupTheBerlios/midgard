// $Id: midgard_CG_kido.cc,v 1.19 2001/06/30 20:30:06 thoma Exp $
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
#include "KiDo_auswahl.hh"
#include <Gtk_OStream.h>


void midgard_CG::on_kido_wahl_clicked()
{
   if (Werte.Spezialisierung()!="Sanfte Techniken" && 
       Werte.Spezialisierung()!="Harte Techniken" &&
       Werte.Spezialisierung()!="Gemischte Techniken")
    {
      std::string strinfo="Erst eine Technik wählen\n";
      manage(new WindowInfo(strinfo));
      return;
    }
   vec_Kido.clear();
   manage(new KiDo_auswahl(this,maxkido,Werte));
}

void midgard_CG::show_kido()
{
   clist_kido->clear();
   Gtk::OStream os(clist_kido);
   for (std::vector<H_Data_kido>::const_iterator i=vec_Kido.begin();i!=vec_Kido.end();++i)
    {
      os << (*i)->Hoho()<<"\t"<<(*i)->Name()<<"\t"<<"\t"<<(*i)->Ap()<<"\t"<<(*i)->Kosten()<<"\n";
    }
   for (unsigned int i=0;i<clist_kido->columns().size();++i)
      clist_kido->set_column_auto_resize(i,true);
}

void midgard_CG::kido_uebernehmen(std::vector<string>& technik)
{
   clist_kido->clear();
   for (std::vector<string>::const_iterator i=technik.begin();i!=technik.end();++i)
      vec_Kido.push_back(new Data_kido(*i));
   get_kido(vec_Kido);
   midgard_CG::show_kido();
}

void midgard_CG::stil_optionmenue()
{
  static bool block=false;
  if (block==true) return;
  int ityp = int(optionmenu_KiDo_Stile->get_menu()->get_active()->get_user_data());
  if (ityp==optionmenu_KiDo_Stile::sanft) Werte.Spezialisierung()="Sanfte Techniken";
  if (ityp==optionmenu_KiDo_Stile::hart) Werte.Spezialisierung()="Harte Techniken";
  if (ityp==optionmenu_KiDo_Stile::gemischt) Werte.Spezialisierung()="Gemischte Techniken";
  button_kido_auswahl->set_sensitive(true);
}
