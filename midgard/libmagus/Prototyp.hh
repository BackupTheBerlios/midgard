// $Id: Prototyp.hh,v 1.3 2003/05/26 06:23:35 christof Exp $               
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

#ifndef PROTOTYPCLASS
#define PROTOTYPCLASS
#include <string>
class Tag;
#include <Misc/Handles.h>
#include <Misc/CacheStatic.h>
#include <list>
//#include <Prozente100.hh>
class Prozente100;

class Prototyp : public HandleContent //Copyable
{
   std::string name;
   int fertigkeit,waffe,waffe_grund,zauber,
          zauberwerk,sprache,schrift;
   int fert_spez,waff_spez,spra_spez,schr_spez; // Hochspezialisiert oder Allgemeinbildung 

 public:
   Prototyp(const Tag &tag);

   const std::string &Name() const {  return name; }
   int Fertigkeit() const {return fertigkeit;}
   int Waffe() const {return waffe;}
   int WaffeGrund() const {return waffe_grund;}
   int Zauber() const {return zauber;}
   int ZauberWerk() const {return zauberwerk;}
   int Sprache() const {return sprache;}
   int Schrift() const {return schrift;}

   int FertSpezialist() const {return fert_spez;}
   int WaffSpezialist() const {return waff_spez;}
   int SpraSpezialist() const {return spra_spez;}
   int SchrSpezialist() const {return schr_spez;}

   static void setLast(const Prozente100 &p);
};

class cH_Prototyp : public Handle<Prototyp>
{
    typedef CacheStatic<std::string,cH_Prototyp> cache_t;
    static cache_t cache;
    friend class std::map<std::string,cH_Prototyp>;
    cH_Prototyp(){};
 public:
    cH_Prototyp(const std::string& name  ,bool create=false);
    static cH_Prototyp load(const Tag &tag);
    cH_Prototyp( Prototyp *s) : Handle<Prototyp>(s) {};
};

namespace Prototyp_All
{  void load(std::list<cH_Prototyp> &list, const Tag &t);
};

#endif
