// $Id: Optionen.cc,v 1.7 2003/12/19 08:29:50 christof Exp $
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

#include "Optionen.hh"
#include <cassert>
#include "Ausgabe.hh"

Optionen::Optionen()
{
   Optionen_init();
   Hausregeln_init();
   make_ausschluesse();
}

Optionen::st_OptionenCheck &Optionen::OptionenCheck(OptionenCheckIndex oi) 
{
 for(std::list<st_OptionenCheck>::iterator i=list_OptionenCheck.begin();i!=list_OptionenCheck.end();++i)
   if(i->index==oi) 
     { return *i;
     }
 assert(!"OptionenCheck: nicht gefunden");
 abort();
}

const Optionen::st_OptionenCheck &Optionen::OptionenCheck(OptionenCheckIndex oi) const
{  return const_cast<Optionen*>(this)->OptionenCheck(oi);
}

Optionen::st_Haus &Optionen::HausregelCheck(HausIndex hi) 
{
 for(std::list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
   if(i->index==hi) return *i;
 assert(!"HausregelCheck: nicht gefunden");
 abort();
}

void Optionen::setOptionCheck(std::string os,bool b)
{
 for(std::list<st_OptionenCheck>::iterator i=list_OptionenCheck.begin();i!=list_OptionenCheck.end();++i)
   if(i->text==os) 
     {  i->active=b;return; }
 Ausgabe(Ausgabe::Warning, "Option "+os+" unbekannt");
}

void Optionen::setHausregeln(std::string hs,bool b)
{
  for(std::list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
    if(i->text==hs)  
      { i->active=b; return; }
 Ausgabe(Ausgabe::Warning, "Option "+hs+" unbekannt");
}

#if 0
void Optionen::setAllHausregeln(bool b)
{
  for(std::list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
     i->active=b;
}
#endif 
 
void Optionen::set_Original(bool active,OptionenCheckIndex index)
{
  for(std::list<Optionen::st_OptionenCheck>::iterator i=list_OptionenCheck.begin();i!=list_OptionenCheck.end();++i)
   { if (i->index==index) { i->active=active; return; }
   }
}   

void Optionen::Optionen_init()
{
  list_OptionenCheck.push_back(st_OptionenCheck(Original,"Originalregeln",true));
  list_OptionenCheck.push_back(st_OptionenCheck(NSC_only,"NSC zulassen",false));
}


void Optionen::Hausregeln_init()
{
 list_Hausregeln.push_back(st_Haus(Gold,"1 GS entspricht 1 GFP",false));
 list_Hausregeln.push_back(st_Haus(Werte100,"Grundwerte über 100 zulassen",false));
}

Optionen::Optionen(const Optionen &b)
	: list_Hausregeln(b.list_Hausregeln), list_OptionenCheck(b.list_OptionenCheck)
{  make_ausschluesse();
}

void Optionen::operator=(const Optionen &b)
{  list_Hausregeln=b.list_Hausregeln;
   list_OptionenCheck=b.list_OptionenCheck;
   make_ausschluesse();
}

void Optionen::make_ausschluesse()
{
 Model_ref<bool> orig=OptionenCheck(Original).active;
 ausschluesse.push_back(RadioModel(orig,HausregelCheck(Gold).active));
 ausschluesse.push_back(RadioModel(orig,HausregelCheck(Werte100).active));
}
