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

void MagusKI::VerteileGFP(int gfp)
{
  while(gfp>0)
   {
     int i=random.integer(1,2);
     if     (i==1) Steigern(gfp);
     else if(i==2) NeuLernen(gfp);
cout << "Noch "<< gfp<<" GFP\n";
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
return Enums::sFert; //DEBUG

  int min=Enums::sFert;
  int max=Enums::sZWerk;
  int i=random.integer(min,max);
  return Enums::MBEListen(i);
}

void MagusKI::NeuLernen(int &gfp)
{
  Enums::MBEListen was=Was();
  std::list<MBEmlt> LL=NeuLernenList(was,gfp);
  if(LL.empty()) return;
  std::vector<MBEmlt> V=List_to_Vector(LL);
  int j=random.integer(0,V.size()-1);
  MBEmlt M=V[j];
cout << M->Name()<<"  neu gelernt\t";
cout << Aben.List_Fertigkeit().size()<<'\t';

  std::string info;
  Enums::e_wie_steigern wie=Enums::eUnterweisung;
  Enums::st_bool_steigern bool_steigern(false,false,false,false,false,false,false,false);
  bool ok=Aben.neu_lernen(M,info,wie,bool_steigern);

  if(ok) gfp-=M->Kosten(Aben);

cout << "Info: "<<info<<'\n';

//  get_known_list(was).push_back(M);
cout << Aben.List_Fertigkeit().size()<<'\n';
}


void MagusKI::Steigern(int &gfp) 
{
  Enums::MBEListen was=Was();
  std::list<MBEmlt> &LL=get_known_list(was);
  if(LL.empty()) return;
  int j=random.integer(0,LL.size()-1);
  int x=0;
  for(std::list<MBEmlt>::iterator i=LL.begin();i!=LL.end();++i)
   {
     if(j==x++) 
      {
cerr <<  (*i)->Name() << " gesteigert\n";
         std::string info;
         Enums::e_wie_steigern wie=Enums::eUnterweisung;
         Enums::st_bool_steigern bool_steigern(false,false,false,false,false,false,false,false);
         bool ok=Aben.steigere(*i,info,wie,bool_steigern);        
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

