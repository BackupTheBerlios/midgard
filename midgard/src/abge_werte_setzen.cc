// $Id: abge_werte_setzen.cc,v 1.10 2001/05/21 06:48:23 thoma Exp $
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

void midgard_CG::on_abge_werte_setzen_clicked()
{
  Random random;
  werte.grad=1;
  //////////////////////////////////////////////////////////////////////
  // Übrige Werte würfeln //////////////////////////////////////////////
  // Aussehn
//  werte.au = random.integer(1,100);
  werte.au = constraint_aw(random,spezies_constraint.au);
  // pers. Ausstrahlung
  werte.pa = random.integer(1,100)-40 + werte.in/2. + werte.au/4. ;
  // Selbstbeherrschung
//  werte.sb = random.integer(1,100);
  werte.sb = constraint_aw(random,spezies_constraint.sb);

  // Reaktionswert
  werte.rw = random.integer(1,20)+10 + werte.ge/2. + werte.in/4.;
  // Handgemengewert
  werte.hgw = random.integer(1,20)+10+ werte.st/2. + werte.ge/4.;
  // Bewegungsweite
  werte.b = spezies_constraint.b_s;
  for (int i=0;i<spezies_constraint.b_f;++i) werte.b+=random.integer(1,3);
  //////////////////////////////////////////////////////////////////////
  // Boni 
  // Assassine, Beschwörer & Druide
  if (typ.sb == 20 || typ_2.sb ) werte.sb += random.integer(1,20); 
  // Spitzbube
  if (typ.sb == -20&& typ_2.sb == -20) werte.sb -= random.integer(1,20); 
//cout << typ.sb<<"\n";
  midgard_CG::grundwerte_boni_setzen();

  // Ausdauerbonus für Typen
  if      (typ.ausdauer == "k" || typ_2.ausdauer == "k" ) werte.bo_au_typ = 4 ;
  else if (typ.ausdauer == "ak"|| typ_2.ausdauer == "ak" ) werte.bo_au_typ = 3 ;
  else werte.bo_au_typ = 2 ;
//cout <<"werte.bo_au_typ\t"<<werte.bo_au_typ<<"\n";
  // Werte würfeln und setzen
  werte.lp = random.integer(1,6)+werte.lpbasis+spezies_constraint.lpbasis ;
  werte.ap = random.integer(1,6)+werte.bo_au+werte.bo_au_typ + werte.grad*spezies_constraint.ap_grad ;
  if (werte.ap<1) werte.ap=1;
  werte.abwehr_wert= 11 ;
  //Barde,Ordenskrieger,Zauberer
  if (typ.z == "j" || typ.z == "z" || typ_2.z == "j" || typ_2.z == "z" ) werte.zaubern_wert = "10" ;
   else werte.zaubern_wert="";
  werte.psyZR_wert = 10;
  werte.phsZR_wert = 10;
  werte.phkZR_wert = 10;
  werte.gift_wert = 3*werte.lp + spezies_constraint.gift ;
  // Körper und Stand
  werte.groesse = spezies_constraint.groesse_s + werte.st/10.;
  for (int i=0;i<spezies_constraint.groesse_f;++i) 
      werte.groesse += random.integer(1,spezies_constraint.groesse_w) ;
   
  int ges=random.integer(1,6) + spezies_constraint.gestalt;
  int gin=werte.groesse-100;
  if (werte.st >= 81) ges++;
  if (werte.st >= 96) ges++;
  if (ges<=2) 
   { werte.gestalt = "schlank";
     werte.gewicht = gin-(int)(gin*0.1) ; }
  if (ges>=3&&ges<=4) werte.gestalt = "normal";
  if (ges>=5) 
   { werte.gestalt = "breit";
     werte.gewicht =  gin+(int)(gin*0.2) ; }
  int istand=random.integer(1,100);
  int typstand = typ.stand;
  (typstand<typ_2.stand)?typstand=typ_2.stand:
  istand += typstand;
//cout << "typstand\t"<<typstand<<"\n";
  if (istand<=10) werte.stand = "Unfrei";
  if (11<=istand&&istand<=50) werte.stand = "Volk";
  if (51<=istand&&istand<=90) werte.stand = "Mittelschicht";
  if (istand>=91) werte.stand = "Adel";

  midgard_CG::zeige_werte(werte,"alle");
}


