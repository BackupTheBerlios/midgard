// $Id: zauber_exp.cc,v 1.13 2002/06/03 21:29:07 christof Exp $
/*  Midgard Roleplaying Character Generator
 *  Copyright (C) 2001-2002 Christof Petig
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

#include <iostream>
#include <Aux/Transaction.h>
#include "export_common.h"

void arkanum_speichern(Tag &o)
{  
   Transaction t;

   Tag &zauber=o.push_back(Tag("Zauber"));
 { FetchIStream is;
   Query q("select name, region,region_zusatz, stufe, kosten, ap, art, "
   	"ursprung, agens, prozess, reagens, "
   	"zauberdauer, reichweite, wirkungsziel, wirkungsbereich, "
   	"wirkungsdauer, material, "
   	"zauberart, element, spruchrolle, thaumagram,zusaetze,nsc_only "
   	"from zauber "
   	IF_REGION("where coalesce(region,'')='"+region+"' ")
   	"order by coalesce(region,''),name");
  while ((q >> is).good())
  {Tag &spruch=zauber.push_back(Tag("Spruch"));
   std::string zauber=fetch_and_set_string_attrib(is, spruch, "Name");
   fetch_and_set_string_attrib(is, spruch, "Region");
   fetch_and_set_string_attrib(is, spruch, "RegionZusatz");
   fetch_and_set_string_attrib(is, spruch, "Grad");
   fetch_and_set_int_attrib(is, spruch, "Lernkosten");
   fetch_and_set_string_attrib(is, spruch, "AP");
   fetch_and_set_string_attrib(is, spruch, "Typ");
   fetch_and_set_string_attrib(is, spruch, "Ursprung");
   fetch_and_set_string_attrib(is, spruch, "Agens");
   fetch_and_set_string_attrib(is, spruch, "Prozess");
   fetch_and_set_string_attrib(is, spruch, "Reagens");
   fetch_and_set_string_attrib(is, spruch, "Zauberdauer");
   fetch_and_set_string_attrib(is, spruch, "Reichweite");
   fetch_and_set_string_attrib(is, spruch, "Wirkungsziel");
   fetch_and_set_string_attrib(is, spruch, "Wirkungsbereich");
   fetch_and_set_string_attrib(is, spruch, "Wirkungsdauer");
   fetch_and_set_string_attrib(is, spruch, "Material");
   fetch_and_set_string_attrib(is, spruch, "Zauberart");
   fetch_and_set_string_attrib(is, spruch, "Element");
   fetch_and_set_bool_attrib(is, spruch, "Spruchrolle");
   fetch_and_set_string_attrib(is, spruch, "Thaumagramm");
   fetch_and_set_int_attrib(is, spruch, "Zus�tze");
   fetch_and_set_bool_attrib(is, spruch, "NSC_only");

   grund_standard_ausnahme(spruch, "zauber_typen",zauber);
   lernschema(spruch, MIDGARD3_4("Zauber","Zauberk�nste"),zauber);
   ausnahmen(spruch, "z", zauber);

   //********** fz_zus�tze **********************************
   {  Query queryZu("select name from fz_zusaetze "
      " where art='"+zauber+"' order by name");
      FetchIStream isZu;
      while ((queryZu>>isZu).good())
      {  spruch.push_back(Tag("Zus�tze")).setAttr("Name",fetch_string(isZu));
      }
   }  
                                                                    
   //********** Agens **********************************
   {  Query queryAg("select typ,agens from zauber_typen "
      " where name='"+zauber+"' and agens is not null");
      FetchIStream isAg;
      while ((queryAg>>isAg).good())
      {  Tag &agenstyp=spruch.push_back(Tag("AgensTyp"));
         fetch_and_set_string_attrib(isAg, agenstyp, "Typ");
         fetch_and_set_string_attrib(isAg, agenstyp, "Agens");
      }
   }  
                                                                    
                                                                    
      
//****************** Beschreibung *************************
      Query query2("select beschreibung from zauber_beschreibung "
      	"where name='"+zauber+"' and beschreibung is not null and beschreibung!=''");
      FetchIStream is2;
      if ((query2>>is2).good()) 
      {  std::string b=fetch_string(is2);
         if (!b.empty()) spruch.push_back(Tag("Beschreibung",b));
      }
  }
 }
  if (!region.empty())
 { FetchIStream is;
   Query q("select name, region,region_zusatz from zauber "
   	+ RegionErgaenzungQuery("zauber.name","zauber_typen","Zauber","z")
   	+ "order by coalesce(region,''),name");
  while ((q >> is).good())
  {Tag &spruch=zauber.push_back(Tag("Spruch"));
   std::string zauber=fetch_and_set_string_attrib(is, spruch, "Name");
   fetch_and_set_string_attrib(is, spruch, "Region");
   fetch_and_set_string_attrib(is, spruch, "RegionZusatz");

   grund_standard_ausnahme(spruch, "zauber_typen",zauber,"",true);
   lernschema(spruch, MIDGARD3_4("Zauber","Zauberk�nste"), zauber,true);
   ausnahmen(spruch, "z", zauber,true);
  }
 }
   
   //***************** Zauberwerk ********************************

  Tag &zauberwerke=o.push_back(Tag("Zauberwerke"));
  {Query query("select name, region,region_zusatz, art, stufe, zeitaufwand, kosten, kosten_gfp"
  	" from zauberwerk"
  	IF_REGION(" where coalesce(region,'')='"+region+"' ")
  	" order by coalesce(region,''),name,art,stufe");
   FetchIStream is;
  while ((query>>is).good())
  {Tag &zw=zauberwerke.push_back(Tag("Zauberwerk"));
   std::string zauberwerk=fetch_and_set_string_attrib(is, zw, "Name");
   fetch_and_set_string_attrib(is, zw, "Region");
   fetch_and_set_string_attrib(is, zw, "RegionZusatz");
   std::string art=fetch_and_set_string_attrib(is, zw, "Art");
   std::string stufe=fetch_and_set_string_attrib(is, zw, "Stufe");
   fetch_and_set_string_attrib(is, zw, "Zeitaufwand");
   fetch_and_set_string_attrib(is, zw, "Geldaufwand");
   fetch_and_set_string_attrib(is, zw, "Kosten");
   
   grund_standard_ausnahme(zw, "zauberwerk_typen", zauberwerk, "stufe='"+stufe+"' and art='"+art+"'");

//************************ Voraussetzungen ****************************
	// Zauberwerk Voraussetzungen
  {Query query2("select voraussetzung, verbindung, "
   " coalesce(fertigkeit) from zauberwerk_voraussetzung"
	" where name='"+zauberwerk+"' and voraussetzung is not null "
	" order by voraussetzung");
   FetchIStream is2;
   while ((query2>>is2).good())
   {  Tag &vor=zw.push_back(Tag("Voraussetzung"));
      fetch_and_set_string_attrib(is2, vor, "Zauber");
      fetch_and_set_string_attrib(is2, vor, "Verbindung");
   }
  }
  {Query query3("select fertigkeit from zauberwerk_voraussetzung"
	" where name='"+zauberwerk+"' and fertigkeit is not null "
	" order by fertigkeit");
   FetchIStream is3;
   while ((query3>>is3).good())
   {  zw.push_back(Tag("Voraussetzung")).setAttr("Fertigkeit",fetch_string(is3));
   }
  }
  }
 }
  if (!region.empty())
  {FetchIStream is;
   Query q("select name, region,region_zusatz, art, stufe from zauberwerk "
   	+ RegionErgaenzungQuery("zauberwerk.name","zauberwerk_typen","Zauber","z")
   	+ "order by coalesce(region,''),name");
  while ((q >> is).good())
  {Tag &zw=zauberwerke.push_back(Tag("Zauberwerk"));
   std::string zauberwerk=fetch_and_set_string_attrib(is, zw, "Name");
   fetch_and_set_string_attrib(is, zw, "Region");
   fetch_and_set_string_attrib(is, zw, "RegionZusatz");
   std::string art=fetch_and_set_string_attrib(is, zw, "Art");
   std::string stufe=fetch_and_set_string_attrib(is, zw, "Stufe");

   grund_standard_ausnahme(zw, "zauberwerk_typen",zauberwerk,"stufe='"+stufe+"' and art='"+art+"'",true);
//   lernschema(zw, "Zauber",zauberwerk,true);
//   ausnahmen(zw, "z", zauberwerk,true);
  }
  }

//********************* Spezialgebiete ********************
  if (region.empty() || region=="3")
  {Tag &sg=o.push_back(Tag("Spezialgebiete"));
   Query query("select typ, spezialgebiet, nr, spezial, spezial2"
  	" from spezialgebiete"
   	" where typ in (" + string(region.empty()?"'Ma'":"'eBe'") +
  	") order by typ,nr");
   FetchIStream is;
   while ((query>>is).good())
   {  Tag &sp=sg.push_back(Tag("Spezialgebiet"));
      fetch_and_set_string_attrib(is, sp, "Typ");
      fetch_and_set_string_attrib(is, sp, "Name");
      fetch_and_set_int_attrib(is, sp, "MAGUS-Index");
      fetch_and_set_string_attrib(is, sp, "Spezialisierung");
      fetch_and_set_string_attrib(is, sp, "Sekund�relement");
   }
  }

}

// ------------------------------------------------------
// -------- alte Variante, wird bald abgeschaltet ! -----

#if 0
void arkanum_speichern(std::ostream &o)
{  
   Transaction t;

   o << " <Zauber>\n";
 { FetchIStream is;
   Query q("select name, region,region_zusatz, stufe, kosten, ap, art, "
   	"ursprung, agens, prozess, reagens, "
   	"zauberdauer, reichweite, wirkungsziel, wirkungsbereich, "
   	"wirkungsdauer, material, "
   	"zauberart, element, spruchrolle, thaumagram,zusaetze,nsc_only "
   	"from zauber "
   	IF_REGION("where coalesce(region,'')='"+region+"' ")
   	"order by coalesce(region,''),name");
  while ((q >> is).good())
  {o << "  <Spruch";
   std::string zauber=fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_string_attrib(is, o, "Region");
   fetch_and_write_string_attrib(is, o, "RegionZusatz");
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
   fetch_and_write_int_attrib(is, o, "Zus�tze");
   fetch_and_write_bool_attrib(is, o, "NSC_only");
   o << ">\n";
   grund_standard_ausnahme(o, "zauber_typen",zauber);
   lernschema(o, MIDGARD3_4("Zauber","Zauberk�nste"),zauber);
   ausnahmen(o, "z", zauber);

   //********** fz_zus�tze **********************************
   {  Query queryZu("select name from fz_zusaetze "
      " where art='"+zauber+"' order by name");
      FetchIStream isZu;
      while ((queryZu>>isZu).good())
      {  o << "    <Zus�tze";
         fetch_and_write_string_attrib(isZu, o, "Name");
         o << "/>\n";
      }
   }  
                                                                    
   //********** Agens **********************************
   {  Query queryAg("select typ,agens from zauber_typen "
      " where name='"+zauber+"' and agens is not null");
      FetchIStream isAg;
      while ((queryAg>>isAg).good())
      {  o << "    <AgensTyp";
         fetch_and_write_string_attrib(isAg, o, "Typ");
         fetch_and_write_string_attrib(isAg, o, "Agens");
         o << "/>\n";
      }
   }  
                                                                    
                                                                    
      
//****************** Beschreibung *************************
      Query query2("select beschreibung from zauber_beschreibung "
      	"where name='"+zauber+"' and beschreibung is not null and beschreibung!=''");
      FetchIStream is2;
      if ((query2>>is2).good()) 
         fetch_and_write_string(is2,o,"Beschreibung",4);
   o << "  </Spruch>\n";
  }
 }
#ifdef REGION // Lernschema f�r Typen dieser Region
  if (!region.empty())
 { FetchIStream is;
   Query q("select name, region,region_zusatz from zauber "
   	+ RegionErgaenzungQuery("zauber.name","zauber_typen","Zauber","z")
   	+ "order by coalesce(region,''),name");
  while ((q >> is).good())
  {o << "  <Spruch";
   std::string zauber=fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_string_attrib(is, o, "Region");
   fetch_and_write_string_attrib(is, o, "RegionZusatz");
   o << ">\n";

   grund_standard_ausnahme(o, "zauber_typen",zauber,"",true);
   lernschema(o, MIDGARD3_4("Zauber","Zauberk�nste"), zauber,true);
   ausnahmen(o, "z", zauber,true);
   o << "  </Spruch>\n";
  }
 }
#endif
   o << " </Zauber>\n";
   
   //***************** Zauberwerk ********************************

   o << " <Zauberwerke>\n";
  {Query query("select name, region,region_zusatz, art, stufe, zeitaufwand, kosten, kosten_gfp"
  	" from zauberwerk"
  	IF_REGION(" where coalesce(region,'')='"+region+"' ")
  	" order by coalesce(region,''),name,art,stufe");
   FetchIStream is;
  while ((query>>is).good())
  {o << "  <Zauberwerk";
   std::string zauberwerk=fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_string_attrib(is, o, "Region");
   fetch_and_write_string_attrib(is, o, "RegionZusatz");
   std::string art=fetch_and_write_string_attrib(is, o, "Art");
   std::string stufe=fetch_and_write_string_attrib(is, o, "Stufe");
   fetch_and_write_string_attrib(is, o, "Zeitaufwand");
   fetch_and_write_string_attrib(is, o, "Geldaufwand");
   fetch_and_write_string_attrib(is, o, "Kosten");
   o << ">\n";
   
   grund_standard_ausnahme(o, "zauberwerk_typen", zauberwerk, "stufe='"+stufe+"' and art='"+art+"'");

//************************ Voraussetzungen ****************************
	// Zauberwerk Voraussetzungen
  {Query query2("select voraussetzung, verbindung, "
   " coalesce(fertigkeit) from zauberwerk_voraussetzung"
	" where name='"+zauberwerk+"' and voraussetzung is not null "
	" order by voraussetzung");
   FetchIStream is2;
   while ((query2>>is2).good())
   {  o << "    <Voraussetzung";
      fetch_and_write_string_attrib(is2, o, "Zauber");
      fetch_and_write_string_attrib(is2, o, "Verbindung");
      o << "/>\n";
   }
  }
  {Query query3("select fertigkeit from zauberwerk_voraussetzung"
	" where name='"+zauberwerk+"' and fertigkeit is not null "
	" order by fertigkeit");
   FetchIStream is3;
   while ((query3>>is3).good())
   {  o << "    <Voraussetzung";
      fetch_and_write_string_attrib(is3, o, "Fertigkeit");
      o << "/>\n";
   }
  }
   o << "  </Zauberwerk>\n";
  }
 }
#ifdef REGION // Lernschema f�r Typen dieser Region
  if (!region.empty())
  {FetchIStream is;
   Query q("select name, region,region_zusatz, art, stufe from zauberwerk "
   	+ RegionErgaenzungQuery("zauberwerk.name","zauberwerk_typen","Zauber","z")
   	+ "order by coalesce(region,''),name");
  while ((q >> is).good())
  {o << "  <Zauberwerk";
   std::string zauberwerk=fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_string_attrib(is, o, "Region");
   fetch_and_write_string_attrib(is, o, "RegionZusatz");
   std::string art=fetch_and_write_string_attrib(is, o, "Art");
   std::string stufe=fetch_and_write_string_attrib(is, o, "Stufe");
   o << ">\n";

   grund_standard_ausnahme(o, "zauberwerk_typen",zauberwerk,"stufe='"+stufe+"' and art='"+art+"'",true);
//   lernschema(o, "Zauber",zauberwerk,true);
//   ausnahmen(o, "z", zauberwerk,true);
   o << "  </Zauberwerk>\n";
  }
  }
#endif
   o << " </Zauberwerke>\n";

//********************* Spezialgebiete ********************
  if (region.empty() || region=="3")
  {o << " <Spezialgebiete>\n";
   Query query("select typ, spezialgebiet, nr, spezial, spezial2"
  	" from spezialgebiete"
   	" where typ in (" + string(region.empty()?"'Ma'":"'eBe'") +
  	") order by typ,nr");
   FetchIStream is;
   while ((query>>is).good())
   {  o << "  <Spezialgebiet";
      fetch_and_write_typ_attrib(is, o, "Typ");
      fetch_and_write_string_attrib(is, o, "Name");
      fetch_and_write_int_attrib(is, o, "MAGUS-Index");
      fetch_and_write_string_attrib(is, o, "Spezialisierung");
      fetch_and_write_string_attrib(is, o, "Sekund�relement");
      o << "/>\n";
   }
   o << " </Spezialgebiete>\n";
  }

}
#endif
