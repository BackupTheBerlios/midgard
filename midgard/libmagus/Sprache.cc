/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2002-2004 Christof Petig
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
#include <Misc/itos.h>
#include "Schrift.hh"
#include "Grundwerte.hh"
#include "Abenteurer.hh"
#include "NotFound.h"
#include <Misc/Tag.h>
#include "Ausgabe.hh"

cH_Sprache::cache_t cH_Sprache::cache;

cH_Sprache::cH_Sprache(const std::string& name,bool create)
{
 cH_Sprache *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  Ausgabe(Ausgabe::Warning, "Sprache '" + name + "' nicht im Cache");
  if (create)
  {  Tag t2("Sprache"); 
     t2.setAttr("Name",name);
     *this=new Sprache(t2);
  }
  else throw NotFound(name);
  }
}

void Sprache::get_Sprache(const Tag &t)
{
  region=t.getAttr("Region");
  region_zusatz=t.getAttr("RegionZusatz");
  alte_sprache=t.getBoolAttr("alteSprache");
  minderheit=t.getBoolAttr("Minderheit");
  maxwert=t.getIntAttr("Maximalwert");
  kosten=t.getIntAttr("Kosten");
  if(t.getIntAttr("Gruppe")) 
     V_sprachgruppe.push_back(t.getIntAttr("Gruppe"));
  if(t.getIntAttr("Gruppe2")) 
     V_sprachgruppe.push_back(t.getIntAttr("Gruppe2"));

  FOR_EACH_CONST_TAG_OF(i,t,"Schrift")
     VSchrift.push_back(i->getAttr("Name",Name()));
}

int Sprache::Kosten(const Abenteurer& A) const
{ 
  cH_Fertigkeit F("Sprechen: Sprache");
  return  int(F->Standard_Faktor(A) * kosten) ; 
}

int Sprache::MaxErfolgswert(const Abenteurer& A) const
{
  if (A.In() < 31) return (11>maxwert ? maxwert : 11); 
  if (A.In() < 61) return (18>maxwert ? maxwert : 18); 

  int ab= cH_Fertigkeit("Sprache")->MaxErfolgswert(A);
  if(maxwert==20) return ab;
  else return (ab>maxwert ? maxwert : ab);
}


std::string Sprache::Schriften() const
{
  std::string s;
  for(std::vector<std::string>::const_iterator j=VSchrift.begin();j!=VSchrift.end();)
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
 for(std::vector<std::string>::const_iterator i=VSchrift.begin();i!=VSchrift.end();++i)
  {  
   for(std::list<MBEmlt>::const_iterator j=list_Schrift.begin();j!=list_Schrift.end();++j)
    {
      if(*i == (*(*j))->Name()) // Schrift ist gelernt
         sus.push_back(*i,dynamic_cast<const class Schrift*>((*j)->getMBE())->Art_der_Schrift(),
             (*j)->Erfolgswert());
    }
  }
  return sus;
}

std::string Sprache_und_Schrift::getErfolgswert() const
{
   std::string back;
   if(!gelernt) back += "(";
   back += "+"+itos(sprache->Erfolgswert());
   if(!gelernt) back += ")";

   if(ungelernt_besser) back+=" (+"+itos(ungelernt)+")";
   return back;
}

void Sprache_und_Schrift::ungelernte_ist_besser(std::vector<Sprache_und_Schrift> &SuS,const std::string &name,const int wert)
{
  for(std::vector<Sprache_und_Schrift>::iterator i=SuS.begin();i!=SuS.end();++i)
   {
     if(name==i->getSprache()->getMBE()->Name())
      {
        i->ungelernt_besser=true;
        i->ungelernt=wert;
        return;
      }  
   } 
}

bool Sprache::Sprachgruppe(const std::vector<int>& V2) const
{
  for(std::vector<int>::const_iterator j=V_sprachgruppe.begin();j!=V_sprachgruppe.end();++j)
    for(std::vector<int>::const_iterator k=V2.begin();k!=V2.end();++k)
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
     MBEmlt m(s);
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
       if(Name()==(*(*j))->Name() /*&& (*j)->Erfolgswert()>e*/) e=(*j)->Erfolgswert();
     }
  }
 return e;
}


bool Sprache::ist_erlaubt(const Abenteurer& A,bool nachbarland) const 
{
  if(nachbarland)
   {
     std::vector<std::string> L=A.Herkunft()->Nachbarlaender();
     for(std::vector<std::string>::const_iterator i=L.begin();i!=L.end();++i)
      {
        std::vector<std::string> V=cH_Land(*i)->Sprachen();
        for(std::vector<std::string>::const_iterator j=V.begin();j!=V.end();++j)
          if(!cH_Sprache(*j)->Alte_Sprache() && *j==Name())   return true  ;
      }
   }
  else
   {
     std::vector<std::string> V=A.Spezies()->getVSprache();
     if(V.empty()) // Keine Sprachenvorgabe aufgrund der Spezies
         V=A.Herkunft()->Sprachen();
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

static MidgardBasicElement::EP_t Sprache_EP=MidgardBasicElement::EP_t_undefined;

Sprache::Sprache(const Tag &t)
      : MidgardBasicElement(t.getAttr("Name"))
{  get_Sprache(t); get_map_typ(); get_Steigern_Kosten_map();
   if (Sprache_EP==EP_t_undefined) Sprache_EP=EP_steigern("Sprache");
   else EP_steigern(Sprache_EP);
}

cH_Sprache cH_Sprache::load(const Tag &t,bool &is_new)
{  cH_Sprache *res=cache.lookup(t.getAttr("Name"));
   assert (!res);
   {  cH_Sprache r2=new Sprache(t);
      is_new=true;
      cache.Register(t.getAttr("Name"),r2);
      return r2;
   }
}

void Sprachen_All::load(std::list<cH_MidgardBasicElement> &list,const Tag &t)
{  bool is_new=false;
   cH_Sprache z=cH_Sprache::load(t,is_new);
   if (is_new) list.push_back(z);
}

