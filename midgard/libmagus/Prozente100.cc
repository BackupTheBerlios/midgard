/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

#include "Prozente100.hh"
#include <cassert>

Prozente100::Prozente100()
: mage(true)
{
   VWas.push_back(st_was(MidgardBasicElement::FERTIGKEIT,30));
   VWas.push_back(st_was(MidgardBasicElement::WAFFE,30));
   VWas.push_back(st_was(MidgardBasicElement::ZAUBER,30));
   VWas.push_back(st_was(MidgardBasicElement::SPRACHE,7));
   VWas.push_back(st_was(MidgardBasicElement::SCHRIFT,3));
   VWas.push_back(st_was(MidgardBasicElement::WAFFEGRUND,0));
   VWas.push_back(st_was(MidgardBasicElement::ZAUBERWERK,0));
   VWas.push_back(st_was(MidgardBasicElement::KIDO,0));

   VSpezialist.push_back(st_was(MidgardBasicElement::FERTIGKEIT,50));
   VSpezialist.push_back(st_was(MidgardBasicElement::WAFFE,95));
   VSpezialist.push_back(st_was(MidgardBasicElement::SPRACHE,50));
   VSpezialist.push_back(st_was(MidgardBasicElement::SCHRIFT,50));

   check100();
}


void Prozente100::check100()
{
  assert(!VWas.empty());
  // Erst normieren
  int summe=Vsumme();
  if(!summe) VWas.begin()->prozent=100;
  for(std::vector<st_was>::iterator i=VWas.begin();i!=VWas.end();++i)
     i->prozent*=100./summe;
  summe=Vsumme(); 
  if(summe!=100) // dann den Rest verteilen
   {
     int diff=100-summe;
     add(MidgardBasicElement::FERTIGKEIT,diff);
   }
 for(std::vector<st_was>::iterator i=VSpezialist.begin();i!=VSpezialist.end();++i)
  { if     (i->prozent<0)   i->prozent=0;
    else if(i->prozent>100) i->prozent=100;
  }
}

const std::vector<Prozente100::st_was> Prozente100::get100V() const 
{
  const_cast<Prozente100&>(*this).check100();
  std::vector<st_was> V;
  int s=0;
  for(std::vector<st_was>::const_iterator i=VWas.begin();i!=VWas.end();++i)
   {
     if(i->prozent != 0)
      {
        V.push_back(st_was(i->was,s+i->prozent));
        s+=i->prozent;
      }
   }
  assert(s==100);
  return V;
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
  if(!mage) { set(MidgardBasicElement::ZAUBER,0); set(MidgardBasicElement::ZAUBERWERK,0);}
  check100(); 
}


void Prozente100::add(const MidgardBasicElement::MBEE &was,const int prozent)
{
  for(std::vector<st_was>::iterator i=VWas.begin();i!=VWas.end();++i)
     if(was==i->was) i->prozent+=prozent;
}

void Prozente100::set(const MidgardBasicElement::MBEE &was,const int prozent)
{
  for(std::vector<st_was>::iterator i=VWas.begin();i!=VWas.end();++i)
     if(was==i->was) i->prozent=prozent;
}

int Prozente100::get(const MidgardBasicElement::MBEE &was) const
{
  for(std::vector<st_was>::const_iterator i=VWas.begin();i!=VWas.end();++i)
     if(was==i->was) return i->prozent;
  assert(!"never get here"); abort();
}

void Prozente100::setS(const MidgardBasicElement::MBEE &was,const int prozent)
{
  for(std::vector<st_was>::iterator i=VSpezialist.begin();i!=VSpezialist.end();++i)
     if(was==i->was) i->prozent=prozent;
}

int Prozente100::getS(const MidgardBasicElement::MBEE &was) const
{
  for(std::vector<st_was>::const_iterator i=VSpezialist.begin();i!=VSpezialist.end();++i)
     if(was==i->was) return i->prozent;
  return 0; // wenn etwas nicht gesteigert werden kann dann entspricht das 100% Allgemeinbildung
}



void Grund_Standard_Ausnahme_MBE::check100()
{
   int summe=Gprozent+Sprozent+Aprozent;
   if(!summe) {Gprozent=100;}
   if(summe!=100)
    {
      Gprozent*=100./summe;
      Sprozent*=100./summe;
      Aprozent*=100./summe;
    }
   summe=Gprozent+Sprozent+Aprozent;
   if(summe!=100) Gprozent=100-Aprozent-Sprozent;
   if(Gprozent<0) {Gprozent=0; Aprozent=100-Sprozent;}
   summe=Gprozent+Sprozent+Aprozent;
   assert(summe==100);
}

