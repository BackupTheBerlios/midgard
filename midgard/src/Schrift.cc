/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include "Schrift.hh"
#include "Sprache.hh"
#include <cstring>
#include <Gtk_OStream.h>
#include <Misc/itos.h>
#include "ProgressBar.h"
#include "Grundwerte.hh"

cH_Schrift::cache_t cH_Schrift::cache;

cH_Schrift::cH_Schrift(const std::string& name IF_XML(,bool create))
{
 cH_Schrift *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
 cerr << "Schrift '" << name << "' nicht im Cache\n";
  if (create)
  {  static Tag t2("Schrift"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Name",name);
     t2.setAttr("Typ","?");
     *this=cH_Schrift(name, &t2);
  }
  else throw NotFound();
  }
}

cH_Schrift::cH_Schrift(const std::string& name,const Tag *tag)
{*this=cH_Schrift(new Schrift(name,tag));  
 cache.Register(name,*this);
}


void Schrift::get_Schrift()
{
  assert(tag);
  art_der_schrift=tag->getAttr("Name");
  region=tag->getAttr("Region");
  region_zusatz=tag->getAttr("RegionZusatz");
  kosten=tag->getIntAttr("Kosten");
  alt=tag->getBoolAttr("alte_Schrift");
  kult=tag->getBoolAttr("Kultschrift");;
}

bool Schrift::kann_Sprache(const std::list<MidgardBasicElement_mutable>& sprache) const
{
 for(std::list<MidgardBasicElement_mutable>::const_iterator i=sprache.begin();i!=sprache.end();++i)
  {
   vector<std::string> V=cH_Sprache(*i)->Schrift();
   for(vector<std::string>::const_iterator j=V.begin();j!=V.end();++j)
      if(*j==Name()) return true ;
  }  
 return false;
}

int Schrift::MaxErfolgswert(const Grundwerte& w,const vector<cH_Typen>& Typ) const
{
  if(w.In() < 61) return 14; 
  return cH_Fertigkeit("Schreiben")->MaxErfolgswert(w,Typ) ;
}

std::list<cH_MidgardBasicElement> Schrift::gleicheSchrift(const std::list<cH_MidgardBasicElement>& listSchrift) const
{
  std::list<cH_MidgardBasicElement> LS;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=listSchrift.begin();i!=listSchrift.end();++i)
     if(cH_Schrift(*i)->Art_der_Schrift()==Art_der_Schrift()) 
        LS.push_back(*i);
  return LS;
}

bool Schrift::Mutterschrift(cH_Land herkunft,cH_Spezies spezies) const
{
  std::vector<std::string> V=herkunft->Sprachen();
  for(std::vector<std::string>::const_iterator i=V.begin();i!=V.end();++i)
   {
     const std::vector<std::string> W=cH_Sprache(*i)->Schrift();
     for(std::vector<std::string>::const_iterator j=W.begin();j!=W.end();++j)
      {
       if(spezies->Name()=="Waldgnom" && Name()=="Zwergenrunen Futhark") return false;
       if(spezies->Name()=="Berggnom" && Name()=="Baumrunen Beth-Luis-Nion") return false;
       if(*j==Name()) return true;
      }
   }
  return false;
}


Schriften_All::Schriften_All(Gtk::ProgressBar *progressbar)
{
 const Tag *schriften=xml_data->find("Schriften");
 if (schriften)
 {  Tag::const_iterator b=schriften->begin(),e=schriften->end();
    double size=e-b;
    FOR_EACH_CONST_TAG_OF_5(i,*schriften,b,e,"Schrift")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
       FOR_EACH_CONST_TAG_OF(j,*i,"Variante")
          list_All.push_back(&*(cH_Schrift(j->getAttr("Name"),&*i)));
    }
 }   

 ProgressBar::set_percentage(progressbar,1);
}  
