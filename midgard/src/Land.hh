// $Id: Land.hh,v 1.14 2002/06/24 10:51:30 christof Exp $               
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
#include <gtk--/progressbar.h>
#include "xml.h"

class Land  : public HandleContent
{
   std::string name; 
   std::string kontinent;
   vector<std::string> vec_sprache;

  public:
   Land() {};
#ifndef USE_XML   
   Land(const std::string& n);
#else
   Land(const std::string& kontinent, const Tag *tag);
#endif   

   std::string Name() const   {return name; }
   std::string Kontinent() const {return kontinent;}
   vector<std::string> Sprachen() const {return vec_sprache;}
};

class cH_Land : public Handle<const Land>
{
    typedef CacheStatic<std::string,cH_Land> cache_t;
    static cache_t cache;
    friend class std::map<std::string,cH_Land>;
//    cH_Land(){};
  public:
   cH_Land(const Land *s) : Handle<const Land>(s) {};
#ifdef USE_XML   
   cH_Land(const std::string& kontinent, const Tag *tag);
#endif   
   cH_Land(const std::string& name IF_XML(,bool create=false));
   cH_Land() {*this=new Land();}
};

class Laender_All
{
   std::vector<cH_Land> list_All;
  public:
   Laender_All(Gtk::ProgressBar *progressbar);
   std::vector<cH_Land> get_All() const {return list_All;}
};

#endif
