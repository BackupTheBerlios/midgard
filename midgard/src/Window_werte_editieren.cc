// $Id: Window_werte_editieren.cc,v 1.17 2001/06/12 09:31:06 thoma Exp $
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
   werte.st = atoi( st_ein->get_text().c_str());
   werte.ge = atoi( ge_ein->get_text().c_str());
   werte.ko = atoi( ko_ein->get_text().c_str());
   werte.in = atoi( in_ein->get_text().c_str());
   werte.zt = atoi( zt_ein->get_text().c_str());
   werte.au = atoi( au_ein->get_text().c_str());
   werte.pa = atoi( pa_ein->get_text().c_str());
   werte.sb = atoi( sb_ein->get_text().c_str());
   werte.rw = atoi( rw_ein->get_text().c_str());
   werte.hgw= atoi(hgw_ein->get_text().c_str());
   werte.b  = atoi(  b_ein->get_text().c_str());
   werte.lp = atoi( lp_ein->get_text().c_str());
   werte.ap = atoi( ap_ein->get_text().c_str());
   werte.bo_au = atoi (bo_au_ein->get_text().c_str());
   werte.bo_sc = atoi (bo_sc_ein->get_text().c_str());
   werte.bo_an = atoi (bo_an_ein->get_text().c_str());
   werte.bo_ab = atoi (bo_ab_ein->get_text().c_str());
   werte.bo_za = atoi (bo_za_ein->get_text().c_str());
   werte.bo_psy = atoi (bo_psy_ein->get_text().c_str());
   werte.bo_phs = atoi (bo_phs_ein->get_text().c_str());
   werte.bo_phk = atoi (bo_phk_ein->get_text().c_str());
   werte.bo_gi = atoi (bo_gi_ein->get_text().c_str());

 werte.abwehr_wert  =  atoi (abwehr_ein ->  get_text().c_str());
 werte.zaubern_wert =        zaubern_ein -> get_text().c_str();
 werte.psyZR_wert   =  atoi (psyZR_ein ->   get_text().c_str());
 werte.phsZR_wert   =  atoi (phsZR_ein ->   get_text().c_str());
 werte.phkZR_wert   =  atoi (phkZR_ein ->   get_text().c_str());
 werte.gift_wert    =  atoi (gift_ein ->    get_text().c_str());
 werte.gfp          = atoi (gfp_ein->get_text().c_str());

 werte.kaw = atoi (kaw_ein->get_text().c_str());   
 werte.wlw = atoi (wlw_ein->get_text().c_str());   
 werte.lpbasis  = atoi (lpbasis_ein-> get_text().c_str());          


   werte.alter = atoi( alter_ein->get_text().c_str());
   werte.gestalt = gestalt_ein->get_text();
   werte.gewicht = atoi( gewicht_ein->get_text().c_str());
   werte.groesse = atoi( groesse_ein->get_text().c_str());
   werte.grad = atoi( grad_ein->get_text().c_str());
   werte.spezialisierung = spezialisierung_ein->get_text();

   int istand = int(optionmenu_stand->get_menu()->get_active()->get_user_data());
   werte.stand=vstand[istand];

//   werte.stand = stand_ein->get_text();
   werte.herkunft = herkunft_ein->get_text();
   werte.glaube = glaube_ein->get_text();
   werte.name_charakter = name_charakter_ein->get_text();
   werte.name_spieler = name_spieler_ein->get_text();
   werte.version = version_ein->get_text();


   hauptfenster->get_Ausnahmen();
   hauptfenster->zeige_werte(werte, "alle");
   destroy();
}

Window_werte_editieren::Window_werte_editieren(midgard_CG* h,st_werte& w)
:werte(w)
{
 hauptfenster=h;
 vstand.resize(5);
 vstand[1]="Unfrei";
 vstand[2]="Volk";
 vstand[3]="Mittelschicht";
 vstand[4]="Adel";


 st_ein->set_value(werte.st);   
 ge_ein->set_value(werte.ge);   
 ko_ein->set_value(werte.ko);   
 in_ein->set_value(werte.in);   
 zt_ein->set_value(werte.zt);     
 au_ein->set_value(werte.au);     
 pa_ein->set_value(werte.pa);     
 sb_ein->set_value(werte.sb);     
 rw_ein->set_value(werte.rw);     
 hgw_ein->set_value(werte.hgw);   
 b_ein->set_value(werte.b);     
 lp_ein->set_value(werte.lp);   
 lpbasis_ein->set_value(werte.lpbasis);   
 kaw_ein->set_value(werte.kaw);   
 wlw_ein->set_value(werte.wlw);   
 ap_ein->set_value(werte.ap);          
 bo_au_ein->  set_value(werte.bo_au );
 bo_sc_ein->  set_value(werte.bo_sc );
 bo_an_ein->  set_value(werte.bo_an );
 bo_ab_ein->  set_value(werte.bo_ab );
 bo_za_ein->  set_value(werte.bo_za );
 bo_psy_ein-> set_value(werte.bo_psy); 
 bo_phs_ein-> set_value(werte.bo_phs); 
 bo_phk_ein-> set_value(werte.bo_phk); 
 bo_gi_ein->  set_value(werte.bo_gi); 
 abwehr_ein -> set_value(werte.abwehr_wert);
 zaubern_ein -> set_value(atoi(werte.zaubern_wert.c_str()));
 psyZR_ein -> set_value(werte.psyZR_wert);
 phsZR_ein -> set_value(werte.phsZR_wert);
 phkZR_ein -> set_value(werte.phkZR_wert);
 gift_ein -> set_value(werte.gift_wert);
 gfp_ein ->set_value(werte.gfp);
   
 alter_ein->set_value(werte.alter);   
 gestalt_ein->set_text(werte.gestalt);   
 gewicht_ein->set_value(werte.gewicht);   
 groesse_ein->set_value(werte.groesse);   
 grad_ein->set_value(werte.grad);   
 spezialisierung_ein->set_text(werte.spezialisierung);
// stand_ein->set_text(werte.stand);
 int inr=0;
 for (unsigned int i=0; i<vstand.size();++i)
   if (vstand[i]==werte.stand) inr=i;
 optionmenu_stand->set_history(inr);
 herkunft_ein->set_text(werte.herkunft);
 glaube_ein->set_text(werte.glaube);
 name_charakter_ein->set_text(werte.name_charakter);
 name_spieler_ein->set_text(werte.name_spieler);
 version_ein->set_text(werte.version);
}
