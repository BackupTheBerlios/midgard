// $Id: table_grundwerte_grundwere_edit.cc,v 1.29 2006/02/19 21:46:02 christof Exp $
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

#include "table_grundwerte.hh"
#include "midgard_CG.hh"
#include "libmagus/Datenbank.hh"
#include <Misc/TemporaryValue.hh>

static bool oldtyp_bool;

void table_grundwerte::on_togglebutton_edit_werte_toggled()
{
  if(edit_werte)
   { 
     TemporaryValue<bool> m(combo_typ->is_sensitive(),true);
     edit_sensitive(true);
     hauptfenster->getChar()->begin_undo();
   }
  else 
    {
//     set_all_entrys(); // eigentlich überflüssig (wg. focus_leaf_event)
     edit_sensitive(false);
     fill_typauswahl();
     hauptfenster->getChar().name_undo("Werte editiert");
    }
}

void table_grundwerte::on_button_grda1setzen_clicked()
{
  hauptfenster->getAben().setGrad1Werte();
  zeige_werte();
//  hauptfenster->lernschema_sensitive(true);
//  hauptfenster->frame_steigern->set_sensitive(true);
}

void table_grundwerte::on_entry_nameC_activate()
{ 
  if(hauptfenster->getChar().getWizard().aktiv()) 
   { 
     if (hauptfenster->getChar().getWizard().getMode().Value()==Wizard::Aktiv)
     	edit_werte=false;
     hauptfenster->getChar().getWizard().done(Wizard::NAMEN,hauptfenster->getAben());
   }
  else 
   {
     entry_nameS->grab_focus();
   }
}
bool table_grundwerte::on_entry_nameC_focus_out_event(GdkEventFocus *ev)
{ hauptfenster->getAben().setNameC(entry_nameC->get_text());  
//  hauptfenster->set_title(hauptfenster->getAben().Name_Abenteurer());
  return false; 
}

void table_grundwerte::on_entry_nameS_activate()
{ entry_version->grab_focus(); }
bool table_grundwerte::on_entry_nameS_focus_out_event(GdkEventFocus *ev)
{ hauptfenster->getAben().setNameS(entry_nameS->get_text()); return false;}

void table_grundwerte::on_entry_version_activate()
{  entry_bezeichnung->grab_focus();}
bool table_grundwerte::on_entry_version_focus_out_event(GdkEventFocus *ev)
{  hauptfenster->getAben().setVersion(entry_version->get_text()); return false;}

void table_grundwerte::on_entry_bezeichnung_activate()
{ entry_herkunft->grab_focus();}
bool table_grundwerte::on_entry_bezeichnung_focus_out_event(GdkEventFocus *ev)
{  hauptfenster->getAben().setBezeichnung(entry_bezeichnung->get_text());return false;}

void table_grundwerte::on_entry_spezialisierung_activate()
{ entry_merkmale->grab_focus();}
bool table_grundwerte::on_entry_spezialisierung_focus_out_event(GdkEventFocus *ev)
{  hauptfenster->getAben().setSpezialisierung(entry_spezialisierung->get_text());return false;}

void table_grundwerte::on_entry_merkmale_activate()
{ spinbutton_grad->grab_focus();}
bool table_grundwerte::on_entry_merkmale_focus_out_event(GdkEventFocus *ev)
{  hauptfenster->getAben().setMerkmale(entry_merkmale->get_text());return false;}

void table_grundwerte::on_entry_glaube_activate()
{ entry_spezialisierung->grab_focus();}
bool table_grundwerte::on_entry_glaube_focus_out_event(GdkEventFocus *ev)
{  hauptfenster->getAben().setGlaube(entry_glaube->get_text());return false;}

void table_grundwerte::on_entry_herkunft_activate()
{ entry_glaube->grab_focus();}
bool table_grundwerte::on_entry_herkunft_focus_out_event(GdkEventFocus *ev)
{  hauptfenster->getAben().setHerkunft(cH_Land(entry_herkunft->get_text(),true)); return false;}



