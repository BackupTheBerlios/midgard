// $Id: Window_werte_editieren.cc,v 1.24 2001/11/04 07:22:20 thoma Exp $
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

// generated 2001/2/7 8:11:20 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to window_werte_editieren.cc_glade

// This file is for your program, I won't touch it again!

#include "Window_werte_editieren.hh"
#include "midgard_CG.hh"

void Window_werte_editieren::on_nwe_close_clicked()
{   
   gtk_spin_button_update(alter_ein->gtkobj());
   gtk_spin_button_update(gewicht_ein->gtkobj());
   gtk_spin_button_update(groesse_ein->gtkobj());
   Werte.set_Basiswerte(atoi(st_ein->get_text().c_str()),
                        atoi( ge_ein->get_text().c_str()),
                        atoi( ko_ein->get_text().c_str()),
                        atoi( in_ein->get_text().c_str()),
                        atoi( zt_ein->get_text().c_str()));
   int istand = int(optionmenu_stand->get_menu()->get_active()->get_user_data());
   Werte.set_Abgeleitetewerte(atoi( au_ein->get_text().c_str()),
                              atoi( pa_ein->get_text().c_str()),
                              atoi( sb_ein->get_text().c_str()),
                              atoi( rw_ein->get_text().c_str()),
                              atoi(hgw_ein->get_text().c_str()),
                              atoi(  b_ein->get_text().c_str()),
                              atoi( lp_ein->get_text().c_str()),
                              atoi( ap_ein->get_text().c_str()),
                              atoi(abwehr_ein ->  get_text().c_str()),
                              atoi(zaubern_ein -> get_text().c_str()),
                              atoi (resistenz_ein ->   get_text().c_str()),
                              gestalt_ein->get_text(),
                              atoi( gewicht_ein->get_text().c_str()),
                              atoi( groesse_ein->get_text().c_str()),
                              atoi( grad_ein->get_text().c_str()),
                              vstand[istand]);
   Werte.set_Abgeleitetewerte_Boni(atoi (bo_au_ein->get_text().c_str()),
                              atoi (bo_sc_ein->get_text().c_str()),
                              atoi (bo_an_ein->get_text().c_str()),
                              atoi (bo_ab_ein->get_text().c_str()),
                              atoi (bo_za_ein->get_text().c_str()),
                              atoi (bo_psy_ein->get_text().c_str()),
                              atoi (bo_phs_ein->get_text().c_str()),
                              atoi (bo_phk_ein->get_text().c_str()),
                              atoi (bo_gi_ein->get_text().c_str()),
                              atoi (kaw_ein->get_text().c_str()),
                              atoi (wlw_ein->get_text().c_str()), 
                              atoi (lpbasis_ein-> get_text().c_str()));

   Werte.set_GFP(atoi (gfp_ein->get_text().c_str()));
   Werte.set_Alter(atoi( alter_ein->get_text().c_str()));
   Werte.set_Spezialisierung(spezialisierung_ein->get_text());
   Werte.set_Herkunft(cH_Land(herkunft_ein->get_text()));
   Werte.set_Glaube(glaube_ein->get_text());
   Werte.set_Namen(name_charakter_ein->get_text(),name_spieler_ein->get_text(),
               version_ein->get_text());

   hauptfenster->clear_Ausnahmen();
   hauptfenster->zeige_werte(Werte);
   destroy();
}

Window_werte_editieren::Window_werte_editieren(midgard_CG* h,Grundwerte& w)
:Werte(w)
{
 hauptfenster=h;
 vstand.resize(5);
 vstand[1]="Unfrei";
 vstand[2]="Volk";
 vstand[3]="Mittelschicht";
 vstand[4]="Adel";


 st_ein->set_value(Werte.St());   
 ge_ein->set_value(Werte.Ge());   
 ko_ein->set_value(Werte.Ko());   
 in_ein->set_value(Werte.In());   
 zt_ein->set_value(Werte.Zt());     
 au_ein->set_value(Werte.Au());     
 pa_ein->set_value(Werte.pA());     
 sb_ein->set_value(Werte.Sb());     
 rw_ein->set_value(Werte.RW());     
 hgw_ein->set_value(Werte.HGW());   
 b_ein->set_value(Werte.B());     
 lp_ein->set_value(Werte.LP());   
 lpbasis_ein->set_value(Werte.LPBasis());   
 kaw_ein->set_value(Werte.KAW());   
 wlw_ein->set_value(Werte.WLW());   
 ap_ein->set_value(Werte.AP());          
 bo_au_ein->  set_value(Werte.bo_Au ());
 bo_sc_ein->  set_value(Werte.bo_Sc ());
 bo_an_ein->  set_value(Werte.bo_An ());
 bo_ab_ein->  set_value(Werte.bo_Ab ());
 bo_za_ein->  set_value(Werte.bo_Za ());
 bo_psy_ein-> set_value(Werte.bo_Psy()); 
 bo_phs_ein-> set_value(Werte.bo_Phs()); 
 bo_phk_ein-> set_value(Werte.bo_Phk()); 
 bo_gi_ein->  set_value(Werte.bo_Gift()); 
 abwehr_ein -> set_value(Werte.Abwehr_wert());
 zaubern_ein -> set_value(Werte.Zaubern_wert());
 resistenz_ein -> set_value(Werte.Resistenz());
// gift_ein -> set_value(Werte.gift_wert());
 gfp_ein ->set_value(Werte.GFP());
   
 alter_ein->set_value(Werte.Alter());   
 gestalt_ein->set_text(Werte.Gestalt());   
 gewicht_ein->set_value(Werte.Gewicht());   
 groesse_ein->set_value(Werte.Groesse());   
 grad_ein->set_value(Werte.Grad());   
 spezialisierung_ein->set_text(Werte.Spezialisierung());
// stand_ein->set_text(Werte.Stand());
 int inr=0;
 for (unsigned int i=0; i<vstand.size();++i)
   if (vstand[i]==Werte.Stand()) inr=i;
 optionmenu_stand->set_history(inr);
 herkunft_ein->set_text(Werte.Herkunft()->Name());
 glaube_ein->set_text(Werte.Glaube());
 name_charakter_ein->set_text(Werte.Name_Charakter());
 name_spieler_ein->set_text(Werte.Name_Spieler());
 version_ein->set_text(Werte.Version());
}

