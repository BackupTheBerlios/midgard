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
   Aben->getWerte().setSpezies(getSpezies());
   hauptfenster->table_grundwerte->Eigenschaften_variante(1);
   Aben->getWerte().setGeschlecht(getGeschlecht());
   Aben->setTyp1(getTyp());
   hauptfenster->table_grundwerte->on_abge_werte_setzen_clicked();
   Aben->getWerte().setHerkunft(getLand());
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
}


enum Zufall::B_VORGABE_BITS &operator++(enum Zufall::B_VORGABE_BITS &s)
{  return (enum Zufall::B_VORGABE_BITS)(++(int&)s);
}

void Zufall::Teil(e_Vorgabe vorgabe)
{
  for(B_VORGABE_BITS i=B_VORGABE_BITS(0);i<B_MAX;++i)
   {
    if(!(vorgabe&(1<<i))) continue;
    if (i==B_Spezies) cout << "Spezies NICHT auswürfeln\n";
    if (i==B_Typ) cout << "Typ NICHT auswürfeln\n";
   }
}

void Zufall::setMuttersprache()
{
  MidgardBasicElement_mutable sprache=getMuttersprache();
  Aben->List_Sprache().push_back(sprache);
  Aben->setMuttersprache(sprache->Name());  
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
