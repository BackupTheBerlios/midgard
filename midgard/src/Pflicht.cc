/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

#include "Pflicht.hh"
#include "ProgressBar.h"


/*
cH_Pflicht::cache_t cH_Pflicht::cache;

cH_Pflicht::cH_Pflicht(const std::string& spezies,const vector<cH_Typen>& Typ)
{
 st_index index(spezies,Typ);
 cH_Pflicht *cached(cache.lookup(index));
 if (cached) *this=*cached;
 else
  {
   *this=cH_Pflicht(new Pflicht(spezies,Typ));
   cache.Register(index,*this);
  }
}
*/


void Pflicht::SuchePflichtVerbot(const Tag *list,const string &name,
		pflicht_nach_typ_t &pflicht_nach_typ)
{  FOR_EACH_CONST_TAG(j,*list)
   {  if (j->Type()!="Lernschema" && j->Type()!="Verbot") continue; // faster
      if (j->getAttr("Spezies").empty()) continue;
      if (j->Type()=="Lernschema")
         pflicht_nach_typ[j->getAttr("Spezies")].push_back
         	(pf(name,"",j->getIntAttr("Lernpunkte"),j->getIntAttr("Erfolgswert"),""));
      else // if (j->Type()=="Verbot")
         pflicht_nach_typ[j->getAttr("Spezies")].push_back
         	(pf("",name,0,0,j->getBoolAttr("Spielbeginn")?"S":""));
   }
}

Pflicht::Pflicht(Gtk::ProgressBar *progressbar)//const std::string& spezies,const vector<cH_Typen>& Typ)
{
 pflicht_nach_typ_t pflicht_nach_typ;
 const Tag *Fertigkeiten=xml_data->find("Fertigkeiten");
 if (Fertigkeiten)
 {  Tag::const_iterator b=Fertigkeiten->begin(),e=Fertigkeiten->end();
    double size=(e-b)*4;
    
    FOR_EACH_CONST_TAG_OF_5(i,*Fertigkeiten,b,e,"Fertigkeit")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
       SuchePflichtVerbot(i,i->getAttr("Name"),pflicht_nach_typ);
    }
 }
 const Tag *Zauber=xml_data->find("Zauber");
 if (Zauber)
 {  Tag::const_iterator b=Zauber->begin(),e=Zauber->end();
    double size=(e-b)*4;
    FOR_EACH_CONST_TAG_OF_5(i,*Zauber,b,e,"Spruch")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size+.25);
       SuchePflichtVerbot(i,i->getAttr("Name"),pflicht_nach_typ);
    }
 }
 const Tag *Waffen=xml_data->find("Waffen");
 if (Waffen)
 {  Tag::const_iterator b=Waffen->begin(),e=Waffen->end();
    double size=(e-b)*4;
    FOR_EACH_CONST_TAG_OF_5(i,*Waffen,b,e,"Waffe")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size+.5);
       SuchePflichtVerbot(i,i->getAttr("Name"),pflicht_nach_typ);
    }
 }
 const Tag *Waffen_Grundkenntnisse=xml_data->find("Waffen-Grundkenntnisse");
 if (Waffen_Grundkenntnisse)
 {  Tag::const_iterator b=Waffen_Grundkenntnisse->begin(),e=Waffen_Grundkenntnisse->end();
    double size=(e-b)*4;
    FOR_EACH_CONST_TAG_OF_5(i,*Waffen_Grundkenntnisse,b,e,"Waffen-Grundkenntnis")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size+.75);
       SuchePflichtVerbot(i,i->getAttr("Name"),pflicht_nach_typ);
    }
 }
 
 for (pflicht_nach_typ_t::const_iterator i=pflicht_nach_typ.begin();
 		i!=pflicht_nach_typ.end();++i)
    pflicht_map[i->first] = i->second;

 ProgressBar::set_percentage(progressbar,1);
}

int Pflicht::istPflicht(const std::string& spezies,const vector<cH_Typen>& Typ,
                        const std::string& name,LE le) const
{
  assert (Typ.size()==2);
  std::list<pf> list_pflicht   = const_cast<map<std::string,list<pf> > &>(pflicht_map)[spezies];
  std::list<pf> list_pflicht_2 = const_cast<map<std::string,list<pf> > &>(pflicht_map)[Typ[0]->Short()];
  std::list<pf> list_pflicht_3 = const_cast<map<std::string,list<pf> > &>(pflicht_map)[Typ[1]->Short()];
  list_pflicht.merge(list_pflicht_2);
  list_pflicht.merge(list_pflicht_3);
  for(std::list<pf>::const_iterator i=list_pflicht.begin();i!=list_pflicht.end();++i)
   if(i->pflicht==name) 
      { if (le==LERNPUNKTE)  return  i->lernpunkte;
        if (le==ERFOLGSWERT) return i->erfolgswert;
      }
  return 0; 
}

bool Pflicht::istVerboten(const std::string& spezies,const vector<cH_Typen>& Typ,
                          const std::string& name,bool spielbeginn) const
{
  assert (Typ.size()==2);
  std::list<pf> list_pflicht =   const_cast<map<std::string,list<pf> > &>(pflicht_map)[spezies];
  std::list<pf> list_pflicht_2 = const_cast<map<std::string,list<pf> > &>(pflicht_map)[Typ[0]->Short()];
  std::list<pf> list_pflicht_3 = const_cast<map<std::string,list<pf> > &>(pflicht_map)[Typ[1]->Short()];
  list_pflicht.merge(list_pflicht_2);
  list_pflicht.merge(list_pflicht_3);
  for(std::list<pf>::const_iterator i=list_pflicht.begin();i!=list_pflicht.end();++i)
   {  if(spielbeginn && i->verboten==name && i->spielbeginn!="") return true;
      if(i->verboten==name) return true;
   }
  return false; 
}


