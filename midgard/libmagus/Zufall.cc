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
#include "Random.hh"

Zufall::Zufall(Abenteurer &a) 
: Aben(a),oldAben(Aben)
          {}

void Zufall::Voll()
{
  Teil(e_Vorgabe::none,oldAben);
}

void Zufall::Teil(e_Vorgabe vorgabe,const Abenteurer &A)
{ oldAben=A;

   if(vorgabe&B_Spezies)  Aben.setSpezies(getSpezies());
   else            Aben.setSpezies(oldAben.Spezies());
   Aben.gw_wuerfeln_2x();
   if(vorgabe&B_St)       Aben.setSt(oldAben.St());
   if(vorgabe&B_Gs)       Aben.setGs(oldAben.Gs());
   if(vorgabe&B_Gw)       Aben.setGw(oldAben.Gw());
   if(vorgabe&B_Ko)       Aben.setKo(oldAben.Ko());
   if(vorgabe&B_In)       Aben.setIn(oldAben.In());
   if(vorgabe&B_Zt)       Aben.setZt(oldAben.Zt());
   Aben.Au_pA_wuerfeln();
   Aben.setGeschlecht(getGeschlecht());
   if(!(vorgabe&B_Typ) || !oldAben.Valid())      Aben.setTyp1(getTyp());
   else             Aben.setTyp1(oldAben.Typ1());
   if (Aben.Typ1()->NSC_only()) 
      Aben.getOptionen().OptionenCheck(Optionen::NSC_only).active=true;
   Aben.abge_werte_setzen();
   if(vorgabe&B_Au)       Aben.setAu(oldAben.Au());
   if(vorgabe&B_pA)       Aben.setpA(oldAben.pA());
   if(vorgabe&B_Wk)       Aben.setWk(oldAben.Wk());
   if(vorgabe&B_Sb)       Aben.setSb(oldAben.Sb());
   if(vorgabe&B_B)        Aben.setB(oldAben.B());
   
   if(!(vorgabe&B_Herkunft)) Aben.setHerkunft(getLand());
   else            Aben.setHerkunft(oldAben.Herkunft());
   if (!Aben.Herkunft()->Region().empty())
      Aben.getRegion(cH_Region::getRegionfromAbk(Aben.Herkunft()->Region()))=true;
   setMuttersprache();
   Aben.setUeberleben(getUeberleben());
   if(!(vorgabe&B_AngeFert)) setAngebFert();
   else            Aben.List_Fertigkeit_ang()=oldAben.List_Fertigkeit_ang();
   Lernschema();
   setBeruf();
   lernpunkte.geld_wuerfeln(Aben);
   setWaffenBesitz();
   lernpunkte.ruestung_auswaehlen(Aben,Random::W100());
   lernpunkte.ausruestung_setzen(Aben);
}

extern std::vector<MBEmlt> List_to_Vector(std::list<MBEmlt> L,const Abenteurer& Aben,int lp);

void Zufall::setAngebFert()
{
   Aben.setAngebFert();
   int wurf;
   do{
      wurf=Random::W100(); 
      if(wurf==100) 
       { std::list<MBEmlt> L=LernListen::getMBEm(Aben,LernListen::lAngebFert);
         std::vector<MBEmlt> V=List_to_Vector(L,Aben,99);
         if(V.empty()) break;
         int i=Random::integer(0,V.size()-1);
         cH_Fertigkeit_angeborene F(V[i]->getMBE());
         Aben.setAngebSinnFert(F->Min(),V[i]);
       }
      else lernpunkte.AngebFert_gewuerfelt(Aben,wurf);
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
  A.List_Fertigkeit()=A.Spezies()->getFertigkeiten(lpspezies,A);

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
  A.setAlter( age * A.Spezies()->AlterFaktor());

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

