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
#include <Misc/itos.h>
#include "ProgressBar.h"
#include "Schrift.hh"
#include "Grundwerte.hh"
#include "Abenteurer.hh"
#include "midgard_CG.hh"

cH_Sprache::cache_t cH_Sprache::cache;

cH_Sprache::cH_Sprache(const std::string& name,bool create)
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

int Sprache::Kosten(const Abenteurer& A) const
{ 
  cH_Fertigkeit F("Sprechen: Sprache");
  return  (int)(F->Standard_Faktor(A) * kosten) ; 
}

int Sprache::MaxErfolgswert(const Abenteurer& A) const
{
  if (A.getWerte().In() < 31) return (11>maxwert ? maxwert : 11); 
  if (A.getWerte().In() < 61) return (18>maxwert ? maxwert : 18); 

  int ab= cH_Fertigkeit("Sprache")->MaxErfolgswert(A);
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



const Sprache_und_Schrift Sprache::SchriftWert(int erfolgswert,bool gelernt,const std::list<MBEmlt>& list_Schrift) const 
{
 MBEmlt mbe(&*this);
 mbe->setErfolgswert(erfolgswert);
 Sprache_und_Schrift sus(mbe,gelernt);
 for(vector<std::string>::const_iterator i=VSchrift.begin();i!=VSchrift.end();++i)
  {  
   for(std::list<MBEmlt>::const_iterator j=list_Schrift.begin();j!=list_Schrift.end();++j)
    {
      if(*i == (*(*j))->Name()) // Schrift ist gelernt
         sus.push_back(*i,(*j)->Erfolgswert());
    }
  }
  return sus;
}

bool Sprache::Sprachgruppe(const std::vector<int>& V2) const
{
  for(vector<int>::const_iterator j=V_sprachgruppe.begin();j!=V_sprachgruppe.end();++j)
    for(vector<int>::const_iterator k=V2.begin();k!=V2.end();++k)
      if(*j==*k) return true;
  return false;
}

std::list<MBEmlt> Sprache::getVerwandteSprachen(const std::list<MBEmlt>& gekonnteSprachen,const std::list<cH_MidgardBasicElement>& alleSprachen)
{
  std::list<MBEmlt> L;
  for(std::list<MBEmlt>::const_iterator i=gekonnteSprachen.begin();i!=gekonnteSprachen.end();++i)
   {
     std::list<MBEmlt> tmplist=cH_Sprache((*i)->getMBE())->VerwandteSprachen((*i)->Erfolgswert(),gekonnteSprachen,alleSprachen);
     L.splice(L.end(),tmplist);
   }
  L=Sprache::cleanVerwandteSprachen(L);
  return L;
}



std::list<MBEmlt> Sprache::VerwandteSprachen(const int erfolgswert,const std::list<MBEmlt>& gelernte_listSprache,const std::list<cH_MidgardBasicElement>& listSprache) const
{
  std::list<MBEmlt> VS;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=listSprache.begin();i!=listSprache.end();++i)
   {
     if(erfolgswert>=10 && !MBEmlt(*i)->ist_gelernt(gelernte_listSprache) &&
        Sprachgruppe(cH_Sprache(*i)->getVSprachgruppe())) 
      {
        MBEmlt M(*i);
        M->setErfolgswert(erfolgswert-10);
        VS.push_back(M);
      }
   }
 return VS;
}

std::list<MBEmlt> Sprache::cleanVerwandteSprachen(std::list<MBEmlt> L)
{
  // Aus der Liste die Sprache mit dem höchsten Erfolgswert nehmen.
  std::map<std::string,int> M;
  for(std::list<MBEmlt>::const_iterator i=L.begin();i!=L.end();++i)
   {
     if(M[(*(*i))->Name()] < (*i)->Erfolgswert()) 
         M[(*(*i))->Name()] = (*i)->Erfolgswert();
   }
  std::list<MBEmlt> N;
  for(std::map<std::string,int>::const_iterator i=M.begin();i!=M.end();++i)
   {
     const cH_Sprache s(i->first);
     MBEmlt m(&*s);
     m->setErfolgswert(i->second);
     N.push_back(m);
   }
 return N;
}

int Sprache::getHoeherenErfolgswert(const std::list<MBEmlt>& gelernte_listSprache,const std::list<cH_MidgardBasicElement>& listSprache) const
{
 int e=0;
 for(std::list<MBEmlt>::const_iterator i=gelernte_listSprache.begin();i!=gelernte_listSprache.end();++i)
  {
    assert(Name()!=(*(*i))->Name());
    std::list<MBEmlt> tmplist=cH_Sprache((*i)->getMBE())->VerwandteSprachen((*i)->Erfolgswert(),gelernte_listSprache,listSprache);
    for(std::list<MBEmlt>::const_iterator j=tmplist.begin();j!=tmplist.end();++j)
     {
       if(Name()==(*(*j))->Name() && (*j)->Erfolgswert()>e) e=(*j)->Erfolgswert();
     }
  }
 return e;
}


bool Sprache::ist_erlaubt(const VAbenteurer& A,bool nachbarland=false) const 
{
  if(nachbarland)
   {
     std::vector<std::string> L=A->getWerte().Herkunft()->Nachbarlaender();
     for(std::vector<std::string>::const_iterator i=L.begin();i!=L.end();++i)
      {
        std::vector<std::string> V=cH_Land(*i)->Sprachen();
        for(std::vector<std::string>::const_iterator j=V.begin();j!=V.end();++j)
          if(!cH_Sprache(*j)->Alte_Sprache() && *j==Name())   return true  ;
      }
   }
  else
   {
     std::vector<std::string> V=A->getWerte().Spezies()->getVSprache();
     if(V.empty()) // Keine Sprachenvorgabe aufgrund der Spezies
         V=A->getWerte().Herkunft()->Sprachen();
     if(find(V.begin(),V.end(),Name())!=V.end()) return true;
   }
  return false;
}

void Sprache::setErfolgswertMutterGastlandsprache(MBEmlt &M,std::string mode,int in,int bonus)
{
  if(mode=="Muttersprache")
   {
     if(in<=30) M->setErfolgswert(10);
     else if (30<in && in<=60) M->setErfolgswert(14);
     else if (in>60) M->setErfolgswert(18+bonus);
   }
  else if(mode=="Gastlandsprache")
   {
     if(in>30) M->setErfolgswert(12);
     else M->setErfolgswert(9);
   }
  else assert(!"never get here\n");
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

