/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2002      Christof Petig 
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

#include "Fertigkeiten_angeboren.hh"
#include "ProgressBar.h"
#include "Grundwerte.hh"

cH_Fertigkeit_angeborene::cache_t cH_Fertigkeit_angeborene::cache;

cH_Fertigkeit_angeborene::cH_Fertigkeit_angeborene(const std::string& name IF_XML(,bool create))
{
 cH_Fertigkeit_angeborene *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  cerr << "angeborene Fertigkeit '" << name << "' nicht im Cache\n";
  if (create)
  {  static Tag t2("angeboreneFertigkeit"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Name",name);
     *this=cH_Fertigkeit_angeborene(&t2);
  }
  else throw NotFound();
  }
}

cH_Fertigkeit_angeborene::cH_Fertigkeit_angeborene(const Tag *tag)
{*this=cH_Fertigkeit_angeborene(new Fertigkeit_angeborene(tag));
 cache.Register(tag->getAttr("Name"),*this);
}

void Fertigkeit_angeborene::get_Fertigkeit()
{
 assert(tag);
 min=tag->getIntAttr("Min");
 max=tag->getIntAttr("Max");
 erfolgswert=tag->getIntAttr("Wert");
}


int Fertigkeit_angeborene::FErfolgswert(const Grundwerte &Werte) const
{
  if(Name()=="Trinken") return Erfolgswert()+Werte.Ko()/10;
  if(Name()=="Berserkergang") return Erfolgswert()-Werte.Wk()/5;
  else return Erfolgswert();
}



Fertigkeiten_angeborene_All::Fertigkeiten_angeborene_All(Gtk::ProgressBar *progressbar)
{
 const Tag *angeboreneFertigkeiten=xml_data->find("angeboreneFertigkeiten");
 if (angeboreneFertigkeiten)
 {  Tag::const_iterator b=angeboreneFertigkeiten->begin(),e=angeboreneFertigkeiten->end();
    double size=e-b;
    FOR_EACH_CONST_TAG_OF_5(i,*angeboreneFertigkeiten,b,e,"angeboreneFertigkeit")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
       list_All.push_back(&*(cH_Fertigkeit_angeborene(&*i)));
    }
 }
 ProgressBar::set_percentage(progressbar,1);
}
