/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

// generated 2002/9/6 20:10:27 CEST by thoma@Tiger.(none)
// using glademm V1.1.1c_cvs
//
// newer (non customized) versions of this file go to table_zufall.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "table_zufall.hh"
#include "midgard_CG.hh"
#include "Zufall.hh"
#include "KI.hh"
#include "Optionen.hh"
#include <Misc/itos.h>
#include "Prototyp.hh"

void table_zufall::on_button_steigern_clicked()
{
  int gfp;
  spinbutton_gfp->update();
  spinbutton_grad->update();
  if(radiobutton_steigern_gfp->get_active()) gfp=spinbutton_gfp->get_value_as_int();
  else { Grad_anstieg GA=hauptfenster->getDatabase().GradAnstieg;
         int grad=spinbutton_grad->get_value_as_int();
         gfp=hauptfenster->random.integer(GA.getGFP(grad),GA.getGFP(grad+1));
cout << grad<<'\t'<<gfp<<'\n';
       }
  MagusKI mki(hauptfenster);
  int spezial_allgemein=int(hauptfenster->table_zufall->hscale_spezial_allgemein->get_adjustment()->get_value());
  mki.VerteileGFP(gfp,spezial_allgemein,prozente100);
}


void table_zufall::on_radiobutton_steigern_grad_toggled()
{
  if(radiobutton_steigern_grad->get_active())
    spinbutton_grad->set_sensitive(true);
}

void table_zufall::on_radiobutton_steigern_gfp_toggled()
{
  if(radiobutton_steigern_gfp->get_active())
    spinbutton_gfp->set_sensitive(true);
}


gint table_zufall::on_hscale_spezial_allgemein_button_release_event(GdkEventButton *ev)
{ 
  Gtk::Adjustment *A=hscale_spezial_allgemein->get_adjustment();
  int Av=(int)A->get_value();
  hauptfenster->table_zufall->label_spezialist->set_text(itos(100-Av)+"%");
  hauptfenster->table_zufall->label_allgemein->set_text(itos(Av)+"%");
  return false;
}


void table_zufall::fill_combo_steigern()
{
  std::list<std::string> L;
  std::list<cH_Prototyp> P=hauptfenster->getDatabase().prototyp;
  for(std::list<cH_Prototyp>::const_iterator i=P.begin();i!=P.end();++i)
     L.push_back((*i)->Name());
  combo_prototyp->set_popdown_strings(L);
}

void table_zufall::on_combo_prototyp_activate()
{
}

gint table_zufall::on_combo_prototyp_focus_out_event(GdkEventFocus *ev)
{
  return 0;
}

void table_zufall::on_combo_prototyp_changed()
{
  if(!combo_prototyp->get_value_in_list()) return;
  cH_Prototyp P(combo_prototyp->get_entry()->get_text());

  prozente100.set(Prozente100::fertigkeiten,P->Fertigkeit());
  prozente100.set(Prozente100::waffen,P->Waffe());
  prozente100.set(Prozente100::waffen_grund,P->WaffeGrund());
  prozente100.set(Prozente100::zauber,P->Zauber());
  prozente100.set(Prozente100::zauberwerk,P->ZauberWerk());
  prozente100.set(Prozente100::sprachen,P->Sprache());
  prozente100.set(Prozente100::schriften,P->Schrift());

  prozente100.check100();
  set_bereiche_spinbuttons();    
}

void table_zufall::set_bereiche_spinbuttons()
{
  spinbutton_fertigkeit->set_value(prozente100.get(Prozente100::fertigkeiten));
  spinbutton_waffen->set_value(prozente100.get(Prozente100::waffen));
  spinbutton_waffen_grund->set_value(prozente100.get(Prozente100::waffen_grund));
  spinbutton_zauber->set_value(prozente100.get(Prozente100::zauber));
  spinbutton_zauberwerk->set_value(prozente100.get(Prozente100::zauberwerk));
  spinbutton_sprachen->set_value(prozente100.get(Prozente100::sprachen));
  spinbutton_schriften->set_value(prozente100.get(Prozente100::schriften));
}



void table_zufall::on_button_check100_clicked()
{
  spinbutton_fertigkeit->update();
  spinbutton_waffen->update();
  spinbutton_waffen_grund->update();
  spinbutton_zauber->update();
  spinbutton_zauberwerk->update();
  spinbutton_sprachen->update();
  spinbutton_schriften->update();
  prozente100.set(Prozente100::fertigkeiten,spinbutton_fertigkeit->get_value_as_int());
  prozente100.set(Prozente100::waffen,spinbutton_waffen->get_value_as_int());
  prozente100.set(Prozente100::waffen_grund,spinbutton_waffen_grund->get_value_as_int());
  prozente100.set(Prozente100::zauber,spinbutton_zauber->get_value_as_int());
  prozente100.set(Prozente100::zauberwerk,spinbutton_zauberwerk->get_value_as_int());
  prozente100.set(Prozente100::sprachen,spinbutton_sprachen->get_value_as_int());
  prozente100.set(Prozente100::schriften,spinbutton_schriften->get_value_as_int());
  prozente100.check100();
  set_bereiche_spinbuttons();    
  
}

