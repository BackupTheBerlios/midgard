// $Id: table_grundwerte_grundwere_edit.cc,v 1.4 2002/05/27 13:56:07 thoma Exp $
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

void table_grundwerte::on_togglebutton_edit_werte_toggled()
{
  if(togglebutton_edit_werte->get_active()) edit_sensitive(true);
  else 
    {
//     set_all_entrys(); // eigentlich überflüssig (wg. focus_leaf_event)
     edit_sensitive(false);
     fill_typauswahl();
    }
}

void table_grundwerte::on_button_grda1setzen_clicked()
{
  hauptfenster->getWerte().setGrad1Werte(hauptfenster->getCChar().getVTyp());
  zeige_werte();
}

void table_grundwerte::on_entry_nameC_activate()
{ 
  if(hauptfenster->wizard) 
   { 
     togglebutton_edit_werte->set_active(false);
     hauptfenster->wizard->next_step(Wizard::NAMEN);
   }
  else 
   {
     entry_nameS->grab_focus();
   }
}
gint table_grundwerte::on_entry_nameC_focus_out_event(GdkEventFocus *ev)
{ hauptfenster->getWerte().setNameC(entry_nameC->get_text());  return false; }

void table_grundwerte::on_entry_nameS_activate()
{ entry_version->grab_focus(); }
gint table_grundwerte::on_entry_nameS_focus_out_event(GdkEventFocus *ev)
{ hauptfenster->getWerte().setNameS(entry_nameS->get_text()); return false;}

void table_grundwerte::on_entry_version_activate()
{  entry_bezeichnung->grab_focus();}
gint table_grundwerte::on_entry_version_focus_out_event(GdkEventFocus *ev)
{  hauptfenster->getWerte().setVersion(entry_version->get_text()); return false;}

void table_grundwerte::on_entry_bezeichnung_activate()
{ entry_herkunft->grab_focus();}
gint table_grundwerte::on_entry_bezeichnung_focus_out_event(GdkEventFocus *ev)
{  hauptfenster->getWerte().setBezeichnung(entry_bezeichnung->get_text());return false;}

void table_grundwerte::on_entry_spezialisierung_activate()
{ entry_merkmale->grab_focus();}
gint table_grundwerte::on_entry_spezialisierung_focus_out_event(GdkEventFocus *ev)
{  hauptfenster->getWerte().setSpezialisierung(entry_spezialisierung->get_text());return false;}

void table_grundwerte::on_entry_merkmale_activate()
{ spinbutton_grad->grab_focus();}
gint table_grundwerte::on_entry_merkmale_focus_out_event(GdkEventFocus *ev)
{  hauptfenster->getWerte().setMerkmale(entry_merkmale->get_text());return false;}

void table_grundwerte::on_entry_glaube_activate()
{ entry_spezialisierung->grab_focus();}
gint table_grundwerte::on_entry_glaube_focus_out_event(GdkEventFocus *ev)
{  hauptfenster->getWerte().setGlaube(entry_glaube->get_text());return false;}

void table_grundwerte::on_entry_herkunft_activate()
{ entry_glaube->grab_focus();}
gint table_grundwerte::on_entry_herkunft_focus_out_event(GdkEventFocus *ev)
{  hauptfenster->getWerte().setHerkunft(cH_Land(entry_herkunft->get_text(),true)); return false;}



void table_grundwerte::on_spinbutton_grad_activate()
{ 
  spinbutton_lp->grab_focus();
}
gint table_grundwerte::on_spinbutton_grad_focus_out_event(GdkEventFocus *ev)
{  spinbutton_grad->update(); 
   hauptfenster->getWerte().setGrad(spinbutton_grad->get_value_as_int()); 
   hauptfenster->getWerte().set_Grad_Basiswerte(hauptfenster->getCWerte().Grad());
   int mingfp=hauptfenster->getDatabase().GradAnstieg.getGFP_for(Grad_anstieg::Grad_,hauptfenster->getCWerte());
   spinbutton_gfp->update();
   if (mingfp>spinbutton_gfp->get_value_as_int()) { hauptfenster->getWerte().setGFP(mingfp); }
   return false; 
}

void table_grundwerte::on_spinbutton_lp_activate()
{ spinbutton_ap->grab_focus();}
gint table_grundwerte::on_spinbutton_lp_focus_out_event(GdkEventFocus *ev)
{ spinbutton_lp->update();  hauptfenster->getWerte().setLP(spinbutton_lp->get_value_as_int()); return false;}

void table_grundwerte::on_spinbutton_ap_activate()
{ spinbutton_alter->grab_focus();}
gint table_grundwerte::on_spinbutton_ap_focus_out_event(GdkEventFocus *ev)
{  spinbutton_ap->update();  hauptfenster->getWerte().setAP(spinbutton_ap->get_value_as_int()); return false;}


