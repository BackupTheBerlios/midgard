// $Id: Datenbank.hh,v 1.15 2003/09/01 06:47:57 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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
//#include "Midgard_Info.hh"
#include "Prototyp.hh"
#include "Prototyp2.hh"
#include "Waffe.hh"
#include <Misc/Tag.h>
#include <BaseObjects/Model.h> // for cheap sigc++

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
  std::vector<cH_PreiseNewMod> preisenewmod;

  std::list<cH_Prototyp> prototyp;
  std::list<cH_Prototyp2> prototyp2;
  
  mutable Tag tag_eigene_artikel;
  
   //Konstruktor
  Datenbank();
  void load(SigC::Slot1<void,double> progress);
  static void init(SigC::Slot1<void,double> progress);
  
  // verwendet Alias map
  cH_Waffe WaffeVonBezeichnung(const std::string &name) const
  {  return Waffe::WaffeVonBezeichnung(name);
  }
  
  void load_region(const Tag &t,const std::string &file);
  void load_one(const std::string&, const Tag&);
  void load_list(const Tag&);
};

extern const class Datenbank Datenbank;
#endif
