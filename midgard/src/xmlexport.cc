// $Id: xmlexport.cc,v 1.9 2002/01/29 10:45:28 thoma Exp $
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

#include <string>
#include <Aux/FetchIStream.h>
#include <iostream>
#include <fstream>
#include <Aux/Transaction.h>
#include <Aux/dbconnect.h>
#include "../xml/export_common.h"
#include <list>

void charakter_speichern(std::ostream &o, const std::string &name,const std::string &version="")
{  //Transaction t;
   Query query1("select charakter_name, spieler_name, version, grad, "
   		"spezies, geschlecht, typ_s, typ_2_s, "
   		"spezialisierung, stadt_land,"
   		"st, gw, gs, ko, inn, zt, au, pa, wk,"
   		"sb, rw, hgw, b, kaw, wlw, gg, sg, abwehr, zaubern,"
   		"resistenz, lpbasis, lp, ap, alter, gestalt,"
   		"gewicht, groesse, stand, herkunft,"
   		"glaube, db_bo_au, db_bo_sc, db_bo_an, "
   		"db_bo_ab, db_bo_za, db_bo_psy, db_bo_phs, db_bo_phk,"
   		"db_bo_gi, db_gfp, gold, silber, kupfer, "
   		"aep, kep, zep, steigern_bool, steigern_ep_prozent,"
   		"grad_basiswerte, grad_abwehr, grad_resistenz,"
   		"grad_zaubern, steigertage, "
   		"abwehr_pp, zaubern_pp, resistenz_pp, "
   		"beschreibung, ruestung "
   	"from charaktere "
   	"where charakter_name='"+name+"' and version='"+version+"'");
   
   FetchIStream is=query1.Fetch();
   o <<	"<Midgard-Abenteurer Version=\"8\">\n";
   o << "  <Figur";
   fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_string_attrib(is, o, "Spieler");
   fetch_and_write_string_attrib(is, o, "Zeitpunkt");
   int grad=fetch_and_write_int_attrib(is, o, "Grad");
   o << "/>\n";
   o << "  <Typ";
   fetch_and_write_string_attrib(is, o, "Spezies");
   fetch_and_write_string_attrib(is, o, "Geschlecht");
   fetch_and_write_typ_attrib(is, o, "Abkürzung");
   fetch_and_write_typ_attrib(is, o, "Abkürzung2");
   fetch_and_write_string_attrib(is, o, "Spezialisierung");
   fetch_and_write_string_attrib(is, o, "Stadt_Land"); // ???
   o << "/>\n";
   o << "  <Basiseigenschaften";
   fetch_and_write_int_attrib(is, o, "St");
   fetch_and_write_int_attrib(is, o, "Gw");
   fetch_and_write_int_attrib(is, o, "Gs");
   fetch_and_write_int_attrib(is, o, "Ko");
   fetch_and_write_int_attrib(is, o, "In");
   fetch_and_write_int_attrib(is, o, "Zt");
   o << "/>\n";
   o << "  <abgeleiteteEigenschaften";
   fetch_and_write_int_attrib(is, o, "Au");
   fetch_and_write_int_attrib(is, o, "pA");
   fetch_and_write_int_attrib(is, o, "Wk");
   fetch_and_write_int_attrib(is, o, "Sb");
   fetch_and_write_int_attrib(is, o, "RW");
   fetch_and_write_int_attrib(is, o, "HGW");
   fetch_and_write_int_attrib(is, o, "B");
   fetch_and_write_int_attrib(is, o, "KAW");
   fetch_and_write_int_attrib(is, o, "WLW");
   fetch_and_write_int_attrib(is, o, "GG");
   fetch_and_write_int_attrib(is, o, "SG");
   o << "/>\n";
   o << "  <Erfolgswerte";
   fetch_and_write_int_attrib(is, o, "Abwehr");
   fetch_and_write_int_attrib(is, o, "Zaubern");
   o << "/>\n";
   o << "  <Resistenzen";
   fetch_and_write_int_attrib(is, o, "Zauber");
   o << "/>\n";
   o << "  <Gesundheit"; // schlechter Name ?
   fetch_and_write_int_attrib(is, o, "LP_Basis");
   fetch_and_write_int_attrib(is, o, "LP");
   fetch_and_write_int_attrib(is, o, "AP");
   o << "/>\n";
   o << "  <Beschreibung"; // soziale?
   fetch_and_write_int_attrib(is, o, "Alter");
   fetch_and_write_string_attrib(is, o, "Gestalt");
   fetch_and_write_int_attrib(is, o, "Gewicht");
   fetch_and_write_int_attrib(is, o, "Größe");
   fetch_and_write_string_attrib(is, o, "Stand");
   fetch_and_write_string_attrib(is, o, "Herkunft");
   fetch_and_write_string_attrib(is, o, "Glaube");
   o << "/>\n";
   o << "  <Boni"; 
   fetch_and_write_int_attrib(is, o, "Ausdauer");
   fetch_and_write_int_attrib(is, o, "Schaden");
   fetch_and_write_int_attrib(is, o, "Angriff");
   fetch_and_write_int_attrib(is, o, "Abwehr");
   fetch_and_write_int_attrib(is, o, "Zaubern");
   o << ">\n";
   o << "    <Resistenzen"; // Würde ich unter BONI fassen MAT
   fetch_and_write_int_attrib(is, o, "psy");
   fetch_and_write_int_attrib(is, o, "phs");
   fetch_and_write_int_attrib(is, o, "phk");
   fetch_and_write_int_attrib(is, o, "Gift");
   o << "/>\n";
   o << "  </Boni>\n"; 
   fetch_and_write_int(is, o, "GFP", 2);
   o << "  <Vermögen";
   fetch_and_write_int_attrib(is, o, "GS");
   fetch_and_write_int_attrib(is, o, "SS");
   fetch_and_write_int_attrib(is, o, "KS");
   o << "/>\n";
   o << "  <Steigern";
   fetch_and_write_int_attrib(is, o, "AEP");
   fetch_and_write_int_attrib(is, o, "KEP");
   fetch_and_write_int_attrib(is, o, "ZEP");
   fetch_and_write_bool_attrib(is, o, "EPabziehen", false);
   fetch_and_write_int_attrib(is, o, "EPproGFP", 50);
   fetch_and_write_int_attrib(is, o, "Basiswerte", grad);
   fetch_and_write_int_attrib(is, o, "Abwehr", grad);
   fetch_and_write_int_attrib(is, o, "Resistenz", grad);
   fetch_and_write_int_attrib(is, o, "Zaubern", grad);
   fetch_and_write_int_attrib(is, o, "benötigte_Tage");
   o << "><Praxispunkte";
   fetch_and_write_int_attrib(is, o, "Abwehr");
   fetch_and_write_int_attrib(is, o, "Zaubern");
   fetch_and_write_int_attrib(is, o, "Resistenz");
   o << "/></Steigern>\n";
   fetch_and_write_string(is, o, "Text", 2);
   
   o << "  <Ausrüstung>\n"; // oder Besitz?
   fetch_and_write_string(is, o, "Rüstung", 4);
  {Query query2("select fertigkeit, av_bonus, sl_bonus, region, magisch "
   	"from charaktere_fertigkeiten "
   	"where charakter_name='"+name+"' and version='"+version+"' "
   	"and art='Besitz_W' "
   	"order by fertigkeit");
   FetchIStream is2;
   while ((query2>>is2).good())
   {  std::string typ;
      o << "    <Waffe";
      fetch_and_write_string_attrib(is2, o, "Bezeichnung");
      fetch_and_write_int_attrib(is2, o, "AngriffVerteidigung_Bonus");
      fetch_and_write_int_attrib(is2, o, "SchadenLebenspunkte_Bonus");
      fetch_and_write_string_attrib(is2, o, "Region");
      {  std::string magisch;
         
         is2 >> FetchIStream::MapNull<string>(magisch,"");
         if (!magisch.size()) o << "/>\n";
         else o << '>' << magisch << "</Waffe>\n";
      }
   }
  }
  {Query query2("select av_bonus, fertigkeit, region, magisch, wert, sl_bonus "
   	"from charaktere_fertigkeiten "
   	"where charakter_name='"+name+"' and version='"+version+"' "
   	"and art='Ausruestung' "
   	"order by sl_bonus");
   FetchIStream is2;
   list<int> parent_list;
//   parent_list.push_back(0);
   int last_id=0;
   while ((query2>>is2).good())
   {  int parent_id=fetch_int(is2);
      if (last_id && parent_id==last_id)
      {  o << ">\n";
         parent_list.push_back(parent_id);
      }
      else 
      {  if (last_id) o << "/>\n"; // close last 
         while (parent_list.back()!=parent_id && !parent_list.empty())
         {  parent_list.pop_back();
            o << string(4+parent_list.size()*2,' ') << "</Gegenstand>\n";
         }
      }
      o << string(4+parent_list.size()*2,' ') << "<Gegenstand";
      fetch_and_write_string_attrib(is2, o, "Bezeichnung");
      fetch_and_write_string_attrib(is2, o, "Region");
      fetch_and_write_string_attrib(is2, o, "Besonderheit");
      if (fetch_int(is2)) write_bool_attrib(o, "sichtbar", true);
      last_id=fetch_int(is2);
   }
   if (last_id) o << "/>\n"; // close last 
   while (!parent_list.empty())
   {  parent_list.pop_back();
      o << string(4+parent_list.size()*2,' ') << "</Gegenstand>\n";
   }
  }
   o << "  </Ausrüstung>\n";
   
   o << "  <Fertigkeiten>\n";   
  {Query query2("select art, fertigkeit, wert, region, av_bonus, magisch, zauberwerk_stufe "
   	"from charaktere_fertigkeiten "
   	"where charakter_name='"+name+"' and version='"+version+"' "
   	"and art!='Besitz_W' and art!='Ausrüstung' and art!='Ausruestung' "
   	"order by art, fertigkeit");
   FetchIStream is2;
   while ((query2>>is2).good())
   {  std::string typ;
      is2 >> typ;
      // oder <Beruf Wert=12>Arzt</Beruf> ?
      o << "    <"<<typ;
      if (typ!="Region") fetch_and_write_string_attrib(is2, o, "Bezeichnung");
      else { std::string dummy; is2 >> dummy; }
      fetch_and_write_int_attrib(is2, o, "Wert");
      // dies ist wahrscheinlich unnötig ...
      fetch_and_write_string_attrib(is2, o, "Region");
      fetch_and_write_int_attrib(is2, o, "Praxispunkte");
      fetch_and_write_string_attrib(is2, o, "Art"); // Zauberwerk
      fetch_and_write_string_attrib(is2, o, "Stufe"); // Zauberwerk
      o << "/>\n";
   }
   o << "  </Fertigkeiten>\n";   
  }
   
   o << "</Midgard-Abenteurer>\n";
}

