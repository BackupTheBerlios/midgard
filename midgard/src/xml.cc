// $Id: xml.cc,v 1.6 2001/12/27 14:11:47 christof Exp $
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

void xml_init(const std::string &filename="midgard.xml")
{  if (top) return; // oder merge?
   {  ifstream in(filename.c_str());
      top=new TagStream(in);
   }
   xml_data=top->find("MidgardCG-data");
   if (!xml_data) cerr << "Ladefehler XML Datei " << filename << "\n";
   
   Tag::const_iterator b=xml_data->begin(),e=xml_data->end();
    for (Tag::const_iterator i=xml_data->find(b,"MCG:include");
    		i!=e;	i=xml_data->find(i+1,"MCG:include"))
    {  ifstream in2(i->getAttr("File").c_str());
       // wenn nicht, URL holen?
       if (in2.good()) 
       {  TagStream ts2(in2);
          Tag *data2=ts2->find("MidgardCG-data");
          for (Tag::const_iterator j=data2->begin();j!=data2->end();++j))
          {  if (top->find(j->Type()))
             {  // merge
             }
             else top->push_back(*j);
          }
       }
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

#else // no XML, no op

void xml_init(const std::string &filename="midgard.xml")
{}
void xml_free()
{}

#endif
