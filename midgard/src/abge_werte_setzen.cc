// $Id: abge_werte_setzen.cc,v 1.30 2001/12/10 17:11:05 thoma Exp $
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
  Werte.set_Sinn("Sechster Sinn",Werte.Zt()/25);

  Random random;
  int grad =1;
  //////////////////////////////////////////////////////////////////////
  // Übrige Werte würfeln //////////////////////////////////////////////
  // Aussehn
  int au = constraint_aw(random,Werte.Spezies()->Au());
  // pers. Ausstrahlung
  int pa = random.integer(1,100)-30 + 3*(Werte.In()/10. + Werte.Au()/10.) ;
  // Reaktionswert
  int rw=0;// = random.integer(1,20)+10 + Werte.Ge()/2. + Werte.In()/4.;
  // Handgemengewert
  int hgw=0;// = random.integer(1,20)+10+ Werte.St()/2. + Werte.Ge()/4.;
  // Bewegungsweite
  int b = Werte.Spezies()->B_s();
  for (int i=0;i<Werte.Spezies()->B_f();++i) b+=random.integer(1,3);

  // Willenskraft & Selbstbeherrschung
  int wk = random.integer(1,100)-40 + 3*(Werte.In()/10. + Werte.Ko()/10.) ;
//  int sb = constraint_aw(random,Werte.Spezies()->Sb()) 
  int sb = random.integer(1,100) + 3*(Werte.In()/10. + wk/10.) - 30;
  //////////////////////////////////////////////////////////////////////
  // Boni für Selbstbeherrschung
  // Assassine, Beschwörer & Druide
  sb += Typ[0]->Sb() + Typ[1]->Sb();
  // Saddhu
  if (Typ[0]->Short() == "Sa") sb = 80+random.integer(1,20);

  grundwerte_boni_setzen();
  ////////////////////////////////////////////////////////////////////////
  // Was mit den Boni zusammenhägt:
  // Raufen
  Werte.set_Raufen((Werte.St()+Werte.Gw())/20+Werte.bo_An() );
  if(Werte.Spezies()->Name()=="Zwerg") Werte.set_Raufen(Werte.Raufen()+1);  
  // Abwehr
  int abwehr_wert=11 ;
  // Zaubern:
  //Barde,Ordenskrieger,Zauberer
  int zaubern_wert=0;
  if (Typ[0]->Zaubern() == "j" || Typ[0]->Zaubern() == "z" || Typ[1]->Zaubern() == "j" || Typ[1]->Zaubern() == "z" ) 
     zaubern_wert = 10 ;
  else zaubern_wert = 2;
  
  int resistenz = 10;

  ////////////////////////////////////////////////////////////////////////
  // LP und AP
  int bo_au_typ;  
  // Ausdauerbonus für Typen
  if      (Typ[0]->Ausdauer() == "k" || Typ[1]->Ausdauer() == "k" ) bo_au_typ = 4 ;
  else if (Typ[0]->Ausdauer() == "ak"|| Typ[1]->Ausdauer() == "ak" ) bo_au_typ = 3 ;
  else bo_au_typ = 2 ;
  // Werte würfeln und setzen
  int lp = random.integer(1,6)+Werte.Ko()/10.+4+Werte.Spezies()->LPBasis() ;
  int ap = random.integer(1,6)+Werte.bo_Au()+bo_au_typ + Werte.Grad()*Werte.Spezies()->AP_Grad() ;
  if (ap<1) ap=1;

  /////////////////////////////////////////////////////////////////////////
  // Körper und Stand
  int groesse = Werte.Spezies()->Groesse_s() + Werte.St()/10.;
  for (int i=0;i<Werte.Spezies()->Groesse_f();++i) 
      groesse += random.integer(1,Werte.Spezies()->Groesse_w()) ;
  if (Werte.Spezies()->Name()=="Mensch" && Werte.Geschlecht()=="w")
    groesse-=10;   

  int ges=random.integer(1,6) + Werte.Spezies()->Gestalt();
  int gewicht=0,ganz=0;
  if(Werte.Spezies()->Name()=="Mensch" || Werte.Spezies()->Name()=="Elf" || Werte.Spezies()->Name()=="Zwerg")
      ganz=4;
  else ganz=3;
  for (int i=0;i<ganz;++i) gewicht+=random.integer(1,6) ;
  gewicht += Werte.St()/10. + groesse;
  if(Werte.Spezies()->Name()=="Mensch" || Werte.Spezies()->Name()=="Elf" || Werte.Spezies()->Name()=="Zwerg")
      gewicht-=120;
  else gewicht -=90;

  std::string gestalt;
  if (Werte.St() >= 81) ges++;
  if (Werte.St() >= 96) ges++;
  if (ges<=2) 
   { gestalt = "schlank";
     gewicht *= gewicht-(int)(gewicht*0.1) ; }
  if (ges>=3&&ges<=4) 
     gestalt = "normal";
  if (ges>=5) 
   { gestalt = "breit";
     gewicht =  gewicht+(int)(gewicht*0.1) ; }

  int ihand=random.integer(1,20);
  std::string shand;
  if(ihand<=15) shand="Rechtshänder";
  else if (16<=ihand && ihand<=19) shand="Linkshänder";
  else shand="Beidhändig";
  if (Werte.Spezies()->Name()=="Waldgnom" || Werte.Spezies()->Name()=="Berggnom")
      shand="Beidhändig";

  int istand=random.integer(1,100);
  int typstand = Typ[0]->Stand();
  (typstand<Typ[1]->Stand())?typstand=Typ[1]->Stand():
  istand += typstand;
