// $Id: all_exp.cc,v 1.9 2002/01/18 08:09:25 christof Exp $
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

void arkanum_speichern(std::ostream &o);
void land_speichern(std::ostream &o);
void fert_speichern(std::ostream &o);
void waffen_speichern(std::ostream &o);
void kido_speichern(std::ostream &o);

int main(int argc, char *argv[])
{  Petig::PrintUncaughtExceptions();
   try{
      Petig::Connection conn;
      conn.setDbase("midgard");
      Petig::dbconnect(conn);

   if (argc>1) region=argv[1];
   
   std::cout << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n\n";
   std::cout << "<MidgardCG-data";
   write_string_attrib(std::cout,"Region",region);
   {  Transaction tr;
      Query query("select name, file, url, maintainer, version, nr"
   	" from regionen where abkuerzung='"+region+"'");
      FetchIStream is=query.Fetch();
      if (query.good())
      {  fetch_and_write_string_attrib(is, std::cout, "Name");
         fetch_and_write_string_attrib(is, std::cout, "Dateiname");
         fetch_and_write_string_attrib(is, std::cout, "URL");
         fetch_and_write_string_attrib(is, std::cout, "Maintainer");
         fetch_and_write_string_attrib(is, std::cout, "Version");
         fetch_and_write_int_attrib(is, std::cout, "MCG-Index");
      }
   }
   std::cout << ">\n";
   land_speichern(std::cout);
   fert_speichern(std::cout);
   waffen_speichern(std::cout);
   // Arkanum ist ein extra Package
   if (!region.empty()) arkanum_speichern(std::cout);
   kido_speichern(std::cout);
   std::cout << "</MidgardCG-data>\n";
   Petig::dbdisconnect();
   } catch (SQLerror &e)
   {  std::cerr << e << '\n';
   }
   return 0;
}
