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

#include "Beruf.hh"
#include "Grundwerte.hh"
#include "Abenteurer.hh"
#include "ProgressBar.h"
#include "Typen.hh"
#include "itos.h"

cH_Beruf::cache_t cH_Beruf::cache;

cH_Beruf::cH_Beruf(const std::string& name ,bool create)
{
 cH_Beruf *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
  cerr << "Beruf '" << name << "' nicht im Cache\n";
  if (create)
  {  static Tag t2("Beruf"); 
     // note that this Tag is shared ... works well for now
     t2.setAttr("Name",name);
     *this=cH_Beruf(&t2);
  }
  else throw NotFound();
  }
}

cH_Beruf::cH_Beruf(const Tag *tag)
{*this=cH_Beruf(new Beruf(tag));
 cache.Register(tag->getAttr("Name"),*this);
}

void Beruf::get_Beruf()
{
   assert(tag);
   const Tag *Voraussetzungen=tag->find("Voraussetzungen");
   if (!Voraussetzungen) Voraussetzungen=tag; // might as well be empty
   const Tag *Stand=tag->find("Stand");
     region=tag->getAttr("Region");
     region_zusatz=tag->getAttr("RegionZusatz");
     geschlecht=Voraussetzungen->getAttr("Geschlecht");
     if (!Stand) u=v=m=a=true;
     else
     {  u=Stand->getBoolAttr("Unfrei");
        v=Stand->getBoolAttr("Volk");
        m=Stand->getBoolAttr("Mittelschicht");
        a=Stand->getBoolAttr("Adel");
     }
     typ_k=Voraussetzungen->getBoolAttr("K�mpfer");
     typ_z=Voraussetzungen->getBoolAttr("Zauberer");
     stadt=Voraussetzungen->getBoolAttr("Stadt");
     land=Voraussetzungen->getBoolAttr("Land");

    const Tag *Vorteil=tag->find("Vorteil");
    if (Vorteil)
       FOR_EACH_CONST_TAG_OF(i,*Vorteil,"Fertigkeit")
          vorteile.push_back(st_vorteil(i->getAttr("Name"),i->getIntAttr("Wert")));
}


/*
std::string Beruf::get_Vorteile() const
{
  std::string s;
  for(vector<st_vorteil>::const_iterator i=vorteile.begin();i!=vorteile.end();++i)
   {  
     s+= (*i);
     if(i+1!=vorteile.end()) s+=", ";
   }
  return s;
}
*/

bool Beruf::Stand(const std::string& stand) const
{
//cout << "Stand "<<Name()<<' '<<stand<<' '<<u<<'-'<<v<<'-'<<m<<'-'<<a<<'\n';
  if(stand=="Unfrei" && u) return true;
  if(stand=="Volk" && v) return true;
  if(stand=="Mittelschicht" && m) return true;
  if(stand=="Adel" && a) return true;
  return false;
}

bool Beruf::Typ(const vector<cH_Typen>& Typ) const
{
//cout << "Typ  "<<Name()<<' '<<Typ[0]->Beruf()<<' '<<Typ[1]->Beruf()<<' '<<typ_z<<"<->"<<typ_k<<'\n';
  if(Typ[0]->Beruf()=="") return true;
  else if(Typ[0]->Beruf()=="z" && typ_z ) return true; 
  else if(Typ[1]->Beruf()=="z" && typ_z ) return true; 
  else if(Typ[0]->Beruf()=="k" && typ_k ) return true; 
  else if(Typ[1]->Beruf()=="k" && typ_k ) return true; 
  return false;
}


Beruf_All::Beruf_All(Gtk::ProgressBar *progressbar)
{
 const Tag *berufe=xml_data->find("Berufe");
// int count=0;
 if (!berufe)
    cerr << "<Berufe><Beruf/>... nicht gefunden\n";
 else
 {  Tag::const_iterator b=berufe->begin(),e=berufe->end();
    double size=e-b;
    FOR_EACH_CONST_TAG_OF_5(i,*berufe,b,e,"Beruf")
    {  // if (!((++count)&31))
       ProgressBar::set_percentage(progressbar,(i-b)/size);
// warum sowas?
//    die Klasse cH_Beruf enth�lt den Cache, erzeuge ich nur einen Beruf, so
//    wird er nicht in den Cache (nach Namen) aufgenommen.
//    Ich brauche aber einen cH_MidgardBasicElement, daher bilde ich einen
//    Beruf* um danach (aus dem ebenfalls MidgardBasicElement*) ein 
//    cH_MidgardBasicElement zu machen. Wow.
       list_All.push_back(&*(cH_Beruf(&*i)));
    }
 }
 ProgressBar::set_percentage(progressbar,1);
}



std::string BerufsKategorie::wuerfeln(int wurf)
{
 std::string kat=itos(wurf)+" gew�rfelt: ";
 if(wurf<=20) kat+="Kein(e) Beruf/Fertigkeit w�hlbar";
 if(21<=wurf&&wurf<=50)
  { kat+="Eine Fertigkeit aus der Kategorie I w�hlbar";
    kat_I=true; }
 if(51<=wurf&&wurf<=80)
  { kat+="Eine Fertigkeit aus der Kategorie I oder II w�hlbar";
    kat_I=true; 
    kat_II=true;}
 if(81<=wurf&&wurf<=95)
  { kat+="Eine Fertigkeit aus der Kategorie I,II oder III w�hlbar";
    kat_I=true; 
    kat_II=true;
    kat_III=true;}
 if(96<=wurf&&wurf<=100)
  { kat+="Eine Fert. aus der Kat. III oder IV oder zwei aus den Kat. I und II w�hlbar (aber trotzdem nur EIN Beruf)";
    kat_I=true; 
    kat_II=true;
    kat_III=true;
    kat_IV=true; }
 return kat;
}


bool Beruf::Berufsfertigkeit(VAbenteurer& A,st_vorteil F)
{
  if(F.name=="Schmecken+10")  A->getWerte().setSinn("Schmecken",10);
  else if(F.gelernt) // Erfolgswert um eins erh�hen
   {
    if(F.name=="Schreiben: Muttersprache(+12)")
     {for(std::list<MBEmlt>::iterator k=A->List_Schrift().begin();k!=A->List_Schrift().end();++k)
       {
         if((*(*k))->Name()==A->Muttersprache() ) 
            { (*k)->addErfolgswert(1); break  ;  }
       }
     }  
    else
     {for (std::list<MBEmlt>::iterator k=A->List_Fertigkeit().begin();k!=A->List_Fertigkeit().end();++k)
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
     if((*MBE)->ZusatzEnum(A->getVTyp())) return true;
//         lernen_zusatz(MBE->ZusatzEnum(A->getVTyp()),MBE);
     if((*MBE)->Name()!="Landeskunde (Heimat)")
          A->List_Fertigkeit().push_back(MBE);
   }
 return false;
}

