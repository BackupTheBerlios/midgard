// $Id: Ausnahmen.hh,v 1.5 2002/01/12 08:12:24 thoma Exp $               
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

#ifndef _CLASS_AUSNAHMEN_HH
#  define _CLASS_AUSNAHMEN_HH

#include <vector.h>
#include <map.h>
#include "Typen.hh"
#include "Grundwerte.hh"
//#include "class_berufe.hh"
#include "Beruf.hh"
#include <gtk--/progressbar.h>

class Data_Ausnahmen 
{
   std::string name, art, standard;

public:
   Data_Ausnahmen(std::string nn, std::string aa, std::string ss)
         :name(nn), art(aa), standard(ss) {}

   std::string Name() const {return name;}
   std::string Art() const {return art;}
   void Standard(vector<std::string>& vstandard) const
      {vstandard[0] = "*"+standard+"*"; vstandard[1] = "";}
   double Fac() const;

};

class Ausnahmen 
{
   struct st_index1 {std::string typ; 
                     std::string herkunft; 
                     std::string spezies;
                     std::string beruf;
                     std::string stand;
            st_index1(std::string t,std::string h,std::string s,
                      std::string b,std::string st)
               : typ(t), herkunft(h), spezies(s), beruf(b),stand(st) {} 
            } ;
   std::map<st_index1,Data_Ausnahmen> map_ausnahmen;
   std::list<cH_MidgardBasicElement> list_Beruf;
   Grundwerte Werte;
   vector<cH_Typen> Typ;

 public:
   Ausnahmen() {}
   Ausnahmen(Gtk::ProgressBar *progressbar);
   void set_Beruf (const std::list<cH_MidgardBasicElement>& vB) {list_Beruf = vB;}
   void set_Werte (const Grundwerte& W) {Werte=W;}
   void set_Typ   (const vector<cH_Typen>& T) {Typ=T;}

   double Ausnahmen_float(const std::string& name) const;
   void Ausnahmen_string(const std::string& name, vector<std::string>& standard) const;
};
#endif
