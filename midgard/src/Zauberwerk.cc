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
#include "midgard_CG.hh"
#include "Typen.hh"
#include "ProgressBar.h"


cH_Zauberwerk::cache_t cH_Zauberwerk::cache;

cH_Zauberwerk::cH_Zauberwerk(const std::string& name,const std::string& art,
		const std::string& stufe IF_XML(,bool create))
{
 st_index index(name,art,stufe);
 cH_Zauberwerk *cached(cache.lookup(index));
 if (cached) *this=*cached;
 else
  {
  cerr << "Zauberwerk '" << name << "' nicht im Cache\n";
  if (create)
  {  static Tag t2("Zauberwerk"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Name",name);
     t2.setAttr("Art",art);
     t2.setAttr("Stufe",stufe);
     *this=cH_Zauberwerk(&t2);
  }
  else throw NotFound();
  }
}

cH_Zauberwerk::cH_Zauberwerk(const Tag *tag)
{*this=cH_Zauberwerk(new Zauberwerk(tag));
 cache.Register(st_index(tag->getAttr("Name"),tag->getAttr("Art"),
 		tag->getAttr("Stufe")),*this);
}

void Zauberwerk::get_Zauberwerk()
{
   assert(tag);
   kosten=tag->getIntAttr("Kosten");
   zeitaufwand=tag->getAttr("Zeitaufwand");
   preis=tag->getAttr("Geldaufwand");
   region=tag->getAttr("Region");

    FOR_EACH_CONST_TAG_OF(i,*tag,"regionaleBesonderheit")
         VAusnahmen.push_back(st_ausnahmen(i->getAttr("Herkunft"),
                              i->getAttr("Spezies"),
                              i->getAttr("Typ"),
                              i->getAttr("Beruf"),
                              i->getAttr("Stand"),
                              i->getAttr("Standard")));
}

void Zauberwerk::getVoraussetzungen()
{
   assert(tag);
   FOR_EACH_CONST_TAG_OF(i,*tag,"Voraussetzung")
   {  if (i->getAttr("Zauber").empty()) continue;
      vec_vor.push_back(st_vor(i->getAttr("Zauber"),i->getAttr("Verbindung")));
   }
}

void Zauberwerk::getVoraussetzungenFert()
{
   assert(tag);
   FOR_EACH_CONST_TAG_OF(i,*tag,"Voraussetzung")
   {  if (i->getAttr("Fertigkeit").empty()) continue;
      vec_vorF.push_back(st_vor(i->getAttr("Fertigkeit"),""));
   }
}



bool Zauberwerk::Voraussetzungen(const std::list<cH_MidgardBasicElement>& listZauber) const
{
 if(vec_vor.size()==0) return true; // Keine Voraussetzung
 std::map<std::string,bool> mapB;
 for(std::vector<st_vor>::const_iterator i=vec_vor.begin();i!=vec_vor.end();++i)
  {
    mapB[i->voraussetzung]=false;   
    for(std::list<cH_MidgardBasicElement>::const_iterator j=listZauber.begin();j!=listZauber.end();++j)
     {
      // Nur EINE Voraussetzung
      if((*j)->Name()==i->voraussetzung && vec_vor.size()==1) return true;
      // Nur EINE von mehreren Voraussetzung nötig
      else if((*j)->Name()==i->voraussetzung && i->op=="or") return true;
      // Mehrere Voraussetzungen nötig
      else if ((*j)->Name()==i->voraussetzung) mapB[i->voraussetzung]=true;
     }
  }
 for(std::map<std::string,bool>::const_iterator i=mapB.begin();i!=mapB.end();++i)
   if(i->second==false) return false;
 return true;
}

bool Zauberwerk::Voraussetzungen_Fertigkeit(const std::list<cH_MidgardBasicElement>& listFert) const
{
 if(vec_vorF.size()==0) return true; // Keine Voraussetzung
 std::map<std::string,bool> mapB;
 for(std::vector<st_vor>::const_iterator i=vec_vorF.begin();i!=vec_vorF.end();++i)
  {
    mapB[i->voraussetzung]=false;   
    for(std::list<cH_MidgardBasicElement>::const_iterator j=listFert.begin();j!=listFert.end();++j)
     {
      // Nur EINE Voraussetzung
      if((*j)->Name()==i->voraussetzung && vec_vorF.size()==1) return true;
      // Nur EINE von mehreren Voraussetzung nötig
      else if((*j)->Name()==i->voraussetzung && i->op=="or") return true;
      // Mehrere Voraussetzungen nötig
      else if ((*j)->Name()==i->voraussetzung) mapB[i->voraussetzung]=true;
     }
  }
 for(std::map<std::string,bool>::const_iterator i=mapB.begin();i!=mapB.end();++i)
   if(i->second==false) return false;
 return true;
}


Zauberwerk_All::Zauberwerk_All(Gtk::ProgressBar *progressbar)
{
 const Tag *zauberwerke=xml_data->find("Zauberwerke");
 if (!zauberwerke)
    cerr << "<Zauberwerke><Zauberwerk/>... nicht gefunden\n";
 else
 {  Tag::const_iterator b=zauberwerke->begin(),e=zauberwerke->end();
    double size=e-b;
    FOR_EACH_CONST_TAG_OF_5(i,*zauberwerke,b,e,"Zauberwerk")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
// warum sowas? siehe Zauber.pgcc
       list_All.push_back(&*(cH_Zauberwerk(&*i)));
    }
 }
 ProgressBar::set_percentage(progressbar,1);
}


