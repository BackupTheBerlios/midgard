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

void Zufall::Voll()
{
  Teil(e_Vorgabe(0));
}


enum Zufall::B_VORGABE_BITS &operator++(enum Zufall::B_VORGABE_BITS &s)
{  return (enum Zufall::B_VORGABE_BITS)(++(int&)s);
}

struct st_vor{bool spezies; bool typ; bool herkunft; bool st; bool gs; bool gw; bool ko; 
                     bool in; bool zt; bool au; bool pa; bool wk; bool sb; bool b;
              st_vor() :
                  spezies(true),typ(true),herkunft(true),st(true),gs(true),gw(true),ko(true),
                  in(true),zt(true),au(true),pa(true),wk(true),sb(true),b(true){}

/*
              st_vor(bool _spezies,_typ,_herkunft,_st,_gs,_gw,_ko,_in,_zt,_au,_pa,_wk,_sb,_b) :
                  spezies(_spezies),typ(_typ),herkunft(_herkunft),st(_st),gs(_gs),gw(_gw),ko(_ko),
                  in(_in),zt(_zt),au(_au),pa(_pa),wk(_wk),sb(_sb),b(_b){}
*/
              };
      

void Zufall::Teil(e_Vorgabe vorgabe)
{
  st_vor sv;
  for(B_VORGABE_BITS i=B_VORGABE_BITS(0);i<B_MAX;++i)
   {
    if(!(vorgabe&(1<<i))) continue;
    if (i==B_Spezies) sv.spezies=false;
    if (i==B_Typ) sv.typ=false;
    if (i==B_Herkunft) sv.herkunft=false;
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

   if(sv.spezies)       Aben->getWerte().setSpezies(getSpezies());
   hauptfenster->table_grundwerte->Eigenschaften_variante(1);
   Aben->getWerte().setGeschlecht(getGeschlecht());
   if(sv.typ)           Aben->setTyp1(getTyp());
   hauptfenster->table_grundwerte->on_abge_werte_setzen_clicked();
   if(sv.herkunft)      Aben->getWerte().setHerkunft(getLand());
   setMuttersprache();
   Aben->getWerte().setUeberleben(getUeberleben());
   Aben->List_Fertigkeit_ang().clear();
   hauptfenster->table_lernschema->on_angeborene_fertigkeit_clicked();
   Lernschema();
// Lücke Beruf
   hauptfenster->table_lernschema->geld_wuerfeln();
   setWaffenBesitz();
   hauptfenster->table_lernschema->on_button_ruestung_clicked(random.integer(1,100));
   hauptfenster->table_lernschema->ausruestung_setzen();
   hauptfenster->table_grundwerte->zeige_werte();


}

void Zufall::setMuttersprache()
{
  MidgardBasicElement_mutable sprache=getMuttersprache();
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
  A.List_Fertigkeit()=A.getWerte().Spezies()->getFertigkeiten(lpspezies,A.getWerte());

  int fachlern=random.integer(1,6)+random.integer(1,6);
  lernpunkte.setFach(fachlern - lpspezies);
  lernpunkte.setAllgemein(random.integer(1,6)+1);
  lernpunkte.setUnge(random.integer(1,6));
  if (A.Typ2()->Short()=="") lernpunkte.setWaffen(random.integer(1,6)+random.integer(1,6));
  else                     lernpunkte.setWaffen(random.integer(1,6)+1); // Doppelcharakter
  if (A.Typ1()->is_mage() && A.Typ2()->Short()=="")
      lernpunkte.setZauber(random.integer(1,6)+random.integer(1,6));
  if (A.Typ2()->is_mage() && A.Typ2()->Short()!="") 
      lernpunkte.setZauber(random.integer(1,6)+1);


  int age = (lernpunkte.Allgemein() + lernpunkte.Unge()
             + lernpunkte.Fach()
             + lernpunkte.Waffen() + lernpunkte.Zauber())/4+16;
  A.getWerte().setAlter( age * A.getWerte().Spezies()->AlterFaktor());

}



WaffeBesitzLernen Zufall::WaffenBesitz_wuerfeln(const VAbenteurer &A,int wurf)
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
