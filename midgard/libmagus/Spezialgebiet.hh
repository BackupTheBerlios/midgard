// $Id: Spezialgebiet.hh,v 1.1 2003/05/06 07:12:04 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2002 Christof Petig
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

#ifndef CLASS_SPEZ_
#define CLASS_SPEZ_

#include<string>
#include <Misc/Handles.h>
#include <Misc/CacheStatic.h>
#include <vector>
#include <string>
#include "xml.h"

class Spezialgebiet : public HandleContent
{
   std::string typ;
   int nr;
   std::string name;
   std::string spezial;
   std::string spezial2;

public:
   Spezialgebiet(const Tag *tag);
   Spezialgebiet() : nr(0) {}

   std::string Typ() const {return typ;}   
   std::string Name() const {return name;}   
   std::string Spezial() const {return spezial;}   
   std::string Spezial2() const {return spezial2;}   

   bool operator==(const Spezialgebiet &b) const
      {  return Name()==b.Name();  }
};

class cH_Spezialgebiet : public Handle<const Spezialgebiet>    
{
    typedef CacheStatic<std::string,cH_Spezialgebiet> cache_t;
    static cache_t cache;
    friend class std::map<std::string,cH_Spezialgebiet>;
  public:
   cH_Spezialgebiet() {*this=new Spezialgebiet();}
   cH_Spezialgebiet(const std::string& name);
   cH_Spezialgebiet(const Tag *tag);
   cH_Spezialgebiet(const Spezialgebiet *s) : Handle<const Spezialgebiet>(s) {};

   static bool is_cached(const std::string s);
};
 
class Spezialgebiet_All
{
      std::vector<cH_Spezialgebiet> list_All;
   public:
      Spezialgebiet_All();
      std::vector<cH_Spezialgebiet> get_All() const {return list_All;}
};

bool operator==(void *p,const cH_Spezialgebiet &t);
  
#endif
