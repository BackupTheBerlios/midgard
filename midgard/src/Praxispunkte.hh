/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

#ifndef _PRAXISPUNKTE_HH
#  define _PRAXISPUNKTE_HH
#include <string>
#include <map>
#include <gtk--/progressbar.h>
class cH_MidgardBasicElement;
class cH_Typen;
#include <vector>
class Grundwerte;

class Praxispunkte 
{
      struct st_map {int max_wert;int lernfaktor;
             st_map() : max_wert(0),lernfaktor(0) {}
             st_map(int m,int l) : max_wert(m),lernfaktor(l) {}
            };
      std::map<std::string,st_map> prax_map;
      
   public:
      Praxispunkte() {}
      Praxispunkte(Gtk::ProgressBar *progressbar);
private:
      bool wuerfeln(const cH_MidgardBasicElement& MBE, 
                                 const Grundwerte& Werte,
                                 const vector<cH_Typen>& Typ,
                                 bool wuerfeln);
};

#endif
