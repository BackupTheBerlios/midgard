// $Id: zeige_werte.cc,v 1.53 2002/04/16 10:59:36 thoma Exp $
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
//#include "class_spezies.hh"
#include "dtos1.h"
#include <Aux/itos.h>
#include <Aux/fixedpoint.h>
#include <Aux/Ausgabe_neu.h>
#include "Grad_anstieg.hh"

void midgard_CG::zeige_werte()
{
   if (MOptionen->OptionenCheck(Midgard_Optionen::Original).active) original_midgard_check() ;
   spinbutton_st->set_value(Werte.St());
   spinbutton_gw->set_value(Werte.Gw());
   spinbutton_gs->set_value(Werte.Gs());
   spinbutton_ko->set_value(Werte.Ko());
   spinbutton_in->set_value(Werte.In());
   spinbutton_zt->set_value(Werte.Zt());
   label_sehen->set_text(itos(Werte.Sehen()));
   label_hoeren->set_text(itos(Werte.Hoeren()));
   label_riechen->set_text(itos(Werte.Riechen()));
   label_schmecken->set_text(itos(Werte.Schmecken()));
   label_tasten->set_text(itos(Werte.Tasten()));
   label_sechster_sinn->set_text(itos(Werte.SechsterSinn()));

   spinbutton_au->set_value(Werte.Au());
   spinbutton_pa->set_value(Werte.pA());
   spinbutton_sb->set_value(Werte.Sb());      
   spinbutton_wk->set_value(Werte.Wk());      
   spinbutton_b->set_value(Werte.B());     
   spinbutton_lp->set_value(Werte.LP());      
   spinbutton_ap->set_value(Werte.AP());   
   abwehr_wert->set_text(itos(Werte.Abwehr_wert()));
   zaubern_wert->set_text(itos(Werte.Zaubern_wert()));
   kaw->set_text(itos(Werte.KAW()));
   wlw->set_text(itos(Werte.WLW()));
   resistenz->set_text(itos(Werte.Resistenz()));
   gift_wert->set_text(itos(Werte.Gift()));
   bo_au->set_text(itos(Werte.bo_Au())) ;
   bo_sc->set_text(itos(Werte.bo_Sc())) ;
   bo_an->set_text(itos(Werte.bo_An())) ;
   bo_ab->set_text(itos(Werte.bo_Ab())) ;
   bo_za->set_text(itos(Werte.bo_Za())) ;
   bo_psy->set_text(itos(Werte.bo_Psy(Typ))) ;
   bo_phs->set_text(itos(Werte.bo_Phs(Typ))) ;
   bo_phk->set_text(itos(Werte.bo_Phk(Typ))) ;
   spinbutton_alter->set_value(Werte.Alter());
   spinbutton_gfp->set_value(Werte.GFP());
   spinbutton_tage->set_value(Werte.Steigertage());
   spinbutton_gg->set_value(Werte.GG());
   spinbutton_sg->set_value(Werte.SG());
   label_gestalt->set_text(Werte.Gestalt());  
   spinbutton_Cgewicht->set_value(Werte.Gewicht());
   spinbutton_groesse->set_value(Werte.Groesse());
   spinbutton_grad->set_value(Werte.Grad());      
   entry_spezialisierung->set_text(Werte.Spezialisierung());
   {
    int inr=0;
    for (unsigned int i=0; i<Vstand.size();++i)
    if (Vstand[i]==Werte.Stand()) inr=i;
     optionmenu_stand->set_history(inr);
   }
   {
    int inr=0;
    for (unsigned int i=0; i<Vhand.size();++i)
     if (Vhand[i]==Werte.Hand()) inr=i;
       optionmenu_hand->set_history(inr);
   }
   entry_herkunft->set_text(Werte.Herkunft()->Name());
   entry_glaube->set_text(Werte.Glaube());
   entry_nameC->set_text(Werte.Name_Abenteurer());
   entry_nameS->set_text(Werte.Name_Spieler());
   entry_version->set_text(Werte.Version());
   gfp->set_text(itos(Werte.GFP()));

   label_ruestung_lernschema->set_text(Werte.Ruestung()->Long());
   label_herkunft_lernschema->set_text(Werte.Herkunft()->Name());
   label_s_grad->set_text(itos(Werte.Grad()));
   label_s_ap->set_text(itos(Werte.AP()));
   label_s_abwehr->set_text(itos(Werte.Abwehr_wert()));
   label_s_zaubern->set_text(itos(Werte.Zaubern_wert()));
   label_s_resistenz->set_text(itos(Werte.Resistenz()));
   label_pp_abwehr->set_text(itos(Werte.AbwehrPP()));
   label_pp_zaubern->set_text(itos(Werte.ZaubernPP()));
   label_pp_resistenz->set_text(itos(Werte.ResistenzPP()));
   label_steigertage->set_text(dtos1(Werte.Steigertage()));
   label_steigertage->set_text(Formatiere_short(fixedpoint<1>(Werte.Steigertage())));
   label_alter->set_text(itos(Werte.Alter()));

   
   label_grad_GFP->set_text(Database.GradAnstieg.getGFP_for_str(Grad_anstieg::Grad_fehlt,Werte));
   label_ausdauer_GFP->set_text(Database.GradAnstieg.getGFP_for_str(Grad_anstieg::Ausdauer,Werte));
   label_abwehr_GFP->set_text(Database.GradAnstieg.getGFP_for_str(Grad_anstieg::Abwehr,Werte));
   label_resistenz_GFP->set_text(Database.GradAnstieg.getGFP_for_str(Grad_anstieg::Resistenz,Werte));
   std::string z=Database.GradAnstieg.getGFP_for_str(Grad_anstieg::Zaubern,Werte);
   if(!Typ[0]->is_mage() && !Typ[1]->is_mage()) z="";
   label_zauber_GFP->set_text(z);
}
