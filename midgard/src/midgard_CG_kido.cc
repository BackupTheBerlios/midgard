// $Id: midgard_CG_kido.cc,v 1.26 2001/11/13 15:26:57 thoma Exp $
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
   list_Kido.clear();
   manage(new KiDo_auswahl(this,maxkido,Werte,Database,Typ));
}

void midgard_CG::show_kido()
{
   clist_kido->clear();
   Gtk::OStream os(clist_kido);
   for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Kido.begin();i!=list_Kido.end();++i)
    {
      cH_KiDo kd(*i);
      os << kd->Hoho()<<"\t"<<kd->Name()<<"\t"<<kd->Ap()<<"\t"<<kd->Kosten(Typ,Database.ausnahmen)<<"\n";
    }
   for (unsigned int i=0;i<clist_kido->columns().size();++i)
      clist_kido->set_column_auto_resize(i,true);
}

void midgard_CG::stil_optionmenue()
{
//  static bool block=false;
//  if (block==true) return;
  int ityp = int(optionmenu_KiDo_Stile->get_menu()->get_active()->get_user_data());
  if (ityp==optionmenu_KiDo_Stile::sanft) Werte.set_Spezialisierung("Sanfte Techniken");
  if (ityp==optionmenu_KiDo_Stile::hart) Werte.set_Spezialisierung("Harte Techniken");
  if (ityp==optionmenu_KiDo_Stile::gemischt) Werte.set_Spezialisierung("Gemischte Techniken");
  // NUR sensetiv setzen, wenn Charaktererschaffung also Grad=1
  if(Werte.Grad()==1) button_kido_auswahl->set_sensitive(true);
}
