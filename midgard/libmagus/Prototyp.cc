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
#include "Enums.hh"
#include "Prozente100.hh"

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
  std::cerr << "Prototyp '" << name << "' nicht im Cache\n";
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

Prototyp::Prototyp(const Tag *tag)
{
  assert(tag);
  name=tag->getAttr("Name");;
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


void Prototyp::setLast(const Prozente100 &p100)
{
  cH_Prototyp P("Letzte Einstellung",true);
  P->fertigkeit = p100.get(Enums::sFert);
  P->waffe = p100.get(Enums::sWaff);
  P->waffe_grund = p100.get(Enums::sWGru);
  P->zauber = p100.get(Enums::sZaub);
  P->zauberwerk = p100.get(Enums::sZWerk);
  P->sprache = p100.get(Enums::sSpra);
  P->schrift = p100.get(Enums::sSchr);
  P->fert_spez = p100.getS(Enums::sFert);
  P->waff_spez = p100.getS(Enums::sWaff);
  P->spra_spez = p100.getS(Enums::sSpra);
  P->schr_spez = p100.getS(Enums::sSchr);
}
