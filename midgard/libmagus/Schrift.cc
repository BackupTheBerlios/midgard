/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2002-2003 Christof Petig
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

#include "Schrift.hh"
#include "Sprache.hh"
#include <cstring>
#include <Misc/itos.h>
#include "Abenteurer.hh"
#include <iostream>
#include <Misc/Tag.h>
#include "NotFound.h"

cH_Schrift::cache_t cH_Schrift::cache;

cH_Schrift::cH_Schrift(const std::string& name ,bool create)
{
 cH_Schrift *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
 std::cerr << "Schrift '" << name << "' nicht im Cache\n";
  if (create)
  {  Tag t2("Schrift"); 
     t2.setAttr("Name",name);
     t2.setAttr("Typ","?");
     *this=new Schrift(name, t2);
  }
  else throw NotFound();
  }
}

void Schrift::get_Schrift(const Tag &t)
{
  art_der_schrift=t.getAttr("Name");
  region=t.getAttr("Region");
  region_zusatz=t.getAttr("RegionZusatz");
  kosten=t.getIntAttr("Kosten");
  alt=t.getBoolAttr("alte_Schrift");
  kult=t.getBoolAttr("Kultschrift");;
}

bool Schrift::kann_Sprache(const std::list<MBEmlt>& sprache) const
{
 for(std::list<MBEmlt>::const_iterator i=sprache.begin();i!=sprache.end();++i)
  {
   std::vector<std::string> V=cH_Sprache((*i)->getMBE())->Schrift();
   for(std::vector<std::string>::const_iterator j=V.begin();j!=V.end();++j)
      if(*j==Name()) return true ;
  }  
 return false;
}

int Schrift::MaxErfolgswert(const Abenteurer &A) const
{
  if(A.getWerte().In() < 61) return 14; 
  return cH_Fertigkeit("Schreiben")->MaxErfolgswert(A) ;
}

std::list<cH_MidgardBasicElement> Schrift::gleicheSchrift(const std::list<cH_MidgardBasicElement>& listSchrift) const
{
  std::list<cH_MidgardBasicElement> LS;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=listSchrift.begin();i!=listSchrift.end();++i)
     if(cH_Schrift(*i)->Art_der_Schrift()==Art_der_Schrift()) 
        LS.push_back(*i);
  return LS;
}

bool Schrift::Mutterschrift(const Abenteurer& A) const
{
  
  std::vector<std::string> V=A.getWerte().Spezies()->getVSprache();
  if(V.empty()) V=A.getWerte().Herkunft()->Sprachen();
  for(std::vector<std::string>::const_iterator i=V.begin();i!=V.end();++i)
   {
     const std::vector<std::string> W=cH_Sprache(*i)->Schrift();
     for(std::vector<std::string>::const_iterator j=W.begin();j!=W.end();++j)
      {
       std::string spezies=A.getWerte().Spezies()->Name();
       if(spezies=="Waldgnom" && Name()=="Zwergenrunen Futhark") return false;
       if(spezies=="Berggnom" && Name()=="Baumrunen Beth-Luis-Nion") return false;
       if(*j==Name()) return true;
      }
   }
  return false;
}

static MidgardBasicElement::EP_t Schrift_EP=MidgardBasicElement::EP_t_undefined;

Schrift::Schrift(const std::string& name,const Tag &t)
      : MidgardBasicElement(name)
{get_Schrift(t);get_map_typ();
 get_Steigern_Kosten_map();
   if (Schrift_EP==EP_t_undefined) Schrift_EP=EP_steigern("Schreiben");
   else EP_steigern(Schrift_EP);
}

cH_Schrift cH_Schrift::load(const std::string &name,const Tag &t)
{  cH_Schrift *res=cache.lookup(name);
   assert (!res);
   {  cH_Schrift r2=new Schrift(name,t);
      cache.Register(name,r2);
      return r2;
   }
}

void Schriften_All::load(std::list<cH_MidgardBasicElement> &list,const Tag &t)
{  FOR_EACH_CONST_TAG_OF(j,t,"Variante")
   {  cH_Schrift z=cH_Schrift::load(j->getAttr("Name"),t);
      // das &* dient dazu um aus einem cH_Schrift ein cH_MBE zu machen
      list.push_back(&*z);
   }
}