void table_grundwerte::on_spinbutton_grad_activate()
{ 
  spinbutton_lp->grab_focus();
}
bool table_grundwerte::on_spinbutton_grad_focus_out_event(GdkEventFocus *ev)
{  spinbutton_grad->update(); 
   hauptfenster->getAben().setGrad(spinbutton_grad->get_value_as_int()); 
   hauptfenster->getAben().set_Grad_Basiswerte(hauptfenster->getAben().Grad());
   int mingfp=Datenbank.GradAnstieg.getGFP_for(Grad_anstieg::Grad_,hauptfenster->getAben());
   spinbutton_gfp->update();
   if (mingfp>spinbutton_gfp->get_value_as_int()) { hauptfenster->getAben().setGFP(mingfp); }
   return false; 
}

void table_grundwerte::on_spinbutton_lp_activate()
{ spinbutton_ap->grab_focus();}
bool table_grundwerte::on_spinbutton_lp_focus_out_event(GdkEventFocus *ev)
{ spinbutton_lp->update();  hauptfenster->getAben().setLP(spinbutton_lp->get_value_as_int()); return false;}

void table_grundwerte::on_spinbutton_ap_activate()
{ spinbutton_alter->grab_focus();}
bool table_grundwerte::on_spinbutton_ap_focus_out_event(GdkEventFocus *ev)
{  spinbutton_ap->update();  hauptfenster->getAben().setAP(spinbutton_ap->get_value_as_int()); return false;}


void table_grundwerte::on_spinbutton_Cgewicht_activate()
{ spinbutton_groesse->grab_focus();}
bool table_grundwerte::on_spinbutton_Cgewicht_focus_out_event(GdkEventFocus *ev)
{ spinbutton_Cgewicht->update();  hauptfenster->getAben().setGewicht(spinbutton_Cgewicht->get_value_as_int()); zeige_werte();return false;}

void table_grundwerte::on_spinbutton_groesse_activate()
{ spinbutton_tage->grab_focus();}
bool table_grundwerte::on_spinbutton_groesse_focus_out_event(GdkEventFocus *ev)
{ spinbutton_groesse->update();   hauptfenster->getAben().setGroesse(spinbutton_groesse->get_value_as_int()); zeige_werte();return false;}

void table_grundwerte::on_spinbutton_alter_activate()
{ spinbutton_Cgewicht->grab_focus();}
bool table_grundwerte::on_spinbutton_alter_focus_out_event(GdkEventFocus *ev)
{ spinbutton_alter->update();  hauptfenster->getAben().setAlter(spinbutton_alter->get_value_as_int()); return false;}

void table_grundwerte::on_spinbutton_tage_activate()
{ spinbutton_gg->grab_focus();}
bool table_grundwerte::on_spinbutton_tage_focus_out_event(GdkEventFocus *ev)
{ spinbutton_tage->update(); hauptfenster->getAben().setSteigertage(spinbutton_tage->get_value_as_int()); return false;}

void table_grundwerte::on_spinbutton_gg_activate()
{ spinbutton_sg->grab_focus();}
bool table_grundwerte::on_spinbutton_gg_focus_out_event(GdkEventFocus *ev)
{ spinbutton_gg->update();  hauptfenster->getAben().setGG(spinbutton_gg->get_value_as_int()); return false;}

void table_grundwerte::on_spinbutton_sg_activate()
{ spinbutton_gfp->grab_focus();}
bool table_grundwerte::on_spinbutton_sg_focus_out_event(GdkEventFocus *ev)
{ spinbutton_sg->update();  hauptfenster->getAben().setSG(spinbutton_sg->get_value_as_int()); return false;}

void table_grundwerte::on_spinbutton_gfp_activate()
{ spinbutton_st->grab_focus();}
bool table_grundwerte::on_spinbutton_gfp_focus_out_event(GdkEventFocus *ev)
{ 
  int mingfp=Datenbank.GradAnstieg.getGFP_for(Grad_anstieg::Grad_,hauptfenster->getAben());
  spinbutton_gfp->update();
  int gfp = spinbutton_gfp->get_value_as_int();
  gfp = ( gfp>mingfp) ? gfp : mingfp ;
  hauptfenster->getAben().setGFP(gfp); 
  return false;
}

void table_grundwerte::on_spinbutton_st_activate()
{ spinbutton_gs->grab_focus();}     
bool table_grundwerte::on_spinbutton_st_focus_out_event(GdkEventFocus *ev)
{ spinbutton_st->update();  hauptfenster->getAben().setSt(spinbutton_st->get_value_as_int()); zeige_werte();return false;}     

