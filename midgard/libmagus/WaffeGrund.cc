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

#include "WaffeGrund.hh"
#include "Typen.hh"
#include "LernListen.hh"
#include "Waffe.hh"
#include "NotFound.h"
#include "Ausgabe.hh"

cH_WaffeGrund::cache_t cH_WaffeGrund::cache;

cH_WaffeGrund::cH_WaffeGrund(const std::string& name ,bool create)
{
 cH_WaffeGrund *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  Ausgabe(Ausgabe::Warning, "Waffengrundfert. '" + name + "' nicht im Cache");
  if (create)
  {  Tag t2("Waffen-Grundkenntnis");
     t2.setAttr("Name",name);
     *this=new WaffeGrund(t2);
  }
  else throw NotFound(name);
  }
}

void WaffeGrund::get_WaffeGrund(const Tag &t)
{  if (t.hasAttr("Kosten")) 
   { kosten=t.getIntAttr("Kosten");
     region=t.getAttr("Region");
   }
}

bool WaffeGrund::is_sinnvoll(const std::list<cH_MidgardBasicElement> &WL,
                             const Abenteurer &A,const LernListen &LL) const
{
  for(std::list<cH_MidgardBasicElement>::const_iterator i=WL.begin();i!=WL.end();++i)
   {
     if(cH_Waffe(*i)->Grundkenntnis()==Name())
      {
//cout << (*i)->Name()<<'\t'<<cH_Waffe(*i)->Grundkenntnis()<<'\t'<<Name()<<'\t'
//<<(*i)->Voraussetzung(A,false)<<'\n';
        if(!LL.region_check((*i)->Region())) continue;
        if((*i)->Voraussetzung(A,false)) return true;
      }
   }
  return false;
}

WaffeGrund::WaffeGrund(const Tag &t)
      : MidgardBasicElement(t.getAttr("Name"))
{ load(t);
}

void WaffeGrund::load(const Tag &t)
{get_WaffeGrund(t);get_map_typ(t);
}

cH_WaffeGrund cH_WaffeGrund::load(const Tag &t,bool &is_new)
{  cH_WaffeGrund *res=cache.lookup(t.getAttr("Name"));
   if (!res)
   {  cH_WaffeGrund r2=new WaffeGrund(t);
      is_new=true;
      cache.Register(t.getAttr("Name"),r2);
      return r2;
   }
   else 
   {  const_cast<WaffeGrund&>(**res).load(t);
      return *res;
   }
}

void WaffeGrund_All::load(std::list<cH_MidgardBasicElement> &list,const Tag &t)
{  bool is_new=false;
   cH_WaffeGrund z=cH_WaffeGrund::load(t,is_new);
   // das &* dient dazu um aus einem cH_WaffeGrund ein cH_MBE zu machen
   if (is_new) list.push_back(&*z);
}

