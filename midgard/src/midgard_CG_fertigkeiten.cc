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
#include "Fertigkeiten_auswahl.hh"
#include <Gtk_OStream.h>
#include "Window_angeb_fert.hh"

void midgard_CG::on_fertigkeiten_wahl_clicked()
{   
//  manage(new Fertigkeiten_auswahl(this,typ.s,werte,lernpunkte,vec_beruf));
  manage(new Fertigkeiten_auswahl(this,typ.s,lernpunkte));
}

void midgard_CG::show_fertigkeiten()
{
   fertigkeiten_clist->clear();
   Gtk::OStream os(fertigkeiten_clist);
   for(vector<st_ausgewaehlte_fertigkeiten>::iterator i=vec_fertigkeiten.begin();
         i!=vec_fertigkeiten.end();++i)
      {
         os << i->name;
         if (i->erfolgswert!=0) os <<"\t" <<i->erfolgswert;
         os << "\n";
      }
   for(vector<st_angeborene_fertigkeit>::iterator i=vec_an_fertigkeit.begin();
         i!=vec_an_fertigkeit.end();++i)
      {
         os << i->name;
         if (i->erfolgswert!=0) os <<"\t" <<i->erfolgswert;
         os << "\n";
      }
   for (unsigned int i=0;i<fertigkeiten_clist->columns().size();++i)
      fertigkeiten_clist->set_column_auto_resize(i,true);
   fertigkeiten_clist->set_reorderable(true);
}

void midgard_CG::fertigkeiten_uebernehmen(vector<st_ausgewaehlte_fertigkeiten>& saf)
{
   vec_fertigkeiten = saf;

   for(vector<st_ausgewaehlte_fertigkeiten>::iterator i=vec_fertigkeiten.begin();
         i!=vec_fertigkeiten.end();++i)
      {
         int bonus = midgard_CG::attribut_check(i->attribut);
         i->erfolgswert += bonus;
      }
    midgard_CG::show_fertigkeiten();
}

gint midgard_CG::on_angeborene_fertigkeit_button_release_event(GdkEventButton *event)
{
  if (event->button==1) midgard_CG::on_angeborene_fertigkeit_clicked() ;
  if (event->button==3) midgard_CG::on_angeborene_fertigkeit_right_clicked() ;
  return false;
}

void midgard_CG::on_angeborene_fertigkeit_clicked()
{
  vec_an_fertigkeit.clear();
  Random random;
  int wurf = random.integer(1,100);
//wurf = -1; /*debug*/
  while (wurf==100)
   {
      manage (new Window_angeb_fert(this,vec_an_fertigkeit,werte,wurf));
      wurf = random.integer(1,100);
   }
  manage (new Window_angeb_fert(this,vec_an_fertigkeit,werte,wurf));
  string stinfo="Für die Angeborene Fertigkeit\n wurde eine ";stinfo+=itos(wurf);stinfo+=" gewürfelt.\n";
  manage(new WindowInfo(stinfo));
  midgard_CG::show_fertigkeiten();
}

void midgard_CG::on_angeborene_fertigkeit_right_clicked()
{
  vec_an_fertigkeit.clear();
  manage (new Window_angeb_fert(this,vec_an_fertigkeit,werte,-1));
  midgard_CG::show_fertigkeiten();
}

