// $Id: common_exp.cc,v 1.19 2002/02/06 11:37:48 thoma Exp $
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

#include "export_common.h"
#include <Aux/Transaction.h>

static void schwierigkeit(std::ostream &o, 
	const std::string &_query, const std::string &tag, int indent=4)
{  std::string content;
   int in_this_line=0;
   int per_line=3;
   if (tag=="Grund") per_line=4;

   Query query(_query);
   FetchIStream is;
   while ((query>>is).good())
   {  if (++in_this_line>per_line) 
      { content+="\n"+string(indent,' '); in_this_line=1; }
      content+="<"+tag+" Typ=\""+toXML(fetch_typ(is))+"\"/>";
   }
   if (!content.empty())
      o << string(indent,' ') << content << '\n';
}

void grund_standard_ausnahme(std::ostream &o, 
	const std::string &table, const std::string &name,
	const std::string &condition, bool nur_region)
{  std::string query0="select typ from "+table+" where name='"+name
   	+"' and standard='";
   std::string query1="'";
   if (!condition.empty()) query1+=" and "+condition;
#ifdef REGION   
   if (nur_region || region.empty())
   {  query1+=" and exists (select true from typen where typ=typs and coalesce(region,'')='"
   	+region+"') ";
   }
#endif   
   query1+=" order by typ";
   schwierigkeit(o,query0+"G"+query1, "Grund");
   schwierigkeit(o,query0+"S"+query1, "Standard");
   schwierigkeit(o,query0+"A"+query1, "Ausnahme");
}

void lernschema(std::ostream &o, const std::string &art, const std::string &name, bool nur_region)
{  
   std::string constraint;

#ifdef REGION   
   if (nur_region || region.empty())
   {  constraint=" and exists (select true from typen where typ=typs and coalesce(region,'')='"
   	+region+"') ";
   }
#endif   
   
   Query query(
#ifdef MIDGARD3
	"select typ, lernpunkte, 0 as wert, pflicht, p_element, s_element"
	" from lernschema"
	" where fertigkeit='"+name+"' and art='"+art+"'"
	+constraint+
	" order by lernpunkte,typ"
#else
	"select typ, lernpunkte, wert, pflicht"
	" from lernschema_4"
	" where name='"+name+"' and art='"+art+"'"
	+constraint+
	" order by lernpunkte,wert,typ"
#endif
	);

   FetchIStream is;
   while ((query>>is).good())
   {  o << "    <Lernschema";
      fetch_and_write_typ_attrib(is, o, "Typ");
      fetch_and_write_int_attrib(is, o, "Lernpunkte");
      fetch_and_write_int_attrib(is, o, "Erfolgswert");
      fetch_and_write_bool_attrib(is, o, "Pflicht");
#ifdef MIDGARD3
      fetch_and_write_string_attrib(is, o, "Primärelement");
      fetch_and_write_string_attrib(is, o, "Sekundärelement");
#endif
      o << "/>\n";
   }
}

void ausnahmen(std::ostream &o, const std::string &art, const std::string &name, bool nur_region)
{  std::string constraint;
#ifdef REGION   
   if (nur_region || region.empty())
   {  constraint=" and (exists (select true from typen where typ=typs and coalesce(region,'')='"
   	+region+"') or herkunft"+Herkunft()+") ";
   }
#endif

   Query query("select spezies, herkunft, typ, beruf, stand, standard"
	" from ausnahmen where name='"+name+"' and art='"+art+"'"
	+constraint+
	" order by spezies,herkunft,typ,beruf,stand");
   FetchIStream is2;
   while ((query>>is2).good())
   {  o << "    <regionaleBesonderheit";
      fetch_and_write_string_attrib(is2, o, "Spezies");
      fetch_and_write_string_attrib(is2, o, "Herkunft");
      fetch_and_write_typ_attrib(is2, o, "Typ");
      fetch_and_write_string_attrib(is2, o, "Beruf");
      fetch_and_write_string_attrib(is2, o, "Stand");
      fetch_and_write_string_attrib(is2, o, "Standard");
      o << "/>\n";
   }
}

void pflicht_lernen(std::ostream &o, const std::string &name, bool nur_region)
{  std::string constraint;
  {if (nur_region || region.empty())
   {  constraint="and exists (select true from typen where typ=typs and coalesce(region,'')='"
   	+region+"')"; 
   }
   Query query("select typ,coalesce(lernpunkte,0),coalesce(erfolgswert,0)"
	" from pflicht_lernen"
	" where pflicht='"+name+"' "
	+constraint+
	" order by typ");
   FetchIStream is2;
   while ((query>>is2).good())
   {  o << "    <Lernschema";
      fetch_and_write_typ_attrib(is2, o, "Typ");
      fetch_and_write_int_attrib(is2,o,"Lernpunkte");
      fetch_and_write_int_attrib(is2,o,"Erfolgswert");
      write_bool_attrib(o,"Pflicht",true);
      o << "/>\n";
   }
  }
   if (region.empty()) // auch Spezies
   {  constraint=" and exists(select true from spezies where typ=spezies)";
   Query query("select typ,coalesce(lernpunkte,0),coalesce(erfolgswert,0)"
	" from pflicht_lernen"
	" where pflicht='"+name+"' "
	+constraint+
	" order by typ");
   FetchIStream is2;
   while ((query>>is2).good())
   {  o << "    <Lernschema";
      fetch_and_write_typ_attrib(is2, o, "Spezies");
      fetch_and_write_int_attrib(is2,o,"Lernpunkte");
      fetch_and_write_int_attrib(is2,o,"Erfolgswert");
      write_bool_attrib(o,"Pflicht",true);
      o << "/>\n";
   }
  }
}

