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

cH_Sinne::cH_Sinne(const std::string& name,bool create)
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
 if(Name()=="Sechster Sinn") anfangswert=0;
 else                        anfangswert=8;
}


Sinne_All::Sinne_All()
{
  list_All.clear();
  MBEmlt s1(&*cH_Sinne("Sehen",true));
  s1->setErfolgswert(8);
  MBEmlt s2(&*cH_Sinne("Hören",true));
  s2->setErfolgswert(8);
  MBEmlt s3(&*cH_Sinne("Riechen",true));
  s3->setErfolgswert(8);
  MBEmlt s4(&*cH_Sinne("Schmecken",true));
  s4->setErfolgswert(8);
  MBEmlt s5(&*cH_Sinne("Tasten",true));
  s5->setErfolgswert(8);
  MBEmlt s6(&*cH_Sinne("Sechster Sinn",true));
  s6->setErfolgswert(0);
  list_All.push_back(s1);
  list_All.push_back(s2);
  list_All.push_back(s3);
  list_All.push_back(s4);
  list_All.push_back(s5);
  list_All.push_back(s6);
/*
  list_All.push_back(&*(cH_Sinne("Sehen",true)));
  list_All.push_back(&*(cH_Sinne("Hören",true)));
  list_All.push_back(&*(cH_Sinne("Riechen",true)));
  list_All.push_back(&*(cH_Sinne("Schmecken",true)));
  list_All.push_back(&*(cH_Sinne("Tasten",true)));
  list_All.push_back(&*(cH_Sinne("Sechster Sinn",true)));
*/
/*
  // Weil die Sinne gechached sind müssen die Werte explizit gesetzt werden:
  cH_Sinne("Sehen")->setAnfangswert(8);
  cH_Sinne("Hören")->setAnfangswert(8);
  cH_Sinne("Riechen")->setAnfangswert(8);
  cH_Sinne("Schmecken")->setAnfangswert(8);
  cH_Sinne("Tasten")->setAnfangswert(8);
  cH_Sinne("Sechster Sinn")->setAnfangswert(0);
*/
}