//std::cout << "typstand\t"<<typstand<<"\n";
  std::string stand;  
  if (istand<=10) stand = "Unfrei";
  if (11<=istand&&istand<=50) stand = "Volk";
  if (51<=istand&&istand<=90) stand = "Mittelschicht";
  if (istand>=91) stand = "Adel";
  Werte.set_Abgeleitetewerte(au,pa,sb,wk,rw,hgw,b,lp,ap,abwehr_wert,zaubern_wert,
   resistenz,gestalt,shand,gewicht,groesse,grad,stand);

  if (Originalbool) original_midgard_check() ;
//  clear_Ausnahmen();
  zeige_werte(Werte);
  button_herkunft->set_sensitive(true);
  button_sprache->set_sensitive(true);
  button_beschreibung->set_sensitive(true);
//  frame_steigern->show();  
//  table_lernschema->set_sensetive(true);
  frame_lernschema->set_sensitive(true);
}


void midgard_CG::grundwerte_boni_setzen()
{
  int bo_au  = Werte.Ko()/10. + Werte.St()/20. - 7 ;
  int bo_sc  = Werte.St()/20. + Werte.Gs()/30. - 3 ;;

  //Angriff
  int bo_an  =0;
  int ist=Werte.Gs();
  if (1<=ist&&ist<=5) { bo_an-=2; }
  if (6<=ist&&ist<=20) { bo_an-=1; }
  if (81<=ist&&ist<=95) { bo_an+=1;}
  if (96<=ist) {bo_an+=2;}

  //Abwehr
  int bo_ab  =0;
  ist=Werte.Gw();
  if (1<=ist&&ist<=5) { bo_ab-=2;}
  if (6<=ist&&ist<=20) { bo_ab-=1; }
  if (81<=ist&&ist<=95) { bo_ab+=1;}
  if (96<=ist) { bo_ab+=2;}

  //Zaubern
  int bo_za  =0;
  ist=Werte.Zt();
  if (ist<=5)           {bo_za-=3; }
  if (6<=ist&&ist<=20)  {bo_za-=2; }
  if (21<=ist&&ist<=40) {bo_za-=1; }
  if (61<=ist&&ist<=80) {bo_za+=1; }
  if (81<=ist&&ist<=95) {bo_za+=2; }
  if (96<=ist&&ist<=99) {bo_za+=3; }
  if (ist>=100)         {bo_za+=4; }

  // Geistesmagie
  ist=Werte.Zt();
  int bo_psyZt =0;
  if (ist<=5)           {bo_psyZt-=2; }
  if (6<=ist&&ist<=20)  {bo_psyZt-=1; }
  if (81<=ist&&ist<=95) {bo_psyZt+=1; }
  if (96<=ist&&ist<=99) {bo_psyZt+=2; }
  if (ist>=100)         {bo_psyZt+=3; }
  ist=Werte.In();
  int bo_psyIn =0;
  if (ist<=5)           { bo_psyIn-=2; }
  if (6<=ist&&ist<=20)  { bo_psyIn-=1; }
  if (81<=ist&&ist<=95) { bo_psyIn+=1; }
  if (96<=ist)          { bo_psyIn+=2; }
  int bo_psy = (bo_psyZt>bo_psyIn) ? bo_psyZt : bo_psyIn ;
  if (Werte.Spezies()->Name()=="Elf" && Werte.Zt() <= 100 ) { bo_psy+=2;}
  if (Werte.Spezies()->Name()=="Elf" && Werte.Zt() >= 100 ) { bo_psy+=3;}
  if (Werte.Spezies()->Name()=="Berggnom") { bo_psy+=5;}
  if (Werte.Spezies()->Name()=="Waldgnom") { bo_psy+=5;}
  if (Werte.Spezies()->Name()=="Halbling") { bo_psy+=5;}
  if (Werte.Spezies()->Name()=="Zwerg")    { bo_psy+=4;}
  // Körpermagie
  ist=Werte.Zt();
  int bo_phsZt =0;
  if (ist<=5)           {bo_phsZt-=2; }
  if (6<=ist&&ist<=20)  {bo_phsZt-=1; }
  if (81<=ist&&ist<=95) {bo_phsZt+=1; }
  if (96<=ist&&ist<=99) {bo_phsZt+=2; }
  if (ist>=100)         {bo_phsZt+=3; }
  ist=Werte.Ko();
  int bo_phsKo =0;
  if (ist<=5)           { bo_phsKo-=2; }
  if (6<=ist&&ist<=20)  { bo_phsKo-=1; }
  if (81<=ist&&ist<=95) { bo_phsKo+=1; }
  if (96<=ist)          { bo_phsKo+=2; }
  int bo_phs = (bo_phsZt>bo_phsKo) ? bo_phsZt : bo_phsKo ;
  if (Werte.Spezies()->Name()=="Elf" && Werte.Zt() <= 100 ) { bo_phs+=2;}
  if (Werte.Spezies()->Name()=="Elf" && Werte.Zt() >= 100 ) { bo_phs+=3;}
  if (Werte.Spezies()->Name()=="Berggnom") { bo_phs+=5;}
  if (Werte.Spezies()->Name()=="Waldgnom") { bo_phs+=5;}
  if (Werte.Spezies()->Name()=="Halbling") { bo_phs+=5;}
  if (Werte.Spezies()->Name()=="Zwerg")    { bo_phs+=4;}
  // Umgebungsmagie
  ist=Werte.Gw();
  int bo_phk =0;
  if (ist<=5)           {bo_phk-=2; }
  if (6<=ist&&ist<=20)  {bo_phk-=1; }
  if (81<=ist&&ist<=95) {bo_phk+=1; }
  if (96<=ist)          {bo_phk+=2; }
  if (Werte.Spezies()->Name()=="Elf") { bo_phs+=2;}
  if (Werte.Spezies()->Name()=="Berggnom") { bo_phs+=5;}
  if (Werte.Spezies()->Name()=="Waldgnom") { bo_phs+=5;}
  if (Werte.Spezies()->Name()=="Halbling") { bo_phs+=5;}

/*
  // Speziesspezifische Boni
//  if (bo_ab <Werte.Spezies()->Abb()) bo_ab =Werte.Spezies()->Abb();
  if (bo_psy<Werte.Spezies()->Psy()) bo_psy=Werte.Spezies()->Psy();
  if (bo_phs<Werte.Spezies()->Phs()) bo_phs=Werte.Spezies()->Phs();
  if (bo_phk<Werte.Spezies()->Phk()) bo_phk=Werte.Spezies()->Phk();
*/

  // Grundlegende Resistenz
  if (Typ[0]->Zaubern()=="z" || Typ[1]->Zaubern()=="z" ) 
      { bo_phs+=3; bo_psy+=3; bo_phk+=3; }
  else
      { bo_phs+=2; }

  Werte.set_Abgeleitetewerte_Boni(bo_au,bo_sc,bo_an,bo_ab,bo_za,bo_psy,bo_phs,
   bo_phk);



/*
  int bo_gi  =0;
  int kaw;
  int wlw;
  int lpbasis;
*/



/*
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
*/
/*
  // Höhere Resistenz zählt + Resistenzen für Kämpfer|Zauberer
  (bo_psy >= ibo_psy2) ? : bo_psy=ibo_psy2 ;
  if (Typ[0]->Zaubern()=="z" || Typ[1]->Zaubern()=="z" ) 
      { bo_phs+=3; bo_psy+=3; bo_phk+=3; }
  else
      { bo_phs+=2; }
  // Speziesspezifische Boni
  if (bo_ab <Werte.Spezies()->Abb()) bo_ab =Werte.Spezies()->Abb();
  if (bo_psy<Werte.Spezies()->Psy()) bo_psy=Werte.Spezies()->Psy();
  if (bo_phs<Werte.Spezies()->Phs()) bo_phs=Werte.Spezies()->Phs();
  if (bo_phk<Werte.Spezies()->Phk()) bo_phk=Werte.Spezies()->Phk();
*/
//  Werte.set_Abgeleitetewerte_Boni(bo_au,bo_sc,bo_an,bo_ab,bo_za,bo_psy,bo_phs,
//   bo_phk,bo_gi,kaw,wlw,lpbasis);
}

void midgard_CG::original_midgard_check()
{
   int st=Werte.St(),gw=Werte.Gw(),gs=Werte.Gs(),ko=Werte.Ko(),in=Werte.In(),zt=Werte.Zt();
   if (st>100) st=100;
   if (st<1)  st=1;
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
   Werte.set_Basiswerte(st,gw,gs,ko,in,zt);

   int au=Werte.Au(),pa=Werte.pA(),sb=Werte.Sb(),wk=Werte.Wk(),rw=Werte.RW(),hgw=Werte.HGW();
   if (au>100) au=100;
   if (au<1)   au=1;
   if (pa>100) pa=100;
   if (pa<1)   pa=1;
   if (sb>100) sb=100;
   if (sb<1)   sb=1;
   if (wk>100) wk=100;
   if (wk<1)   wk=1;
   if (rw>100) rw=100;
   if (rw<1)   rw=1;
   if (hgw>100) hgw=100;
   if (hgw<1)   hgw=1;
   Werte.set_Abgeleitetewerte_small(au,pa,sb,wk,rw,hgw);
}
