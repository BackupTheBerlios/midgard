// $Id: Spezialgebiet.hh,v 1.5 2002/01/12 08:12:25 thoma Exp $               
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

#ifndef CLASS_SPEZ_
#define CLASS_SPEZ_

#include<string>
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include <vector>
#include <string>
#include <gtk--/progressbar.h>


class Spezialgebiet : public HandleContent
{
   std::string typ;
   int nr;
   std::string name;
   std::string spezial;
   std::string spezial2;

public:
   Spezialgebiet(const std::string& _name);
   Spezialgebiet() : nr(0) {}

   std::string Typ() const {return typ;}   
   std::string Name() const {return name;}   
   std::string Spezial() const {return spezial;}   
   std::string Spezial2() const {return spezial2;}   
   
};

class cH_Spezialgebiet : public Handle<const Spezialgebiet>    
{
    typedef CacheStatic<std::string,cH_Spezialgebiet> cache_t;
    static cache_t cache;
//    cH_Spezialgebiet(Spezialgebiet *s) : Handle<const Spezialgebiet>(s) {};
    friend class std::map<std::string,cH_Spezialgebiet>;
///    cH_Typen(){};
  public:
   cH_Spezialgebiet() {*this=new Spezialgebiet();}
   cH_Spezialgebiet(const std::string& name);
   cH_Spezialgebiet(const Spezialgebiet *s) : Handle<const Spezialgebiet>(s) {};

   static bool is_cached(const std::string s);
};
 
class Spezialgebiet_All
{
      std::vector<cH_Spezialgebiet> list_All;
   public:
      Spezialgebiet_All(Gtk::ProgressBar *progressbar);
      std::vector<cH_Spezialgebiet> get_All() const {return list_All;}
};
  
#endif
