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
 
#ifndef ZUFALL_STEIGERN_HH
#define ZUFALL_STEIGERN_HH

#include "Prozente100.hh"
#include "Zufall.hh"
#include "Prototyp2.hh"
class Abenteurer;
class Zufall;

class zufall_steigern
{
      Prozente100 prozente100;
      Grund_Standard_Ausnahme_MBE GSA_MBE;
      std::vector<cH_Prototyp2> prototypen;
      
      void zeige_werte();
      void fill_combos();
      void fill_combo_typen(const bool nsc_allowed);
      void fill_combo_steigern();
      void fill_prototyp2_list();
      void set_tree_prototyp_titels();
      std::vector<cH_Prototyp2> getSelectedPrototypen();
      bool entry_is_a_prototyp(const std::string &e);
      void set_bereiche_spinbuttons();
      int get_spezialbildung();
      Zufall::e_Vorgabe getVorgaben(Abenteurer& oldAben) const ;
   public:
      zufall_steigern() {}

      void init(); // ???
      void steigern(Abenteurer &A, unsigned gfp);
      static unsigned GFPvonGrad(unsigned grad);
      
      void setzeProzente(const Prozente100 &proz) { prozente100=proz; }
      void setzeGSA(const Grund_Standard_Ausnahme_MBE &g) { GSA_MBE=g; }
      void setzePrototypen(const std::vector<cH_Prototyp2> &p) { prototypen=p; }
      
   private:
      void check100();
};

#endif
