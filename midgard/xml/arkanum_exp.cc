// $Id: arkanum_exp.cc,v 1.1 2001/12/19 14:12:06 christof Exp $
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
exec sql include sqlca;
#include "export_common.h"

// wegen eines bugs in epcg <=V6.1
#define GARNIX 

void arkanum_speichern(std::ostream &o)
{  
   Transaction t;

   o << " <Zauber>\n";
 { FetchIStream is;
   Query q("select name, region, stufe, kosten, ap, art, "
   	"ursprung, agens, prozess, reagens, "
   	"zauberdauer, reichweite, wirkungsziel, wirkungsbereich, "
   	"wirkungsdauer, material, "
   	"zauberart, element, spruchrolle, thaumagram "
   	"from zauber "
   	IF_REGION("where coalesce(region,'')='"+region+"' ")
   	"order by coalesce(region,''),name");
  while ((q >> is).good())
  {o << "  <Spruch";
   string zauber=fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_string_attrib(is, o, "Region");
   fetch_and_write_string_attrib(is, o, "Grad");
   fetch_and_write_int_attrib(is, o, "Lernkosten");
   fetch_and_write_string_attrib(is, o, "AP");
   fetch_and_write_string_attrib(is, o, "Typ");
   fetch_and_write_string_attrib(is, o, "Ursprung");
   fetch_and_write_string_attrib(is, o, "Agens");
   fetch_and_write_string_attrib(is, o, "Prozess");
   fetch_and_write_string_attrib(is, o, "Reagens");
   fetch_and_write_string_attrib(is, o, "Zauberdauer");
   fetch_and_write_string_attrib(is, o, "Reichweite");
   fetch_and_write_string_attrib(is, o, "Wirkungsziel");
   fetch_and_write_string_attrib(is, o, "Wirkungsbereich");
   fetch_and_write_string_attrib(is, o, "Wirkungsdauer");
   fetch_and_write_string_attrib(is, o, "Material");
   fetch_and_write_string_attrib(is, o, "Zauberart");
   fetch_and_write_string_attrib(is, o, "Element");
   fetch_and_write_bool_attrib(is, o, "Spruchrolle");
   fetch_and_write_string_attrib(is, o, "Thaumagramm");
   o << ">\n";
   grund_standard_ausnahme(o, "zauber_typen",zauber);
   lernschema(o, "Zauber",zauber);
   ausnahmen(o, "z", zauber);
      
//****************** Beschreibung *************************
      Query query2("select beschreibung from zauber_beschreibung "
      	"where name='"+zauber+"' and beschreibung is not null and beschreibung!=''");
      FetchIStream is2;
      if ((query2>>is2).good()) 
         fetch_and_write_string(is2,o,"Beschreibung",4);
   o << "  </Spruch>\n";
  }
 }
#ifdef REGION // Lernschema für Typen dieser Region
  if (region!="")
 { FetchIStream is;
   Query q("select name, region from zauber "
   	+ RegionErgaenzungQuery("zauber.name","zauber_typen","Zauber","z")
   	+ "order by coalesce(region,''),name");
  while ((q >> is).good())
  {o << "  <Spruch";
   std::string zauber=fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_string_attrib(is, o, "Region");
   o << ">\n";

   grund_standard_ausnahme(o, "zauber_typen",zauber,"",true);
   lernschema(o, "Zauber",zauber,true);
   ausnahmen(o, "z", zauber,true);
   o << "  </Spruch>\n";
  }
 }
#endif
   o << " </Zauber>\n";
   
   //***************** Zauberwerk ********************************

   o << " <Zauberwerke>\n";
  {Query query("select name, region, art, stufe, zeitaufwand, kosten, kosten_gfp"
  	" from zauberwerk"
  	IF_REGION(" where coalesce(region,'')='"+region+"' ")
  	" order by coalesce(region,''),name");
   FetchIStream is;
  while ((query>>is).good())
  {o << "  <Zauberwerk";
   string zauberwerk=fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_string_attrib(is, o, "Region");
   fetch_and_write_string_attrib(is, o, "Art");
   string stufe=fetch_and_write_string_attrib(is, o, "Stufe");
   fetch_and_write_string_attrib(is, o, "Zeitaufwand");
   fetch_and_write_string_attrib(is, o, "Geldaufwand");
   fetch_and_write_string_attrib(is, o, "Kosten");
   o << ">\n";
   
   grund_standard_ausnahme(o, "zauberwerk_typen", zauberwerk, "stufe='"+stufe+"'");

//************************ Voraussetzungen ****************************
	// Zauberwerk Voraussetzungen
   Query query2("select voraussetzung,verbindung from zauberwerk_voraussetzung"
	" where name='"+zauberwerk+"' order by voraussetzung");
   FetchIStream is2;
   while ((query2>>is2).good())
   {  o << "    <Voraussetzung";
      fetch_and_write_string_attrib(is2, o, "Fertigkeit");
      fetch_and_write_string_attrib(is2, o, "Verbindung");
      o << "/>\n";
   }
   o << "  </Zauberwerk>\n";
  }
 }
#ifdef REGION // Lernschema für Typen dieser Region
  if (region!="")
  {FetchIStream is;
   Query q("select name, region from zauberwerk "
   	+ RegionErgaenzungQuery("zauberwerk.name","zauberwerk_typen","Zauber","z")
   	+ "order by coalesce(region,''),name");
  while ((q >> is).good())
  {o << "  <Zauberwerk";
   std::string zauber=fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_string_attrib(is, o, "Region");
   o << ">\n";

   grund_standard_ausnahme(o, "zauber_typen",zauber,"",true);
   lernschema(o, "Zauber",zauber,true);
   ausnahmen(o, "z", zauber,true);
   o << "  </Zauberwerk>\n";
  }
  }
#endif
   o << " </Zauberwerke>\n";

//********************* Spezialgebiete ********************
#ifdef REGION
  if (region=="")
#endif  
  {o << " <Spezialgebiete>\n";
   Query query("select typ, spezialgebiet, nr, spezial, spezial2"
  	" from spezialgebiete order by typ,nr");
   FetchIStream is;
   while ((query>>is).good())
   {  o << "  <Spezialgebiet";
      fetch_and_write_typ_attrib(is, o, "Typ");
      fetch_and_write_string_attrib(is, o, "Name");
      fetch_and_write_int_attrib(is, o, "MCG:Index");
      fetch_and_write_string_attrib(is, o, "Spezialisierung");
      fetch_and_write_string_attrib(is, o, "Sekundärelement");
      o << "/>\n";
   }
   o << " </Spezialgebiete>\n";
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
   arkanum_speichern(std::cout);
   std::cout << "</MidgardCG-data>\n";
   Petig::dbdisconnect();
   } catch (SQLerror &e)
   {  std::cerr << e << '\n';
   }
   return 0;
}
#endif