void table_grundwerte::on_spinbutton_gw_activate()
{ spinbutton_ko->grab_focus();}     
bool table_grundwerte::on_spinbutton_gw_focus_out_event(GdkEventFocus *ev)
{ spinbutton_gw->update();  hauptfenster->getAben().setGw(spinbutton_gw->get_value_as_int()); zeige_werte();return false;}     

void table_grundwerte::on_spinbutton_gs_activate()
{ spinbutton_gw->grab_focus();}     
bool table_grundwerte::on_spinbutton_gs_focus_out_event(GdkEventFocus *ev)
{ spinbutton_gs->update();  hauptfenster->getAben().setGs(spinbutton_gs->get_value_as_int()); zeige_werte();return false;}     

void table_grundwerte::on_spinbutton_ko_activate()
{ spinbutton_in->grab_focus();}     
bool table_grundwerte::on_spinbutton_ko_focus_out_event(GdkEventFocus *ev)
{ spinbutton_ko->update();  hauptfenster->getAben().setKo(spinbutton_ko->get_value_as_int()); zeige_werte();return false;}     

void table_grundwerte::on_spinbutton_in_activate()
{ spinbutton_zt->grab_focus();}     
bool table_grundwerte::on_spinbutton_in_focus_out_event(GdkEventFocus *ev)
{ spinbutton_in->update();  hauptfenster->getAben().setIn(spinbutton_in->get_value_as_int()); zeige_werte();return false;}     

void table_grundwerte::on_spinbutton_zt_activate()
{ spinbutton_au->grab_focus(); }     
bool table_grundwerte::on_spinbutton_zt_focus_out_event(GdkEventFocus *ev)
{  spinbutton_zt->update();  hauptfenster->getAben().setZt(spinbutton_zt->get_value_as_int());
   hauptfenster->getAben().setSinn("Sechster Sinn",hauptfenster->getAben().Zt()/25);   
   zeige_werte();
   return false;
}     

void table_grundwerte::on_spinbutton_sb_activate()
{ spinbutton_wk->grab_focus();}
bool table_grundwerte::on_spinbutton_sb_focus_out_event(GdkEventFocus *ev)
{ spinbutton_sb->update();  hauptfenster->getAben().setSb(spinbutton_sb->get_value_as_int()); return false;}

void table_grundwerte::on_spinbutton_wk_activate()
{ spinbutton_b->grab_focus();}
bool table_grundwerte::on_spinbutton_wk_focus_out_event(GdkEventFocus *ev)
{ spinbutton_wk->update();  hauptfenster->getAben().setWk(spinbutton_wk->get_value_as_int()); return false;}

void table_grundwerte::on_spinbutton_au_activate()
{ spinbutton_pa->grab_focus();}
bool table_grundwerte::on_spinbutton_au_focus_out_event(GdkEventFocus *ev)
{ spinbutton_au->update();  hauptfenster->getAben().setAu(spinbutton_au->get_value_as_int()); return false;}

void table_grundwerte::on_spinbutton_pa_activate()
{ spinbutton_sb->grab_focus();}   
bool table_grundwerte::on_spinbutton_pa_focus_out_event(GdkEventFocus *ev)
{ spinbutton_pa->update();  hauptfenster->getAben().setpA(spinbutton_pa->get_value_as_int()); return false;}   

void table_grundwerte::on_spinbutton_b_activate()
{ button_grda1setzen->grab_focus();} 
bool table_grundwerte::on_spinbutton_b_focus_out_event(GdkEventFocus *ev)
{ spinbutton_b->update();   hauptfenster->getAben().setB(spinbutton_b->get_value_as_int()); return false;} 