void Window_werte_editieren::st_activate()
{   
 ge_ein->grab_focus();
}

void Window_werte_editieren::ge_activate()
{   
 ko_ein->grab_focus();
}

void Window_werte_editieren::ko_activate()
{   
 in_ein->grab_focus();
}

void Window_werte_editieren::in_activate()
{   
 zt_ein->grab_focus();
}

void Window_werte_editieren::zt_activate()
{   
 au_ein->grab_focus();
}
void Window_werte_editieren::bzt_activate()
{   
 bo_psy_ein->grab_focus();
}

void Window_werte_editieren::au_activate()
{   
 pa_ein->grab_focus();
}

void Window_werte_editieren::pa_activate()
{   
 sb_ein->grab_focus();
}

void Window_werte_editieren::sb_activate()
{   
 rw_ein->grab_focus();
}

void Window_werte_editieren::rw_activate()
{   
 hgw_ein->grab_focus();
}

void Window_werte_editieren::hgw_activate()
{   
 b_ein->grab_focus();
}

void Window_werte_editieren::b_activate()
{   
 lp_ein->grab_focus();
}

void Window_werte_editieren::lp_activate()
{   
 ap_ein->grab_focus();
}

void Window_werte_editieren::ap_activate()
{   
 bo_au_ein->grab_focus();
}

void Window_werte_editieren::bau_activate()
{   
 bo_sc_ein->grab_focus();
}

void Window_werte_editieren::grad_activate()
{   
 st_ein->grab_focus();
}

void Window_werte_editieren::alter_activate()
{   
 gewicht_ein->grab_focus();
}

void Window_werte_editieren::gewicht_activate()
{   
 groesse_ein->grab_focus();
}

void Window_werte_editieren::groesse_activate()
{   
 gestalt_ein->grab_focus();
}

void Window_werte_editieren::gestalt_activate()
{   
 spezialisierung_ein->grab_focus();
}

void Window_werte_editieren::spezial_activate()
{   
 herkunft_ein->grab_focus();
}

void Window_werte_editieren::her_activate()
{   
 glaube_ein->grab_focus();
}

void Window_werte_editieren::glau_activate()
{   
 name_charakter_ein->grab_focus();
}

void Window_werte_editieren::ns_activate()
{   
 version_ein->grab_focus();
}

void Window_werte_editieren::nc_activate()
{   
 name_spieler_ein->grab_focus();
}

void Window_werte_editieren::sc_activate()
{   
 bo_an_ein->grab_focus();
}

void Window_werte_editieren::an_activate()
{   
 bo_ab_ein->grab_focus();
}

void Window_werte_editieren::ab_activate()
{   
 bo_za_ein->grab_focus();
}

void Window_werte_editieren::psy_activate()
{   
 bo_phs_ein->grab_focus();
}

void Window_werte_editieren::phs_activate()
{   
 bo_phk_ein->grab_focus();
}

void Window_werte_editieren::phk_activate()
{   
 bo_gi_ein->grab_focus();
}

void Window_werte_editieren::gift_activate()
{   
 kaw_ein->grab_focus();
}
/*
void Window_werte_editieren::wgift_activate()
{   
 gfp_ein->grab_focus();
}
*/
void Window_werte_editieren::lpb_activate()
{   
 abwehr_ein->grab_focus();
}

void Window_werte_editieren::kaw_activate()
{   
 wlw_ein->grab_focus();
}

void Window_werte_editieren::re_activate()
{   
 gfp_ein->grab_focus();
}

void Window_werte_editieren::wza_activate()
{   
 resistenz_ein->grab_focus();
}

void Window_werte_editieren::wab_activate()
{   
 zaubern_ein->grab_focus();
}

void Window_werte_editieren::gfp_activate()
{   
 alter_ein->grab_focus();
}

void Window_werte_editieren::vers_activate()
{   
 on_nwe_close_clicked();
}

void Window_werte_editieren::wlw_activate()
{   
 lpbasis_ein->grab_focus();
}
