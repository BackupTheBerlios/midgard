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
// Lücke
   
   hauptfenster->table_lernschema->geld_wuerfeln();
// Lücke

   hauptfenster->table_lernschema->on_button_ruestung_clicked(random(1,100));
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
    if (i==B_Spezies) cout << "Spezies\n";
    if (i==B_Typ) cout << "Typ\n";
   }
}

void Zufall::setMuttersprache()
{
  MidgardBasicElement_mutable sprache=getMuttersprache();
  Aben->List_Sprache().push_back(sprache);
  Aben->setMuttersprache(sprache->Name());  
}

