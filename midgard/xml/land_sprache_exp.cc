// $Id: land_sprache_exp.cc,v 1.10 2002/01/08 09:40:51 christof Exp $
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

void land_speichern(std::ostream &o)
{  
   Transaction t;
   FetchIStream is;

  if (region=="")
  {o << " <Länder>\n";
  {Query query("select land, kontinent, sprache"
   	" from land"
   	" order by kontinent,land,sprache");
  while ((query>>is).good())
  {o << "  <Land";
   fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_string_attrib(is, o, "Kontinent");
   fetch_and_write_string_attrib(is, o, "Sprache");
   o << "/>\n";
  }
 }
   o << " </Länder>\n";
  }

//******************************************************************
   o << " <Schriften>\n";
  {Query query("select name, region, typ, kosten, alt, kult"
   	" from schrift"
   	" where coalesce(region,'')='"+region+"'"
   	" order by coalesce(region,''),name");
  while ((query>>is).good())
  {o << "  <Schrift";
   fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_string_attrib(is, o, "Region");
   fetch_and_write_string_attrib(is, o, "Typ");
   fetch_and_write_int_attrib(is, o, "Kosten");
   fetch_and_write_bool_attrib(is, o, "alte_Schrift");
   fetch_and_write_bool_attrib(is, o, "Kultschrift");
   o << "/>\n";
  }
  }
   o << " </Schriften>\n";

//******************************************************************
   o << " <Sprachen>\n";
  {Query query("select name, region, fp, max_wert, alt,"
  	" gruppe_1, gruppe_2, minderheit"
   	" from sprachen"
   	" where coalesce(region,'')='"+region+"'"
   	" order by coalesce(region,''),name");
  while ((query>>is).good())
  {o << "  <Sprache";
   std::string sprache=fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_string_attrib(is, o, "Region");
   fetch_and_write_int_attrib(is, o, "Kosten");
   fetch_and_write_int_attrib(is, o, "Maximalwert");
//   fetch_and_write_string_attrib(is, o, "Schrift");
   fetch_and_write_bool_attrib(is, o, "alteSprache");
   fetch_and_write_int_attrib(is, o, "Gruppe");
   fetch_and_write_int_attrib(is, o, "Gruppe2");
   fetch_and_write_bool_attrib(is, o, "Minderheit");
   o << ">";
   Query query2("select art_der_schrift, schrift from sprache_schrift"
   	" where sprache="+toSQL(sprache)+" order by art_der_schrift");
   FetchIStream is2;
   while ((query2>>is2).good())
   {  o << "\n    <Schrift";
      fetch_and_write_string_attrib(is2, o, "Name");
      fetch_and_write_string_attrib(is2, o, "Bezeichnung", sprache);
      o << "/>";
   }
   o << "</Sprache>\n";
  }
  }
   o << " </Sprachen>\n";

//******************************************************************
  if (region=="")
  {o << " <SpeziesListe>\n";
   Query query("select spezies, nr,"
   		" ap_wert, alter, groesse_f, groesse_w, groesse_s, b_f, b_s,"
   		" lpbasis, ap_grad, gestalt, m_abb,"
   		" m_psy, m_phs, m_phk, gift," 
		" m_st,m_ge,m_ko,m_in,m_zt,m_sb,m_au,"
		" h_st,h_ge,h_ko,h_in,h_zt,h_sb,h_au"
   	" from spezies"
   	" order by spezies");
  while ((query>>is).good())
  {o << "  <Spezies";
   std::string name=fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_int_attrib(is, o, "MCG-Index");
   fetch_and_write_int_attrib(is, o, "MCG-AP_wert");
   o << ">\n";
   o << "    <Alter";
   fetch_and_write_int_attrib(is, o, "AnzahlWürfel");
   o << "/>\n";
   o << "    <Größe";
   fetch_and_write_int_attrib(is, o, "AnzahlWürfel");
   fetch_and_write_int_attrib(is, o, "ArtWürfel");
   fetch_and_write_int_attrib(is, o, "Addiere");
   o << "/>\n";
   o << "    <Bewegungsweite";
   fetch_and_write_int_attrib(is, o, "AnzahlWürfel");
   fetch_and_write_int_attrib(is, o, "Addiere");
   o << "/>\n";
   o << "    <Modifikation";
   fetch_and_write_int_attrib(is, o, "LP_Basis");
   fetch_and_write_int_attrib(is, o, "APproGrad");
   fetch_and_write_int_attrib(is, o, "Gestalt");
   fetch_and_write_int_attrib(is, o, "Abwehr");
   o << "><Resistenzen";
   fetch_and_write_int_attrib(is, o, "psy");
   fetch_and_write_int_attrib(is, o, "phs");
   fetch_and_write_int_attrib(is, o, "phk");
   fetch_and_write_int_attrib(is, o, "Gift");
   o << "/></Modifikation>\n";
   o << "    <Minima";
   fetch_and_write_int_attrib(is, o, "St");
   fetch_and_write_int_attrib(is, o, "Ge");
   fetch_and_write_int_attrib(is, o, "Ko");
   fetch_and_write_int_attrib(is, o, "In");
   fetch_and_write_int_attrib(is, o, "Zt");
   fetch_and_write_int_attrib(is, o, "Sb");
   fetch_and_write_int_attrib(is, o, "Au");
   o << "/>\n";
   o << "    <Maxima";
   fetch_and_write_int_attrib(is, o, "St");
   fetch_and_write_int_attrib(is, o, "Ge");
   fetch_and_write_int_attrib(is, o, "Ko");
   fetch_and_write_int_attrib(is, o, "In");
   fetch_and_write_int_attrib(is, o, "Zt");
   fetch_and_write_int_attrib(is, o, "Sb");
   fetch_and_write_int_attrib(is, o, "Au");
   o << "/>\n";
   {  Query query2("select typen from spezies_typen"
      	" where spezies='"+name+"'"
      	" order by spezies,typen");
      FetchIStream is2;
      std::string typen;
      while ((query2>>is2).good()) 
      {  if (!typen.empty()) typen+=",";
         typen+=fetch_typ(is2);
      }
      if (!typen.empty()) 
      {  o << "    <Typen>" << typen << "</Typen>\n";
      }
   }
   o << "  </Spezies>\n";
  }
   o << " </SpeziesListe>\n";
  }

//******************************************************************
  if (region=="")
  {o << " <Gradanstieg>\n";
   Query query("select grad, gfp, abwehr, resistenz, zaubern,"
   	" abwehr_kosten, resistenz_kosten, zaubern_kosten"
   	" from grad_anstieg"
   	" order by grad");
  while ((query>>is).good())
  {o << "  <Grad";
   fetch_and_write_int_attrib(is, o, "Grad");
   fetch_and_write_int_attrib(is, o, "GFP");
   fetch_and_write_int_attrib(is, o, "Abwehr");
   fetch_and_write_int_attrib(is, o, "Resistenz");
   fetch_and_write_int_attrib(is, o, "Zaubern");
   o << "><Kosten";
   fetch_and_write_int_attrib(is, o, "Abwehr");
   fetch_and_write_int_attrib(is, o, "Resistenz");
   fetch_and_write_int_attrib(is, o, "Zaubern");
   o << "/></Grad>\n";
  }
   o << " </Gradanstieg>\n";
 }

//********************** typen ****************************************
   o << " <Typen>\n";
  {Query query("select typs, region, typnr, typl, typlw, typz,"
   		" ausdauer, stand, sb, ruestung"
   	" from typen"
   	" where coalesce(region,'')='"+region+"'"
   	" order by coalesce(region,''),typs");
  while ((query>>is).good())
  {o << "  <Typ";
   fetch_and_write_typ_attrib(is, o, "Abkürzung");
   fetch_and_write_string_attrib(is, o, "Region");
   fetch_and_write_int_attrib(is, o, "MCG-Index");
   fetch_and_write_string_attrib(is, o, "Bezeichnung-Mann");
   fetch_and_write_string_attrib(is, o, "Bezeichnung-Frau");
   char zauberer=fetch_string(is,"n")[0];
   write_bool_attrib(o, "Zauberer",zauberer=='z'||zauberer=='j');
   fetch_and_write_string_attrib(is, o, "Ausdauer");
   o << "><Modifikation";
   fetch_and_write_int_attrib(is, o, "Stand");
   fetch_and_write_int_attrib(is, o, "Sb");
   fetch_and_write_int_attrib(is, o, "Rüstung");
   o << "/></Typ>\n";
  }
  }
   o << " </Typen>\n";
   
// ******************** preise ***********************
  
  if (region=="")
  {o << " <Preise>\n";
  {Query query("select name, art, kosten, einheit"MIDGARD3_4("",",gewicht")
   	" from preise"
   	" where not exists (select true from waffen"
   		" where waffen.name=preise.name)"
   	" and not exists (select true from ruestung"
   		" where ruestung.ruestung=preise.name)"
   	" order by art,name");
  while ((query>>is).good())
  {o << "  <Kaufpreis";
   fetch_and_write_string_attrib(is, o, "Ware");
   fetch_and_write_string_attrib(is, o, "Art");
   fetch_and_write_float_attrib(is, o, "Preis");
   fetch_and_write_string_attrib(is, o, "Währung");
#ifndef MIDGARD3   
   fetch_and_write_float_attrib(is, o, "Gewicht");
#endif
   o << "/>\n";
  }
  }

  {Query query("select name, art, faktor, min, einheit, typ, nr"
   	" from preise_modifikation"
   	" order by art,typ,name");
  while ((query>>is).good())
  {o << "  <Modifikation";
   fetch_and_write_string_attrib(is, o, "Bezeichnung");
   fetch_and_write_string_attrib(is, o, "Art");
   fetch_and_write_float_attrib(is, o, "Faktor");
   fetch_and_write_int_attrib(is, o, "Mindestpreis");
   fetch_and_write_string_attrib(is, o, "Einheit");
   fetch_and_write_string_attrib(is, o, "Typ");
   fetch_and_write_int_attrib(is, o, "MCG-Nr");
   o << "/>\n";
  }
   o << " </Preise>\n";
  }
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
      
      if (argc>1) region=argv[1];

   std::cout << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n\n";
   std::cout << "<MidgardCG-data>\n";
   land_speichern(std::cout);
   std::cout << "</MidgardCG-data>\n";
   Petig::dbdisconnect();
   } catch (SQLerror &e)
   {  std::cerr << e << '\n';
   }
   return 0;
}
#endif
