// $Id: xml.h,v 1.13 2002/10/24 07:21:01 christof Exp $
/*  Midgard Character Generator
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

#ifndef MCG_XML_H
#define MCG_XML_H

#include "Tag.hh"


extern const Tag *xml_data;
const Tag *find_Tag(const std::string &listtag, const std::string &elementtag,
		const std::vector<pair<std::string,std::string> > &anforderungen);
const Tag *find_Tag(const std::string &listtag, const std::string &elementtag,
		const std::string &name, const std::string &wert);

struct xml_liste
{  const char * const listtag;
   const char * const elementtag;
   const char * const * const key;
};

extern const struct xml_liste xml_tags[];
// suche nach elementtag
const xml_liste *suche_Tageigenschaften(const std::string &std::list,const std::string &elem);

namespace Gtk { class ProgressBar; }
class midgard_CG;
void xml_init(Gtk::ProgressBar *pb, midgard_CG *hauptfenster);

void xml_free();
#endif
