/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2002-2003 Christof Petig 
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

#include "Sinne.hh"
#include "NotFound.h"

cH_Sinne::cH_Sinne(const std::string& name,bool create)
{
 if (create) *this=new Sinne(name);
 else throw NotFound();
}

void Sinne::get_Sinne()
{
 if(Name()=="Sechster Sinn") anfangswert=0;
 else                        anfangswert=8;
}

Sinne::Sinne(const std::string &name)
      : MidgardBasicElement(name)
{get_Sinne();
}

MBEmlt cH_Sinne::init(const std::string &name)
{  cH_MidgardBasicElement r2=new Sinne(name);
   MBEmlt r3=r2;
   r3->setErfolgswert(r2->Anfangswert());
   return r3;
}

void Sinne_All::init(std::list<MBEmlt> &list)
{  list.push_back(cH_Sinne::init("Sehen"));
   list.push_back(cH_Sinne::init("Hören"));
   list.push_back(cH_Sinne::init("Riechen"));
   list.push_back(cH_Sinne::init("Schmecken"));
   list.push_back(cH_Sinne::init("Tasten"));
   list.push_back(cH_Sinne::init("Sechster Sinn"));
}

