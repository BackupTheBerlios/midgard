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

#ifndef MAGUSKI
#define MAGUSKI

class midgard_CG; 
#include "LernListen.hh"
#include<list>

class MagusKI
{
      midgard_CG *hauptfenster;
      Abenteurer &Aben;
      Datenbank Database;
      Random random;
      LernListen LL;
      Prozente100 prozente100;

      int spezial_allgemein;
      

      const Enums::MBEListen Was() const;

      void NeuLernen(int &gfp);
      std::list<MBEmlt>& get_known_list(const Enums::MBEListen was);
      std::list<MBEmlt> NeuLernenList(const Enums::MBEListen was,const int gfp) const;

      void Steigern(int &gfp) ; 

      
   public:

      MagusKI(midgard_CG *h)
        : hauptfenster(h),  Aben(h->getChar().getAbenteurer()),
          Database(h->getCDatabase()),random(h->random) ,
          LL(Database)
          {};

      void VerteileGFP(int gfp,const int spezial_allgemein,const Prozente100 &p) ;
//      void set_spezial_allgemein(int s) {spezial_allgemein=s;}

   private:
};


#endif
