// $Id: WaffeGrund.hh,v 1.7 2003/12/09 08:01:46 christof Exp $               
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

#ifndef _WAFFEGRUND_HH
#  define _WAFFEGRUND_HH
#include <vector>
#include <list>
#include "MidgardBasicElement.hh"
#include "Typen.hh"
#include <Misc/Tag.h>

class cH_WaffeGrund;

class WaffeGrund : public MidgardBasicElement
{
     void get_WaffeGrund(const Tag &t);
  public:
     WaffeGrund(const Tag &t);
     void load(const Tag &t);

     // Wenn Keine Waffe gelernt werden kann, die zu einer Grundkenntnis
     // gehört, dann ist eine Grundkenntnis nicht sinnvoll
     bool is_sinnvoll(const std::list<cH_MidgardBasicElement> &WL,
                      const Abenteurer &A) const;
     enum MBEE What() const {return MidgardBasicElement::WAFFEGRUND;}
     std::string What_str() const {return "Grundkenntnis";}
     int MaxErfolgswert(const Grundwerte& w,const std::vector<cH_Typen>& Typ) const 
         {return 0;} //wg. virtueller Funktion
};

class cH_WaffeGrund : public Handle<const WaffeGrund>
{
    typedef CacheStatic<std::string,cH_WaffeGrund> cache_t;
    static cache_t cache;
    cH_WaffeGrund() {};
    cH_WaffeGrund(const WaffeGrund *s) : Handle<const WaffeGrund>(s) {};
    friend class std::map<std::string,cH_WaffeGrund>;
 public:
    cH_WaffeGrund(const std::string& n ,bool create=false);
    static cH_WaffeGrund load(const Tag &tag,bool &is_new);

    cH_WaffeGrund(const cH_MidgardBasicElement &x) : Handle<const WaffeGrund>
      (dynamic_cast<const WaffeGrund *>(&*x)){}   
};
  
  
namespace WaffeGrund_All
{  void load(std::list<cH_MidgardBasicElement> &list, const Tag &t);
}

#endif
