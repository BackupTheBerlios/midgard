// $Id: all_exp.cc,v 1.14 2002/06/05 06:43:29 christof Exp $
/*  Midgard Roleplaying Character Generator
 *  Copyright (C) 2001 Christof Petig
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
#include <Aux/dbconnect.h>
#include <export_common.h>
#include <Aux/exception.h>
#include <Aux/FetchIStream.h>
#include <Aux/Transaction.h>
#include "TagStream.hh"

int main(int argc, char *argv[])
{  Petig::PrintUncaughtExceptions();
   try{
      Petig::Connection conn;
      conn.setDbase("midgard");
      Petig::dbconnect(conn);

   if (argc>1) region=argv[1];
   
      TagStream ts;
      Tag &data=ts.push_back(Tag("MAGUS-data"));
      region_tags(data,region);
   land_speichern(data);
   fert_speichern(data);
   waffen_speichern(data);
   // Arkanum ist ein extra Package
   if (!region.empty()) arkanum_speichern(data);
   kido_speichern(data);
      ts.write(std::cout);
   Petig::dbdisconnect();
   } catch (SQLerror &e)
   {  std::cerr << e << '\n';
   }
   return 0;
}
