// $Id: Lernschema.hh,v 1.1 2003/05/06 07:12:04 christof Exp $               
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

#ifndef _LERNSCHEMA_HH
#  define _LERNSCHEMA_HH
#include <map>
#include <vector>
#include "MidgardBasicElement.hh"


class Lernschema 
{
   public:
      struct st_index {std::string typ; std::string art; std::string fertigkeit;
             st_index()  {};
             st_index(std::string t, std::string a, std::string f) 
               : typ(t),art(a),fertigkeit(f) {}
             bool operator==(const st_index& b) const
               {return art==b.art && typ==b.typ && fertigkeit==b.fertigkeit;}
             bool operator<(const st_index& b) const
               { return  art <b.art || 
                        (art==b.art && typ <b.typ) ||
                        (art==b.art && typ==b.typ && fertigkeit<b.fertigkeit);}
         };
   private:
      struct st_wert  {bool pflicht;int erfolgswert;
                       std::string attribut; int lernpunkte;
                       std::string p_element; std::string s_element;
             st_wert(): pflicht(false),erfolgswert(0),lernpunkte(99){}
             st_wert (bool p,int e, std::string a, int l,
                      std::string pe, std::string se)
                      : pflicht(p),erfolgswert(e),
                        attribut(a),lernpunkte(l),p_element(pe),
                        s_element(se) {}
         };

      std::map<st_index,st_wert> lern_map;
	
	static void StoreLernschema(const std::string &slist,const std::string &element,
		const std::string &typ, std::map<Lernschema::st_index,Lernschema::st_wert> &lern_map);

   public:
      Lernschema() {}; //der andere ctor war mal mit Progressbar
      Lernschema(bool t);

//      void getLernschema();
      bool get_Pflicht(const std::vector<st_index>& VI) const ;
      int get_Lernpunkte(const  std::vector<st_index>& VI) const ;
      std::list<MBEmlt> get_List(const std::string& art, 
                                       const std::vector<cH_Typen>& _Typ,
                                       const std::list<MBEmlt>& Gelerntes) const;
      // Doppelklassen
      static std::vector<Lernschema::st_index> getIndex(const std::vector<cH_Typen>& Typ,const std::string& art,const std::string& name);
};

#endif
