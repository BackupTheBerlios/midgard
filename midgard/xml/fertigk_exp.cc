// $Id: fertigk_exp.cc,v 1.37 2002/07/08 09:26:31 christof Exp $
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

#include <Misc/Transaction.h>
#include <Misc/dbconnect.h>
#include "export_common.h"
#include <Misc/itos.h>

void fert_speichern(Tag &o)
{  
   Transaction t;
   
   Tag &fertigkeiten=o.push_back(Tag("Fertigkeiten"));
  {Query query("select fertigkeit, region, region_zusatz, lp as lernpunkte, "
  	MIDGARD3_4("","lp_land, lp_stadt, ")
  	" anfangswert0, fp, anfangswert, "
  	MIDGARD3_4("","ungelernt, ")
  	" attribut"
  	MIDGARD3_4("",", berufsklasse, maxwert, maxunterweisung, zusaetze")
  	" from fertigkeiten left join steigern_fertigkeiten on name=fertigkeit"
  	" where coalesce(region,'')='"+region+"'"
  	" order by coalesce(region,''),coalesce(wie,fertigkeit)!=fertigkeit,fertigkeit");
   FetchIStream is;
  while ((query>>is).good())
  {Tag &fertigk=fertigkeiten.push_back(Tag("Fertigkeit"));
   std::string fert=fetch_and_set_string_attrib(is, fertigk, "Name");
   fetch_and_set_string_attrib(is, fertigk, "Region");
   fetch_and_set_string_attrib(is, fertigk, "RegionZusatz");
   fetch_and_set_int_attrib(is, fertigk, "Lernpunkte",99); // außergewöhnliche Fertigkeit
#ifndef MIDGARD3
   fetch_and_set_int_attrib(is, fertigk, "Lernpunkte-Land",99);
   fetch_and_set_int_attrib(is, fertigk, "Lernpunkte-Stadt",99);
#endif
   fetch_and_set_int_attrib(is, fertigk, "Anfangswert");
   fetch_and_set_int_attrib(is, fertigk, "Lernkosten");
   fetch_and_set_int_attrib(is, fertigk, "Erfolgswert");
#ifndef MIDGARD3
   fetch_and_set_int_attrib(is, fertigk, "Erfolgswert-ungelernt",-99);
#endif
   fetch_and_set_string_attrib(is, fertigk, "Attribut");
#ifndef MIDGARD3
   fetch_and_set_int_attrib(is, fertigk, "Berufskategorie");
   fetch_and_set_int_attrib(is, fertigk, "Maximalwert");
   fetch_and_set_int_attrib(is, fertigk, "MaximalMitUnterweisung");
   fetch_and_set_int_attrib(is, fertigk, "Zusätze");
#endif
   
   grund_standard_ausnahme(fertigk, "fertigkeiten_typen", fert);
      //********** fertigkeiten_voraussetzung **********************************
   {  Query query2("select st," MIDGARD3_4("ge,","gw,gs,")
   		"ko,\"in\",zt,au,pa,sb,rw, fertigkeit"
   	" from fertigkeiten_voraussetzung"
   	" where name='"+fert+"' order by fertigkeit");
      FetchIStream is2;
      while ((query2>>is2).good()) 
      {  Tag &v=fertigk.push_back(Tag("Voraussetzungen"));
         fetch_and_set_int_attrib(is2, v, "St");
#ifdef MIDGARD3
         fetch_and_set_int_attrib(is2, v, "Ge");
#else         
         fetch_and_set_int_attrib(is2, v, "Gw");
         fetch_and_set_int_attrib(is2, v, "Gs");
#endif
         fetch_and_set_int_attrib(is2, v, "Ko");
         fetch_and_set_int_attrib(is2, v, "In");
         fetch_and_set_int_attrib(is2, v, "Zt");
         fetch_and_set_int_attrib(is2, v, "Au");
         fetch_and_set_int_attrib(is2, v, "pA");
         fetch_and_set_int_attrib(is2, v, "Sb");
         fetch_and_set_int_attrib(is2, v, "RW");
         fetch_and_set_string_attrib(is2, v, "Fertigkeit");
      }
    }
      //********** fertigkeiten_voraussetzungen_2 **********************************
   {  Query queryV2("select voraussetzung from fertigkeiten_voraussetzungen_2 "
   	" where name='"+fert+"' order by voraussetzung");
      FetchIStream isV2;
      while ((queryV2>>isV2).good()) 
      {  fetch_and_set_string_attrib(isV2, fertigk.push_back(Tag("Voraussetzungen_2")), "Name");
      }
    }

      //********** fertigkeiten_zusätze **********************************
   {  Query queryZu("select name from fz_zusaetze "
   	" where art='"+fert+"' order by name");
      FetchIStream isZu;
      while ((queryZu>>isZu).good()) 
      {  fetch_and_set_string_attrib(isZu, fertigk.push_back(Tag("Zusätze")), "Name");
      }
    }

      //********** fertigkeiten_besitz **********************************
   {  Query queryZu("select gegenstand,min,position from fertigkeiten_besitz "
   	" where name='"+fert+"' order by min,gegenstand");
      FetchIStream isZu;
      while ((queryZu>>isZu).good()) 
      {  Tag &b=fertigk.push_back(Tag("Besitz"));
         fetch_and_set_string_attrib(isZu, b, "Name");
         fetch_and_set_int_attrib(isZu, b, "Min");
         fetch_and_set_string_attrib(isZu, b, "Position");      }
    }

      //********** fertigkeiten_voraussetzungen_2 **********************************
   {  Query queryV2("select region,lp_stadt,lp_land from regionen_lernen "
   	" where name='"+fert+"' order by region");
      FetchIStream isV2;
      while ((queryV2>>isV2).good()) 
      {  Tag &rlp=fertigk.push_back(Tag("Region_Lernpunkte"));
         fetch_and_set_string_attrib(isV2, rlp, "Region");
         fetch_and_set_int_attrib(isV2, rlp, "LP_Stadt");
         fetch_and_set_int_attrib(isV2, rlp, "LP_Land");
      }
    }
   
      //********** Lernschema **********************************
    lernschema(fertigk, MIDGARD3_4("Fertigkeit","Fachkenntnisse"), fert);
//    pflicht_lernen(fertigk, fert);
//    verbot_lernen(fertigk, fert);
    ausnahmen(fertigk, "f", fert);

// ************************* Steigern wie *****************************
    {  Query query2("select wie from steigern_fertigkeiten where name='"+fert+"'");
       FetchIStream is2=query2.Fetch();
       std::string wie;
       if (is2.good()) wie=fetch_string(is2, fert);
       if (wie!=fert && !wie.empty())
       {  fertigk.push_back(Tag("steigern_wie")).setAttr("Fertigkeit",wie);
       }
    }
//********************* praxispunkte ********************
#ifdef MIDGARD3
      { Query query2("select coalesce(max_wert,0), coalesce(lernfaktor,0)"
      		" from praxispunkte where name='"+fert+"'");
      	FetchIStream is2=query2.Fetch();
      	if (is2.good())
      	{  Tag &pp=fertigk.push_back(Tag("Praxispunkte"));
           fetch_and_set_int_attrib(is2, pp, "MaximalWert");
           fetch_and_set_int_attrib(is2, pp, "Lernfaktor");
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
        {  Tag &k=fertigk.push_back(Tag("Kosten"));
           for (int i=0;i<=28;++i) 
              fetch_and_set_int_attrib(is2, k, "Wert"+itos(i));
        }
      }

      //********** ZEP oder KEP ? ****************
     {   Query query2("select ep from steigern_fertigkeiten_mit"
     		" where name='"+fert+"' order by ep");
      	FetchIStream is2;
      	Tag ep("EP-Typ");
      	while ((query2>>is2).good())
        {  ep.setBoolAttr(fetch_string(is2),true);
        }
        if (ep.attbegin()!=ep.attend()) fertigk.push_back(ep);
     }
  }
  }
#ifdef REGION // Lernschema für Typen dieser Region
  if (!region.empty())
 { FetchIStream is;
   Query q("select fertigkeit, region from fertigkeiten "
   	+ RegionErgaenzungQuery("fertigkeiten.fertigkeit","fertigkeiten_typen","Fertigkeit","f")
   	+ "order by coalesce(region,''),fertigkeit");
  while ((q >> is).good())
  {Tag &fertigk=fertigkeiten.push_back(Tag("Fertigkeit"));
   std::string fert=fetch_and_set_string_attrib(is, fertigk, "Name");
   fetch_and_set_string_attrib(is, fertigk, "Region");

   grund_standard_ausnahme(fertigk, "fertigkeiten_typen",fert,"",true);
   lernschema(fertigk, MIDGARD3_4("Fertigkeit","Fachkenntnisse"),fert,true);
   ausnahmen(fertigk, "f", fert,true);
  }
 }
  if (!region.empty())
 { FetchIStream is;
   Query q("select distinct name from lernschema_4 "
   	"join typen on typ=typs "
   	"where (name like 'Schreiben:%' or name like 'Sprechen:%') "
   	"and region='"+region+"' "
   	"order by name");
  while ((q >> is).good())
  {Tag &fertigk=fertigkeiten.push_back(Tag("Fertigkeit"));
   std::string fert=fetch_and_set_string_attrib(is, fertigk, "Name");

   lernschema(fertigk, MIDGARD3_4("Fertigkeit","Fachkenntnisse"),fert,true);
  }
 }
#endif

//********************* angeborene Fertigkeiten ********************
  if (region.empty())
  {Tag &angeboreneFertigkeiten=o.push_back(Tag("angeboreneFertigkeiten"));
  {Query query("select name, min, max, wert"
  	" from angeborene_fertigkeiten"
  	" order by name");
   FetchIStream is;
   while ((query>>is).good())
  {Tag &fertigk=angeboreneFertigkeiten.push_back(Tag("angeboreneFertigkeit"));
   fetch_and_set_string_attrib(is, fertigk, "Name");
   fetch_and_set_int_attrib(is, fertigk, "Min");
   fetch_and_set_int_attrib(is, fertigk, "Max");
   fetch_and_set_int_attrib(is, fertigk, "Wert");
  }
  }
  }

//********************* Berufe ********************
   Tag &Berufe=o.push_back(Tag("Berufe"));
  {
#ifdef MIDGARD3
   Query query("select beruf, region, lernpunkte, st, ge,"
  	" ko, \"in\", zt, pa, au, sb, typ, geschlecht"
   	" from berufe_voraussetzung"
  	" where coalesce(region,'')='"+region+"'"
   	" order by region, beruf");
#else
   Query query("select beruf, region,region_zusatz, land, stadt,"
   	"typ_k, typ_z, geschlecht, u,v,m,a"
   	" from berufe_voraussetzung_4"
  	" where coalesce(region,'')='"+region+"'"
   	" order by region, beruf");
#endif
   FetchIStream is;
   while ((query>>is).good())
  {Tag &Beruf=Berufe.push_back(Tag("Beruf"));
   std::string beruf=fetch_and_set_string_attrib(is, Beruf, "Name");
   fetch_and_set_string_attrib(is, Beruf, "Region");
   fetch_and_set_string_attrib(is, Beruf, "RegionZusatz");
#ifdef MIDGARD3    
   fetch_and_set_int_attrib(is, Beruf, "Lernpunkte");
#endif
   Tag &v=Beruf.push_back(Tag("Voraussetzungen"));
#ifdef MIDGARD3
   fetch_and_set_int_attrib(is, v, "St");
   fetch_and_set_int_attrib(is, v, "Ge");
   fetch_and_set_int_attrib(is, v, "Ko");
   fetch_and_set_int_attrib(is, v, "In");
   fetch_and_set_int_attrib(is, v, "Zt");
   fetch_and_set_int_attrib(is, v, "pA");
   fetch_and_set_int_attrib(is, v, "Au");
   fetch_and_set_int_attrib(is, v, "Sb");
   fetch_and_set_typ_attrib(is, v, "Typ");
#else
   fetch_and_set_bool_attrib(is, v, "Land");
   fetch_and_set_bool_attrib(is, v, "Stadt");
   fetch_and_set_bool_attrib(is, v, "Kämpfer");
   fetch_and_set_bool_attrib(is, v, "Zauberer");
#endif
   fetch_and_set_string_attrib(is, v, "Geschlecht");
   {  Tag staende("Stand");
#ifdef MIDGARD3
      Query query2("select stand from berufe_stand where beruf='"+beruf
      		+"' order by stand");
      FetchIStream is2;
      while ((query2>>is2).good())
      {  std::string stand=fetch_string(is2);
         if (stand=="U") staende.setBoolAttr("Unfrei",true);
         if (stand=="V") staende.setBoolAttr("Volk",true);
         if (stand=="M") staende.setBoolAttr("Mittelschicht",true);
         if (stand=="A") staende.setBoolAttr("Adel",true);
      }
#else
      if (fetch_bool(is)) staende.setBoolAttr("Unfrei",true);
      if (fetch_bool(is)) staende.setBoolAttr("Volk",true);
      if (fetch_bool(is)) staende.setBoolAttr("Mittelschicht",true);
      if (fetch_bool(is)) staende.setBoolAttr("Adel",true);
#endif
      if (staende.attbegin()!=staende.attend() && staende.attend()-staende.attbegin()!=4)
         Beruf.push_back(staende);
   }
   {  Query query2(
   		"select vorteil from berufe_vorteile" MIDGARD3_4("","_4")
   		" where beruf='"+beruf
      		+"' order by vorteil");
      FetchIStream is2;
      Tag vorteile("Vorteil");
      while ((query2>>is2).good())
      {  vorteile.push_back(Tag("Fertigkeit")).setAttr("Name",fetch_string(is2));
      }
      if (vorteile.begin()!=vorteile.end())
         Beruf.push_back(vorteile);
   }
  }
  }

//********************* praxispunkte ********************
#ifdef MIDGARD3
  if (region.empty())
  {Tag &pp=o.push_back(Tag("Praxispunkte"));
   Query query("select name, max_wert, lernfaktor"
   	" from praxispunkte"
   	" where not exists (select true from fertigkeiten where name=fertigkeit)"
   	" order by name");
   FetchIStream is;
  while ((query>>is).good())
  {Tag &s=pp.push_back("Steigern");
   fetch_and_set_string_attrib(is, s, "Name");
   fetch_and_set_int_attrib(is, s, "MaximalWert");
   fetch_and_set_int_attrib(is, s, "Lernfaktor");
  }
  }
#endif

//********************* ZEP oder KEP oder beides? ********************
  if (region.empty())
  {Tag &verwendbareEP=o.push_back(Tag("verwendbareEP"));
//   verwendbareEP.push_back(Tag("-- hier stehen nur die Dinge, die nicht schon Fertigkeiten sind"));
   Query query("select name, ep"
   	" from steigern_fertigkeiten_mit"
   	" where not exists (select true from fertigkeiten where name=fertigkeit)"
   	" order by name,ep");
   FetchIStream is;
   Tag ep("EP-Typ");
  while ((query>>is).good())
  {std::string fert2=fetch_string(is),ep2=fetch_string(is);
   if (ep.getAttr("Fertigkeit")!=fert2)
   {  if (ep.attbegin()!=ep.attend())
      {  verwendbareEP.push_back(ep);
         ep=Tag("EP-Typ");
         ep.setAttr("Fertigkeit",fert2);
      }
      else ep.setAttr("Fertigkeit",fert2);
   }
   ep.setBoolAttr(ep2,true);
  }
  if (ep.attbegin()!=ep.attend()) verwendbareEP.push_back(ep);
 }

//*************************** Steigerungstabelle *******************
  if (region.empty())
  {Tag &SteigernKosten=o.push_back(Tag("SteigernKosten"));
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
       {  Tag &f=SteigernKosten.push_back(Tag("Kosten"));
          fetch_and_set_string_attrib(is, f, "Fertigkeit");
          for (int i=0;i<=28;++i) 
             fetch_and_set_int_attrib(is, f, "Wert"+itos(i));
       }
  }

//******************************************************************
}

