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

#include "Waffe.hh"
#include "Typen.hh"
#include <Misc/itos.h>
#include <iostream>
#include "Abenteurer.hh"
// #include <memory>
#include <Misc/Tag.h>
#include "NotFound.h"

cH_Waffe::cache_t cH_Waffe::cache;

cH_Waffe::cH_Waffe(const std::string& name , bool create)
{
 cH_Waffe *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  std::cerr << "Waffe '" << name << "' nicht im Cache\n";
  if (create)
  {  Tag t2("Waffe"); 
     t2.setAttr("Name",name);
     *this=new Waffe(t2);
  }
  else throw NotFound();
  }
}

void Waffe::get_Waffe(const Tag &t)
{
  if (t.hasAttr("Schaden"))
  {grundkenntnisse=t.getAttr("Grundkenntnisse");
   schwierigkeit=t.getIntAttr("Schwierigkeit");
   art=t.getAttr("Kategorie");
   art2=t.getAttr("Klasse");
   schaden=t.getAttr("Schaden");
   schaden_bonus=t.getIntAttr("Schadensbonus");
   schaden_bonus2=t.getIntAttr("Schadensbonus2");
   voraussetzung=t.getAttr("erfordert");
   region=t.getAttr("Region");
   text=t.getAttr("Text");
  }
   
   const Tag *Modifikationen=t.find("Modifikationen");
   if (Modifikationen)
   {  waffenrang=Modifikationen->getAttr("Waffenrang");
      wm_abwehr_leicht=Modifikationen->getAttr("Abwehr-leicht");
      wm_abwehr_schwer=Modifikationen->getAttr("Abwehr-schwer");
   }

   const Tag *Voraussetzungen=t.find("Voraussetzungen");
   if (Voraussetzungen)
   {  st=Voraussetzungen->getIntAttr("St");
      gw=Voraussetzungen->getIntAttr("Gw");
      gs=Voraussetzungen->getIntAttr("Gs");
      min_st_einhand=Voraussetzungen->getIntAttr("Min_St_Einhand");
   }

   const Tag *Reichweite=t.find("Reichweite");
   if (Reichweite)
   {  reichweite_0=Reichweite->getIntAttr("null");
      reichweite_n=Reichweite->getIntAttr("nah");
      reichweite_m=Reichweite->getIntAttr("mittel");
      reichweite_f=Reichweite->getIntAttr("fern");
   }

   const Tag *Lernkosten=t.find("Lernkosten");
   if (Lernkosten)
   {  lern_land=Lernkosten->getIntAttr("Land",99);
      lern_stadt=Lernkosten->getIntAttr("Stadt",99);
   }

   FOR_EACH_CONST_TAG_OF(i,t,"Voraussetzungen_F")
     vec_voraussetzung_F.push_back(i->getAttr("Name"));
   FOR_EACH_CONST_TAG_OF(i,t,"Voraussetzungen_W")
     vec_voraussetzung_W.push_back(i->getAttr("Name"));
             

    FOR_EACH_CONST_TAG_OF(i,t,"regionaleBesonderheit")
         VAusnahmen.push_back(st_ausnahmen(i->getAttr("Herkunft"),
                              i->getAttr("Spezies"),
                              i->getAttr("Typ"),
                              i->getAttr("Beruf"),
                              i->getAttr("Stand"),
                              i->getAttr("Standard")));
}

std::list<cH_MidgardBasicElement> Waffe::getAllgemeinwissen(const std::list<cH_MidgardBasicElement> &L)
{
  std::list<cH_MidgardBasicElement> S;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=L.begin();i!=L.end();++i)
     if((*i)->LernLand() || (*i)->LernStadt()) S.push_back(*i);
  return S;
}

void Waffe::get_Alias(const Tag &t) 
{
    FOR_EACH_CONST_TAG_OF(i,t,"regionaleVariante")
    {  int Angriff=0;
       const Tag *Modifikationen=i->find("Modifikationen");
       if (Modifikationen) Angriff=Modifikationen->getIntAttr("Angriff");
       list_alias.push_back(st_alias(i->getAttr("Name"),i->getAttr("Region"),
       		i->getAttr("Schaden"),i->getIntAttr("Schadensbonus"),
            i->getIntAttr("St"),Angriff));
       Waffe_from_Alias[i->getAttr("Name")]=Name();
    }
}


