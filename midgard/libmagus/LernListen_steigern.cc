// $Id: LernListen_steigern.cc,v 1.10 2006/02/03 07:44:19 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include "LernListen.hh"
#include "Abenteurer.hh"
#include "WaffeGrund.hh"
#include "Schrift.hh"
#include "Zauber.hh"
#include "Zauberwerk.hh"
#include "Datenbank.hh"

std::list<MBEmlt> LernListen::get_steigern_MBEm(const Abenteurer& A,MidgardBasicElement::MBEE was)
{
  std::list<cH_MidgardBasicElement> V_;
  switch(was) {
     case MidgardBasicElement::FERTIGKEIT: V_=Datenbank.Fertigkeit; break;
     case MidgardBasicElement::WAFFE: V_=Datenbank.Waffe; break;
     case MidgardBasicElement::ZAUBER: V_=Datenbank.Zauber; break;
     case MidgardBasicElement::SPRACHE: V_=Datenbank.Sprache; break;
     case MidgardBasicElement::SCHRIFT: V_=Datenbank.Schrift; break;
     case MidgardBasicElement::WAFFEGRUND: V_=Datenbank.WaffeGrund; break;
     case MidgardBasicElement::ZAUBERWERK:V_=Datenbank.Zauberwerk; break; 
     default : assert(!"never get here\n");
   }
  std::list<MBEmlt> V;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=V_.begin();i!=V_.end();++i)
   { MBEmlt MBEm=A.get_unknown(*i);
     if (!!MBEm) V.push_back(MBEm);
   }
  return V;
}

std::list<MBEmlt> LernListen::get_steigern_Zauberliste(const Abenteurer& A,
      bool salz,bool beschwoerung, bool alle,bool spruchrolle)
{
  std::list<MBEmlt> L_=get_steigern_MBEm(A,MidgardBasicElement::ZAUBER);
  std::list<MBEmlt> L;
  for(std::list<MBEmlt>::const_iterator i=L_.begin();i!=L_.end();++i)
   {
     cH_Zauber z((*i)->getMBE());
     if(!alle)
      {
        if (z->Zauberart()=="Zaubersalz"   && !salz ) continue;
        if (z->Zauberart()=="Beschwörung"  && !beschwoerung) continue;
        if (!z->Spruchrolle()              && spruchrolle) continue;
        // maximale Stufe
        std::vector<std::string> standard=z->Standard(A);
        int maxstufe=A.Grad();
        if ((A.Typ1()->Short()=="Ma" 
              && z->get_spezial_zauber_for_magier(A,standard[0]))
            || (A.Typ2()->Short()=="Ma" 
              && z->get_spezial_zauber_for_magier(A,standard[1])))
          ++maxstufe;
        if (A.In()<=10 && maxstufe>2) maxstufe=2;
        else if (A.In()<=30 && maxstufe>4) maxstufe=4;
        if (z->iStufe()>maxstufe) continue;
      }
     if (z->Spruchrolle()) z->setSpruchrolleFaktor(0.1);
     else z->setSpruchrolleFaktor(1);
     L.push_back(*i);
   }
 return L;
}

std::list<MBEmlt> LernListen::get_steigern_ZauberWerkliste(const Abenteurer& A,
     bool alle)
{
  std::list<MBEmlt> L_=get_steigern_MBEm(A,MidgardBasicElement::ZAUBERWERK);
  std::list<MBEmlt> L;
  for(std::list<MBEmlt>::const_iterator i=L_.begin();i!=L_.end();++i)
   { const cH_Zauberwerk z((*i)->getMBE());
     if(alle) L.push_back(*i); 
     else
      {  if (!z->Voraussetzungen(A.List_Zauber())) continue;
         if (!z->Voraussetzungen_Fertigkeit(A.List_Fertigkeit())) continue;
         L.push_back(*i); 
      }
   }
 return L;
}


void LernListen::shorten_for_GFP(std::list<MBEmlt> &L_,const Abenteurer& A,const int gfp)
{
  std::list<MBEmlt> L;
  for(std::list<MBEmlt>::const_iterator i=L_.begin();i!=L_.end();++i)
   {
     if((*(*i))->Kosten(A) > gfp) continue;
     L.push_back(*i);
   }
  L_=L;
}

