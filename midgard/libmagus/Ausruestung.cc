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


#include "Ausruestung.hh"
#include <Misc/itos.h>
#include <dtos1.h>

std::string Ausruestung::SAnzahl() const
{
 if(anzahl) 
   {
     return itos(anzahl)+"$\\times$ ";
   }
 return "";
}


std::string Ausruestung::SGewicht() const
{
  std::string gewicht;
  if(Gewicht()!=0) gewicht= dtos1(Gewicht())+" kg" ;
  return gewicht;
}

void AusruestungBaum::fixLinks()
{ for (iterator i=child.begin();i!=child.end();++i)
    i->setParent(this);
}

void AusruestungBaum::setParent(AusruestungBaum *p) 
{ parent=p;
  fixLinks();
}

AusruestungBaum &AusruestungBaum::push_back(const Ausruestung& a)
{ child.push_back(a);
  iterator _new=--child.end();
  _new->setParent(this);
  return *_new; 
}

AusruestungBaum &AusruestungBaum::insert(iterator where, const AusruestungBaum& a)
{ iterator _new=child.insert(where,a);
  _new->setParent(this);
  return *_new;
}
