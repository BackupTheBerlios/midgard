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
#include "Schrift.hh"
#include "Land.hh"
#include "WaffeGrund.hh"
#include "class_lernpunkte.hh"

void Zufall::Lernschema()
{
  Lernpunkte lernpunkte;
  Lernpunkte_wuerfeln(lernpunkte,Aben,random);
  st_LL FAUWZ_Listen=getLernlisten();

  Lernpunkte_verteilen(FAUWZ_Listen.Waff,lernpunkte.Waffen());
  setSpezialwaffe();
  Lernpunkte_verteilen(FAUWZ_Listen.Zaub,lernpunkte.Zauber());
  setSpezialgebiet();
  Lernpunkte_verteilen(FAUWZ_Listen.Fach,lernpunkte.Fach());
  Lernpunkte_verteilen(FAUWZ_Listen.Allg,lernpunkte.Allgemein(),false);
  Lernpunkte_verteilen(FAUWZ_Listen.Unge,lernpunkte.Unge());
}

void Zufall::setSpezialwaffe()
{
  if (!Aben->Typ1()->Spezialwaffe() && !Aben->Typ2()->Spezialwaffe()) return;
  std::list<MidgardBasicElement_mutable> L=Aben->List_Waffen();
  std::vector<MidgardBasicElement_mutable> V;
  for(std::list<MidgardBasicElement_mutable>::const_iterator i=L.begin();i!=L.end();++i)
   {
     if(cH_Waffe(*i)->Verteidigung()) continue;
     if(cH_Waffe((*i))->Reichweite().empty() && i->Lernpunkte() > 1) continue;
     if(!cH_Waffe((*i))->Reichweite().empty() && i->Lernpunkte() > 2) continue; 
     V.push_back(*i);
   }
  int i=random.integer(0,V.size()-1);
  Aben->getWerte().setSpezialisierung(V[i]->Name());      
  Waffe::setSpezialWaffe(Aben->getWerte().Spezialisierung(),Aben->List_Waffen());
}

void Zufall::setSpezialgebiet()
{
  if (!Aben->Typ1()->Spezialgebiet() && !Aben->Typ2()->Spezialgebiet()) return;

//  Aben->getWerte().setSpezialgebiet();
}



std::vector<MidgardBasicElement_mutable> List_to_Vector(std::list<MidgardBasicElement_mutable> L,const VAbenteurer& Aben,int lp)
{
  std::vector<MidgardBasicElement_mutable> V;
  for(std::list<MidgardBasicElement_mutable>::const_iterator i=L.begin();i!=L.end();++i)
   {
     // Vorraussetzungen?
     if(((*i)->What()==MidgardBasicElement::FERTIGKEIT || (*i)->What()==MidgardBasicElement::WAFFE)
          && !(*i)->Voraussetzung(Aben.getAbenteurer(),false))  continue;
     if(i->Lernpunkte()<=lp)   V.push_back(*i);
   }
  return V;
}

