// $Id: xml.cc,v 1.1 2001/11/21 07:21:01 christof Exp $
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
static TagStream *top;
Tag *xml_data;

void xml_init(const std::string &filename="midgard.xml")
{  if (top) return; // oder merge?
   {  ifstream in(filename);
      top=new TagStream(in);
   }
   xml_data=top.find("MidgardCG-data");
   if (!xml_data) cerr << "Ladefehler XML Datei " << filename << "\n";
}

void xml_free()
{  xml_data=0;
   if (top) delete top;
   top=0;
}

#else // no XML, no op
void xml_init(const std::string &filename="midgard.xml")
{}
void xml_free()
{}
#endif
