// $Id: midgard_CG_lernen.cc,v 1.42 2002/01/15 12:21:18 thoma Exp $
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
#include "Window_herkunft.hh"


void midgard_CG::on_herkunftsland_clicked()
{
   manage (new Window_herkunft(this,Database));
}

void midgard_CG::herkunft_uebernehmen(const cH_Land& s)
{
   Werte.setHerkunft(s); 
   zeige_werte(Werte); 
   button_lernpunkte->set_sensitive(true);
   togglebutton_lernpunkte_edit->set_sensitive(true);
}

void midgard_CG::on_entry_Cname_activate()         
{
  Werte.setCharaktername(entry_Cname->get_text());
}


void midgard_CG::on_lernpunkte_wuerfeln_clicked()
{
  lernpunkte.set_Fach(random.integer(1,6)+random.integer(1,6));
  lernpunkte.set_Allgemein(random.integer(1,6)+1);
  lernpunkte.set_Unge(random.integer(1,6));
  if (Typ[1]->Short()=="") lernpunkte.set_Waffen(random.integer(1,6)+random.integer(1,6));
  else                  lernpunkte.set_Waffen(random.integer(1,6)+1); // Doppelcharakter
  if (Typ[0]->Zaubern()=="j" || Typ[0]->Zaubern() == "z" && Typ[1]->Short()=="") 
      lernpunkte.set_Zauber(random.integer(1,6)+random.integer(1,6));
  if (Typ[1]->Zaubern()=="j" || Typ[1]->Zaubern() == "z" && Typ[1]->Short()!="") 
      lernpunkte.set_Zauber(random.integer(1,6)+1);

//  if (Werte.Alter()==0)
   {
     int age = (lernpunkte.Allgemein() + lernpunkte.Unge() 
             + lernpunkte.Fach()
             + lernpunkte.Waffen() + lernpunkte.Zauber())/4+16;

//     if (Typ[0]->Zaubern()=="z" ) age = age/4+19;
//     if (Typ[0]->Zaubern()=="n" || Typ[0]->Zaubern()=="j") age = age/4+16;
     Werte.setAlter( age * Werte.Spezies()->Alter());
     spinbutton_alter->set_text(itos(Werte.Alter()));
   }
  zeige_lernpunkte();
  zeige_notebook();
}


void midgard_CG::on_button_fach_trans_clicked()
{
 int F=lernpunkte.Fach();
 int U=lernpunkte.Unge();
 if(F>0) 
   {
     lernpunkte.set_Fach(F-1);
     lernpunkte.set_Unge(U+1);
   }
 zeige_lernpunkte();
}

void midgard_CG::on_button_waffe_trans_clicked()
{
 int W=lernpunkte.Waffen();
 int U=lernpunkte.Unge();
 if(W>0) 
   {
     lernpunkte.set_Waffen(W-1);
     lernpunkte.set_Unge(U+1);
   }
 zeige_lernpunkte();
}

void midgard_CG::on_togglebutton_lernpunkte_edit_toggled()
{
//  manage(new Window_lernpunkte_editieren(this,&lernpunkte)); 
  edit_lernpunkte(togglebutton_lernpunkte_edit->get_active());
  zeige_notebook();
}

void midgard_CG::edit_lernpunkte(bool b)
{
 spinbutton_fach->set_sensitive(b);
 spinbutton_allgemein->set_sensitive(b);
 spinbutton_unge->set_sensitive(b);
 spinbutton_waffen->set_sensitive(b);
 spinbutton_zauber->set_sensitive(b);
}

/*
void midgard_CG::setze_lernpunkte(const Lernpunkte& l)
{
 lernpunkte = l;
 zeige_lernpunkte();
}
*/

void midgard_CG::on_spinbutton_fach_activate()
{
  gtk_spin_button_update(spinbutton_fach->gtkobj());
  lernpunkte.set_Fach(spinbutton_fach->get_value_as_int());
  spinbutton_allgemein->grab_focus();
}
void midgard_CG::on_spinbutton_allgemein_activate()
{
  gtk_spin_button_update(spinbutton_unge->gtkobj());
  lernpunkte.set_Unge(spinbutton_unge->get_value_as_int());
  spinbutton_unge->grab_focus();
}
void midgard_CG::on_spinbutton_unge_activate()
{
  gtk_spin_button_update(spinbutton_allgemein->gtkobj());
  lernpunkte.set_Allgemein(spinbutton_allgemein->get_value_as_int());
  spinbutton_waffen->grab_focus();
}
void midgard_CG::on_spinbutton_waffen_activate()
{
  gtk_spin_button_update(spinbutton_waffen->gtkobj());
  lernpunkte.set_Waffen(spinbutton_waffen->get_value_as_int());
  spinbutton_zauber->grab_focus();
}
void midgard_CG::on_spinbutton_zaubern_activate()
{
  gtk_spin_button_update(spinbutton_zauber->gtkobj());
  lernpunkte.set_Waffen(spinbutton_zauber->get_value_as_int());
  edit_lernpunkte(false);
}

                                        

