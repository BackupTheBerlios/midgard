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
#include "Grundwerte.hh"

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
 kultwaffe=tag->getBoolAttr("Kultwaffe",false);
 lernpflichten_info=tag->getAttr("Lernpflichten");
 min_st=tag->getIntAttr("MinSt");
 min_gw=tag->getIntAttr("MinGw");
 min_gs=tag->getIntAttr("MinGs");
 min_in=tag->getIntAttr("MinIn");
 min_pa=tag->getIntAttr("MinpA");
 FOR_EACH_CONST_TAG_OF(i,*tag,"Herkunft")
   vec_herkunft.push_back(Typen::st_herkunft(i->getAttr("Land"),i->getAttr("Kultwaffe")));
 FOR_EACH_CONST_TAG_OF(i,*tag,"Gruppe")
   vec_gruppe.push_back(i->getAttr("Name"));
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


bool Typen::Mindestwerte(const Grundwerte& Werte) const
{
  if (Werte.St() < min_st ||
      Werte.Gw() < min_gw ||
      Werte.Gs() < min_gs ||
      Werte.In() < min_in ||
      Werte.pA() < min_pa )   return false;
  else return true;
  abort(); 
}

/*
bool Typen::Herkunft(const cH_Land land) const
{
  return true;
}
*/


bool Typen::Gruppe(const std::string &gruppe) const
{
  return std::find(vec_gruppe.begin(),vec_gruppe.end(),gruppe)!=vec_gruppe.end(); 
}



bool Typen::get_Typ_from_long(const std::vector<cH_Typen>& V,
                                    std::string& name)
{
  string::size_type s1=name.find_first_of("(");
  if(s1!=string::npos) name.erase(s1,1);
  string::size_type s2=name.find_last_of(")");
  if(s2!=string::npos) name.erase(s2,1);
  for(std::vector<cH_Typen>::const_iterator i=V.begin();i!=V.end();++i)
   {
     if((*i)->Typl()==name || (*i)->Typlw()==name) 
      {
        name = (*i)->Short();
        return true;
      }
   }
  return false;
}


std::string Typen::getLernpflichtenInfo(cH_Land herkunft) const
{ 
  std::vector<std::string> vk;
  for(std::vector<st_herkunft>::const_iterator i=vec_herkunft.begin();i!=vec_herkunft.end();++i)
   {
     if(herkunft->Name()==i->land)
       vk.push_back(i->kultwaffe);
   }
  if(vk.empty())  return lernpflichten_info;
  std::string K="Für einen "+Short()+" muß als erstes ";
  if(vk.size()==1) K+="die ";
  else K+="eine ";
  K+="Kultwaffe gewählt werden:\n";
  for(std::vector<std::string>::const_iterator i=vk.begin();i!=vk.end();++i)
   {
     K+="\t"+*i+"\n";
   }
  return lernpflichten_info + "\n"+K;
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

