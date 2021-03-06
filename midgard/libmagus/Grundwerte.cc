// $Id: Grundwerte.cc,v 1.24 2006/02/02 13:48:28 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2003-2005 Christof Petig
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
#include <Misc/itos.h>
#include "Sinne.hh"
#include "Fertigkeiten.hh"
#include "magustrace.h"
#include <Misc/TraceNV.h>

static unsigned neucount;

void Grundwerte::reset()
{
  ManuProC::Trace _t2(LibMagus::trace_vector,__PRETTY_FUNCTION__);
// *this=Grundwerte(); 
  raufen=0;
  au=0;
  pa=0;
  sb=0;
  wk=0;
  b=0;
  lp=0;
  ap=0;
  gg=0;
  sg=0;
  abwehr_wert=0;
  abwehr_pp=0;
  zaubern_wert=0;
  zauber_pp=0;
  pp_spezialzauber=0;
  resistenz=0;
  resistenz=0;
  resistenz_pp=0;
  alter=0;
  geschlecht=Enums::Mann;
  gewicht=0;
  groesse=0;
  grad=1;
  stand="";
  glaube="";
  if (name_abenteurer.empty()) 
    name_abenteurer="Neu "+itos(++neucount);
  version="Erschaffung";
  gfp=0;
  steigertage=0;
  gold=0; 
  silber=0; 
  kupfer=0;
  stadt_land=Enums::Stadt;
  goldanteil=50;
  fpanteil=50;
  wie_steigern=ws_Unterweisung;
  wie_steigern_variante=wie_steigern_variante_t();
  reduzieren=false;
  
  grad_basiswerte=1;
  herkunft=cH_Land("",true);

 resetSinne();
 ruestung.clear();
 ruestung.push_back(cH_Ruestung("OR",true));
 ruestung.push_back(cH_Ruestung("OR",true));

 muttersprache=""; 
 
 Typ.clear();
 Typ.resize(2);
}


int Grundwerte::bo_Au() const 
{ 
  return  Ko()/10 + St()/20 - 7 ;
}

int Grundwerte::bo_Sc() const 
{ 
  return  St()/20 + Gs()/30 - 3 ;
}

int Grundwerte::Raufen() const 
{ 
  return  (St()+Gw())/20 +bo_An() + Spezies()->Raufen();
}

std::string  Grundwerte::RaufenSchaden() const 
{ 
  int b=-4+bo_Sc();
  return  "W6"+itos0p(b,0,true);
}


std::string Grundwerte::Gestalt() const 
{ 
 if (Groesse() <= Gewicht()) return "breit";
 double normgew = Groesse() + Spezies()->Normgestalt(); 
 if (normgew <= 0) return "Fehler 8-) "; 
 double ge = Gewicht() / normgew;
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

int Grundwerte::bo_Psy() const
{
 int bo_psy;  
 if(Spezies()->Psy(*this)) 
    bo_psy = Spezies()->Psy(*this) ;
 else
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

  // Vorzeichen unterschiedlich:
  if( bo_psyIn*bo_psyZt<=0) bo_psy = bo_psyIn+bo_psyZt;
  else 
   {
     // Höheren Wert nehmen:
     bo_psy = (abs(bo_psyZt)>abs(bo_psyIn))?abs(bo_psyZt):abs(bo_psyIn);
     // Vorzeichen setzen:
     if(bo_psyZt<0) bo_psy*=-1;
   }
  }
  if (Typ[0]->Zaubern()=="z" || Typ[1]->Zaubern()=="z" )
    bo_psy+=3;

  return bo_psy;
}

int Grundwerte::bo_Phs() const
{
 int bo_phs;
 if(Spezies()->Phs(*this)) 
    bo_phs = Spezies()->Phs(*this) ;
 else
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
  if( bo_phsKo*bo_phsZt<=0) bo_phs = bo_phsKo+bo_phsZt;
  else 
   {
     // Höheren Wert nehmen:
     bo_phs = (abs(bo_phsZt)>abs(bo_phsKo))?abs(bo_phsZt):abs(bo_phsKo);
     // Vorzeichen setzen:
     if(bo_phsZt<0) bo_phs*=-1;
   }
  }
  if (Typ[0]->Zaubern()=="z" || Typ[1]->Zaubern()=="z" )
    bo_phs+=3;
  else bo_phs+=2;
  return bo_phs;
}

