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

#include "Spezies.hh"
#include "MidgardBasicElement.hh"
#include "Grundwerte.hh"
#include "Zauber.hh"
#include "Fertigkeiten_angeboren.hh"
#include "Fertigkeiten.hh"
#include <iostream>
#include "NotFound.h"

cH_Spezies::cache_t cH_Spezies::cache;

cH_Spezies::cH_Spezies(const std::string& name ,bool create)
{
 cH_Spezies *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  std::cerr << "Spezies '" << name << "' nicht im Cache\n";
  if (create)
  {  Tag t2("Spezies"); 
     t2.setAttr("Name",name);
     *this=new Spezies(t2);
  }
  else throw NotFound();
  }
}

Spezies::Spezies(const Tag &tag) 
: name(tag.getAttr("Name"))
{
 nr=tag.getIntAttr("MAGUS-Index",tag.getIntAttr("MCG-Index"));
 only_nsc=tag.getBoolAttr("only_NSC");
 land=tag.getBoolAttr("Land");
 hand_bonus=tag.getIntAttr("HandBonus");
 raufen=tag.getIntAttr("RaufenBonus");

 const Tag *Alter=tag.find("Alter");
 if (Alter) alter_fak=Alter->getIntAttr("Faktor");
 else alter_fak=1;

 const Tag *Groesse=tag.find("Größe");
 if(!Groesse) Groesse=&tag;
 groesse_bonus=Groesse->getIntAttr("Addiere");
 groesse_wanz=Groesse->getIntAttr("AnzahlWürfel");
 groesse_wuerfel=Groesse->getIntAttr("Würfel");

 const Tag *Gewicht=tag.find("Gewicht");
 if (!Gewicht) Gewicht=&tag;
 gewicht_bonus=Gewicht->getIntAttr("Addiere");
 gewicht_wanz=Gewicht->getIntAttr("AnzahlWürfel");

 const Tag *NormGe=tag.find("Normgestalt");
 if (!NormGe) NormGe=&tag;
 normgestalt = NormGe->getIntAttr("Wert"); 

 const Tag *Bewegungsweite=tag.find("Bewegungsweite");
 if (!Bewegungsweite) Bewegungsweite=&tag;
 b_bonus=Bewegungsweite->getIntAttr("Addiere");
 b_wanz=Bewegungsweite->getIntAttr("AnzahlWürfel");

 const Tag *Modifikation=tag.find("Modifikation");
 if (!Modifikation) Modifikation=&tag;
 lp=Modifikation->getIntAttr("LP_Bonus");
 ap_bonus=Modifikation->getIntAttr("AP_Bonus");
 ap_grad_fak=Modifikation->getIntAttr("AP_GradFaktor");

 const Tag *Resistenzen=Modifikation->find("Resistenzen");
 if (!Resistenzen) Resistenzen=&tag;
 psy=Resistenzen->getIntAttr("psy");
 phs=Resistenzen->getIntAttr("phs");
 phk=Resistenzen->getIntAttr("phk");
 psy100=Resistenzen->getIntAttr("psy100");
 phs100=Resistenzen->getIntAttr("phs100");
 phk100=Resistenzen->getIntAttr("phk100");

 const Tag *Grundwerte=Modifikation->find("Grundwerte");
 if (!Grundwerte) Grundwerte=&tag;
 st=Grundwerte->getIntAttr("St");
 gw=Grundwerte->getIntAttr("Gw");
 gs=Grundwerte->getIntAttr("Gs");
 ko=Grundwerte->getIntAttr("Ko");
 in=Grundwerte->getIntAttr("In");
 zt=Grundwerte->getIntAttr("Zt");
 sb=Grundwerte->getIntAttr("Sb");
 au=Grundwerte->getIntAttr("Au");

 FOR_EACH_CONST_TAG_OF(i,tag,"Typ")
    vec_typen.push_back(st_spez(i->getAttr("Name"),i->getIntAttr("MaximalerGrad")));
 FOR_EACH_CONST_TAG_OF(i,tag,"AngeboreneFerigkeit")
    vec_angebfert.push_back(st_angebfert(i->getAttr("Art"),
            i->getAttr("Name"),i->getIntAttr("Erfolgswert"),i->getIntAttr("LP")));
 // mal sinnvoll !            
 FOR_EACH_CONST_TAG_OF(i,tag,"angeboreneFertigkeit")
    vec_angebfert.push_back(st_angebfert(i->getAttr("Art"),
            i->getAttr("Name"),i->getIntAttr("Erfolgswert"),i->getIntAttr("LP")));
 FOR_EACH_CONST_TAG_OF(i,tag,"Land")
   vec_herkunft.push_back(i->getAttr("Name"));
 FOR_EACH_CONST_TAG_OF(i,tag,"Sprache")
   vec_sprache.push_back(i->getAttr("Name"));
}

bool Spezies::Typ_erlaubt(std::string typ) const
{
  if(vec_typen.empty()) return true;
  bool verbotene_typen=false;
  if(vec_typen.begin()->typen.substr(0,1)=="-") verbotene_typen=true;
  for(std::vector<st_spez>::const_iterator i=vec_typen.begin();i!=vec_typen.end();++i)
   {
    std::string s=i->typen.substr(0,1);
    if(s=="-") 
      {  
         std::string t=i->typen.substr(1,std::string::npos);
         if(t==typ) return false;
      }
    if(i->typen == typ) return true ;
   }
  if(verbotene_typen) return true;
  return false;
}

