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

enum Zufall::eFAUWZ &operator++(enum Zufall::eFAUWZ &s)
{  return (enum Zufall::eFAUWZ)(++(int&)s);
}


void Zufall::Lernschema()
{
  Lernpunkte lernpunkte;
  Lernpunkte_wuerfeln(lernpunkte,Aben,random);
  st_LL FAUWZ_Listen=getLernlisten();

  if(Aben->Typ1()->getLernpflichtSchrift() || Aben->Typ2()->getLernpflichtSchrift())
   {
     int i=random.integer(1,2);
     if     (i==1) lernpunkte.set_schreiben_pflicht_allg(true);
     else if(i==2) lernpunkte.set_schreiben_pflicht_fach(true);
   }

  for(eFAUWZ i=eWaffen;i<eMAX;++i)
     Lernpunkte_verteilen(i,lernpunkte,FAUWZ_Listen);

  setSpezialwaffe();
  setSpezialgebiet();
}

void Zufall::setSpezialwaffe()
{
  if (!Aben->Typ1()->Spezialwaffe() && !Aben->Typ2()->Spezialwaffe()) return;
  std::list<MBEmlt> L=Aben->List_Waffen();
  std::vector<MBEmlt> V;
  for(std::list<MBEmlt>::const_iterator i=L.begin();i!=L.end();++i)
   {
     if(cH_Waffe(i->getMBE())->Verteidigung()) continue;
     if(cH_Waffe(i->getMBE())->Reichweite().empty() && i->Lernpunkte() > 1) continue;
     if(!cH_Waffe(i->getMBE())->Reichweite().empty() && i->Lernpunkte() > 2) continue; 
     V.push_back(*i);
   }
  if(V.empty()) return;
  int i=random.integer(0,V.size()-1);
  Aben->getWerte().setSpezialisierung(V[i]->Name());      
  Waffe::setSpezialWaffe(Aben->getWerte().Spezialisierung(),Aben->List_Waffen());
}

void Zufall::setSpezialgebiet()
{
  if (!Aben->Typ1()->Spezialgebiet() && !Aben->Typ2()->Spezialgebiet()) return;
  std::vector<std::string> V=LL.getSpezialgebiet(Aben);
  if(V.empty()) return;
  int i=random.integer(0,V.size()-1);
  Aben->getWerte().setSpezialgebiet(cH_Spezialgebiet(V[i]));
}



std::vector<MBEmlt> List_to_Vector(std::list<MBEmlt> L,const VAbenteurer& Aben,int lp)
{
  std::vector<MBEmlt> V;
  for(std::list<MBEmlt>::const_iterator i=L.begin();i!=L.end();++i)
   {
     // Vorraussetzungen?
     if(((*i)->What()==MidgardBasicElement::FERTIGKEIT || (*i)->What()==MidgardBasicElement::WAFFE)
          && !(*i)->Voraussetzung(Aben.getAbenteurer(),false))  continue;
     if(i->Lernpunkte()<=lp)   V.push_back(*i);
   }
  return V;
}

