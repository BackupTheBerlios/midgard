// $Id: Typen.hh,v 1.23 2002/07/03 10:25:34 thoma Exp $               
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

#ifndef CLASS_TYPEN_
#define CLASS_TYPEN_

#include<string>
#include <Misc/Handles.h>
#include <Misc/CacheStatic.h>
#include <vector>
#include <string>
#include <gtk--/progressbar.h>
#include "xml.h"

class Grundwerte;
class cH_Typen;
class cH_Land;

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

   std::vector<std::string> vec_herkunft;
   std::vector<std::string> vec_gruppe;


public:
   Typen(const Tag *tag);
   Typen() : typnr(0),stand(0),sb(0),ruestung(0),geld(0),
         stadt(true),land(true),nsc_only(false),
         min_st(0),min_gw(0),min_gs(0),min_in(0),min_pa(0) {}
   
   std::string Name(const std::string& geschlecht) const 
      { if (geschlecht=="m") return typl; else return typlw;}
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
   const std::vector<std::string> &get_vec_herkunft() const {return vec_herkunft;}
   const std::vector<std::string> &get_vec_gruppe() const {return vec_gruppe;}
   bool Gruppe(const std::string &gruppe) const;


   bool is_mage() const 
    { if(Zaubern()=="z" || Zaubern()=="j") return true; else return false; } 
   
   bool operator==(const Typen &b) const
   {  return typs==b.typs;
   }
   bool operator<(const Typen &b) const
   {  return typs<b.typs;
   }

   static bool get_Typ_from_long(const std::vector<cH_Typen>& V,
                                        std::string& name);
};

class cH_Typen : public Handle<const Typen>    
{
    typedef CacheStatic<std::string,cH_Typen> cache_t;
    static cache_t cache;
    friend class std::map<std::string,cH_Typen>;
  public:
   cH_Typen() {*this=new Typen();}
   cH_Typen(const std::string& name IF_XML(,bool create=false));
   cH_Typen(const Tag *tag);
   cH_Typen(const Typen *s) : Handle<const Typen>(s) {};
};
 
class Typen_All
{
      std::vector<cH_Typen> list_All;
   public:
      Typen_All(Gtk::ProgressBar *progressbar);
      std::vector<cH_Typen> get_All() const {return list_All;}
};

bool operator==(gpointer p,const cH_Typen &t);

#endif