void table_grundwerte::on_spinbutton_Cgewicht_activate()
{ spinbutton_groesse->grab_focus();}
gint table_grundwerte::on_spinbutton_Cgewicht_focus_out_event(GdkEventFocus *ev)
{ spinbutton_Cgewicht->update();  hauptfenster->getWerte().setGewicht(spinbutton_Cgewicht->get_value_as_int()); zeige_werte();return false;}

void table_grundwerte::on_spinbutton_groesse_activate()
{ spinbutton_tage->grab_focus();}
gint table_grundwerte::on_spinbutton_groesse_focus_out_event(GdkEventFocus *ev)
{ spinbutton_groesse->update();   hauptfenster->getWerte().setGroesse(spinbutton_groesse->get_value_as_int()); zeige_werte();return false;}

void table_grundwerte::on_spinbutton_alter_activate()
{ spinbutton_Cgewicht->grab_focus();}
gint table_grundwerte::on_spinbutton_alter_focus_out_event(GdkEventFocus *ev)
{ spinbutton_alter->update();  hauptfenster->getWerte().setAlter(spinbutton_alter->get_value_as_int()); return false;}

void table_grundwerte::on_spinbutton_tage_activate()
{ spinbutton_gg->grab_focus();}
gint table_grundwerte::on_spinbutton_tage_focus_out_event(GdkEventFocus *ev)
{ spinbutton_tage->update(); hauptfenster->getWerte().setSteigertage(spinbutton_tage->get_value_as_int()); return false;}

void table_grundwerte::on_spinbutton_gg_activate()
{ spinbutton_sg->grab_focus();}
gint table_grundwerte::on_spinbutton_gg_focus_out_event(GdkEventFocus *ev)
{ spinbutton_gg->update();  hauptfenster->getWerte().setGG(spinbutton_gg->get_value_as_int()); return false;}

void table_grundwerte::on_spinbutton_sg_activate()
{ spinbutton_gfp->grab_focus();}
gint table_grundwerte::on_spinbutton_sg_focus_out_event(GdkEventFocus *ev)
{ spinbutton_sg->update();  hauptfenster->getWerte().setSG(spinbutton_sg->get_value_as_int()); return false;}

void table_grundwerte::on_spinbutton_gfp_activate()
{ spinbutton_st->grab_focus();}
gint table_grundwerte::on_spinbutton_gfp_focus_out_event(GdkEventFocus *ev)
{ 
  int mingfp=hauptfenster->getDatabase().GradAnstieg.getGFP_for(Grad_anstieg::Grad_,hauptfenster->getWerte());
  spinbutton_gfp->update();
  int gfp = spinbutton_gfp->get_value_as_int();
  gfp = ( gfp>mingfp) ? gfp : mingfp ;
  hauptfenster->getWerte().setGFP(gfp); 
  return false;
}

void table_grundwerte::on_spinbutton_st_activate()
{ spinbutton_gs->grab_focus();}     
gint table_grundwerte::on_spinbutton_st_focus_out_event(GdkEventFocus *ev)
{ spinbutton_st->update();  hauptfenster->getWerte().setSt(spinbutton_st->get_value_as_int()); zeige_werte();return false;}     

void table_grundwerte::on_spinbutton_gw_activate()
{ spinbutton_ko->grab_focus();}     
gint table_grundwerte::on_spinbutton_gw_focus_out_event(GdkEventFocus *ev)
{ spinbutton_gw->update();  hauptfenster->getWerte().setGw(spinbutton_gw->get_value_as_int()); zeige_werte();return false;}     

void table_grundwerte::on_spinbutton_gs_activate()
{ spinbutton_gw->grab_focus();}     
gint table_grundwerte::on_spinbutton_gs_focus_out_event(GdkEventFocus *ev)
{ spinbutton_gs->update();  hauptfenster->getWerte().setGs(spinbutton_gs->get_value_as_int()); zeige_werte();return false;}     

void table_grundwerte::on_spinbutton_ko_activate()
{ spinbutton_in->grab_focus();}     
gint table_grundwerte::on_spinbutton_ko_focus_out_event(GdkEventFocus *ev)
{ spinbutton_ko->update();  hauptfenster->getWerte().setKo(spinbutton_ko->get_value_as_int()); zeige_werte();return false;}     

void table_grundwerte::on_spinbutton_in_activate()
{ spinbutton_zt->grab_focus();}     
gint table_grundwerte::on_spinbutton_in_focus_out_event(GdkEventFocus *ev)
{ spinbutton_in->update();  hauptfenster->getWerte().setIn(spinbutton_in->get_value_as_int()); zeige_werte();return false;}     

