/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

#include "Land.hh"
#include "ProgressBar.h"
#include "MidgardBasicElement.hh" // für NotFound
#include "Abenteurer.hh"

cH_Land::cache_t cH_Land::cache;

cH_Land::cH_Land(const std::string& name IF_XML(,bool create))
{
 cH_Land *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  cerr << "Land '" << name << "' nicht im Cache\n";
  if (create || name.empty()) // don t ask me ... it just works this way ...
  {  static Tag t2("Land"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Name",name);
     *this=cH_Land("?",&t2);
  }
  else throw NotFound();
  }
}

bool Land::ist_erlaubt(const VAbenteurer& A) const
{
  std::vector<std::string> V=A.getWerte().Spezies()->getVHerkunft();
  if(V.empty()) // Keine Herkunftsvorgabe aufgrund der Spezies
   { 
     std::vector<cH_Typen> Typ=A.getVTyp();
     for(std::vector<cH_Typen>::const_iterator i=Typ.begin();i!=Typ.end();++i)
      {
        const std::vector<Typen::st_herkunft> V=(*i)->get_vec_herkunft();
        for(std::vector<Typen::st_herkunft>::const_iterator j=V.begin();j!=V.end();++j)
         {
           if(j->land==Name()) return true;
         }
      }
   }
  else
   {
     if(find(V.begin(),V.end(),Name())!=V.end()) return true;
   }
  return false;
}


cH_Land::cH_Land(const std::string& kontinent,const Tag *tag)
{
   *this=cH_Land(new Land(kontinent,tag));
   cache.Register(tag->getAttr("Name"),*this);
}

Land::Land(const std::string& _kontinent, const Tag *tag)
  : name(tag->getAttr("Name")), kontinent(_kontinent)
{  FOR_EACH_CONST_TAG_OF(i,*tag,"Sprache")
      vec_sprache.push_back(i->getAttr("Name"));
   FOR_EACH_CONST_TAG_OF(i,*tag,"Nachbarland")
      nachbarlaender.push_back(i->getAttr("Name"));
}

Laender_All::Laender_All(Gtk::ProgressBar *progressbar)
{
 const Tag *Laender=xml_data->find("Länder");
 if (Laender)
 {  Tag::const_iterator b=Laender->begin(),e=Laender->end();
    double size=(e-b);
    FOR_EACH_CONST_TAG_OF_5(i,*Laender,b,e,"Kontinent")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
       FOR_EACH_CONST_TAG_OF(j,*i,"Land")
          list_All.push_back(cH_Land(i->getAttr("Name"),&*j));
    }
 }
 ProgressBar::set_percentage(progressbar,1);
}
