/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2003	    Christof Petig
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

#include "config.h"
#include "zufall_steigern.hh"
#include "Zufall.hh"
#include "KI.hh"
#include "Optionen.hh"
#include <Misc/itos.h>
#include "Prototyp.hh"
#include "Random.hh"

unsigned zufall_steigern::GFPvonGrad(unsigned grad)
{  const Grad_anstieg &GA=Datenbank.GradAnstieg;
   return Random::integer(GA.getGFP(grad),GA.getGFP(grad+1)-1);
}

void zufall_steigern::steigern(Abenteurer &A, unsigned gfp)
{
  assert(A.Typ1()->Valid());
//  check100();
  prozente100.check100();
  Prototyp::setLast(prozente100);
  
  if (A.GFP()>=gfp) return;

  gfp-=A.GFP();

  if(prototypen.empty())
     MagusKI(A).VerteileGFP(gfp,prozente100,GSA_MBE);
  else
   {
     MagusKI(A).VerteileGFP(gfp,prozente100,prototypen);
   }
}

#if 0
std::vector<cH_Prototyp2> zufall_steigern::getSelectedPrototypen()
{
  std::vector<cH_Prototyp2> P;
  std::vector<cH_RowDataBase> VR=tree_prototyp->getSelectedRowDataBase_vec();
  for(std::vector<cH_RowDataBase>::const_iterator i=VR.begin();i!=VR.end();++i)
   {
     const Data_Prototyp *dt=dynamic_cast<const Data_Prototyp*>(&**i);     
     P.push_back(dt->getPrototyp());
   }
  return P;
}


void zufall_steigern::on_radiobutton_steigern_grad_toggled()
{
  if(radiobutton_steigern_grad->get_active())
   {
    spinbutton_grad->set_sensitive(true);
    spinbutton_grad->grab_focus();
    spinbutton_grad->select_region(0,-1);
    spinbutton_gfp->set_sensitive(false);
   }
}

void zufall_steigern::on_radiobutton_steigern_gfp_toggled()
{
  if(radiobutton_steigern_gfp->get_active())
   {
    spinbutton_gfp->set_sensitive(true);
    spinbutton_gfp->grab_focus();
    spinbutton_gfp->select_region(0,-1);
    spinbutton_grad->set_sensitive(false);
   }   
}


void zufall_steigern::fill_combo_steigern()
{
  static bool filled=false;
  if(filled) return;
  filled=true;
  std::list<std::string> L;
  std::list<cH_Prototyp> P=hauptfenster->getDatabase().prototyp;
  for(std::list<cH_Prototyp>::const_iterator i=P.begin();i!=P.end();++i)
     L.push_back((*i)->Name());
  combo_prototyp->set_popdown_strings(L);
  if(!L.empty()) 
     combo_prototyp->get_entry()->set_text(*L.begin());
  on_button_check100_clicked();

 combo_prototyp->set_sensitive(true);
}

void zufall_steigern::on_combo_prototyp_activate()
{
}

bool zufall_steigern::on_combo_prototyp_focus_out_event(GdkEventFocus *ev)
{
  return 0;
}

bool zufall_steigern::entry_is_a_prototyp(const std::string &e)
{
  std::list<std::string> L;
  std::list<cH_Prototyp> P=hauptfenster->getDatabase().prototyp;
  for(std::list<cH_Prototyp>::const_iterator i=P.begin();i!=P.end();++i)
     L.push_back((*i)->Name());
  if(find(L.begin(),L.end(),e)==L.end()) return false;
  return true;
}

void zufall_steigern::on_combo_prototyp_changed()
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
  Prototyp::setLast(prozente100);
   
  set_bereiche_spinbuttons();    
}

