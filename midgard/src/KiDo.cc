/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include "KiDo.hh"
#include <cstring>
#include <Gtk_OStream.h>
#include <Aux/itos.h>
#include "ProgressBar.h"

cH_KiDo::cache_t cH_KiDo::cache;

cH_KiDo::cH_KiDo(const std::string& name IF_XML(,bool create))
{
 cH_KiDo *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  cerr << "KiDo '" << name << "' nicht im Cache\n";
  if (create)
  {  static Tag t2("KiDo"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Name",name);
     t2.setAttr("�bersetzung","?");
     t2.setAttr("Stil","?");
     *this=cH_KiDo(&t2);
  }
  else throw NotFound();
  }
}

cH_KiDo::cH_KiDo(const Tag *tag)
{*this=cH_KiDo(new KiDo(tag));
 cache.Register(tag->getAttr("Name"),*this);
}

void KiDo::get_KiDo()
{
  assert(tag);
  deutsch = tag->getAttr("�bersetzung");
  stufe = tag->getAttr("Stufe");
  stil=tag->getAttr("Stil");
  kosten=tag->getIntAttr("Lernkosten");
  ap=tag->getIntAttr("AP");
  effekt=tag->Value();  
}


int KiDo::get_erfolgswert_kido(const std::list<cH_MidgardBasicElement>& L)
{
 for (std::list<cH_MidgardBasicElement>::const_iterator i= L.begin();i!=L.end();++i)
   if (cH_Fertigkeit(*i)->Name() == "KiDo") return cH_Fertigkeit(*i)->Erfolgswert();
 abort();
}   

std::map<std::string,int> KiDo::maxkidostil(const std::list<cH_MidgardBasicElement>& list_Kido)
{
  std::map<std::string,int> MK;
  for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Kido.begin();i!=list_Kido.end();++i)
     MK[cH_KiDo(*i)->Stufe()]++;
  return MK;
}


KiDo_All::KiDo_All(Gtk::ProgressBar *progressbar)
{
 const Tag *Kido_Fertigkeiten=xml_data->find("Kido-Fertigkeiten");
 if (Kido_Fertigkeiten)
 {  Tag::const_iterator b=Kido_Fertigkeiten->begin(),e=Kido_Fertigkeiten->end();
    double size=(e-b);
    FOR_EACH_CONST_TAG_OF_5(i,*Kido_Fertigkeiten,b,e,"KiDo")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
       list_All.push_back(&*(cH_KiDo(&*i)));
    }
 }
 ProgressBar::set_percentage(progressbar,1);
}  