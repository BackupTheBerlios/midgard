/*  Midgard Character Generator
 *  Copyright (C) 2006 Christof Petig 
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

#include <iostream>
#include <libmagus/Zauber.hh>
#include <libmagus/LernListen.hh>
#include "test_header.cc"
   VAbenteurer::iterator ch=AbenteurerAuswahl::Chars->load("Hl.magus");
//   std::list<MBEmlt> L=LernListen::getMBEm(ch->getAbenteurer(),LernListen::lZaub);
   std::list<MBEmlt> L=LernListen::get_steigern_Zauberliste(ch->getAbenteurer(),false,false,false,false);
   { std::ofstream out("lernliste.txt");
     for (std::list<MBEmlt>::const_iterator i=L.begin();i!=L.end();++i)
       out << (*i)->getHandle<const Zauber>()->Kosten(ch->getAbenteurer()) << ' '
         << (*i)->getHandle<const Zauber>()->Name() << '\n';
   }
TEST_FOOTER
