// $Id: grundwerte_abge_werte.cc,v 1.3 2003/07/25 07:29:50 christof Exp $
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

#include "Grundwerte.hh"
#include <Misc/Trace.h>
#include "Abenteurer.hh"
#include "zufall.h"

static const UniqueValue::value_t trace_channel=ManuProC::Tracer::channels.get();
static ManuProC::Tracer::Environment trace_channel_e("DEBUG_GRUNDWERTE",trace_channel);

std::vector<std::string> Grundwerte::Vstand, Grundwerte::Vhand;

namespace { struct Foo { Foo() {
  Grundwerte::Vhand.resize(3);
  Grundwerte::Vhand[0]="Rechtshänder";
  Grundwerte::Vhand[1]="Linkshänder"; 
  Grundwerte::Vhand[2]="Beidhändig";  

  Grundwerte::Vstand.resize(5);
  Grundwerte::Vstand[1]="Unfrei";
  Grundwerte::Vstand[2]="Volk";  
  Grundwerte::Vstand[3]="Mittelschicht";
  Grundwerte::Vstand[4]="Adel";
}};}
static Foo foo;
	

// Typ sollte besser in Grundwerte
void Grundwerte::abge_werte_setzen(const Abenteurer &A)
{ ManuProC::Trace _t(trace_channel,__FUNCTION__);
  setGrad(1);
  { //Bewegungsweite
    int b = Spezies()->B_Bonus();
    for (int i=0;i<Spezies()->B_Wanz();++i) b+=Random::W3();
    setB(b);
  }
  setWk(Random::W100()-40 + 3*(In()/10 + Ko()/10) );
  {
    int sb = Random::W100() + 3*(In()/10 + Wk()/10) - 30;
    // Boni für Selbstbeherrschung: Assassine, Beschwörer & Druide
    sb += A.Typ1()->Sb() + A.Typ2()->Sb();
    // Saddhu
    if (A.Typ1()->Short() == "Sa") sb = 80+Random::W20();
    setSb(sb);
  }

  ////////////////////////////////////////////////////////////////////////
  // Ausdauer
  {
    int bo_au_typ;  
    if      (A.Typ1()->Ausdauer() == "k" || A.Typ2()->Ausdauer() == "k" ) bo_au_typ = 4 ;
    else if (A.Typ1()->Ausdauer() == "ak"|| A.Typ2()->Ausdauer() == "ak" ) bo_au_typ = 3 ;
    else bo_au_typ = 2 ;
    int ap = Random::W6() + bo_Au() + bo_au_typ + Spezies()->AP_Bonus();
    if (ap<4) ap=4;
    setAP(ap);
  }
  setLP(Random::W6() + Ko()/10 + 4 + Spezies()->LP_Bonus());

  /////////////////////////////////////////////////////////////////////////
  // Körper und Stand
  {
    int groesse = Spezies()->Groesse_Bonus() +  St()/10 ;
    for (int i=0;i<Spezies()->Groesse_Wanz();++i) 
       groesse += Random::integer(1,Spezies()->Groesse_Wuerfel()) ;
    if (Spezies()->Name()=="Mensch" && Geschlecht()==Enums::Frau)
       groesse-=10;   
    setGroesse(groesse);
  }
  {
    int gewicht = Spezies()->Gewicht_Bonus() + St()/10 + Groesse();
    for (int i=0;i<Spezies()->Gewicht_Wanz();++i) 
       gewicht += Random::W6() ;
    if (Spezies()->Name()=="Mensch" && Geschlecht()==Enums::Frau)
       gewicht-=4;   
    setGewicht(gewicht);
  }

  {
    int ihand=Random::W20()+Spezies()->HandBonus();
    std::string h;
    if(ihand<=15) h=Vhand[0];
    else if (16<=ihand && ihand<=19) h=Vhand[1];
    else h=Vhand[2];
    setHand(h);
  }
  {
    int istand=Random::W100();
    int typstand1 = A.Typ1()->Stand();
    int typstand2 = A.Typ2()->Stand();
    if(typstand1*typstand2 <= 0 ) istand += typstand1 + typstand2 ;
    else  // gleiches Vorzeichen
     { int t= (abs(typstand1)>abs(typstand2)) ? abs(typstand1) : abs(typstand2);
       if (typstand1<0) t*=-1;
       istand += t;
     }
//std::cout << "typstand\t"<<typstand<<"\n";
    std::string stand;  
    if(Spezies()->Name()=="Mensch")
     {
       if (istand<=10) stand = Vstand[1];
       if (11<=istand&&istand<=50) stand =  Vstand[2];
       if (51<=istand&&istand<=90) stand =  Vstand[3];
       if (istand>=91) stand =  Vstand[4];
       if (A.Typ1()->Short()=="MMa") stand =  Vstand[3];
     }
    else if(Spezies()->Name()=="Halbling" ||
            Spezies()->Name()=="Waldgnom" ||
            Spezies()->Name()=="Berggnom")
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
    setStand(stand);
   }
  setGrad1Werte(A.getVTyp());
}
