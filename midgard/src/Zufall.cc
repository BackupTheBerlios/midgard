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

// generated 2002/9/6 20:10:27 CEST by thoma@Tiger.(none)
// using glademm V1.1.1c_cvs
//
// newer (non customized) versions of this file go to table_zufall.cc_new

// This file is for your program, I won't touch it again!

#include "Zufall.hh"
#include "Fertigkeiten_angeboren.hh"

void Zufall::Voll()
{
  Teil(e_Vorgabe(0),oldAben);
}


enum Zufall::B_VORGABE_BITS &operator++(enum Zufall::B_VORGABE_BITS &s)
{  return (enum Zufall::B_VORGABE_BITS)(++(int&)s);
}

struct st_vor{bool spezies; bool typ; bool herkunft; bool angefert;
                     bool st; bool gs; bool gw; bool ko; 
                     bool in; bool zt; bool au; bool pa; bool wk; bool sb; bool b;
              st_vor() :
                  spezies(true),typ(true),herkunft(true),angefert(true),
                  st(true),gs(true),gw(true),ko(true),
                  in(true),zt(true),au(true),pa(true),wk(true),sb(true),b(true){}
              };
      

void Zufall::Teil(e_Vorgabe vorgabe,const Abenteurer &A)
{
  oldAben=A;
  st_vor sv;
  for(B_VORGABE_BITS i=B_VORGABE_BITS(0);i<B_MAX;++i)
   {
    if(!(vorgabe&(1<<i))) continue;
    if (i==B_Spezies) sv.spezies=false;
    if (i==B_Typ) sv.typ=false;
    if (i==B_Herkunft) sv.herkunft=false;
    if (i==B_AngeFert) sv.angefert=false;
    if (i==B_St) sv.st=false;
    if (i==B_Gs) sv.gs=false;
    if (i==B_Gw) sv.gw=false;
    if (i==B_Ko) sv.ko=false;
    if (i==B_In) sv.in=false;
    if (i==B_Zt) sv.zt=false;
    if (i==B_Au) sv.au=false;
    if (i==B_pA) sv.pa=false;
    if (i==B_Wk) sv.wk=false;
    if (i==B_Sb) sv.sb=false;
    if (i==B_B)  sv.b=false;
   }

   if(sv.spezies)  Aben->getWerte().setSpezies(getSpezies());
   else            Aben->getWerte().setSpezies(oldAben.getWerte().Spezies());
   hauptfenster->table_grundwerte->Eigenschaften_variante(1);
   if(!sv.st)       Aben->getWerte().setSt(oldAben.getWerte().St());
   if(!sv.gs)       Aben->getWerte().setGs(oldAben.getWerte().Gs());
   if(!sv.gw)       Aben->getWerte().setGw(oldAben.getWerte().Gw());
   if(!sv.ko)       Aben->getWerte().setKo(oldAben.getWerte().Ko());
   if(!sv.in)       Aben->getWerte().setIn(oldAben.getWerte().In());
   if(!sv.zt)       Aben->getWerte().setZt(oldAben.getWerte().Zt());
   Aben->getWerte().setGeschlecht(getGeschlecht());
   if(sv.typ || !oldAben.Valid())      Aben->setTyp1(getTyp());
   else            Aben->setTyp1(oldAben.Typ1());     
   hauptfenster->table_grundwerte->on_abge_werte_setzen_clicked();
   if(!sv.au)       Aben->getWerte().setAu(oldAben.getWerte().Au());
   if(!sv.pa)       Aben->getWerte().setpA(oldAben.getWerte().pA());
   if(!sv.wk)       Aben->getWerte().setWk(oldAben.getWerte().Wk());
   if(!sv.sb)       Aben->getWerte().setSb(oldAben.getWerte().Sb());
   if(!sv.b)        Aben->getWerte().setB(oldAben.getWerte().B());
   
   if(sv.herkunft) Aben->getWerte().setHerkunft(getLand());
   else            Aben->getWerte().setHerkunft(oldAben.getWerte().Herkunft());
   setMuttersprache();
   Aben->getWerte().setUeberleben(getUeberleben());
   if(sv.angefert) setAngebFert();
   else            Aben->List_Fertigkeit_ang()=oldAben.List_Fertigkeit_ang();
   Lernschema();
   setBeruf();
   hauptfenster->table_lernschema->geld_wuerfeln();
   setWaffenBesitz();
   hauptfenster->table_lernschema->on_button_ruestung_clicked(random.integer(1,100));
   hauptfenster->table_lernschema->ausruestung_setzen();
   hauptfenster->table_grundwerte->zeige_werte();
   hauptfenster->table_lernschema->button_sensitive(true);
}

extern std::vector<MBEmlt> List_to_Vector(std::list<MBEmlt> L,const VAbenteurer& Aben,int lp);


