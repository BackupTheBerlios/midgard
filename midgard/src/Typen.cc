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

#include "Typen.hh"
#include "ProgressBar.h"
#include "MidgardBasicElement.hh" // für NotFound

cH_Typen::cache_t cH_Typen::cache;

cH_Typen::cH_Typen(const std::string& name IF_XML(,bool create))
{
 cH_Typen *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
 {cerr << "Typen '" << name << "' nicht im Cache\n";
  if (create)
  {  static Tag t2("Typ"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Abkürzung",name);
     t2.setAttr("Bezeichnung-Mann",name);
     t2.setAttr("Bezeichnung-Frau",name);
     *this=cH_Typen(&t2);
  }
  else throw NotFound();
 }
}

cH_Typen::cH_Typen(const Tag *tag)
{*this=cH_Typen(new Typen(tag));
 cache.Register(tag->getAttr("Abkürzung"),*this);
}

Typen::Typen(const Tag *tag)
: typs(tag->getAttr("Abkürzung"))
  ,typnr(tag->getIntAttr("MAGUS-Index",tag->getIntAttr("MCG-Index")))
  ,stand(0),sb(0),ruestung(0),geld(0)
{
 typl=tag->getAttr("Bezeichnung-Mann");
 typlw=tag->getAttr("Bezeichnung-Frau");
 typz=tag->getBoolAttr("Zauberer")?"z":(tag->getBoolAttr("kannZaubern")?"j":"n");
 ausdauer=tag->getAttr("Ausdauer");
 const Tag *Modifikation=tag->find("Modifikation");
 if (Modifikation)
 {  stand=Modifikation->getIntAttr("Stand");
    sb=Modifikation->getIntAttr("Sb");
    ruestung=Modifikation->getIntAttr("Rüstung");
    geld=Modifikation->getIntAttr("Geld");
 }
 region=tag->getAttr("Region");
 beruf=tag->getAttr("Berufswahl");
 land=tag->getBoolAttr("Land",true);
 stadt=tag->getBoolAttr("Stadt",true);
 sprueche_mit_pp=tag->getAttr("SprücheMitPraxisPunkten");
 nsc_only=tag->getBoolAttr("NSC_only",false);
}

bool Typen::Spezialwaffe() const
{
  if (Zaubern()=="z") return false;
  if (Short()=="Ba") return false;
  if (Short()=="") return false;
  return true;
}

bool Typen::Spezialgebiet() const
{
  if (Short()=="Ma")  return true;
  if (Short()=="eBe") return true;
  return false;
}


Typen_All::Typen_All(Gtk::ProgressBar *progressbar)
{
 const Tag *typen=xml_data->find("Typen");
 if (typen)
 {  Tag::const_iterator b=typen->begin(),e=typen->end();
    double size=e-b;
    FOR_EACH_CONST_TAG_OF_5(i,*typen,b,e,"Typ")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
       list_All.push_back(cH_Typen(&*i));
    }
 }   
 ProgressBar::set_percentage(progressbar,1);
}




bool operator==(gpointer data,const cH_Typen &t)
{  return *(static_cast<Typen*>(data))==*t;
}

