// $Id: Ruestung.hh,v 1.1 2003/05/07 00:02:03 christof Exp $               
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

#ifndef RUESTUNGCLASS
#define RUESTUNGCLASS
#include <Misc/Handles.h>
#include <Misc/CacheStatic.h>
#include <vector>
#include <string>
#include "xml.h"

class Grundwerte;
class Ruestung  : public HandleContentCopyable
{
   std::string name, longname, region,behinderung_wie; 
   int lp_verlust,min_staerke,rw_verlust,b_verlust,
      abwehr_bonus_verlust,angriffs_bonus_verlust;
   int vollruestungsabzug;

   std::string BehinderungWie() const {return behinderung_wie;}
  public:
//   Ruestung() {};
   Ruestung(const Tag *tag);

   std::string Name() const   {return name; }
   std::string Long() const {return longname;}
   std::string Region() const {return region;}
   int LP_Verlust() const {return lp_verlust;}
   int Min_Staerke() const {return min_staerke;}
   int RW_Verlust() const {return rw_verlust;}
//   int B_Verlust() const {return b_verlust;}
   int B_Verlust(const double &ueberlast,const Grundwerte &Werte,bool &ew) const;
   int AbwehrBonus_Verlust(int abwehr_bonus) const;
   int AngriffsBonus_Verlust(int angriffs_bonus) const;
   int VollRuestungsAbzug() const {return vollruestungsabzug;}
};

class cH_Ruestung : public Handle<const Ruestung>
{
    typedef CacheStatic<std::string,cH_Ruestung> cache_t;
    static cache_t cache;
  public:
//   cH_Ruestung() {*this=new Ruestung();}
   cH_Ruestung() {} // needed for e.g. Gtk::TreeModelColumn<cH_Ruestung>
   cH_Ruestung(const std::string& name, bool create=false);
   cH_Ruestung(const Tag *tag);
   cH_Ruestung(const Ruestung *s) : Handle<const Ruestung>(s) {};
};

class Ruestung_All
{
   std::vector<cH_Ruestung> list_All;
  public:
   Ruestung_All();
   std::vector<cH_Ruestung> get_All() const {return list_All;}
};

#endif
