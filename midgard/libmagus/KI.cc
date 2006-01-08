/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2003 Christof Petig
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

#include "KI.hh"
#include "Random.hh"
#include <Misc/itos.h>
#include "Zauber.hh"
#include "Fertigkeiten.hh"
#include <Ausgabe.hh>
//#include <iostream>
#include "LernListen.hh"
//#include "Prototyp2.hh"
//#include "Beruf.hh"
#include "Datenbank.hh"

void MagusKI::VerteileGFP(int gfp,const Prozente100 &p,
                          const Grund_Standard_Ausnahme_MBE &gsa)
{
  prozente100=p;
  GSA_MBE=gsa;
  vec_Prototypen.clear();
  use_GSA_MBE=true;
  Verteile(gfp);
}

void MagusKI::VerteileGFP(int gfp,const Prozente100 &p,const std::vector<cH_Prototyp2> &Prototypen)
{
  prozente100=p;
  vec_Prototypen=Prototypen;
  use_GSA_MBE=false;
  Verteile(gfp);
}

void MagusKI::ausgabe(const st_KI& stki, const bool gesteigert,MidgardBasicElement::MBEE was) const
{
  std::string aktion="neu gelernt";
  if(gesteigert) aktion="gesteigert";
  std::string prefix=was +" "+aktion ;
  if(stki.e_ki==OK)
   { 
     Ausgabe(Ausgabe::Debug,prefix+"\tOK:\t"+stki.name+"\t"+itos(stki.wert));
   }
  else if(stki.e_ki==EmptyList)
   { 
     Ausgabe(Ausgabe::Debug,prefix+ "\tEmptyList:");
   }
  else if(stki.e_ki==NotAllowedForGrad)
   { 
     Ausgabe(Ausgabe::Debug,prefix+"\tNotAllowdForGrad:\t"+stki.name);
   }
  else if(stki.e_ki==Geheimzeichen)
   { 
     Ausgabe(Ausgabe::Debug,prefix+"\tGeheimzeichen:\t"+stki.name);
   }
  else if(stki.e_ki==NoSteigern)
   { 
     Ausgabe(Ausgabe::Debug,prefix+"\tNoSteigern:\t"+stki.name+"\t"+itos(stki.wert));
   }
  else assert(!"never get here\n");
}

void MagusKI::Verteile(int gfp)
{
  int count=0;//,gfpmem=gfp; // wenn man nicht mitzählt, kann es zu Endlosschleifen kommen
  const int MAXCOUNT=100;
  while(gfp>0 && count<MAXCOUNT)
   {
     int i=Random::W100();
     const MidgardBasicElement::MBEE was=Was();
     int spezial_allgemein=prozente100.getS(was);

     while(true)
      {
        st_KI stki(OK);
        if     (i<=spezial_allgemein) {stki=Steigern(gfp,was); ausgabe(stki,true,was); }
        else                          {stki=NeuLernen(gfp,was);ausgabe(stki,false,was); }
        if(stki.e_ki==OK) break;
        else if(stki.e_ki==EmptyList) break;
        else if(stki.e_ki==NotAllowedForGrad) ++count;
        else if(stki.e_ki==Geheimzeichen) ++count;
        else if(stki.e_ki==NoSteigern) ++count;
        else assert(!"never get here\n");
        if(count>=MAXCOUNT) break;
      }
     int kosten=teste_auf_gradanstieg();
     gfp-=kosten;
   }
  if(count==MAXCOUNT) 
     Ausgabe(Ausgabe::Error,"Steigern abgebrochen, weil "+itos(count)+" Versuche erfolglos blieben.");
  // Das Alter anpassen
  Aben.Steigertage2Alter();
}

std::vector<MBEmlt> List_to_Vector(const std::list<MBEmlt> &L)
{
  std::vector<MBEmlt> V;
  for(std::list<MBEmlt>::const_iterator i=L.begin();i!=L.end();++i)
     V.push_back(*i);
  return V;
}


const MidgardBasicElement::MBEE MagusKI::Was() const
{
  int z=Random::W100();
  const std::vector<Prozente100::st_was> V=prozente100.get100V();
  for(std::vector<Prozente100::st_was>::const_iterator i=V.begin();i!=V.end();++i)
    if( z <= i->prozent) return i->was; 
  assert(!"never get here"); abort();
}

