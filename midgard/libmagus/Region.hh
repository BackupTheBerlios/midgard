// $Id: Region.hh,v 1.10 2004/08/30 13:17:56 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2002-2004 Christof Petig
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
   enum epic {None, Rawindra,KanThaiPan,Alba,Eschar,Gildenbrief,GildenbriefBerufe,
              HD,Waeland,
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
   Region(const Tag &tag, const std::string &file=std::string());

   int Nr()  const {return nr;}
   const std::string &Name() const   {return name; }
   const std::string &Titel() const   {return titel; }
//   Model<bool> &Active() const {return active; }
//   void setActive(bool a) const {active=a; }
   const std::string &Abkuerzung() const {return abkuerzung;}
   const std::string &File() const {return file;}
   const std::string &Url() const {return url;}
   const std::string &Maintainer() const {return maintainer;}
   const std::string &Version() const {return version;}
   const std::string &Copyright() const {return copyright;}
   const std::string &Jahr() const {return jahr;}
   bool Offiziell() const {return offiziell;}
   RegionenPic_enum::epic Pic() const {return pic;}

   bool operator==(const Region& b) const { return Nr()==b.Nr(); }
   // Name()==b.Name();  Nr ist schneller
   bool operator<(const Region& b) const { return Nr()<b.Nr(); }

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
   static cH_Region load(const Tag &name, const std::string &file);
   static cH_Region getRegionfromAbk(const std::string &r);
};

namespace Regionen_All
{  void load(std::vector<cH_Region> &list, const Tag &t, const std::string &file);
   cH_Region getRegionfromAbk(const std::vector<cH_Region>& V,const std::string &r);
};
#endif