int Grundwerte::bo_Phk() const
{
  int bo_phk =0;   
 if(Spezies()->Phk(*this)) 
    bo_phk = Spezies()->Phk(*this) ;
 else
 {
  if (Gw()<=5)              {bo_phk-=2; }
  else if (6<=Gw()  && Gw()<=20) {bo_phk-=1; }
  else if (81<=Gw() && Gw()<=95) {bo_phk+=1; }
  else if (96<=Gw())             {bo_phk+=2; }
 }
  if (Typ[0]->Zaubern()=="z" || Typ[1]->Zaubern()=="z" )
    bo_phk+=3;

  return bo_phk;
}

const std::string Grundwerte::Resistenzen_alle() const
{
 int R=Resistenz();
 int R1=R+bo_Psy();
 int R2=R+bo_Phs();
 int R3=R+bo_Phk();
 int R4=Gift();
 std::string s=itos(R1)+"/"+itos(R2)+"/"+itos(R3)+"/"+itos(R4);
 return s;
}



void Grundwerte::setSinn(const std::string &name,int wert)
{
//  if (name=="Sechster Sinn") return; // accepting it doesn't hurt for now
// MAT: 26.4.2005: ist glaube ich nicht n�tig
  for(std::list<MBEmlt>::iterator i=list_Sinne.begin();i!=list_Sinne.end();++i)
   {
     if((*(*i))->Name()==name) 
      {
        (*i)->setErfolgswert(wert);
        return;
      }
   }
  std::cerr << "Sinn "<<name<<" not found\n";
  assert(!"Sinn nicht gefunden\n");
}

//#include<iostream>
int Grundwerte::getSinn(const std::string &name) const
{
  for(std::list<MBEmlt>::const_iterator i=list_Sinne.begin();i!=list_Sinne.end();++i)
   {
     if((*(*i))->Name()==name) 
      {
        if(name=="SechsterSinn" && (*i)->Erfolgswert()==0)
            return Zt()/25;
        return (*i)->Erfolgswert();
      }
   }
  assert(!"Sinn nicht gefunden\n");
  abort();
}

                                           


void Grundwerte::resetSinne() 
{
 list_Sinne.clear();
 Sinne_All::init(list_Sinne); 
 setSinn("Sechster Sinn",Zt()/25); 
}


std::string Grundwerte::Version() const
{
  return version;
}

void Grundwerte::setGrad1Werte()
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
  if     (Groesse()>180) return "groß";
  else if(Groesse()>165) return "mittel";
  else return "klein";
}



void Grundwerte::setSinnCheck(const std::string &name,int wert)
{
  if(getSinn(name)>8) setSinn(name,8); // Speziesspezifische Fertigkeit
  else setSinn(name,wert);
}


cH_Ruestung Grundwerte::Ruestung(unsigned int i) const
{
 if(ruestung.size()<i+1) return cH_Ruestung("OR");
 else return ruestung[i];
}

std::string Grundwerte::Ruestung_RW_Verlust() const
{
 std::string s;
 if(  Ruestung(0)->RW_Verlust() && !Ruestung(1)->RW_Verlust() )
    s= "\\scriptsize ("+itos(Gw()-Ruestung(0)->RW_Verlust())+")";
 else if( !Ruestung(0)->RW_Verlust() && Ruestung(1)->RW_Verlust() )
    s= "\\scriptsize ("+itos(Gw()-Ruestung(1)->RW_Verlust())+")";
 else if( Ruestung(0)->RW_Verlust() && Ruestung(1)->RW_Verlust() )
    s= "\\tiny ("+itos(Gw()-Ruestung(0)->RW_Verlust())
         +","+itos(Gw()-Ruestung(1)->RW_Verlust())+")";
 return s;
}


std::string Grundwerte::Ruestung_Abwehr_Verlust(const std::list<MBEmlt>& list_Fertigkeit) const
{
 int v0 = Ruestung(0)->AbwehrBonus_Verlust(bo_Ab());
 int v1 = Ruestung(1)->AbwehrBonus_Verlust(bo_Ab());
 // Abzug, wenn in Vollrüstung gekämpft wird, obwohl die
 // entsprechende Fertigkeit nicht beherrscht wird.
 bool kiv_gelernt=MBEmlt(cH_Fertigkeit("Kampf in Vollrüstung"))->ist_gelernt(list_Fertigkeit);
 if(Ruestung(0)->VollRuestungsAbzug()!=0 && !kiv_gelernt)
   v0 += Ruestung(0)->VollRuestungsAbzug();
 if(Ruestung(1)->VollRuestungsAbzug()!=0 && !kiv_gelernt)
   v1 += Ruestung(1)->VollRuestungsAbzug();

 std::string s;
 if     ( v0 && !v1)  s="\\scriptsize --"+itos(v0);
 else if(!v0 &&  v1)  s="\\scriptsize --"+itos(v1);
 else if( v0 &&  v1)  s="\\tiny --("+itos(v0)+"/"+itos(v1)+")";
 return s;
}

