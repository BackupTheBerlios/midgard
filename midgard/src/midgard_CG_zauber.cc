// $Id: midgard_CG_zauber.cc,v 1.24 2001/06/27 10:10:16 thoma Exp $
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
#include "Zauber_auswahl.hh"
#include <Gtk_OStream.h>

void midgard_CG::on_zauber_wahl_clicked()
{
  zauber_clist->clear();
  if (werte.spezial2=="" && Typ.Short()=="eBe")
   {
      string strinfo="Erst Primär- und Sekundärelement wählen\n";
      manage(new WindowInfo(strinfo));
      return;
   }
  manage(new Zauber_auswahl(this,werte,Typ,Typ2,lernpunkte.Zauber()));
}

void midgard_CG::show_zauber()
{
   zauber_clist->clear();
   midgard_CG::Zauber_get_Daten(vec_Zauber);
   Gtk::OStream os(zauber_clist);
   for(vector<H_Data_zauber>::const_iterator i=vec_Zauber.begin();
         i!=vec_Zauber.end();++i)
      {
         os << (*i)->Name()<<"\t"<<(*i)->Erfolgswert()<<"\n";
      }
   for (unsigned int i=0;i<zauber_clist->columns().size();++i)
      zauber_clist->set_column_auto_resize(i,true);
   zauber_clist->set_reorderable(true);
}

void midgard_CG::zauber_uebernehmen(const vector<H_Data_zauber>& saz)
{
   vec_Zauber=saz;
   angeborene_zauber();
   for(vector<H_Data_zauber>::const_iterator i=vec_Zauber.begin();
         i!=vec_Zauber.end();++i)
      {
         int erf = midgard_CG::get_erfolgswert_zaubern(Typ,Typ2,(*i)->Name());
         (*i)->set_Erfolgswert(erf);
      }
   midgard_CG::show_zauber();
}

void midgard_CG::angeborene_zauber()
{
 if (Typ.Short()=="eBe" || Typ2.Short()=="eBe" || Typ.Short()=="dBe" || Typ2.Short()=="dBe" ) 
    vec_Zauber.push_back(new Data_zauber("Lehrersuche"));
 if (werte.spezies=="Elf") 
    vec_Zauber.push_back(new Data_zauber("Erkennen der Aura"));
}