void verbot_lernen(std::ostream &o, const std::string &name, bool nur_region)
{  std::string constraint;
  {if (nur_region || region.empty())
   {  constraint="and exists (select true from typen where typ=typs and coalesce(region,'')='"
   	+region+"')"; 
   }
   Query query("select typ,coalesce(spielbegin,'')"
	" from pflicht_lernen"
	" where verboten='"+name+"' "
	+constraint+
	" order by typ");
   FetchIStream is2;
   while ((query>>is2).good())
   {  o << "    <Verbot";
      fetch_and_write_typ_attrib(is2, o, "Typ");
      std::string spielbeg=fetch_string(is2);
      write_bool_attrib(o,"Spielbeginn",!spielbeg.empty());
      o << "/>\n";
   }
  }
   
   if (region.empty()) // auch Spezies
   {  constraint=" and exists(select true from spezies where typ=spezies)";
   Query query("select typ,coalesce(spielbegin,'')"
	" from pflicht_lernen"
	" where verboten='"+name+"' "
	+constraint+
	" order by typ");
   FetchIStream is2;
   while ((query>>is2).good())
   {  o << "    <Verbot";
      fetch_and_write_typ_attrib(is2, o, "Spezies");
      std::string spielbeg=fetch_string(is2);
      write_bool_attrib(o,"Spielbeginn",!spielbeg.empty());
      o << "/>\n";
   }
  }
}

#ifdef REGION
std::string Herkunft(bool invert)
{  std::string herkunft;
   if (region=="A") herkunft="='Alba'";
   else if (region=="E") herkunft="='Eschar'";
   else if (region=="K") herkunft="='KanThaiPan'";
   else if (region=="R") herkunft=" in ('Minangpahit','Rawindra')";
   else if (region.empty()) herkunft=" in ('Küstenstaaten','Ikenga Becken')";
   else herkunft="='never'";
   if (invert)
   {  if (herkunft[0]=='=') return "!"+herkunft;
      if (herkunft[0]=='i') return " not"+herkunft;
   }
   return herkunft;
}

std::string RegionErgaenzungQuery(const std::string &attribute, 
	const std::string &typtable, const std::string &lernsch_art,
	const std::string &ausnahmen_art)
{  std::string result;
   std::string herkunft=Herkunft();

   result="where coalesce(region,'')!='"+region+"' and (";
   
   result+="exists (select true from "+typtable+" join typen"
   	" on typ=typs where region='"+region+"'"
   	" and "+attribute+"="+typtable+".name) ";
   
   if (typtable!="waffen_grund_typen")
      result+="or exists (select true from "
   	MIDGARD3_4("lernschema","lernschema_4")
   	" join typen"
   	" on typ=typs where region='"+region+"'"
   	" and art='"+lernsch_art+"'"
   	" and "+attribute+"="
   	MIDGARD3_4("lernschema.fertigkeit","lernschema_4.name")
   	") ";
   	
   if (typtable!="waffen_grund_typen")
      result+="or exists (select true from pflicht_lernen join typen"
   	" on typ=typs where region='"+region+"'"
   	" and ("+attribute+"=pflicht_lernen.verboten"
   	" or "+attribute+"=pflicht_lernen.pflicht)) ";

   if (typtable!="waffen_grund_typen")
      result+="or exists (select true from ausnahmen join typen"
   	" on typ=typs"
   	" where (region='"+region+"' or herkunft"+herkunft+")"
   	" and art='"+ausnahmen_art+"'"
   	" and "+attribute+"=ausnahmen.name) ";
   	
   if (attribute=="waffen.name")
      result+="or exists (select true from waffen_region_name"
   	" where region='"+region+"'"
   	" and "+attribute+"=waffen_region_name.name) ";
   	
   result+=") ";
   	
   return result;
}

void region_tags(std::ostream &os, const string &region)
{  Transaction tr;
   write_string_attrib(std::cout,"Region",region);
   Query query("select name, copyright, jahr, offiziell, file, url, maintainer,"
   	" version, nr, pic"
	" from regionen where abkuerzung='"+region+"'");
   FetchIStream is=query.Fetch();
   if (query.good())
   {  fetch_and_write_string_attrib(is, std::cout, "Name");
      fetch_and_write_string_attrib(is, std::cout, "Copyright");
      fetch_and_write_string_attrib(is, std::cout, "Jahr");
      fetch_and_write_bool_attrib(is, std::cout, "offiziell");
      fetch_and_write_string_attrib(is, std::cout, "Dateiname");
      fetch_and_write_string_attrib(is, std::cout, "URL");
      fetch_and_write_string_attrib(is, std::cout, "Maintainer");
      fetch_and_write_string_attrib(is, std::cout, "Version");
      fetch_and_write_int_attrib(is, std::cout, "MAGUS-Index");
      fetch_and_write_int_attrib(is, std::cout, "MAGUS-Bild");
   }
}

void kaufpreis(std::ostream &o, const string &art, const string &name)
//***** preise ******
{  Query query2("select art2, kosten, einheit, gewicht"
   		" from preise where name='"+name+"' and art='"+art+"'");
   FetchIStream is2=query2.Fetch();
   if (is2.good())
   {  o << "    <Kaufpreis";
      fetch_and_write_string_attrib(is2, o, "Art2");
      fetch_and_write_float_attrib(is2, o, "Preis");
      fetch_and_write_string_attrib(is2, o, "Währung");
      fetch_and_write_float_attrib(is2, o, "Gewicht");
      o << "/>\n";
   }
}   

#endif
