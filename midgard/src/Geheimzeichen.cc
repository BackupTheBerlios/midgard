/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2002 Christof Petig
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

#include "Geheimzeichen.hh"
#include "ProgressBar.h"
#include "MidgardBasicElement.hh" // für NotFound

cH_Geheimzeichen::cache_t cH_Geheimzeichen::cache;

cH_Geheimzeichen::cH_Geheimzeichen(const std::string& name ,bool create)
{
 cH_Geheimzeichen *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  cerr << "Geheimzeichen '" << name << "' nicht im Cache\n";
  if (create) // don t ask me ... it just works this way ...
  {  static Tag t2("Geheimzeichen"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Name",name);
     *this=cH_Geheimzeichen(&t2);
  }
  else throw NotFound();
  }
}

Geheimzeichen::Geheimzeichen(const Tag *tag)
: name(tag->getAttr("Name"))
{
}


cH_Geheimzeichen::cH_Geheimzeichen(const Tag *tag)
{
   *this=cH_Geheimzeichen(new Geheimzeichen(tag));
   cache.Register(tag->getAttr("Name"),*this);
}

Geheimzeichen_All::Geheimzeichen_All(Gtk::ProgressBar *progressbar)
{
 const Tag *G=xml_data->find("geheimzeichen");
 if (G)
 {  Tag::const_iterator b=G->begin(),e=G->end();
    double size=(e-b);
    FOR_EACH_CONST_TAG_OF_5(i,*G,b,e,"Name")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
       list_All.push_back(&*(cH_Geheimzeichen(&*i)));
    }
 }
 ProgressBar::set_percentage(progressbar,1);
}
