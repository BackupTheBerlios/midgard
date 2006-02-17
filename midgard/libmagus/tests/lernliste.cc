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
#include <libmagus/Abenteurer.hh>
#include <libmagus/LernListen.hh>

void dump_Liste(std::ostream &os, Abenteurer const &a, LernListen::eMBE was, std::string const& swas)
{ std::list<MBEmlt> L=LernListen::getMBEm(a,was,0,0,swas);
  os << a.Name_Abenteurer() << ' ' << swas << '\n';
  for (std::list<MBEmlt>::const_iterator i=L.begin();i!=L.end();++i)
  { if ((*i)->Lernpunkte()<99)
       os << (*i)->Lernpunkte() << "Lp +" << (*i)->Erfolgswert() << ' '
         << (*i)->getMBE()->Name() << '\n';
  }
}

#include "test_header.cc"
   std::ofstream out("lernliste.txt");
   VAbenteurer::iterator ch=AbenteurerAuswahl::Chars->load("Hl.magus");
   out << "Sprüche Heiler\n";
   std::list<MBEmlt> L=LernListen::get_steigern_Zauberliste(ch->getAbenteurer(),false,false,false,false);
   for (std::list<MBEmlt>::const_iterator i=L.begin();i!=L.end();++i)
       out << (*i)->getHandle<const Zauber>()->Kosten(ch->getAbenteurer()) << ' '
         << (*i)->getMBE()->Name() << '\n';
         
   ch=AbenteurerAuswahl::Chars->push_back();
   ch->getAbenteurer().Originalregeln();
  try{
   ch->getAbenteurer().setSt(50);
   ch->getAbenteurer().setGs(50);
   ch->getAbenteurer().setGw(50);
   ch->getAbenteurer().setKo(50);
   ch->getAbenteurer().setIn(50);
   ch->getAbenteurer().setZt(50);
   ch->getAbenteurer().Au_pA_wuerfeln();
   ch->getAbenteurer().setTyp1(Typen::getTyp("Magier"));
   ch->getAbenteurer().setNamen("Magier","test","");
   ch->getAbenteurer().abge_werte_setzen();
   ch->getAbenteurer().setHerkunft(cH_Land("Alba"));
   dump_Liste(out,ch->getAbenteurer(),LernListen::lFach,"Fach");
   dump_Liste(out,ch->getAbenteurer(),LernListen::lAllg,"Allg");
   dump_Liste(out,ch->getAbenteurer(),LernListen::lUnge,"Unge");
   dump_Liste(out,ch->getAbenteurer(),LernListen::lWaff,"Waff");
   dump_Liste(out,ch->getAbenteurer(),LernListen::lZaub,"Zaub");
  } catch (NotFound &e) { std::cerr << e.what() << ' ' << e.Name() << '\n'; }
TEST_FOOTER
