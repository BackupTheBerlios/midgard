// $Id: grundwere_edit_setzen.cc,v 1.20 2002/01/21 08:45:00 thoma Exp $
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

void midgard_CG::on_togglebutton_edit_werte_toggled()
{
  if(togglebutton_edit_werte->get_active()) edit_sensitive(true);
  else edit_sensitive(false);
}

void midgard_CG::set_all_entrys()
{
  Werte.setNameC(entry_nameC->get_text());
  Werte.setNameS(entry_nameS->get_text());
  Werte.setVersion(entry_version->get_text());
  Werte.setSpezialisierung(entry_spezialisierung->get_text());
  Werte.setGlaube(entry_glaube->get_text());
  Werte.setHerkunft(entry_herkunft->get_text());

  gtk_spin_button_update(spinbutton_grad->gtkobj());  
  Werte.setGrad(spinbutton_grad->get_value_as_int());
  gtk_spin_button_update(spinbutton_lp->gtkobj());  
  Werte.setLP(spinbutton_lp->get_value_as_int());
  gtk_spin_button_update(spinbutton_ap->gtkobj());  
  Werte.setAP(spinbutton_ap->get_value_as_int());
  gtk_spin_button_update(spinbutton_Cgewicht->gtkobj());  
  Werte.setGewicht(spinbutton_Cgewicht->get_value_as_int());
  gtk_spin_button_update(spinbutton_groesse->gtkobj());  
  Werte.setGroesse(spinbutton_groesse->get_value_as_int());
  gtk_spin_button_update(spinbutton_alter->gtkobj());  
  Werte.setAlter(spinbutton_alter->get_value_as_int());
  gtk_spin_button_update(spinbutton_tage->gtkobj());  
  Werte.setSteigertage(spinbutton_tage->get_value_as_int());
  gtk_spin_button_update(spinbutton_gg->gtkobj());  
  Werte.setGG(spinbutton_gg->get_value_as_int());
  gtk_spin_button_update(spinbutton_sg->gtkobj());  
  Werte.setSG(spinbutton_sg->get_value_as_int());
  gtk_spin_button_update(spinbutton_gfp->gtkobj());  
  Werte.setGFP(spinbutton_gfp->get_value_as_int());


  gtk_spin_button_update(spinbutton_st->gtkobj());  
  Werte.setSt(spinbutton_st->get_value_as_int());
  gtk_spin_button_update(spinbutton_gw->gtkobj());  
  Werte.setGw(spinbutton_gw->get_value_as_int());
  gtk_spin_button_update(spinbutton_gs->gtkobj());  
  Werte.setGs(spinbutton_gs->get_value_as_int());
  gtk_spin_button_update(spinbutton_ko->gtkobj());  
  Werte.setKo(spinbutton_ko->get_value_as_int());
  gtk_spin_button_update(spinbutton_in->gtkobj());  
  Werte.setIn(spinbutton_in->get_value_as_int());
  gtk_spin_button_update(spinbutton_zt->gtkobj());  
  Werte.setZt(spinbutton_zt->get_value_as_int());

  gtk_spin_button_update(spinbutton_au->gtkobj());  
  Werte.setAu(spinbutton_au->get_value_as_int());
  gtk_spin_button_update(spinbutton_pa->gtkobj());  
  Werte.setpA(spinbutton_pa->get_value_as_int());
  gtk_spin_button_update(spinbutton_sb->gtkobj());  
  Werte.setSb(spinbutton_sb->get_value_as_int());
  gtk_spin_button_update(spinbutton_wk->gtkobj());  
  Werte.setWk(spinbutton_wk->get_value_as_int());
  gtk_spin_button_update(spinbutton_b->gtkobj());  
  Werte.setB(spinbutton_b->get_value_as_int());

  zeige_werte(Werte);
}

