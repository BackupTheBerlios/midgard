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

#include "Zufall.hh"
#include "Fertigkeiten_angeboren.hh"
#include "zufall.h"

Zufall::Zufall(Abenteurer &a) 
: Aben(a),oldAben(Aben), lernpunkte(a)
          {}

void Zufall::Voll()
{
  Teil(e_Vorgabe::all,oldAben);
}

#if 0
enum Zufall::B_VORGABE_BITS &operator++(enum Zufall::B_VORGABE_BITS &s)
{  ++(int&)s;
   return s;
}

struct st_vor{bool spezies; bool typ; bool herkunft; bool angefert;
                     bool st; bool gs; bool gw; bool ko; 
                     bool in; bool zt; bool au; bool pa; bool wk; bool sb; bool b;
              st_vor() :
                  spezies(true),typ(true),herkunft(true),angefert(true),
                  st(true),gs(true),gw(true),ko(true),
                  in(true),zt(true),au(true),pa(true),wk(true),sb(true),b(true){}
              };
#endif      

void Zufall::Teil(e_Vorgabe vorgabe,const Abenteurer &A)
{ oldAben=A;

   if(vorgabe&B_Spezies)  Aben.getWerte().setSpezies(getSpezies());
   else            Aben.getWerte().setSpezies(oldAben.getWerte().Spezies());
   Aben.getWerte().gw_wuerfeln_2x();
   if(vorgabe&B_St)       Aben.getWerte().setSt(oldAben.getWerte().St());
   if(vorgabe&B_Gs)       Aben.getWerte().setGs(oldAben.getWerte().Gs());
   if(vorgabe&B_Gw)       Aben.getWerte().setGw(oldAben.getWerte().Gw());
   if(vorgabe&B_Ko)       Aben.getWerte().setKo(oldAben.getWerte().Ko());
   if(vorgabe&B_In)       Aben.getWerte().setIn(oldAben.getWerte().In());
   if(vorgabe&B_Zt)       Aben.getWerte().setZt(oldAben.getWerte().Zt());
   Aben.getWerte().Au_pA_wuerfeln();
   Aben.getWerte().setGeschlecht(getGeschlecht());
   if(!(vorgabe&B_Typ) || !oldAben.Valid())      Aben.setTyp1(getTyp());
   else             Aben.setTyp1(oldAben.Typ1());
   Aben.getWerte().abge_werte_setzen(Aben);
   if(vorgabe&B_Au)       Aben.getWerte().setAu(oldAben.getWerte().Au());
   if(vorgabe&B_pA)       Aben.getWerte().setpA(oldAben.getWerte().pA());
   if(vorgabe&B_Wk)       Aben.getWerte().setWk(oldAben.getWerte().Wk());
   if(vorgabe&B_Sb)       Aben.getWerte().setSb(oldAben.getWerte().Sb());
   if(vorgabe&B_B)        Aben.getWerte().setB(oldAben.getWerte().B());
   
   if(!(vorgabe&B_Herkunft)) Aben.getWerte().setHerkunft(getLand());
   else            Aben.getWerte().setHerkunft(oldAben.getWerte().Herkunft());
   setMuttersprache();
   Aben.getWerte().setUeberleben(getUeberleben());
   if(!(vorgabe&B_AngeFert)) setAngebFert();
   else            Aben.List_Fertigkeit_ang()=oldAben.List_Fertigkeit_ang();
   Lernschema();
   setBeruf();
   lernpunkte.geld_wuerfeln();
   setWaffenBesitz();
   lernpunkte.on_button_ruestung_clicked(Random::W100());
   lernpunkte.ausruestung_setzen();
}

extern std::vector<MBEmlt> List_to_Vector(std::list<MBEmlt> L,const Abenteurer& Aben,int lp);

void Zufall::setAngebFert()
{
   Aben.setAngebFert();
   int wurf;
   do{
      wurf=Random::W100(); 
      if(wurf==100) 
       { std::list<MBEmlt> L=LL.getMBEm(Aben,LernListen::lAngebFert);
         std::vector<MBEmlt> V=List_to_Vector(L,Aben,99);
         if(V.empty()) break;
         int i=Random::integer(0,V.size()-1);
         cH_Fertigkeit_angeborene F(V[i]->getMBE());
         Aben.setAngebSinnFert(F->Min(),V[i]);
       }
      else lernpunkte.AngebFert_gewuerfelt(wurf);
     }while (wurf==100);
  Aben.List_Fertigkeit_ang().sort();
  Aben.List_Fertigkeit_ang().unique();
}


void Zufall::setMuttersprache()
{
  MBEmlt sprache=getMuttersprache();
  Aben.List_Sprache().push_back(sprache);
  Aben.setMuttersprache((*sprache)->Name());  
}


////////////////////////////////////////////////////////////////////////////
// Würfeln
////////////////////////////////////////////////////////////////////////////