bool Waffe::Grundkenntnis_vorhanden(const std::list<MBEmlt>& list_WaffenGrund) const
{
 for (std::list<MBEmlt>::const_iterator i=list_WaffenGrund.begin();i!=list_WaffenGrund.end();++i)
   if (Grundkenntnis()==(*(*i))->Name()) return true;
 return false;
}

bool Waffe::Min_St_Einhand(const Grundwerte &W) const
{
   if(W.St() >= min_st_einhand) return true;
   return false;
}

bool Waffe::Voraussetzung(const Abenteurer &A,bool anzeigen) const
{
 const Grundwerte &Werte=A.getWerte();
 if ( St()>Werte.St() || Gw()>Werte.Gw() || Gs()>Werte.Gs() ) return false;
 if(anzeigen) return true;

 const std::list<MBEmlt> &list_Fertigkeit=A.List_Fertigkeit();
 const std::list<MBEmlt> &list_Waffen=A.List_Waffen();
 std::list<MBEmlt> L=list_Fertigkeit;
 for(std::list<MBEmlt>::const_iterator j=list_Waffen.begin();j!=list_Waffen.end();++j)
   L.push_back(*j);
     
 std::vector<std::string> VF=vec_voraussetzung_F;
 for(std::vector<std::string>::const_iterator i=vec_voraussetzung_W.begin();i!=vec_voraussetzung_W.end();++i)
   VF.push_back(*i);   

FertEnd:
 for(std::vector<std::string>::iterator i=VF.begin();i!=VF.end();++i)
   {
    for(std::list<MBEmlt>::const_iterator j=L.begin();j!=L.end();++j)
      {
        if((*i)==(*(*j))->Name()) 
          { VF.erase(i);
            goto FertEnd;
          }
      }
     return false;
   }
 return true;
}

std::string add_plus_or_minus(std::string &s,const int sb)
{
  if(s.find("|")!=std::string::npos) s="("+s+")";
  if     (sb == 0) return s;
  else if(sb  > 0) return s+"+"+itos(sb);
  else if(sb  < 0) return s+itos(sb);
  abort();
}


std::string WaffeBesitz::Schaden(const Grundwerte& Werte,const std::string& name) const
{
  if (Waffe()->Art()=="Verteidigung") 
     return itos(Waffe()->Schaden_Bonus(name))+"AP";

  std::string s=Waffe()->Schaden(name);
  int sb =Waffe()->Schaden_Bonus(name) + sl_Bonus();
  int sb2=Waffe()->Schaden_Bonus2(name) + sl_Bonus();
  // Nicht stark genug fürs Einhändige Tragen dieser Waffe?
  if(Waffe()->Text().find("Einhändig")!=std::string::npos &&
       !Waffe()->Min_St_Einhand(Werte)) sb2=sb;

  if ( Waffe()->Grundkenntnis() == "Kampf ohne Waffen" ) 
      { s="W6";
        int w = Erfolgswert();
        if      (w <= 7) sb=-4;
        else if (w <=11) sb=-3;
        else if (w <=15) sb=-2;
        else             sb=-1;
        if(name=="Kampfriemen") sb+=1;
      }
  if (Waffe()->Art()!="Schußwaffe" && Waffe()->Art()!="Wurfwaffe") 
    {  sb += Werte.bo_Sc(); sb2 += Werte.bo_Sc();}
  if(sb==sb2)  return add_plus_or_minus(s,sb); 
  else         return add_plus_or_minus(s,sb)+"|"+itos(sb2);
}

std::string WaffeBesitz::Bonus() const 
{ 
  if (Magisch()=="" && av_Bonus()==0 && sl_Bonus()==0 ) return "";
  return "("+itos(av_Bonus())+"/"+itos(sl_Bonus())+")";
}



std::string Waffe::Reichweite() const
{  
   if(reichweite_0==-1) return ""; // postgres
   else if (reichweite_0==0 && reichweite_n==0 && 
            reichweite_m==0 && reichweite_n==0) return ""; // xml
   return itos(reichweite_0)+"/"+itos(reichweite_n)+"/"+
               itos(reichweite_m)+"/"+itos(reichweite_f);
}

std::string Waffe::WM_Abwehr() const
{
  std::string s1=wm_abwehr_leicht, s2 = wm_abwehr_schwer;
  if (s1=="" && s2=="") return "";
  if (s1=="") s1="0";
  if (s2=="") s2="0";
  return s1+"|"+s2;
}


