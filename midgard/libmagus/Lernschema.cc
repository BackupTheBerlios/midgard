/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2002-2003 Christof Petig 
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

#include "Lernschema.hh"
#include "Typen.hh"
#include "Waffe.hh"
#include "Zauber.hh"
#include "Zauberwerk.hh"
#include "Fertigkeiten.hh"
#include <Misc/Tag.h>

void Lernschema::load(const Tag &t,const std::string &art)
{  FOR_EACH_CONST_TAG_OF(j,t,"Lernschema")
   {  if (j->getAttr("Typ").empty()) continue; // Spezies ??
      lern_map[st_index(j->getAttr("Typ"),art,t.getAttr("Name"))] 
             = st_wert(j->getBoolAttr("Pflicht"),j->getIntAttr("Erfolgswert")
             		,"",j->getIntAttr("Lernpunkte"),"","");
   }
}

std::list<MBEmlt> Lernschema::get_List(const std::string& art, 
      const std::vector<cH_Typen>& Typ,
      const std::list<MBEmlt>& Gelerntes) const
{
 std::list<MBEmlt> L;
 for(std::map<st_index,st_wert>::const_iterator i=lern_map.begin();i!=lern_map.end();++i)
  {
   if( (i->first.typ==Typ[0]->Short() || i->first.typ==Typ[1]->Short()) &&
        i->first.art==art)
     {
      if(art=="Fachkenntnisse") 
         { 
           MBEmlt fert(&*cH_Fertigkeit(i->first.fertigkeit));
           // Erfolgswert nur dann setzen, wenn die Fertigkeit noch nicht gelernt wurde
           if(!fert->ist_gelernt(Gelerntes))
              fert->setErfolgswert(i->second.erfolgswert);
           L.push_back(fert); 
         }
      if(art=="Waffenfertigkeiten") 
         { 
           MBEmlt waffe(&*cH_Waffe(i->first.fertigkeit));
           // Erfolgswert nur dann setzen, wenn die Fertigkeit noch nicht gelernt wurde
           if(!waffe->ist_gelernt(Gelerntes))
              waffe->setErfolgswert(i->second.erfolgswert);
           L.push_back(waffe); 
         }
      if(art=="Zauberkünste") 
         { 
           MBEmlt z(&*cH_Zauber(i->first.fertigkeit));
           L.push_back(z);
         }
     }   
  }
 L.sort();
 L.unique();
 return L;
}

// Doppelklassen
std::vector<Lernschema::st_index> Lernschema::getIndex(const std::vector<cH_Typen>& Typ,const std::string& art,const std::string& name)
{
  assert(Typ.size()==2);
  std::vector<st_index> VI;
  for(std::vector<cH_Typen>::const_iterator i=Typ.begin();i!=Typ.end();++i)
   {
     if((*i)->Short()!="")
         VI.push_back(st_index((*i)->Short(),art,name));
   }
  return VI;
}

bool Lernschema::get_Pflicht(const std::vector<st_index>& VI) const
{
  for(std::vector<st_index>::const_iterator i=VI.begin();i!=VI.end();++i)
   {
//cout <<"Lernschema::get_Pflicht:  "<< i->typ<<' '<<i->art<<' '<<i->fertigkeit<<'\n';
     bool b=const_cast<std::map<st_index,st_wert>&>(lern_map)[*i].pflicht; 
     if(b) return true;
   }
  return false;
}

int Lernschema::get_Lernpunkte(const std::vector<st_index>& VI) const
{
  int lernp=99;
  for(std::vector<st_index>::const_iterator i=VI.begin();i!=VI.end();++i)
   {
     int l=const_cast<std::map<st_index,st_wert>&>(lern_map)[*i].lernpunkte; 
     (l<lernp) ? (lernp=l) : 1 ;
   }
  return lernp;
}

