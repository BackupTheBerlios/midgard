// $Id: midgard_CG_waffen.cc,v 1.9 2001/05/15 22:21:41 thoma Exp $
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
#include "Waffen_auswahl.hh"
#include <Gtk_OStream.h>

void midgard_CG::on_waffen_wahl_clicked()
{
  waffen_clist->clear();
  manage(new Waffen_auswahl(this,typ.s,typ_2.s,lernpunkte,werte));
}

void midgard_CG::show_waffen()
{
   waffen_clist->clear();
   Gtk::OStream os(waffen_clist);
   for(vector<st_ausgewaehlte_waffen>::iterator i=vec_waffen.begin();
         i!=vec_waffen.end();++i)
      {
         os << i->name<<"\t"<<i->erfolgswert<<"\n";
      }
   for (unsigned int i=0;i<waffen_clist->columns().size();++i)
      waffen_clist->set_column_auto_resize(i,true);
   waffen_clist->set_reorderable(true);

}

void midgard_CG::waffen_uebernehmen(vector<st_ausgewaehlte_waffen>& saw, map<string,string> wg)
{
   vec_waffen = saw;
   waffen_grundkenntnisse = wg;
   midgard_CG::show_waffen();
}

void midgard_CG::on_waffen_clist_select_row(gint row, gint column, GdkEvent *event)
{   
 /* Funktion für Spezialwaffe */
 if (typ.z=="n" || typ.s == "Ord")
   {
    static int oldrow = -1;
    ++++vec_waffen[row].erfolgswert;    
    if(oldrow!=-1) ----vec_waffen[oldrow].erfolgswert;    
    oldrow=row;
    werte.spezialisierung = waffen_clist->get_text(row,0);
    midgard_CG::waffen_uebernehmen(vec_waffen,waffen_grundkenntnisse);
   }
}

