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

#include "Zauber.hh"
#include "midgard_CG.hh"
#include "Typen.hh"
#include <xml.h>
#include "ProgressBar.h"

cH_Zauber::cache_t cH_Zauber::cache;

cH_Zauber::cH_Zauber(const std::string& name, bool create)
{
 cH_Zauber *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  cerr << "Zauber '" << name << "' nicht im Cache\n";
  if (create)
  {  static Tag t2("Spruch"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Name",name);
     t2.setAttr("Grad","?");
     t2.setAttr("Typ","?");
     t2.setAttr("Ursprung","?");
     t2.setAttr("Zauberdauer","?");
     t2.setAttr("Wirkungsziel","?");
     t2.setAttr("Wirkungsbereich","?");
     // Wirkungsdauer, Reichweite ???
     *this=cH_Zauber(&t2);
  }
  else throw NotFound();
  }
}

cH_Zauber::cH_Zauber(const Tag *tag)
{*this=cH_Zauber(new Zauber(tag));
 cache.Register(tag->getAttr("Name"),*this);
}

void Zauber::get_Zauber()
{
 assert(tag);
    ursprung=tag->getAttr("Ursprung");
    kosten=tag->getIntAttr("Lernkosten");
    stufe=tag->getAttr("Grad");
    spruchrolle=tag->getBoolAttr("Spruchrolle");
    region=tag->getAttr("Region");
    zauberart=tag->getAttr("Zauberart");
    element=tag->getAttr("Element");
    ap=tag->getAttr("AP");;
    art=tag->getAttr("Typ");
    zauberdauer=tag->getAttr("Zauberdauer");
    reichweite=tag->getAttr("Reichweite");
    wirkungsziel=tag->getAttr("Wirkungsziel");
    wirkungsbereich=tag->getAttr("Wirkungsbereich");
    wirkungsdauer=tag->getAttr("Wirkungsdauer");
    material=tag->getAttr("Material");
    agens=tag->getAttr("Agens");
    prozess=tag->getAttr("Prozess");
    reagens=tag->getAttr("Reagens");
    enum_zusatz=MidgardBasicElement::eZusatz(tag->getIntAttr("Zusätze",ZNone));

    FOR_EACH_CONST_TAG_OF(i,*tag,"Zusätze")
         Vzusatz.push_back(i->getAttr("Name"));
}

int Zauber::Kosten_eBe(const std::string& pe,const std::string& se) const
{
  double fac; 
    if      (Element() == pe ) fac = 0.5;
    else if (Element() == se ) fac = 1.0;
    else fac = 5.0;  // oder vielleicht null?

  return (int)(fac*GrundKosten());
}

int Zauber::Erfolgswert_Z(const vector<cH_Typen>& Typ,const Grundwerte& Werte,const Ausnahmen& ausnahmen) const
{
   assert(Typ.size()==2);
   int ifac=-2;
   vector<std::string> standard=Standard(Typ,ausnahmen);
   if (standard[0]=="G" || standard[1]=="G") ifac=0;

   int ispez=0;
   if (Typ[0]->Short()=="Ma")
      ispez = get_spezial_zauber_for_magier(Werte,standard[0]);
   if (Typ[1]->Short()=="Ma") 
      ispez = get_spezial_zauber_for_magier(Werte,standard[1]);

//cout << Name()<<' '<<Werte.Zaubern_wert()<<'+'<<Werte.bo_Za()<<'+'<<ifac<<'+'<<ispez<<'=';
   int erf = Werte.Zaubern_wert()+Werte.bo_Za() + ifac + ispez ;
//cout << erf<<'\n';
   return erf;
}

int Zauber::get_spezial_zauber_for_magier(const Grundwerte& Werte,const std::string& standard) const
{
 int ispez=0;
 if (standard!="G" && Agens()==Werte.Spezialgebiet()->Spezial()) ispez = 2;
 if (standard!="G" && Prozess()==Werte.Spezialgebiet()->Spezial()) ispez = 2;
 return ispez;
}


Zauber_All::Zauber_All(Gtk::ProgressBar *progressbar)
{
 const Tag *zauber=xml_data->find("Zauber");
 if (!zauber)
    cerr << "<Zauber><Spruch/>... nicht gefunden\n";
 else
 {  Tag::const_iterator b=zauber->begin(),e=zauber->end();
    double size=e-b;
    FOR_EACH_CONST_TAG_OF_5(i,*zauber,b,e,"Spruch")
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
// warum sowas?
//    die Klasse cH_Zauber enthält den Cache, erzeuge ich nur einen Zauber, so
//    wird er nicht in den Cache (nach Namen) aufgenommen.
//    Ich brauche aber einen cH_MidgardBasicElement, daher bilde ich einen
//    Zauber* um danach (aus dem ebenfalls MidgardBasicElement*) ein 
//    cH_MidgardBasicElement zu machen. Wow.
       list_All.push_back(&*(cH_Zauber(&*i)));
    }
 }
 ProgressBar::set_percentage(progressbar,1);
}

