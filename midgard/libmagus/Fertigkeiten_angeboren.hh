/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

#ifndef _FERTIGKEITEN_A_HH
#  define _FERTIGKEITEN_A_HH
#include <list>
#include "MidgardBasicElement.hh"
#include <Misc/Tag.h>

class Fertigkeit_angeborene : public MidgardBasicElement
{
     int min,max;

     void get_Fertigkeit(const Tag &t);
  public:
     Fertigkeit_angeborene(const Tag &tag);

     enum MBEE What() const {return MidgardBasicElement::FERTIGKEIT_ANG;}
     std::string What_str() const {return "ang.Fertigkeit";}

     int FErfolgswert(const Abenteurer &a,const MBEmlt &mbem) const;
     int Min() const {return min;}
     int Max() const {return max;}
     int MaxErfolgswert(const Grundwerte& w,const std::vector<cH_Typen>& Typ) const 
         {return 0;} //wg. virtueller Funktion
};

class cH_Fertigkeit_angeborene : public Handle<const Fertigkeit_angeborene>
{
    typedef CacheStatic<std::string,cH_Fertigkeit_angeborene> cache_t;
    static cache_t cache;
    friend class std::map<std::string,cH_Fertigkeit_angeborene>;
    cH_Fertigkeit_angeborene(){};
 public:
    cH_Fertigkeit_angeborene(const std::string& n ,bool create=false);
    static cH_Fertigkeit_angeborene load(const Tag &tag);
    cH_Fertigkeit_angeborene(const Fertigkeit_angeborene *r) : Handle<const Fertigkeit_angeborene>(r){}

    cH_Fertigkeit_angeborene(const cH_MidgardBasicElement &x) : Handle<const Fertigkeit_angeborene>
      (dynamic_cast<const Fertigkeit_angeborene *>(&*x)){}
};

namespace Fertigkeiten_angeborene_All 
{  void load(std::list<cH_MidgardBasicElement> &list, const Tag &t);
}

#endif
