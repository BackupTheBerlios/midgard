// $Id: midgard_CG_kido.cc,v 1.10 2001/05/25 10:22:38 thoma Exp $
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
   if (werte.spezialisierung!="Sanfte Techniken" && 
       werte.spezialisierung!="Harte Techniken" &&
       werte.spezialisierung!="Gemischte Techniken")
    {
      string strinfo="Erst eine Technik wählen\n";
      manage(new WindowInfo(strinfo));
      return;
    }
   vec_kido.clear();
   manage(new KiDo_auswahl(this,maxkido,werte));
}

void midgard_CG::show_kido()
{
   clist_kido->clear();
   Gtk::OStream os(clist_kido);
   for (vector<st_kido>::const_iterator i=vec_kido.begin();i!=vec_kido.end();++i)
    {
      os << i->hoho<<"\t"<<i->technik<<"\t"<<"\t"<<i->ap<<"\t"<<i->fp<<"\n";
    }
   for (unsigned int i=0;i<clist_kido->columns().size();++i)
      clist_kido->set_column_auto_resize(i,true);
}

void midgard_CG::kido_uebernehmen(vector<string>& technik)
{
   clist_kido->clear();
   for (vector<string>::const_iterator i=technik.begin();i!=technik.end();++i)
      vec_kido.push_back(st_kido((*i),"","","",0,0,""));
   get_kido(vec_kido);
   midgard_CG::show_kido();
}

void midgard_CG::stil_optionmenue()
{
  static bool block=false;
  if (block==true) return;
  int ityp = int(optionmenu_KiDo_Stile->get_menu()->get_active()->get_user_data());
  if (ityp==optionmenu_KiDo_Stile::sanft) werte.spezialisierung="Sanfte Techniken";
  if (ityp==optionmenu_KiDo_Stile::hart) werte.spezialisierung="Harte Techniken";
  if (ityp==optionmenu_KiDo_Stile::gemischt) werte.spezialisierung="Gemischte Techniken";
}
