/*  Midgard Character Generator
 *  Copyright (C) 2004 Christof Petig 
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
#include <Ausgabe.hh>
#include <AbenteurerAuswahl.h>
#include <Misc/itos.h>
#include <libmagus.hh>

void progress(double d)
{  Ausgabe(Ausgabe::Warning, "Progress " +itos(int(d*100))+ "%");
}

int main(int argc,const char **argv)
{  libmagus_init(argc,argv,&progress);
   VAbenteurer::iterator i
       =AbenteurerAuswahl::Chars->load
       ("../../../charaktere/Christof Petig/Aneren.magus");

   i->undosave("steigern Klettern");
   Enums::st_bool_steigern bs(false,false,false,false,false,false,false,false);
   MBEmlt f(cH_Fertigkeit("Klettern"));
   i->getAbenteurer().steigere(f,Enums::eUnterweisung,bs);
   i->getAbenteurer().speicherstream(std::cout);

   i->undosave("steigern Suchen");
   f=MBEmlt(cH_Fertigkeit("Suchen"));
   i->getAbenteurer().steigere(f,Enums::eUnterweisung,bs);
   i->getAbenteurer().speicherstream(std::cout);
   return 0;
}
