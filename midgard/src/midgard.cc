// $Id: midgard.cc,v 1.56 2003/08/11 06:19:56 christof Exp $
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
//#include <unistd.h>
//#include "xml.h"
#ifdef __MINGW32__
#include <io.h>
#include <libmagus/Ausgabe.hh>
#endif
//#include <sys/types.h>
//#include <sys/stat.h>
//#include "Windows_Linux.hh"
//#include "Magus_Optionen.hh"
#include <libmagus/libmagus.hh>

//#include <locale>

int main(int argc, char **argv)
{  libmagus_init0(argc,argv);
#ifdef __MINGW32__ // gtkrc als Standard Ressourcen Datei
   std::string gtkrc;
   if (!getenv("GTK_RC_FILES"))
   {  gtkrc="GTK_RC_FILES="+magus_paths::with_path("gtkrc");
      Ausgabe(Ausgabe::Debug,gtkrc);
      putenv(gtkrc.c_str());
   }
#endif
   Gtk::Main m(&argc, &argv,true); 

   std::vector<std::string> dateien;
   for (i=1;i<argc;++i) dateien.push_back(argv[i]);

//   setlocale(LC_ALL, "de_DE");
   midgard_CG *magus=new midgard_CG(dateien);
   m.run(*magus);
   delete magus;
   return 0;
}
