// $Id: Region.hh,v 1.4 2003/05/08 06:15:30 christof Exp $               
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

#ifndef REGIONCLASS
#define REGIONCLASS
#include <Misc/Handles.h>
#include <Misc/CacheStatic.h>
#include <vector>
#include <string>
//#include "xml.h"
//#include "Optionen.hh"
//#include <BaseObjects/Model.h>

class cH_Region;
class Tag;

namespace RegionenPic_enum
{
   enum epic {None, Rawindra,KanThaiPan,Alba,Eschar,Gildenbrief,HD,Waeland,
              Nahuatlan,Arkanum,DFR,Meister_der_Sphaeren,Tipps_und_Tricks,
              Abenteuer,HD_finster,Kuestenstaaten,Ikengabecken};
}


class Region  : public HandleContent
{
 public:

 private:
   int nr;
   std::string name,titel,abkuerzung,file,url,maintainer,version,copyright,jahr; 
   RegionenPic_enum::epic pic;
   bool offiziell;
//   mutable Model<bool> active;

  public:
   Region(const Tag *tag);

   int Nr()  const {return nr;}
   std::string Name() const   {return name; }
   std::string Titel() const   {return titel; }
//   Model<bool> &Active() const {return active; }
//   void setActive(bool a) const {active=a; }
   std::string Abkuerzung() const {return abkuerzung;}
   std::string File() const {return file;}
   std::string Url() const {return url;}
   std::string Maintainer() const {return maintainer;}
   std::string Version() const {return version;}
   std::string Copyright() const {return copyright;}
   std::string Jahr() const {return jahr;}
   bool Offiziell() const {return offiziell;}
   RegionenPic_enum::epic Pic() const {return pic;}

   bool operator==(const Region& b) const {return Name()==b.Name();}

//   static bool setActive(const std::vector<cH_Region>& LR,const cH_Region& R,bool active);
//   static bool isActive(const std::vector<cH_Region>& LR,const cH_Region& R);
};

class cH_Region : public Handle<const Region>
{
    typedef CacheStatic<std::string,cH_Region> cache_t;
    static cache_t cache;
    friend class std::map<std::string,cH_Region>;
    cH_Region(){};
  public:
   cH_Region(const Region *s) : Handle<const Region>(s) {}
   cH_Region(const std::string& name,bool create=false);
   cH_Region(const Tag *name);
};

class Regionen_All
{
   std::vector<cH_Region> list_All;
  public:
   Regionen_All();
   std::vector<cH_Region> get_All() const {return list_All;}
   static cH_Region Regionen_All::getRegionfromAbk(const std::vector<cH_Region>& V,const std::string &r);
};

#endif