int Spezies::Psy(const Grundwerte &W) const
{
  if(W.Zt()<100) return psy;
  else return psy100;
}
int Spezies::Phs(const Grundwerte &W) const
{
  if(W.Zt()<100) return phs;
  else return phs100;
}
int Spezies::Phk(const Grundwerte &W) const
{
  if(W.Zt()<100) return phk;
  else return phk100;
}

std::list<MBEmlt> Spezies::getZauber() const
{
  std::list<MBEmlt> L;
  for(std::vector<st_angebfert>::const_iterator i=vec_angebfert.begin();i!=vec_angebfert.end();++i)
   {
    if(!(i->art=="z")) continue;
    cH_MidgardBasicElement z(&*cH_Zauber(i->name)); 
    MBEmlt Z(z);
    L.push_back(Z);
   }
 return L;
}

std::list<MBEmlt> Spezies::getAngFertigkeiten() const
{
  std::list<MBEmlt> L;
  for(std::vector<st_angebfert>::const_iterator i=vec_angebfert.begin();i!=vec_angebfert.end();++i)
   {
    if(!(i->art=="af")) continue;
    cH_MidgardBasicElement f(&*cH_Fertigkeit_angeborene(i->name)); 
    MBEmlt F(f);
    F->setErfolgswert(i->erfolgswert);
    L.push_back(F);
   }
 return L;
}

std::list<MBEmlt> Spezies::getFertigkeiten(int &lp,const Grundwerte &Werte) const
{
  std::list<MBEmlt> L;
  for(std::vector<st_angebfert>::const_iterator i=vec_angebfert.begin();i!=vec_angebfert.end();++i)
   {
    if(!(i->art=="f")) continue;
    cH_MidgardBasicElement f(&*cH_Fertigkeit(i->name)); 
    MBEmlt F(f);
    F->setErfolgswert(i->erfolgswert + cH_Fertigkeit(f)->AttributBonus(Werte) );
    lp+=i->lp;
    L.push_back(F);
   }
 return L;
}

std::list<MBEmlt> Spezies::getFreiwilligeFertigkeiten(const Grundwerte &Werte) const
{
  std::list<MBEmlt> L;
  for(std::vector<st_angebfert>::const_iterator i=vec_angebfert.begin();i!=vec_angebfert.end();++i)
   {
    if(!(i->art=="ff")) continue;
    cH_MidgardBasicElement f(&*cH_Fertigkeit(i->name)); 
    MBEmlt F(f);
    F->setErfolgswert(i->erfolgswert + cH_Fertigkeit(f)->AttributBonus(Werte));
//cout << i->erfolgswert<<' '<<cH_Fertigkeit(f)->AttributBonus(Werte)<<'\n';
    F->setLernpunkte(i->lp);
    L.push_back(F);
   }
 return L;
}

std::list<std::pair<std::string,int> > Spezies::getSinne() const
{
  std::list<std::pair<std::string,int> > S;
  for(std::vector<st_angebfert>::const_iterator i=vec_angebfert.begin();i!=vec_angebfert.end();++i)
   {
    if(!(i->art=="s")) continue;
    S.push_back(std::pair<std::string,int>(i->name,i->erfolgswert));
   }
 return S;
}

bool Spezies::istVerboten(const cH_MidgardBasicElement &mbe) const
{
  for(std::vector<st_angebfert>::const_iterator i=vec_angebfert.begin();i!=vec_angebfert.end();++i)
   {
    if( mbe->Name()==i->name  &&  i->art=="v") return true;
   }
  return false;
}

bool Spezies::istVerbotenSpielbegin(const cH_MidgardBasicElement &mbe) const
{
  for(std::vector<st_angebfert>::const_iterator i=vec_angebfert.begin();i!=vec_angebfert.end();++i)
   {
    if( mbe->Name()==i->name  &&  i->art=="sv") return true;
   }
  return false;
}


bool operator==(void* data,const cH_Spezies &s)
{  return *(static_cast<Spezies*>(data))==*s;
}

bool Spezies::get_Spezies_from_long(const std::vector<cH_Spezies>& V,
                                        std::string& name)
{
  for(std::vector<cH_Spezies>::const_iterator i=V.begin();i!=V.end();++i)
   {
     if((*i)->Name()==name )  return true;
   }
  return false;
}

int Spezies::B_Durchschnitt() const
{
  return 2*B_Wanz()+B_Bonus();
}


cH_Spezies Spezies::getSpezies(std::string s,const std::vector<cH_Spezies> V)
{
  for(std::vector<cH_Spezies>::const_iterator i=V.begin();i!=V.end();++i)
   {
     if(s==(*i)->Name()) return *i;
   }
  return cH_Spezies("Mensch");
}

cH_Spezies cH_Spezies::load(const Tag &t)
{  cH_Spezies *res=cache.lookup(t.getAttr("Name"));
   assert(!res);
   {  cH_Spezies r2=new Spezies(t);
      cache.Register(t.getAttr("Name"),r2);
      return r2;
   }
}

void Spezies_All::load(std::list<cH_Spezies> &list,const Tag &t)
{  list.push_back(cH_Spezies::load(t));
}

void Spezies_All::load(std::vector<cH_Spezies> &list,const Tag &t)
{  list.push_back(cH_Spezies::load(t));
}

