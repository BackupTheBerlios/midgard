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

#include "Prozente100.hh"

Prozente100::Prozente100()
: mage(true)
{
   VWas.push_back(st_was(fertigkeiten,30));
   VWas.push_back(st_was(waffen,30));
   VWas.push_back(st_was(zauber,30));
   VWas.push_back(st_was(sprachen,7));
   VWas.push_back(st_was(schriften,3));
   VWas.push_back(st_was(waffen_grund,0));
   VWas.push_back(st_was(zauberwerk,0));
   check100();
}


void Prozente100::check100()
{
  assert(!VWas.empty());
  while(true)
   {    
     int summe=Vsumme();
     if(summe==100) break;
     int diff=100-summe;
     add(fertigkeiten,diff);
   }
}


int Prozente100::Vsumme()
{
  int s=0;
  for(std::vector<st_was>::const_iterator i=VWas.begin();i!=VWas.end();++i)
     s+=i->prozent;
  return s;
}


void Prozente100::set_mage(bool m)
{
  mage=m;
  if(!mage) { set(zauber,0); set(zauberwerk,0);}
  check100(); 
}


void Prozente100::add(const ewas &was,const int prozent)
{
  for(std::vector<st_was>::iterator i=VWas.begin();i!=VWas.end();++i)
     if(was==i->was) i->prozent+=prozent;
}

void Prozente100::set(const ewas &was,const int prozent)
{
  for(std::vector<st_was>::iterator i=VWas.begin();i!=VWas.end();++i)
     if(was==i->was) i->prozent=prozent;
}

int Prozente100::get(const ewas &was) const
{
  for(std::vector<st_was>::const_iterator i=VWas.begin();i!=VWas.end();++i)
     if(was==i->was) return i->prozent;
  assert(!"never get here"); abort();
}

