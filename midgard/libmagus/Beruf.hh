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

#ifndef _BERUF_HH
#  define _BERUF_HH

#include "MidgardBasicElement.hh"
class VAbenteurer;
#include <Misc/Tag.h>

class BerufsKategorie
{
 public:
      bool kat_I, kat_II, kat_III, kat_IV;
      BerufsKategorie()
       : kat_I(false),kat_II(false),kat_III(false),kat_IV(false) {} 

      BerufsKategorie(bool a,bool b, bool c, bool d)
       : kat_I(a),kat_II(b),kat_III(c),kat_IV(d) {}

      std::string wuerfeln(int wurf);
};


class Beruf : public MidgardBasicElement
{
   public:
      struct st_vorteil{std::string name;int wert;bool gelernt;int kat;
             st_vorteil(std::string n,int w) 
               : name(n),wert(w),gelernt(),kat(-1) {}};
   private:
      std::string geschlecht; 
      int klasse;
      std::vector<st_vorteil> vorteile;
      bool u,v,m,a,typ_k,typ_z,stadt,land;
      
  public:
      Beruf(const Tag &t);
      void load(const Tag &t);

     enum MBEE What() const {return MidgardBasicElement::BERUF;}
     std::string What_str() const {return "Beruf";}

     bool Stand(const std::string& stand) const;
     bool Typ(const std::vector<cH_Typen>& Typ) const;
     bool Land() const {return land;}
     bool Stadt() const {return stadt;}

     const std::vector<st_vorteil> &Vorteile() const {return vorteile;}
     int MaxErfolgswert(const Grundwerte& w,const std::vector<cH_Typen>& Typ) const 
         {return 0;} //wg. virtueller Funktion

      // true = Zusatzfertigkeit
     static bool Berufsfertigkeit(Abenteurer& A,st_vorteil F);

};


class cH_Beruf : public Handle<const Beruf>
{
    typedef CacheStatic<std::string,cH_Beruf> cache_t;
    static cache_t cache;
    cH_Beruf(const Beruf *s) : Handle<const Beruf>(s) {};
    friend class std::map<std::string,cH_Beruf>;
    cH_Beruf(){};
 public:
    cH_Beruf(const std::string& n ,bool create=false);
    static cH_Beruf load(const Tag &t,bool &is_new);

    cH_Beruf(const cH_MidgardBasicElement &x) : Handle<const Beruf>
      (dynamic_cast<const Beruf *>(&*x)){}
};

class Beruf_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   Beruf_All();
   static void load(std::list<cH_MidgardBasicElement> &list, const Tag &t);
   const std::list<cH_MidgardBasicElement> &get_All() const {return list_All;}
};

#endif