void table_grundwerte::on_spinbutton_zt_activate()
{ spinbutton_au->grab_focus(); }     
gint table_grundwerte::on_spinbutton_zt_focus_out_event(GdkEventFocus *ev)
{  spinbutton_zt->update();  hauptfenster->getWerte().setZt(spinbutton_zt->get_value_as_int());
   hauptfenster->getWerte().setSinn("Sechster Sinn",hauptfenster->getCWerte().Zt()/25);   
   zeige_werte();
   return false;
}     

void table_grundwerte::on_spinbutton_sb_activate()
{ spinbutton_wk->grab_focus();}
gint table_grundwerte::on_spinbutton_sb_focus_out_event(GdkEventFocus *ev)
{ spinbutton_sb->update();  hauptfenster->getWerte().setSb(spinbutton_sb->get_value_as_int()); return false;}

void table_grundwerte::on_spinbutton_wk_activate()
{ spinbutton_b->grab_focus();}
gint table_grundwerte::on_spinbutton_wk_focus_out_event(GdkEventFocus *ev)
{ spinbutton_wk->update();  hauptfenster->getWerte().setWk(spinbutton_wk->get_value_as_int()); return false;}

void table_grundwerte::on_spinbutton_au_activate()
{ spinbutton_pa->grab_focus();}
gint table_grundwerte::on_spinbutton_au_focus_out_event(GdkEventFocus *ev)
{ spinbutton_au->update();  hauptfenster->getWerte().setAu(spinbutton_au->get_value_as_int()); return false;}

void table_grundwerte::on_spinbutton_pa_activate()
{ spinbutton_sb->grab_focus();}   
gint table_grundwerte::on_spinbutton_pa_focus_out_event(GdkEventFocus *ev)
{ spinbutton_pa->update();  hauptfenster->getWerte().setpA(spinbutton_pa->get_value_as_int()); return false;}   

void table_grundwerte::on_spinbutton_b_activate()
{ button_grda1setzen->grab_focus();} 
gint table_grundwerte::on_spinbutton_b_focus_out_event(GdkEventFocus *ev)
{ spinbutton_b->update();   hauptfenster->getWerte().setB(spinbutton_b->get_value_as_int()); return false;} 

gint table_grundwerte::on_entry_nameC_focus_in_event(GdkEventFocus *ev)
{ entry_nameC->select_region(0,-1); return false;}
gint table_grundwerte::on_entry_nameS_focus_in_event(GdkEventFocus *ev)
{ entry_nameS->select_region(0,-1); return false;}
gint table_grundwerte::on_entry_version_focus_in_event(GdkEventFocus *ev)
{ entry_version->select_region(0,-1); return false;}
gint table_grundwerte::on_entry_bezeichnung_focus_in_event(GdkEventFocus *ev)
{ entry_bezeichnung->select_region(0,-1); return false;}
gint table_grundwerte::on_entry_merkmale_focus_in_event(GdkEventFocus *ev)
{ entry_merkmale->select_region(0,-1); return false;}
gint table_grundwerte::on_entry_spezialisierung_focus_in_event(GdkEventFocus *ev)
{ entry_spezialisierung->select_region(0,-1); return false;}
gint table_grundwerte::on_entry_glaube_focus_in_event(GdkEventFocus *ev)
{ entry_glaube->select_region(0,-1); return false;}
gint table_grundwerte::on_entry_herkunft_focus_in_event(GdkEventFocus *ev)
{ entry_herkunft->select_region(0,-1); return false;}
gint table_grundwerte::on_spinbutton_grad_focus_in_event(GdkEventFocus *ev)
{ spinbutton_grad->select_region(0,-1); return false;}
gint table_grundwerte::on_spinbutton_lp_focus_in_event(GdkEventFocus *ev)
{ spinbutton_lp->select_region(0,-1); return false;}
gint table_grundwerte::on_spinbutton_ap_focus_in_event(GdkEventFocus *ev)
{ spinbutton_ap->select_region(0,-1); return false;}
gint table_grundwerte::on_spinbutton_Cgewicht_focus_in_event(GdkEventFocus *ev)
{ spinbutton_Cgewicht->select_region(0,-1); return false;}
gint table_grundwerte::on_spinbutton_groesse_focus_in_event(GdkEventFocus *ev)
{ spinbutton_groesse->select_region(0,-1); return false;}
gint table_grundwerte::on_spinbutton_alter_focus_in_event(GdkEventFocus *ev)
{ spinbutton_alter->select_region(0,-1); return false;}
gint table_grundwerte::on_spinbutton_tage_focus_in_event(GdkEventFocus *ev)
{ spinbutton_tage->select_region(0,-1); return false;}
gint table_grundwerte::on_spinbutton_gg_focus_in_event(GdkEventFocus *ev)
{ spinbutton_gg->select_region(0,-1); return false;}
gint table_grundwerte::on_spinbutton_sg_focus_in_event(GdkEventFocus *ev)
{ spinbutton_sg->select_region(0,-1); return false;}
gint table_grundwerte::on_spinbutton_gfp_focus_in_event(GdkEventFocus *ev)
{ spinbutton_gfp->select_region(0,-1); return false;}
gint table_grundwerte::on_spinbutton_st_focus_in_event(GdkEventFocus *ev)
{ spinbutton_st->select_region(0,-1); return false;}     
gint table_grundwerte::on_spinbutton_gw_focus_in_event(GdkEventFocus *ev)
{ spinbutton_gw->select_region(0,-1); return false;}     
gint table_grundwerte::on_spinbutton_gs_focus_in_event(GdkEventFocus *ev)
{ spinbutton_gs->select_region(0,-1); return false;}     
gint table_grundwerte::on_spinbutton_ko_focus_in_event(GdkEventFocus *ev)
{ spinbutton_ko->select_region(0,-1); return false;}     
gint table_grundwerte::on_spinbutton_in_focus_in_event(GdkEventFocus *ev)
{ spinbutton_in->select_region(0,-1); return false;}     
gint table_grundwerte::on_spinbutton_zt_focus_in_event(GdkEventFocus *ev)
{ spinbutton_zt->select_region(0,-1); return false;}     
gint table_grundwerte::on_spinbutton_sb_focus_in_event(GdkEventFocus *ev)
{ spinbutton_sb->select_region(0,-1); return false;}
gint table_grundwerte::on_spinbutton_wk_focus_in_event(GdkEventFocus *ev)
{ spinbutton_wk->select_region(0,-1); return false;}
gint table_grundwerte::on_spinbutton_au_focus_in_event(GdkEventFocus *ev)
{ spinbutton_au->select_region(0,-1); return false;}
gint table_grundwerte::on_spinbutton_pa_focus_in_event(GdkEventFocus *ev)
{ spinbutton_pa->select_region(0,-1); return false;}   
gint table_grundwerte::on_spinbutton_b_focus_in_event(GdkEventFocus *ev)
{ spinbutton_b->select_region(0,-1); return false;} 