void zufall_steigern::set_bereiche_spinbuttons()
{
  spinbutton_fertigkeit->set_value(prozente100.get(Enums::sFert));
  spinbutton_waffen->set_value(prozente100.get(Enums::sWaff));
  spinbutton_waffen_grund->set_value(prozente100.get(Enums::sWGru));
  spinbutton_zauber->set_value(prozente100.get(Enums::sZaub));
  spinbutton_zauberwerk->set_value(prozente100.get(Enums::sZWerk));
  spinbutton_sprachen->set_value(prozente100.get(Enums::sSpra));
  spinbutton_schriften->set_value(prozente100.get(Enums::sSchr));

  scale_fert->set_value(prozente100.getS(Enums::sFert));
  scale_waffen->set_value(prozente100.getS(Enums::sWaff));
  scale_sprachen->set_value(prozente100.getS(Enums::sSpra));
  scale_schriften->set_value(prozente100.getS(Enums::sSchr));

  spinbutton_grund->set_value(GSA_MBE.getG());
  spinbutton_standard->set_value(GSA_MBE.getS());
  spinbutton_ausnahme->set_value(GSA_MBE.getA());
}



void zufall_steigern::on_button_check100_clicked()
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
  
  spinbutton_grund->update();
  spinbutton_standard->update();
  spinbutton_ausnahme->update();
  GSA_MBE.setG(spinbutton_grund->get_value_as_int());
  GSA_MBE.setS(spinbutton_standard->get_value_as_int());
  GSA_MBE.setA(spinbutton_ausnahme->get_value_as_int());

  set_bereiche_spinbuttons();    
  Prototyp::setLast(prozente100);

}


void zufall_steigern::on_scale_fert_activate()
{
  prozente100.setS(Enums::sFert,scale_fert->get_value());
}
void zufall_steigern::on_scale_waffen_activate()
{
  prozente100.setS(Enums::sWaff,scale_waffen->get_value());
}
void zufall_steigern::on_scale_schriften_activate()
{
  prozente100.setS(Enums::sSchr,scale_schriften->get_value());
}
void zufall_steigern::on_scale_sprachen_activate()
{
  prozente100.setS(Enums::sSpra,scale_sprachen->get_value());
}

void zufall_steigern::on_togglebutton_prototyp_toggled()
{
  if(togglebutton_prototyp->get_active()) frame_prototyp_mod->show();
  else frame_prototyp_mod->hide();
}

void zufall_steigern::on_spinbutton_fertigkeit_activate()
{  
  spinbutton_waffen->grab_focus();
  spinbutton_waffen->select_region(0,-1);
}

void zufall_steigern::on_spinbutton_waffen_activate()
{  
  spinbutton_waffen_grund->grab_focus();
  spinbutton_waffen_grund->select_region(0,-1);
}

void zufall_steigern::on_spinbutton_waffen_grund_activate()
{  
  spinbutton_zauber->grab_focus();
  spinbutton_zauber->select_region(0,-1);
}

void zufall_steigern::on_spinbutton_zauber_activate()
{  
  spinbutton_zauberwerk->grab_focus();
  spinbutton_zauberwerk->select_region(0,-1);
}

void zufall_steigern::on_spinbutton_zauberwerk_activate()
{  
  spinbutton_sprachen->grab_focus();
  spinbutton_sprachen->select_region(0,-1);
}

void zufall_steigern::on_spinbutton_sprachen_activate()
{  
  spinbutton_schriften->grab_focus();
  spinbutton_schriften->select_region(0,-1);
}

void zufall_steigern::on_spinbutton_schriften_activate()
{  
 on_button_check100_clicked();
}

void zufall_steigern::on_spinbutton_grund_activate()
{
 spinbutton_standard->grab_focus();
 spinbutton_standard->select_region(0,-1);
}

void zufall_steigern::on_spinbutton_standard_activate()
{
 spinbutton_ausnahme->grab_focus();
 spinbutton_ausnahme->select_region(0,-1);
}

void zufall_steigern::on_spinbutton_ausnahme_activate()
{
  on_button_check100_clicked();
}

#endif
