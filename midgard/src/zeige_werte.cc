// $Id: zeige_werte.cc,v 1.55 2002/05/14 14:01:44 thoma Exp $
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
   label_pp_spezial->set_text(itos(Werte.SpezialPP()));
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
