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

#ifndef PROZ100
#define PROZ100
#include <vector>
#include "Enums.hh"

class Prozente100{

   public:
      struct st_was{Enums::MBEListen was;int prozent;
             st_was(Enums::MBEListen w,int p):was(w),prozent(p){}
                   };
   private:
      std::vector<st_was> VWas;
      std::vector<st_was> VSpezialist;
      bool mage;

      int Vsumme();
      void add(const Enums::MBEListen &was,const int prozent);
      
   public:
      Prozente100();

      void check100();
      void set_mage(bool m);         
      int get(const Enums::MBEListen &was) const;
      void set(const Enums::MBEListen &was,const int prozent);
      const std::vector<st_was> get100V() const;

      int getS(const Enums::MBEListen &was) const;
      void setS(const Enums::MBEListen &was,const int prozent);
      

};

#endif