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

#include <gtk--/progressbar.h>
#include "MidgardBasicElement.hh"

class BerufsKategorie
{
 public:
      bool kat_I, kat_II, kat_III, kat_IV;
      BerufsKategorie()
       : kat_I(false),kat_II(false),kat_III(false),kat_IV(false) {} 

      BerufsKategorie(bool a,bool b, bool c, bool d)
       : kat_I(a),kat_II(b),kat_III(c),kat_IV(d) {}
};


class Beruf : public MidgardBasicElement
{
   private:
      std::string geschlecht; 
      int klasse;
      vector<std::string> vorteile;
      bool u,v,m,a,typ_k,typ_z,stadt,land;
      
     void get_Beruf();      
  public:
//      Beruf() {}
      Beruf(const Tag *t) : MidgardBasicElement(t,t->getAttr("Name"))
          {get_Beruf();}

     enum MBEE What() const {return MidgardBasicElement::BERUF;}
     std::string What_str() const {return "Beruf";}

     bool Stand(const std::string& stand) const;
     bool Typ(const vector<cH_Typen>& Typ) const;
     bool Land() const {return land;}
     bool Stadt() const {return stadt;}

     std::vector<string> Vorteile() const {return vorteile;}
     std::string Beruf::get_Vorteile() const;
     int MaxErfolgswert(const Grundwerte& w,const vector<cH_Typen>& Typ) const 
         {return 0;} //wg. virtueller Funktion

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
    cH_Beruf(const Tag *tag);

    cH_Beruf(const cH_MidgardBasicElement &x) : Handle<const Beruf>
      (dynamic_cast<const Beruf *>(&*x)){}
};

class Beruf_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   Beruf_All(Gtk::ProgressBar *progressbar);
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};

#endif
