// $Id: Land.hh,v 1.1 2003/05/06 07:12:04 christof Exp $               
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

#ifndef LANDCLASS
#define LANDCLASS
#include <Misc/Handles.h>
#include <Misc/CacheStatic.h>
#include <vector>
#include <string>
#include "xml.h"
//class cH_Typen;
class Abenteurer;
class cH_Land;

class Land  : public HandleContent
{
   std::string name; 
   std::string kontinent;
   std::vector<std::string> vec_sprache;
   std::vector<std::string> nachbarlaender;

  public:
   Land() {};
   Land(const std::string& kontinent, const Tag *tag);

   std::string Name() const   {return name; }
   std::string Kontinent() const {return kontinent;}
   std::vector<std::string> Sprachen() const {return vec_sprache;}
   std::vector<std::string> Nachbarlaender() const {return nachbarlaender;}
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
   cH_Land(const std::string& kontinent, const Tag *tag);
   cH_Land(const std::string& name, bool create=false);
   cH_Land() {*this=new Land();}
};

class Laender_All
{
   std::vector<cH_Land> list_All;
  public:
   Laender_All();
   std::vector<cH_Land> get_All() const {return list_All;}
};

#endif
