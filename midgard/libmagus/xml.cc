// $Id: xml.cc,v 1.4 2003/05/09 08:19:10 christof Exp $
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
#include <iostream>
#include "magus_paths.h"
#include <map>

//#define PARANOIA
#define VERBOSE
#include <Misc/TagStream.h>

static TagStream *top;
const Tag *xml_data;
static Tag *xml_data_mutable; // local non const pointer for merging

static void xml_merge(Tag *merge_here, const Tag *tomerge);

typedef std::map<std::string,Tag::difference_type> fastfind_t;
//typedef std::map<std::string,unsiged> fastfind_t;
static fastfind_t fastfind_cache;
static std::string make_key(const xml_liste &tagprops,const Tag &t);

static void reserve(Tag *t, const std::string &type, unsigned int sz)
{  Tag *n=t->find(type);
   if (!n) { t->push_back(Tag(type)); n=&(t->back()); assert(n->Type()==type); }
   n->reserve(sz);
}

static void reserve(Tag *t)
{  t->reserve(64);
//   reserve(t,"Länder",8); // geht irgendwie nicht ...
   reserve(t,"Schriften",32);
   reserve(t,"Sprachen",64);
   reserve(t,"SpeziesListe",16);
   reserve(t,"Gradanstieg",16);
   reserve(t,"Typen",64);
   reserve(t,"Preise",256);
   reserve(t,"Fertigkeiten",256);
   reserve(t,"angeboreneFertigkeiten",32);
   reserve(t,"Berufe",256);
   reserve(t,"verwendbareEP",8);
   reserve(t,"SteigernKosten",8);
   reserve(t,"Rüstungen",32);
   reserve(t,"Waffen",128);
   reserve(t,"Waffen-Grundkenntnisse",32);
   reserve(t,"Waffen-Steigern",16);
   reserve(t,"KI",32);
   reserve(t,"Zauber",1024);
   reserve(t,"Zauberwerke",512);
   reserve(t,"Spezialgebiete",32);
   reserve(t,"Kido-Fertigkeiten",64);
}

void xml_init(SigC::Slot1<void,double> progress,SigC::Slot1<void,const std::string&> meldungen)
{  std::string filename=magus_paths::with_path("midgard.xml");
   if (top) return; // oder merge?
   {  std::ifstream in(filename.c_str());
      top=new TagStream(in);
   }
//   xml_data_mutable=&ts.getContent();
   xml_data_mutable=const_cast<Tag*>(top->find("MAGUS-data"));
   if (!xml_data_mutable) 
      xml_data_mutable=const_cast<Tag*>(top->find("MidgardCG-data"));
   if (!xml_data_mutable) 
   {  std::cerr << "Ladefehler XML Datei " << filename << "\n";
      exit(2);
   }
   
   reserve(xml_data_mutable);
   
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
       std::string file=magus_paths::with_path(t2->getAttr("File"),false,true);
       if (t2->getBoolAttr("inactive",false))
          continue;
       progress(++count/anzdateien);
       t2->Type("Region"); // change Type of Tag "MAGUS-include" -> "Region"
       
//       std::cerr << "loading XML " << file << '\n';
       std::ifstream in2(file.c_str());
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
             {  // std::cout << "TODO: merge '"<< j->Type()<<"' from '"<< file << "'\n";
                xml_merge(merge_here,&*j);
             }
             else 
             {  // std::cout << "initial Tag '"<< j->Type()<<"' from '"<< file << "'\n";
                xml_data_mutable->push_back(*j);
                
                const Tag &newtag=xml_data_mutable->back();
                // prime the cache
                FOR_EACH_CONST_TAG(k,newtag)
                {  const xml_liste *tagprops=suche_Tageigenschaften(newtag.Type(),k->Type());
                   if (tagprops)
                      fastfind_cache[make_key(*tagprops,*k)]=k-newtag.begin();
                }
                // xml_data_mutable->debug();
             }
          }
       }
       else std::cerr << "Kann Datei '" << file << "' nicht öffnen\n";
       goto reloop;
    }
    
#if 0
    for (fastfind_t::const_iterator i=fastfind_cache.begin();i!=fastfind_cache.end();++i)
       std::cout << i->first << '@' << i->second << '\n';
#endif  
#if 0
    FOR_EACH_CONST_TAG(i,*xml_data_mutable)
    {  std::cout << i->Type() << '#' << i->size() << '\n';
    }
#endif    
    fastfind_cache.clear();
    xml_data=xml_data_mutable;
}

void xml_free()
{  xml_data_mutable=0;
   if (top) delete top;
   top=0;
}