std::string Grundwerte::Ruestung_Angriff_Verlust(const std::list<MBEmlt>& list_Fertigkeit) const
{
 int v0 = Ruestung(0)->AngriffsBonus_Verlust(bo_An());
 int v1 = Ruestung(1)->AngriffsBonus_Verlust(bo_An());
 // Abzug, wenn in Vollrüstung gekämpft wird, obwohl die
 // entsprechende Fertigkeit nicht beherrscht wird.
 bool kiv_gelernt=MBEmlt(cH_Fertigkeit("Kampf in Vollrüstung"))->ist_gelernt(list_Fertigkeit);
 if(Ruestung(0)->VollRuestungsAbzug()!=0 && !kiv_gelernt)
   v0 += Ruestung(0)->VollRuestungsAbzug();
 if(Ruestung(1)->VollRuestungsAbzug()!=0 && !kiv_gelernt)
   v1 += Ruestung(1)->VollRuestungsAbzug();

 std::string s;
 if     ( v0 && !v1) s="\\scriptsize --"+itos(abs(v0));
 else if(!v0 &&  v1) s="\\scriptsize --"+itos(abs(v1));
 else if( v0 &&  v1) s="\\tiny --("+itos(v0)+"/"+itos(v1)+")";
 return s;
}

int Grundwerte::gold_kosten(int kosten) const
{ // soll es nicht 100% ergeben, dann getrennt rechnen
  if (fpanteil!=100-goldanteil) 
     return int(kosten * goldanteil/100. + 0.5);
  
  // damit es zu 100% aufgeht (Rundungsprobleme)
  return kosten-ep_kosten(kosten);
}


int Grundwerte::ep_kosten(int kosten) const
{
  int i =int(kosten * get_Steigern_EP_Prozent()/100. +0.5);
  return i;
}

std::string Grundwerte::Geschlecht_str() const
{
  switch (geschlecht) {
      case Enums::Mann: return "m";
      case Enums::Frau: return "f";
      case Enums::NoFM: 
      default : return "";
   }
  abort();
}

void Grundwerte::setGeschlecht(const std::string& _g)
{
  if     (_g=="m") setGeschlecht(Enums::Mann);
  else if(_g=="f") setGeschlecht(Enums::Frau);
  else             setGeschlecht(Enums::NoFM);
}

std::string Grundwerte::Stadt_Land_str() const
{
  switch (stadt_land) {
      case Enums::Stadt: return "Stadt";
      case Enums::Land: return "Land";
      case Enums::NoSL: 
      default : return "";
   }
  abort();
}

void Grundwerte::setStadtLand(const std::string& _g)
{
  if     (_g=="Stadt") setStadtLand(Enums::Stadt);
  else if(_g=="Land")  setStadtLand(Enums::Land);
  else                 setStadtLand(Enums::NoSL);
}

Grundwerte::Grundwerte(bool initialize)
	:  Ueberleben_angeboren(cH_Fertigkeit("Überleben Heimat",true)),
             raufen(),au(),pa(),sb(), wk(),
             b(),lp(),ap(),gg(),sg(),abwehr_wert(),abwehr_pp(),
             zaubern_wert(),zauber_pp(),pp_spezialzauber(),resistenz(),resistenz_pp(),
             alter(),geschlecht(Enums::Mann),gewicht(),groesse(),grad(1),
             stand(),glaube(),name_abenteurer(),version("Erschaffung"),
             gfp(),steigertage(),gold(), silber(), kupfer(),
             aep(),kep(),zep(),herkunft(cH_Land("",true)),spezies("Mensch"),
             stadt_land(Enums::Stadt), /*steigern_EP_prozent(50),*/ grad_basiswerte(1),
             Typ(2), wie_steigern(ws_Unterweisung), wie_steigern_variante(),
             goldanteil(50), fpanteil(50)
{ ManuProC::Trace _t2(LibMagus::trace_vector,__PRETTY_FUNCTION__,NV1(initialize));
  if (!initialize)
  { //std::cerr << "no init requested, ignored\n";
    initialize=true;
  }
  if (initialize) reset();
  else // minimal initialization
  {  ruestung.resize(2);
     Typ.resize(2);
//     resetSinne(); // hmmm
  }
}

void Grundwerte::setRuestung1(const std::string &r,bool force)
{assert(!ruestung.empty());
 ruestung[0]=cH_Ruestung(r,force);
}

void Grundwerte::setRuestung2(const std::string &r,bool force)
{assert(ruestung.size()>1);
 ruestung[1]=cH_Ruestung(r,force);
}
