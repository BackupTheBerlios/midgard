// $Id: abge_werte_setzen.cc,v 1.24 2001/07/29 20:29:59 thoma Exp $
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
#include "zufall.h"

void midgard_CG::on_abge_werte_setzen_clicked()
{
  Random random;
  int grad =1;
  //////////////////////////////////////////////////////////////////////
  // Übrige Werte würfeln //////////////////////////////////////////////
  // Aussehn
  int au = constraint_aw(random,Spezies_constraint.Au());
  // pers. Ausstrahlung
  int pa = random.integer(1,100)-40 + Werte.In()/2. + Werte.Au()/4. ;
  // Reaktionswert
  int rw = random.integer(1,20)+10 + Werte.Ge()/2. + Werte.In()/4.;
  // Handgemengewert
  int hgw = random.integer(1,20)+10+ Werte.St()/2. + Werte.Ge()/4.;
  // Bewegungsweite
  int b = Spezies_constraint.B_s();
  for (int i=0;i<Spezies_constraint.B_f();++i) b+=random.integer(1,3);

  // Selbstbeherrschung
  int sb = constraint_aw(random,Spezies_constraint.Sb());

  //////////////////////////////////////////////////////////////////////
  // Boni 
  // Assassine, Beschwörer & Druide
  if (Typ.Sb() == 20 || Typ2.Sb() ) sb += random.integer(1,20); 
  // Spitzbube
  if (Typ.Sb() == -20&& Typ2.Sb() == -20) sb -= random.integer(1,20); 
  // Saddhu
  if (Typ.Short() == "Sa") sb = 80+random.integer(1,20);

  midgard_CG::grundwerte_boni_setzen();

  int bo_au_typ;  

  // Ausdauerbonus für Typen
  if      (Typ.Ausdauer() == "k" || Typ2.Ausdauer() == "k" ) bo_au_typ = 4 ;
  else if (Typ.Ausdauer() == "ak"|| Typ2.Ausdauer() == "ak" ) bo_au_typ = 3 ;
  else bo_au_typ = 2 ;
  
  // Werte würfeln und setzen
  int lp = random.integer(1,6)+Werte.LPBasis()+Spezies_constraint.LPBasis() ;
  int ap = random.integer(1,6)+Werte.bo_Au()+bo_au_typ + Werte.Grad()*Spezies_constraint.AP_Grad() ;
  if (ap<1) ap=1;

  int abwehr_wert= 11 ;
  //Barde,Ordenskrieger,Zauberer
  int zaubern_wert=0;
  if (Typ.Zaubern() == "j" || Typ.Zaubern() == "z" || Typ2.Zaubern() == "j" || Typ2.Zaubern() == "z" ) zaubern_wert = 10 ;

  int resistenz = 10;

  // Körper und Stand
  int groesse = Spezies_constraint.Groesse_s() + Werte.St()/10.;
  for (int i=0;i<Spezies_constraint.Groesse_f();++i) 
      groesse += random.integer(1,Spezies_constraint.Groesse_w()) ;

  int ges=random.integer(1,6) + Spezies_constraint.Gestalt();
  int gin=groesse-100;
  std::string gestalt;
  int gewicht=0;
  if (Werte.St() >= 81) ges++;
  if (Werte.St() >= 96) ges++;
  if (ges<=2) 
   { gestalt = "schlank";
     gewicht = gin-(int)(gin*0.1) ; }
  if (ges>=3&&ges<=4) 
   { gestalt = "normal";
     gewicht = gin; }
  if (ges>=5) 
   { gestalt = "breit";
     gewicht =  gin+(int)(gin*0.2) ; }
  int istand=random.integer(1,100);
  int typstand = Typ.Stand();
  (typstand<Typ2.Stand())?typstand=Typ2.Stand():
  istand += typstand;
//std::cout << "typstand\t"<<typstand<<"\n";
  std::string stand;  
  if (istand<=10) stand = "Unfrei";
  if (11<=istand&&istand<=50) stand = "Volk";
  if (51<=istand&&istand<=90) stand = "Mittelschicht";
  if (istand>=91) stand = "Adel";
  Werte.set_Abgeleitetewerte(au,pa,sb,rw,hgw,b,lp,ap,abwehr_wert,zaubern_wert,
   resistenz,gestalt,gewicht,groesse,grad,stand);

  if (Originalbool) original_midgard_check() ;
  clear_Ausnahmen();
  midgard_CG::zeige_werte(Werte);
  button_herkunft->set_sensitive(true);
  button_sprache->set_sensitive(true);
  button_beschreibung->set_sensitive(true);
//  frame_steigern->show();  
  frame_lernschema->show();
}


