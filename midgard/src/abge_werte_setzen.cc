// $Id: abge_werte_setzen.cc,v 1.45 2002/02/21 10:23:30 thoma Exp $
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
  Werte.setGrad(1);
  Werte.setAu( constraint_aw(random,Werte.Spezies()->Au()) );
  Werte.setpA( random.integer(1,100)-30 + 3*(Werte.In()/10. + Werte.Au()/10.) );
  {
    int b = Werte.Spezies()->B_s();
    for (int i=0;i<Werte.Spezies()->B_f();++i) b+=random.integer(1,3);
    Werte.setB(b);
  }
  Werte.setWk(random.integer(1,100)-40 + 3*(Werte.In()/10. + Werte.Ko()/10.) );
  {
//  int sb = constraint_aw(random,Werte.Spezies()->Sb()) 
    int sb = random.integer(1,100) + 3*(Werte.In()/10. + Werte.Wk()/10.) - 30;
    // Boni für Selbstbeherrschung: Assassine, Beschwörer & Druide
    sb += Typ[0]->Sb() + Typ[1]->Sb();
    // Saddhu
    if (Typ[0]->Short() == "Sa") sb = 80+random.integer(1,20);
    Werte.setSb(sb);
  }

  ////////////////////////////////////////////////////////////////////////
  // Ausdauer
  {
    int bo_au_typ;  
    if      (Typ[0]->Ausdauer() == "k" || Typ[1]->Ausdauer() == "k" ) bo_au_typ = 4 ;
    else if (Typ[0]->Ausdauer() == "ak"|| Typ[1]->Ausdauer() == "ak" ) bo_au_typ = 3 ;
    else bo_au_typ = 2 ;
    int ap = random.integer(1,6)+Werte.bo_Au()+bo_au_typ + Werte.Grad()*Werte.Spezies()->AP_Grad() ;
    if (ap<4) ap=4;
    Werte.setAP(ap);
  }
  Werte.setLP(random.integer(1,6)+Werte.Ko()/10+4+Werte.Spezies()->LPBasis());

  /////////////////////////////////////////////////////////////////////////
  // Körper und Stand
  {
    int groesse = Werte.Spezies()->Groesse_s() + Werte.St()/10.;
    for (int i=0;i<Werte.Spezies()->Groesse_f();++i) 
       groesse += random.integer(1,Werte.Spezies()->Groesse_w()) ;
    if (Werte.Spezies()->Name()=="Mensch" && Werte.Geschlecht()=="w")
       groesse-=10;   
    Werte.setGroesse(groesse);
  }

  {
   int gewicht=0,ganz=0;
   if(Werte.Spezies()->Name()=="Mensch" || 
      Werte.Spezies()->Name()=="Elf" || 
      Werte.Spezies()->Name()=="Zwerg" )
    ganz=4;
   else ganz=3;
   for (int i=0;i<ganz;++i) gewicht+=random.integer(1,6) ;
   if (Werte.Spezies()->Name()=="Mensch" && Werte.Geschlecht()=="w")
    gewicht-=4;
   gewicht += Werte.St()/10. + Werte.Groesse();
   if(Werte.Spezies()->Name()=="Mensch")
       gewicht-=120;
    else if (Werte.Spezies()->Name()=="Elf")
       gewicht-=128;
    else if (Werte.Spezies()->Name()=="Halbling")
       gewicht -=87;
    else
       gewicht -=90;
   Werte.setGewicht(gewicht);
  }
  {
    int ihand=random.integer(1,20);
    std::string h;
    if(ihand<=15) h=Vhand[0];
    else if (16<=ihand && ihand<=19) h=Vhand[1];
    else h=Vhand[2];
    if (Werte.Spezies()->Name()=="Waldgnom" || 
        Werte.Spezies()->Name()=="Berggnom")
      h=Vhand[2];
    Werte.setHand(h);
  }
  {
    int istand=random.integer(1,100);
    int typstand = Typ[0]->Stand();

/*
>     int typstand = Typ[0]->Stand();   // Anscheinend für
> Doppelcharaktere
>     (typstand<Typ[1]->Stand()) ? typstand=Typ[1]->Stand() : istand +=
> typstand;
> // Falls der Standmodifikator von Typ0 < Typ1, wird typstand = Typ1,
> sonst wird Typ1 addiert. Ne.
> Besser: 
>     (typstand<Typ[1]->Stand()) ? istand+=Typ[1]->Stand() : istand +=
> typstand;
> 
*/

    (typstand<Typ[1]->Stand()) ? typstand=Typ[1]->Stand() : istand += typstand;
//std::cout << "typstand\t"<<typstand<<"\n";
    std::string stand;  
    if(Werte.Spezies()->Name()=="Mensch")
     {
       if (istand<=10) stand = Vstand[1];
       if (11<=istand&&istand<=50) stand =  Vstand[2];
       if (51<=istand&&istand<=90) stand =  Vstand[3];
       if (istand>=91) stand =  Vstand[4];;
     }
    else if(Werte.Spezies()->Name()=="Halbling" ||
            Werte.Spezies()->Name()=="Waldgnom" ||
            Werte.Spezies()->Name()=="Berggnom")
     {
       if (istand<=50) stand =  Vstand[2];
       if (51<=istand) stand =  Vstand[3];
     }
    else
     {
       if (            istand<=50) stand =  Vstand[2];
       if (51<=istand&&istand<=90) stand =  Vstand[3];
       if (istand>=91) stand =  Vstand[4];
     }
    Werte.setStand(stand);
   }
  Werte.setGrad1Werte(Typ);

  zeige_werte(Werte);
  button_herkunft->set_sensitive(true);
  button_beschreibung->set_sensitive(true);
//  frame_steigern->show();  
//  table_lernschema->set_sensetive(true);
  frame_lernschema->set_sensitive(true);
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
   Werte.setBasiswerte(st,gw,gs,ko,in,zt);

   int au=Werte.Au(),pa=Werte.pA(),sb=Werte.Sb(),wk=Werte.Wk();
   if (au>100) au=100;
   if (au<1)   au=1;
   if (pa>100) pa=100;
   if (pa<1)   pa=1;
   if (sb>100) sb=100;
   if (sb<1)   sb=1;
   if (wk>100) wk=100;
   if (wk<1)   wk=1;
   Werte.setAbgeleitetewerte_small(au,pa,sb,wk);
}
