// $Id: Datenbank.hh,v 1.16 2002/11/05 07:24:19 thoma Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#ifndef DATENBANKCLASS
#define DATENBANKCLASS

#include <MidgardBasicElement.hh>
#include <vector>
#include <string>
#include <list>

#include "Land.hh"   
//#include "Ausnahmen.hh"
#include "Spezies.hh"
#include "Typen.hh"
#include "Grad_anstieg.hh"
#include "Lernschema.hh"
#include "Preise.hh"
#include "Region.hh"  
#include "Ruestung.hh"
#include "Midgard_Info.hh"
#include "Prototyp.hh"
#include "Prototyp2.hh"

class midgard_CG;

class Datenbank
{
 public:
  std::vector<cH_Region> Regionen;
  std::vector<cH_Land> Laender;
  std::vector<cH_Ruestung> Ruestung;
  Lernschema lernschema;
  std::list<cH_MidgardBasicElement> Beruf;
  std::list<cH_MidgardBasicElement> Fertigkeit_ang;
  std::list<cH_MidgardBasicElement> Fertigkeit;
  std::list<cH_MidgardBasicElement> WaffeGrund;
  std::list<cH_MidgardBasicElement> Waffe;
  std::map<std::string,std::string> Waffe_from_Alias;
  std::list<cH_MidgardBasicElement> Zauber;
  std::list<cH_MidgardBasicElement> Zauberwerk;
  std::list<cH_MidgardBasicElement> Kido;
  std::list<cH_MidgardBasicElement> Sprache;
  std::list<cH_MidgardBasicElement> Schrift;
  std::vector<cH_Spezies> Spezies;
  std::vector<cH_Typen> Typen;
  Grad_anstieg GradAnstieg;
  std::vector<cH_Spezialgebiet> Spezialgebiet;
  std::list<cH_Preise> preise;
//  std::list<cH_PreiseMod> preisemod;
  std::vector<cH_PreiseNewMod> preisenewmod;

  std::list<cH_Prototyp> prototyp;
  std::list<cH_Prototyp2> prototyp2;
  
   //Konstruktor
  Datenbank();
  void load(Midgard_Info* MI,midgard_CG *hauptfenster);
};

#endif
