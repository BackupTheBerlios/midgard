/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

#include "Land.hh"
#include "NotFound.h"
#include "Abenteurer.hh"
#include <Misc/Tag.h>
#include "Ausgabe.hh"

cH_Land::cache_t cH_Land::cache;

cH_Land::cH_Land(const std::string& name ,bool create)
{
 cH_Land *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  Ausgabe(Ausgabe::Warning, "Land '" + name + "' nicht im Cache");
  if (create || name.empty()) // don t ask me ... it just works this way ...
  {  Tag t2("Land"); 
     t2.setAttr("Name",name);
     *this=new Land("?",t2);
  }
  else throw NotFound(name);
  }
}

bool Land::ist_erlaubt(const Abenteurer& A) const
{
  std::vector<std::string> V=A.Spezies()->getVHerkunft();
  if(V.empty()) // Keine Herkunftsvorgabe aufgrund der Spezies
   { 
     std::vector<cH_Typen> Typ=A.getVTyp();
     for(std::vector<cH_Typen>::const_iterator i=Typ.begin();i!=Typ.end();++i)
      {
        const std::vector<Typen::st_herkunft> V=(*i)->get_vec_herkunft();
        for(std::vector<Typen::st_herkunft>::const_iterator j=V.begin();j!=V.end();++j)
         {
           if(j->land==Name()) return true;
         }
      }
   }
  else
   {
     if(find(V.begin(),V.end(),Name())!=V.end()) return true;
   }
  return false;
}

bool Land::ist_bekannt(std::string s,const std::vector<cH_Land>& L)
{
  for( std::vector<cH_Land>::const_iterator i=L.begin();i!=L.end();++i)
   {
    if(s==(*i)->Name()) return true;
   }
  return false;
}

Land::Land(const std::string& _kontinent, const Tag &tag)
  : name(tag.getAttr("Name")), kontinent(_kontinent), region(tag.getAttr("Region"))
{  FOR_EACH_CONST_TAG_OF(i,tag,"Sprache")
      vec_sprache.push_back(i->getAttr("Name"));
   FOR_EACH_CONST_TAG_OF(i,tag,"Nachbarland")
      nachbarlaender.push_back(i->getAttr("Name"));
}

cH_Land cH_Land::load(const std::string& _kontinent,const Tag &t)
{  cH_Land *res=cache.lookup(t.getAttr("Name"));
   assert (!res);
   {  cH_Land r2=new Land(_kontinent,t);
      cache.Register(t.getAttr("Name"),r2);
      return r2;
   }
}

void Laender_All::load(std::list<cH_Land> &list,const std::string& _kontinent,const Tag &t)
{  list.push_back(cH_Land::load(_kontinent,t));
}

void Laender_All::load(std::vector<cH_Land> &list,const std::string& _kontinent,const Tag &t)
{  list.push_back(cH_Land::load(_kontinent,t));
}