MagusKI::st_KI  MagusKI::NeuLernen(int &gfp,const MidgardBasicElement::MBEE was)
{
  std::list<MBEmlt> LL_=NeuLernenList(was,gfp);
  std::list<MBEmlt> LL;
  if(use_GSA_MBE)  LL=KI_GSA_Liste(LL_);
  else             LL=KI_Prototypen_Liste(was,LL_,false);
  if(LL.empty()) return st_KI(EmptyList);
  std::vector<MBEmlt> V=List_to_Vector(LL);
  int j=Random::integer(0,V.size()-1);
  MBEmlt M=V[j];

  if((*M)->Name()=="Geheimzeichen")   return st_KI((*M)->Name(),Geheimzeichen);
  if(!allowed_for_grad(M,eNeuLernen)) return st_KI((*M)->Name(),NotAllowedForGrad);

  Aben.wie_steigern=Abenteurer::ws_Unterweisung;
  bool ok=Aben.neu_lernen(M);
  if(ok) 
   { gfp-=(*M)->Kosten(Aben);
     Aben.get_known_list(was).push_back(M);
     return st_KI((*M)->Name(),(*M).Erfolgswert(),OK);
   }
 return st_KI((*M)->Name(),(*M).Erfolgswert(),NoSteigern); 
}


MagusKI::st_KI MagusKI::Steigern(int &gfp,const MidgardBasicElement::MBEE was) 
{
  std::list<MBEmlt> &LL_=Aben.get_known_list(was);
  std::list<MBEmlt> LL;
  if(use_GSA_MBE) LL=KI_GSA_Liste(LL_);
  else            LL=KI_Prototypen_Liste(was,LL_,true);
  if(LL.empty()) return st_KI(EmptyList);
  int j=Random::integer(0,LL.size()-1);
  int x=0;
  for(std::list<MBEmlt>::iterator i=LL.begin();i!=LL.end();++i)
   {
     if(j==x++) 
      {
         if(!allowed_for_grad(*i,eSteigern)) return st_KI((*(*i))->Name(),NotAllowedForGrad);

         Aben.wie_steigern=Abenteurer::ws_Selbststudium;
         bool ok=Aben.steigere(*i);
         if(ok) 
           { gfp-=(*i)->Steigern(Aben);
             return st_KI((*(*i))->Name(),(*(*i)).Erfolgswert(),OK);
           }
         else
             return st_KI((*(*i))->Name(),(*(*i)).Erfolgswert(),NoSteigern);
      }
   }
 assert(!"never get here");
 abort();
}


std::list<MBEmlt> MagusKI::NeuLernenList(const MidgardBasicElement::MBEE was,const int gfp) const
{
   std::list<MBEmlt> LL;
  switch (was) {
     case MidgardBasicElement::FERTIGKEIT: 
     case MidgardBasicElement::WAFFE: 
     case MidgardBasicElement::SPRACHE: 
     case MidgardBasicElement::SCHRIFT: 
     case MidgardBasicElement::WAFFEGRUND: LL=LernListen::get_steigern_MBEm(Aben,was); break;
     case MidgardBasicElement::ZAUBER: {
         bool salz=false;
         bool beschw=false;
         bool spruchrolle=false;
         LL=LernListen::get_steigern_Zauberliste(Aben,salz,beschw,false,spruchrolle); 
         break;
        }
     case MidgardBasicElement::ZAUBERWERK: LL=LernListen::get_steigern_ZauberWerkliste(Aben,false); break;
     default: assert(!"never get here\n");
   }
 LernListen::shorten_for_GFP(LL,Aben,gfp);
 return LL;
}


struct st_sort{std::string name; int kosten;
       st_sort(std::string n,int k) :name(n),kosten(k) {}
       bool operator<(const st_sort &b) const {return kosten<b.kosten || 
            (kosten==b.kosten && name<b.name); }
       };

