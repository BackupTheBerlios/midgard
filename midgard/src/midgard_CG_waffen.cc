// $Id: midgard_CG_waffen.cc,v 1.22 2001/10/05 09:54:37 thoma Exp $
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
  manage(new Waffen_auswahl(this,Typ->Short(),Typ2->Short(),lernpunkte.Waffen(),Werte));
}

void midgard_CG::show_waffen()
{
   waffen_clist->clear();
   Gtk::OStream os(waffen_clist);
   for(std::vector<H_Data_waffen>::iterator i=vec_Waffen.begin();
         i!=vec_Waffen.end();++i)
      {
         os << (*i)->Name()<<"\t"<<(*i)->Erfolgswert()<<"\n";
      }
   for (unsigned int i=0;i<waffen_clist->columns().size();++i)
      waffen_clist->set_column_auto_resize(i,true);
   waffen_clist->set_reorderable(true);

}

void midgard_CG::waffen_uebernehmen(const std::vector<H_Data_waffen>& saw, map<std::string,string> wg)
{
   vec_Waffen = saw;
   waffen_grundkenntnisse = wg;
   midgard_CG::show_waffen();
   button_geld_waffen->set_sensitive(true);
   button_ruestung->set_sensitive(true);   

   hbox_zauber->set_sensitive(true); 
   table_magier_lernen->set_sensitive(true);
   hbox_kido->set_sensitive(true);
   table_kido_lernen->set_sensitive(true);

}

void midgard_CG::on_waffen_clist_select_row(gint row, gint column, GdkEvent *event)
{   
 /* Funktion für Spezialwaffe */
 if (Typ->Zaubern()=="n" || Typ->Short() == "Ord")
   {
    static int oldrow = -1;
//    ++++vec_waffen[row].erfolgswert;    
//    if(oldrow!=-1) ----vec_waffen[oldrow].erfolgswert;    
    vec_Waffen[row]->set_Erfolgswert(vec_Waffen[row]->Erfolgswert()+2);    
    if(oldrow!=-1) vec_Waffen[oldrow]->set_Erfolgswert(vec_Waffen[oldrow]->Erfolgswert()-2);    
    oldrow=row;
    Werte.Spezialisierung() = waffen_clist->get_text(row,0);
    midgard_CG::waffen_uebernehmen(vec_Waffen,waffen_grundkenntnisse);
   }
}

