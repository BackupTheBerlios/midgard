// $Id: midgard.cc,v 1.36 2002/02/15 08:24:36 thoma Exp $
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
#ifndef USE_XML   
#include <Aux/dbconnect.h>
#endif
//#include <unistd.h>
#include "xml.h"

int main(int argc, char **argv)
{   
   Gtk::Main m(&argc, &argv, true); 
   // hmm ich habe gehört, das true hilft gegen den Umlaut bug ...
   
   std::string datei;
   if (argc==2) datei=argv[1];

   manage(new midgard_CG(datei));
   m.run();
      
   xml_free();
   return 0;
}
