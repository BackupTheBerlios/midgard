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

#include "Region.hh"
#include "NotFound.h"
#include <iostream>
#include <Misc/Tag.h>
#include "xml.h"

cH_Region::cache_t cH_Region::cache;

cH_Region::cH_Region(const std::string& name,bool create)
{
 cH_Region *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else if (create)
  { Tag t2("Region");
    t2.setAttr("Name",name);
    t2.setAttr("Region",name);
    *this=new Region(t2);
  }
 else
  {
  std::cerr << "Region '" << name << "' nicht im Cache\n";
  throw NotFound();
  }
}

Region::Region(const Tag &tag, const std::string &_file) 
: name(tag.getAttr("Name"))
{
  nr=tag.getIntAttr("MAGUS-Index");
  titel=tag.getAttr("Titel");
  abkuerzung=tag.getAttr("Region");
  file=_file;
  url=tag.getAttr("URL");
  maintainer=tag.getAttr("Maintainer");
  version=tag.getAttr("Version");
  copyright=tag.getAttr("Copyright");
  jahr=tag.getAttr("Jahr");
  offiziell=tag.getBoolAttr("offiziell");
  pic=RegionenPic_enum::epic(tag.getIntAttr("MAGUS-Bild",tag.getIntAttr("MCG-Bild")));
}

cH_Region Regionen_All::getRegionfromAbk(const std::vector<cH_Region>& V,const std::string& r)
{
 for(std::vector<cH_Region>::const_iterator i=V.begin();i!=V.end();++i)
  {
   if(r==(*i)->Abkuerzung()) 
    {
      if((*i)->Nr()<0) return cH_Region("",true); // DFR und Arkanum gelten NICHT als Regionen
      return (*i);
    }
  }
 return cH_Region("???",true);
// assert(!"Region nicht gefunden\n");
// abort(); // never get here
}

cH_Region cH_Region::load(const Tag &t, const std::string &file)
{  cH_Region *res=cache.lookup(t.getAttr("Name"));
   assert (!res);
      cH_Region r2=new Region(t,file);
      cache.Register(t.getAttr("Name"),r2);
      return r2;
}

void Regionen_All::load(std::vector<cH_Region> &list,const Tag &t, const std::string &file)
{  list.push_back(cH_Region::load(t,file));
}