void midgard_CG::grundwerte_boni_setzen()
{
  werte.bo_au=0;
  werte.bo_sc=0;
  werte.bo_an=0;
  werte.bo_ab=0;
  werte.bo_za=0;
  werte.bo_psy=0;
  werte.bo_phs=0;
  werte.bo_phk=0;
  werte.bo_gi=0;
  // Stärke
  int ist=werte.st;
  if (ist<=10) { werte.bo_sc-=2; werte.bo_au-=1;werte.kaw=0;}
  if (11<=ist&&ist<=30) { werte.bo_sc-=1; werte.kaw=0;}
  if (31<=ist&&ist<=60) { werte.kaw=2;}
  if (61<=ist&&ist<=80) { werte.bo_sc+=1; werte.kaw=4;}
  if (81<=ist&&ist<=90) { werte.bo_sc+=2; werte.kaw=6;}
  if (91<=ist&&ist<=95) { werte.bo_sc+=2; werte.bo_au+=1;werte.kaw=8;}
  if (96<=ist&&ist<=99) { werte.bo_sc+=3; werte.bo_au+=2;werte.kaw=10;}
  if (ist>=100) { werte.bo_sc+=4; werte.bo_au+=3;werte.kaw=15;}
  // Geschicklichkeit
  ist=werte.ge;
  if (ist<=1) { werte.bo_sc-=2; werte.bo_an-=2; werte.bo_phk-=2;}
  if (2<=ist&&ist<=10) { werte.bo_sc-=1; werte.bo_an-=1; werte.bo_phk-=1;}
  if (11<=ist&&ist<=20) { werte.bo_sc-=1; }
  if (81<=ist&&ist<=90) { werte.bo_ab+=1;}
  if (91<=ist&&ist<=95) { werte.bo_sc+=1; werte.bo_ab+=1; werte.bo_phk+=1;}
  if (96<=ist&&ist<=99) { werte.bo_sc+=1; werte.bo_an+=1; werte.bo_ab+=2; werte.bo_phk+=2;}
  if (ist>=100) { werte.bo_sc+=2; werte.bo_an+=2; werte.bo_ab+=2; werte.bo_phk+=2;}
  // Konsitution
  ist=werte.ko;
  if (ist<=1) { werte.bo_au-=4; werte.lpbasis=5; werte.wlw=25; werte.bo_gi-=10; }
  if (2<=ist&&ist<=10) { werte.bo_au-=3; werte.lpbasis=6; werte.wlw=30; werte.bo_gi-=10; }
  if (11<=ist&&ist<=20) {werte.bo_au-=2; werte.lpbasis=7; werte.wlw=30; werte.bo_gi-=5; }
  if (21<=ist&&ist<=30) {werte.bo_au-=1; werte.lpbasis=8; werte.wlw=40; }
  if (31<=ist&&ist<=60) {werte.bo_au-=0; werte.lpbasis=9; werte.wlw=50; }
  if (61<=ist&&ist<=80) {werte.bo_au+=1; werte.lpbasis=10; werte.wlw=60; werte.bo_gi+=5; }
  if (81<=ist&&ist<=90) {werte.bo_au+=2; werte.lpbasis=11; werte.wlw=70; werte.bo_gi+=5; }
  if (91<=ist&&ist<=95) {werte.bo_au+=3; werte.lpbasis=12; werte.wlw=80; werte.bo_gi+=5; }
  if (96<=ist&&ist<=99) {werte.bo_au+=4; werte.lpbasis=13; werte.wlw=90; werte.bo_gi+=10; }
  if (ist>=100) { werte.bo_au+=5; werte.lpbasis=15; werte.wlw=95; werte.bo_gi+=15; }
  // Intelligenz
  ist=werte.in;
  if (ist<=10) { werte.bo_psy-=2;}
  if (11<=ist&&ist<=20) {werte.bo_psy-=1;}
  if (91<=ist&&ist<=95) {werte.bo_psy+=1;}
  if (96<=ist&&ist<=99) {werte.bo_psy+=2;}
  if (ist>=100) { werte.bo_psy+=3;}
  // Zaubertalent
  ist=werte.zt;
  int ibo_psy2=0;
  if (ist<=10) { werte.bo_za-=3; ibo_psy2-=2; werte.bo_phs-=2; }
  if (11<=ist&&ist<=20) {werte.bo_za-=2; ibo_psy2-=1; werte.bo_phs-=1; }
  if (21<=ist&&ist<=30) {werte.bo_za-=1; }
  if (61<=ist&&ist<=80) {werte.bo_za+=1; }
  if (81<=ist&&ist<=95) {werte.bo_za+=2; ibo_psy2+=1; werte.bo_phs+=1; }
  if (96<=ist&&ist<=99) {werte.bo_za+=3; ibo_psy2+=2; werte.bo_phs+=2; }
  if (ist>=100)         {werte.bo_za+=4; ibo_psy2+=3; werte.bo_phs+=3; }

  // Höhere Resistenz zählt + Resistenzen für Kämpfer|Zauberer
  (werte.bo_psy >= ibo_psy2) ? : werte.bo_psy=ibo_psy2 ;
  if (typ.z=="z" || typ_2.z=="z" ) 
      { werte.bo_phs+=3; werte.bo_psy+=3; werte.bo_phk+=3; }
  else
      { werte.bo_phs+=2; }

  // Speziesspezifische Boni
  if (werte.bo_ab <spezies_constraint.m_abb) werte.bo_ab =spezies_constraint.m_abb;
  if (werte.bo_psy<spezies_constraint.m_psy) werte.bo_psy=spezies_constraint.m_psy;
  if (werte.bo_phs<spezies_constraint.m_phs) werte.bo_phs=spezies_constraint.m_phs;
  if (werte.bo_phk<spezies_constraint.m_phk) werte.bo_phk=spezies_constraint.m_phk;

}