// $Id: Schrift.hh,v 1.26 2002/10/24 07:21:01 christof Exp $               
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

#ifndef SCHRIFTCLASS
#define SCHRIFTCLASS
#include "MidgardBasicElement.hh"
#include "Typen.hh"
#include "Fertigkeiten.hh"
class Abenteurer;

class Schrift : public MidgardBasicElement
{
    std::string art_der_schrift;
    bool alt,kult;

     void get_Schrift();
     int Grundkosten() const {return kosten;}
  
  public:
   Schrift(const std::string& name,const Tag *t) : MidgardBasicElement(t,name)
      { get_Schrift();get_map_typ(); get_Steigern_Kosten_map();
        EP_steigern("Schreiben");
      }
   enum MBEE What() const {return MidgardBasicElement::SCHRIFT;}
   std::string What_str() const {return "Urschrift";}

   std::string Art_der_Schrift() const   {return art_der_schrift; }

   bool Kult() const {return kult;}
   bool Alt() const {return alt;}
   bool kann_Sprache(const std::list<MBEmlt>& sprache) const;
   bool Mutterschrift(const Abenteurer& A) const;
//   int MaxErfolgswert(const Grundwerte& w,const std::vector<cH_Typen>& Typ) const;
   int MaxErfolgswert(const Abenteurer &A) const;
   int Kosten(const Abenteurer &A) const
        { cH_Fertigkeit F("Lesen/Schreiben");
             return  (int)(F->Standard_Faktor(A) * kosten) ; }
   std::list<cH_MidgardBasicElement> gleicheSchrift(const std::list<cH_MidgardBasicElement>& listSchrift) const;
};

class cH_Schrift : public Handle<const Schrift>
{
    typedef CacheStatic<std::string,cH_Schrift> cache_t;
    static cache_t cache;
    cH_Schrift(const Schrift *s) : Handle<const Schrift>(s) {};
    friend class std::map<std::string,cH_Schrift>;
    cH_Schrift(){};
  public:
   cH_Schrift(const std::string& name ,bool create=false);
   cH_Schrift(const std::string& name,const Tag *tag);

   cH_Schrift(const cH_MidgardBasicElement &x) : Handle<const Schrift>
      (dynamic_cast<const Schrift *>(&*x)){}
};

class Schriften_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   Schriften_All();
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};

#endif
