/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2002-2003 Christof Petig 
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

#include "Beruf.hh"
#include "Grundwerte.hh"
#include "Abenteurer.hh"
#include "Typen.hh"
#include <Misc/itos.h>
#include "NotFound.h"
#include "Ausgabe.hh"

cH_Beruf::cache_t cH_Beruf::cache;

cH_Beruf::cH_Beruf(const std::string& name ,bool create)
{
 cH_Beruf *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  Ausgabe(Ausgabe::Warning, "Beruf '" + name + "' nicht im Cache");
  if (create)
  {  Tag t2("Beruf"); 
     t2.setAttr("Name",name);
     *this=new Beruf(t2);
  }
  else throw NotFound(name);
  }
}

void Beruf::load(const Tag &t)
{
   const Tag *Voraussetzungen=t.find("Voraussetzungen");
   if (!Voraussetzungen) Voraussetzungen=&t; // might as well be empty
   const Tag *Stand=t.find("Stand");
     region=t.getAttr("Region");
     region_zusatz=t.getAttr("RegionZusatz");
     geschlecht=Voraussetzungen->getAttr("Geschlecht");
     if (!Stand) u=v=m=a=true;
     else
     {  u=Stand->getBoolAttr("Unfrei");
        v=Stand->getBoolAttr("Volk");
        m=Stand->getBoolAttr("Mittelschicht");
        a=Stand->getBoolAttr("Adel");
     }
     typ_k=Voraussetzungen->getBoolAttr("Kämpfer");
     typ_z=Voraussetzungen->getBoolAttr("Zauberer");
     stadt=Voraussetzungen->getBoolAttr("Stadt");
     land=Voraussetzungen->getBoolAttr("Land");

    const Tag *Vorteil=t.find("Vorteil");
    if (Vorteil)
       FOR_EACH_CONST_TAG_OF(i,*Vorteil,"Fertigkeit")
          vorteile.push_back(st_vorteil(i->getAttr("Name"),i->getIntAttr("Wert")));
}


bool Beruf::Stand(const std::string& stand) const
{
//cout << "Stand "<<Name()<<' '<<stand<<' '<<u<<'-'<<v<<'-'<<m<<'-'<<a<<'\n';
  if(stand=="Unfrei" && u) return true;
  if(stand=="Volk" && v) return true;
  if(stand=="Mittelschicht" && m) return true;
  if(stand=="Adel" && a) return true;
  return false;
}

bool Beruf::Typ(const std::vector<cH_Typen>& Typ) const
{
//cout << "Typ  "<<Name()<<' '<<Typ[0]->Beruf()<<' '<<Typ[1]->Beruf()<<' '<<typ_z<<"<->"<<typ_k<<'\n';
  if(Typ[0]->Beruf()=="") return true;
  else if(Typ[0]->Beruf()=="z" && typ_z ) return true; 
  else if(Typ[1]->Beruf()=="z" && typ_z ) return true; 
  else if(Typ[0]->Beruf()=="k" && typ_k ) return true; 
  else if(Typ[1]->Beruf()=="k" && typ_k ) return true; 
  return false;
}


Beruf_All::Beruf_All()
{
}



std::string BerufsKategorie::wuerfeln(int wurf)
{
 std::string kat=itos(wurf)+" gewürfelt: ";
 if(wurf<=20) kat+="Kein(e) Beruf/Fertigkeit wählbar";
 if(21<=wurf&&wurf<=50)
  { kat+="Eine Fertigkeit aus der Kategorie I wählbar";
    kat_I=true; }
 if(51<=wurf&&wurf<=80)
  { kat+="Eine Fertigkeit aus der Kategorie I oder II wählbar";
    kat_I=true; 
    kat_II=true;}
 if(81<=wurf&&wurf<=95)
  { kat+="Eine Fertigkeit aus der Kategorie I,II oder III wählbar";
    kat_I=true; 
    kat_II=true;
    kat_III=true;}
 if(96<=wurf&&wurf<=100)
  { kat+="Eine Fert. aus der Kat. III oder IV oder zwei aus den Kat. I und II wählbar (aber trotzdem nur EIN Beruf)";
    kat_I=true; 
    kat_II=true;
    kat_III=true;
    kat_IV=true; }
 return kat;
}


bool Beruf::Berufsfertigkeit(Abenteurer& A,st_vorteil F)
{
  if(F.name=="Schmecken+10")  A.setSinn("Schmecken",10);
  else if(F.gelernt) // Erfolgswert um eins erhöhen
   {
    if(F.name=="Schreiben: Muttersprache(+12)")
     {for(std::list<MBEmlt>::iterator k=A.List_Schrift().begin();k!=A.List_Schrift().end();++k)
       {
         if((*(*k))->Name()==A.Muttersprache() ) 
            { (*k)->addErfolgswert(1); break  ;  }
       }
     }  
    else
     {for (std::list<MBEmlt>::iterator k=A.List_Fertigkeit().begin();k!=A.List_Fertigkeit().end();++k)
       {
         if((*(*k))->Name()==F.name)
           { (*k)->addErfolgswert(1);
             if((*(*k))->What()==MidgardBasicElement::FERTIGKEIT)
                (*k)->setLernArt("Beruf+");
             break;
           }
       }  
     }
   }
  else // neue Fertigkeit
   {
     cH_MidgardBasicElement cMBE(&*cH_Fertigkeit(F.name));
     MBEmlt MBE(cMBE);
     MBE->setLernArt("Beruf");
     MBE->setErfolgswert(F.wert);
     if((*MBE)->ZusatzEnum(A.getVTyp())) return true;
//         lernen_zusatz(MBE->ZusatzEnum(A.getVTyp()),MBE);
     if((*MBE)->Name()!="Landeskunde (Heimat)")
          A.List_Fertigkeit().push_back(MBE);
   }
 return false;
}

Beruf::Beruf(const Tag &t)
      : MidgardBasicElement(t.getAttr("Name")), klasse(),u(),v(),m(),a(),
      	typ_k(), typ_z(), stadt(), land()
{load(t);
}

cH_Beruf cH_Beruf::load(const Tag &t,bool &is_new)
{  cH_Beruf *res=cache.lookup(t.getAttr("Name"));
   if (!res)
   {  cH_Beruf r2=new Beruf(t);
      is_new=true;
      cache.Register(t.getAttr("Name"),r2);
//       cache.Register(t.getAttr("Name_w"),r2); weibliche Bezeichnung?
      return r2;
   }
   else 
   {  const_cast<Beruf&>(**res).load(t);
      return *res;
   }
}

void Beruf_All::load(std::list<cH_MidgardBasicElement> &list,const Tag &t)
{  bool is_new=false;
   cH_Beruf z=cH_Beruf::load(t,is_new);
   // das &* dient dazu um aus einem cH_Beruf ein cH_MBE zu machen
   if (is_new) list.push_back(&*z);
}
