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
#include <libmagus/AbenteurerAuswahl.h>
#include <libmagus/libmagus.hh>
#include <libmagus/Ausgabe.hh>
#include <Misc/itos.h>
#include <libmagus/spielleiter_export.hh>

void progress(double d) {}

int main(int argc,char **argv)
{ if (argc!=2)
  { std::cout << "Syntax: " << argv[0] << " <Datei>\n";
    return 1;
  }
 try {  
   libmagus_init(argc,const_cast<const char**>(argv),&progress);
   VAbenteurer::iterator ch=AbenteurerAuswahl::Chars->load(argv[1]);
   spielleiter_export_save(ch->getAbenteurer(),"/dev/stdout");
   return 0;
 } catch (...)
 { Ausgabe(Ausgabe::Error, "exception");  
   return 1;
 }
}
