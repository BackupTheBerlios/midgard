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

#ifndef MAGUSZUFALL
#define MAGUSZUFALL

#include "Enums.hh" 
#include "AbenteurerLernpunkte.hh"
#include "Abenteurer.hh"
#include <Misc/bitmask.h>
#include <LernListen.hh>

class Zufall
{
      Abenteurer &Aben;
      Abenteurer oldAben;
      LernListen LL;
      AbenteurerLernpunkte lernpunkte;
      
//      friend enum Zufall::B_VORGABE_BITS &operator++(enum Zufall::B_VORGABE_BITS &s);

   public:

      Zufall(Abenteurer &a) ;

      enum B_VORGABE_BITS{B_Spezies,B_Typ,B_Herkunft,B_AngeFert,B_St,B_Gs,B_Gw,
            B_Ko,B_In,B_Zt,B_Au,B_pA,B_Wk,B_Sb,B_B,B_MAX};
      typedef bitmask<B_VORGABE_BITS> e_Vorgabe;
#if 0      
      enum e_Vorgabe{eSpezies=1<<B_Spezies,eTyp=1<<B_Typ,
         eHerkunft=1<<B_Herkunft,eAngeFert=1<<B_AngeFert,
         eSt=1<<B_St,eGs=1<<B_Gs,
         eGw=1<<B_Gw,eKo=1<<B_Ko,eIn=1<<B_In,eZt=1<<B_Zt,
         eAu=1<<B_Au,epA=1<<B_pA,eWk=1<<B_Wk,eSb=1<<B_Sb,
         eB=1<<B_B
        };
#endif

      void Voll(); // kompletten Zufallsabenteruer erzeugen
      void Teil(e_Vorgabe vorgabe,const Abenteurer &A);

//      Abenteurer Abenteurer() const {return Aben;}

   private:
      cH_Spezies getSpezies() const;
      Enums::geschlecht getGeschlecht() const;
      cH_Typen getTyp() const;
      Enums::StadtLand getStadtLand() const;
      cH_Land getLand() const;
      MBEmlt getMuttersprache() const;
      MBEmlt getUeberleben() const;
      MBEmlt getZusatz(MidgardBasicElement::eZusatz was,MBEmlt& MBE,bool ungew=true) const;

      void setMuttersprache(); 
      void setWaffenBesitz();
      void setSpezialwaffe();
      void setSpezialgebiet();
      void setAngebFert();
      void setBeruf();

      // Lernschema
      struct st_LL{std::list<MBEmlt> Fach;
                   std::list<MBEmlt> Allg;
                   std::list<MBEmlt> Unge;
                   std::list<MBEmlt> Waff;
                   std::list<MBEmlt> Zaub;
             st_LL(std::list<MBEmlt> f,
                   std::list<MBEmlt> a,
                   std::list<MBEmlt> u,
                   std::list<MBEmlt> w,
                   std::list<MBEmlt> z)
                   :Fach(f),Allg(a),Unge(u),Waff(w),Zaub(z) {}
               ;};
      void Lernschema();
      st_LL getLernlisten();
      enum eFAUWZ {eWaffen,eZauber,eFach,eAllg,eUnge,eMAX};
      friend enum Zufall::eFAUWZ &operator++(enum Zufall::eFAUWZ &s);
      void Lernpunkte_verteilen(const eFAUWZ was,const Lernpunkte &lernpunkte,
                                const st_LL &Listen);
      bool knows_everything(const std::list<MBEmlt> &List_gelerntes,const std::list<MBEmlt> &L);
   public:
      static void Lernpunkte_wuerfeln(Lernpunkte &lernpunkte, Abenteurer &A);
      static WaffeBesitzLernen WaffenBesitz_wuerfeln(const Abenteurer &A,int wurf);
};

#endif
