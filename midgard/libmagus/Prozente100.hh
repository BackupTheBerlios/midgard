/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2003-2004 Christof Petig
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

#ifndef PROZ100
#define PROZ100
#include <vector>
#include "MidgardBasicElement.hh"

class Prozente100{

   public:
      struct st_was{MidgardBasicElement::MBEE was;int prozent;
             st_was(MidgardBasicElement::MBEE w,int p):was(w),prozent(p){}
                   };
   private:
      std::vector<st_was> VWas;
      std::vector<st_was> VSpezialist;
      bool mage;

      int Vsumme();
      void add(const MidgardBasicElement::MBEE &was,const int prozent);
      
   public:
      Prozente100();

      void check100();
      void set_mage(bool m);         
      int get(const MidgardBasicElement::MBEE &was) const;
      void set(const MidgardBasicElement::MBEE &was,const int prozent);
      const std::vector<st_was> get100V() const;

      int getS(const MidgardBasicElement::MBEE &was) const;
      void setS(const MidgardBasicElement::MBEE &was,const int prozent);
      

};

class Grund_Standard_Ausnahme_MBE
{
      int Gprozent, Sprozent, Aprozent;

      void check100();

   public:   
      Grund_Standard_Ausnahme_MBE()
         : Gprozent(80), Sprozent(20), Aprozent(0) {}

      void setG(int i) {Gprozent=i;}
      void setS(int i) {Sprozent=i;}
      void setA(int i) {Aprozent=i;}

      int getG() {check100(); return Gprozent;}
      int getS() {check100(); return Sprozent;}
      int getA() {check100(); return Aprozent;}
};



#endif
