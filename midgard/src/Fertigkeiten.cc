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
#include <LernListen.hh>

cH_Fertigkeit::cache_t cH_Fertigkeit::cache;

cH_Fertigkeit::cH_Fertigkeit(const std::string& name, bool create)
{
 cH_Fertigkeit *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  std::cerr << "Fertigkeit '" << name << "' nicht im Cache\n";
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
//  erfolgswert=anfangswert; //Defaultwert
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

    FOR_EACH_CONST_TAG_OF(i,*tag,"Voraussetzungen_2")
      vec_voraussetzung.push_back(i->getAttr("Name"));

    FOR_EACH_CONST_TAG_OF(i,*tag,"Lernpunkte_Herkunft")
      vec_region_lp.push_back(st_region_lern(i->getAttr("Herkunft"),
            i->getIntAttr("LP_Stadt"),i->getIntAttr("LP_Land")));

    FOR_EACH_CONST_TAG_OF(i,*tag,"Zusätze")
      Vzusatz.push_back(st_zusatz(i->getAttr("Name"),i->getAttr("Typ"),
                        i->getAttr("Region"),i->getAttr("RegionZusatz"),""));

    FOR_EACH_CONST_TAG_OF(i,*tag,"regionaleBesonderheit")
         VAusnahmen.push_back(st_ausnahmen(i->getAttr("Herkunft"),
                              i->getAttr("Spezies"),
                              i->getAttr("Typ"),
                              i->getAttr("Beruf"),
                              i->getAttr("Stand"),
                              i->getAttr("Standard")));

    FOR_EACH_CONST_TAG_OF(i,*tag,"Besitz")
      {
         e_pos epos;
         std::string pos=i->getAttr("Position");
         if(pos=="Besitz") epos=Besitz;
         else if(pos=="Rucksack") epos=Rucksack;
         else {std::cerr <<"Falsche Position für "<<Name()<<'\n'; continue;}
         vec_Besitz.push_back(st_besitz(i->getAttr("Name"),
                              i->getIntAttr("Min"),
                              epos));
      }
}

bool Fertigkeit::Voraussetzung(const Abenteurer &A,bool anzeigen) const 
{ 
 const Grundwerte &Werte=A.getWerte();
 // Mindestwerte
 if(voraussetzung.st > 0 && voraussetzung.st > Werte.St()) return false;
 if(voraussetzung.gw > 0 && voraussetzung.gw > Werte.Gw()) return false;
 if(voraussetzung.gs > 0 && voraussetzung.gs > Werte.Gs()) return false;
 if(voraussetzung.ko > 0 && voraussetzung.ko > Werte.Ko()) return false;
 if(voraussetzung.in > 0 && voraussetzung.in > Werte.In()) return false;
 if(voraussetzung.zt > 0 && voraussetzung.zt > Werte.Zt()) return false;
 if(voraussetzung.au > 0 && voraussetzung.au > Werte.Au()) return false;
 if(voraussetzung.pa > 0 && voraussetzung.pa > Werte.pA()) return false;
 if(voraussetzung.sb > 0 && voraussetzung.sb > Werte.Sb()) return false;

 // Höchstwerte
 if(voraussetzung.st < 0 && -voraussetzung.st < Werte.St()) return false;
 if(voraussetzung.gw < 0 && -voraussetzung.gw < Werte.Gw()) return false;
 if(voraussetzung.gs < 0 && -voraussetzung.gs < Werte.Gs()) return false;
 if(voraussetzung.ko < 0 && -voraussetzung.ko < Werte.Ko()) return false;
 if(voraussetzung.in < 0 && -voraussetzung.in < Werte.In()) return false;
 if(voraussetzung.zt < 0 && -voraussetzung.zt < Werte.Zt()) return false;
 if(voraussetzung.au < 0 && -voraussetzung.au < Werte.Au()) return false;
 if(voraussetzung.pa < 0 && -voraussetzung.pa < Werte.pA()) return false;
 if(voraussetzung.sb < 0 && -voraussetzung.sb < Werte.Sb()) return false;

 if(anzeigen) return true;

 const std::list<MBEmlt> &list_Fertigkeit=A.List_Fertigkeit();
 const std::list<MBEmlt> &list_Waffen=A.List_Waffen();
 std::list<MBEmlt> L=list_Fertigkeit;
 for(std::list<MBEmlt>::const_iterator j=list_Waffen.begin();j!=list_Waffen.end();++j)
   L.push_back(*j);
       
 std::vector<std::string> VF=vec_voraussetzung;
FertEnd:
 for(std::vector<std::string>::iterator i=VF.begin();i!=VF.end();++i)
  {
    for(std::list<MBEmlt>::const_iterator j=L.begin();j!=L.end();++j)
     {
      if((*i)==(*(*j))->Name()) 
       { VF.erase(i); 
         goto FertEnd;
       }
     }
    return false;
  }
  if(Name()=="Winden" && A.getWerte().Gestalt() != "schlank") return false;
  return true;
}


