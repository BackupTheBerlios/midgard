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


void table_zufall::on_button_zufall_voll_clicked()
{
   hauptfenster->on_wizard_beenden_activate();
   Midgard_Optionen *MO=hauptfenster->MOptionen;
   bool old_value=MO->OberCheck(Midgard_Optionen::NoInfoFenster).active;
   std::string noinfofenster=MO->OberCheck(Midgard_Optionen::NoInfoFenster).text;
   MO->setOber(noinfofenster,true);
   Abenteurer oldAben=hauptfenster->getAben();
   hauptfenster->getChar().push_back();
   hauptfenster->on_neuer_charakter_clicked();
   hauptfenster->table_lernschema->init(hauptfenster);
   hauptfenster->table_steigern->init(hauptfenster);
   
   Zufall zufall(hauptfenster);

   try{
   if(!togglebutton_vorgaben->get_active()) zufall.Voll();
   else
    {
      Zufall::e_Vorgabe v=getVorgaben(oldAben);
      zufall.Teil(v,oldAben);
    }
   }catch (std::exception &e) { std::cerr << e.what()<<'\n';}
   MO->setOber(noinfofenster,old_value);
   hauptfenster->frame_lernschema->set_sensitive(true);
   hauptfenster->frame_steigern->set_sensitive(true);
}



Zufall::e_Vorgabe table_zufall::getVorgaben(Abenteurer& oldAben) const
{
   LernListen LL(hauptfenster->getDatabase());
      Zufall::e_Vorgabe v=Zufall::e_Vorgabe(0);
      if(checkbutton_spezies->get_active()) 
         { v=Zufall::e_Vorgabe(v|Zufall::eSpezies);
           std::string spezies=combo_spezies->get_entry()->get_text();
           if(Spezies::get_Spezies_from_long(LL.getSpezies(true),spezies))
              oldAben.getWerte().setSpezies(Spezies::getSpezies(spezies,LL.getSpezies(true)));
         }
      if(checkbutton_typ->get_active())  
         {  v=Zufall::e_Vorgabe(v|Zufall::eTyp);
           std::string typ=combo_typ->get_entry()->get_text();
           if(Typen::get_Typ_from_long(hauptfenster->getCDatabase().Typen,typ))
              oldAben.setTyp1(cH_Typen(typ));
         }
      if(checkbutton_herkunft->get_active())
         { v=Zufall::e_Vorgabe(v|Zufall::eHerkunft);
           cH_Land L(combo_herkunft->get_entry()->get_text(),true);
           oldAben.getWerte().setHerkunft(L);
         }
      if(checkbutton_ange_fert->get_active())v=Zufall::e_Vorgabe(v|Zufall::eAngeFert);
      if(checkbutton_werte->get_active())
        {
         if(checkbutton_st->get_active())  
           { v=Zufall::e_Vorgabe(v|Zufall::eSt); 
             spinbutton_st->update();
             oldAben.getWerte().setSt(spinbutton_st->get_value_as_int());
           }
         if(checkbutton_gs->get_active()) 
           { v=Zufall::e_Vorgabe(v|Zufall::eGs);
             spinbutton_gs->update();
             oldAben.getWerte().setGs(spinbutton_gs->get_value_as_int());
           }
         if(checkbutton_gw->get_active())
           { v=Zufall::e_Vorgabe(v|Zufall::eGw);
             spinbutton_gw->update();
             oldAben.getWerte().setGw(spinbutton_gw->get_value_as_int());
           }
         if(checkbutton_ko->get_active())  
           { v=Zufall::e_Vorgabe(v|Zufall::eKo);
             spinbutton_ko->update();
             oldAben.getWerte().setKo(spinbutton_ko->get_value_as_int());
           }
         if(checkbutton_in->get_active()) 
           { v=Zufall::e_Vorgabe(v|Zufall::eIn);
             spinbutton_in->update();
             oldAben.getWerte().setIn(spinbutton_in->get_value_as_int());
           }
         if(checkbutton_zt->get_active()) 
           { v=Zufall::e_Vorgabe(v|Zufall::eZt);
             spinbutton_zt->update();
             oldAben.getWerte().setZt(spinbutton_zt->get_value_as_int());
           }
         if(checkbutton_au->get_active()) 
           { v=Zufall::e_Vorgabe(v|Zufall::eAu);
             spinbutton_au->update();
             oldAben.getWerte().setAu(spinbutton_au->get_value_as_int());
           }
         if(checkbutton_pa->get_active())  
           { v=Zufall::e_Vorgabe(v|Zufall::epA);
             spinbutton_pa->update();
             oldAben.getWerte().setpA(spinbutton_pa->get_value_as_int());
           }
         if(checkbutton_wk->get_active())  
           { v=Zufall::e_Vorgabe(v|Zufall::eWk);
             spinbutton_wk->update();
             oldAben.getWerte().setWk(spinbutton_wk->get_value_as_int());
           }
         if(checkbutton_sb->get_active())    
           { v=Zufall::e_Vorgabe(v|Zufall::eSb);
             spinbutton_sb->update();
             oldAben.getWerte().setSb(spinbutton_sb->get_value_as_int());
           }
         if(checkbutton_b->get_active())  
           { v=Zufall::e_Vorgabe(v|Zufall::eB);
             spinbutton_b->update();
             oldAben.getWerte().setB(spinbutton_b->get_value_as_int());
           }
        }
  return v;
}

