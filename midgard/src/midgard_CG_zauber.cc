// $Id: midgard_CG_zauber.cc,v 1.7 2001/04/19 13:29:12 thoma Exp $
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
  manage(new Zauber_auswahl(this,typ.s,lernpunkte));
}

void midgard_CG::show_zauber()
{
   zauber_clist->clear();
   midgard_CG::Zauber_get_daten(zauber);
   Gtk::OStream os(zauber_clist);
   for(vector<st_zauber>::iterator i=zauber.begin();
         i!=zauber.end();++i)
      {
         os << i->name<<"\t"<<i->erfolgswert<<"\n";
      }
   for (unsigned int i=0;i<zauber_clist->columns().size();++i)
      zauber_clist->set_column_auto_resize(i,true);
   zauber_clist->set_reorderable(true);
}

void midgard_CG::zauber_uebernehmen(vector<st_ausgewaehlte_zauber>& saz)
{
   zauber.clear();
   vec_zauber = saz;
   for(vector<st_ausgewaehlte_zauber>::iterator i=vec_zauber.begin();
         i!=vec_zauber.end();++i)
      {
         string erf = midgard_CG::get_erfolgswert_zaubern(typ,i->name);
         zauber.push_back(st_zauber(i->ap,i->name,erf,"0","0","0","0","0","0","0","0","0","0","0","0","0",0));
      }
   midgard_CG::show_zauber();
}