void Zufall:: Lernpunkte_verteilen(const eFAUWZ was,const Lernpunkte &lernpunkte,const st_LL &Listen)
{
 std::list<MBEmlt> L;
 int lp=0;
 bool nachbarland=false;
 bool mutter_12=false,mutter_9=false;
 switch (was) {
   case eWaffen: lp=lernpunkte.Waffen(); L=Listen.Waff; break;
   case eZauber: lp=lernpunkte.Zauber(); L=Listen.Zaub; break;
   case eFach:   lp=lernpunkte.Fach();   L=Listen.Fach; mutter_12=lernpunkte.get_schreiben_pflicht_fach(); break;
   case eAllg:   lp=lernpunkte.Allgemein(); L=Listen.Allg; nachbarland=true; mutter_9=lernpunkte.get_schreiben_pflicht_allg();break;
   case eUnge:   lp=lernpunkte.Unge();   L=Listen.Unge; break;
   default: return;
  }
  std::list<MBEmlt> List_gelerntes;
reloop:
  L.sort(MBEmlt::sort(MidgardBasicElement_mutable::sort::LERNPUNKTEPFLICHT));
  std::vector<MBEmlt> V=List_to_Vector(L,Aben,lp); // Lernpunkte und Vorraussetzungen
  while(lp>0)
   {
     if(V.begin()==V.end()) break;
     if(knows_everything(List_gelerntes,L)) break;
     int i;
     std::vector<MBEmlt>::const_iterator ci;
     try{
     if(V[0].Lernpunkte()==0) i=0;  // Fertigkeiten mit '0' Lernpunkten 
     else if(V[0].Pflicht()) i=0;   // Pflichtfertigkeiten 
     else if(was==eAllg && mutter_9) 
       { 
         i=-1;
         mutter_9=false;
         ci=find(V.begin(),V.end(),MBEmlt(&*cH_Fertigkeit("Schreiben: Muttersprache(+9)")));
//         if(ci==V.end()) assert(!"Muttersprache nicht im Lernschema gefunden");
         if(ci==V.end()) 
            { cerr << "Zu blöd für Schreiben: Muttersprache(+9)\n";
//              const_cast<Lernpunkte&>(lernpunkte).set_schreiben_pflicht_allg(true);
              throw std::exception();
            }
//cout << Aben->Typ1()->Name(Enums::Mann) <<" lernt Allgemeine Sprache\n";
       }
     else if(was==eFach && mutter_12) 
       { 
         i=-1;
         mutter_12=false;
         ci=find(V.begin(),V.end(),MBEmlt(&*cH_Fertigkeit("Schreiben: Muttersprache(+12)")));
         if(ci==V.end()) 
            { cerr << "Zu blöd für Schreiben: Muttersprache(+12)\n";
              const_cast<Lernpunkte&>(lernpunkte).set_schreiben_pflicht_allg(true);
              throw std::exception();
            }
//cout << Aben->Typ1()->Name(Enums::Mann) <<" lernt Fach Sprache\n";
       }
     else i=random.integer(0,V.size()-1);
     }catch(std::exception &e){cerr << e.what()<<'\n';i=random.integer(0,V.size()-1);} 
//if(i==0)
//cout << V[0]->Name()<<'\t'<<V[0].Lernpunkte()<<'\t'<<V[0].Pflicht()<<'\n';
     MBEmlt M=V[0];
     if(i==-1)  M=*ci;
     else       M=V[i];

     if     (was==eFach) M.setLernArt("Fach");
     else if(was==eAllg) M.setLernArt("Allg");
     else if(was==eAllg) M.setLernArt("Unge");


//cout << '\t'<<L.size()<<' '<<M->Name()<<'\n';
     L.remove(M); // Die nächste Methode ändert 'M' daher muß es HIER entfernt werden

     if(M->What()==MidgardBasicElement::FERTIGKEIT) 
       {  cH_Fertigkeit(M.getMBE())->get_region_lp(lp,hauptfenster); 
          if (M->Name()=="Muttersprache")
             Sprache::setErfolgswertMuttersprache(M,Aben->getWerte().In(),cH_Fertigkeit(M.getMBE())->AttributBonus(Aben->getWerte()));
          else if(M->Name()=="Gastlandsprache")
             Sprache::setErfolgswertGastlandsprache(M,Aben->getWerte().In());
       }

     // Fertigkeit/Zauber mit Zusätzen
     if(M->ZusatzEnum(Aben->getVTyp())) 
          M=getZusatz(M->ZusatzEnum(Aben->getVTyp()),M,nachbarland);

     if(M.Lernpunkte()<=lp)
      {
       if(M->What()==MidgardBasicElement::FERTIGKEIT)
        {
          if(M.ist_gelernt(Aben->List_Fertigkeit())) {List_gelerntes.push_back(M);goto reloop;}
          Aben->List_Fertigkeit().push_back(M);
        }
       else if(M->What()==MidgardBasicElement::SPRACHE)
        {
          if(M.ist_gelernt(Aben->List_Sprache())) {List_gelerntes.push_back(M);goto reloop;}
          Aben->List_Sprache().push_back(M);
        }
       else if(M->What()==MidgardBasicElement::SCHRIFT)
        {
          if(M.ist_gelernt(Aben->List_Schrift())) {List_gelerntes.push_back(M);goto reloop;}
          Aben->List_Schrift().push_back(M);
        }
       else if(M->What()==MidgardBasicElement::WAFFE)
        {
          if(M.ist_gelernt(Aben->List_Waffen())) {List_gelerntes.push_back(M);goto reloop;}
          Aben->List_Waffen().push_back(M);
          Aben->List_WaffenGrund().push_back(MBEmlt(&*cH_WaffeGrund(cH_Waffe(M.getMBE())->Grundkenntnis())));
          Aben->List_WaffenGrund().sort(MBEmlt::sort(MidgardBasicElement_mutable::sort::NAME));
          Aben->List_WaffenGrund().unique();
        }
       else if(M->What()==MidgardBasicElement::ZAUBER)
        {
          if(M.ist_gelernt(Aben->List_Zauber())) {List_gelerntes.push_back(M);goto reloop;}
          Aben->List_Zauber().push_back(M);
        }
       lp-=M.Lernpunkte();
       goto reloop;
      }
   }  
}

