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

class MagusKI
{
      midgard_CG *hauptfenster;
      VAbenteurer Aben;
      Datenbank Database;
      Random random;
      LernListen LL;
      
   public:

      MagusKI(midgard_CG *h)
        : hauptfenster(h),  Aben(h->getChar()),
          Database(h->getCDatabase()),random(h->random) ,
          LL(Database)
          {};

      void Steigern(int gfp); 

   private:
};

#endif
