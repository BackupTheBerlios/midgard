// $Id: Land.hh,v 1.3 2003/09/01 06:47:57 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#ifndef LANDCLASS
#define LANDCLASS
#include <Misc/Handles.h>
#include <Misc/CacheStatic.h>
#include <list>
#include <vector>
#include <string>
class Tag;
//#include "xml.h"
//class cH_Typen;
class Abenteurer;
class cH_Land;

class Land  : public HandleContent
{
   std::string name; 
   std::string kontinent;
   std::string region;
   std::vector<std::string> vec_sprache;
   std::vector<std::string> nachbarlaender;

  public:
   Land() {};
   Land(const std::string& kontinent, const Tag &tag);

   const std::string &Name() const   {return name; }
   const std::string &Kontinent() const {return kontinent;}
   const std::string &Region() const {return region;}
   const std::vector<std::string> &Sprachen() const {return vec_sprache;}
   const std::vector<std::string> &Nachbarlaender() const {return nachbarlaender;}
   bool ist_erlaubt(const Abenteurer& A) const;
   static bool ist_bekannt(std::string s,const std::vector<cH_Land>& L);
};

class cH_Land : public Handle<const Land>
{
    typedef CacheStatic<std::string,cH_Land> cache_t;
    static cache_t cache;
    friend class std::map<std::string,cH_Land>;
  public:
   cH_Land(const Land *s) : Handle<const Land>(s) {};
   static cH_Land load(const std::string& kontinent, const Tag &tag);
   cH_Land(const std::string& name, bool create=false);
   cH_Land() {} // *this=new Land();}
};

namespace Laender_All
{  void load(std::list<cH_Land> &list, const std::string& kontinent, const Tag &t);
   void load(std::vector<cH_Land> &list, const std::string& kontinent, const Tag &t);
}

#endif
