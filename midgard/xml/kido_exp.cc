// $Id: kido_exp.cc,v 1.2 2002/01/03 08:20:58 christof Exp $
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
#include <Aux/Transaction.h>
#include <Aux/dbconnect.h>
#include "export_common.h"

void kido_speichern(std::ostream &o)
{  
   Transaction t;
#ifdef REGION   
   if (region=="K")
#endif
  {Query query("select name_orig, name, stufe, stil, fp, ap, effekt"
   	" from kido"
   	" order by name_orig");
   FetchIStream is;
   o << " <Kido-Fertigkeiten>\n";
  while ((query>>is).good())
  {o << "  <KiDo";
   fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_string_attrib(is, o, "Übersetzung");
   fetch_and_write_string_attrib(is, o, "Stufe");
   fetch_and_write_string_attrib(is, o, "Stil");
   fetch_and_write_int_attrib(is, o, "Lernkosten");
   fetch_and_write_string_attrib(is, o, "AP");
   o << ">";
   std::string Erklaerung=fetch_string(is);
   if (Erklaerung.size())  o << toXML(Erklaerung); 
   o << "</KiDo>\n";
  }
   o << " </Kido-Fertigkeiten>\n";
  }
}

#ifndef XML_NO_MAIN
int main(int argc, char *argv[])
{  
   try{
      Petig::Connection conn;
      conn.setDbase("midgard");
      Petig::dbconnect(conn);
      
      if (argc>1) region=argv[1];

   std::cout << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n\n";
   std::cout << "<MidgardCG-data>\n";
   kido_speichern(std::cout);
   std::cout << "</MidgardCG-data>\n";
   Petig::dbdisconnect();
   } catch (SQLerror &e)
   {  std::cerr << e << '\n';
   }
   return 0;
}
#endif