std::list<MBEmlt> MagusKI::KI_Prototypen_Liste(const MidgardBasicElement::MBEE was,const std::list<MBEmlt> &L,bool steigern)
{
  std::string Was;
  if     (was==MidgardBasicElement::FERTIGKEIT)Was="F";
  else if(was==MidgardBasicElement::ZAUBER)Was="Z";
  else return L;
  
  std::list<st_sort> S;
  for(std::list<MBEmlt>::const_iterator i=L.begin();i!=L.end();++i)
   {
     double fac=Prototyp2::fac_for(Was,(*(*i))->Name(),vec_Prototypen);
     int kosten;
     if(steigern)  kosten = (*i)->Steigern(Aben);
     else          kosten = (*(*i))->Kosten(Aben);
     S.push_back(st_sort((*(*i))->Name(),kosten*fac));
   }
  S.sort();
  std::list<MBEmlt> newL;
  if(S.empty()) return newL;
  if     (was==MidgardBasicElement::FERTIGKEIT) newL.push_back(MBEmlt(cH_Fertigkeit(S.begin()->name)));
  else if(was==MidgardBasicElement::ZAUBER) newL.push_back(MBEmlt(cH_Zauber(S.begin()->name)));
  return newL;
}


std::list<MBEmlt> MagusKI::KI_GSA_Liste(const std::list<MBEmlt> &L)
{
  std::list<MBEmlt> Grund,Standard,Ausnahme;
  for(std::list<MBEmlt>::const_iterator i=L.begin();i!=L.end();++i)
   {
     if     ((*(*i))->Grundfertigkeit(Aben))    Grund.push_back(*i);
     else if((*(*i))->Standardfertigkeit(Aben)) Standard.push_back(*i);
     else Ausnahme.push_back(*i);
   }
  int z=Random::W100();
  bool g=false,s=false,a=false;
  if     (z<GSA_MBE.getG()) g=true;
  else if(z<GSA_MBE.getG()+GSA_MBE.getS()) s=true;
  else a=true;

  if(g)
   { if     (!Grund.empty())    return Grund;
     else if(!Standard.empty()) return Standard;
     else                       return Ausnahme;
   }
  else if(s)
   { if     (!Standard.empty()) return Standard;
     else if(!Grund.empty())    return Grund;
     else                       return Ausnahme;
   }
  else if(a)
   {
     if     (!Ausnahme.empty()) return Ausnahme;
     else if(!Standard.empty()) return Standard;
     else                       return Grund;
   }  
  assert(!"never get here\n");
  abort();
}



bool MagusKI::allowed_for_grad(const MBEmlt &M,eSL was)
{
  int maxkosten = int(0.5*Datenbank.GradAnstieg.getGFP(Aben.Grad()+1));
  if(was==eNeuLernen && (*M)->Kosten(Aben)>maxkosten)
   {
Ausgabe(Ausgabe::Debug,(*M)->Name() +" wird nicht neu gelernt, weil es "+itos((*M)->Kosten(Aben))
+" kostet\tGrad: "+itos(Aben.Grad())+" "
+itos(Datenbank.GradAnstieg.getGFP(Aben.Grad()+1)));
     return false;
   }
  else if(was==eSteigern && M->Steigern(Aben)>maxkosten)
   {
Ausgabe(Ausgabe::Debug,(*M)->Name() +" wird nicht gesteigert, weil es "+itos((*M).Steigern(Aben))
+" kostet\tGrad: "+itos(Aben.Grad())+" "
+itos(Datenbank.GradAnstieg.getGFP(Aben.Grad()+1)));
     return false;
   }
  return true;
}

int MagusKI::teste_auf_gradanstieg()
{
  int oldgrad=Aben.Grad();
  Aben.setGrad(Datenbank.GradAnstieg.get_Grad(Aben.GFP()));
  int kosten=0;
  if(oldgrad!=Aben.Grad())
   { Aben.wie_steigern=Abenteurer::ws_Unterweisung;
     kosten+=Aben.get_ausdauer(Aben.Grad());
     kosten+=Aben.get_ab_re_za(ResistenzUndCo::eAbwehr);
     kosten+=Aben.get_ab_re_za(ResistenzUndCo::eResistenz);
     kosten+=Aben.get_ab_re_za(ResistenzUndCo::eZaubern);
     Aben.eigenschaften_steigern();
   }  
  return kosten;
}

MagusKI::MagusKI(Abenteurer &a)
  : Aben(a), use_GSA_MBE(true)
{ a.fpanteil=0;
  a.goldanteil=0;
}
