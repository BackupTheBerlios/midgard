/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

#include "Zufall.hh"
#include "Sprache.hh"
#include "WaffeGrund.hh"
#include "class_lernpunkte.hh"

void Zufall::Lernschema()
{
  Lernpunkte lernpunkte;
  Lernpunkte_wuerfeln(lernpunkte,Aben,random);
  st_LL FAUWZ_Listen=getLernlisten();

  Lernpunkte_verteilen(FAUWZ_Listen.Fach,lernpunkte.Fach());
  Lernpunkte_verteilen(FAUWZ_Listen.Allg,lernpunkte.Allgemein());
  Lernpunkte_verteilen(FAUWZ_Listen.Unge,lernpunkte.Unge());
  Lernpunkte_verteilen(FAUWZ_Listen.Waff,lernpunkte.Waffen());
  Lernpunkte_verteilen(FAUWZ_Listen.Zaub,lernpunkte.Zauber());
}


std::vector<MidgardBasicElement_mutable> List_to_Vector(std::list<MidgardBasicElement_mutable> L)
{
  std::vector<MidgardBasicElement_mutable> V;
  for(std::list<MidgardBasicElement_mutable>::const_iterator i=L.begin();i!=L.end();++i)
   {
     V.push_back(*i);
   }
  return V;
}

void Zufall::Lernpunkte_verteilen(std::list<MidgardBasicElement_mutable> L,int lp)
{
reloop:
  L.sort(MidgardBasicElement_mutable::sort(MidgardBasicElement_mutable::sort::LERNPUNKTE));
  std::vector<MidgardBasicElement_mutable> V=List_to_Vector(L);
  while(lp>0)
   {
     if(V.begin()==V.end()) break;
     int i;
     if(V[0].Lernpunkte()==0) i=0;  // damit Fertigkeiten mit '0' Lernpunkten gelernt werden
     else i=random.integer(0,V.size()-1);
      
     MidgardBasicElement_mutable M=V[i];

     // Vorraussetzungen?
     if((M->What()==MidgardBasicElement::FERTIGKEIT || M->What()==MidgardBasicElement::WAFFE)
          && !M->Voraussetzung(Aben,false))  continue;
    

     if(M->What()==MidgardBasicElement::FERTIGKEIT) 
       {  cH_Fertigkeit(M)->get_region_lp(lp,hauptfenster); 
          if (M->Name()=="Muttersprache")
             Sprache::setErfolgswertMuttersprache(M,Aben.getWerte().In(),cH_Fertigkeit(M)->AttributBonus(Aben->getWerte()));
          else if(M->Name()=="Gastlandsprache")
             Sprache::setErfolgswertGastlandsprache(M,Aben.getWerte().In());
       }
cout << "lp="<<lp<<'\t'<<M.Lernpunkte()<<'\t'<<M->Name()<<'\t'<<M.Erfolgswert()<<'\n';

     if(M.Lernpunkte()<=lp)
      {
       if(M->What()==MidgardBasicElement::FERTIGKEIT)
        {
          if(M.ist_gelernt(Aben.List_Fertigkeit())) continue;
          Aben.List_Fertigkeit().push_back(M);
        }
       if(M->What()==MidgardBasicElement::WAFFE)
        {
          if(M.ist_gelernt(Aben.List_Waffen())) continue;
          Aben.List_Waffen().push_back(M);
          Aben.List_WaffenGrund().push_back(MidgardBasicElement_mutable(&*cH_WaffeGrund(cH_Waffe(M)->Grundkenntnis())));
          Aben.List_WaffenGrund().sort(MidgardBasicElement_mutable::sort(MidgardBasicElement_mutable::sort::NAME));
          Aben.List_WaffenGrund().unique();
        }
       if(M->What()==MidgardBasicElement::ZAUBER)
        {
          if(M.ist_gelernt(Aben.List_Zauber())) continue;
          Aben.List_Zauber().push_back(M);
        }
       lp-=M.Lernpunkte();
       L.remove(M);
       goto reloop;
      }
   }  
}



Zufall::st_LL Zufall::getLernlisten()
{
   
  st_LL FAUWZ_Listen=st_LL( LL.getMBEm(Aben,LernListen::lFach,0,0,"Fach"),
                            LL.getMBEm(Aben,LernListen::lAllg,0,0,"Allg"),
                            LL.getMBEm(Aben,LernListen::lUnge,0,0,"Unge"),
                            LL.getMBEm(Aben,LernListen::lWaff,0,0,"Waff"),
                            LL.getMBEm(Aben,LernListen::lZaub,0,0,"Zaub"));

  return FAUWZ_Listen;
}



void Zufall::Lernpunkte_wuerfeln(Lernpunkte &lernpunkte, VAbenteurer &A,Random &random)
{
  //Speziesspezifische Fertigkeiten
  int lpspezies=0;
  A.List_Fertigkeit()=A.getWerte().Spezies()->getFertigkeiten(lpspezies,A.getWerte());

  int fachlern=random.integer(1,6)+random.integer(1,6);
  lernpunkte.setFach(fachlern - lpspezies);
  lernpunkte.setAllgemein(random.integer(1,6)+1);
  lernpunkte.setUnge(random.integer(1,6));
  if (A.Typ2()->Short()=="") lernpunkte.setWaffen(random.integer(1,6)+random.integer(1,6));
  else                     lernpunkte.setWaffen(random.integer(1,6)+1); // Doppelcharakter
  if (A.Typ1()->is_mage() && A.Typ2()->Short()=="")
      lernpunkte.setZauber(random.integer(1,6)+random.integer(1,6));
  if (A.Typ2()->is_mage() && A.Typ2()->Short()!="") 
      lernpunkte.setZauber(random.integer(1,6)+1);


  int age = (lernpunkte.Allgemein() + lernpunkte.Unge()
             + lernpunkte.Fach()
             + lernpunkte.Waffen() + lernpunkte.Zauber())/4+16;
  A.getWerte().setAlter( age * A.getWerte().Spezies()->AlterFaktor());

}


