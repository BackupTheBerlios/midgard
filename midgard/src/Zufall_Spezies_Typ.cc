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
#include "Spezies.hh"

cH_Spezies Zufall::getSpezies() const
{
   std::vector<cH_Spezies> V=LL.getSpezies(true);
   int i=random.integer(0,V.size()-1);
   return V[i];   
}

Enums::geschlecht Zufall::getGeschlecht() const
{
  int i=random.integer(0,1);
  if     (i==0) return Enums::Mann;
  else if(i==1) return Enums::Frau;
  assert(!"never get here\n"); abort();
}

cH_Typen Zufall::getTyp() const
{
   std::vector<pair<cH_Typen,bool> > V=LL.getTypen(Aben,true);
   int i=random.integer(0,V.size()-1);
   return V[i].first;   
}

Enums::StadtLand Zufall::getStadtLand() const
{
  if     (hauptfenster->getWerte().Spezies()->Land()) return Enums::Land;
  else if(!hauptfenster->getChar().Typ1()->Stadt())  return Enums::Land;
  else if(!hauptfenster->getChar().Typ1()->Land()) return Enums::Stadt;

  int i=random.integer(0,1);
  if     (i==0) return Enums::Stadt;
  else if(i==1) return Enums::Land;
  assert(!"never get here\n"); abort();
}