void Zufall::Lernpunkte_wuerfeln(Lernpunkte &lernpunkte, Abenteurer &A)
{
  //Speziesspezifische Fertigkeiten
  int lpspezies=0;
  A.List_Fertigkeit()=A.getWerte().Spezies()->getFertigkeiten(lpspezies,A.getWerte());

  int fachlern=Random::W6()+Random::W6();
  lernpunkte.setFach(fachlern - lpspezies);
  lernpunkte.setAllgemein(Random::W6()+1);
  lernpunkte.setUnge(Random::W6());
  lernpunkte.setWaffen(Random::W6()+Random::W6());  
  if (A.Typ1()->is_mage()) lernpunkte.setZauber(Random::W6()+Random::W6());

  // Doppelcharaktere
  if(A.Typ2()->Short()!="" || A.Typ1()->Short()=="To" )
   {
      lernpunkte.setWaffen(Random::W6()+1);
      lernpunkte.setZauber(Random::W6()+1);
   }

  int age = (lernpunkte.Allgemein() + lernpunkte.Unge()
             + lernpunkte.Fach()
             + lernpunkte.Waffen() + lernpunkte.Zauber())/4+16;
  A.getWerte().setAlter( age * A.getWerte().Spezies()->AlterFaktor());

}



WaffeBesitzLernen Zufall::WaffenBesitz_wuerfeln(const Abenteurer &A,int wurf)
{
  WaffeBesitzLernen l;
  if (A.Typ1()->Geld() == 1)
  { if      ( 1<=wurf&&wurf<=10 ) { l.set_EWaffe(3);      }
    else if (11<=wurf&&wurf<=20 ) { l.set_EWaffe(3); l.set_AWaffe(1); }
    else if (21<=wurf&&wurf<=30 ) { l.set_EWaffe(2); l.set_AWaffe(2); }
    else if (31<=wurf&&wurf<=60 ) { l.set_EWaffe(3); l.set_AWaffe(2); }
    else if (61<=wurf&&wurf<=80 ) { l.set_EWaffe(2); l.set_AWaffe(3); }
    else if (81<=wurf&&wurf<=95 ) {      l.set_AWaffe(5); }
    else if (96<=wurf&&wurf<=100) { l.set_EWaffe(1); l.set_AWaffe(4); l.setMagisch(true); }
  }  
  if (A.Typ1()->Geld() == 2)
  { if      ( 1<=wurf&&wurf<=10 ) { l.set_EWaffe(2);      }  
    else if (11<=wurf&&wurf<=20 ) { l.set_EWaffe(1); l.set_AWaffe(1); }  
    else if (21<=wurf&&wurf<=30 ) { l.set_EWaffe(2); l.set_AWaffe(1); }  
    else if (31<=wurf&&wurf<=60 ) { l.set_EWaffe(3); l.set_AWaffe(1); }  
    else if (61<=wurf&&wurf<=80 ) { l.set_EWaffe(2); l.set_AWaffe(2); }  
    else if (81<=wurf&&wurf<=95 ) {      l.set_AWaffe(4); }  
    else if (96<=wurf&&wurf<=100) { l.set_EWaffe(1); l.set_AWaffe(3); l.setMagisch(true); }
  }  
 if (A.Typ1()->Geld() == 3)
  { if      ( 1<=wurf&&wurf<=10 ) { l.set_EWaffe(1);      }  
    else if (11<=wurf&&wurf<=20 ) {      l.set_AWaffe(1); }  
    else if (21<=wurf&&wurf<=30 ) { l.set_EWaffe(2);      }  
    else if (31<=wurf&&wurf<=60 ) { l.set_EWaffe(1); l.set_AWaffe(1); }  
    else if (61<=wurf&&wurf<=80 ) { l.set_EWaffe(1); l.set_AWaffe(1); }  
    else if (81<=wurf&&wurf<=95 ) {      l.set_AWaffe(2); }  
    else if (96<=wurf&&wurf<=100) { l.set_EWaffe(1); l.set_AWaffe(1); l.setMagisch(true); }
  }  
 if (A.Typ1()->Geld() == 4)
  { if      ( 1<=wurf&&wurf<=10 ) { l.set_EWaffe(2);      }  
    else if (11<=wurf&&wurf<=20 ) { l.set_EWaffe(1); l.set_AWaffe(1); }  
    else if (21<=wurf&&wurf<=30 ) { l.set_EWaffe(3);      }  
    else if (31<=wurf&&wurf<=60 ) { l.set_EWaffe(2); l.set_AWaffe(1); }  
    else if (61<=wurf&&wurf<=80 ) { l.set_EWaffe(1); l.set_AWaffe(2); }  
    else if (81<=wurf&&wurf<=95 ) {      l.set_AWaffe(3); }  
    else if (96<=wurf&&wurf<=100) { l.set_EWaffe(1); l.set_AWaffe(2); l.setMagisch(true); }
  }  
 return l;
}

