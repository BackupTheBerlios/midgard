// $Id: Abenteurer_besitz.cc,v 1.2 2002/10/25 21:01:17 thoma Exp $               
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

#include "Abenteurer.hh"
#include "dtos1.h"

void rekursiv(const std::list<AusruestungBaum> &AB, double &last)
{
  for(std::list<AusruestungBaum>::const_iterator i=AB.begin();i!=AB.end();++i)
   {
     last+=i->getAusruestung().Gewicht();
     std::list<AusruestungBaum> L=i->getChildren();
     rekursiv(L,last);
   }
}

double Abenteurer::getBelastung() const
{
  double last=0;
  for(AusruestungBaum::const_iterator i=getBesitz().begin();i!=getBesitz().end();++i)
   {
     last+=i->getAusruestung().Gewicht();
     std::list<AusruestungBaum> L=i->getChildren();
     rekursiv(L,last);
   }
  return last;
}



void Abenteurer::setStandardAusruestung()
{
  if(!getBesitz().empty()) return;

  AusruestungBaum *Koerper = &besitz.push_back(Ausruestung("Körper"));
  Koerper->setParent(&besitz);
  AusruestungBaum *Hose=&Koerper->push_back(Ausruestung("Hose"));
  Hose->setParent(Koerper);
  AusruestungBaum *Hemd=&Koerper->push_back(Ausruestung("Hemd"));
  Hemd->setParent(Koerper);
  AusruestungBaum *Guertel=&Koerper->push_back(Ausruestung("Gürtel"));
  Guertel->setParent(Koerper);
  AusruestungBaum *Schuhe=&Koerper->push_back(Ausruestung("Schuhe"));
  Schuhe->setParent(Koerper);
  AusruestungBaum *Rucksack=&Koerper->push_back(Ausruestung("Rucksack",0,"Leder","",true));
  Rucksack->setParent(Koerper);
  AusruestungBaum *Decke=&Rucksack->push_back(Ausruestung("Decke",0,"warm","",false));
  Decke->setParent(Rucksack);
  AusruestungBaum *Lederbeutel=&Rucksack->push_back(Ausruestung("Lederbeutel"));
  Lederbeutel->setParent(Guertel);
  AusruestungBaum *Geld=&Rucksack->push_back(Ausruestung("Geld",0,"","",false));
  Geld->setParent(Lederbeutel);

//  return *Rucksack;
//  setFertigkeitenAusruestung(Rucksack);
}

int Abenteurer::getTragkraft() const
{
  return 10;
}
int Abenteurer::getHubkraft() const 
{
  return 50;
}
int Abenteurer::getSchubkraft() const
{
  return 100;
}
