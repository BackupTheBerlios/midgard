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

#include "test_header.cc"
   VAbenteurer::iterator ch=AbenteurerAuswahl::Chars->load("Hl.magus");
   ch->begin_undo();
   ch->getAbenteurer().wie_steigern=Abenteurer::ws_Selbststudium;
   ch->getAbenteurer().addAEP(100);
   MBEmlt mk=ch->getAbenteurer().get_known(MidgardBasicElement::FERTIGKEIT,"Menschenkenntnis");
   ch->getAbenteurer().Steigern(mk);
   ch->name_undo("in Selbststudium gesteigert");
   { std::ofstream out("test9.magus");
     ch->getAbenteurer().speichern(out);
   }
TEST_FOOTER
