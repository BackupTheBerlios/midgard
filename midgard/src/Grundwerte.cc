// $Id: Grundwerte.cc,v 1.12 2002/02/21 21:56:26 thoma Exp $               
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
#include <Aux/itos.h>

int Grundwerte::bo_Au() const 
{ 
  return  int(Ko()/10. + St()/20.) - 7 ;
}

int Grundwerte::bo_Sc() const 
{ 
  return  int(St()/20. + Gs()/30.) - 3 ;
}

int Grundwerte::Raufen() const 
{ 
  int r = (St()+Gw())/20 +bo_An() ;
  if( Spezies()->Name()=="Zwerg") 
    return r+1;
  else 
    return r;
}

std::string Grundwerte::Gestalt() const 
{ 
  int g2=Groesse()-Gewicht();
  if(g2<=0) return "breit";
  double ge=100./g2;
  if(ge>1.1)      return "breit";
  else if(ge<0.9) return "schlank";
  else            return "normal";
}


int Grundwerte::bo_An() const 
{ 
  int bo_an = 0;
  if (1<=Gs()  &&Gs() <=5)  { bo_an-=2; }
  else if (6<=Gs()  &&Gs() <=20) { bo_an-=1; }
  else if (81<=Gs() &&Gs() <=95) { bo_an+=1; }
  else if (96<=Gs())             { bo_an+=2; }
  return bo_an;
}

int Grundwerte::bo_Ab() const 
{ 
  int bo_ab = 0;
  if (1<=Gw()  &&Gw() <=5)  { bo_ab-=2; }
  else if (6<=Gw()  &&Gw() <=20) { bo_ab-=1; }
  else if (81<=Gw() &&Gw() <=95) { bo_ab+=1; }
  else if (96<=Gw())             { bo_ab+=2; }
  return bo_ab;
}

int Grundwerte::bo_Za() const 
{ 
  int bo_za  =0;
  if (Zt()<=5)              {bo_za-=3; }
  else if (6<=Zt()  && Zt()<=20) {bo_za-=2; }
  else if (21<=Zt() && Zt()<=40) {bo_za-=1; }
  else if (61<=Zt() && Zt()<=80) {bo_za+=1; }
  else if (81<=Zt() && Zt()<=95) {bo_za+=2; }
  else if (96<=Zt() && Zt()<=99) {bo_za+=3; }
  else if (Zt()>=100)            {bo_za+=4; }
  return bo_za;
}

int Grundwerte::bo_Psy(const vector<cH_Typen>& Typ) const
{
  int bo_psyZt =0;
  if (Zt()<=5)              {bo_psyZt-=2; }
  else if (6<=Zt()  && Zt()<=20) {bo_psyZt-=1; }
  else if (81<=Zt() && Zt()<=95) {bo_psyZt+=1; }
  else if (96<=Zt() && Zt()<=99) {bo_psyZt+=2; }
  else if (Zt()>=100)            {bo_psyZt+=3; }

  int bo_psyIn =0;
  if (In()<=5)              { bo_psyIn-=2; }
  else if (6<=In()  && In()<=20) { bo_psyIn-=1; }
  else if (81<=In() && In()<=95) { bo_psyIn+=1; }
  else if (96<=In())             { bo_psyIn+=2; }

  int bo_psy;  
  // Vorzeichen unterschiedlich:
  if( bo_psyIn*bo_psyZt<=0) bo_psy = bo_psyIn+bo_psyZt;
  else 
   {
     // H�heren Wert nehmen:
     bo_psy = (abs(bo_psyZt)>abs(bo_psyIn))?abs(bo_psyZt):abs(bo_psyIn);
     // Vorzeichen setzen:
     if(bo_psyZt<0) bo_psy*=-1;
   }
  if (Spezies()->Name()=="Elf" && Zt() < 100 ) { bo_psy=2;}
  else if (Spezies()->Name()=="Elf" && Zt() >= 100 ) { bo_psy=3;}

  if (Spezies()->Name()=="Berggnom") { bo_psy=5;}
  else if (Spezies()->Name()=="Waldgnom") { bo_psy=5;}
  else if (Spezies()->Name()=="Halbling") { bo_psy=5;}
  else if (Spezies()->Name()=="Zwerg")    { bo_psy=4;}

  if (Typ[0]->Zaubern()=="z" || Typ[1]->Zaubern()=="z" )
    bo_psy+=3;

  return bo_psy;
}