void table_zufall::on_togglebutton_vorgaben_toggled()
{
  if(togglebutton_vorgaben->get_active()) 
   {
     frame_vorgaben->show();
//     hauptfenster->table_grundwerte->togglebutton_edit_werte->set_active(true);
   }
  else frame_vorgaben->hide();
}

void table_zufall::zeige_werte()
{
   spinbutton_st->set_value(hauptfenster->getWerte().St());
   spinbutton_gw->set_value(hauptfenster->getWerte().Gw());
   spinbutton_gs->set_value(hauptfenster->getWerte().Gs());
   spinbutton_ko->set_value(hauptfenster->getWerte().Ko());
   spinbutton_in->set_value(hauptfenster->getWerte().In());
   spinbutton_zt->set_value(hauptfenster->getWerte().Zt());
   spinbutton_au->set_value(hauptfenster->getWerte().Au());
   spinbutton_pa->set_value(hauptfenster->getWerte().pA());
   spinbutton_sb->set_value(hauptfenster->getWerte().Sb());      
   spinbutton_wk->set_value(hauptfenster->getWerte().Wk());      
   spinbutton_b->set_value(hauptfenster->getWerte().B());     
   combo_spezies->get_entry()->set_text(hauptfenster->getWerte().Spezies()->Name());
   combo_typ ->get_entry()->set_text(hauptfenster->getChar()->Typ1()->Name(hauptfenster->getWerte().Geschlecht()));
   combo_herkunft->get_entry()->set_text(hauptfenster->getWerte().Herkunft()->Name());
}

void table_zufall::fill_combos()
{
  bool nsc_allowed = hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::NSC_only).active;
  LernListen LL(hauptfenster->getCDatabase());
  std::list<std::string> L;

  // Typen
  fill_combo_typen(LL,nsc_allowed);
/*  
  const std::vector<std::pair<cH_Typen,bool> > T=LL.getTypen(hauptfenster->getAben(),nsc_allowed);
  for(std::vector<std::pair<cH_Typen,bool> >::const_iterator i=T.begin();i!=T.end();++i)
     L.push_back(i->first->Name(hauptfenster->getWerte().Geschlecht()));
  combo_typ->set_popdown_strings(L);
*/
  // Spezies
  L.clear();
  std::vector<cH_Spezies> S=LL.getSpezies(nsc_allowed);
  for(std::vector<cH_Spezies>::const_iterator i=S.begin();i!=S.end();++i)
     L.push_back((*i)->Name());
 combo_spezies->set_popdown_strings(L);

  // Herkunft
  L.clear();
   std::vector<std::pair<cH_Land,bool> > H=LL.getHerkunft(hauptfenster->getAben());
  for(std::vector<std::pair<cH_Land,bool> >::const_iterator i=H.begin();i!=H.end();++i)
     L.push_back(i->first->Name());
 L.sort();
 combo_herkunft->set_popdown_strings(L);
}