void midgard_CG::on_entry_nameC_activate()
{ set_all_entrys(); entry_nameS->grab_focus(); }
void midgard_CG::on_entry_nameS_activate()
{ set_all_entrys(); entry_version->grab_focus();}
void midgard_CG::on_entry_version_activate()
{ 
 OptionBool.version=false;
 menu_init();
 entry_herkunft->grab_focus();
 set_all_entrys(); 
}
void midgard_CG::on_entry_spezialisierung_activate()
{ set_all_entrys(); spinbutton_grad->grab_focus();}
void midgard_CG::on_entry_glaube_activate()
{ set_all_entrys(); entry_spezialisierung->grab_focus();}
void midgard_CG::on_entry_herkunft_activate()
{ set_all_entrys(); entry_glaube->grab_focus();}
void midgard_CG::on_spinbutton_grad_activate()
{ set_all_entrys(); spinbutton_lp->grab_focus();}
void midgard_CG::on_spinbutton_lp_activate()
{ set_all_entrys(); spinbutton_ap->grab_focus();}
void midgard_CG::on_spinbutton_ap_activate()
{ set_all_entrys(); spinbutton_alter->grab_focus();}
void midgard_CG::on_spinbutton_Cgewicht_activate()
{ set_all_entrys(); spinbutton_groesse->grab_focus();}
void midgard_CG::on_spinbutton_groesse_activate()
{ set_all_entrys(); spinbutton_tage->grab_focus();}
void midgard_CG::on_spinbutton_alter_activate()
{ set_all_entrys(); spinbutton_Cgewicht->grab_focus();}
void midgard_CG::on_spinbutton_tage_activate()
{ set_all_entrys(); spinbutton_gg->grab_focus();}
void midgard_CG::on_spinbutton_gg_activate()
{ set_all_entrys(); spinbutton_sg->grab_focus();}
void midgard_CG::on_spinbutton_sg_activate()
{ set_all_entrys(); spinbutton_gfp->grab_focus();}
void midgard_CG::on_spinbutton_gfp_activate()
{ set_all_entrys(); spinbutton_st->grab_focus();}
void midgard_CG::on_spinbutton_st_activate()
{ set_all_entrys(); spinbutton_gs->grab_focus();}     
void midgard_CG::on_spinbutton_gw_activate()
{ set_all_entrys(); spinbutton_ko->grab_focus();}     
void midgard_CG::on_spinbutton_gs_activate()
{ set_all_entrys(); spinbutton_gw->grab_focus();}     
void midgard_CG::on_spinbutton_ko_activate()
{ set_all_entrys(); spinbutton_in->grab_focus();}     
void midgard_CG::on_spinbutton_in_activate()
{ set_all_entrys(); spinbutton_zt->grab_focus();}     
void midgard_CG::on_spinbutton_zt_activate()
{ set_all_entrys(); spinbutton_au->grab_focus();}     
void midgard_CG::on_spinbutton_sb_activate()
{ set_all_entrys(); spinbutton_wk->grab_focus();}
void midgard_CG::on_spinbutton_wk_activate()
{ set_all_entrys(); spinbutton_b->grab_focus();}
void midgard_CG::on_spinbutton_au_activate()
{ set_all_entrys(); spinbutton_pa->grab_focus();}
void midgard_CG::on_spinbutton_pa_activate()
{ set_all_entrys(); spinbutton_sb->grab_focus();}   
void midgard_CG::on_spinbutton_b_activate()
{ set_all_entrys();} 

gint midgard_CG::on_entry_nameC_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_entry_nameS_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_entry_version_focus_out_event(GdkEventFocus *ev)
{ 
 OptionBool.version=false;
 menu_init();
 set_all_entrys(); 
  return false;
}
gint midgard_CG::on_entry_spezialisierung_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_entry_glaube_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_entry_herkunft_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_spinbutton_grad_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_spinbutton_lp_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_spinbutton_ap_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_spinbutton_Cgewicht_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_spinbutton_groesse_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_spinbutton_alter_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_spinbutton_tage_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_spinbutton_gg_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_spinbutton_sg_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_spinbutton_gfp_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_spinbutton_st_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}     
gint midgard_CG::on_spinbutton_gw_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}     
gint midgard_CG::on_spinbutton_gs_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}     
gint midgard_CG::on_spinbutton_ko_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}     
gint midgard_CG::on_spinbutton_in_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}     
gint midgard_CG::on_spinbutton_zt_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}     
gint midgard_CG::on_spinbutton_sb_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_spinbutton_wk_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_spinbutton_au_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}
gint midgard_CG::on_spinbutton_pa_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;}   
gint midgard_CG::on_spinbutton_b_focus_out_event(GdkEventFocus *ev)
{ set_all_entrys(); return false;} 




void midgard_CG::edit_sensitive(bool b)
{
  entry_nameC->set_sensitive(b);
  entry_nameS->set_sensitive(b);
  entry_version->set_sensitive(b);
  entry_spezialisierung->set_sensitive(b);
  entry_glaube->set_sensitive(b);
  spinbutton_alter->set_sensitive(b);
  spinbutton_gfp->set_sensitive(b);
  spinbutton_tage->set_sensitive(b);
  spinbutton_gg->set_sensitive(b);
  spinbutton_sg->set_sensitive(b);
  optionmenu_stand->set_sensitive(b);
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

