// $Id: LernListen.hh,v 1.2 2002/09/07 07:15:56 thoma Exp $
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

#ifndef _LERNLISTEN_HH
#  define _LERNLISTEN_HH

#include "Datenbank.hh"

class midgard_CG;
class VAbenteurer;

class LernListen
{
      const Datenbank D;
  public:
      LernListen(const Datenbank& d) : D(d){}   

      bool nsc_check(bool nsc_allowed,bool nsc_only) const ;
      bool region_check(const std::string& region) const;
                
      
      std::vector<cH_Spezies> getSpezies(bool nsc_allowed) const ;
      std::vector<pair<cH_Typen,bool> > getTypen(const VAbenteurer& A,bool nsc_allowed) const ;

/*   

     std::list<cH_MidgardBasicElement> getBeruf(){}; 
     std::list<cH_MidgardBasicElement> getFertigkeit_ang(){}; 
     std::list<cH_MidgardBasicElement> getFertigkeit(){};
     std::list<cH_MidgardBasicElement> getFertigkeit_universal(){};
     std::list<cH_MidgardBasicElement> getWaffenGrund() {};
     std::list<cH_MidgardBasicElement> getWaffen() {};
     std::list<cH_MidgardBasicElement> getWaffen_besitz(){};
     std::list<cH_MidgardBasicElement> getZauber() {};
     std::list<cH_MidgardBasicElement> getZauberwerk(){};
     std::list<cH_MidgardBasicElement> getKido() {};
     std::list<cH_MidgardBasicElement> getSprache(){}; 
     std::list<cH_MidgardBasicElement> getSchrift(){}; 
*/
};


#endif