void table_grundwerte::on_combo_stand_activate()
{
 combo_hand->grab_focus();
}

gint table_grundwerte::on_combo_stand_focus_out_event(GdkEventFocus *ev)
{
  for(std::vector<std::string>::const_iterator i=Vstand.begin();i!=Vstand.end();++i)
   {
    if(*i==combo_stand->get_entry()->get_text())
      {  hauptfenster->getWerte().setStand(*i);
         break;
      }
   }
  return false;
}
                
void table_grundwerte::on_combo_hand_activate()
{
 spinbutton_gfp->grab_focus();
}

gint table_grundwerte::on_combo_hand_focus_out_event(GdkEventFocus *ev)
{
  for(std::vector<std::string>::const_iterator i=Vhand.begin();i!=Vhand.end();++i)
   {
    if(*i==combo_hand->get_entry()->get_text())
     {
        hauptfenster->getWerte().setHand(*i);
        break;
     }
   }
 return false;
}
                

void table_grundwerte::edit_sensitive(bool b)
{
  if(b)   button_grda1setzen->show();
  else    button_grda1setzen->hide();
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
//  optionmenu_stand->set_sensitive(b);
//  optionmenu_hand->set_sensitive(b);
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


void table_grundwerte::original_midgard_check()
{
   int st=hauptfenster->getCWerte().St();
   int gw=hauptfenster->getCWerte().Gw();
   int gs=hauptfenster->getCWerte().Gs();
   int ko=hauptfenster->getCWerte().Ko();
   int in=hauptfenster->getCWerte().In();
   int zt=hauptfenster->getCWerte().Zt();
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
   hauptfenster->getWerte().setBasiswerte(st,gw,gs,ko,in,zt);


   int au=hauptfenster->getCWerte().Au();
   int pa=hauptfenster->getCWerte().pA();
   int sb=hauptfenster->getCWerte().Sb();
   int wk=hauptfenster->getCWerte().Wk();
   if (au>100) au=100;
   if (au<1)   au=1;  
   if (pa>100) pa=100;
   if (pa<1)   pa=1;  
   if (sb>100) sb=100;
   if (sb<1)   sb=1;  
   if (wk>100) wk=100;
   if (wk<1)   wk=1;  
   hauptfenster->getWerte().setAbgeleitetewerte_small(au,pa,sb,wk);
}
 
