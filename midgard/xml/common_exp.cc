// $Id: common_exp.cc,v 1.5 2001/12/12 10:30:01 christof Exp $
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

static void schwierigkeit(ostream &o, 
	const std::string &_query, const std::string &tag)
{  std::string content;
   Query query(_query);
   FetchIStream is;
   while ((query>>is).good())
   {  std::string typ;
      if (!content.empty()) content+=',';
      is>>typ;
      content+=typ_standardisierung(typ);
   }
   if (!content.empty())
      o << "    <"<<tag<<">" << content << "</"<<tag<<">\n";
}

void grund_standard_ausnahme(ostream &o, 
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

void lernschema(ostream &o, const std::string &art, const std::string &name, bool nur_region)
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
	"select typ, 0 as lernpunkte, wert, pflicht"
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

void ausnahmen(ostream &o, const std::string &art, const std::string &name, bool nur_region)
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

#warning FIXME Region
void pflicht_lernen(ostream &o, const std::string &name)
{  Query query("select typ,coalesce(lernpunkte,0),coalesce(erfolgswert,0)"
	" from pflicht_lernen"
	" where pflicht='"+name+"' order by typ");
   FetchIStream is2;
   while ((query>>is2).good())
   {  o << "    <Lernschema";
      fetch_and_write_typ_attrib(is2, o, "Typ");
      fetch_and_write_int_attrib(is2,o,"Lernpunkte");
      fetch_and_write_int_attrib(is2,o,"Anfangswert");
      write_bool_attrib(o,"Pflicht",true);
      o << "/>\n";
   }
}

#warning FIXME Region
void verbot_lernen(ostream &o, const std::string &name)
{  Query query("select typ,coalesce(spielbegin,'')"
	" from pflicht_lernen"
	" where verboten='"+name+"' order by typ");
   FetchIStream is2;
   while ((query>>is2).good())
   {  o << "    <Verbot";
      fetch_and_write_typ_attrib(is2, o, "Typ");
      std::string spielbeg=fetch_string(is2);
      write_bool_attrib(o,"Spielbeginn",!spielbeg.empty());
      o << "/>\n";
   }
}

#ifdef REGION
std::string Herkunft(bool invert)
{  std::string herkunft;
   if (region=="A") herkunft="='Alba'";
   else if (region=="E") herkunft="='Eschar'";
   else if (region=="K") herkunft="='KanThaiPan'";
   else if (region=="R") herkunft=" in ('Minangpahit','Rawindra')";
   else if (region=="") herkunft=" in ('Küstenstaaten','Ikenga Becken')";
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
   
   result+="or exists (select true from lernschema join typen"
   	" on typ=typs where region='"+region+"'"
   	" and art='"+lernsch_art+"'"
   	" and "+attribute+"=lernschema.fertigkeit) ";
   	
   	// pflicht_lernen lasse ich mal außen vor ??
   	
   result+="or exists (select true from ausnahmen join typen"
   	" on typ=typs"
   	" where (region='"+region+"' or herkunft"+herkunft+")"
   	" and art='"+ausnahmen_art+"'"
   	" and "+attribute+"=ausnahmen.name) ";
   	
   result+=") ";
   	
   return result;
}
#endif
