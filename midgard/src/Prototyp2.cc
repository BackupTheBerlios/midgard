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

#include "Prototyp2.hh"
#include <cstring>
#include <Gtk_OStream.h>
#include <Misc/itos.h>

class NotFound : public std::exception
{public:
   virtual const char* what() const throw() { return "NotFound"; }
};



double Prototyp2::fac_for(const std::string &art, const std::string &name, const std::vector<cH_Prototyp2> &A)
{
  int count=0;
  double facsum=0;
  for(std::vector<cH_Prototyp2>::const_iterator i=A.begin();i!=A.end();++i)
   {
     std::vector<st_protolisten> PL;
     if     (art=="Z") PL=(*i)->LZauber();
     else if(art=="F") PL=(*i)->LFertigkeiten();
     else {cerr << "Art = "<<art<<'\n'; assert(!"Art nicht definiert");}
     std::vector<st_protolisten>::const_iterator j=find(PL.begin(),PL.end(),name);
     if(j!=PL.end())
      {
        ++count;
        facsum+=j->fac;
      }
   }
  if(count) return facsum/count; 
  else return 10.0; // groﬂer Wert
}


   

cH_Prototyp2::cache_t cH_Prototyp2::cache;

cH_Prototyp2::cH_Prototyp2(const std::string& name,bool create)
{
 cH_Prototyp2 *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  cerr << "Prototyp2 '" << name << "' nicht im Cache\n";
  if (create)
  {  static Tag t2("Prototyp2"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Name",name);
     *this=cH_Prototyp2(&t2);
  }
  else throw NotFound();
  }
}

cH_Prototyp2::cH_Prototyp2(const Tag *tag)
{*this=cH_Prototyp2(new Prototyp2(tag));
 cache.Register(tag->getAttr("Name"),*this);
}

Prototyp2::Prototyp2(const Tag *tag)
{
  assert(tag);
  name=tag->getAttr("Name"); // Info, Wissen, Natur, ....
  FOR_EACH_CONST_TAG_OF(i,*tag,"Eigenschaft")
    {
      std::string art=i->getAttr("Art");
      if     (art=="Z") lzauber.push_back(st_protolisten(
                    i->getAttr("Name"),i->getFloatAttr("Faktor")));
      else if(art=="F") lfertigkeiten.push_back(st_protolisten(
                    i->getAttr("Name"),i->getFloatAttr("Faktor")));
      else {cerr << "Art = "<<art<<'\n'; assert(!"Art nicht definiert");}
    }

}

Prototyp2_All::Prototyp2_All()
{
 const Tag *ki=xml_data->find("KI");

 if (ki)
 {  Tag::const_iterator b=ki->begin(),e=ki->end();
    FOR_EACH_CONST_TAG_OF_5(i,*ki,b,e,"Prototyp2")
    {  list_All.push_back(cH_Prototyp2(&*i));
    }
 }
}  


