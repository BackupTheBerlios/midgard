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
      Abenteurer oldAben;
      Datenbank Database;
      Random random;
      LernListen LL;
      
      enum B_VORGABE_BITS{B_Spezies,B_Typ,B_Herkunft,B_AngeFert,B_St,B_Gs,B_Gw,
            B_Ko,B_In,B_Zt,B_Au,B_pA,B_Wk,B_Sb,B_B,B_MAX};
   
   public:

      Zufall(midgard_CG *h)
        : hauptfenster(h),  Aben(h->getChar()),oldAben(Aben.getAbenteurer()),
          Database(h->getCDatabase()),random(h->random) ,
          LL(Database)
          {};

      enum e_Vorgabe{eSpezies=1<<B_Spezies,eTyp=1<<B_Typ,
         eHerkunft=1<<B_Herkunft,eAngeFert=1<<B_AngeFert,
         eSt=1<<B_St,eGs=1<<B_Gs,
         eGw=1<<B_Gw,eKo=1<<B_Ko,eIn=1<<B_In,eZt=1<<B_Zt,
         eAu=1<<B_Au,epA=1<<B_pA,eWk=1<<B_Wk,eSb=1<<B_Sb,
         eB=1<<B_B
        };

      void Voll(); // kompletten Zufallsabenteruer erzeugen
      void Teil(e_Vorgabe vorgabe,const Abenteurer &A);

//      VAbenteurer Abenteurer() const {return Aben;}

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
      void Lernpunkte_verteilen(const eFAUWZ was,const Lernpunkte &lernpunkte,
                                const st_LL &Listen);
      bool knows_everything(const std::list<MBEmlt> &List_gelerntes,const std::list<MBEmlt> &L);
   public:
      static void Lernpunkte_wuerfeln(Lernpunkte &lernpunkte, VAbenteurer &A, Random &random);
      static WaffeBesitzLernen WaffenBesitz_wuerfeln(const VAbenteurer &A,int wurf);
};

#endif
