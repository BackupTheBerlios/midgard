// $Id: land_sprache_exp.cc,v 1.30 2002/03/15 07:08:41 thoma Exp $
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

  if (region.empty())
  {o << " <Länder>\n";
  {Query query("select distinct kontinent from land"
   	" order by kontinent");
  while ((query>>is).good())
  {o << "  <Kontinent";
   string kontinent=fetch_and_write_string_attrib(is, o, "Name");
   o << ">\n";
   Query query2("select distinct land from land"
   	" where kontinent='"+kontinent+"'"
   	" order by land");
   FetchIStream is2;
   while ((query2>>is2).good())
   {o << "    <Land";
    string land=fetch_and_write_string_attrib(is2, o, "Name");
    o << ">\n";
    Query query3("select sprache from land"
   	" where kontinent='"+kontinent+"'"
   	" and land='"+land+"'"
   	" order by sprache");
    FetchIStream is3;
    while ((query3>>is3).good())
    { o << "      <Sprache";
      fetch_and_write_string_attrib(is3, o, "Name");
      o << "/>\n";
    }
    o << "    </Land>\n";
   }
   o << "  </Kontinent>\n";
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
   string schrift=fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_string_attrib(is, o, "Region");
   fetch_and_write_string_attrib(is, o, "Typ");
   fetch_and_write_int_attrib(is, o, "Kosten");
   fetch_and_write_bool_attrib(is, o, "alte_Schrift");
   fetch_and_write_bool_attrib(is, o, "Kultschrift");
   o << ">\n";
   Query query2("select schrift from sprache_schrift"
   	" where art_der_schrift="+toSQL(schrift)+" order by schrift");
   FetchIStream is2;
   while ((query2>>is2).good())
   {  o << "    <Variante";
      fetch_and_write_string_attrib(is2, o, "Name");
      o << "/>\n";
   }
   o << "  </Schrift>\n";
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
   Query query2("select schrift from sprache_schrift"
   	" where sprache="+toSQL(sprache)+" order by schrift");
   FetchIStream is2;
   while ((query2>>is2).good())
   {  o << "\n    <Schrift";
      fetch_and_write_string_attrib(is2, o, "Name", sprache);
      o << "/>";
   }
   o << "</Sprache>\n";
  }
  }
   o << " </Sprachen>\n";

//******************************************************************
  if (region.empty())
  {o << " <SpeziesListe>\n";
   Query query("select spezies, nr, only_nsc, land, hand_bonus, raufen,alter_fak, "
         " groesse_wanz, groesse_wuerfel, groesse_bonus, gewicht_wanz, gewicht_bonus, "
         " b_wanz, b_bonus, lp, ap_bonus, ap_grad_fak, "
         " psy, psy100, phs, phs100, phk, phk100, "
   		" st,gs,gw,ko,\"in\",zt,sb,au "
      	" from spezies"
      	" order by spezies");
  while ((query>>is).good())
  {o << "  <Spezies";
   std::string name=fetch_and_write_string_attrib(is, o, "Name");
   fetch_and_write_int_attrib(is, o, "MAGUS-Index");
   fetch_and_write_bool_attrib(is, o, "only_NSC");
   fetch_and_write_bool_attrib(is, o, "Land");
   fetch_and_write_int_attrib(is, o, "HandBonus");
   fetch_and_write_int_attrib(is, o, "RaufenBonus");
   o << ">\n";
   o << "    <Alter";
   fetch_and_write_int_attrib(is, o, "Faktor");
   o << "/>\n";
   o << "    <Größe";
   fetch_and_write_int_attrib(is, o, "AnzahlWürfel");
   fetch_and_write_int_attrib(is, o, "Würfel");
   fetch_and_write_int_attrib(is, o, "Addiere");
   o << "/>\n";
   o << "    <Gewicht";
   fetch_and_write_int_attrib(is, o, "AnzahlWürfel");
   fetch_and_write_int_attrib(is, o, "Addiere");
   o << "/>\n";
   o << "    <Bewegungsweite";
   fetch_and_write_int_attrib(is, o, "AnzahlWürfel");
   fetch_and_write_int_attrib(is, o, "Addiere");
   o << "/>\n";
   o << "    <Modifikation";
   fetch_and_write_int_attrib(is, o, "LP_Bonus");
   fetch_and_write_int_attrib(is, o, "AP_Bonus");
   fetch_and_write_int_attrib(is, o, "AP_GradFaktor");
   o << ">\n       <Resistenzen";
   fetch_and_write_int_attrib(is, o, "psy");
   fetch_and_write_int_attrib(is, o, "psy100");
   fetch_and_write_int_attrib(is, o, "phs");
   fetch_and_write_int_attrib(is, o, "phs100");
   fetch_and_write_int_attrib(is, o, "phk");
   fetch_and_write_int_attrib(is, o, "phk100");
   o << "/>\n       <Grundwerte";
   fetch_and_write_int_attrib(is, o, "St");
   fetch_and_write_int_attrib(is, o, "Gs");
   fetch_and_write_int_attrib(is, o, "Gw");
   fetch_and_write_int_attrib(is, o, "Ko");
   fetch_and_write_int_attrib(is, o, "In");
   fetch_and_write_int_attrib(is, o, "Zt");
   fetch_and_write_int_attrib(is, o, "Sb");
   fetch_and_write_int_attrib(is, o, "Au");
   o << "/>\n    </Modifikation>\n";
   {  Query query2("select typen,maxgrad from spezies_typen"
      	" where spezies='"+name+"'"
      	" order by spezies,typen");
      FetchIStream is2;
      std::string typen;
      while ((query2>>is2).good()) 
      {  o << "    <Typ";
         fetch_and_write_string_attrib(is2, o, "Name");
         fetch_and_write_int_attrib(is2, o, "MaximalerGrad");
         o << "/>\n";
      }
   }
   {  Query query3("select art,name,erfolgswert,lp from spezies_angeborene_fert"
      	" where spezies='"+name+"'");
      FetchIStream is3;
      std::string typen;
      while ((query3>>is3).good()) 
      {  o << "    <AngeboreneFerigkeit";
         fetch_and_write_string_attrib(is3, o, "Art");
         fetch_and_write_string_attrib(is3, o, "Name");
         fetch_and_write_int_attrib(is3, o, "Erfolgswert");
         fetch_and_write_int_attrib(is3, o, "LP");
         o << "/>\n";
      }
   }
   o << "  </Spezies>\n";
  }
   o << " </SpeziesListe>\n";
  }

//******************************************************************
  if (region.empty())
  {o << " <Gradanstieg>\n";
   Query query("select grad, gfp, abwehr, resistenz, zaubern, schicksalsgunst,"
   	" ap_kosten, abwehr_kosten, resistenz_kosten, zaubern_kosten"
   	" from grad_anstieg"
   	" order by grad");
  while ((query>>is).good())
  {o << "  <Grad";
   fetch_and_write_int_attrib(is, o, "Grad");
   fetch_and_write_int_attrib(is, o, "GFP");
   fetch_and_write_int_attrib(is, o, "Abwehr");
   fetch_and_write_int_attrib(is, o, "Resistenz");
   fetch_and_write_int_attrib(is, o, "Zaubern");
   fetch_and_write_int_attrib(is, o, "Schicksalsgunst");
   o << "><Kosten";
   fetch_and_write_int_attrib(is, o, "Ausdauer");
   fetch_and_write_int_attrib(is, o, "Abwehr");
   fetch_and_write_int_attrib(is, o, "Resistenz");
   fetch_and_write_int_attrib(is, o, "Zaubern");
   o << "/></Grad>\n";
  }
   o << " </Gradanstieg>\n";
 }

//********************** typen ****************************************
   o << " <Typen>\n";
  {Query query("select typs, region, typnr, typl, typlw, "
  		"typz, sprueche_mit_pp, nsc_only, beruf, "
  		"stadt_land, ausdauer, stand, sb, ruestung, geld "
   	" from typen"
   	" where coalesce(region,'')='"+region+"'"
   	" order by typnr,coalesce(region,''),typs");
  while ((query>>is).good())
  {o << "  <Typ";
   fetch_and_write_typ_attrib(is, o, "Abkürzung");
   fetch_and_write_string_attrib(is, o, "Region");
   fetch_and_write_int_attrib(is, o, "MAGUS-Index");
   fetch_and_write_string_attrib(is, o, "Bezeichnung-Mann");
   fetch_and_write_string_attrib(is, o, "Bezeichnung-Frau");
   o << "\n       ";
   char zauberer=fetch_string(is,"n")[0];
   write_bool_attrib(o, "Zauberer",zauberer=='z');
   write_bool_attrib(o, "kannZaubern",zauberer=='z'||zauberer=='j');
   fetch_and_write_bool_attrib(is, o, "SprücheMitPraxisPunkten");
   fetch_and_write_bool_attrib(is, o, "NSC_only");
   fetch_and_write_string_attrib(is, o, "Berufswahl");
   string stadt_land=fetch_string(is);
   if (stadt_land=="s") write_bool_attrib(o, "Land", false, true);
   else if (stadt_land=="l") write_bool_attrib(o, "Stadt", false, true);
   fetch_and_write_string_attrib(is, o, "Ausdauer");
   o << ">\n    <Modifikation";
   fetch_and_write_int_attrib(is, o, "Stand");
   fetch_and_write_int_attrib(is, o, "Sb");
   fetch_and_write_int_attrib(is, o, "Rüstung");
   fetch_and_write_int_attrib(is, o, "Geld");
   o << "/></Typ>\n";
  }
  }
   o << " </Typen>\n";
   
// ******************** preise ***********************
  
  if (region.empty())
  {o << " <Preise>\n";
  {Query query("select name, art, art2, kosten, einheit"MIDGARD3_4("",",gewicht")
   	" from preise"
   	" where not exists (select true from waffen"
   		" where waffen.name=preise.name)"
   	" and not exists (select true from ruestung"
   		" where ruestung.ruestung=preise.name)"
   	" order by art,art2,name");
  while ((query>>is).good())
  {o << "  <Kaufpreis";
   fetch_and_write_string_attrib(is, o, "Ware");
   fetch_and_write_string_attrib(is, o, "Art");
   fetch_and_write_string_attrib(is, o, "Art2");
   fetch_and_write_float_attrib(is, o, "Preis");
   fetch_and_write_string_attrib(is, o, "Währung");
#ifndef MIDGARD3   
   fetch_and_write_float_attrib(is, o, "Gewicht");
#endif
   o << "/>\n";
  }
  }

  {Query query("select name, art, art2, faktor, typ, nr" 
  		// min, einheit?
   	" from preise_modifikation"
   	" order by art,art2,typ,name");
  while ((query>>is).good())
  {o << "  <Modifikation";
   fetch_and_write_string_attrib(is, o, "Bezeichnung");
   fetch_and_write_string_attrib(is, o, "Art");
   fetch_and_write_string_attrib(is, o, "Art2");
   fetch_and_write_float_attrib(is, o, "Faktor");
//   fetch_and_write_int_attrib(is, o, "Mindestpreis");
//   fetch_and_write_string_attrib(is, o, "Einheit");
   fetch_and_write_string_attrib(is, o, "Typ");
   fetch_and_write_int_attrib(is, o, "MAGUS-Nr");
   o << "/>\n";
  }
   o << " </Preise>\n";
  }
  }

//******************************************************************
}