MidgardBasicElement::eZusatz Fertigkeit::ZusatzEnum(const std::vector<cH_Typen>& Typ) const
{
  if(Name()=="Abrichten" && (Typ[0]->Short()=="Tm" || Typ[1]->Short()=="Tm" ||
                             Typ[0]->Short()=="Wi" || Typ[1]->Short()=="Wi"))
     return ZNone;
  return enum_zusatz;
}

int Fertigkeit::FErfolgswert(const Abenteurer &a,const MBEmlt &mbem) const
{
  if(Name()=="Trinken" && a.getWerte().Spezies()->Name()!="Zwerg") 
      return mbem->Erfolgswert()+a.getWerte().Ko()/10;
  if(Name()=="Berserkergang") return mbem->Erfolgswert()-a.getWerte().Wk()/5;
  else return mbem->Erfolgswert();
}

//int Fertigkeit::MaxErfolgswert(const Grundwerte& w,const std::vector<cH_Typen>& Typ) const
int Fertigkeit::MaxErfolgswert(const Abenteurer& A) const
{
//cout << Name()<<" Maximaler Erfolgswert = "<<maxerfolgswert<<'+'
//  <<AttributBonus(w)<<" Attribut = "<<Attribut()<<'\n';
  return maxerfolgswert + AttributBonus(A.getWerte());
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


void Fertigkeit::get_region_lp(int &lp,const Abenteurer& A,const Datenbank &D) const
{
  for(std::vector<st_region_lern>::const_iterator i=vec_region_lp.begin();i!=vec_region_lp.end();++i)
   {
     if(!LernListen(D).region_check(i->region)) continue;
     if(A.getWerte().Herkunft()->Name()==i->region)
       {
         if     (A.getWerte().Stadt_Land()==Enums::Land  ) lp=i->lp_land;
         else if(A.getWerte().Stadt_Land()==Enums::Stadt ) lp=i->lp_stadt;
       }
   }
}


Fertigkeiten_All::Fertigkeiten_All()
{
 const Tag *fertigkeiten=xml_data->find("Fertigkeiten");
 if (!fertigkeiten)
    std::cerr << "<Fertigkeiten><Fertigkeit/>... nicht gefunden\n";
 else
 {  Tag::const_iterator b=fertigkeiten->begin(),e=fertigkeiten->end();
    for (Tag::const_iterator i=fertigkeiten->find(b,"Fertigkeit");
    		i!=e;	i=fertigkeiten->find(i+1,"Fertigkeit"))
    {  
// warum sowas?
//    die Klasse cH_Fertigkeit enthält den Cache, erzeuge ich nur eine Fertigkeit, so
//    wird sie nicht in den Cache (nach Namen) aufgenommen.
//    Ich brauche aber einen cH_MidgardBasicElement, daher bilde ich einen
//    Fertigkeit* um danach (aus dem ebenfalls MidgardBasicElement*) ein 
//    cH_MidgardBasicElement zu machen. Wow.
       list_All.push_back(&*(cH_Fertigkeit(&*i)));
    }
 }
}  


