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

#include "Ruestung.hh"
#include "ProgressBar.h"
#include "MidgardBasicElement.hh" // für NotFound

cH_Ruestung::cache_t cH_Ruestung::cache;

cH_Ruestung::cH_Ruestung(const std::string& name IF_XML(,bool create))
{
 cH_Ruestung *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  cerr << "Rüstung '" << name << "' nicht im Cache\n";
  const Tag *t=find_Tag("Rüstungen","Rüstung","Abkürzung",name);
  if (t) *this=cH_Ruestung(t);
  else if (create || !xml_data) // !xml_data = vor Einlesen der Daten
  {  static Tag t2("Rüstung"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Abkürzung",name);
     t2.setAttr("Name",name);
     *this=cH_Ruestung(&t2);
  }
  else throw NotFound();
  }
}

cH_Ruestung::cH_Ruestung(const Tag *tag)
{*this=cH_Ruestung(new Ruestung(tag));
 cache.Register(tag->getAttr("Abkürzung"),*this);
}

Ruestung::Ruestung(const Tag *tag) 
: name(tag->getAttr("Abkürzung"))
{
  longname=tag->getAttr("Name");
  region=tag->getAttr("Region");
  lp_verlust=tag->getIntAttr("schütztLP");
  min_staerke=tag->getIntAttr("minimaleStärke");
  const Tag *Verlust=tag->find("Verlust");
  if (Verlust)
  {  rw_verlust=Verlust->getIntAttr("RW");
     b_verlust=Verlust->getIntAttr("B");
     abwehr_bonus_verlust=Verlust->getIntAttr("Abwehrbonus");;
     angriffs_bonus_verlust=Verlust->getIntAttr("Angriffsbonus");
  }
  else
     rw_verlust=b_verlust=abwehr_bonus_verlust=angriffs_bonus_verlust=0;
  vollruestungsabzug=tag->getIntAttr("Vollrüstung");
}

Ruestung_All::Ruestung_All(Gtk::ProgressBar *progressbar)
{
 const Tag *ruestungen=xml_data->find("Rüstungen");
 if (ruestungen)
 {  Tag::const_iterator b=ruestungen->begin(),e=ruestungen->end();
    double size=e-b;
    FOR_EACH_CONST_TAG_OF_5(i,*ruestungen,b,e,"Rüstung")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
       list_All.push_back(cH_Ruestung(&*i));
    }
 }   
 ProgressBar::set_percentage(progressbar,1);
}


int Ruestung::AbwehrBonus_Verlust(int abwehr_bonus) const
{
  if(abwehr_bonus_verlust<=abwehr_bonus) return abwehr_bonus_verlust;
  else return 0;
  abort();
} 

int Ruestung::AngriffsBonus_Verlust(int angriffs_bonus) const
{
  if(angriffs_bonus_verlust<=angriffs_bonus) return angriffs_bonus_verlust;
  else return 0;
  abort();
}

