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

#include "Prototyp2.hh"
#include <cstring>
#include <Misc/itos.h>
#include "NotFound.h"
#include <Misc/Tag.h>
#include "Ausgabe.hh"

double Prototyp2::fac_for(const std::string &art, const std::string &name, const std::vector<cH_Prototyp2> &A)
{
  int count=0;
  double facsum=0;
  for(std::vector<cH_Prototyp2>::const_iterator i=A.begin();i!=A.end();++i)
   {
     std::vector<st_protolisten> PL;
     if     (art=="Z") PL=(*i)->LZauber();
     else if(art=="F") PL=(*i)->LFertigkeiten();
     else {Ausgabe(Ausgabe::Fatal,"Art = "+art); assert(!"Art nicht definiert");}
     std::vector<st_protolisten>::const_iterator j=find(PL.begin(),PL.end(),name);
     if(j!=PL.end())
      {
        ++count;
        facsum+=j->fac;
      }
   }
  if(count) return facsum/count; 
  else return 10.0; // großer Wert
}

cH_Prototyp2::cache_t cH_Prototyp2::cache;

cH_Prototyp2::cH_Prototyp2(const std::string& name,bool create)
{
 cH_Prototyp2 *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  Ausgabe(Ausgabe::Warning, "Prototyp2 '" + name + "' nicht im Cache");
  if (create)
  {  Tag t2("Prototyp2"); 
     t2.setAttr("Name",name);
     *this=new Prototyp2(t2);
  }
  else throw NotFound(name);
  }
}

Prototyp2::Prototyp2(const Tag &tag)
{
  name=tag.getAttr("Name"); // Info, Wissen, Natur, ....
  FOR_EACH_CONST_TAG(i,tag)
    { if     (i->Type()=="Zauber") lzauber.push_back(st_protolisten(
                    i->getAttr("Name"),i->getFloatAttr("Faktor")));
      else if(i->Type()=="Fertigkeit") lfertigkeiten.push_back(st_protolisten(
                    i->getAttr("Name"),i->getFloatAttr("Faktor")));
      else {Ausgabe(Ausgabe::Fatal,"Art = "+i->Type()); assert(!"Art nicht definiert");}
    }

}

cH_Prototyp2 cH_Prototyp2::load(const Tag &t)
{  cH_Prototyp2 *res=cache.lookup(t.getAttr("Name"));
   assert (!res);
   {  cH_Prototyp2 r2=new Prototyp2(t);
      cache.Register(t.getAttr("Name"),r2);
      return r2;
   }
}

void Prototyp2_All::load(std::list<cH_Prototyp2> &list,const Tag &t)
{  list.push_back(cH_Prototyp2::load(t));
}
