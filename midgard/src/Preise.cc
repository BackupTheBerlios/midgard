/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include "MidgardBasicElement.hh" // nur f�r NotFound
#include "Preise.hh"
#include "ProgressBar.h"
#include <Aux/itos.h>

cH_Preise::cache_t cH_Preise::cache;

cH_Preise::cH_Preise(const std::string& name IF_XML(,bool create))
{
 cH_Preise *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  cerr << "Preis '" << name << "' nicht im Cache\n";
  if (create)
  {  static Tag t2("Kaufpreis"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Ware",name);
     t2.setAttr("Art","?");
     t2.setAttr("Art2","?");
     *this=cH_Preise(&t2);
  }
  else throw NotFound();
  }
}

cH_Preise::cH_Preise(const Tag *tag)
{*this=cH_Preise(new Preise(tag));
 cache.Register(tag->getAttr("Ware"),*this);
}

cH_Preise::cH_Preise(const std::string& _name, const std::string& _art, const Tag *tag)
{*this=cH_Preise(new Preise(_name,_art,tag));
 cache.Register(_name,*this);
}

void Preise::get_Preise()
{
  art2=tag->getAttr("Art2");
  einheit=tag->getAttr("W�hrung");
  kosten=tag->getFloatAttr("Preis");
  gewicht=tag->getFloatAttr("Gewicht");
}

Preise_All::Preise_All(Gtk::ProgressBar *progressbar)
{
 const Tag *preise=xml_data->find("Preise");
 if (preise)
 {  Tag::const_iterator b=preise->begin(),e=preise->end();
    double size=(e-b)*3;
    FOR_EACH_CONST_TAG_OF_5(i,*preise,b,e,"Kaufpreis")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
       list_All.push_back(cH_Preise(&*i));
    }
 }   
 const Tag *waffen=xml_data->find("Waffen");
 if (waffen)
 {  Tag::const_iterator b=waffen->begin(),e=waffen->end();
    double size=(e-b)*3;
    FOR_EACH_CONST_TAG_OF_5(i,*waffen,b,e,"Waffe")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size+.33);
       {  const Tag *preis=i->find("Kaufpreis");
          if (preis) 
             list_All.push_back(cH_Preise(i->getAttr("Name"),"Waffen",&*i));
       }
       FOR_EACH_CONST_TAG_OF(j,*i,"regionaleVariante")
       {  const Tag *preis=i->find("Kaufpreis");
          if (preis)
             list_All.push_back(cH_Preise(j->getAttr("Name"),"Waffen",&*i));
       }
    }
 }   
 const Tag *ruestungen=xml_data->find("R�stungen");
 if (ruestungen)
 {  Tag::const_iterator b=ruestungen->begin(),e=ruestungen->end();
    double size=(e-b)*3;
    FOR_EACH_CONST_TAG_OF_5(i,*ruestungen,b,e,"R�stung")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size+.66);
       {  const Tag *preis=i->find("Kaufpreis");
          if (preis) 
             list_All.push_back(cH_Preise(i->getAttr("Name"),"R�stung",&*i));
       }
    }
 }   
 ProgressBar::set_percentage(progressbar,1);
}  
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
cH_PreiseMod::cache_t cH_PreiseMod::cache;

cH_PreiseMod::cH_PreiseMod(const std::string& art,const std::string& art2,const std::string typ,const int &nr)
{
 st_index index(art,art2,typ,nr);
 cH_PreiseMod *cached(cache.lookup(index));
 if (cached) *this=*cached;
  assert(!"PreiseMod im Cache");
}

cH_PreiseMod::cH_PreiseMod(const Tag *tag)
{*this=cH_PreiseMod(new PreiseMod(tag));
	// art,art2,typ,nr
 cache.Register(st_index(tag->getAttr("Art"),tag->getAttr("Art2"),
 		tag->getAttr("Typ"),
 		tag->getIntAttr("MAGUS-Nr",tag->getIntAttr("MCG-Nr"))),*this);
}

void PreiseMod::get_PreiseMod()
{
  assert(tag);
  nr=tag->getIntAttr("MAGUS-Nr",tag->getIntAttr("MCG-Nr"));
  art=tag->getAttr("Art");
  art2=tag->getAttr("Art2");
  typ=tag->getAttr("Typ");
  payload=st_payload(tag->getAttr("Bezeichnung"),tag->getFloatAttr("Faktor"));
//cout << tag->getAttr("Bezeichnung")<<' '<<tag->getFloatAttr("Faktor")<<'\n';
#warning Christof: FLOAT geht nicht :-(
}


PreiseMod_All::PreiseMod_All(Gtk::ProgressBar *progressbar)
{
 const Tag *preise=xml_data->find("Preise");
 if (preise)
 {  Tag::const_iterator b=preise->begin(),e=preise->end();
    double size=e-b;
    FOR_EACH_CONST_TAG_OF_5(i,*preise,b,e,"Modifikation")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
       list_All.push_back(cH_PreiseMod(&*i));
    }
 }   
 ProgressBar::set_percentage(progressbar,1);
}  


/////////////////////////////////////////////////////////////////////////
// Neuanlegen
/////////////////////////////////////////////////////////////////////////

// use this tag to determine whether this is a user defined item
Tag Preise::eigenerArtikel("Kaufpreis");

void Preise::saveArtikel(std::string art,std::string art2,std::string name,double preis, std::string einheit,double gewicht)
{
  eigenerArtikel.setAttr("Art2",art2);
  eigenerArtikel.setAttr("W�hrung",einheit);
  eigenerArtikel.setAttr("Preis",dtos(preis));
  eigenerArtikel.setAttr("Gewicht",dtos(gewicht));
  cH_Preise(name,art,&eigenerArtikel);
}
