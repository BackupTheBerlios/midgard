/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2003 Christof Petig
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

#include<list>
//#include<MidgardBasicElement.hh>
//#include <Enums.hh>
#include <Abenteurer.hh>
class Abenteurer;
#include <Prozente100.hh>
class cH_Prototyp2;

class MagusKI
{
      Abenteurer &Aben;
      Prozente100 prozente100;
      Grund_Standard_Ausnahme_MBE GSA_MBE;
      std::vector<cH_Prototyp2> vec_Prototypen;
      bool use_GSA_MBE;

      const Enums::MBEListen Was() const;

      std::list<MBEmlt> NeuLernenList(const Enums::MBEListen was,const int gfp) const;
      std::list<MBEmlt> KI_GSA_Liste(const std::list<MBEmlt> &L);
      std::list<MBEmlt> KI_Prototypen_Liste(const Enums::MBEListen was,const std::list<MBEmlt> &L,bool steigern);

      enum e_KI {OK, EmptyList, NotAllowedForGrad,Geheimzeichen,NoSteigern};
      struct st_KI {std::string name; int wert; e_KI e_ki;
             st_KI(const e_KI e) : wert(0), e_ki(e){} 
             st_KI(const std::string &n,const e_KI e) 
               : name(n),wert(0),e_ki(e){}
             st_KI(const std::string &n,const int w,const e_KI e) 
               : name(n),wert(w),e_ki(e){} };

      void ausgabe(const st_KI& stki, const bool gesteigert,Enums::MBEListen was) const;

      st_KI NeuLernen(int &gfp,const Enums::MBEListen was);
      st_KI Steigern(int &gfp,const Enums::MBEListen was) ; 

      void Verteile(int gfp);
      enum eSL {eSteigern,eNeuLernen,eSpeziel};
      bool allowed_for_grad(const MBEmlt &M,eSL was);
      int teste_auf_gradanstieg();
      const Abenteurer::e_wie_steigern get_wie_steigern(const eSL e);
      const Enums::st_bool_steigern get_bool_steigern();
      
      void operator=(const MagusKI &);
      MagusKI(const MagusKI &);
      
   public:

      MagusKI(Abenteurer &a)
        : Aben(a),
          use_GSA_MBE(true)
          {};

      void VerteileGFP(int gfp,const Prozente100 &p,
                       const Grund_Standard_Ausnahme_MBE &gsa) ;
      void VerteileGFP(int gfp,const Prozente100 &p,const std::vector<cH_Prototyp2> &Prototypen) ;

   private:
};


#endif
