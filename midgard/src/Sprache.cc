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

#include "Sprache.hh"
#include <cstring>
#include <Gtk_OStream.h>
#include <Aux/itos.h>
#include "ProgressBar.h"
#include "Schrift.hh"
#include "Grundwerte.hh"

cH_Sprache::cache_t cH_Sprache::cache;

cH_Sprache::cH_Sprache(const std::string& name IF_XML(,bool create))
{
 cH_Sprache *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  cerr << "Sprache '" << name << "' nicht im Cache\n";
  if (create)
  {  static Tag t2("Sprache"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Name",name);
     *this=cH_Sprache(&t2);
  }
  else throw NotFound();
  }
}

cH_Sprache::cH_Sprache(const Tag *tag)
{*this=cH_Sprache(new Sprache(tag));
 cache.Register(tag->getAttr("Name"),*this);
}

void Sprache::get_Sprache()
{
  region=tag->getAttr("Region");
  region_zusatz=tag->getAttr("RegionZusatz");
  alte_sprache=tag->getBoolAttr("alteSprache");
  minderheit=tag->getBoolAttr("Minderheit");
  maxwert=tag->getIntAttr("Maximalwert");
  kosten=tag->getIntAttr("Kosten");
  if(tag->getIntAttr("Gruppe")) 
     V_sprachgruppe.push_back(tag->getIntAttr("Gruppe"));
  if(tag->getIntAttr("Gruppe2")) 
     V_sprachgruppe.push_back(tag->getIntAttr("Gruppe2"));

  FOR_EACH_CONST_TAG_OF(i,*tag,"Schrift")
     VSchrift.push_back(i->getAttr("Name",tag->getAttr("Name")));
}

int Sprache::Kosten(const Grundwerte &Werte,const vector<cH_Typen>& Typ) const
{ 
  cH_Fertigkeit F("Sprechen: Sprache");
  return  (int)(F->Standard_Faktor(Werte,Typ) * kosten) ; 
}

int Sprache::MaxErfolgswert(const Grundwerte& w,const vector<cH_Typen>& Typ) const
{
  if (w.In() < 31) return (11>maxwert ? maxwert : 11); 
  if (w.In() < 61) return (18>maxwert ? maxwert : 18); 

  int ab= cH_Fertigkeit("Sprache")->MaxErfolgswert(w,Typ);
  if(maxwert==20) return ab;
  else return (ab>maxwert ? maxwert : ab);
}


std::string Sprache::Schriften() const
{
  std::string s;
  for(vector<std::string>::const_iterator j=VSchrift.begin();j!=VSchrift.end();)
   {
     s=*j;
     if(++j!=VSchrift.end()) s+=", ";
   }
  return s;
}



//const vector<pair<std::string,int> > Sprache::SchriftWert(const std::list<cH_MidgardBasicElement>& list_Schrift,const std::list<cH_MidgardBasicElement>& list_AllSchrift) const 
const vector<pair<std::string,int> > Sprache::SchriftWert(const std::list<MidgardBasicElement_mutable>& list_Schrift) const 
{
 vector<pair<std::string,int> > vs;
 for(vector<std::string>::const_iterator i=VSchrift.begin();i!=VSchrift.end();++i)
  {  
   for(std::list<MidgardBasicElement_mutable>::const_iterator j=list_Schrift.begin();j!=list_Schrift.end();++j)
    {
      if(*i == (*j)->Name()) // Schrift ist gelernt
        vs.push_back(pair<std::string,int>(*i,(*j).Erfolgswert()));
/*
      else // Schrift nicht gelernt, aber vielleicht ist dieselbe Schrift gelernt?
        {
          cH_Schrift schrift(*i);
          std::list<cH_MidgardBasicElement> LM=schrift->gleicheSchrift(list_AllSchrift);
          for(std::list<cH_MidgardBasicElement>::const_iterator l=LM.begin();l!=LM.end();++l)
            {
              if((*l)->Name()==*i)
                 vs.push_back(pair<std::string,int>(*i,+8));
            }
        }
*/
    }
  }
 return vs;
}

bool Sprache::Sprachgruppe(const std::vector<int>& V2) const
{
  for(vector<int>::const_iterator j=V_sprachgruppe.begin();j!=V_sprachgruppe.end();++j)
    for(vector<int>::const_iterator k=V2.begin();k!=V2.end();++k)
      if(*j==*k) return true;
  return false;
}

std::list<MidgardBasicElement_mutable> Sprache::VerwandteSprachen(const int erfolgswert,const std::list<MidgardBasicElement_mutable>& gelernte_listSprache,const std::list<cH_MidgardBasicElement>& listSprache) const
{
  std::list<MidgardBasicElement_mutable> VS;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=listSprache.begin();i!=listSprache.end();++i)
   {
     if(erfolgswert>=10 && !MidgardBasicElement_mutable(*i).ist_gelernt(gelernte_listSprache) &&
        Sprachgruppe(cH_Sprache(*i)->getVSprachgruppe())) 
      {
//         cH_MidgardBasicElement MBE=new Sprache(*cH_Sprache(*i)); // Kopie anlegen
//         MBE->setErfolgswert(Erfolgswert()-10);
//         VS.push_back(MBE) ;
        MidgardBasicElement_mutable M(*i);
        M.setErfolgswert(erfolgswert-10);
        VS.push_back(*i);
      }
   }
 return VS;
}

std::list<MidgardBasicElement_mutable> Sprache::cleanVerwandteSprachen(std::list<MidgardBasicElement_mutable> L)
{
  // Aus der Liste die Sprache mit dem höchsten Erfolgswert nehmen.
  std::map<std::string,int> M;
  for(std::list<MidgardBasicElement_mutable>::const_iterator i=L.begin();i!=L.end();++i)
   {
     if(M[(*i)->Name()] < (*i).Erfolgswert()) 
         M[(*i)->Name()] = (*i).Erfolgswert();
   }
  std::list<MidgardBasicElement_mutable> N;
  for(std::map<std::string,int>::const_iterator i=M.begin();i!=M.end();++i)
   {
     const cH_Sprache s(i->first);
//     s->setErfolgswert(i->second);
//     N.push_back(&*s);
     
     MidgardBasicElement_mutable m(&*s);
     m.setErfolgswert(i->second);
     N.push_back(m);
   }
 return N;
}


Sprachen_All::Sprachen_All(Gtk::ProgressBar *progressbar)
{
 const Tag *sprachen=xml_data->find("Sprachen");
 if (sprachen)
 {  Tag::const_iterator b=sprachen->begin(),e=sprachen->end();
    double size=e-b;
    FOR_EACH_CONST_TAG_OF_5(i,*sprachen,b,e,"Sprache")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
       list_All.push_back(&*(cH_Sprache(&*i)));
    }
 }   
 ProgressBar::set_percentage(progressbar,1);
}  