void midgard_CG::zeige_lernpunkte()
{
 spinbutton_fach->set_text(itos(lernpunkte.Fach()));
 spinbutton_allgemein->set_text(itos(lernpunkte.Allgemein()));
 spinbutton_unge->set_text(itos(lernpunkte.Unge()));
 spinbutton_waffen->set_text(itos(lernpunkte.Waffen()));
 spinbutton_zauber->set_text(itos(lernpunkte.Zauber()));
}


void midgard_CG::on_button_geld_waffen_clicked()
{   
  Werte.setGeld(0,0,0);
  on_speichern_clicked();
  manage(new Window_Waffe_Geld(this,Werte,Typ,Database,list_Waffen));
}

void midgard_CG::waffe_besitz_uebernehmen(const std::list<cH_MidgardBasicElement>& wbu)
{
 list_Waffen_besitz = wbu;
 on_speichern_clicked();
}

void midgard_CG::zeige_notebook()
{
   hbox_beruf->set_sensitive(true);
   table_beruf->set_sensitive(true);

   hbox_fertigkeit->set_sensitive(true);
   table_fertigkeit->set_sensitive(true);
   hbox_waffen->set_sensitive(true);
   table_waffen->set_sensitive(true);
   hbox_zauber->set_sensitive(true); 
   table_magier_lernen->set_sensitive(true);
   hbox_kido->set_sensitive(true);
   table_kido_lernen->set_sensitive(true);

}

void midgard_CG::on_button_ruestung_clicked()
{
  std::string rue;
  int wurf = random.integer(1,100);
  if (Typ[0]->Ruestung() == 1)
   {
      if ( 1 <= wurf && wurf  <= 10 ) rue = "OR" ;
      if (11 <= wurf && wurf  <= 20 ) rue = "TR" ;
      if (21 <= wurf && wurf  <= 30 ) rue = "TR" ;
      if (31 <= wurf && wurf  <= 60 ) rue = "LR" ;
      if (61 <= wurf && wurf  <= 80 ) rue = "LR" ;
      if (81 <= wurf && wurf  <= 95 ) rue = "LR" ;
      if (96 <= wurf && wurf  <= 100) rue = "LR" ;
   }    
  if (Typ[0]->Ruestung()== 2)
   {
      if ( 1 <= wurf && wurf  <= 10 ) rue = "OR" ;
      if (11 <= wurf && wurf  <= 20 ) rue = "TR" ;
      if (21 <= wurf && wurf  <= 30 ) rue = "LR" ;
      if (31 <= wurf && wurf  <= 60 ) rue = "LR" ;
      if (61 <= wurf && wurf  <= 80 ) rue = "KR" ;
      if (81 <= wurf && wurf  <= 95 ) rue = "KR" ;
      if (96 <= wurf && wurf  <= 100) rue = "KR" ;
   }    
  if (Typ[0]->Ruestung()== 3)
   {
      if ( 1 <= wurf && wurf  <= 10 ) rue = "OR" ;
      if (11 <= wurf && wurf  <= 20 ) rue = "TR" ;
      if (21 <= wurf && wurf  <= 30 ) rue = "LR" ;
      if (31 <= wurf && wurf  <= 60 ) rue = "KR" ;
      if (61 <= wurf && wurf  <= 80 ) rue = "KR" ;
      if (81 <= wurf && wurf  <= 95 ) rue = "KR" ;
      if (96 <= wurf && wurf  <= 100) rue = "PR" ;
   }    
  if (Typ[0]->Ruestung()== 4)
   {
      if ( 1 <= wurf && wurf  <= 10 ) rue = "OR" ;
      if (11 <= wurf && wurf  <= 20 ) rue = "OR" ;
      if (21 <= wurf && wurf  <= 30 ) rue = "OR" ;
      if (31 <= wurf && wurf  <= 60 ) rue = "TR" ;
      if (61 <= wurf && wurf  <= 80 ) rue = "TR" ;
      if (81 <= wurf && wurf  <= 95 ) rue = "LR" ;
      if (96 <= wurf && wurf  <= 100) rue = "LR" ;
   }    
  Werte.setRuestung(cH_Ruestung(rue));
  std::string strinfo ="Beim Auswürfeln der Rüstung wurde eine\n"+itos(wurf)+" gewürfelt\n";
  strinfo += "---> " + Werte.Ruestung()->Long();
  manage(new WindowInfo(strinfo));
}
