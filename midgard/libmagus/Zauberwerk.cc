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

#include "Zauberwerk.hh"
#include "Typen.hh"
#include <iostream>

cH_Zauberwerk::cache_t cH_Zauberwerk::cache;

cH_Zauberwerk::cH_Zauberwerk(const std::string& name,const std::string& art,
		const std::string& stufe ,bool create)
{
 st_index index(name,art,stufe);
 cH_Zauberwerk *cached(cache.lookup(index));
 if (cached) *this=*cached;
 else
  {
  std::cerr << "Zauberwerk '" << name << "' nicht im Cache\n";
  if (create)
  {  static Tag t2("Zauberwerk"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Name",name);
     t2.setAttr("Art",art);
     t2.setAttr("Stufe",stufe);
     *this=new Zauberwerk(t2);
  }
  else throw NotFound();
  }
}

void Zauberwerk::get_Zauberwerk(const Tag &t)
{
  if (t.hasAttr("Kosten"))
  {kosten=t.getIntAttr("Kosten");
   zeitaufwand=t.getAttr("Zeitaufwand");
   preis=t.getAttr("Geldaufwand");
   region=t.getAttr("Region");
   region_zusatz=t.getAttr("RegionZusatz");
  }

    FOR_EACH_CONST_TAG_OF(i,t,"regionaleBesonderheit")
         VAusnahmen.push_back(st_ausnahmen(i->getAttr("Herkunft"),
                              i->getAttr("Spezies"),
                              i->getAttr("Typ"),
                              i->getAttr("Beruf"),
                              i->getAttr("Stand"),
                              i->getAttr("Standard")));
}

void Zauberwerk::getVoraussetzungen(const Tag &t)
{
   FOR_EACH_CONST_TAG_OF(i,t,"Voraussetzung")
   {  if (i->getAttr("Zauber").empty()) continue;
      vec_vor.push_back(st_vor(i->getAttr("Zauber"),i->getAttr("Verbindung")));
   }
}

void Zauberwerk::getVoraussetzungenFert(const Tag &t)
{
   FOR_EACH_CONST_TAG_OF(i,t,"Voraussetzung")
   {  if (i->getAttr("Fertigkeit").empty()) continue;
      vec_vorF.push_back(st_vor(i->getAttr("Fertigkeit"),""));
   }
}



bool Zauberwerk::Voraussetzungen(const std::list<MBEmlt>& listZauber) const
{
 if(vec_vor.size()==0) return true; // Keine Voraussetzung
 std::map<std::string,bool> mapB;
 for(std::vector<st_vor>::const_iterator i=vec_vor.begin();i!=vec_vor.end();++i)
  {
    mapB[i->voraussetzung]=false;   
    for(std::list<MBEmlt>::const_iterator j=listZauber.begin();j!=listZauber.end();++j)
     {
      // Nur EINE Voraussetzung
      if((*(*j))->Name()==i->voraussetzung && vec_vor.size()==1) return true;
      // Nur EINE von mehreren Voraussetzung nötig
      else if((*(*j))->Name()==i->voraussetzung && i->op=="or") return true;
      // Mehrere Voraussetzungen nötig
      else if ((*(*j))->Name()==i->voraussetzung) mapB[i->voraussetzung]=true;
     }
  }
 for(std::map<std::string,bool>::const_iterator i=mapB.begin();i!=mapB.end();++i)
   if(i->second==false) return false;
 return true;
}

bool Zauberwerk::Voraussetzungen_Fertigkeit(const std::list<MBEmlt>& listFert) const
{
 if(vec_vorF.size()==0) return true; // Keine Voraussetzung
 std::map<std::string,bool> mapB;
 for(std::vector<st_vor>::const_iterator i=vec_vorF.begin();i!=vec_vorF.end();++i)
  {
    mapB[i->voraussetzung]=false;   
    for(std::list<MBEmlt>::const_iterator j=listFert.begin();j!=listFert.end();++j)
     {
      // Nur EINE Voraussetzung
      if((*(*j))->Name()==i->voraussetzung && vec_vorF.size()==1) return true;
      // Nur EINE von mehreren Voraussetzung nötig
      else if((*(*j))->Name()==i->voraussetzung && i->op=="or") return true;
      // Mehrere Voraussetzungen nötig
      else if ((*(*j))->Name()==i->voraussetzung) mapB[i->voraussetzung]=true;
     }
  }
 for(std::map<std::string,bool>::const_iterator i=mapB.begin();i!=mapB.end();++i)
   if(i->second==false) return false;
 return true;
}


Zauberwerk_All::Zauberwerk_All()
{
#if 0
 const Tag *zauberwerke=xml_data->find("Zauberwerke");
 if (!zauberwerke)
    std::cerr << "<Zauberwerke><Zauberwerk/>... nicht gefunden\n";
 else
 {  Tag::const_iterator b=zauberwerke->begin(),e=zauberwerke->end();
    FOR_EACH_CONST_TAG_OF_5(i,*zauberwerke,b,e,"Zauberwerk")
    {  
// warum sowas? siehe Zauber.pgcc
       list_All.push_back(&*(cH_Zauberwerk(&*i)));
    }
 }
#endif
}

Zauberwerk::Zauberwerk(const Tag &t)
      : MidgardBasicElement(t.getAttr("Name")),
      	stufe(t.getAttr("Stufe")),art(t.getAttr("Art")) 
{ load(t);
}

void Zauberwerk::load(const Tag &t)
{  get_Zauberwerk(t);get_map_typ(t);
   getVoraussetzungen(t);getVoraussetzungenFert(t);
}

cH_Zauberwerk cH_Zauberwerk::load(const Tag &t,bool &is_new)
{  st_index index(t.getAttr("Name"),t.getAttr("Art"),t.getAttr("Stufe"));
   cH_Zauberwerk *res=cache.lookup(index);
   if (!res)
   {  cH_Zauberwerk r2=new Zauberwerk(t);
      is_new=true;
      cache.Register(index,r2);
      return r2;
   }
   else 
   {  const_cast<Zauberwerk&>(**res).load(t);
      return *res;
   }
}

void Zauberwerk_All::load(std::list<cH_MidgardBasicElement> &list,const Tag &t)
{  bool is_new=false;
   cH_Zauberwerk z=cH_Zauberwerk::load(t,is_new);
   // das &* dient dazu um aus einem cH_Zauberwerk ein cH_MBE zu machen
   if (is_new) list.push_back(&*z);
}
