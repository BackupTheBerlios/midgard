/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

#include "WaffeGrund.hh"
#include "midgard_CG.hh"
#include "Typen.hh"
#include "ProgressBar.h"

cH_WaffeGrund::cache_t cH_WaffeGrund::cache;

cH_WaffeGrund::cH_WaffeGrund(const std::string& name ,bool create)
{
 cH_WaffeGrund *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  cerr << "Waffengrundfert. '" << name << "' nicht im Cache\n";
  if (create)
  {  static Tag t2("Waffen-Grundkenntnis");
     // note that this Tag is shared ... works well for now
     t2.setAttr("Name",name);
     *this=cH_WaffeGrund(&t2);
  }
  else throw NotFound();
  }
}

cH_WaffeGrund::cH_WaffeGrund(const Tag *tag)
{*this=cH_WaffeGrund(new WaffeGrund(tag));
 cache.Register(tag->getAttr("Name"),*this);
}

void WaffeGrund::get_WaffeGrund()
{
   kosten=tag->getIntAttr("Kosten");
   region=tag->getAttr("Region");
}

WaffeGrund_All::WaffeGrund_All(Gtk::ProgressBar *progressbar)
{
 const Tag *waffengrundf=xml_data->find("Waffen-Grundkenntnisse");
 if (waffengrundf)
 {  Tag::const_iterator b=waffengrundf->begin(),e=waffengrundf->end();
    double size=e-b;
    FOR_EACH_CONST_TAG_OF_5(i,*waffengrundf,b,e,"Waffen-Grundkenntnis")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
       list_All.push_back(&*(cH_WaffeGrund(&*i)));
    }
 }   
 ProgressBar::set_percentage(progressbar,1);
}
