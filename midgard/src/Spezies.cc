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

#include "Spezies.hh"
#include "ProgressBar.h"
#include "MidgardBasicElement.hh" // für NotFound

cH_Spezies::cache_t cH_Spezies::cache;

cH_Spezies::cH_Spezies(const std::string& name IF_XML(,bool create))
{
 cH_Spezies *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  cerr << "Spezies '" << name << "' nicht im Cache\n";
  const Tag *t=find_Tag("SpeziesListe","Spezies","Name",name);
  if (t) *this=cH_Spezies(t);
  else if (create || !xml_data) // !xml_data = vor Einlesen der Daten
  {  static Tag t2("Spezies"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Name",name);
     *this=cH_Spezies(&t2);
  }
  else throw NotFound();
  }
}

cH_Spezies::cH_Spezies(const Tag *tag)
{*this=cH_Spezies(new Spezies(tag));
 cache.Register(tag->getAttr("Name"),*this);
}

Spezies::Spezies(const Tag *tag) 
: name(tag->getAttr("Name"))
{
 nr=tag->getIntAttr("MAGUS-Index",tag->getIntAttr("MCG-Index"));
 land=tag->getBoolAttr("Land");
 
 const Tag *Minima=tag->find("Minima");
 const Tag *Maxima=tag->find("Maxima");
 if (!Minima) Minima=tag; // similar to empty tag for this purpose
 if (!Maxima) Maxima=tag;
 st=Minima->getIntAttr("St",-Maxima->getIntAttr("St"));
 gw=Minima->getIntAttr("St",-Maxima->getIntAttr("Gw"));
 gs=Minima->getIntAttr("St",-Maxima->getIntAttr("Gs"));
 ko=Minima->getIntAttr("St",-Maxima->getIntAttr("Ko"));
 in=Minima->getIntAttr("St",-Maxima->getIntAttr("In"));
 zt=Minima->getIntAttr("St",-Maxima->getIntAttr("Zt"));
 sb=Minima->getIntAttr("St",-Maxima->getIntAttr("Sb"));
 au=Minima->getIntAttr("St",-Maxima->getIntAttr("Au"));
 
 const Tag *Modifikation=tag->find("Modifikation");
 if (!Modifikation) Modifikation=tag;
 lpbasis=Modifikation->getIntAttr("LP_Basis");
 ap_grad=Modifikation->getIntAttr("APproGrad");
 m_abb=Modifikation->getIntAttr("Abwehr");
 gestalt=Modifikation->getIntAttr("Gestalt");

 const Tag *Resistenzen=Modifikation->find("Resistenzen");
 if (!Resistenzen) Resistenzen=tag;
 m_psy=Resistenzen->getIntAttr("psy");
 m_phs=Resistenzen->getIntAttr("phs");
 m_phk=Resistenzen->getIntAttr("phk");

 const Tag *Alter=tag->find("Alter");
 if (Alter) alter=Alter->getIntAttr("AnzahlWürfel");
 else alter=1;

 const Tag *Groesse=tag->find("Größe");
 if (!Groesse)
 {  groesse_f=2;
    groesse_w=20;
    groesse_s=150;
 }
 else
 {  groesse_f=Groesse->getIntAttr("AnzahlWürfel");
    groesse_w=Groesse->getIntAttr("ArtWürfel");
    groesse_s=Groesse->getIntAttr("Addiere");
 }
 
 const Tag *Bewegungsweite=tag->find("Bewegungsweite");
 if (Bewegungsweite) 
 {  b_f=Bewegungsweite->getIntAttr("AnzahlWürfel");
    b_s=Bewegungsweite->getIntAttr("Addiere");
 }
 else { b_f=4; b_s=16; }
 
 FOR_EACH_CONST_TAG_OF(i,*tag,"Typ")
    vec_typen.push_back(st_spez(i->getAttr("Name"),i->getIntAttr("MaximalerGrad")));
}


Spezies_All::Spezies_All(Gtk::ProgressBar *progressbar)
{
 const Tag *spezies=xml_data->find("SpeziesListe");
 if (spezies)
 {  Tag::const_iterator b=spezies->begin(),e=spezies->end();
    double size=e-b;
    FOR_EACH_CONST_TAG_OF_5(i,*spezies,b,e,"Spezies")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
       list_All.push_back(cH_Spezies(&*i));
    }
 }   
 ProgressBar::set_percentage(progressbar,1);
}

bool Spezies::Typ_erlaubt(std::string typ) const
{
  for(std::vector<st_spez>::const_iterator i=vec_typen.begin();i!=vec_typen.end();++i)
    if(i->typen == typ) return true ;
  return false;
}

bool operator==(gpointer data,const cH_Spezies &s)
{  return *(static_cast<Spezies*>(data))==*s;
}