int Grundwerte::bo_Phs(const vector<cH_Typen>& Typ) const
{
  int bo_phsZt =0;
  if (Zt()<=5)              {bo_phsZt-=2; }
  else if (6<=Zt()  && Zt()<=20) {bo_phsZt-=1; }
  else if (81<=Zt() && Zt()<=95) {bo_phsZt+=1; }
  else if (96<=Zt() && Zt()<=99) {bo_phsZt+=2; }
  else if (Zt()>=100)            {bo_phsZt+=3; }

  int bo_phsKo =0;
  if (Ko()<=5)            { bo_phsKo-=2; }
  else if (6<=Ko()&&Ko()<=20)  { bo_phsKo-=1; }
  else if (81<=Ko()&&Ko()<=95) { bo_phsKo+=1; }
  else if (96<=Ko())           { bo_phsKo+=2; }

  // Vorzeichen unterschiedlich:
  int bo_phs;
  if( bo_phsKo*bo_phsZt<=0) bo_phs = bo_phsKo+bo_phsZt;
  else 
   {
     // H�heren Wert nehmen:
     bo_phs = (abs(bo_phsZt)>abs(bo_phsKo))?abs(bo_phsZt):abs(bo_phsKo);
     // Vorzeichen setzen:
     if(bo_phsZt<0) bo_phs*=-1;
   }

  if (Spezies()->Name()=="Elf" && Zt() < 100 ) { bo_phs=2;}
  else if (Spezies()->Name()=="Elf" && Zt() >= 100 ) { bo_phs=3;}
  if (Spezies()->Name()=="Berggnom") { bo_phs=5;}
  else if (Spezies()->Name()=="Waldgnom") { bo_phs=5;}
  else if (Spezies()->Name()=="Halbling") { bo_phs=5;}
  else if (Spezies()->Name()=="Zwerg")    { bo_phs=4;}

  if (Typ[0]->Zaubern()=="z" || Typ[1]->Zaubern()=="z" )
    bo_phs+=3;
  else bo_phs+=2;
  return bo_phs;
}

int Grundwerte::bo_Phk(const vector<cH_Typen>& Typ) const
{
  int bo_phk =0;   
  if (Gw()<=5)              {bo_phk-=2; }
  else if (6<=Gw()  && Gw()<=20) {bo_phk-=1; }
  else if (81<=Gw() && Gw()<=95) {bo_phk+=1; }
  else if (96<=Gw())             {bo_phk+=2; }
  if (Spezies()->Name()=="Elf")      { bo_phk=2;}
  else if (Spezies()->Name()=="Berggnom") { bo_phk=5;}
  else if (Spezies()->Name()=="Waldgnom") { bo_phk=5;}
  else if (Spezies()->Name()=="Halbling") { bo_phk=5;}

  if (Typ[0]->Zaubern()=="z" || Typ[1]->Zaubern()=="z" )
    bo_phk+=3;

  return bo_phk;
}

void Grundwerte::resetSinne() 
{ 
 sinnmap["Sehen"]=8;
 sinnmap["H�ren"]=8;
 sinnmap["Riechen"]=8;
 sinnmap["Schmecken"]=8;
 sinnmap["Tasten"]=8; 
 sinnmap["Sechster Sinn"]=Zt()/25;
}


std::string Grundwerte::Version() const
{
  return version;
// if(!b) return version;
// return "Grad "+itos(grad);
}

void Grundwerte::setGrad1Werte(const vector<cH_Typen>& Typ)
{
 
  setSinn("Sechster Sinn",Zt()/25);
  setAbwehr_wert(11) ;
  setResistenz(10);

  if (Typ[0]->Zaubern() == "j" || Typ[0]->Zaubern() == "z" ||
      Typ[1]->Zaubern() == "j" || Typ[1]->Zaubern() == "z" ) 
      setZaubern_wert(10) ;
  else setZaubern_wert(2) ;
}

std::string Grundwerte::GroesseBez() const
{
  if     (Groesse()>180) return "gro�";
  else if(Groesse()>165) return "mittel";
  else return "klein";
}
