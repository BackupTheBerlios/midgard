// $Id: zeige_werte.cc,v 1.15 2001/06/12 09:31:06 thoma Exp $
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

void midgard_CG::zeige_werte(const st_werte& w, const string& welche)
{
 werte=w; 
 if (welche == "grund" || welche == "alle")
   {
       st->set_text(itos(werte.st));
       ge->set_text(itos(werte.ge));
       ko->set_text(itos(werte.ko));
       in->set_text(itos(werte.in));
       zt->set_text(itos(werte.zt));
   }   
 if (welche == "abgel" || welche == "alle")
   {
       au->set_text(itos(werte.au));
       pa->set_text(itos(werte.pa));
       sb->set_text(itos(werte.sb));      
       rw->set_text(itos(werte.rw));    
       hgw->set_text(itos(werte.hgw)); 
       b->set_text(itos(werte.b));     
       lp->set_text(itos(werte.lp));      
       lpbasis->set_text(itos(werte.lpbasis));      
       ap->set_text(itos(werte.ap));   
       abwehr_wert->set_text(itos(werte.abwehr_wert));
       zaubern_wert->set_text(werte.zaubern_wert);
       kaw->set_text(itos(werte.kaw));
       wlw->set_text(itos(werte.wlw));
       psyZR_wert->set_text(itos(werte.psyZR_wert));
       phsZR_wert->set_text(itos(werte.phsZR_wert));
       phkZR_wert->set_text(itos(werte.phkZR_wert));
       gift_wert->set_text(itos(werte.gift_wert));
       bo_au->set_text(itos(werte.bo_au)) ;
       bo_sc->set_text(itos(werte.bo_sc)) ;
       bo_an->set_text(itos(werte.bo_an)) ;
       bo_ab->set_text(itos(werte.bo_ab)) ;
       bo_za->set_text(itos(werte.bo_za)) ;
       bo_psy->set_text(itos(werte.bo_psy)) ;
       bo_phs->set_text(itos(werte.bo_phs)) ;
       bo_phk->set_text(itos(werte.bo_phk)) ;
       bo_gi->set_text(itos(werte.bo_gi)) ;
       alter->set_text(itos(werte.alter));
       gestalt->set_text(werte.gestalt);  
       gewicht->set_text(itos(werte.gewicht));
       groesse->set_text(itos(werte.groesse));
       grad->set_text(itos(werte.grad));      
       spezialisierung->set_text(werte.spezialisierung);
       stand->set_text(werte.stand);
       herkunft->set_text(werte.herkunft);
       glaube->set_text(werte.glaube);
       name_charakter->set_text(werte.name_charakter);
       name_spieler->set_text(werte.name_spieler);
       gfp->set_text(itos(werte.gfp));
   }
}
