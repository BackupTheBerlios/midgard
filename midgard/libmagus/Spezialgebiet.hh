// $Id: Spezialgebiet.hh,v 1.3 2003/05/26 06:23:35 christof Exp $               
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

#ifndef CLASS_SPEZ_
#define CLASS_SPEZ_

#include<string>
#include <Misc/Handles.h>
#include <Misc/CacheStatic.h>
#include <vector>
#include <string>
class Tag;

class Spezialgebiet : public HandleContent
{
   std::string typ;
   int nr;
   std::string name;
   std::string spezial;
   std::string spezial2;

public:
   Spezialgebiet(const Tag &tag);
   Spezialgebiet() : nr() {}

   const std::string &Typ() const {return typ;}   
   const std::string &Name() const {return name;}   
   const std::string &Spezial() const {return spezial;}   
   const std::string &Spezial2() const {return spezial2;}   

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
   static cH_Spezialgebiet load(const Tag &tag);
   cH_Spezialgebiet(const Spezialgebiet *s) : Handle<const Spezialgebiet>(s) {};

   static bool is_cached(const std::string s);
};
 
namespace Spezialgebiet_All
{  void load(std::vector<cH_Spezialgebiet> &list,const Tag &t);
};

bool operator==(void *p,const cH_Spezialgebiet &t);
  
#endif