void Zufall::setAngebFert()
{
   Aben->setAngebFert();
   int wurf;
   do{
      wurf=random.integer(0,100); 
      if(wurf==100) 
       { std::list<MBEmlt> L=LL.getMBEm(Aben,LernListen::lAngebFert);
         std::vector<MBEmlt> V=List_to_Vector(L,Aben,99);
         if(V.empty()) break;
         int i=random.integer(0,V.size()-1);
         cH_Fertigkeit_angeborene F(V[i].getMBE());
         Aben->setAngebSinnFert(F->Min(),V[i]);
       }
      else hauptfenster->table_lernschema->AngebFert_gewuerfelt(wurf);
     }while (wurf==100);
  Aben->List_Fertigkeit_ang().sort();
  Aben->List_Fertigkeit_ang().unique();
}


void Zufall::setMuttersprache()
{
  MBEmlt sprache=getMuttersprache();
  Aben->List_Sprache().push_back(sprache);
  Aben->setMuttersprache(sprache->Name());  
}


////////////////////////////////////////////////////////////////////////////
// Würfeln
////////////////////////////////////////////////////////////////////////////

void Zufall::Lernpunkte_wuerfeln(Lernpunkte &lernpunkte, VAbenteurer &A,Random &random)
{
  //Speziesspezifische Fertigkeiten
  int lpspezies=0;
  A->List_Fertigkeit()=A->getWerte().Spezies()->getFertigkeiten(lpspezies,A->getWerte());

  int fachlern=random.integer(1,6)+random.integer(1,6);
  lernpunkte.setFach(fachlern - lpspezies);
  lernpunkte.setAllgemein(random.integer(1,6)+1);
  lernpunkte.setUnge(random.integer(1,6));
  lernpunkte.setWaffen(random.integer(1,6)+random.integer(1,6));  
  if (A->Typ1()->is_mage()) lernpunkte.setZauber(random.integer(1,6)+random.integer(1,6));

  // Doppelcharaktere
  if(A->Typ2()->Short()!="" || A->Typ1()->Short()=="To" )
   {
      lernpunkte.setWaffen(random.integer(1,6)+1);
      lernpunkte.setZauber(random.integer(1,6)+1);
   }

  int age = (lernpunkte.Allgemein() + lernpunkte.Unge()
             + lernpunkte.Fach()
             + lernpunkte.Waffen() + lernpunkte.Zauber())/4+16;
  A->getWerte().setAlter( age * A->getWerte().Spezies()->AlterFaktor());

}



WaffeBesitzLernen Zufall::WaffenBesitz_wuerfeln(const VAbenteurer &A,int wurf)
{
  WaffeBesitzLernen l;
  if (A->Typ1()->Geld() == 1)
  { if      ( 1<=wurf&&wurf<=10 ) { l.set_EWaffe(3);      }
    else if (11<=wurf&&wurf<=20 ) { l.set_EWaffe(3); l.set_AWaffe(1); }
    else if (21<=wurf&&wurf<=30 ) { l.set_EWaffe(2); l.set_AWaffe(2); }
    else if (31<=wurf&&wurf<=60 ) { l.set_EWaffe(3); l.set_AWaffe(2); }
    else if (61<=wurf&&wurf<=80 ) { l.set_EWaffe(2); l.set_AWaffe(3); }
    else if (81<=wurf&&wurf<=95 ) {      l.set_AWaffe(5); }
    else if (96<=wurf&&wurf<=100) { l.set_EWaffe(1); l.set_AWaffe(4); l.setMagisch(true); }
  }  
  if (A->Typ1()->Geld() == 2)
  { if      ( 1<=wurf&&wurf<=10 ) { l.set_EWaffe(2);      }  
    else if (11<=wurf&&wurf<=20 ) { l.set_EWaffe(1); l.set_AWaffe(1); }  
    else if (21<=wurf&&wurf<=30 ) { l.set_EWaffe(2); l.set_AWaffe(1); }  
    else if (31<=wurf&&wurf<=60 ) { l.set_EWaffe(3); l.set_AWaffe(1); }  
    else if (61<=wurf&&wurf<=80 ) { l.set_EWaffe(2); l.set_AWaffe(2); }  
    else if (81<=wurf&&wurf<=95 ) {      l.set_AWaffe(4); }  
    else if (96<=wurf&&wurf<=100) { l.set_EWaffe(1); l.set_AWaffe(3); l.setMagisch(true); }
  }  
 if (A->Typ1()->Geld() == 3)
  { if      ( 1<=wurf&&wurf<=10 ) { l.set_EWaffe(1);      }  
    else if (11<=wurf&&wurf<=20 ) {      l.set_AWaffe(1); }  
    else if (21<=wurf&&wurf<=30 ) { l.set_EWaffe(2);      }  
    else if (31<=wurf&&wurf<=60 ) { l.set_EWaffe(1); l.set_AWaffe(1); }  
    else if (61<=wurf&&wurf<=80 ) { l.set_EWaffe(1); l.set_AWaffe(1); }  
    else if (81<=wurf&&wurf<=95 ) {      l.set_AWaffe(2); }  
    else if (96<=wurf&&wurf<=100) { l.set_EWaffe(1); l.set_AWaffe(1); l.setMagisch(true); }
  }  
 if (A->Typ1()->Geld() == 4)
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

