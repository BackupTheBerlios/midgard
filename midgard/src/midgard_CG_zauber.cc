// $Id: midgard_CG_zauber.cc,v 1.56 2002/03/01 18:56:12 thoma Exp $
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
#include <Gtk_OStream.h>
#ifndef USE_XML
#include <Aux/SQLerror.h>
#endif
#include "Zauber.hh"

/*
void midgard_CG::angeborene_zauber()
{
 if (Typ[0]->Short()=="eBe" || Typ[1]->Short()=="eBe" || Typ[0]->Short()=="dBe" || Typ[1]->Short()=="dBe" ) 
    list_Zauber.push_back(&*cH_Zauber("Lehrersuche"));
 if (Werte.Spezies()->Name()=="Elf") 
    list_Zauber.push_back(&*cH_Zauber("Erkennen der Aura"));
}
*/

void midgard_CG::show_magier_spezialgebiet(bool show)
{
 if (show)
   { spezialgebiet_button_fill();
     option_magier_spezialgebiet->show();
   }
 else option_magier_spezialgebiet->hide();
}

void midgard_CG::spezialgebiet_button_fill()
{
 {
  Gtk::OStream t_(option_magier_spezialgebiet);
  for(std::vector<cH_Spezialgebiet>::iterator i=Database.Spezialgebiet.begin();i!=Database.Spezialgebiet.end();++i)
   {
    if((*i)->Typ() != Typ[0]->Short() && (*i)->Typ() != Typ[1]->Short() ) continue;
    t_ << (*i)->Name();
    t_.flush((*i)->ref(),&HandleContent::unref);
   }  
 }
 option_magier_spezialgebiet->get_menu()->deactivate.connect(SigC::slot(static_cast<class midgard_CG*>(this), &midgard_CG::spezialgebiet_button));
}

void midgard_CG::spezialgebiet_button()
{
 gpointer user_data=option_magier_spezialgebiet->get_menu()->get_active()->get_user_data();
 cH_Spezialgebiet ptr = static_cast<Spezialgebiet*>(user_data);
// if (s=="Spezialgebiet" || s == "Primär- und Sekundärelement") return ;
 Werte.setSpezialgebiet(ptr);
//cout << Werte.Spezialisierung()<<"\t"<<Werte.Spezial()<<"\t"<<Werte.Spezial2(
} 

              