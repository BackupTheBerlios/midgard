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

#include <fstream>
#include <libmagus/AbenteurerAuswahl.h>
#include <libmagus/magus_paths.h>
#include <libmagus/libmagus.hh>
#include <libmagus/Ausgabe.hh>
#include <libmagus/Datenbank.hh>
#include <Misc/itos.h>

void progress(double d)
{  Ausgabe(Ausgabe::Warning, "Progress " +itos(int(d*100))+ "%");
}

int main(int argc,char **argv)
{  //libmagus_init0magus_paths::init(argv[0]);
 try {  
   libmagus_init0(argc,const_cast<const char**>(argv));
   magus_paths::prepend_dir("../../xml/");
   libmagus_init1(&progress);
   
#define TEST_FOOTER \
   return 0; \
 } catch (...) \
 { Ausgabe(Ausgabe::Error, "exception"); \
   return 1; \
 } \
}
