// $Id: midgard.cc,v 1.22 2001/09/19 13:36:43 thoma Exp $
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

// generated 2001/2/2 12:23:26 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to midgard.cc_glade

// This file is for your program, I won't touch it again!

#include <gtk--/main.h>

#include "midgard_CG.hh"
#include "Window_werte_editieren.hh"
#include "Window_lernpunkte_editieren.hh"
#include <Aux/dbconnect.h>
#include "Midgard_Info.hh"
#include <unistd.h>

int main(int argc, char **argv)
{   
   Gtk::Main m(&argc, &argv);
   manage(new Midgard_Info(true));
   while(Gtk::Main::events_pending()) Gtk::Main::iteration() ;
   if (argc==1) sleep(5);
   try {
      Petig::dbconnect(Petig::Connection("","midgard"));
      manage(new midgard_CG(argc,argv));
      m.run();
      
      Petig::dbdisconnect("midgard");
   } catch (SQLerror &e)
   {  std::cerr << e << '\n';
      return 1;
   }
   return 0;
}