void table_zufall::fill_combo_typen(const LernListen &LL,const bool nsc_allowed)
{
  std::list<std::string> L;
  cH_Spezies spezies=hauptfenster->getWerte().Spezies();

  // ist eine Spezies in der Combo gesetzt?
  std::string ss=combo_spezies->get_entry()->get_text();
  if(Spezies::get_Spezies_from_long(hauptfenster->getCDatabase().Spezies,ss))
     spezies=Spezies::getSpezies(ss,hauptfenster->getDatabase().Spezies)  ;    

  const std::vector<std::pair<cH_Typen,bool> > T=LL.getTypen(hauptfenster->getWerte(),spezies,nsc_allowed);
  for(std::vector<std::pair<cH_Typen,bool> >::const_iterator i=T.begin();i!=T.end();++i)
     L.push_back(i->first->Name(hauptfenster->getWerte().Geschlecht()));
  combo_typ->set_popdown_strings(L);
}


void table_zufall::on_checkbutton_spezies_toggled()
{ if(checkbutton_spezies->get_active()) combo_spezies->set_sensitive(true);
  else combo_spezies->set_sensitive(false);
}

void table_zufall::on_checkbutton_werte_toggled()
{ if(checkbutton_werte->get_active()) frame_werte_vorgaben->show();
  else frame_werte_vorgaben->hide();
}


void table_zufall::on_checkbutton_herkunft_toggled()
{ if(checkbutton_herkunft->get_active()) combo_herkunft->set_sensitive(true);
  else combo_herkunft->set_sensitive(false);
}

void table_zufall::on_checkbutton_typ_toggled()
{ if(checkbutton_typ->get_active()) combo_typ->set_sensitive(true);
  else combo_typ->set_sensitive(false);
}

void table_zufall::on_checkbutton_st_toggled()
{ if(checkbutton_st->get_active()) spinbutton_st->set_sensitive(true);
  else spinbutton_st->set_sensitive(false);
}

void table_zufall::on_checkbutton_gs_toggled()
{ if(checkbutton_gs->get_active()) spinbutton_gs->set_sensitive(true);
  else spinbutton_gs->set_sensitive(false);
}

void table_zufall::on_checkbutton_gw_toggled()
{ if(checkbutton_gw->get_active()) spinbutton_gw->set_sensitive(true);
  else spinbutton_gw->set_sensitive(false);
}

void table_zufall::on_checkbutton_ko_toggled()
{ if(checkbutton_ko->get_active()) spinbutton_ko->set_sensitive(true);
  else spinbutton_ko->set_sensitive(false);
}

void table_zufall::on_checkbutton_in_toggled()
{ if(checkbutton_in->get_active()) spinbutton_in->set_sensitive(true);
  else spinbutton_in->set_sensitive(false);
}

void table_zufall::on_checkbutton_zt_toggled()
{ if(checkbutton_zt->get_active()) spinbutton_zt->set_sensitive(true);
  else spinbutton_zt->set_sensitive(false);
}

void table_zufall::on_checkbutton_au_toggled()
{ if(checkbutton_au->get_active()) spinbutton_au->set_sensitive(true);
  else spinbutton_au->set_sensitive(false);
}

void table_zufall::on_checkbutton_pa_toggled()
{ if(checkbutton_pa->get_active()) spinbutton_pa->set_sensitive(true);
  else spinbutton_pa->set_sensitive(false);
}

void table_zufall::on_checkbutton_wk_toggled()
{ if(checkbutton_wk->get_active()) spinbutton_wk->set_sensitive(true);
  else spinbutton_wk->set_sensitive(false);
}

void table_zufall::on_checkbutton_sb_toggled()
{ if(checkbutton_sb->get_active()) spinbutton_sb->set_sensitive(true);
  else spinbutton_sb->set_sensitive(false);
}

void table_zufall::on_checkbutton_b_toggled()
{ if(checkbutton_b->get_active()) spinbutton_b->set_sensitive(true);
  else spinbutton_b->set_sensitive(false);  
}

void table_zufall::on_combo_spezies_activate()
{  
}

bool table_zufall::on_combo_spezies_focus_out_event(GdkEventFocus *ev)
{  return false;
}

void table_zufall::on_combo_spezies_changed()
{  
  LernListen LL(hauptfenster->getCDatabase());
  bool nsc_allowed = hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::NSC_only).active;
  fill_combo_typen(LL,nsc_allowed);
}

void table_zufall::on_combo_typ_activate()
{  
}

bool table_zufall::on_combo_typ__focus_out_event(GdkEventFocus *ev)
{  return 0;
}

void table_zufall::on_combo_typ__changed()
{  
}