int Waffe::WM_Angriff(const std::string& name) const 
{
  if(Name()==name) return 0;
  for(std::list<st_alias>::const_iterator i=list_alias.begin();i!=list_alias.end();++i)
    if (name==(*i).name) return (*i).angriffs_mod;
  assert(false);
}

std::string Waffe::Schaden(const std::string& name) const 
{
//cout << "Schaden: "<<name<<' '<<schaden<<'\n';
  if(Name()==name) return schaden;
  for(std::list<st_alias>::const_iterator i=list_alias.begin();i!=list_alias.end();++i)
    if (name==(*i).name) 
      return (*i).schaden;
  assert(false);
}

int Waffe::Schaden_Bonus2(const std::string& name) const 
{
  if(Name()==name) return schaden_bonus2;
  for(std::list<st_alias>::const_iterator i=list_alias.begin();i!=list_alias.end();++i)
    if (name==(*i).name) return (*i).schaden_bonus;
  assert(false);
}

int Waffe::Schaden_Bonus(const std::string& name) const 
{
  if(Name()==name) return schaden_bonus;
  for(std::list<st_alias>::const_iterator i=list_alias.begin();i!=list_alias.end();++i)
    if (name==(*i).name) return (*i).schaden_bonus;
  assert(false);
}

std::string Waffe::Region(const std::string& name) const
{
  if(Name()==name) return region;
  for(std::list<st_alias>::const_iterator i=list_alias.begin();i!=list_alias.end();++i)
   if (name==(*i).name) return (*i).region;
  assert(false);
}


std::string Waffe::Schwierigkeit_str() const
{
  switch(Schwierigkeit()) {
    case 0: return "Verteidigung";
    case 1: return "extrem leicht";
    case 2: return "sehr leicht";          
    case 3: return "leicht";
    case 4: return "normal";
    case 5: return "schwer";
    case 6: return "sehr schwer";
    case 7: return "extrem schwer";
   }
  return itos(Schwierigkeit());
}

int Waffe::MaxErfolgswert(const Abenteurer &A) const
{
 assert(A.getVTyp().size()==2);
 int maxwert=0;
 double x=Standard_Faktor(A);

 if (art == "Verteidigung")
  {
    if (A.Typ1()->Zaubern() == "z" && A.Typ2()->Short()!="") maxwert = 6;
    else
     {
      if     (x==1.0)  maxwert = 7;
      else if(x==0.5)  maxwert = 8;
      else if(x==2.0)  maxwert = 6;
      else assert(!"Auf Fixedpoint umstellen");
     }
  }
 else
  {
    if (A.Typ1()->Zaubern() == "z" && A.Typ2()->Short()=="") maxwert = 14;
    else
     {
      if     (x==1.0)  maxwert = 17;
      else if(x==0.5)  maxwert = 19;
      else if(x==2.0)  maxwert = 14;
      else assert(!"Auf Fixedpoint umstellen");
     }
  }
 return maxwert;
}


