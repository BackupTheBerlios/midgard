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

#include "Prototyp.hh"
#include <cstring>
#include <Misc/itos.h>
#include "Enums.hh"
#include "Prozente100.hh"
#include "NotFound.h"
#include <Misc/Tag.h>
#include "Ausgabe.hh"

cH_Prototyp::cache_t cH_Prototyp::cache;

cH_Prototyp::cH_Prototyp(const std::string& name,bool create)
{
 cH_Prototyp *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  Ausgabe(Ausgabe::Warning, "Prototyp '" + name + "' nicht im Cache");
  if (create)
  {  Tag t2("Prototyp"); 
     t2.setAttr("Name",name);
     *this=new Prototyp(t2);
  }
  else throw NotFound(name);
  }
}

Prototyp::Prototyp(const Tag &tag)
{
  name=tag.getAttr("Name");;
  fertigkeit = tag.getIntAttr("Fertigkeit");
  waffe = tag.getIntAttr("Waffen");
  waffe_grund = tag.getIntAttr("WaffenGrund");
  zauber = tag.getIntAttr("Zauber");
  zauberwerk = tag.getIntAttr("Zauberwerk");
  sprache = tag.getIntAttr("Sprache");
  schrift = tag.getIntAttr("Schrift");
  fert_spez = tag.getIntAttr("FertSpezialist");
  waff_spez = tag.getIntAttr("WaffSpezialist");
  spra_spez = tag.getIntAttr("SpraSpezialist");
  schr_spez = tag.getIntAttr("SchrSpezialist");
}

void Prototyp::setLast(const Prozente100 &p100)
{
  cH_Prototyp P("Letzte Einstellung",true);
  P->fertigkeit = p100.get(MidgardBasicElement::FERTIGKEIT);
  P->waffe = p100.get(MidgardBasicElement::WAFFE);
  P->waffe_grund = p100.get(MidgardBasicElement::WAFFEGRUND);
  P->zauber = p100.get(MidgardBasicElement::ZAUBER);
  P->zauberwerk = p100.get(MidgardBasicElement::ZAUBERWERK);
  P->sprache = p100.get(MidgardBasicElement::SPRACHE);
  P->schrift = p100.get(MidgardBasicElement::SCHRIFT);
  P->fert_spez = p100.getS(MidgardBasicElement::FERTIGKEIT);
  P->waff_spez = p100.getS(MidgardBasicElement::WAFFE);
  P->spra_spez = p100.getS(MidgardBasicElement::SPRACHE);
  P->schr_spez = p100.getS(MidgardBasicElement::SCHRIFT);
}

cH_Prototyp cH_Prototyp::load(const Tag &t)
{  cH_Prototyp *res=cache.lookup(t.getAttr("Name"));
   assert (!res);
   {  cH_Prototyp r2=new Prototyp(t);
      cache.Register(t.getAttr("Name"),r2);
      return r2;
   }
}

void Prototyp_All::load(std::list<cH_Prototyp> &list,const Tag &t)
{  list.push_back(cH_Prototyp::load(t));
}