const Tag *find_Tag(const std::string &listtag, const std::string &elementtag,
		const std::vector<std::pair<std::string,std::string> > &anforderungen)
{
   if (!xml_data)
   {  std::cerr << "find_Tag("<< listtag<< "," << elementtag <<",";
      for (std::vector<std::pair<std::string,std::string> >::const_iterator i=anforderungen.begin();i!=anforderungen.end();++i)
         std::cerr << '\'' << i->first << "'='" << i->second << "' ";
      std::cerr << ") ohne Daten!\n";
      return 0;
   }
   
#ifdef VERBOSE
std::cerr << "find_Tag("<< listtag<< "," << elementtag <<",";
for (std::vector<std::pair<std::string,std::string> >::const_iterator i=anforderungen.begin();i!=anforderungen.end();++i)
std::cerr << '\'' << i->first << "'='" << i->second << "' ";
std::cerr << ")\n";
#endif
#ifdef PARANOIA
{const xml_liste *liste=suche_Tageigenschaften(listtag,elementtag);
 if (!liste) std::cerr << "find_Tag " << listtag << ',' << elementtag << ": unbekannt\n";
 else
 {  const char * const *k=liste->key;
    std::vector<std::pair<std::string,std::string> >::const_iterator i=anforderungen.begin();
    for (;*k && i!=anforderungen.end();++i,++k)
    {  if (*k!=i->first)
 	  std::cerr << "find_Tag " << listtag << ',' << elementtag << ": key " << i->first << "!=" <<*k<<"\n";
    }
    if (*k)
       std::cerr << "find_Tag " << listtag << ',' << elementtag << ": missing key " <<*k<<"\n";
    else if (i!=anforderungen.end())
       std::cerr << "find_Tag " << listtag << ',' << elementtag << ": additional key " <<i->first<<"\n";
 }
}
#endif
 const Tag *liste=xml_data->find(listtag);
 if (!liste)
    std::cerr << "<"<<listtag<<"><"<<elementtag<<"/>... nicht gefunden\n";
 else
 {  Tag::const_iterator b=liste->begin(),e=liste->end();
    FOR_EACH_CONST_TAG_OF_5(i,*liste,b,e,elementtag)
    {  for (std::vector<std::pair<std::string,std::string> >::const_iterator j=anforderungen.begin();
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
{  std::vector<std::pair<std::string,std::string> > anforderungen;
   anforderungen.push_back(std::pair<std::string,std::string>(name,wert));
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
   {  "KI","Prototyp",std_matching },
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
   
const xml_liste *suche_Tageigenschaften(const std::string &liste, const std::string &elem)
{  const xml_liste *result=xml_tags;
//   std::cerr << "suche_Tageigenschaften " << art << '\n';
   for (;result->listtag;++result)
      if (result->listtag==liste && result->elementtag==elem) return result;
   return 0;
}

static bool attr_is_key(const std::string &tag, const char * const *key)
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

static std::string make_key(const xml_liste &tagprops,const Tag &t)
{  std::string res;
//   for (unsigned int i=reinterpret_cast<unsigned int>(&tagprops); i!=0 ;i>>=6) res+=char((i&0x3f)+' ');
// faster but not readable
//   for (unsigned int i=&tagprops; i!=0 ;i>>=8) res+=char(i ? i : 0x88);

// fast functional index
   res+=char((reinterpret_cast<unsigned int>(&tagprops)&0x3f)+' ');
   res+=char(((reinterpret_cast<unsigned int>(&tagprops)>>6)&0x3f)+' ');
   for (const char * const *k=tagprops.key;*k;++k) res=res+"."+t.getAttr(*k);
   return res;
}

static void xml_merge(Tag *merge_here, const Tag *tomerge)
{  // suche nach tomerge->getAttr("name");
//   std::cout << "merge " << merge_here->Type() << ',' << tomerge->Type() << '\n';
   const xml_liste *tagprops=0;
   FOR_EACH_CONST_TAG(i,*tomerge)
   {  if (i->Type().empty()) continue;
      // nicht immer suchen ...
      if (!tagprops || tagprops->elementtag!=i->Type())
         tagprops=suche_Tageigenschaften(tomerge->Type(),i->Type());
      if (!tagprops)
      {  std::cerr << "Can't find properties for Tag '" << i->Type() << "'\n";
         continue;
      }
//      std::cout << make_key(*tagprops,*i) << '\n';
      
      fastfind_t::iterator ff=fastfind_cache.find(make_key(*tagprops,*i));
      if (ff!=fastfind_cache.end())
      {
         const Tag::iterator j=merge_here->begin()+ff->second;
#if 1
	 const char * const *k=0;
         for (k=tagprops->key;*k && i->getAttr(*k)==j->getAttr(*k);++k) ;
         if (*k) 
         {  std::cerr << "xml_merge: cache failure: " << ff->first << '\n';
            goto continue_i;
         }
#endif      
         xml_merge_element(*j,*i,tagprops->key);
         goto continue_i;
      }
      // not found
//      std::cerr << "pushing back " << i->getAttr("Name") << '\n';
      merge_here->push_back(*i);
      fastfind_cache[make_key(*tagprops,*i)]=merge_here->end()-merge_here->begin()-1;
    continue_i:
      ;
   }
}

