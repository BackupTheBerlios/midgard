// $Id: waffen_exp.cc,v 1.22 2002/06/08 16:25:24 christof Exp $
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

#include <fstream>
#include <Aux/Transaction.h>
#include <Aux/dbconnect.h>
#include "export_common.h"
#include <Aux/itos.h>

void waffen_speichern(Tag &o)
{  
   Tag &Ruestungen=o.push_back(Tag("Rüstungen"));

   Transaction t;
   FetchIStream is;
  {Query query("select ruestung, region, ruestung_s, lp_verlust,"
   		" min_staerke,rw_verlust,b_verlust, abwehr_bonus_verlust,"
   		" angriffs_bonus_verlust, vollruestung"
   	" from ruestung"
   	" where coalesce(region,'')='"+region+"'"
   	" order by coalesce(region,''),lp_verlust");
  while ((query>>is).good())
  {Tag &Ruestung=Ruestungen.push_back(Tag("Rüstung"));
   std::string ruestung=fetch_and_set_string_attrib(is, Ruestung, "Name");
   fetch_and_set_string_attrib(is, Ruestung, "Region");
   fetch_and_set_string_attrib(is, Ruestung, "Abkürzung");
   fetch_and_set_int_attrib(is, Ruestung, "schütztLP");
   fetch_and_set_int_attrib(is, Ruestung, "minimaleStärke");
   Tag &Verlust=Ruestung.push_back(Tag("Verlust"));
   fetch_and_set_int_attrib(is, Verlust, "RW");
   fetch_and_set_int_attrib(is, Verlust, "B");
   fetch_and_set_int_attrib(is, Verlust, "Abwehrbonus");
   fetch_and_set_int_attrib(is, Verlust, "Angriffsbonus");
   fetch_and_set_int_attrib(is, Verlust, "Vollrüstung");
   kaufpreis(Ruestung, "Rüstungen", ruestung);
  }
  }

//********************** waffen ********************************************

   Tag &Waffen=o.push_back(Tag("Waffen"));
  {Query query("select name, region, grundkenntnisse, schwierigkeit,"
   		"art, art_2, schaden, schaden_b, zusatz, "
   		MIDGARD3_4("angriffsrangmod,","waffenrang,")
   		"wm_abwehr_leicht, wm_abwehr_schwer, st, "
   		MIDGARD3_4("ge,","gw,gs,")
   		" reichweite_0, reichweite_n,"
   		"reichweite_m, reichweite_f"
   		MIDGARD3_4("",",lern_land,lern_stadt")
   	" from waffen"
   	" where coalesce(region,'')='"+region+"'"
   	" order by coalesce(region,''),art,name");
  while ((query>>is).good())
  {Tag &Waffe=Waffen.push_back(Tag("Waffe"));
   std::string waffe=fetch_and_set_string_attrib(is, Waffe, "Name");
   fetch_and_set_string_attrib(is, Waffe, "Region");
   std::string grund=fetch_and_set_string_attrib(is, Waffe, "Grundkenntnisse");
   fetch_and_set_int_attrib(is, Waffe, "Schwierigkeit",-1);
   fetch_and_set_string_attrib(is, Waffe, "Kategorie");
   fetch_and_set_string_attrib(is, Waffe, "Klasse");
   fetch_and_set_string_attrib(is, Waffe, "Schaden");
   fetch_and_set_int_attrib(is, Waffe, "Schadensbonus");
   fetch_and_set_string_attrib(is, Waffe, "erfordert");
   Tag &Mod=Waffe.push_back(Tag("Modifikationen"));
#ifdef MIDGARD3   
   fetch_and_set_string_attrib(is, Mod, "Angriffsrang");
#else   
   fetch_and_set_string_attrib(is, Mod, "Waffenrang");
#endif
   fetch_and_set_string_attrib(is, Mod, "Abwehr-leicht");
   fetch_and_set_string_attrib(is, Mod, "Abwehr-schwer");
   Tag &Vor=Waffe.push_back(Tag("Voraussetzungen"));
   fetch_and_set_int_attrib(is, Vor, "St");
#ifdef MIDGARD3   
   fetch_and_set_int_attrib(is, Vor, "Ge");
#else
   fetch_and_set_int_attrib(is, Vor, "Gw");
   fetch_and_set_int_attrib(is, Vor, "Gs");
#endif   
   Tag &Rw=Waffe.push_back(Tag("Reichweite"));
   fetch_and_set_int_attrib(is, Rw, "null");
   fetch_and_set_int_attrib(is, Rw, "nah");
   fetch_and_set_int_attrib(is, Rw, "mittel");
   fetch_and_set_int_attrib(is, Rw, "fern");
#ifndef MIDGARD3
   Tag &Lk=Waffe.push_back(Tag("Lernkosten"));
   fetch_and_set_int_attrib(is, Lk, "Land");
   fetch_and_set_int_attrib(is, Lk, "Stadt");
#endif   

   //********** waffen_voraussetzungen *****************************
   {  Query queryV1("select voraussetzung from waffen_voraussetzung "
      " where name='"+waffe+"' and art='F' order by voraussetzung");
      FetchIStream isV1;
      while ((queryV1>>isV1).good())   
      {  Waffe.push_back(Tag("Voraussetzungen_F")).setAttr("Name",fetch_string(isV1));
      }
      Query queryV2("select voraussetzung from waffen_voraussetzung "
      " where name='"+waffe+"' and art='W' order by voraussetzung");
      FetchIStream isV2;
      while ((queryV2>>isV2).good())   
      {  Waffe.push_back(Tag("Voraussetzungen_W")).setAttr("Name",fetch_string(isV2));
      }
    }

                                                             

 //************************* waffen_region_name ************************  
   {  Query query2("select r.alias,r.region,coalesce(r.schaden,w.schaden),"
         " coalesce(r.schaden_b,w.schaden_b),"
         " r.angriffs_mod"
      	" from waffen_region_name r join waffen w using (name) "
      	" where name='"+waffe+"'"
   	" and coalesce(r.region,'')='"+region+"'"
      	" order by r.region,r.alias");
      FetchIStream is2;
      while ((query2>>is2).good()) 
      {  Tag &Rv=Waffe.push_back(Tag("regionaleVariante"));
         std::string varian=fetch_and_set_string_attrib(is2, Rv, "Name");
         fetch_and_set_string_attrib(is2, Rv, "Region");
         fetch_and_set_string_attrib(is2, Rv, "Schaden");
         fetch_and_set_int_attrib(is2, Rv, "Schadensbonus");
         int agmod=fetch_int(is2);
         if (agmod) Rv.push_back(Tag("Modifikationen")).setIntAttr("Angriff",agmod);
         kaufpreis(Rv, "Waffen", varian);
      }
     }

//*************** Waffen Typen ***************************
      grund_standard_ausnahme(Waffe, "waffen_typen", waffe);

      //********** Lernschema **********************************
      // wert, attribut, [p+s]_element 
      lernschema(Waffe, MIDGARD3_4("Waffe","Waffenfertigkeiten"), waffe);
//      pflicht_lernen(Waffe, waffe);
//      verbot_lernen(Waffe, waffe);
//      ausnahmen(Waffe, "w", waffe);
      kaufpreis(Waffe, "Waffen", waffe);
  }
 }
  if (!region.empty())
  {FetchIStream is;
   Query q("select name, region from waffen "
   	+ RegionErgaenzungQuery("waffen.name","waffen_typen","Waffe","w")
   	+ "order by coalesce(region,''),name");
  while ((q >> is).good())
  {Tag &Waffe=Waffen.push_back(Tag("Waffe"));
   std::string waffe=fetch_and_set_string_attrib(is, Waffe, "Name");
   fetch_and_set_string_attrib(is, Waffe, "Region");

 //************************* waffen_region_name ************************  
   {  Query query2("select r.alias,r.region,coalesce(r.schaden,w.schaden),"
         " coalesce(r.schaden_b,w.schaden_b),"
         " r.angriffs_mod"
      	" from waffen_region_name r join waffen w using (name) "
      	" where name='"+waffe+"'"
   	" and coalesce(r.region,'')='"+region+"'"
      	" order by r.region,r.alias");
      FetchIStream is2;
      while ((query2>>is2).good()) 
      {  Tag &Rv=Waffe.push_back(Tag("regionaleVariante"));
         std::string varian=fetch_and_set_string_attrib(is2, Rv, "Name");
         fetch_and_set_string_attrib(is2, Rv, "Region");
         fetch_and_set_string_attrib(is2, Rv, "Schaden");
         fetch_and_set_int_attrib(is2, Rv, "Schadensbonus");
         int agmod=fetch_int(is2);
         if (agmod) Rv.push_back(Tag("Modifikationen")).setIntAttr("Angriff",agmod);
         kaufpreis(Rv, "Waffen", varian);
      }
     }

   grund_standard_ausnahme(Waffe, "waffen_typen",waffe,"",true);
   lernschema(Waffe, MIDGARD3_4("Waffe","Waffenfertigkeiten"), waffe,true);
   ausnahmen(Waffe, "w", waffe,true);
  }
  }

//******************waffen_grund************************************************

  Tag &WGke=o.push_back(Tag("Waffen-Grundkenntnisse"));
  {Query query("select name, region, fp from waffen_grund"
   	" where coalesce(region,'')='"+region+"'"
   	" order by name");
  while ((query>>is).good())
  {Tag &WGk=WGke.push_back(Tag("Waffen-Grundkenntnis"));
   std::string grund=fetch_and_set_string_attrib(is, WGk, "Name");
   fetch_and_set_string_attrib(is, WGk, "Region");
   fetch_and_set_int_attrib(is, WGk, "Kosten");
//*************** Waffen Grund Typen ***************************

   // nicht erforderlich für Grundkenntnisse?
      grund_standard_ausnahme(WGk, "waffen_grund_typen", grund);
  }

//*************** andere Regionen ***************************
   if (!region.empty())
   { FetchIStream is;
     Query q("select name, region from waffen_grund "
       	+ RegionErgaenzungQuery("waffen_grund.name","waffen_grund_typen","Waffengrund","g")
       	+ "order by coalesce(region,''),name");
      while ((q >> is).good())
      {Tag &WGk=WGke.push_back(Tag("Waffen-Grundkenntnis"));
       std::string grund=fetch_and_set_string_attrib(is, WGk, "Name");
       fetch_and_set_string_attrib(is, WGk, "Region");
       grund_standard_ausnahme(WGk, "waffen_grund_typen", grund, "", true);
      }
   }
  }

//********************* steigern_fertigkeiten_werte ********************
 if (region.empty())
 {Tag &WSt=o.push_back(Tag("Waffen-Steigern"));
  {Query query("select " MIDGARD3_4("name,","schwierigkeit,")
      	    "coalesce(p1,0), coalesce(p2,0), coalesce(p3,0),"
      	    "coalesce(p4,0), coalesce(p5,0), coalesce(p6,0), coalesce(p7,0),"
      	    "coalesce(p8,0), coalesce(p9,0), coalesce(p10,0), coalesce(p11,0),"
      	    "coalesce(p12,0), coalesce(p13,0), coalesce(p14,0), coalesce(p15,0),"
      	    "coalesce(p16,0), coalesce(p17,0), coalesce(p18,0), coalesce(p19,0),"
      	    "coalesce(p20,0)"
       		" from waffen_steigern"
       		" order by " MIDGARD3_4("name","schwierigkeit"));
    FetchIStream is;
       while ((query>>is).good())
       {  Tag &k=WSt.push_back(Tag("Kosten"));
#ifdef MIDGARD3
          fetch_and_set_string_attrib(is, k, "Kategorie");
#else
	  // 0 auch ausgeben!
          fetch_and_set_int_attrib(is, k, "Schwierigkeit",-1);
#endif
          for (int i=1;i<=20;++i) 
             fetch_and_set_int_attrib(is, k, "Wert"+itos(i));
       }
   }

//**************************** Waffen Typen ***************************
   grund_standard_ausnahme(WSt, "waffen_typen", "Waffen");
 }
//******************************************************************
}

