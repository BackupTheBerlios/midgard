// $Id: Grundwerte.cc,v 1.4 2002/01/19 17:07:32 christof Exp $               
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
  int g1=Groesse()-100;
  int g2=Groesse()-Gewicht();
  double ge=g2/g1;
  if(ge>1.1)      return "breit";
  else if(ge<0.9) return "schlank";
  else            return "normal";
}


int Grundwerte::bo_An() const 
{ 
  int bo_an = 0;
  if (1<=Gs()  &&Gs() <=5)  { bo_an-=2; }
  if (6<=Gs()  &&Gs() <=20) { bo_an-=1; }
  if (81<=Gs() &&Gs() <=95) { bo_an+=1; }
  if (96<=Gs())             { bo_an+=2; }
  return bo_an;
}

int Grundwerte::bo_Ab() const 
{ 
  int bo_ab = 0;
  if (1<=Gw()  &&Gw() <=5)  { bo_ab-=2; }
  if (6<=Gw()  &&Gw() <=20) { bo_ab-=1; }
  if (81<=Gw() &&Gw() <=95) { bo_ab+=1; }
  if (96<=Gw())             { bo_ab+=2; }
  return bo_ab;
}

int Grundwerte::bo_Za() const 
{ 
  int bo_za  =0;
  if (Zt()<=5)              {bo_za-=3; }
  if (6<=Zt()  && Zt()<=20) {bo_za-=2; }
  if (21<=Zt() && Zt()<=40) {bo_za-=1; }
  if (61<=Zt() && Zt()<=80) {bo_za+=1; }
  if (81<=Zt() && Zt()<=95) {bo_za+=2; }
  if (96<=Zt() && Zt()<=99) {bo_za+=3; }
  if (Zt()>=100)            {bo_za+=4; }
  return bo_za;
}

int Grundwerte::bo_Psy(const vector<cH_Typen>& Typ) const
{
  int bo_psyZt =0;
  if (Zt()<=5)              {bo_psyZt-=2; }
  if (6<=Zt()  && Zt()<=20) {bo_psyZt-=1; }
  if (81<=Zt() && Zt()<=95) {bo_psyZt+=1; }
  if (96<=Zt() && Zt()<=99) {bo_psyZt+=2; }
  if (Zt()>=100)            {bo_psyZt+=3; }

  int bo_psyIn =0;
  if (In()<=5)              { bo_psyIn-=2; }
  if (6<=In()  && In()<=20) { bo_psyIn-=1; }
  if (81<=In() && In()<=95) { bo_psyIn+=1; }
  if (96<=In())             { bo_psyIn+=2; }
  
  int bo_psy = (bo_psyZt>bo_psyIn) ? bo_psyZt : bo_psyIn ;

  if (Spezies()->Name()=="Elf" && Zt() <= 100 ) { bo_psy=2;}
  if (Spezies()->Name()=="Elf" && Zt() >= 100 ) { bo_psy=3;}

  if (Spezies()->Name()=="Berggnom") { bo_psy=5;}
  if (Spezies()->Name()=="Waldgnom") { bo_psy=5;}
  if (Spezies()->Name()=="Halbling") { bo_psy=5;}
  if (Spezies()->Name()=="Zwerg")    { bo_psy=4;}

  if (Typ[0]->Zaubern()=="z" || Typ[1]->Zaubern()=="z" )
    bo_psy+=3;

  return bo_psy;
}

int Grundwerte::bo_Phs(const vector<cH_Typen>& Typ) const
{
  int bo_phsZt =0;
  if (Zt()<=5)              {bo_phsZt-=2; }
  if (6<=Zt()  && Zt()<=20) {bo_phsZt-=1; }
  if (81<=Zt() && Zt()<=95) {bo_phsZt+=1; }
  if (96<=Zt() && Zt()<=99) {bo_phsZt+=2; }
  if (Zt()>=100)            {bo_phsZt+=3; }

  int bo_phsKo =0;
  if (Ko()<=5)           { bo_phsKo-=2; }
  if (6<=Ko()&&Ko()<=20)  { bo_phsKo-=1; }
  if (81<=Ko()&&Ko()<=95) { bo_phsKo+=1; }
  if (96<=Ko())          { bo_phsKo+=2; }

  int bo_phs = (bo_phsZt>bo_phsKo) ? bo_phsZt : bo_phsKo ;

  if (Spezies()->Name()=="Elf" && Zt() <= 100 ) { bo_phs=2;}
  if (Spezies()->Name()=="Elf" && Zt() >= 100 ) { bo_phs=3;}
  if (Spezies()->Name()=="Berggnom") { bo_phs=5;}
  if (Spezies()->Name()=="Waldgnom") { bo_phs=5;}
  if (Spezies()->Name()=="Halbling") { bo_phs=5;}
  if (Spezies()->Name()=="Zwerg")    { bo_phs=4;}

  if (Typ[0]->Zaubern()=="z" || Typ[1]->Zaubern()=="z" )
    bo_phs+=3;
  else bo_phs+=2;
  return bo_phs;
}

int Grundwerte::bo_Phk(const vector<cH_Typen>& Typ) const
{
  int bo_phk =0;   
  if (Gw()<=5)              {bo_phk-=2; }
  if (6<=Gw()  && Gw()<=20) {bo_phk-=1; }
  if (81<=Gw() && Gw()<=95) {bo_phk+=1; }
  if (96<=Gw())             {bo_phk+=2; }
  if (Spezies()->Name()=="Elf")      { bo_phk=2;}
  if (Spezies()->Name()=="Berggnom") { bo_phk=5;}
  if (Spezies()->Name()=="Waldgnom") { bo_phk=5;}
  if (Spezies()->Name()=="Halbling") { bo_phk=5;}

  if (Typ[0]->Zaubern()=="z" || Typ[1]->Zaubern()=="z" )
    bo_phk+=3;

  return bo_phk;
}

void Grundwerte::resetSinne() 
{ 
 sinnmap["Sehen"]=8;
 sinnmap["Hören"]=8;
 sinnmap["Riechen"]=8;
 sinnmap["Schmecken"]=8;
 sinnmap["Tasten"]=8; 
}


std::string Grundwerte::Version(bool b) const
{
 if(!b) return version;
 return "Grad "+itos(grad);
}
