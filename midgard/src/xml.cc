// $Id: xml.cc,v 1.33 2002/06/28 07:36:51 thoma Exp $
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

#include "xml.h"

#ifdef USE_XML

//#define PARANOIA
#define VERBOSE
#include "TagStream.hh"
#include "ProgressBar.h"

static TagStream *top;
const Tag *xml_data;
static Tag *xml_data_mutable; // local non const pointer for merging

static void xml_merge(Tag *merge_here, const Tag *tomerge);

void xml_init(Gtk::ProgressBar *progressbar, const std::string &filename)
{  if (top) return; // oder merge?
   {  ifstream in(filename.c_str());
      top=new TagStream(in);
   }
//   xml_data_mutable=&ts.getContent();
   xml_data_mutable=const_cast<Tag*>(top->find("MAGUS-data"));
   if (!xml_data_mutable) 
      xml_data_mutable=const_cast<Tag*>(top->find("MidgardCG-data"));
   if (!xml_data_mutable) 
   {  cerr << "Ladefehler XML Datei " << filename << "\n";
      exit(2);
   }
//   std::string dir=xml_data_mutable->getAttr("XML-Verzeichnis",".");
   std::string dir=filename;
   dir.replace(dir.rfind("midgard.xml"),string("midgard.xml").size(),"");
#if 0
#ifdef __MINGW32__
   dir+='\\'; // Windows
#else
   dir+='/'; // Unix
#endif
#endif
   double anzdateien=1;
   FOR_EACH_CONST_TAG(i,*xml_data_mutable)
   {  if (i->Type()!="MAGUS-include" && i->Type()!="MCG-include") continue;
      if (!i->getBoolAttr("inactive",false)) 
         ++anzdateien;
   }
   int count=0;
reloop:   
//   Tag::iterator b=xml_data_mutable->begin(),e=xml_data_mutable->end();
    FOR_EACH_TAG(i,*xml_data_mutable)
    {  if (i->Type()!="MAGUS-include" && i->Type()!="MCG-include") continue;
       Tag *t2=&*i;
       std::string file=dir+t2->getAttr("File");
       if (t2->getBoolAttr("inactive",false))
          continue;
       ProgressBar::set_percentage(progressbar,++count/anzdateien);
       t2->Type("Region"); // change Type of Tag "MAGUS-include" -> "Region"
       
       cerr << "loading XML " << file << '\n';
       ifstream in2(file.c_str());
       // wenn nicht, URL holen?
       // ab hier sollte man nicht mehr auf i, t2 zugreifen (push_back) !!!
       if (in2.good()) 
       {  TagStream ts2(in2);
          const Tag *data2=ts2.find("MAGUS-data");
          if (!data2) data2=ts2.find("MidgardCG-data");
          if (!data2)
          {  std::cerr << "XML-Datei '"<<file<<"' ist in ihrem Aufbau fehlerhaft\n";
             continue;
          }
          for (Tag::const_attiterator j=data2->attbegin();j!=data2->attend();++j)
             t2->setAttr(j->first,j->second);
          FOR_EACH_CONST_TAG(j,*data2)
          {  if (j->Type().empty()) continue; // inter tag space
             Tag *merge_here;
             if ((merge_here=xml_data_mutable->find(j->Type())))
             {  // cout << "TODO: merge '"<< j->Type()<<"' from '"<< file << "'\n";
                xml_merge(merge_here,&*j);
             }
             else 
             {  // cout << "initial Tag '"<< j->Type()<<"' from '"<< file << "'\n";
                xml_data_mutable->push_back(*j);
                // xml_data_mutable->debug();
             }
          }
       }
       else std::cerr << "Kann Datei '" << file << "' nicht öffnen\n";
       goto reloop;
    }
    xml_data=xml_data_mutable;
}

void xml_free()
{  xml_data_mutable=0;
   if (top) delete top;
   top=0;
}

