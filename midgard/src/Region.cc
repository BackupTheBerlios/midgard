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

#include "Region.hh"
#include "MidgardBasicElement.hh" // nur für NotFound
#include "ProgressBar.h"

#include "../pixmaps/Eschar-trans-50.xpm"
#include "../pixmaps/KiDo-trans-50.xpm"
#include "../pixmaps/Regio-DFR-4-50.xpm"
#include "../pixmaps/Regio_Rawindra-50.xpm"
#include "../pixmaps/Regio_Alba-50.xpm"
#include "../pixmaps/Regio_H_u_D-50.xpm"
#include "../pixmaps/Regio_Gilde-50.xpm"
#include "../pixmaps/Regio_Nahuatlan-50.xpm"
#include "../pixmaps/Regio_Waeland-50.xpm"
#include "../pixmaps/Regio_Arkanum-50.xpm"
//#include "../pixmaps/Arkanum-50.xpm"
#include "../pixmaps/pinguin.xpm"

Gtk::Pixmap *RegionenPic::Pic(epic typ)
{  
   if      (typ==Eschar)     return manage(new Gtk::Pixmap(Eschar_trans_50_xpm));
   else if (typ==KanThaiPan) return manage(new Gtk::Pixmap(KiDo_trans_50_xpm));
   else if (typ==DFR)        return manage(new Gtk::Pixmap(Regio_DFR_4_50_xpm));
   else if (typ==Rawindra)   return manage(new Gtk::Pixmap(Regio_Rawindra_50_xpm));
   else if (typ==Alba)       return manage(new Gtk::Pixmap(Regio_Alba_50_xpm));
   else if (typ==Waeland)    return manage(new Gtk::Pixmap(Regio_Waeland_50_xpm));
   else if (typ==Nahuatlan)  return manage(new Gtk::Pixmap(Regio_Nahuatlan_50_xpm));
   else if (typ==Arkanum)    return manage(new Gtk::Pixmap(Regio_Arkanum_50_xpm));
   else if (typ==Gildenbrief)return manage(new Gtk::Pixmap(Regio_Gilde_50_xpm));
   else if (typ==HD)         return manage(new Gtk::Pixmap(Regio_H_u_D_50_xpm));
   else if (typ==Abenteuer)  return manage(new Gtk::Pixmap(Regio_H_u_D_50_xpm));
   else return manage(new Gtk::Pixmap(pinguin_xpm));
   abort();
}


cH_Region::cache_t cH_Region::cache;

cH_Region::cH_Region(const std::string& name)
{
 cH_Region *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  cerr << "Region '" << name << "' nicht im Cache\n";
  throw NotFound();
  }
}

cH_Region::cH_Region(const Tag *tag)
{*this=cH_Region(new Region(tag));
 cache.Register(tag->getAttr("Name"),*this);
}

Region::Region(const Tag *tag) 
: name(tag->getAttr("Name")), active(false)
{
  abkuerzung=tag->getAttr("Region");
  file=tag->getAttr("Dateiname");
  url=tag->getAttr("URL");
  maintainer=tag->getAttr("Maintainer");
  version=tag->getAttr("Version");
  copyright=tag->getAttr("Copyright");
  jahr=tag->getAttr("Jahr");
  offiziell=tag->getBoolAttr("offiziell");
  pic=RegionenPic::epic(tag->getIntAttr("MAGUS-Bild",tag->getIntAttr("MCG-Bild")));
}

bool Region::setActive(const std::vector<cH_Region>& LR,const cH_Region& R,bool active)
{
  for(std::vector<cH_Region>::const_iterator i=LR.begin();i!=LR.end();++i)
   {
     if(R==*i) 
         { 
            (*i)->setActive(active);
            return true;
         }
   }
 return false;
}

bool Region::isActive(const std::vector<cH_Region>& LR,const cH_Region& R)
{
 for(std::vector<cH_Region>::const_iterator i=LR.begin();i!=LR.end();++i)
     if(R==*i)  return (*i)->Active();
 return false;
}


Regionen_All::Regionen_All(Gtk::ProgressBar *progressbar)
{
 if (xml_data)
 {  Tag::const_iterator b=xml_data->begin(),e=xml_data->end();
    double size=e-b;
    FOR_EACH_CONST_TAG_OF_5(i,*xml_data,b,e,"Region")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
       list_All.push_back(cH_Region(&*i));
    }
 }
 ProgressBar::set_percentage(progressbar,1);
}