bool table_grundwerte::on_entry_nameC_focus_in_event(GdkEventFocus *ev)
{ entry_nameC->select_region(0,-1); return false;}
bool table_grundwerte::on_entry_nameS_focus_in_event(GdkEventFocus *ev)
{ entry_nameS->select_region(0,-1); return false;}
bool table_grundwerte::on_entry_version_focus_in_event(GdkEventFocus *ev)
{ entry_version->select_region(0,-1); return false;}
bool table_grundwerte::on_entry_bezeichnung_focus_in_event(GdkEventFocus *ev)
{ entry_bezeichnung->select_region(0,-1); return false;}
bool table_grundwerte::on_entry_merkmale_focus_in_event(GdkEventFocus *ev)
{ entry_merkmale->select_region(0,-1); return false;}
bool table_grundwerte::on_entry_spezialisierung_focus_in_event(GdkEventFocus *ev)
{ entry_spezialisierung->select_region(0,-1); return false;}
bool table_grundwerte::on_entry_glaube_focus_in_event(GdkEventFocus *ev)
{ entry_glaube->select_region(0,-1); return false;}
bool table_grundwerte::on_entry_herkunft_focus_in_event(GdkEventFocus *ev)
{ entry_herkunft->select_region(0,-1); return false;}
bool table_grundwerte::on_spinbutton_grad_focus_in_event(GdkEventFocus *ev)
{ spinbutton_grad->select_region(0,-1); return false;}
bool table_grundwerte::on_spinbutton_lp_focus_in_event(GdkEventFocus *ev)
{ spinbutton_lp->select_region(0,-1); return false;}
bool table_grundwerte::on_spinbutton_ap_focus_in_event(GdkEventFocus *ev)
{ spinbutton_ap->select_region(0,-1); return false;}
bool table_grundwerte::on_spinbutton_Cgewicht_focus_in_event(GdkEventFocus *ev)
{ spinbutton_Cgewicht->select_region(0,-1); return false;}
bool table_grundwerte::on_spinbutton_groesse_focus_in_event(GdkEventFocus *ev)
{ spinbutton_groesse->select_region(0,-1); return false;}
bool table_grundwerte::on_spinbutton_alter_focus_in_event(GdkEventFocus *ev)
{ spinbutton_alter->select_region(0,-1); return false;}
bool table_grundwerte::on_spinbutton_tage_focus_in_event(GdkEventFocus *ev)
{ spinbutton_tage->select_region(0,-1); return false;}
bool table_grundwerte::on_spinbutton_gg_focus_in_event(GdkEventFocus *ev)
{ spinbutton_gg->select_region(0,-1); return false;}
bool table_grundwerte::on_spinbutton_sg_focus_in_event(GdkEventFocus *ev)
{ spinbutton_sg->select_region(0,-1); return false;}
bool table_grundwerte::on_spinbutton_gfp_focus_in_event(GdkEventFocus *ev)
{ spinbutton_gfp->select_region(0,-1); return false;}
bool table_grundwerte::on_spinbutton_st_focus_in_event(GdkEventFocus *ev)
{ spinbutton_st->select_region(0,-1); return false;}     
bool table_grundwerte::on_spinbutton_gw_focus_in_event(GdkEventFocus *ev)
{ spinbutton_gw->select_region(0,-1); return false;}     
bool table_grundwerte::on_spinbutton_gs_focus_in_event(GdkEventFocus *ev)
{ spinbutton_gs->select_region(0,-1); return false;}     
bool table_grundwerte::on_spinbutton_ko_focus_in_event(GdkEventFocus *ev)
{ spinbutton_ko->select_region(0,-1); return false;}     
bool table_grundwerte::on_spinbutton_in_focus_in_event(GdkEventFocus *ev)
{ spinbutton_in->select_region(0,-1); return false;}     
bool table_grundwerte::on_spinbutton_zt_focus_in_event(GdkEventFocus *ev)
{ spinbutton_zt->select_region(0,-1); return false;}     
bool table_grundwerte::on_spinbutton_sb_focus_in_event(GdkEventFocus *ev)
{ spinbutton_sb->select_region(0,-1); return false;}
bool table_grundwerte::on_spinbutton_wk_focus_in_event(GdkEventFocus *ev)
{ spinbutton_wk->select_region(0,-1); return false;}
bool table_grundwerte::on_spinbutton_au_focus_in_event(GdkEventFocus *ev)
{ spinbutton_au->select_region(0,-1); return false;}
bool table_grundwerte::on_spinbutton_pa_focus_in_event(GdkEventFocus *ev)
{ spinbutton_pa->select_region(0,-1); return false;}   
bool table_grundwerte::on_spinbutton_b_focus_in_event(GdkEventFocus *ev)
{ spinbutton_b->select_region(0,-1); return false;} 


void table_grundwerte::on_combo_stand_activate()
{
 combo_hand->grab_focus();
}

