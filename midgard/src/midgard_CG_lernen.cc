// $Id: midgard_CG_lernen.cc,v 1.24 2001/06/29 09:23:29 thoma Exp $
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
#include "Window_lernpunkte_editieren.hh"
#include "Window_Waffe_Geld.hh"


void midgard_CG::on_lernpunkte_wuerfeln_clicked()
{
  Random random;
  lernpunkte.set_Fertigkeit(random.integer(1,6)+random.integer(1,6));
  lernpunkte.set_Beruf(random.integer(1,6)+random.integer(1,6));
  if (Typ2.Short()=="") lernpunkte.set_Waffen(random.integer(1,6)+random.integer(1,6));
  else                  lernpunkte.set_Waffen(random.integer(1,6)+1); // Doppelcharakter
  if (Typ.Zaubern()=="j" || Typ.Zaubern() == "z" && Typ2.Short()=="") 
      lernpunkte.set_Zauber(random.integer(1,6)+random.integer(1,6));
  if (Typ2.Zaubern()=="j" || Typ2.Zaubern() == "z" && Typ2.Short()!="") 
      lernpunkte.set_Zauber(random.integer(1,6)+1);

  if (werte.alter==0)
   {
     int age = lernpunkte.Beruf() + lernpunkte.Fertigkeiten() 
             + lernpunkte.Waffen() + lernpunkte.Zauber();

     if (Typ.Zaubern()=="z" ) werte.alter = age/4+19;
     if (Typ.Zaubern()=="n" || Typ.Zaubern()=="j") werte.alter = age/4+16;
     werte.alter *= spezies_constraint.alter;
     alter->set_text(itos(werte.alter));
   }
  midgard_CG::zeige_lernpunkte();
  zeige_notebook();
}

void midgard_CG::on_lernpunkte_editieren_clicked()
{
  manage(new Window_lernpunkte_editieren(this,&lernpunkte)); 
  zeige_notebook();
}

void midgard_CG::setze_lernpunkte(const Lernpunkte& l)
{
 lernpunkte = l;
 midgard_CG::zeige_lernpunkte();
}

void midgard_CG::zeige_lernpunkte()
{
 lernpunkte_b->set_text(itos(lernpunkte.Beruf()));
 lernpunkte_f->set_text(itos(lernpunkte.Fertigkeiten()));
 lernpunkte_w->set_text(itos(lernpunkte.Waffen()));
 lernpunkte_z->set_text(itos(lernpunkte.Zauber()));
}

void midgard_CG::on_button_ruestung_clicked()
{   
  midgard_CG::ruestung("wuerfeln");
}

void midgard_CG::on_button_geld_waffen_clicked()
{   
  werte.gold=werte.silber=werte.kupfer=0;
  manage(new Window_Waffe_Geld::Window_Waffe_Geld(this,werte,vec_Waffen));
}

void midgard_CG::waffe_besitz_uebernehmen(const std::vector<H_Data_waffen>& wbu)
{
 vec_Waffen_besitz = wbu;
}

void midgard_CG::zeige_notebook()
{
   hbox_beruf->set_sensitive(true);
   table_beruf->set_sensitive(true);
/*
   hbox_fertigkeit->set_sensitive(true);
   table_fertigkeit->set_sensitive(true);
   hbox_waffen->set_sensitive(true);
   table_waffen->set_sensitive(true);
   hbox_zauber->set_sensitive(true); 
   table_magier_lernen->set_sensitive(true);
   hbox_kido->set_sensitive(true);
   table_kido_lernen->set_sensitive(true);

*/
}
