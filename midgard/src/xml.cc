// $Id: xml.cc,v 1.13 2002/01/03 09:35:27 christof Exp $
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

#include "xml.h"

#ifdef USE_XML
#include "TagStream.hh"

static TagStream *top;
const Tag *xml_data;

static void xml_merge(Tag *merge_here, const Tag *tomerge);

void xml_init(const std::string &filename="midgard.xml")
{  if (top) return; // oder merge?
   {  ifstream in(filename.c_str());
      top=new TagStream(in);
   }
   xml_data=top->find("MidgardCG-data");
   if (!xml_data) cerr << "Ladefehler XML Datei " << filename << "\n";

reloop:   
   Tag::const_iterator b=xml_data->begin(),e=xml_data->end();
    for (Tag::const_iterator i=xml_data->find(b,"MCG:include");
    		i!=e;	i=xml_data->find(i+1,"MCG:include"))
    {  const Tag *t2=&*i;
       std::string file=t2->getAttr("File");
       if (t2->getBoolAttr("Loaded",false) || t2->getBoolAttr("inactive",false))
          continue;
       // ich weiﬂ, ist unsauber, aber was solls, geht nicht sinnvoll anders
       const_cast<Tag*>(t2)->setAttr("Loaded","True");
       
       ifstream in2(file.c_str());
       // wenn nicht, URL holen?
       // ab hier sollte man nicht mehr auf i, t2 zugreifen (push_back) !!!
       if (in2.good()) 
       {  TagStream ts2(in2);
          const Tag *data2=ts2.find("MidgardCG-data");
          for (Tag::const_iterator j=data2->begin();j!=data2->end();++j)
          {  if (j->Type().empty()) continue; // inter tag space
             const Tag *merge_here;
             if ((merge_here=xml_data->find(j->Type())))
             {  cout << "TODO: merge '"<< j->Type()<<"' from '"<< file << "'\n";
                xml_merge(const_cast<Tag*>(merge_here),&*j);
             }
             else 
             {  // cout << "initial Tag '"<< j->Type()<<"' from '"<< file << "'\n";
                const_cast<Tag*>(xml_data)->push_back(*j);
                // xml_data->debug();
             }
          }
       }
       goto reloop;
    }
}

void xml_free()
{  xml_data=0;
   if (top) delete top;
   top=0;
}

const Tag *find_Tag(const std::string &listtag, const std::string &elementtag,
		const vector<pair<std::string,std::string> > &anforderungen)
{const Tag *liste=xml_data->find(listtag);
 cerr << "find_Tag("<< listtag<< "," << elementtag <<"," << anforderungen[0].second << ",...)\n";
 if (!liste)
    cerr << "<"<<listtag<<"><"<<elementtag<<"/>... nicht gefunden\n";
 else
 {  Tag::const_iterator b=liste->begin(),e=liste->end();
    for (Tag::const_iterator i=liste->find(b,elementtag);
    		i!=e;	i=liste->find(i+1,elementtag))
    {  for (vector<pair<std::string,std::string> >::const_iterator j=anforderungen.begin();
    		j!=anforderungen.end();++j)
       {  if (i->getAttr(j->first)!=j->second) goto continue_outer;
       }
       return &*i;
       
       continue_outer: ;
    }
 }
 return 0;
}

const Tag *find_Tag(const std::string &listtag, const std::string &elementtag,
		const std::string &name, const std::string &wert)
{  vector<pair<std::string,std::string> > anforderungen;
   anforderungen.push_back(pair<std::string,std::string>(name,wert));
   return find_Tag(listtag,elementtag,anforderungen);
}

static const char * const std_matching[] = { "Name",0 };
static const char * const ep_matching[] = { "Fertigkeit",0 };
static const char * const grad_matching[] = { "Grad",0 };
static const char * const typ_matching[] = { "Abk¸rzung",0 };
static const char * const zauberwerk_matching[] = { "Name","Art","Stufe",0 };
static const char * const preis_matching[] = { "Ware",0 }; // Region?
static const char * const modifikation_matching[] = { "Art","Bezeichnung",0 };
static const char * const waff_steig_matching[] = { "Schwierigkeit",0 };

const struct xml_liste xml_tags[] =
  {
// Typ-Pflichten ???  
// SteigernKosten ???
   {  "angeboreneFertigkeiten",	"angeboreneFertigkeit",	std_matching },
   {  "Berufe",		"Beruf",	std_matching },
   {  "Fertigkeiten",	"Fertigkeit",	std_matching },
   {  "Gradanstieg",	"Grad",		grad_matching },
   {  "Kido-Fertigkeiten",	"KiDo",	std_matching },
   {  "L‰nder",		"Land",		std_matching },
   {  "Preise",		"Kaufpreis",	preis_matching },
   {  "Preise",		"Modifikation",	modifikation_matching },
   {  "R¸stungen",	"R¸stung",	std_matching },
   {  "Schriften",	"Schrift",	std_matching },
   {  "Spezialgebiete",	"Spezialgebiet",	std_matching },
   {  "SpeziesListe",	"Spezies",	std_matching },
   {  "Sprachen",	"Sprache",	std_matching },
   {  "Typen",		"Typ",		typ_matching },
   {  "verwendbareEP",	"EP-Typ",	ep_matching },
   {  "Waffen-Grundkenntnisse",	"Waffen-Grundkenntnis",	std_matching },
   {  "Waffen-Steigern",	"Kosten",	waff_steig_matching },
   {  "Waffen",		"Waffe",	std_matching },
   {  "Zauber",		"Spruch",	std_matching },
   {  "Zauberwerke",	"Zauberwerk",	zauberwerk_matching },
   {  (const char*)0,	(const char*)0,	(const char*const*)0 }};

static void xml_merge(Tag *merge_here, const Tag *tomerge)
{  // suche nach tomerge->getAttr("name");
   
}

#else // no XML, no op

void xml_init(const std::string &filename="midgard.xml")
{}
void xml_free()
{}

#endif
