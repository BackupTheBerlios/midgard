/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2002 Christof Petig
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

#include "Prototyp.hh"
#include <cstring>
#include <Gtk_OStream.h>
#include <Misc/itos.h>

class NotFound : public std::exception
{public:
   virtual const char* what() const throw() { return "NotFound"; }
};
   

cH_Prototyp::cache_t cH_Prototyp::cache;

cH_Prototyp::cH_Prototyp(const std::string& name,bool create)
{
 cH_Prototyp *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  cerr << "Prototyp '" << name << "' nicht im Cache\n";
  if (create)
  {  static Tag t2("Prototyp"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Name",name);
     *this=cH_Prototyp(&t2);
  }
  else throw NotFound();
  }
}

cH_Prototyp::cH_Prototyp(const Tag *tag)
{*this=cH_Prototyp(new Prototyp(tag));
 cache.Register(tag->getAttr("Name"),*this);
}

void Prototyp::get_Prototyp()
{
  assert(tag);
/*
  fertigkeit = tag->getIntAttr("Fertigkeit");
  waffe = tag->getIntAttr("Waffen");
  waffe_grund = tag->getIntAttr("WaffenGrund");
  zauber = tag->getIntAttr("Zauber");
  zauberwerk = tag->getIntAttr("Zauberwerk");
  sprache = tag->getIntAttr("Sprache");
  schrift = tag->getIntAttr("Schrift");
  fert_spez = tag->getIntAttr("FertSpezialist");
  waff_spez = tag->getIntAttr("WaffSpezialist");
  spra_spez = tag->getIntAttr("SpraSpezialist");
  schr_spez = tag->getIntAttr("SchrSpezialist");
*/
  fertigkeit = 45;
  waffe = 20;
  waffe_grund = 0;
  zauber = 0;
  zauberwerk = 0;
  sprache = 20;
  schrift = 15;

  fert_spez = 50;
  waff_spez =  90;
  spra_spez = 50;
  schr_spez = 50;

}

Prototyp_All::Prototyp_All()
{
 const Tag *ki=xml_data->find("KI");

 if (ki)
 {  Tag::const_iterator b=ki->begin(),e=ki->end();
    FOR_EACH_CONST_TAG_OF_5(i,*ki,b,e,"Prototyp")
    {  list_All.push_back(cH_Prototyp(&*i));
    }
 }
}  
