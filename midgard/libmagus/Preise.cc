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

#include "MidgardBasicElement.hh" // nur für NotFound
#include "Preise.hh"
#include <Misc/itos.h>
#include <fstream>
#include <Misc/TagStream.h>
#include <iostream>
#include "magus_paths.h"
#include "Datenbank.hh"

bool operator!=(const cH_Preise &a, const std::string &b)
{  return a->Name()!=b; }


cH_Preise::cache_t cH_Preise::cache;

cH_Preise::cH_Preise(const std::string& name ,bool create)
{
 cH_Preise *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  std::cerr << "Preis '" << name << "' nicht im Cache\n";
  if (create)
  {  static Tag t2("Kaufpreis"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Ware",name);
     t2.setAttr("Art","?");
     t2.setAttr("Art2","?");
     *this=cH_Preise(&t2);
  }
  else throw NotFound();
  }
}

cH_Preise::cH_Preise(const Tag *tag)
{*this=cH_Preise(new Preise(tag));
 cache.Register(tag->getAttr("Ware"),*this);
}

cH_Preise::cH_Preise(const std::string& _name, const std::string& _art, const Tag *tag)
{*this=cH_Preise(new Preise(_name,_art,tag));
 cache.Register(_name,*this);
}

void Preise::get_Preise()
{
  art2=tag->getAttr("Art2");
  einheit=tag->getAttr("Währung");
  kosten=tag->getFloatAttr("Preis");
  gewicht=tag->getFloatAttr("Gewicht");
  region=tag->getAttr("Region");
  beschreibung=tag->getAttr("Beschreibung");
  ruestung=tag->getBoolAttr("Rüstung_ohne_Gewicht");
  if(kosten<0) {kosten=0; unverkauflich=true;}
}

Preise_All::Preise_All(const std::string &filename,Tag &tag_eigene_artikel)
{
 const Tag *preise=xml_data->find("PreiseNeu");
 if(preise)
 {  Tag::const_iterator b=preise->begin(),e=preise->end();
    FOR_EACH_CONST_TAG_OF_5(i,*preise,b,e,"Dinge")
    {  
       list_All.push_back(cH_Preise(&*i));
    }
 }   
 try {
   std::ifstream f(filename.c_str());
   if (!f.good()) {std::cout << "Cannot open " << filename << '\n'; return;}
   TagStream ts(f);
   const Tag *data=ts.find("MAGUS-data");
   if(!data)    
    { std::cout << "Preise konnten nicht geladen werden";
      ts.debug();
      return;
    }
//cout << "LoadTag\t"<<tag_eigene_artikel<<'\n';
  tag_eigene_artikel=*const_cast<Tag*>(data);
//cout << "LoadTag\t"<<tag_eigene_artikel<<'\n';

  const Tag *preise=data->find("Preise");
  if (preise)
   {  
      Tag::const_iterator b=preise->begin(),e=preise->end();
      FOR_EACH_CONST_TAG_OF_5(i,*preise,b,e,"Dinge")
      {  
       list_All.push_back(cH_Preise(&*i));
      }
    }   
 } catch (std::exception &e) { std::cerr << e.what() << '\n'; }
}  
//////////////////////////////////////////////////////////////////////

cH_PreiseNewMod::cache_t cH_PreiseNewMod::cache;

cH_PreiseNewMod::cH_PreiseNewMod(const Tag *tag)
{*this=cH_PreiseNewMod(new PreiseNewMod(tag));  
 cache.Register(tag->getAttr("Name"),*this);
}

cH_PreiseNewMod::cH_PreiseNewMod(const std::string& name, bool create)
{
 cH_PreiseNewMod *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {  
  std::cerr << "PreiseNewMod '" << name << "' nicht im Cache\n";
  if (create)
  {  
     static Tag t2("Spruch");
     // note that this Tag is shared ... works well for now
     t2.setAttr("Name",name);
     *this=cH_PreiseNewMod(&t2);
  }
  else throw NotFound();
  }
}


void PreiseNewMod::getPNM()
{
  name=tag->getAttr("Name");
  FOR_EACH_CONST_TAG_OF(i,*tag,"Variante")
   {
    std::string variante=i->getAttr("Name");
     FOR_EACH_CONST_TAG_OF(j,*i,variante)
      {
       VS[variante].push_back(st_preismod(j->getAttr("Spezifikation"),
                                 j->getFloatAttr("PreisFaktor")));
      }
   }
}

PreiseNewMod_All::PreiseNewMod_All()
{
  const Tag *P=xml_data->find("PreiseNeuMod");
  if(P)
   {
     Tag::const_iterator b=P->begin(),e=P->end();
     FOR_EACH_CONST_TAG_OF_5(i,*P,b,e,"Art")
       list_All.push_back(cH_PreiseNewMod(&*i));
   } 
}

/////////////////////////////////////////////////////////////////////////
// Neuanlegen
/////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <unistd.h>  
#include <Misc/TagStream.h>

// use this tag to determine whether this is a user defined item
//Tag Preise::Tag_eigene_Artikel("Dinge");

void Preise::saveArtikel(const std::string &Filename,Datenbank &db,
     const std::string &art,const std::string &art2,
     const std::string &name,const double &preis, const std::string &einheit,
     const double &gewicht,const std::string &region,const std::string &beschreibung)
{
   std::string filename=magus_paths::MagusVerzeichnis()+"magus_preise.xml";
   std::ofstream datei(filename.c_str());
   if (!datei.good())
#warning logging   
    { // hauptfenster->set_status("Kann die Ausrüstung nicht speichern");
      return;
    }

   Tag &RootTag=db.tag_eigene_artikel;
   Tag *TeA_=RootTag.find("Preise");
   if(!TeA_) TeA_=&RootTag.push_back(Tag("Preise"));

   Tag &TeA=TeA_->push_back(Tag("Dinge"));

   TeA.setAttr("Art",art);
   TeA.setAttr("Art2",art2);
   TeA.setAttr("Ware",name);
   TeA.setAttr("Währung",einheit);
   TeA.setAttr("Preis",dtos(preis));
   TeA.setAttr("Gewicht",dtos(gewicht));
   TeA.setAttr("Region",region);
   TeA.setAttr("Beschreibung",beschreibung);

   cH_Preise(name,art,&TeA);

   TagStream ts;
   ts.setEncoding("ISO-8859-1");
   ts.setContent(RootTag);
   ts.write(datei);
}
