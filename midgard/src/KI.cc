/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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
#include "KI.hh"
#include "zufall.h"
#include <Misc/itos.h>
#include "Zauber.hh"
#include "Fertigkeiten.hh"

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

void MagusKI::Verteile(int gfp)
{
  int count=0,gfpmem=gfp; // wenn man nicht mitzählt, kann es zu Endlosschleifen kommen
  const int MAXCOUNT=100;
  while(gfp>0 && count<MAXCOUNT)
   {
     int i=random.integer(1,100);
     const Enums::MBEListen was=Was();
     int spezial_allgemein=prozente100.getS(was);

     if     (i<=spezial_allgemein) Steigern(gfp,was);
     else                          NeuLernen(gfp,was);

     if(gfp!=gfpmem) {gfpmem=gfp; count=0;}
     else ++count;

     int kosten=teste_auf_gradanstieg();
     gfp-=kosten;
   }
  if(count==MAXCOUNT) hauptfenster->set_status("Steigern abgebrochen, weil "+itos(MAXCOUNT)+" Versuche erfolglos blieben.");
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


const Enums::MBEListen MagusKI::Was() const
{
  int z=random.integer(1,100);
  const std::vector<Prozente100::st_was> V=prozente100.get100V();
  for(std::vector<Prozente100::st_was>::const_iterator i=V.begin();i!=V.end();++i)
    if( z <= i->prozent) return i->was; 
  assert(!"never get here"); abort();
}

void MagusKI::NeuLernen(int &gfp,const Enums::MBEListen was)
{
  std::list<MBEmlt> LL_=NeuLernenList(was,gfp);
  std::list<MBEmlt> LL;
  if(use_GSA_MBE)  LL=KI_GSA_Liste(LL_);
  else             LL=KI_Prototypen_Liste(was,LL_,false);
  if(LL.empty()) return;
  std::vector<MBEmlt> V=List_to_Vector(LL);
  int j=random.integer(0,V.size()-1);
  MBEmlt M=V[j];

  if(!allowed_for_grad(M,eNeuLernen)) return;

  std::string info;
  bool ok=Aben.neu_lernen(M,info,get_wie_steigern(),get_bool_steigern());
  if(ok) 
   { gfp-=(*M)->Kosten(Aben);
     Aben.get_known_list(was).push_back(M);
   }
}


void MagusKI::Steigern(int &gfp,const Enums::MBEListen was) 
{
  std::list<MBEmlt> &LL_=Aben.get_known_list(was);
  std::list<MBEmlt> LL;
  if(use_GSA_MBE) LL=KI_GSA_Liste(LL_);
  else            LL=KI_Prototypen_Liste(was,LL_,true);
  if(LL.empty()) return;
  int j=random.integer(0,LL.size()-1);
  int x=0;
  for(std::list<MBEmlt>::iterator i=LL.begin();i!=LL.end();++i)
   {
     if(j==x++) 
      {
         if(!allowed_for_grad(*i,eSteigern)) return;

         std::string info;
         bool ok=Aben.steigere(*i,info,get_wie_steigern(),get_bool_steigern());        
         if(ok) gfp-=(*i)->Steigern(Aben);
      }
   }
}


std::list<MBEmlt> MagusKI::NeuLernenList(const Enums::MBEListen was,const int gfp) const
{
  LernListen LLD(Database);
  bool nsc = hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::NSC_only).active;
   std::list<MBEmlt> LL;
  switch (was) {
     case Enums::sFert: 
     case Enums::sWaff: 
     case Enums::sSpra: 
     case Enums::sSchr: 
     case Enums::sWGru: LL=LLD.get_steigern_MBEm(Aben,was,nsc); break;
     case Enums::sZaub: {
         bool salz=false;
         bool beschw=false;
         bool spruchrolle=false;
         LL=LLD.get_steigern_Zauberliste(Aben,salz,beschw,nsc,false,spruchrolle); 
         break;
        }
     case Enums::sZWerk: LL=LLD.get_steigern_ZauberWerkliste(Aben,nsc,false); break;
     default: assert(!"never get here\n");
   }
 LLD.shorten_for_GFP(LL,Aben,gfp);
 return LL;
}


struct st_sort{std::string name; int kosten;
       st_sort(std::string n,int k) :name(n),kosten(k) {}
       bool operator<(const st_sort &b) const {return kosten<b.kosten || 
            (kosten==b.kosten && name<b.name); }
       };

std::list<MBEmlt> MagusKI::KI_Prototypen_Liste(const Enums::MBEListen was,const std::list<MBEmlt> &L,bool steigern)
{
  std::string Was;
  if     (was==Enums::sFert)Was="F";
  else if(was==Enums::sZaub)Was="Z";
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
  if     (was==Enums::sFert) newL.push_back(MBEmlt(&*cH_Fertigkeit(S.begin()->name)));
  else if(was==Enums::sZaub) newL.push_back(MBEmlt(&*cH_Zauber(S.begin()->name)));
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
  int z=random.integer(1,100);
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
  int maxkosten = int(0.5*Database.GradAnstieg.getGFP(Aben.getWerte().Grad()+1));
  if(was==eNeuLernen && (*M)->Kosten(Aben)>maxkosten)
   {
cerr << (*M)->Name() <<" wird nicht neu gelernt, weil es "<<(*M)->Kosten(Aben)
<<" kostet\tGrad: "<<Aben.getWerte().Grad()<<' '
<<Database.GradAnstieg.getGFP(Aben.getWerte().Grad()+1)<<'\n';
     return false;
   }
  if(was==eSteigern && M->Steigern(Aben)>maxkosten)
   {
cerr << (*M)->Name() <<" wird nicht gesteigert, weil es "<<(*M).Steigern(Aben)
<<" kostet\tGrad: "<<Aben.getWerte().Grad()<<' '
<<Database.GradAnstieg.getGFP(Aben.getWerte().Grad()+1)<<'\n';
     return false;
   }
  return true;
}

int MagusKI::teste_auf_gradanstieg()
{
  int oldgrad=Aben.getWerte().Grad();
  Aben.getWerte().setGrad(Database.GradAnstieg.get_Grad(Aben.getWerte().GFP()));
  int kosten=0;
  if(oldgrad!=Aben.getWerte().Grad())
   {
     std::string info;
     kosten+=Aben.get_ausdauer(Aben.getWerte().Grad(),Database,info,
                                get_wie_steigern(),get_bool_steigern());
     kosten+=Aben.get_ab_re_za(Enums::eAbwehr,get_wie_steigern(),true,Database,info,get_bool_steigern());
     kosten+=Aben.get_ab_re_za(Enums::eResistenz,get_wie_steigern(),true,Database,info,get_bool_steigern());
     kosten+=Aben.get_ab_re_za(Enums::eZaubern,get_wie_steigern(),true,Database,info,get_bool_steigern());
     Aben.eigenschaften_steigern(info,Database);
     hauptfenster->set_info(info);
   }  
  return kosten;
}

const Abenteurer::e_wie_steigern MagusKI::get_wie_steigern()
{
  return Enums::eUnterweisung;
}

const Enums::st_bool_steigern MagusKI::get_bool_steigern()
{
  return Enums::st_bool_steigern(false,false,false,false,false,false,false,false);
}

