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

#include "Fertigkeiten_angeboren.hh"
#include "Abenteurer.hh"
#include <Misc/Tag.h>
#include "NotFound.h"
#include "Ausgabe.hh"

cH_Fertigkeit_angeborene::cache_t cH_Fertigkeit_angeborene::cache;

cH_Fertigkeit_angeborene::cH_Fertigkeit_angeborene(const std::string& name ,bool create)
{
 cH_Fertigkeit_angeborene *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  Ausgabe(Ausgabe::Warning, "angeborene Fertigkeit '" + name + "' nicht im Cache");
  if (create)
  {  Tag t2("angeboreneFertigkeit"); 
     t2.setAttr("Name",name);
     *this=new Fertigkeit_angeborene(t2);
  }
  else throw NotFound(name);
  }
}

void Fertigkeit_angeborene::get_Fertigkeit(const Tag &t)
{
 min=t.getIntAttr("Min");
 max=t.getIntAttr("Max");
 anfangswert=t.getIntAttr("Wert");
}

int Fertigkeit_angeborene::FErfolgswert(const Abenteurer &a,const MBEmlt &mbem) const
{
  if(Name()=="Trinken") return mbem->Erfolgswert()+a.Ko()/10;
  if(Name()=="Berserkergang") return mbem->Erfolgswert()-a.Wk()/5;
  return mbem->Erfolgswert();
}

Fertigkeit_angeborene::Fertigkeit_angeborene(const Tag &t)
         : MidgardBasicElement(t.getAttr("Name")),min(),max() 
{get_Fertigkeit(t);}

cH_Fertigkeit_angeborene cH_Fertigkeit_angeborene::load(const Tag &t)
{  cH_Fertigkeit_angeborene *res=cache.lookup(t.getAttr("Name"));
   assert (!res);
   {  cH_Fertigkeit_angeborene r2=new Fertigkeit_angeborene(t);
      cache.Register(t.getAttr("Name"),r2);
      return r2;
   }
}

void Fertigkeiten_angeborene_All::load(std::list<cH_MidgardBasicElement> &list,const Tag &t)
{  cH_Fertigkeit_angeborene z=cH_Fertigkeit_angeborene::load(t);
   // das &* dient dazu um aus einem cH_Fertigkeit_angeborene ein cH_MBE zu machen
   list.push_back(&*z);
}