const Tag *find_Tag(const std::string &listtag, const std::string &elementtag,
		const vector<pair<std::string,std::string> > &anforderungen)
{
   if (!xml_data)
   {  cerr << "find_Tag("<< listtag<< "," << elementtag <<",";
      for (vector<pair<std::string,std::string> >::const_iterator i=anforderungen.begin();i!=anforderungen.end();++i)
         cerr << '\'' << i->first << "'='" << i->second << "' ";
      cerr << ") ohne Daten!\n";
      return 0;
   }
   
#ifdef VERBOSE
cerr << "find_Tag("<< listtag<< "," << elementtag <<",";
for (vector<pair<std::string,std::string> >::const_iterator i=anforderungen.begin();i!=anforderungen.end();++i)
cerr << '\'' << i->first << "'='" << i->second << "' ";
cerr << ")\n";
#endif
#ifdef PARANOIA
{const xml_liste *list=suche_Tageigenschaften(listtag,elementtag);
 if (!list) cerr << "find_Tag " << listtag << ',' << elementtag << ": unbekannt\n";
 else
 {  const char * const *k=list->key;
    vector<pair<std::string,std::string> >::const_iterator i=anforderungen.begin();
    for (;*k && i!=anforderungen.end();++i,++k)
    {  if (*k!=i->first)
 	  cerr << "find_Tag " << listtag << ',' << elementtag << ": key " << i->first << "!=" <<*k<<"\n";
    }
    if (*k)
       cerr << "find_Tag " << listtag << ',' << elementtag << ": missing key " <<*k<<"\n";
    else if (i!=anforderungen.end())
       cerr << "find_Tag " << listtag << ',' << elementtag << ": additional key " <<i->first<<"\n";
 }
}
#endif
 const Tag *liste=xml_data->find(listtag);
 if (!liste)
    cerr << "<"<<listtag<<"><"<<elementtag<<"/>... nicht gefunden\n";
 else
 {  Tag::const_iterator b=liste->begin(),e=liste->end();
    FOR_EACH_CONST_TAG_OF_5(i,*liste,b,e,elementtag)
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
static const char * const typ_matching[] = { "Abkürzung",0 };
static const char * const verbot_matching[] = { "Typ","Fertigkeit",0 };
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
   {  "Länder",		"Land",		std_matching },
   {  "Preise",		"Kaufpreis",	preis_matching },
   {  "Preise",		"Modifikation",	modifikation_matching },
   {  "Rüstungen",	"Rüstung",	typ_matching },
   {  "Schriften",	"Schrift",	std_matching },
   {  "Spezialgebiete",	"Spezialgebiet",	std_matching },
   {  "SpeziesListe",	"Spezies",	std_matching },
   {  "Sprachen",	"Sprache",	std_matching },
   {  "SteigernKosten",	"Kosten",	ep_matching },
   {  "Typen",		"Typ",		typ_matching },
//   {  "Typ-Pflichten",	"Verbot",	verbot_matching },
   {  "verwendbareEP",	"EP-Typ",	ep_matching },
   {  "Waffen-Grundkenntnisse",	"Waffen-Grundkenntnis",	std_matching },
   {  "Waffen-Steigern",	"Kosten",	waff_steig_matching },
   {  "Waffen",		"Waffe",	std_matching },
   {  "Zauber",		"Spruch",	std_matching },
   {  "Zauberwerke",	"Zauberwerk",	zauberwerk_matching },
   {  (const char*)0,	(const char*)0,	(const char*const*)0 }};
   
const xml_liste *suche_Tageigenschaften(const std::string &list, const std::string &elem)
{  const xml_liste *result=xml_tags;
//   cerr << "suche_Tageigenschaften " << art << '\n';
   for (;result->listtag;++result)
      if (result->listtag==list && result->elementtag==elem) return result;
   return 0;
}

static bool attr_is_key(const string &tag, const char * const *key)
{  while (*key && *key!=tag) ++key;
   return (*key)!=0;
}

// TODO: merge of Waffen/Waffe/Waffen-Grundkenntnis/Grund etc

static void xml_merge_element(Tag &merge_here,
	const Tag &tomerge,const char * const *key)
{  bool a_full=false,b_full=false;

   for (Tag::const_attiterator i=merge_here.attbegin();i!=merge_here.attend();++i)
      if (!attr_is_key(i->first,key) && i->first!="Region")
      {  a_full=true; break; }
   for (Tag::const_attiterator i=tomerge.attbegin();i!=tomerge.attend();++i)
      if (!attr_is_key(i->first,key) && i->first!="Region")
      {  b_full=true; break; }
   if (a_full && b_full)
   {  std::cerr << "can't merge Tag attributes:\n";
      merge_here.debug();
      tomerge.debug();
      // try to do it as best as we can ...
      FOR_EACH_CONST_TAG(i,tomerge)
      {  if (i->Type().empty()) continue;
         merge_here.push_back(*i);
      }
   }
   else if (b_full) // this is not well tested but looks good
   {  Tag help=merge_here;
      merge_here=tomerge;
      FOR_EACH_CONST_TAG(i,help)
      {  if (i->Type().empty()) continue;
         merge_here.push_back(*i);
      }
   }
   else
   {  FOR_EACH_CONST_TAG(i,tomerge)
      {  if (i->Type().empty()) continue;
         merge_here.push_back(*i);
      }
   }
}

static void xml_merge(Tag *merge_here, const Tag *tomerge)
{  // suche nach tomerge->getAttr("name");
//   cout << "merge " << merge_here->Type() << ',' << tomerge->Type() << '\n';
   FOR_EACH_CONST_TAG(i,*tomerge)
   {  if (i->Type().empty()) continue;
      const xml_liste *tagprops=suche_Tageigenschaften(tomerge->Type(),i->Type());
      if (!tagprops)
      {  cerr << "Can't find properties for Tag '" << i->Type() << "'\n";
         continue;
      }
      FOR_EACH_TAG(j,*merge_here)
      {  if (j->Type().empty()) continue;
         const char * const *k=0;
         for (k=tagprops->key;*k && i->getAttr(*k)==j->getAttr(*k);++k) ;
         if (!*k) // full match
         {  xml_merge_element(*j,*i,tagprops->key);
            goto continue_i;
         }
      }
      // not found
//      cerr << "pushing back " << i->getAttr("Name") << '\n';
      merge_here->push_back(*i);
    continue_i:
      ;
   }
}

#else // no XML, no op

void xml_init(const std::string &filename="midgard.xml")
{}
void xml_free()
{}

#endif
