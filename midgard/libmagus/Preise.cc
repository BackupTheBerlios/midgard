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

#include "NotFound.h"
#include "Preise.hh"
#include <Misc/itos.h>
#include <fstream>
#include <Misc/TagStream.h>
#include "magus_paths.h"
#include "Datenbank.hh"
#include "Ausgabe.hh"

bool operator!=(const cH_Preise &a, const std::string &b)
{  return a->Name()!=b; }

cH_Preise::cache_t cH_Preise::cache;

cH_Preise::cH_Preise(const std::string& name ,bool create)
{
 cH_Preise *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  Ausgabe(Ausgabe::Warning, "Preis '" + name + "' nicht im Cache");
  if (create)
  {  Tag t2("Kaufpreis"); 
     t2.setAttr("Ware",name);
     t2.setAttr("Art","?");
     t2.setAttr("Art2","?");
     *this=new Preise(t2);
  }
  else throw NotFound(name);
  }
}

void Preise::get_Preise(const Tag &tag)
{
  art2=tag.getAttr("Art2");
  einheit=tag.getAttr("Währung");
  kosten=tag.getFloatAttr("Preis");
  gewicht=tag.getFloatAttr("Gewicht");
  region=tag.getAttr("Region");
  beschreibung=tag.getAttr("Beschreibung");
  ruestung=tag.getBoolAttr("Rüstung_ohne_Gewicht");
  if(kosten<0) {kosten=0; unverkauflich=true;}
}

cH_Preise cH_Preise::load(const Tag &t,bool &is_new)
{  cH_Preise *res=cache.lookup(t.getAttr("Name"));
   if (!res)
   {  cH_Preise r2=new Preise(t);
      is_new=true;
      cache.Register(t.getAttr("Ware"),r2);
      return r2;
   }
   else 
   {  const_cast<Preise&>(**res).load(t);
      return *res;
   }
}

void Preise_All::load(std::list<cH_Preise> &list,const Tag &t)
{  bool is_new=false;
   cH_Preise z=cH_Preise::load(t,is_new);
   if (is_new) list.push_back(z);
}

//////////////////////////////////////////////////////////////////////

cH_PreiseNewMod::cache_t cH_PreiseNewMod::cache;

cH_PreiseNewMod::cH_PreiseNewMod(const std::string& name, bool create)
{
 cH_PreiseNewMod *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {  
  Ausgabe(Ausgabe::Warning, "PreiseNewMod '" + name + "' nicht im Cache");
  if (create)
  {  
     Tag t2("Art");
     t2.setAttr("Name",name);
     *this=new PreiseNewMod(t2);
  }
  else throw NotFound(name);
  }
}


void PreiseNewMod::getPNM(const Tag &t)
{
  name=t.getAttr("Name");
  FOR_EACH_CONST_TAG_OF(i,t,"Variante")
   {
    std::string variante=i->getAttr("Name");
     FOR_EACH_CONST_TAG_OF(j,*i,variante)
      {
       VS[variante].push_back(st_preismod(j->getAttr("Spezifikation"),
                                 j->getFloatAttr("PreisFaktor")));
      }
   }
}

PreiseNewMod::PreiseNewMod(const Tag &t)
{ load(t); }

void PreiseNewMod::load(const Tag &t)
{ getPNM(t); }

cH_PreiseNewMod cH_PreiseNewMod::load(const Tag &t,bool &is_new)
{  cH_PreiseNewMod *res=cache.lookup(t.getAttr("Name"));
   if (!res)
   {  cH_PreiseNewMod r2=new PreiseNewMod(t);
      is_new=true;
      cache.Register(t.getAttr("Name"),r2);
      return r2;
   }
   else 
   {  const_cast<PreiseNewMod&>(**res).load(t);
      return *res;
   }
}

void PreiseNewMod_All::load(std::vector<cH_PreiseNewMod> &list,const Tag &t)
{  bool is_new=false;
   cH_PreiseNewMod z=cH_PreiseNewMod::load(t,is_new);
   if (is_new) list.push_back(z);
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

   cH_Preise::cache.Register(name,new Preise(name,art,TeA));

   TagStream ts;
   ts.setEncoding("ISO-8859-1");
   ts.setContent(RootTag);
   ts.write(datei);
}

Preise::Preise(const Tag &_tag)
     : name(_tag.getAttr("Ware")), art(_tag.getAttr("Art")),   
      unverkauflich()
{load(_tag);}

void Preise::load(const Tag &_tag)
{get_Preise(_tag);}

Preise::Preise(const std::string& _name, const std::string& _art, const Tag &_tag)
     : name(_name), art(_art), unverkauflich()
{get_Preise(_tag);}
