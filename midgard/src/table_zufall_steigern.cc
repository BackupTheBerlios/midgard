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
         gfp-=hauptfenster->getWerte().GFP();
cout << grad<<'\t'<<gfp<<'\n';
         if(gfp<=0) return;
       }
  MagusKI mki(hauptfenster);
//  int spezial_allgemein=int(hscale_spezial_allgemein->get_adjustment()->get_value());
  mki.VerteileGFP(gfp,prozente100);
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


void table_zufall::fill_combo_steigern()
{
  std::list<std::string> L;
  std::list<cH_Prototyp> P=hauptfenster->getDatabase().prototyp;
  for(std::list<cH_Prototyp>::const_iterator i=P.begin();i!=P.end();++i)
     L.push_back((*i)->Name());
  combo_prototyp->set_popdown_strings(L);
  if(!L.empty()) combo_prototyp->get_entry()->set_text(*L.begin());
  on_button_check100_clicked();

 combo_prototyp->set_sensitive(true);
}

void table_zufall::on_combo_prototyp_activate()
{
}

gint table_zufall::on_combo_prototyp_focus_out_event(GdkEventFocus *ev)
{
  return 0;
}

bool table_zufall::entry_is_a_prototyp(const std::string &e)
{
  std::list<std::string> L;
  std::list<cH_Prototyp> P=hauptfenster->getDatabase().prototyp;
  for(std::list<cH_Prototyp>::const_iterator i=P.begin();i!=P.end();++i)
     L.push_back((*i)->Name());
  if(find(L.begin(),L.end(),e)==L.end()) return false;
  return true;
}

void table_zufall::on_combo_prototyp_changed()
{
  std::string e=combo_prototyp->get_entry()->get_text();
  if(!entry_is_a_prototyp(e)) return;
  cH_Prototyp P(e);

  prozente100.set(Enums::sFert,P->Fertigkeit());
  prozente100.set(Enums::sWaff,P->Waffe());
  prozente100.set(Enums::sWGru,P->WaffeGrund());
  prozente100.set(Enums::sZaub,P->Zauber());
  prozente100.set(Enums::sZWerk,P->ZauberWerk());
  prozente100.set(Enums::sSpra,P->Sprache());
  prozente100.set(Enums::sSchr,P->Schrift());
  prozente100.setS(Enums::sFert,P->FertSpezialist());
  prozente100.setS(Enums::sWaff,P->WaffSpezialist());
  prozente100.setS(Enums::sSpra,P->SpraSpezialist());
  prozente100.setS(Enums::sSchr,P->SchrSpezialist());

  prozente100.check100();
  set_bereiche_spinbuttons();    
}

void table_zufall::set_bereiche_spinbuttons()
{
  spinbutton_fertigkeit->set_value(prozente100.get(Enums::sFert));
  spinbutton_waffen->set_value(prozente100.get(Enums::sWaff));
  spinbutton_waffen_grund->set_value(prozente100.get(Enums::sWGru));
  spinbutton_zauber->set_value(prozente100.get(Enums::sZaub));
  spinbutton_zauberwerk->set_value(prozente100.get(Enums::sZWerk));
  spinbutton_sprachen->set_value(prozente100.get(Enums::sSpra));
  spinbutton_schriften->set_value(prozente100.get(Enums::sSchr));

  int wf=prozente100.getS(Enums::sFert);
  int ww=prozente100.getS(Enums::sWaff);
  int wsp=prozente100.getS(Enums::sSpra);
  int wsc=prozente100.getS(Enums::sSchr);
  vscale_spezallg_fert->get_adjustment()->set_value(wf);
  vscale_spezallg_waff->get_adjustment()->set_value(ww);
  vscale_spezallg_spra->get_adjustment()->set_value(wsp);
  vscale_spezallg_schr->get_adjustment()->set_value(wsc);
  label_spez_fert->set_text(itos(100-wf)+"%");
  label_spez_waff->set_text(itos(100-ww)+"%");
  label_spez_spra->set_text(itos(100-wsp)+"%");
  label_spez_schr->set_text(itos(100-wsc)+"%");
  label_allg_fert->set_text(itos(wf)+"%");
  label_allg_waff->set_text(itos(ww)+"%");
  label_allg_spra->set_text(itos(wsp)+"%");
  label_allg_schr->set_text(itos(wsc)+"%");
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
  prozente100.set(Enums::sFert,spinbutton_fertigkeit->get_value_as_int());
  prozente100.set(Enums::sWaff,spinbutton_waffen->get_value_as_int());
  prozente100.set(Enums::sWGru,spinbutton_waffen_grund->get_value_as_int());
  prozente100.set(Enums::sZaub,spinbutton_zauber->get_value_as_int());
  prozente100.set(Enums::sZWerk,spinbutton_zauberwerk->get_value_as_int());
  prozente100.set(Enums::sSpra,spinbutton_sprachen->get_value_as_int());
  prozente100.set(Enums::sSchr,spinbutton_schriften->get_value_as_int());
  prozente100.check100();
  set_bereiche_spinbuttons();    
  
}


gint table_zufall::on_vscale_spezallg_fert_button_release_event(GdkEventButton *ev)
{ 
  int Av=(int)vscale_spezallg_fert->get_adjustment()->get_value();
  label_spez_fert->set_text(itos(100-Av)+"%");
  label_allg_fert->set_text(itos(Av)+"%");
  prozente100.setS(Enums::sFert,Av);
  return false;
}

gint table_zufall::on_vscale_spezallg_waff_button_release_event(GdkEventButton *ev)
{ 
  int Av=(int)vscale_spezallg_waff->get_adjustment()->get_value();
  label_spez_waff->set_text(itos(100-Av)+"%");
  label_allg_waff->set_text(itos(Av)+"%");
  prozente100.setS(Enums::sWaff,Av);
  return false;
}

gint table_zufall::on_vscale_spezallg_spra_button_release_event(GdkEventButton *ev)
{ 
  int Av=(int)vscale_spezallg_spra->get_adjustment()->get_value();
  label_spez_spra->set_text(itos(100-Av)+"%");
  label_allg_spra->set_text(itos(Av)+"%");
  prozente100.setS(Enums::sSpra,Av);
  return false;
}

gint table_zufall::on_vscale_spezallg_schr_button_release_event(GdkEventButton *ev)
{ 
  int Av=(int)vscale_spezallg_schr->get_adjustment()->get_value();
  label_spez_schr->set_text(itos(100-Av)+"%");
  label_allg_schr->set_text(itos(Av)+"%");
  prozente100.setS(Enums::sSchr,Av);
  return false;
}

