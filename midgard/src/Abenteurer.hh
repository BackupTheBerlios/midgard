// $Id: Abenteurer.hh,v 1.1 2002/05/22 17:00:44 thoma Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
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

#ifndef CLASS_ABENTEURER
#define CLASS_ABENTEURER
#include "Ausruestung.hh"
#include "Grundwerte.hh"
#include "Typen.hh"

class Abenteurer
{
   AusruestungBaum besitz;
   Grundwerte Werte;
   std::vector<cH_Typen> Typ;

   std::list<cH_MidgardBasicElement> list_Beruf;
   std::list<cH_MidgardBasicElement> list_Fertigkeit_ang;
   std::list<cH_MidgardBasicElement> list_Fertigkeit;
   std::list<cH_MidgardBasicElement> list_WaffenGrund;
   std::list<cH_MidgardBasicElement> list_Waffen;
   std::list<cH_MidgardBasicElement> list_Waffen_besitz;
   std::list<cH_MidgardBasicElement> list_Zauber;
   std::list<cH_MidgardBasicElement> list_Zauberwerk;
   std::list<cH_MidgardBasicElement> list_Kido;
   std::list<cH_MidgardBasicElement> list_Sprache; 
   std::list<cH_MidgardBasicElement> list_Schrift;        
   
public:
   Abenteurer() {Typ.resize(2);}

   void reset(){  list_Beruf.clear();
             list_Fertigkeit_ang.clear();list_Fertigkeit.clear();
             list_WaffenGrund.clear();list_Waffen.clear();
             list_Waffen_besitz.clear();list_Zauber.clear();
             list_Zauberwerk.clear();list_Kido.clear();
             list_Sprache.clear();list_Schrift.clear(); 
             Typ.clear(); Typ.resize(2);
             }

   Grundwerte &getWerte() {return Werte;}
   const Grundwerte &getCWerte() const {return Werte;}
   
   AusruestungBaum &getBesitz() {return besitz;}
   const AusruestungBaum &getCBesitz() const {return besitz;}

   const cH_Typen &CTyp1() const {return Typ[0];}
   const cH_Typen &CTyp2() const {return Typ[1];}
   void setTyp1(cH_Typen t) {Typ[0]=t;}
   void setTyp2(cH_Typen t) {Typ[1]=t;}
   const vector<cH_Typen> &getVTyp() const {return Typ;}
   bool is_mage() const {if(CTyp1()->is_mage() || CTyp2()->is_mage()) return true;
                         else return false;}

   const std::list<cH_MidgardBasicElement>& CList_Beruf() const {return list_Beruf;}
   const std::list<cH_MidgardBasicElement>& CList_Fertigkeit_ang() const {return list_Fertigkeit_ang;}
   const std::list<cH_MidgardBasicElement>& CList_Fertigkeit() const {return list_Fertigkeit;}
   const std::list<cH_MidgardBasicElement>& CList_WaffenGrund() const {return list_WaffenGrund;}
   const std::list<cH_MidgardBasicElement>& CList_Waffen() const {return list_Waffen;}
   const std::list<cH_MidgardBasicElement>& CList_Waffen_besitz() const {return list_Waffen_besitz;}
   const std::list<cH_MidgardBasicElement>& CList_Zauber() const {return list_Zauber;}
   const std::list<cH_MidgardBasicElement>& CList_Zauberwerk() const {return list_Zauberwerk;}
   const std::list<cH_MidgardBasicElement>& CList_Kido() const {return list_Kido;}
   const std::list<cH_MidgardBasicElement>& CList_Sprache() const {return list_Sprache;} 
   const std::list<cH_MidgardBasicElement>& CList_Schrift() const {return list_Schrift;}

   std::list<cH_MidgardBasicElement>& List_Beruf() {return list_Beruf;}
   std::list<cH_MidgardBasicElement>& List_Fertigkeit_ang() {return list_Fertigkeit_ang;}
   std::list<cH_MidgardBasicElement>& List_Fertigkeit()  {return list_Fertigkeit;}
   std::list<cH_MidgardBasicElement>& List_WaffenGrund() {return list_WaffenGrund;}
   std::list<cH_MidgardBasicElement>& List_Waffen()  {return list_Waffen;}
   std::list<cH_MidgardBasicElement>& List_Waffen_besitz() {return list_Waffen_besitz;}
   std::list<cH_MidgardBasicElement>& List_Zauber()  {return list_Zauber;}
   std::list<cH_MidgardBasicElement>& List_Zauberwerk()  {return list_Zauberwerk;}
   std::list<cH_MidgardBasicElement>& List_Kido()  {return list_Kido;}
   std::list<cH_MidgardBasicElement>& List_Sprache()  {return list_Sprache;} 
   std::list<cH_MidgardBasicElement>& List_Schrift()  {return list_Schrift;}

};

#endif
