// $Id: midgard_CG_beruf.cc,v 1.28 2001/11/06 14:26:21 thoma Exp $
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
#include "Berufe_auswahl.hh"
#include <Gtk_OStream.h>
#include "zufall.h"

void midgard_CG::on_berufe_wahl_clicked()
{
  berufe_clist->clear();
  manage(new Berufe_auswahl(this,Typ[0]->Zaubern(),Typ[1]->Zaubern(),lernpunkte.Beruf(),Werte));
}

void midgard_CG::show_berufe()
{
   berufe_clist->clear();
   Gtk::OStream os(berufe_clist);
   for(std::vector<H_Data_beruf>::iterator i=vec_Beruf.begin();i!=vec_Beruf.end();++i)
      {
         os << (*i)->Name()<<"\t"<<(*i)->Vorteile()<<"\t"<<(*i)->Erfolgswert()<<"\n";
      }
   for (unsigned int i=0;i<berufe_clist->columns().size();++i)
      berufe_clist->set_column_auto_resize(i,true);
   berufe_clist->set_reorderable(true);
}

void midgard_CG::berufe_uebernehmen(std::vector<H_Data_beruf>& sab)
{
   vec_Beruf = sab;
   Database.ausnahmen.set_Beruf(vec_Beruf);
   
   show_berufe();
   button_beruf_erfolgswert->set_sensitive(true);
}

gint midgard_CG::on_beruf_erfolgswert_release_event(GdkEventButton *ev)
{
  if (ev->button==1) on_beruf_erfolgswert_clicked();
  if (ev->button==3) vbox_beruferfolgswert->show();
  hbox_fertigkeit->set_sensitive(true);
  table_fertigkeit->set_sensitive(true);
  return false;
}

void midgard_CG::on_spinbutton_beruferfolgesert_activate()
{
  gtk_spin_button_update(spinbutton_beruferfolgesert->gtkobj());
  int x=spinbutton_beruferfolgesert->get_value_as_int();
  static unsigned int i=0;
  vec_Beruf[i]->set_Erfolgswert(x);
  ++i;
  if (i==vec_Beruf.size())
   {
     i=0;
     vbox_beruferfolgswert->hide();
     label_beruf_ew->set_text("Wert eingeben");
   }
  else  label_beruf_ew->set_text(itos(i+1)+". Beruf");
  berufe_uebernehmen(vec_Beruf);
}


void midgard_CG::on_beruf_erfolgswert_clicked()
{
 Random random;
 int erfahrungswert = (int)((lernpunkte.Waffen() + lernpunkte.Fertigkeiten())/5.);
 int inbo=0;
 if (atoi(in->get_text().c_str()) >= 81 ) ++inbo ;
 if (atoi(in->get_text().c_str()) >= 96 ) ++inbo ;

 for (std::vector<H_Data_beruf>::const_iterator i=vec_Beruf.begin();i!=vec_Beruf.end();++i)
   {
    int ausbildungswert = random.integer(1,3)+6;
    if (i==vec_Beruf.begin()) (*i)->set_Erfolgswert(ausbildungswert+erfahrungswert+inbo);
    else (*i)->set_Erfolgswert(ausbildungswert+inbo);
   } 
   midgard_CG::berufe_uebernehmen(vec_Beruf);
}

