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
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, U
 */

#ifndef WIZARD_HH
#define WIZARD_HH

#include <string>
#include <vector>

class midgard_CG;

class Wizard
{
   public:
     enum esteps {SPEZIES,GRUNDWERTE,GESCHLECHT,TYP,STADTLAND,
                  ABGELEITETEWERTE,HERKUNFT,ANGEBORENEFERTIGKEITEN,
                  LERNPUNKTE};
   private:
     struct st_wiz{int page;std::string text;
            void (midgard_CG::*callback)();
            st_wiz(int p,std::string t,void (midgard_CG::*c)() )
            : page(p),text(t),callback(c){} 
            };

      midgard_CG* hauptfenster;
      esteps actual_step;
      std::vector<st_wiz> vecwiz;

      void fill_vecwiz();
      void evaluate_step(esteps step);
   public:
      Wizard(midgard_CG* h);
      void next_step();
      void same_step();
      void restart();

      esteps ActualStep() const {return actual_step;}
};

#endif
