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

#ifndef _SINNE_HH
#  define _SINNE_HH

#include "MidgardBasicElement.hh"


class Sinne : public MidgardBasicElement
{
  private:
     void get_Sinne();      
  public:
      Sinne(const Tag *t) : MidgardBasicElement(t,t->getAttr("Name"))
          {get_Sinne();}

     enum MBEE What() const {return MidgardBasicElement::SINN;}
     std::string What_str() const {return "Sinn";}

     int MaxErfolgswert(const Grundwerte& w,const vector<cH_Typen>& Typ) const 
         {return 0;} //wg. virtueller Funktion

};


class cH_Sinne : public Handle<const Sinne>
{
    typedef CacheStatic<std::string,cH_Sinne> cache_t;
    static cache_t cache;
    cH_Sinne(const Sinne *s) : Handle<const Sinne>(s) {};
    friend class std::map<std::string,cH_Sinne>;
    cH_Sinne(){};
 public:
    cH_Sinne(const std::string& n,bool create=false);
    cH_Sinne(const Tag *tag);

    cH_Sinne(const cH_MidgardBasicElement &x) : Handle<const Sinne>
      (dynamic_cast<const Sinne *>(&*x)){}
};

class Sinne_All
{
   std::list<MidgardBasicElement_mutable> list_All;
  public:
   Sinne_All();
   std::list<MidgardBasicElement_mutable> get_All() const {return list_All;}
};

#endif
