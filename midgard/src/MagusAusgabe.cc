// $Id: MagusAusgabe.cc,v 1.1 2003/09/01 06:48:57 christof Exp $
/*  Midgard Character Generator
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

#include <MagusAusgabe.hh>
#include <midgard_CG.hh>
#include <WindowInfo.hh>

std::vector<Magus_Ausgabe::entry> Magus_Ausgabe::remembered;

static midgard_CG *hauptfenster;

void Magus_Ausgabe::attach(midgard_CG *h)
{  hauptfenster=h;
   for (std::vector<entry>::const_iterator i=remembered.begin();i!=remembered.end();++i)
      replay(*i);
   remembered.clear();
}

void Magus_Ausgabe::callback(Ausgabe::Level l,const std::string &text)
{  //if (hauptfenster) play(l,text);
   //else 
      remembered.push_back(entry(l,text));
}

void Magus_Ausgabe::replay(const entry &e)
{  // ...
   // InfoFenster->AppendShow( ... ,WindowInfo::None);
   // set_info = InfoFenster->AppendShow(sadd);
}
