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

#include "Fertigkeiten.hh"
#include "midgard_CG.hh"
#include "Typen.hh"
#include "ProgressBar.h"

cH_Fertigkeit::cache_t cH_Fertigkeit::cache;

cH_Fertigkeit::cH_Fertigkeit(const std::string& name, bool create)
{
 cH_Fertigkeit *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  cerr << "Fertigkeit '" << name << "' nicht im Cache\n";
  const Tag *t=find_Tag("Fertigkeiten","Fertigkeit","Name",name);
  if (t) *this=cH_Fertigkeit(t);
  else if (create)
  {  static Tag t2("Fertigkeit"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Name",name);
     *this=cH_Fertigkeit(&t2);
  }
  else throw NotFound();
  }
}

cH_Fertigkeit::cH_Fertigkeit(const Tag *tag)
{assert(tag);
 *this=cH_Fertigkeit(new Fertigkeit(tag));
 cache.Register(tag->getAttr("Name"),*this);
}

void Fertigkeit::get_Fertigkeit()
{
  assert(tag);
  lern_unge=tag->getIntAttr("Lernpunkte",99); // außergewöhnliche Fertigkeit
  lern_land=tag->getIntAttr("Lernpunkte-Land",99);
  lern_stadt=tag->getIntAttr("Lernpunkte-Stadt",99);
  anfangswert0=tag->getIntAttr("Anfangswert");
  anfangswert=tag->getIntAttr("Erfolgswert");
  ungelernt=tag->getIntAttr("Erfolgswert-ungelernt",-99);
  berufskategorie=tag->getIntAttr("Berufskategorie");
  erfolgswert=anfangswert; //Defaultwert
  kosten=tag->getIntAttr("Lernkosten");
  region=tag->getAttr("Region");
  region_zusatz=tag->getAttr("RegionZusatz");
  attribut=tag->getAttr("Attribut");
  maxunterweisung=tag->getIntAttr("MaximalMitUnterweisung");
  enum_zusatz=eZusatz(tag->getIntAttr("Zusätze",ZNone));
  maxerfolgswert=tag->getIntAttr("Maximalwert");
  const Tag *Voraussetzungen=tag->find("Voraussetzungen");
  if (Voraussetzungen)
     voraussetzung = st_Voraussetzung(Voraussetzungen->getIntAttr("St"),
     		Voraussetzungen->getIntAttr("Gw",Voraussetzungen->getIntAttr("RW")),
     		Voraussetzungen->getIntAttr("Gs",Voraussetzungen->getIntAttr("Ge")),
     		Voraussetzungen->getIntAttr("Ko"),
     		Voraussetzungen->getIntAttr("In"),
     		Voraussetzungen->getIntAttr("Zt"),
     		Voraussetzungen->getIntAttr("Au"),
     		Voraussetzungen->getIntAttr("pA"),
                Voraussetzungen->getIntAttr("Sb"),
                Voraussetzungen->getIntAttr("RW"),
                Voraussetzungen->getAttr("Fertigkeit"));

    FOR_EACH_CONST_TAG_OF(i,*tag,"Zusätze")
      Vzusatz.push_back(i->getAttr("Name"));

    FOR_EACH_CONST_TAG_OF(i,*tag,"regionaleBesonderheit")
         VAusnahmen.push_back(st_ausnahmen(i->getAttr("Herkunft"),
                              i->getAttr("Spezies"),
                              i->getAttr("Typ"),
                              i->getAttr("Beruf"),
                              i->getAttr("Stand"),
                              i->getAttr("Standard")));

}

bool Fertigkeit::Voraussetzungen(const Grundwerte& Werte) const 
{
 if ( voraussetzung.st<=Werte.St() &&
      voraussetzung.gw<=Werte.Gw() &&
      voraussetzung.gs<=Werte.Gs() &&
      voraussetzung.ko<=Werte.Ko() &&
      voraussetzung.in<=Werte.In() &&
      voraussetzung.zt<=Werte.Zt() &&
      voraussetzung.au<=Werte.Au() &&
      voraussetzung.pa<=Werte.pA() &&
      voraussetzung.sb<=Werte.Sb()
     )   
    return true;
 else return false ;
}

