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

void MagusKI::VerteileGFP(int gfp,const Prozente100 &p)
{
  prozente100=p;
  while(gfp>0)
   {
     int i=random.integer(1,100);
     const Enums::MBEListen was=Was();
     spezial_allgemein=p.getS(was);

     if     (i<=spezial_allgemein) Steigern(gfp,was);
     else                          NeuLernen(gfp,was);

cout << Aben.getWerte().Grad()<<' '<<Aben.getWerte().GFP()<<'\t'<<gfp<<'\n';
     int kosten=teste_auf_gradanstieg();
     gfp-=kosten;
cout << Aben.getWerte().Grad()<<' '<<Aben.getWerte().GFP()<<'\t'<<gfp<<'\n';

/*
     if     (i>=spezial_allgemein) cerr << i<<' '<<spezial_allgemein<<"\tSteigern\t"<<was<<'\t';
     else                          cerr << i<<' '<<spezial_allgemein<<"\tNeuLenren\t"<<was<<'\t';
cout << "Noch "<< (gfp-=10)<<" GFP\n";
*/
   }
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
  std::list<MBEmlt> LL=NeuLernenList(was,gfp);
  if(LL.empty()) return;
  std::vector<MBEmlt> V=List_to_Vector(LL);
  int j=random.integer(0,V.size()-1);
  MBEmlt M=V[j];

  if(!allowed_for_grad(M)) return;

  std::string info;
  bool ok=Aben.neu_lernen(M,info,get_wie_steigern(),get_bool_steigern());
  if(ok) 
   { gfp-=M->Kosten(Aben);
     get_known_list(was).push_back(M);
   }
}


void MagusKI::Steigern(int &gfp,const Enums::MBEListen was) 
{
  std::list<MBEmlt> &LL=get_known_list(was);
  if(LL.empty()) return;
  int j=random.integer(0,LL.size()-1);
  int x=0;
  for(std::list<MBEmlt>::iterator i=LL.begin();i!=LL.end();++i)
   {
     if(j==x++) 
      {
         if(!allowed_for_grad(*i)) return;

         std::string info;
         bool ok=Aben.steigere(*i,info,get_wie_steigern(),get_bool_steigern());        
         if(ok) gfp-=i->Steigern(Aben);
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

std::list<MBEmlt> &MagusKI::get_known_list(const Enums::MBEListen was) 
{
 return  Aben.get_known_list(was);
}

bool MagusKI::allowed_for_grad(const MBEmlt &M)
{
  if(M->Kosten(Aben)>0.5*Database.GradAnstieg.getGFP(Aben.getWerte().Grad()+1))
   {
cerr << M->Name() <<" wird nicht neu gelernt, weil es "<<M->Kosten(Aben)
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
cout <<"Info : "<< info<<'\n';
     kosten+=Aben.get_ab_re_za(Enums::eAbwehr,get_wie_steigern(),true,Database,info,get_bool_steigern());
     kosten+=Aben.get_ab_re_za(Enums::eResistenz,get_wie_steigern(),true,Database,info,get_bool_steigern());
     kosten+=Aben.get_ab_re_za(Enums::eZaubern,get_wie_steigern(),true,Database,info,get_bool_steigern());
cout <<"Info2: "<< info<<'\n';
     Aben.eigenschaften_steigern(info,Database);

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
