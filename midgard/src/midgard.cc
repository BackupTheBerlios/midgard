// $Id: midgard.cc,v 1.42 2002/06/27 14:51:26 thoma Exp $
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
//#include <unistd.h>
#include "xml.h"
#ifdef __MINGW32__
#include <io.h>
#endif

int main(int argc, char **argv)
{   
#ifdef __MINGW32__ // gtkrc als Standard Ressourcen Datei
   putenv("GTK_RC_FILES=gtkrc");
   {  char buf[10240];
      *buf=0;
      getcwd(buf,sizeof buf);
      cout << "cwd: " << buf << '\n';
      cout << "argv0: " << argv[0] << '\n';
      const char *lastbackslash=strrchr(argv[0],'\\');
      if (lastbackslash)
      {  std::string d((const char *)argv[0],lastbackslash);
         cout << "dir: " << d << '\n';
         chdir(d.c_str());
      }
   }
#endif
   Gtk::Main m(&argc, &argv,true); 
   
   std::string datei;
   if (argc==2) datei=argv[1];

   midgard_CG *magus=manage(new midgard_CG(argv[0],datei));
   m.run();
   magus->destroy();
      
   xml_free();
   return 0;
}