std::string Fertigkeit::Pflicht_str() const
{
  if (Pflicht()) return "X"; 
  else return "";
}

MidgardBasicElement::eZusatz Fertigkeit::ZusatzEnum(const vector<cH_Typen>& Typ) const
{
  if(Name()=="Abrichten" && (Typ[0]->Short()=="Tm" || Typ[1]->Short()=="Tm"))
     return ZNone;
  return enum_zusatz;
}

int Fertigkeit::FErfolgswert(const Grundwerte &Werte) const
{
  if(Name()=="Trinken" && Werte.Spezies()->Name()!="Zwerg") 
      return Erfolgswert()+Werte.Ko()/10;
  if(Name()=="Berserkergang") return Erfolgswert()-Werte.Wk()/5;
  else return Erfolgswert();
}

int Fertigkeit::MaxErfolgswert(const Grundwerte& w,const vector<cH_Typen>& Typ) const
{
//cout << Name()<<" Maximaler Erfolgswert = "<<maxerfolgswert<<'+'
//  <<AttributBonus(w)<<" Attribut = "<<Attribut()<<'\n';
  return maxerfolgswert + AttributBonus(w);
}



int Fertigkeit::AttributBonus(const Grundwerte& Werte) const
{
   int b=0;
   if (Attribut()=="St" && Werte.St()>=81) ++b;
   if (Attribut()=="St" && Werte.St()>=96) ++b;
   if (Attribut()=="Gw" && Werte.Gw()>=81) ++b;
   if (Attribut()=="Gw" && Werte.Gw()>=96) ++b;
   if (Attribut()=="Gs" && Werte.Gs()>=81) ++b;
   if (Attribut()=="Gs" && Werte.Gs()>=96) ++b;
   if (Attribut()=="Ko" && Werte.Ko()>=81) ++b;
   if (Attribut()=="Ko" && Werte.Ko()>=96) ++b;
   if (Attribut()=="In" && Werte.In()>=81) ++b;
   if (Attribut()=="In" && Werte.In()>=96) ++b;
   if (Attribut()=="Zt" && Werte.Zt()>=81) ++b;
   if (Attribut()=="Zt" && Werte.Zt()>=96) ++b;
   if (Attribut()=="Sb" && Werte.Sb()>=81) ++b;
   if (Attribut()=="Sb" && Werte.Sb()>=96) ++b;
   if (Attribut()=="pA" && Werte.pA()>=81) ++b;
   if (Attribut()=="pA" && Werte.pA()>=96) ++b;
 return b;
}

Fertigkeiten_All::Fertigkeiten_All(Gtk::ProgressBar *progressbar)
{
 const Tag *fertigkeiten=xml_data->find("Fertigkeiten");
 if (!fertigkeiten)
    cerr << "<Fertigkeiten><Fertigkeit/>... nicht gefunden\n";
 else
 {  Tag::const_iterator b=fertigkeiten->begin(),e=fertigkeiten->end();
    double size=e-b;
    for (Tag::const_iterator i=fertigkeiten->find(b,"Fertigkeit");
    		i!=e;	i=fertigkeiten->find(i+1,"Fertigkeit"))
    {  ProgressBar::set_percentage(progressbar,(i-b)/size);
// warum sowas?
//    die Klasse cH_Fertigkeit enthält den Cache, erzeuge ich nur eine Fertigkeit, so
//    wird sie nicht in den Cache (nach Namen) aufgenommen.
//    Ich brauche aber einen cH_MidgardBasicElement, daher bilde ich einen
//    Fertigkeit* um danach (aus dem ebenfalls MidgardBasicElement*) ein 
//    cH_MidgardBasicElement zu machen. Wow.
       list_All.push_back(&*(cH_Fertigkeit(&*i)));
    }
 }
 ProgressBar::set_percentage(progressbar,1);
}  


