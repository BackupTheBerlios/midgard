// $Id: fertigk_exp.cc,v 1.13 2002/01/18 08:09:25 christof Exp $
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
#include <Aux/itos.h>

void fert_speichern(std::ostream &o)
{  
   Transaction t;
   
   o << " <Fertigkeiten>\n";
  {Query query("select fertigkeit, region, lp as lernpunkte, "
  	MIDGARD3_4("","lp_land, lp_stadt, ")
  	" anfangswert0, fp, anfangswert, "
  	MIDGARD3_4("","ungelernt, ")
  	" attribut"
  	MIDGARD3_4("",", berufsklasse")
  	" from fertigkeiten left join steigern_fertigkeiten on name=fertigkeit"
  	" where coalesce(region,'')='"+region+"'"
  	" order by coalesce(region,''),coalesce(wie,fertigkeit)!=fertigkeit,fertigkeit");
   FetchIStream is;
  while ((query>>is).good())
  {o << "  <Fertigkeit";
   std::string fert=fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_string_attrib(is, o, "Region");
   fetch_and_write_int_attrib(is, o, "Lernpunkte",99); // außergewöhnliche Fertigkeit
#ifndef MIDGARD3
   fetch_and_write_int_attrib(is, o, "Lernpunkte-Land",99);
   fetch_and_write_int_attrib(is, o, "Lernpunkte-Stadt",99);
#endif
   fetch_and_write_int_attrib(is, o, "Anfangswert");
   fetch_and_write_int_attrib(is, o, "Lernkosten");
   fetch_and_write_int_attrib(is, o, "Erfolgswert");
#ifndef MIDGARD3
   fetch_and_write_int_attrib(is, o, "Erfolgswert-ungelernt");
#endif
   fetch_and_write_string_attrib(is, o, "Attribut");
#ifndef MIDGARD3
   fetch_and_write_int_attrib(is, o, "Berufskategorie");
#endif
   o << ">\n";
   
   grund_standard_ausnahme(o, "fertigkeiten_typen", fert);
      //********** fertigkeiten_voraussetzung **********************************
   {  Query query2("select st," MIDGARD3_4("ge,","gw,gs,")
   		"ko,\"in\",zt,au,pa,sb,rw, fertigkeit"
   	" from fertigkeiten_voraussetzung"
   	" where name='"+fert+"' order by fertigkeit");
      FetchIStream is2;
      while ((query2>>is2).good()) 
      {  o << "    <Voraussetzungen";
         fetch_and_write_int_attrib(is2, o, "St");
#ifdef MIDGARD3
         fetch_and_write_int_attrib(is2, o, "Ge");
#else         
         fetch_and_write_int_attrib(is2, o, "Gw");
         fetch_and_write_int_attrib(is2, o, "Gs");
#endif
         fetch_and_write_int_attrib(is2, o, "Ko");
         fetch_and_write_int_attrib(is2, o, "In");
         fetch_and_write_int_attrib(is2, o, "Zt");
         fetch_and_write_int_attrib(is2, o, "Au");
         fetch_and_write_int_attrib(is2, o, "pA");
         fetch_and_write_int_attrib(is2, o, "Sb");
         fetch_and_write_int_attrib(is2, o, "RW");
         fetch_and_write_string_attrib(is2, o, "Fertigkeit");
         o << "/>\n";
      }
    }
   
      //********** Lernschema **********************************
    lernschema(o, MIDGARD3_4("Fertigkeit","Fachkenntnisse"), fert);
    pflicht_lernen(o, fert);
    verbot_lernen(o, fert);
    ausnahmen(o, "f", fert);

// ************************* Steigern wie *****************************
    {  Query query2("select wie from steigern_fertigkeiten where name='"+fert+"'");
       FetchIStream is2=query2.Fetch();
       std::string wie;
       if (is2.good()) wie=fetch_string(is2, fert);
       if (wie!=fert && !wie.empty())
       {  o << "    <steigern_wie";
          write_string_attrib(o, "Fertigkeit",wie);
          o << "/>\n";
       }
    }
//********************* praxispunkte ********************
#ifdef MIDGARD3
      { Query query2("select coalesce(max_wert,0), coalesce(lernfaktor,0)"
      		" from praxispunkte where name='"+fert+"'");
      	FetchIStream is2=query2.Fetch();
      	if (is2.good())
      	{  o << "    <Praxispunkte";
           fetch_and_write_int_attrib(is2, o, "MaximalWert");
           fetch_and_write_int_attrib(is2, o, "Lernfaktor");
           o << "/>\n";
        }
      }
#endif

//********************* steigern_fertigkeiten_werte ********************
      {  Query query2("select"
      	    " coalesce(p0,0), coalesce(p1,0), coalesce(p2,0), coalesce(p3,0),"
      	    " coalesce(p4,0), coalesce(p5,0), coalesce(p6,0), coalesce(p7,0),"
      	    " coalesce(p8,0), coalesce(p9,0), coalesce(p10,0), coalesce(p11,0),"
      	    " coalesce(p12,0), coalesce(p13,0), coalesce(p14,0), coalesce(p15,0),"
      	    " coalesce(p16,0), coalesce(p17,0), coalesce(p18,0), coalesce(p19,0),"
      	    " coalesce(p20,0), coalesce(p21,0), coalesce(p22,0), coalesce(p23,0),"
      	    " coalesce(p24,0), coalesce(p25,0), coalesce(p26,0), coalesce(p27,0),"
      	    " coalesce(p28,0)"
       	    " from steigern_fertigkeiten_werte"
       	    " where name='"+fert+"'");;
      	FetchIStream is2=query2.Fetch();
      	if (is2.good())
        {  o << "    <Kosten";
           for (int i=0;i<=28;++i) 
              fetch_and_write_int_attrib(is2, o, "Wert"+itos(i));
           o << "/>\n";
        }
      }

      //********** ZEP oder KEP ? ****************
     {   Query query2("select ep from steigern_fertigkeiten_mit"
     		" where name='"+fert+"' order by ep");
      	FetchIStream is2;
      	std::string ep;
      	while ((query2>>is2).good())
        {  ep+=" "+fetch_string(is2)+"=\"true\"";
        }
        if (ep!=" KEP=\"true\" ZEP=\"true\"")
           o << "    <verwendbareEP" << ep << "/>\n";
     }
   
   o << "  </Fertigkeit>\n";
  }
  }
#ifdef REGION // Lernschema für Typen dieser Region
  if (!region.empty())
 { FetchIStream is;
   Query q("select fertigkeit, region from fertigkeiten "
   	+ RegionErgaenzungQuery("fertigkeiten.fertigkeit","fertigkeiten_typen","Fertigkeit","f")
   	+ "order by coalesce(region,''),fertigkeit");
  while ((q >> is).good())
  {o << "  <Fertigkeit";
   std::string fert=fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_string_attrib(is, o, "Region");
   o << ">\n";

   grund_standard_ausnahme(o, "fertigkeiten_typen",fert,"",true);
   lernschema(o, MIDGARD3_4("Fertigkeit","Fachkenntnisse"),fert,true);
   pflicht_lernen(o, fert, true);
   verbot_lernen(o, fert, true);
   ausnahmen(o, "f", fert,true);
   o << "  </Fertigkeit>\n";
  }
 }
#endif
   o << " </Fertigkeiten>\n";

//********************* angeborene Fertigkeiten ********************
  if (region.empty())
  {o << " <angeboreneFertigkeiten>\n";
  {Query query("select name, min, max, wert"
  	" from angeborene_fertigkeiten"
  	" order by name");
   FetchIStream is;
   while ((query>>is).good())
  {o << "  <angeboreneFertigkeit";
   fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_int_attrib(is, o, "Min");
   fetch_and_write_int_attrib(is, o, "Max");
   fetch_and_write_int_attrib(is, o, "Wert");
   o << "/>\n";
  }
   o << " </angeboreneFertigkeiten>\n";
  }
  }

//********************* Berufe ********************
   o << " <Berufe>\n";
  {
#ifdef MIDGARD3
   Query query("select beruf, region, lernpunkte, st, ge,"
  	" ko, \"in\", zt, pa, au, sb, typ, geschlecht"
   	" from berufe_voraussetzung"
  	" where coalesce(region,'')='"+region+"'"
   	" order by region, beruf");
#else
   Query query("select beruf, region, land, stadt,"
   	"typ_k, typ_z, geschlecht, u,v,m,a"
   	" from berufe_voraussetzung_4"
  	" where coalesce(region,'')='"+region+"'"
   	" order by region, beruf");
#endif
   FetchIStream is;
   while ((query>>is).good())
  {o << "  <Beruf";
   std::string beruf=fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_string_attrib(is, o, "Region");
#ifdef MIDGARD3    
   fetch_and_write_int_attrib(is, o, "Lernpunkte");
#endif
   o << ">\n";
   o << "    <Voraussetzungen";
#ifdef MIDGARD3
   fetch_and_write_int_attrib(is, o, "St");
   fetch_and_write_int_attrib(is, o, "Ge");
   fetch_and_write_int_attrib(is, o, "Ko");
   fetch_and_write_int_attrib(is, o, "In");
   fetch_and_write_int_attrib(is, o, "Zt");
   fetch_and_write_int_attrib(is, o, "pA");
   fetch_and_write_int_attrib(is, o, "Au");
   fetch_and_write_int_attrib(is, o, "Sb");
   fetch_and_write_typ_attrib(is, o, "Typ");
#else
   fetch_and_write_bool_attrib(is, o, "Land");
   fetch_and_write_bool_attrib(is, o, "Stadt");
   fetch_and_write_bool_attrib(is, o, "Kämpfer");
   fetch_and_write_bool_attrib(is, o, "Zauberer");
#endif
   fetch_and_write_string_attrib(is, o, "Geschlecht");
   o << "/>\n";
   {  
#ifdef MIDGARD3
      Query query2("select stand from berufe_stand where beruf='"+beruf
      		+"' order by stand");
      FetchIStream is2;
      std::string staende;
      while ((query2>>is2).good())
      {  std::string stand=fetch_string(is2);
         if (stand=="U") staende+=" Unfrei=\"true\"";
         if (stand=="V") staende+=" Volk=\"true\"";
         if (stand=="M") staende+=" Mittelschicht=\"true\"";
         if (stand=="A") staende+=" Adel=\"true\"";
      }
#else
      std::string staende;
      if (fetch_bool(is)) staende+=" Unfrei=\"true\"";
      if (fetch_bool(is)) staende+=" Volk=\"true\"";
      if (fetch_bool(is)) staende+=" Mittelschicht=\"true\"";
      if (fetch_bool(is)) staende+=" Adel=\"true\"";
#endif
      if (!staende.empty() 
      	&& staende!=" Unfrei=\"true\" Volk=\"true\" Mittelschicht=\"true\" Adel=\"true\""
      	&& staende!=" Adel=\"true\" Mittelschicht=\"true\" Unfrei=\"true\" Volk=\"true\"")
         o << "    <Stand" << staende << "/>\n";
   }
   {  Query query2(
   		"select vorteil from berufe_vorteile" MIDGARD3_4("","_4")
   		" where beruf='"+beruf
      		+"' order by vorteil");
      FetchIStream is2;
      std::string vorteile;
      while ((query2>>is2).good())
      {  vorteile+="<Fertigkeit Name=\""+toXML(fetch_string(is2))+"\"/>";
      }
      if (!vorteile.empty())
         o << "    <Vorteil>" << vorteile << "</Vorteil>\n";
   }

   pflicht_lernen(o, beruf);
   verbot_lernen(o, beruf);
   o << "  </Beruf>\n";
  }
  }
   o << " </Berufe>\n";

//********************* Pflicht + verboten ********************
  if (region.empty())
  {o << " <Typ-Pflichten>\n";
   o << "    <-- hier stehen nur die Dinge, die nicht schon Fertigkeiten/Berufe/Waffen(grund)fert. sind -->\n";
   Query query("select pflicht, typ, lernpunkte, verboten, spielbegin, erfolgswert"
   	" from pflicht_lernen"
   	" where not exists (select true from fertigkeiten"
   		" where pflicht=fertigkeit or verboten=fertigkeit)"
   	" and not exists (select true from "
   		MIDGARD3_4("berufe_voraussetzung","berufe_voraussetzung_4")
   		" where pflicht=beruf or verboten=beruf)"
   	" and not exists (select true from waffen"
   		" where pflicht=name or verboten=name)"
   	" and not exists (select true from waffen_grund"
   		" where pflicht=name or verboten=name)"
   	" order by typ,coalesce(pflicht,''),verboten");
   FetchIStream is;
  while ((query>>is).good())
  {std::string pflicht=fetch_string(is);
   if (pflicht.size())
   {  o << "  <Pflicht";
      fetch_and_write_string_attrib(is, o, "Typ");
      write_string_attrib(o, "Fertigkeit", pflicht);
      fetch_and_write_int_attrib(is, o, "Lernpunkte");
      fetch_string(is); // verboten
      std::string spielbeg=fetch_string(is);
      write_bool_attrib(o, "Spielbeginn",!spielbeg.empty());
      fetch_and_write_int_attrib(is, o, "Erfolgswert");
      o << "/>\n";
   }
   else
   {  o << "  <Verbot";
      fetch_and_write_string_attrib(is, o, "Typ");
      fetch_int(is); // Lernpunkte
      fetch_and_write_string_attrib(is, o, "Fertigkeit");
      fetch_and_write_string_attrib(is, o, "Spielbeginn");
      o << "/>\n";
   }
  }
   o << " </Typ-Pflichten>\n";
 }

//********************* praxispunkte ********************
#ifdef MIDGARD3
  if (region.empty())
  {o << " <Praxispunkte>\n";
   Query query("select name, max_wert, lernfaktor"
   	" from praxispunkte"
   	" where not exists (select true from fertigkeiten where name=fertigkeit)"
   	" order by name");
   FetchIStream is;
  while ((query>>is).good())
  {o << "  <Steigern";
   fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_int_attrib(is, o, "MaximalWert");
   fetch_and_write_int_attrib(is, o, "Lernfaktor");
   o << "/>\n";
  }
   o << " </Praxispunkte>\n";
  }
#endif

//********************* ZEP oder KEP oder beides? ********************
  if (region.empty())
  {o << " <verwendbareEP>\n";
   o << "    <-- hier stehen nur die Dinge, die nicht schon Fertigkeiten sind -->\n";
   Query query("select name, ep"
   	" from steigern_fertigkeiten_mit"
   	" where not exists (select true from fertigkeiten where name=fertigkeit)"
   	" order by name,ep");
   FetchIStream is;
   std::string fert,ep;
  while ((query>>is).good())
  {std::string fert2=fetch_string(is),ep2=fetch_string(is);
   if (fert!=fert2)
   {  if (ep.size())
         o << "  <EP-Typ Fertigkeit=\"" << toXML(fert) 
      		<< "\" Typ=\"" << toXML(ep.substr(1)) << "\"/>\n";
      fert=fert2;
      ep="";
   }
   ep+=std::string(",")+ep2;
  }
  if (ep.size()) 
         o << "  <EP-Typ Fertigkeit=\"" << toXML(fert) 
      		<< "\" Typ=\"" << toXML(ep.substr(1)) << "\"/>\n";
   o << " </verwendbareEP>\n";
 }

//*************************** Steigerungstabelle *******************
  if (region.empty())
  {o << " <SteigernKosten>\n";
   Query query("select name,"
      	    " coalesce(p0,0), coalesce(p1,0), coalesce(p2,0), coalesce(p3,0),"
      	    " coalesce(p4,0), coalesce(p5,0), coalesce(p6,0), coalesce(p7,0),"
      	    " coalesce(p8,0), coalesce(p9,0), coalesce(p10,0), coalesce(p11,0),"
      	    " coalesce(p12,0), coalesce(p13,0), coalesce(p14,0), coalesce(p15,0),"
      	    " coalesce(p16,0), coalesce(p17,0), coalesce(p18,0), coalesce(p19,0),"
      	    " coalesce(p20,0), coalesce(p21,0), coalesce(p22,0), coalesce(p23,0),"
      	    " coalesce(p24,0), coalesce(p25,0), coalesce(p26,0), coalesce(p27,0),"
      	    " coalesce(p28,0)"
       		" from steigern_fertigkeiten_werte"
   	" where not exists (select true from fertigkeiten where name=fertigkeit)"
       		" order by name");
   FetchIStream is;
  while ((query>>is).good())
       {  o << "    <Kosten";
          fetch_and_write_string_attrib(is, o, "Fertigkeit");
          for (int i=0;i<=28;++i) 
             fetch_and_write_int_attrib(is, o, "Wert"+itos(i));
          o << "/>\n";
       }
   o << " </SteigernKosten>\n";
  }

//******************************************************************
}

#ifndef XML_NO_MAIN
int main(int argc, char *argv[])
{  
   try{
      Petig::Connection conn;
      conn.setDbase("midgard");
      Petig::dbconnect(conn);

   std::cout << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n\n";
   std::cout << "<MidgardCG-data>\n";
   fert_speichern(std::cout);
   std::cout << "</MidgardCG-data>\n";
   Petig::dbdisconnect();
   } catch (SQLerror &e)
   {  std::cerr << e << '\n';
   }
   return 0;
}
#endif
