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

extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

Glib::RefPtr<Gdk::Pixbuf> RegionenPic::PicModel(epic typ,Midgard_Optionen::IconIndex ii,bool tiny)
{  std::string name="pinguin.xpm";
   if      (typ==Eschar)     name="Eschar-trans-50.xpm";
   else if (typ==KanThaiPan) name="KiDo-trans-50.xpm";
   else if (typ==DFR)        name="Regio-DFR-4-50.xpm";
   else if (typ==Rawindra)   name="Regio_Rawindra-50.xpm";
   else if (typ==Alba)       name="Regio_Alba-50.xpm";
   else if (typ==Waeland)    name="Regio_Waeland-50.xpm";
   else if (typ==Nahuatlan)  name="Regio_Nahuatlan-50.xpm";
   else if (typ==Arkanum)    name="Regio_Arkanum-50.xpm";
   else if (typ==Gildenbrief)name="Regio_Gilde-50.xpm";
   else if (typ==HD)         name="Regio_H_u_D-50.xpm";
   else if (typ==HD_finster) name="Regio_H_u_D_F-50.xpm";
   else if (typ==Tipps_und_Tricks)  name="TuT_50.xpm";
   else if (typ==Abenteuer)  name="Abwehr-50.xpm";

   Glib::RefPtr<Gdk::Pixbuf> res=MagusImage(name);
   if (tiny && ii!=Midgard_Optionen::Ulf && !res.is_null())
      res=res->scale_simple(int(res->get_width()*26.0/res->get_height()+.5),
      				26,Gdk::INTERP_BILINEAR);
   return res;
}

Gtk::Image *RegionenPic::Pic(epic typ,Midgard_Optionen::IconIndex ii,bool tiny)
{  return manage(new Gtk::Image(PicModel(typ,ii,tiny)));
}

cH_Region::cache_t cH_Region::cache;

cH_Region::cH_Region(const std::string& name,bool create)
{
 cH_Region *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else if (create)
  { static Tag t2("Region");
    t2.setAttr("Region",name);
    *this=cH_Region(&t2);
  }
 else
  {
  std::cerr << "Region '" << name << "' nicht im Cache\n";
  throw NotFound();
  }
}

cH_Region::cH_Region(const Tag *tag)
{*this=cH_Region(new Region(tag));
 cache.Register(tag->getAttr("Name"),*this);
}

Region::Region(const Tag *tag) 
: name(tag->getAttr("Name")), active()
{
  nr=tag->getIntAttr("MAGUS-Index");
  titel=tag->getAttr("Titel");
  abkuerzung=tag->getAttr("Region");
  file=tag->getAttr("Dateiname");
  url=tag->getAttr("URL");
  maintainer=tag->getAttr("Maintainer");
  version=tag->getAttr("Version");
  copyright=tag->getAttr("Copyright");
  jahr=tag->getAttr("Jahr");
  offiziell=tag->getBoolAttr("offiziell");
  pic=RegionenPic::epic(tag->getIntAttr("MAGUS-Bild",tag->getIntAttr("MCG-Bild")));
  region_pix=RegionenPic::PicModel(pic,Midgard_Optionen::Self);
  region_pix_small=RegionenPic::PicModel(pic,Midgard_Optionen::Self,true);
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


cH_Region Regionen_All::getRegionfromAbk(const std::vector<cH_Region>& V,const std::string& r)
{
 for(std::vector<cH_Region>::const_iterator i=V.begin();i!=V.end();++i)
  {
   if(r==(*i)->Abkuerzung()) 
    {
      if((*i)->Nr()<0) return cH_Region("",true); // DFR und Arkanum gelten NICHT als Regionen
      return (*i);
    }
  }
 return cH_Region("???",true);
// assert(!"Region nicht gefunden\n");
// abort(); // never get here
}