void midgard_CG::grundwerte_boni_setzen()
{
  int bo_au  =0;
  int bo_sc  =0;
  int bo_an  =0;
  int bo_ab  =0;
  int bo_za  =0;
  int bo_psy =0;
  int bo_phs =0;
  int bo_phk =0;
  int bo_gi  =0;
  int kaw;
  int wlw;
  int lpbasis;
  // Stärke
  int ist=Werte.St();
  if (ist<=10) { bo_sc-=2; bo_au-=1;kaw=0;}
  if (11<=ist&&ist<=30) { bo_sc-=1; kaw=0;}
  if (31<=ist&&ist<=60) { kaw=2;}
  if (61<=ist&&ist<=80) { bo_sc+=1; kaw=4;}
  if (81<=ist&&ist<=90) { bo_sc+=2; kaw=6;}
  if (91<=ist&&ist<=95) { bo_sc+=2; bo_au+=1;kaw=8;}
  if (96<=ist&&ist<=99) { bo_sc+=3; bo_au+=2;kaw=10;}
  if (ist>=100) { bo_sc+=4; bo_au+=3;kaw=15;}
  // Geschicklichkeit
  ist=Werte.Ge();
  if (ist<=1) { bo_sc-=2; bo_an-=2; bo_phk-=2;}
  if (2<=ist&&ist<=10) { bo_sc-=1; bo_an-=1; bo_phk-=1;}
  if (11<=ist&&ist<=20) { bo_sc-=1; }
  if (81<=ist&&ist<=90) { bo_ab+=1;}
  if (91<=ist&&ist<=95) { bo_sc+=1; bo_ab+=1; bo_phk+=1;}
  if (96<=ist&&ist<=99) { bo_sc+=1; bo_an+=1; bo_ab+=2; bo_phk+=2;}
  if (ist>=100) { bo_sc+=2; bo_an+=2; bo_ab+=2; bo_phk+=2;}
  // Konsitution
  ist=Werte.Ko();
  if (ist<=1) { bo_au-=4; lpbasis=5; wlw=25; bo_gi-=10; }
  if (2<=ist&&ist<=10) { bo_au-=3; lpbasis=6; wlw=30; bo_gi-=10; }
  if (11<=ist&&ist<=20) {bo_au-=2; lpbasis=7; wlw=30; bo_gi-=5; }
  if (21<=ist&&ist<=30) {bo_au-=1; lpbasis=8; wlw=40; }
  if (31<=ist&&ist<=60) {bo_au-=0; lpbasis=9; wlw=50; }
  if (61<=ist&&ist<=80) {bo_au+=1; lpbasis=10; wlw=60; bo_gi+=5; }
  if (81<=ist&&ist<=90) {bo_au+=2; lpbasis=11; wlw=70; bo_gi+=5; }
  if (91<=ist&&ist<=95) {bo_au+=3; lpbasis=12; wlw=80; bo_gi+=5; }
  if (96<=ist&&ist<=99) {bo_au+=4; lpbasis=13; wlw=90; bo_gi+=10; }
  if (ist>=100) { bo_au+=5; lpbasis=15; wlw=95; bo_gi+=15; }
  // Intelligenz
  ist=Werte.In();
  if (ist<=10) { bo_psy-=2;}
  if (11<=ist&&ist<=20) {bo_psy-=1;}
  if (91<=ist&&ist<=95) {bo_psy+=1;}
  if (96<=ist&&ist<=99) {bo_psy+=2;}
  if (ist>=100) { bo_psy+=3;}
  // Zaubertalent
  ist=Werte.Zt();
  int ibo_psy2=0;
  if (ist<=10) { bo_za-=3; ibo_psy2-=2; bo_phs-=2; }
  if (11<=ist&&ist<=20) {bo_za-=2; ibo_psy2-=1; bo_phs-=1; }
  if (21<=ist&&ist<=30) {bo_za-=1; }
  if (61<=ist&&ist<=80) {bo_za+=1; }
  if (81<=ist&&ist<=95) {bo_za+=2; ibo_psy2+=1; bo_phs+=1; }
  if (96<=ist&&ist<=99) {bo_za+=3; ibo_psy2+=2; bo_phs+=2; }
  if (ist>=100)         {bo_za+=4; ibo_psy2+=3; bo_phs+=3; }

  // Höhere Resistenz zählt + Resistenzen für Kämpfer|Zauberer
  (bo_psy >= ibo_psy2) ? : bo_psy=ibo_psy2 ;
  if (Typ.Zaubern()=="z" || Typ2.Zaubern()=="z" ) 
      { bo_phs+=3; bo_psy+=3; bo_phk+=3; }
  else
      { bo_phs+=2; }

  // Speziesspezifische Boni
  if (bo_ab <Spezies_constraint.m_Abb()) bo_ab =Spezies_constraint.m_Abb();
  if (bo_psy<Spezies_constraint.m_Psy()) bo_psy=Spezies_constraint.m_Psy();
  if (bo_phs<Spezies_constraint.m_Phs()) bo_phs=Spezies_constraint.m_Phs();
  if (bo_phk<Spezies_constraint.m_Phk()) bo_phk=Spezies_constraint.m_Phk();

  Werte.set_Abgeleitetewerte_Boni(bo_au,bo_sc,bo_an,bo_ab,bo_za,bo_psy,bo_phs,
   bo_phk,bo_gi,kaw,wlw,lpbasis);
}

void midgard_CG::original_midgard_check()
{
   int st=Werte.St(),ge=Werte.Ge(),ko=Werte.Ko(),in=Werte.In(),zt=Werte.Zt();
   if (st>100) st=100;
   if (st<1)  st=1;
   if (ge>100) ge=100;
   if (ge<1)   ge=1;
   if (ko>100) ko=100;
   if (ko<1)   ko=1;
   if (in>100) in=100;
   if (in<1)   in=1;
   if (zt>100) zt=100;
   if (zt<1)   zt=1;
   Werte.set_Basiswerte(st,ge,ko,in,zt);

   int au=Werte.Au(),pa=Werte.pA(),sb=Werte.Sb(),rw=Werte.RW(),hgw=Werte.HGW();
   if (au>100) au=100;
   if (au<1)   au=1;
   if (pa>100) pa=100;
   if (pa<1)   pa=1;
   if (sb>100) sb=100;
   if (sb<1)   sb=1;
   if (rw>100) rw=100;
   if (rw<1)   rw=1;
   if (hgw>100) hgw=100;
   if (hgw<1)   hgw=1;
   Werte.set_Abgeleitetewerte_small(au,pa,sb,rw,hgw);
}
