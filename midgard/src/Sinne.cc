/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2002      Christof Petig 
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

#include "Sinne.hh"

cH_Sinne::cache_t cH_Sinne::cache;

cH_Sinne::cH_Sinne(const std::string& name IF_XML(,bool create))
{
 cH_Sinne *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  cerr << "Sinne '" << name << "' nicht im Cache\n";
  if (create)
  {  static Tag t2("Sinne"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Name",name);
     *this=cH_Sinne(&t2);
  }
  else throw NotFound();
  }
}

cH_Sinne::cH_Sinne(const Tag *tag)
{*this=cH_Sinne(new Sinne(tag));
 cache.Register(tag->getAttr("Name"),*this);
}

void Sinne::get_Sinne()
{
 if(Name()=="Sechster Sinn") erfolgswert=0;
 else                      erfolgswert=8;
}


Sinne_All::Sinne_All()
{
  list_All.push_back(&*(cH_Sinne("Sehen",true)));
  list_All.push_back(&*(cH_Sinne("Hören",true)));
  list_All.push_back(&*(cH_Sinne("Riechen",true)));
  list_All.push_back(&*(cH_Sinne("Schmecken",true)));
  list_All.push_back(&*(cH_Sinne("Tasten",true)));
  list_All.push_back(&*(cH_Sinne("Sechster Sinn",true)));
}