bool table_grundwerte::on_combo_stand_focus_out_event(GdkEventFocus *ev)
{
  for(std::vector<std::string>::const_iterator i=Vstand.begin();i!=Vstand.end();++i)
   {
    if(*i==combo_stand->get_entry()->get_text())
      {  hauptfenster->getAben().setStand(*i);
         break;
      }
   }
  return false;
}
                
void table_grundwerte::on_combo_hand_activate()
{
 spinbutton_gfp->grab_focus();
}

bool table_grundwerte::on_combo_hand_focus_out_event(GdkEventFocus *ev)
{
  for(std::vector<std::string>::const_iterator i=Vhand.begin();i!=Vhand.end();++i)
   {
    if(*i==combo_hand->get_entry()->get_text())
     {
        hauptfenster->getAben().setHand(*i);
        break;
     }
   }
 return false;
}
                

void table_grundwerte::edit_sensitive(bool b)
{
  if(b)   button_grda1setzen->show();
  else    button_grda1setzen->hide();
  combo_typ->set_sensitive(oldtyp_bool);  
  combo_typ2->set_sensitive(oldtyp_bool);  
  entry_nameC->set_sensitive(b);
  entry_nameS->set_sensitive(b);
  entry_version->set_sensitive(b);
  entry_bezeichnung->set_sensitive(b);
  entry_merkmale->set_sensitive(b);
  entry_spezialisierung->set_sensitive(b);
  entry_glaube->set_sensitive(b);
  spinbutton_alter->set_sensitive(b);
  spinbutton_gfp->set_sensitive(b);
  spinbutton_tage->set_sensitive(b);
  spinbutton_gg->set_sensitive(b);
  spinbutton_sg->set_sensitive(b);
  combo_stand->set_sensitive(b);
  combo_hand->set_sensitive(b);
  spinbutton_groesse->set_sensitive(b);
  spinbutton_grad->set_sensitive(b);
  entry_herkunft->set_sensitive(b); 
  spinbutton_Cgewicht->set_sensitive(b);
  spinbutton_lp->set_sensitive(b);
  spinbutton_ap->set_sensitive(b);
  spinbutton_st->set_sensitive(b);
  spinbutton_gs->set_sensitive(b);
  spinbutton_gw->set_sensitive(b);
  spinbutton_ko->set_sensitive(b);
  spinbutton_in->set_sensitive(b);
  spinbutton_zt->set_sensitive(b);
  spinbutton_au->set_sensitive(b);
  spinbutton_pa->set_sensitive(b);
  spinbutton_sb->set_sensitive(b);
  spinbutton_wk->set_sensitive(b);
  spinbutton_b->set_sensitive(b);
}


void table_grundwerte::midgard_check_werte100()
{
   if(hauptfenster->getAben().getOptionen().HausregelCheck(Optionen::Werte100).active)
      return;      
   int st=hauptfenster->getAben().St();
   int gw=hauptfenster->getAben().Gw();
   int gs=hauptfenster->getAben().Gs();
   int ko=hauptfenster->getAben().Ko();
   int in=hauptfenster->getAben().In();
   int zt=hauptfenster->getAben().Zt();
   if (st>100) st=100;
   if (st<1)   st=1;  
   if (gw>100) gw=100;
   if (gw<1)   gw=1;  
   if (gs>100) gs=100;
   if (gs<1)   gs=1;  
   if (ko>100) ko=100;
   if (ko<1)   ko=1;  
   if (in>100) in=100;
   if (in<1)   in=1;  
   if (zt>100) zt=100;
   if (zt<1)   zt=1;  
   hauptfenster->getAben().setBasiswerte(st,gw,gs,ko,in,zt);


   int au=hauptfenster->getAben().Au();
   int pa=hauptfenster->getAben().pA();
   int sb=hauptfenster->getAben().Sb();
   int wk=hauptfenster->getAben().Wk();
   if (au>100) au=100;
   if (au<1)   au=1;  
   if (pa>100) pa=100;
   if (pa<1)   pa=1;  
   if (sb>100) sb=100;
   if (sb<1)   sb=1;  
   if (wk>100) wk=100;
   if (wk<1)   wk=1;  
   hauptfenster->getAben().setAbgeleitetewerte_small(au,pa,sb,wk);
}
 
