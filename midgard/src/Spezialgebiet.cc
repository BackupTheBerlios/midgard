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

#include "Spezialgebiet.hh"

cH_Spezialgebiet::cache_t cH_Spezialgebiet::cache;

cH_Spezialgebiet::cH_Spezialgebiet(const std::string& name)
{
 cH_Spezialgebiet *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else { std::cerr << "Spezialgebiet '"<<name<<"' nicht gefunden\n";
        assert(!"Spezialgebiet im Cache");
      }
}

bool cH_Spezialgebiet::is_cached(const std::string s)
{
  cH_Spezialgebiet *cached(cache.lookup(s));
  if(cached) return true;
  return false;
}

cH_Spezialgebiet::cH_Spezialgebiet(const Tag *tag)
{*this=cH_Spezialgebiet(new Spezialgebiet(tag));
 cache.Register(tag->getAttr("Name"),*this);
}

Spezialgebiet::Spezialgebiet(const Tag *tag) 
: nr(tag->getIntAttr("MAGUS-Index",tag->getIntAttr("MCG-Index")))
	, name(tag->getAttr("Name"))
{
 typ=tag->getAttr("Typ");
 spezial=tag->getAttr("Spezialisierung");
 spezial2=tag->getAttr("Sekundärelement");
}


Spezialgebiet_All::Spezialgebiet_All()
{
 const Tag *spezialgebiete=xml_data->find("Spezialgebiete");
 if (spezialgebiete)
 {  Tag::const_iterator b=spezialgebiete->begin(),e=spezialgebiete->end();
    FOR_EACH_CONST_TAG_OF_5(i,*spezialgebiete,b,e,"Spezialgebiet")
       list_All.push_back(cH_Spezialgebiet(&*i));
 }   
}

bool operator==(void *data,const cH_Spezialgebiet &t)
{  
cout << "SPEZ=" <<static_cast<Spezialgebiet*>(data)->Name()<<' '<< t->Name()<<'\n';
 return *(static_cast<Spezialgebiet*>(data))==*t;
}


