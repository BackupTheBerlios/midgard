// $Id: midgard.cc,v 1.55 2003/07/15 06:12:00 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include <gtkmm/main.h>
#include "midgard_CG.hh"
#include <unistd.h>
#include "xml.h"
#ifdef __MINGW32__
#include <io.h>
#include "registry.h"
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include "Windows_Linux.hh"
#include "Magus_Optionen.hh"

//#include <locale>

int main(int argc, char **argv)
{   
   magus_paths::init(argv[0],"");

#ifdef __MINGW32__ // gtkrc als Standard Ressourcen Datei
   std::string gtkrc="Gtk::RC_FILES="
   	+magus_paths::with_path("gtkrc");
   std::cout << gtkrc << '\n';
   putenv(gtkrc.c_str());
#endif
   Gtk::Main m(&argc, &argv,true); 

   // und mehrere Dateien ? CP   
   std::string datei;
   if (argc==2) datei=argv[1];

//   setlocale(LC_ALL, "de_DE");
   Magus_Optionen magus_optionen;
   magus_optionen.load_options(magus_paths::with_path("magus_optionen.xml",false,true));
   midgard_CG *magus=new midgard_CG(datei,magus_optionen);
   m.run(*magus);
   delete magus;
   return 0;
}
