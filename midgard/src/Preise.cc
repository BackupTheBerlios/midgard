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
}

Preise_All::Preise_All()
{
 const Tag *preise=xml_data->find("Preise");
 if (preise)
 {  Tag::const_iterator b=preise->begin(),e=preise->end();
    FOR_EACH_CONST_TAG_OF_5(i,*preise,b,e,"Kaufpreis")
    {  
       list_All.push_back(cH_Preise(&*i));
    }
 }   
 const Tag *waffen=xml_data->find("Waffen");
 if (waffen)
 {  Tag::const_iterator b=waffen->begin(),e=waffen->end();
    FOR_EACH_CONST_TAG_OF_5(i,*waffen,b,e,"Waffe")
    {  
       {  const Tag *preis=i->find("Kaufpreis");
          if (preis) 
             list_All.push_back(cH_Preise(i->getAttr("Name"),"Waffen",&*i));
       }
       FOR_EACH_CONST_TAG_OF(j,*i,"regionaleVariante")
       {  const Tag *preis=i->find("Kaufpreis");
          if (preis)
             list_All.push_back(cH_Preise(j->getAttr("Name"),"Waffen",&*i));
       }
    }
 }   
 const Tag *ruestungen=xml_data->find("Rüstungen");
 if (ruestungen)
 {  Tag::const_iterator b=ruestungen->begin(),e=ruestungen->end();
    FOR_EACH_CONST_TAG_OF_5(i,*ruestungen,b,e,"Rüstung")
    { 
       {  const Tag *preis=i->find("Kaufpreis");
          if (preis) 
             list_All.push_back(cH_Preise(i->getAttr("Name"),"Rüstung",&*i));
       }
    }
 }   
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





//////////////////////////////////////////////////////////////////////
cH_PreiseMod::cache_t cH_PreiseMod::cache;

cH_PreiseMod::cH_PreiseMod(const std::string& art,const std::string& art2,const std::string typ,const int &nr)
{
 st_index index(art,art2,typ,nr);
 cH_PreiseMod *cached(cache.lookup(index));
 if (cached) *this=*cached;
  assert(!"PreiseMod im Cache");
}

cH_PreiseMod::cH_PreiseMod(const Tag *tag)
{*this=cH_PreiseMod(new PreiseMod(tag));
	// art,art2,typ,nr
 cache.Register(st_index(tag->getAttr("Art"),tag->getAttr("Art2"),
 		tag->getAttr("Typ"),
 		tag->getIntAttr("MAGUS-Nr",tag->getIntAttr("MCG-Nr"))),*this);
}

void PreiseMod::get_PreiseMod()
{
  assert(tag);
  nr=tag->getIntAttr("MAGUS-Nr",tag->getIntAttr("MCG-Nr"));
  art=tag->getAttr("Art");
  art2=tag->getAttr("Art2");
  typ=tag->getAttr("Typ");
  payload=st_payload(tag->getAttr("Bezeichnung"),tag->getFloatAttr("Faktor"));
}


PreiseMod_All::PreiseMod_All()
{
 const Tag *preise=xml_data->find("Preise");
 if (preise)
 {  Tag::const_iterator b=preise->begin(),e=preise->end();
    FOR_EACH_CONST_TAG_OF_5(i,*preise,b,e,"Modifikation")
    {  
       list_All.push_back(cH_PreiseMod(&*i));
    }
 }   
}  


/////////////////////////////////////////////////////////////////////////
// Neuanlegen
/////////////////////////////////////////////////////////////////////////

// use this tag to determine whether this is a user defined item
Tag Preise::eigenerArtikel("Kaufpreis");

void Preise::saveArtikel(std::string art,std::string art2,std::string name,double preis, std::string einheit,double gewicht)
{
  eigenerArtikel.setAttr("Art2",art2);
  eigenerArtikel.setAttr("Währung",einheit);
  eigenerArtikel.setAttr("Preis",dtos(preis));
  eigenerArtikel.setAttr("Gewicht",dtos(gewicht));
  cH_Preise(name,art,&eigenerArtikel);
}
