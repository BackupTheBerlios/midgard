// $Id: common_exp.cc,v 1.27 2002/06/13 06:28:58 christof Exp $
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

static void schwierigkeit(Tag &o, 
	const std::string &_query, const std::string &tag)
{  Query query(_query);
   FetchIStream is;
   while ((query>>is).good())
   {  o.push_back(Tag(tag)).setAttr("Typ",fetch_string(is));
   }
}

void grund_standard_ausnahme(Tag &o, 
	const std::string &table, const std::string &name,
	const std::string &condition, bool nur_region)
{  std::string query0="select typ from "+table+" where name='"+name
   	+"' and standard='";
   std::string query1="'";
   if (!condition.empty()) query1+=" and "+condition;
   if (nur_region || region.empty())
   {  query1+=" and exists (select true from typen where typ=typs and coalesce(region,'')='"
   	+region+"') ";
   }
   query1+=" order by typ";
   schwierigkeit(o,query0+"G"+query1, "Grund");
   schwierigkeit(o,query0+"S"+query1, "Standard");
   schwierigkeit(o,query0+"A"+query1, "Ausnahme");
   schwierigkeit(o,query0+"-"+query1, "Nicht");
}

void lernschema(Tag &o, const std::string &art, const std::string &name, bool nur_region)
{  
   std::string constraint;

   if (nur_region || region.empty())
   {  constraint=" and exists (select true from typen where typ=typs and coalesce(region,'')='"
   	+region+"') ";
   }
   
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
   {  Tag &ls=o.push_back(Tag("Lernschema"));
      fetch_and_set_string_attrib(is, ls, "Typ");
      fetch_and_set_int_attrib(is, ls, "Lernpunkte");
      fetch_and_set_int_attrib(is, ls, "Erfolgswert");
      fetch_and_set_bool_attrib(is, ls, "Pflicht");
#ifdef MIDGARD3
      fetch_and_set_string_attrib(is, ls, "Primärelement");
      fetch_and_set_string_attrib(is, ls, "Sekundärelement");
#endif
   }
}

void ausnahmen(Tag &o, const std::string &art, const std::string &name, bool nur_region)
{  std::string constraint;
   if (nur_region || region.empty())
   {  constraint=" and (exists (select true from typen where typ=typs and coalesce(region,'')='"
   	+region+"') or herkunft"+Herkunft()+") ";
   }

   Query query("select spezies, herkunft, typ, beruf, stand, standard"
	" from ausnahmen where name='"+name+"' and art='"+art+"'"
	+constraint+
	" order by spezies,herkunft,typ,beruf,stand");
   FetchIStream is2;
   while ((query>>is2).good())
   {  Tag &rb=o.push_back(Tag("regionaleBesonderheit"));
      fetch_and_set_string_attrib(is2, rb, "Spezies");
      fetch_and_set_string_attrib(is2, rb, "Herkunft");
      fetch_and_set_string_attrib(is2, rb, "Typ");
      fetch_and_set_string_attrib(is2, rb, "Beruf");
      fetch_and_set_string_attrib(is2, rb, "Stand");
      fetch_and_set_string_attrib(is2, rb, "Standard");
   }
}

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
   	
/*
   if (typtable!="waffen_grund_typen")
      result+="or exists (select true from pflicht_lernen join typen"
   	" on typ=typs where region='"+region+"'"
   	" and ("+attribute+"=pflicht_lernen.verboten"
   	" or "+attribute+"=pflicht_lernen.pflicht)) ";
*/

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

void region_tags(Tag &t, const string &region)
{  Transaction tr;
   t.setAttr_ne("Region",region);
   Query query("select name, titel, copyright, jahr, offiziell, file, url, maintainer,"
   	" version, nr, pic"
	" from regionen where abkuerzung='"+region+"'");
   FetchIStream is=query.Fetch();
   if (query.good())
   {  fetch_and_set_string_attrib(is, t, "Name");
      fetch_and_set_string_attrib(is, t, "Titel");
      fetch_and_set_string_attrib(is, t, "Copyright");
      fetch_and_set_string_attrib(is, t, "Jahr");
      fetch_and_set_bool_attrib(is, t, "offiziell");
      fetch_and_set_string_attrib(is, t, "Dateiname");
      fetch_and_set_string_attrib(is, t, "URL");
      fetch_and_set_string_attrib(is, t, "Maintainer");
      fetch_and_set_string_attrib(is, t, "Version");
      fetch_and_set_int_attrib(is, t, "MAGUS-Index");
      fetch_and_set_int_attrib(is, t, "MAGUS-Bild");
   }
}

void kaufpreis(Tag &o, const string &art, const string &name)
//***** preise ******
{  Query query2("select art2, kosten, einheit, gewicht"
   		" from preise where name='"+name+"' and art='"+art+"'");
   FetchIStream is2=query2.Fetch();
   if (is2.good())
   {  Tag &kp=o.push_back(Tag("Kaufpreis"));
      fetch_and_set_string_attrib(is2, kp, "Art2");
      fetch_and_set_float_attrib(is2, kp, "Preis");
      fetch_and_set_string_attrib(is2, kp, "Währung");
      fetch_and_set_float_attrib(is2, kp, "Gewicht");
   }
}   