bool Zufall::knows_everything(const std::list<MBEmlt> &List_gelerntes,const std::list<MBEmlt> &L)
{
  
  for(std::list<MBEmlt>::const_iterator i=L.begin();i!=L.end();++i)
   {
     std::list<MBEmlt>::const_iterator j;
     j=find(List_gelerntes.begin(),List_gelerntes.end(),*i);
     if(j==List_gelerntes.end()) return false;
   }
  return true;
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



MBEmlt Zufall::getZusatz(MidgardBasicElement::eZusatz was,MBEmlt& MBE,bool nachbarland) const
{
//cout << "Zusatz für "<<MBE->Name()<<'\n';
  std::vector<MidgardBasicElement::st_zusatz> VG;
  switch(was)
   {
//     case MidgardBasicElement::ZHerkunft:
     case MidgardBasicElement::ZUeberleben: VG=LL.getUeberlebenZusatz();break;
     case MidgardBasicElement::ZLand:       VG=LL.getLandZusatz(); break;
     case MidgardBasicElement::ZSprache:    VG=LL.getSprachenZusatz(MBE,Aben,nachbarland); break;
     case MidgardBasicElement::ZSchrift:    VG=LL.getSchriftenZusatz(MBE,Aben); break;
     case MidgardBasicElement::ZWaffe:      VG=LL.getWaffenZusatz(Aben->List_Waffen()); break;
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

  MBEmlt Mtmp=MBE;

  if(was==MidgardBasicElement::ZLand && MBE->Name()=="Landeskunde (Heimat)")
   {
     Mtmp=MBEmlt(&*cH_Fertigkeit("Landeskunde"));
     Mtmp.setZusatz(Aben->getWerte().Herkunft()->Name());
     MBE.setLernArt(MBE.LernArt()+"_Heimat");
   }
  if(was==MidgardBasicElement::ZSprache)
       Mtmp=MBEmlt(&*cH_Sprache(V[i].name));
  else if(was==MidgardBasicElement::ZSchrift)
       Mtmp=MBEmlt(&*cH_Schrift(V[i].name));


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
     std::string art=cH_Waffe(WB.getMBE())->Art2();     
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
     Aben->List_Waffen_besitz().push_back(WB);
     L.remove(WB);
     goto reloop;
   }
}

void Zufall::setBeruf()
{
  std::list<MBEmlt> L=LL.getBeruf(Aben);
  std::vector<MBEmlt> V=List_to_Vector(L,Aben,99);
  if(V.empty()) return;
  int i=random.integer(0,V.size()-1);
  hauptfenster->getChar()->List_Beruf().clear();
  hauptfenster->getChar()->List_Beruf().push_back(V[i]);
  
  BerufsKategorie BKat;
  BKat.wuerfeln(random.integer(1,100));
  std::vector<Beruf::st_vorteil> F=LL.getBerufsVorteil(V[i],BKat,Aben);
  if(F.empty()) return;

  while(true)
   {
     i=random.integer(0,F.size()-1);
     bool zusatz=Beruf::Berufsfertigkeit(Aben,F[i]);
     if(zusatz) 
      {
         MBEmlt M(&*cH_Fertigkeit(F[i].name));
         getZusatz(M->ZusatzEnum(Aben->getVTyp()),M);
      }
     if(F[i].kat==3 || F[i].kat==4) break;
     if(!BKat.kat_IV) break;
     else BKat.kat_IV=false;
   }
}
