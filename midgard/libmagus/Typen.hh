// $Id: Typen.hh,v 1.5 2004/03/12 15:20:04 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2003 Christof Petig
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

#ifndef CLASS_TYPEN_
#define CLASS_TYPEN_

#include<string>
#include <Misc/Handles.h>
#include <Misc/CacheStatic.h>
#include <vector>
#include <string>
#include <list>
//#include "xml.h"
#include "Enums.hh"

class Grundwerte;
class cH_Typen;
class cH_Land;
class Tag;

class Typen : public HandleContent
{
   std::string typs;
   int typnr;
   std::string typl,typlw,typz;
   std::string zaubern,ausdauer,region,beruf;
   int stand,sb,ruestung,geld;
   bool stadt,land;
   std::string sprueche_mit_pp;
   bool nsc_only,kultwaffe;
   int min_st,min_gw,min_gs,min_in,min_pa;

public:
   struct st_herkunft{std::string land; std::string kultwaffe;
          st_herkunft(std::string l,std::string k):land(l),kultwaffe(k){}};
private:
   std::vector<st_herkunft> vec_herkunft;
   std::vector<std::string> vec_gruppe;
   std::string lernpflichten_info;
   bool lernpflicht_schrift;

public:
   Typen(const Tag &tag);
   Typen() : typnr(),stand(),sb(),ruestung(),geld(),
         stadt(true),land(true),nsc_only(),
         min_st(),min_gw(),min_gs(),min_in(),min_pa(),
         lernpflicht_schrift() {}
   
   bool Valid() const;
   std::string Name(const Enums::geschlecht& geschlecht) const 
      { if (geschlecht==Enums::Mann) return typl; else return typlw;}
   std::string Typl() const {return typl;}
   std::string Typlw() const {return typlw;}
   std::string Short() const {return typs;}
   std::string Zaubern() const {return typz;}
   std::string Ausdauer() const {return ausdauer;}
   int Stand() const {return stand;}
   int Sb() const {return sb;}
   int Ruestung() const {return ruestung;}
   int Geld() const {return geld;}
   std::string Region() const {return region;}
   std::string Beruf() const {return beruf;}
   bool Land() const {return land;}
   bool Stadt() const {return stadt;}
   bool SpruecheMitPP() const {return !sprueche_mit_pp.empty();}
   std::string SpruecheMitPP_Text() const {return sprueche_mit_pp;}
   bool NSC_only() const {return nsc_only;}
   bool Kultwaffe() const {return kultwaffe;}
   bool Spezialwaffe() const;
   bool Spezialgebiet() const;
   bool Mindestwerte(const Grundwerte& Werte) const;
//   bool Herkunft(cH_Land land) const;
   const std::vector<st_herkunft> &get_vec_herkunft() const {return vec_herkunft;}
   const std::vector<std::string> &get_vec_gruppe() const {return vec_gruppe;}
   bool Gruppe(const std::string &gruppe) const;
   std::string getLernpflichtenInfo(cH_Land herkunft) const;
   bool getLernpflichtSchrift() const {return lernpflicht_schrift;}

   bool is_mage() const 
    { if(Zaubern()=="z" || Zaubern()=="j") return true; else return false; } 
   
   bool operator==(const Typen &b) const
   {  return typs==b.typs;
   }
   bool operator<(const Typen &b) const
   {  return typs<b.typs;
   }

   // KurzTyp zum Langtyp heraussuchen (verändert name auf jeden Fall)
   static bool get_Typ_from_long(std::string& name);
   // die sinnvolle Variante
   static cH_Typen getTyp(const std::string &langbez); //  throw(NotFound)

};

class cH_Typen : public Handle<const Typen>    
{
    typedef CacheStatic<std::string,cH_Typen> cache_t;
    static cache_t cache;
    friend class std::map<std::string,cH_Typen>;
  public:
   cH_Typen() {*this=new Typen();}
   cH_Typen(const std::string& name ,bool create=false);
   static cH_Typen load(const Tag &tag);
   cH_Typen(const Typen *s) : Handle<const Typen>(s) {};
};
 
namespace Typen_All
{  void load(std::list<cH_Typen> &list, const Tag &t);
   void load(std::vector<cH_Typen> &list, const Tag &t);
}

bool operator==(void *p,const cH_Typen &t);

#endif