int main(int argc, char *argv[])
{  
   if (argc>3 && argc<1) {std::cerr << "USAGE: "<<argv[0]<<" ['Abenteurername'|'Mus%er'] ['Version']\n";
      exit(1); };
   try{
      Petig::Connection conn;
      conn.setDbase("midgard");
      Petig::dbconnect(conn);

   std::cout << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n\n";
   std::cout << "<MidgardCG-data>\n";
  {Transaction tr;
   if (argc==3) charakter_speichern(std::cout,argv[1],argv[2]);
   else if (argc==2)
   {  
//      Transaction tr;
      Query query0("select charakter_name, version "
   	"from charaktere "
   	"where charakter_name like '"+std::string(argv[1])+"' "
   	"order by charakter_name, version");
      FetchIStream is;
      while ((query0>>is).good())
      {  string charakter,version;
         is >> charakter >> version;
         charakter_speichern(std::cout,charakter,version);
      }
   }
   else // argc==1
   {  //Transaction tr;
      Query query0("select charakter_name, version "
   	"from charaktere "
   	"order by charakter_name, version");
      FetchIStream is;
      while ((query0>>is).good())
      {  string charakter,version;
         is >> charakter >> version;
         charakter_speichern(std::cout,charakter,version);
      }
   }
   std::cout << "</MidgardCG-data>\n";
  }
   Petig::dbdisconnect();
   } catch (SQLerror &e)
   {  std::cerr << e << '\n';
   }
   return 0;
}
