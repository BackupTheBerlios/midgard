// $Id: Region.hh,v 1.5 2002/01/18 11:26:00 thoma Exp $               
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

#ifndef REGIONCLASS
#define REGIONCLASS
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include <vector>
#include <string>
#include <gtk--/progressbar.h>
#include <gtk--/pixmap.h>
class cH_Region;

class RegionenPic
{
 public:
   enum epic {None, Rawindra,KanThaiPan,Alba,Eschar,Gildenbrief,HD};
   static Gtk::Pixmap* Pic(epic e) ;
};


class Region  : public HandleContent
{
 public:

 private:
   std::string name,abkuerzung,file,url,maintainer,version,copyright; 
   RegionenPic::epic pic;
   bool offiziell;
   mutable bool active;

  public:
//   Region() {};
   Region(const std::string& n);

   std::string Name() const   {return name; }
   bool Active() const {return active; }
   void setActive(bool a) const {active=a; }
   std::string Abkuerzung() const {return abkuerzung;}
   std::string File() const {return file;}
   std::string Url() const {return url;}
   std::string Maintainer() const {return maintainer;}
   std::string Version() const {return version;}
   std::string Copyright() const {return copyright;}
   bool Offiziell() const {return offiziell;}
   RegionenPic::epic Pic() const {return pic;}

   bool operator==(const Region& b) const {return Name()==b.Name();}

   static bool setActive(const std::vector<cH_Region>& LR,const cH_Region& R,bool active);
};

class cH_Region : public Handle<const Region>
{
    typedef CacheStatic<std::string,cH_Region> cache_t;
    static cache_t cache;
    friend class std::map<std::string,cH_Region>;
    cH_Region(){};
  public:
   cH_Region(Region *s) : Handle<const Region>(s) {};
//   cH_Region() {*this=new Region();}
   cH_Region(const std::string& name);

};

class Regionen_All
{
   std::vector<cH_Region> list_All;
  public:
   Regionen_All(Gtk::ProgressBar *progressbar);
   std::vector<cH_Region> get_All() const {return list_All;}

};

#endif
