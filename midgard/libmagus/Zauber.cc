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
#include "Typen.hh"
#include <xml.h>
#include "zufall.h"
#include <Misc/itos.h>
#include "Abenteurer.hh"
#include <iostream>
#include <Misc/germanstring.h>

bool cH_Zauber::sort::operator() (MBEmlt _x,MBEmlt _y) const
{  cH_Zauber x(_x->getMBE());
   cH_Zauber y(_y->getMBE());
   switch(es) {
               case(NAME) : return germanstring(x->Name()) < germanstring(y->Name())  ;
               case(STUFE): return x->Stufe() < y->Stufe();
               case(URSPRUNG): return germanstring(x->Ursprung()) < germanstring(y->Ursprung()) ;
   }
   return false;
}

int Zauber::iStufe() const 
{  if (Stufe()=="groß") return 6; else return atoi(Stufe().c_str()); }

cH_Zauber::cache_t cH_Zauber::cache;

cH_Zauber::cH_Zauber(const std::string& name, bool create)
{
 cH_Zauber *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  std::cerr << "Zauber '" << name << "' nicht im Cache\n";
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
{*this=cH_Zauber(new Zauber(*tag));
 cache.Register(tag->getAttr("Name"),*this);
}

void Zauber::get_Zauber(const Tag &t)
{
    ursprung=t.getAttr("Ursprung");
    kosten=t.getIntAttr("Lernkosten");
    stufe=t.getAttr("Grad");
    spruchrolle=t.getBoolAttr("Spruchrolle");
    region=t.getAttr("Region");
    region_zusatz=t.getAttr("RegionZusatz");
    zauberart=t.getAttr("Zauberart");
    element=t.getAttr("Element");
    ap=t.getAttr("AP");;
    art=t.getAttr("Typ");
    zauberdauer=t.getAttr("Zauberdauer");
    reichweite=t.getAttr("Reichweite");
    wirkungsziel=t.getAttr("Wirkungsziel");
    wirkungsbereich=t.getAttr("Wirkungsbereich");
    wirkungsdauer=t.getAttr("Wirkungsdauer");
    material=t.getAttr("Material");
    agens=t.getAttr("Agens");
    prozess=t.getAttr("Prozess");
    reagens=t.getAttr("Reagens");
    nsc_only=t.getBoolAttr("NSC_only",false);
    
    enum_zusatz=MidgardBasicElement::eZusatz(t.getIntAttr("Zusätze",ZNone));

    FOR_EACH_CONST_TAG_OF(i,t,"Zusätze")
      Vzusatz.push_back(st_zusatz(i->getAttr("Name"),i->getAttr("Typ"),
                         i->getAttr("Region"),i->getAttr("RegionZusatz"),""));
                               
    FOR_EACH_CONST_TAG_OF(i,t,"AgensTyp")
         map_typ_agens[cH_Typen(i->getAttr("Typ"),true)]=i->getAttr("Agens");

    FOR_EACH_CONST_TAG_OF(i,t,"regionaleBesonderheit")
         VAusnahmen.push_back(st_ausnahmen(i->getAttr("Herkunft"),
                              i->getAttr("Spezies"),
                              i->getAttr("Typ"),
                              i->getAttr("Beruf"), //wird nicht ausgewertet
                              i->getAttr("Stand"),
                              i->getAttr("Standard")));
}

void Zauber::load(const Tag &t)
{  get_Zauber(t); get_map_typ(t); EP_steigern("Zauber");
}

Zauber::Zauber(const Tag &t)
      : MidgardBasicElement(t.getAttr("Name")),spruchrolle_faktor(1)
{  load(t);
} 

int Zauber::Kosten_eBe(const std::string& pe,const std::string& se) const
{
  double fac; 
    if      (Element() == pe ) fac = 0.5;
    else if (Element() == se ) fac = 1.0;
    else fac = 5.0;  // oder vielleicht null?

  return (int)(fac*GrundKosten());
}

int Zauber::Erfolgswert_Z(const Abenteurer &A) const
{
   assert(A.getVTyp().size()==2);
   int ifac=-2;
   std::vector<std::string> standard=Standard(A);
   if (standard[0]=="G" || standard[1]=="G") ifac=0;

   int ispez=0;
   if (A.Typ1()->Short()=="Ma")
      ispez = get_spezial_zauber_for_magier(A,standard[0]);
   if (A.Typ2()->Short()=="Ma") 
      ispez = get_spezial_zauber_for_magier(A,standard[1]);

   int erf = A.getWerte().Zaubern_wert()+A.getWerte().bo_Za() + ifac + ispez ;
   return erf;
}

int Zauber::get_spezial_zauber_for_magier(const Abenteurer &A,const std::string& standard) const
{
 int ispez=0;
 if (standard!="G" && Agens(A.getVTyp())==A.getWerte().Spezialgebiet()->Spezial()) ispez = 2;
 if (standard!="G" && Prozess()==A.getWerte().Spezialgebiet()->Spezial()) ispez = 2;
 return ispez;
}

std::string Zauber::Agens(const std::vector<cH_Typen> &Typ) const
{
   cH_Typen T=Typ[0];
   if(map_typ_agens[Typ[0]]!="") return map_typ_agens[Typ[0]];
   if(map_typ_agens[Typ[1]]!="") return map_typ_agens[Typ[0]];
   return agens;
}

bool Zauber::spruchrolle_wuerfeln(const Abenteurer &A,std::string &info,const int bonus_lesen_von_zauberschrift) const
{
 Random random;
 int iaus=0;
 
 if ((A.Typ1()->Short()!="Ma" && A.Typ2()->Short()!="Ma") && Art()=="A") 
    iaus=-2;
 // Für Magier:
 std::string standard="";
 if (A.Typ1()->Short()=="Ma") standard=Standard(A)[0]; 
 if (A.Typ2()->Short()=="Ma") standard=Standard(A)[1]; 
 if(standard!="") 
   {
    iaus = get_spezial_zauber_for_magier(A,standard); 
    if (!iaus)
     { if (Art()=="S")  iaus=+1;
       if (Art()=="A")  iaus=-1;  }
   }
 
 int xr=random.integer(1,20);
 int x = xr-iStufe();
 int erf_z = A.getWerte().Zaubern_wert() + A.getWerte().bo_Za() ;
 
 x += iaus;
 x += erf_z;
 x += bonus_lesen_von_zauberschrift;

 info += "Lernversuch von Spruchrolle:\n"
 "gewürfelt  Spruchstufe  Ausnahme/Spezial Erfolgswert  Lesen von Zauberschrift  Gesamtergebnis\n     "
      +itos(xr)+  "            -"+itos(iStufe())+"               "
      +itos(iaus)+"             "+itos(erf_z)   +"               "+itos0p(bonus_lesen_von_zauberschrift,0,true)
      +"       =       "+ itos(x)+"\n";
 if (x>=20) return true;
 else return false;
}

cH_Zauber cH_Zauber::load(const Tag &t,bool &is_new)
{  cH_Zauber *res=cache.lookup(t.getAttr("Name"));
   if (!res)
   {  cH_Zauber r2=new Zauber(t);
      is_new=true;
      cache.Register(t.getAttr("Name"),r2);
      return r2;
   }
   else 
   {  const_cast<Zauber&>(**res).load(t);
      return *res;
   }
}

Zauber_All::Zauber_All()
{
#if 0
 const Tag *zauber=xml_data->find("Zauber");
 if (!zauber)
    std::cerr << "<Zauber><Spruch/>... nicht gefunden\n";
 else
 {  Tag::const_iterator b=zauber->begin(),e=zauber->end();
    FOR_EACH_CONST_TAG_OF_5(i,*zauber,b,e,"Spruch")
    {  
// warum sowas?
//    die Klasse cH_Zauber enthält den Cache, erzeuge ich nur einen Zauber, so
//    wird er nicht in den Cache (nach Namen) aufgenommen.
//    Ich brauche aber einen cH_MidgardBasicElement, daher bilde ich einen
//    Zauber* um danach (aus dem ebenfalls MidgardBasicElement*) ein 
//    cH_MidgardBasicElement zu machen. Wow.
       list_All.push_back(&*(cH_Zauber(&*i)));
    }
 }
#endif 
}

void Zauber_All::load(const Tag &t)
{  bool is_new=false;
   cH_Zauber z=cH_Zauber::load(t,is_new);
   // das &* dient dazu um aus einem cH_Zauber ein cH_MBE zu machen
   if (is_new) list_All.push_back(&*z);
}