void Zufall::Lernpunkte_verteilen(std::list<MidgardBasicElement_mutable> L,int lp,bool ungew)
{
reloop:
  L.sort(MidgardBasicElement_mutable::sort(MidgardBasicElement_mutable::sort::LERNPUNKTEPFLICHT));
  std::vector<MidgardBasicElement_mutable> V=List_to_Vector(L,Aben,lp); // Lernpunkte und Vorraussetzungen
  while(lp>0)
   {
     if(V.begin()==V.end()) break;
     int i;
     if(V[0].Lernpunkte()==0) i=0;  // Fertigkeiten mit '0' Lernpunkten 
     else if(V[0].Pflicht()) i=0;   // Pflichtfertigkeiten 
     else i=random.integer(0,V.size()-1);

//if(i==0)
//cout << V[0]->Name()<<'\t'<<V[0].Lernpunkte()<<'\t'<<V[0].Pflicht()<<'\n';

     MidgardBasicElement_mutable M=V[i];

     L.remove(M); // Die nächste Methode ändert 'M' daher muß es HIER entfernt werden

     if(M->What()==MidgardBasicElement::FERTIGKEIT) 
       {  cH_Fertigkeit(M)->get_region_lp(lp,hauptfenster); 
          if (M->Name()=="Muttersprache")
             Sprache::setErfolgswertMuttersprache(M,Aben.getWerte().In(),cH_Fertigkeit(M)->AttributBonus(Aben->getWerte()));
          else if(M->Name()=="Gastlandsprache")
             Sprache::setErfolgswertGastlandsprache(M,Aben.getWerte().In());
       }

     // Fertigkeit/Zauber mit Zusätzen
     if(M->ZusatzEnum(Aben->getVTyp())) 
          M=getZusatz(M->ZusatzEnum(Aben->getVTyp()),M);

     if(M.Lernpunkte()<=lp)
      {
       if(M->What()==MidgardBasicElement::FERTIGKEIT)
        {
          if(M.ist_gelernt(Aben.List_Fertigkeit())) continue;
          Aben.List_Fertigkeit().push_back(M);
        }
       else if(M->What()==MidgardBasicElement::SPRACHE)
        {
          if(M.ist_gelernt(Aben.List_Sprache())) continue;
          Aben.List_Sprache().push_back(M);
        }
       else if(M->What()==MidgardBasicElement::SCHRIFT)
        {
          if(M.ist_gelernt(Aben.List_Schrift())) continue;
          Aben.List_Schrift().push_back(M);
        }
       else if(M->What()==MidgardBasicElement::WAFFE)
        {
          if(M.ist_gelernt(Aben.List_Waffen())) continue;
          Aben.List_Waffen().push_back(M);
          Aben.List_WaffenGrund().push_back(MidgardBasicElement_mutable(&*cH_WaffeGrund(cH_Waffe(M)->Grundkenntnis())));
          Aben.List_WaffenGrund().sort(MidgardBasicElement_mutable::sort(MidgardBasicElement_mutable::sort::NAME));
          Aben.List_WaffenGrund().unique();
        }
       else if(M->What()==MidgardBasicElement::ZAUBER)
        {
          if(M.ist_gelernt(Aben.List_Zauber())) continue;
          Aben.List_Zauber().push_back(M);
        }
       lp-=M.Lernpunkte();
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



MidgardBasicElement_mutable Zufall::getZusatz(MidgardBasicElement::eZusatz was,MidgardBasicElement_mutable& MBE,bool ungew) const
{
//cout << "Zusatz für "<<MBE->Name()<<'\n';
  std::vector<MidgardBasicElement::st_zusatz> VG;
  switch(was)
   {
//     case MidgardBasicElement::ZHerkunft:
     case MidgardBasicElement::ZUeberleben: VG=LL.getUeberlebenZusatz();break;
     case MidgardBasicElement::ZLand:       VG=LL.getLandZusatz(); break;
     case MidgardBasicElement::ZSprache:    VG=LL.getSprachenZusatz(MBE,Aben,!ungew); break;
     case MidgardBasicElement::ZSchrift:    VG=LL.getSchriftenZusatz(MBE,Aben); break;
     case MidgardBasicElement::ZWaffe:      VG=LL.getWaffenZusatz(Aben.List_Waffen()); break;
     case MidgardBasicElement::ZTabelle:    VG=MBE->VZusatz(); break;
     default: assert(!"never get here");
   }
  std::vector<MidgardBasicElement::st_zusatz> V;    
  for (std::vector<MidgardBasicElement::st_zusatz>::const_iterator i=VG.begin();i!=VG.end();++i)
   {
     if(hauptfenster->region_check(i->region)) V.push_back(*i);
   }
  if(V.empty()) return MBE;
  int i=random.integer(0,V.size()-1);

  MBE.setZusatz(V[i]);

  MidgardBasicElement_mutable Mtmp=MBE;

  if(was==MidgardBasicElement::ZLand && MBE->Name()=="Landeskunde (Heimat)")
   {
     Mtmp=MidgardBasicElement_mutable(&*cH_Fertigkeit("Landeskunde"));
     Mtmp.setZusatz(Aben.getWerte().Herkunft()->Name());
     MBE.setLernArt(MBE.LernArt()+"_Heimat");
   }
  if(was==MidgardBasicElement::ZSprache)
       Mtmp=MidgardBasicElement_mutable(&*cH_Sprache(V[i].name));
  else if(was==MidgardBasicElement::ZSchrift)
       Mtmp=MidgardBasicElement_mutable(&*cH_Schrift(V[i].name));


  if(MBE != Mtmp)
   {
     Mtmp.setErfolgswert(MBE.Erfolgswert());
     Mtmp.setLernpunkte(MBE.Lernpunkte());
     Mtmp.setLernArt(MBE.LernArt());
     MBE=Mtmp;
   }
  return MBE;
}

std::vector<WaffeBesitz> List_to_Vector(const std::list<WaffeBesitz>& L)
{
  std::vector<WaffeBesitz> V;
  for(std::list<WaffeBesitz>::const_iterator i=L.begin();i!=L.end();++i)
   {
     V.push_back(*i);
   }
  return V;
}

void Zufall::setWaffenBesitz()
{
  std::list<WaffeBesitz> L=LL.getWaffenBesitz(Aben);
  WaffeBesitzLernen wbl=WaffenBesitz_wuerfeln(Aben,random.integer(1,100));

reloop:
  if(wbl.AWaffe() == 0 && wbl.EWaffe() == 0) return;
  std::vector<WaffeBesitz> V=List_to_Vector(L);
  for(std::vector<WaffeBesitz>::const_iterator i=V.begin();i!=V.end();++i)
   {
     int i=random.integer(0,V.size()-1);
     WaffeBesitz WB=V[i];
     std::string art=cH_Waffe(WB)->Art2();     
     if( (art=="E" || art=="W" || art=="V") && wbl.EWaffe()>0)
      {
        wbl.add_EWaffe(-1);
        if(wbl.getMagisch())
          {
            WB.set_av_Bonus(1);
            wbl.setMagisch(false);
          }
      }
     else if(wbl.AWaffe()>0)  wbl.add_AWaffe(-1)  ;  
     else continue;
     Aben.List_Waffen_besitz().push_back(WB);
     L.remove(WB);
     goto reloop;
   }
}