std::string Waffe::get_Verteidigungswaffe(int ohne_waffe,
   const std::list<MBEmlt>& list_Waffen,
   const std::list<H_WaffeBesitz>& list_Waffen_besitz,
   const Abenteurer &A)
{
   std::list<H_WaffeBesitz> Verteidigungswaffen;
//   MBEmlt wl(&*cH_Waffe("waffenloser Kampf"));
   cH_Waffe wl("waffenloser Kampf");
   Verteidigungswaffen.push_back(new WaffeBesitz(wl,wl->Name(),0,0,"",""));
   for (std::list<H_WaffeBesitz>::const_iterator i=list_Waffen_besitz.begin();
         i!=list_Waffen_besitz.end();++i)
     {
       H_WaffeBesitz WB(*i);
       if (WB->Waffe()->Art()=="Verteidigung" || (*WB)->Name()=="Kampfstab" || (*WB)->Name()=="Sai" ||
          (*WB)->Name()=="Tonfa" || (*WB)->Name()=="GunSen" || (*WB)->Name()=="BuKasa" || 
          (*WB)->Name()=="KusariGama" || (*WB)->Name()=="TetsuBo" ) 
         Verteidigungswaffen.push_back(*i);
     }
   std::string Vwaffewert;
   for(std::list<H_WaffeBesitz>::const_iterator i=Verteidigungswaffen.begin();
         i!=Verteidigungswaffen.end();/*siehe unten*/)
     {
      H_WaffeBesitz WB=*i;
      std::vector<int> vwert;
      for (std::list<MBEmlt>::const_iterator j=list_Waffen.begin();j!=list_Waffen.end();++j)      
         { cH_Waffe w((*j)->getMBE());
            if ((*WB)->Name() == w->Name()) 
               { 
                 int erf_wert;
                 if ((*WB)->Name()=="Kampfstab"||(*WB)->Name()=="Sai"||(*WB)->Name()=="Tonfa"||(*WB)->Name()=="KusariGama") 
                  {erf_wert = (*j)->Erfolgswert()-5; (erf_wert<=7)?:erf_wert=7; }
                 else if ((*WB)->Name()=="TetsuBo")
                  {erf_wert = (*j)->Erfolgswert()-7; (erf_wert<=7)?:erf_wert=7; }
                 else if ((*WB)->Name()=="GunSen"||(*WB)->Name()=="BuKasa")
                  {erf_wert = (*j)->Erfolgswert(); (erf_wert<=10)?:erf_wert=10; }
                 else if ((*WB)->Name()=="waffenloser Kampf")
                  {if ( (*j)->Erfolgswert()<8)              break       ;
                   if ( 8<=(*j)->Erfolgswert()&&(*j)->Erfolgswert()<12) erf_wert = 1;
                   if (12<=(*j)->Erfolgswert()&&(*j)->Erfolgswert()<16) erf_wert = 2;
                   if (16<=(*j)->Erfolgswert())                      erf_wert = 3;
                  }
                 else erf_wert = (*j)->Erfolgswert();
                 int ewert = A.getWerte().Abwehr_wert()+A.getWerte().bo_Ab() // Grundwerte
                           + erf_wert + WB->av_Bonus() ;// Waffenwerte
                 Vwaffewert += itos0p(ewert,-1,true);
               }
         }
       ++i;
       if (i!=Verteidigungswaffen.end() && Vwaffewert!="") Vwaffewert += "|"; 
     }
   return Vwaffewert;
}



void Waffe::setSpezialWaffe(const std::string& name,std::list<MBEmlt>& list_Waffen_gelernt)
{
  for(std::list<MBEmlt>::iterator i=list_Waffen_gelernt.begin();i!=list_Waffen_gelernt.end();++i)
   {
    if(name==(*(*i))->Name()) 
        (*i)->setErfolgswert(7);
    else if(cH_Waffe((*i)->getMBE())->Verteidigung())
         (*i)->setErfolgswert(1);
    else (*i)->setErfolgswert(5);
   }
}

static MidgardBasicElement::EP_t Waffe_EP=MidgardBasicElement::EP_t_undefined;

Waffe::Waffe(const Tag &t)
      : MidgardBasicElement(t.getAttr("Name")), lern_land(),lern_stadt()
{ load(t); }

void Waffe::load(const Tag &t)
{get_Waffe(t);get_Alias(t);get_map_typ(t);get_Steigern_Kosten_map();
 if (Waffe_EP==EP_t_undefined) Waffe_EP=EP_steigern("Waffen");
 else EP_steigern(Waffe_EP);
}

cH_Waffe cH_Waffe::load(const Tag &t,bool &is_new)
{  cH_Waffe *res=cache.lookup(t.getAttr("Name"));
   if (!res)
   {  cH_Waffe r2=new Waffe(t);
      is_new=true;
      cache.Register(t.getAttr("Name"),r2);
      return r2;
   }
   else 
   {  const_cast<Waffe&>(**res).load(t);
      return *res;
   }
}

void Waffe_All::load(std::list<cH_MidgardBasicElement> &list,const Tag &t)
{  bool is_new=false;
   cH_Waffe z=cH_Waffe::load(t,is_new);
   // das &* dient dazu um aus einem cH_Waffe ein cH_MBE zu machen
   if (is_new) list.push_back(&*z);
}

cH_Waffe Waffe::WaffeVonBezeichnung(const std::string &name)
{  std::map<std::string,std::string>::const_iterator i=Waffe_from_Alias.find(name);
   if (i!=Waffe_from_Alias.end()) return cH_Waffe(i->second);
   return cH_Waffe(name,true);
}

std::map<std::string,std::string> Waffe::Waffe_from_Alias;
