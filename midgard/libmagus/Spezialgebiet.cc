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
#include <iostream>
#include <Misc/Tag.h>

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

Spezialgebiet::Spezialgebiet(const Tag &tag) 
: nr(tag.getIntAttr("MAGUS-Index",tag.getIntAttr("MCG-Index")))
	, name(tag.getAttr("Name"))
{
 typ=tag.getAttr("Typ");
 spezial=tag.getAttr("Spezialisierung");
 spezial2=tag.getAttr("Sekundärelement");
}

bool operator==(void *data,const cH_Spezialgebiet &t)
{  
std::cout << "SPEZ=" <<static_cast<Spezialgebiet*>(data)->Name()<<' '<< t->Name()<<'\n';
 return *(static_cast<Spezialgebiet*>(data))==*t;
}

cH_Spezialgebiet cH_Spezialgebiet::load(const Tag &t)
{  cH_Spezialgebiet *res=cache.lookup(t.getAttr("Name"));
   assert (!res);
   {  cH_Spezialgebiet r2=new Spezialgebiet(t);
      cache.Register(t.getAttr("Name"),r2);
      return r2;
   }
}

void Spezialgebiet_All::load(std::vector<cH_Spezialgebiet> &list,const Tag &t)
{  list.push_back(cH_Spezialgebiet::load(t));
}

