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

#ifndef MAGUSZUFALL
#define MAGUSZUFALL

#include "midgard_CG.hh" 
#include "Enums.hh" 
#include "LernListen.hh"

class Lernpunkte;

class Zufall
{
      midgard_CG *hauptfenster;
      VAbenteurer Aben;
      Datenbank Database;
      Random random;
      LernListen LL;
   
   public:

      Zufall(midgard_CG *h)
        : hauptfenster(h),  Aben(h->getChar()),
          Database(h->getCDatabase()),random(h->random) ,
          LL(Database)
          {};
      void Voll(); // kompletten Zufallsabenteruer erzeugen

//      VAbenteurer Abenteurer() const {return Aben;}

   private:
      cH_Spezies getSpezies() const;
      Enums::geschlecht getGeschlecht() const;
      cH_Typen getTyp() const;
      Enums::StadtLand getStadtLand() const;
      cH_Land getLand() const;
      MidgardBasicElement_mutable getMuttersprache() const;
      MidgardBasicElement_mutable getUeberleben() const;

      void setMuttersprache(); 

      // Lernschema
      struct st_LL{std::list<MidgardBasicElement_mutable> Fach;
                   std::list<MidgardBasicElement_mutable> Allg;
                   std::list<MidgardBasicElement_mutable> Unge;
                   std::list<MidgardBasicElement_mutable> Waff;
                   std::list<MidgardBasicElement_mutable> Zaub;
             st_LL(std::list<MidgardBasicElement_mutable> f,
                   std::list<MidgardBasicElement_mutable> a,
                   std::list<MidgardBasicElement_mutable> u,
                   std::list<MidgardBasicElement_mutable> w,
                   std::list<MidgardBasicElement_mutable> z)
                   :Fach(f),Allg(a),Unge(u),Waff(w),Zaub(z) {}
               ;};
      void Lernschema();
      st_LL getLernlisten();
      void Lernpunkte_verteilen(std::list<MidgardBasicElement_mutable> L,int lp);
   public:
      static void Lernpunkte_wuerfeln(Lernpunkte &lernpunkte, VAbenteurer &A, Random &random);
};

#endif
