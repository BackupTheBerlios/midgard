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
      Grund_Standard_Ausnahme_MBE GSA_MBE;
      std::vector<cH_Prototyp2> vec_Prototypen;
      bool use_GSA_MBE;

//      int spezial_allgemein;
      

      const Enums::MBEListen Was() const;

      void NeuLernen(int &gfp,const Enums::MBEListen was);
      std::list<MBEmlt> NeuLernenList(const Enums::MBEListen was,const int gfp) const;
      std::list<MBEmlt> KI_GSA_Liste(const std::list<MBEmlt> &L);
      std::list<MBEmlt> KI_Prototypen_Liste(const Enums::MBEListen was,const std::list<MBEmlt> &L,bool steigern);

      void Steigern(int &gfp,const Enums::MBEListen was) ; 

      void Verteile(int gfp);
      enum eSL {eSteigern,eNeuLernen};
      bool allowed_for_grad(const MBEmlt &M,eSL was);
      int teste_auf_gradanstieg();
      const Abenteurer::e_wie_steigern get_wie_steigern();
      const Enums::st_bool_steigern get_bool_steigern();
      
   public:

      MagusKI(midgard_CG *h)
        : hauptfenster(h),  Aben(h->getChar().getAbenteurer()),
          Database(h->getCDatabase()),random(h->random) ,
          LL(Database),use_GSA_MBE(true)
          {};

      void VerteileGFP(int gfp,const Prozente100 &p,
                       const Grund_Standard_Ausnahme_MBE &gsa) ;
      void VerteileGFP(int gfp,const Prozente100 &p,const std::vector<cH_Prototyp2> &Prototypen) ;

   private:
};


#endif
