// $Id: midgard.cc,v 1.46 2002/07/01 10:22:42 christof Exp $
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

#include <gtk--/main.h>
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

int main(int argc, char **argv)
{   
   std::string magus_verzeichnis,argv0=argv[0];

#ifdef __MINGW32__ // gtkrc als Standard Ressourcen Datei
   putenv("GTK_RC_FILES=gtkrc");
   
//   const char dirsep='\\';
   
  char buf[1024];
  reg_key r1(HKEY_CURRENT_USER, KEY_READ, "Software", "Microsoft", "Windows",
  	"CurrentVersion", "Explorer", "User Shell Folders", NULL); // "AppData");?
  if (r1.get_string("Personal", buf, sizeof buf, "")==ERROR_SUCCESS) magus_verzeichnis=buf;
  else
  {  reg_key r2(HKEY_USERS, KEY_READ, ".Default", "Software", "Microsoft", "Windows",
  	"CurrentVersion", "Explorer", "User Shell Folders", NULL);
     if (r2.get_string("Personal", buf, sizeof buf, "")==ERROR_SUCCESS) magus_verzeichnis=buf;
     else
     {  reg_key r3(HKEY_LOCAL_MACHINE, KEY_READ, "Software", "Microsoft", "Windows",
     		"CurrentVersion", "Explorer", "User Shell Folders", NULL);
        if (r3.get_string("Personal", buf, sizeof buf, "")==ERROR_SUCCESS) magus_verzeichnis=buf;

        // %USERPROFILE%\Anwendungsdaten\Magus ???
        else magus_verzeichnis="C:\\Eigene Dateien";
     }
  }
  magus_verzeichnis+="\\Magus";
  std::cout << "magus_verzeichnis: " << magus_verzeichnis << '\n';

#else
//   const char dirsep='/';
   magus_verzeichnis=string(getenv("HOME"))+"/.magus";
#endif

   if(access(magus_verzeichnis.c_str(),R_OK)) 
       if(mkdir(magus_verzeichnis.c_str() NUR_LINUX(,0777) ))
         { std::cerr << "Homeverzeichnis nicht schreibbar\n"; exit(1);}
   magus_verzeichnis+=WinLux::dirsep;

   // normalize argv0 (prepend current dir if relative)
   if (argv0[0]!=WinLux::dirsep 
#ifdef __MINGW32__
			|| argv0.find(':')==std::string::npos
#endif
								)
   {  char buf[10240];
      *buf=0;
      getcwd(buf,sizeof buf);
      cout << "cwd: " << buf << '\n';
      argv0=buf+std::string(1,WinLux::dirsep)+argv0;
      cout << "argv0: " << argv0 << '\n';
   }

   Gtk::Main m(&argc, &argv,true); 

   // und mehrere Dateien ? CP   
   std::string datei;
   if (argc==2) datei=argv[1];

   midgard_CG *magus=new midgard_CG(argv0,magus_verzeichnis,datei);
   m.run();
   delete magus;
      
   xml_free();
   return 0;
}
