// $Id: Abenteurer.cc,v 1.42 2002/09/21 18:00:13 thoma Exp $            
/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
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

#include "Abenteurer.hh"
//#include "export_common.h"
#include "TagStream.hh"
#include "Preise.hh"
#include "midgard_CG.hh"
#include <Misc/itos.h>
#include <Sprache.hh>
#include <Schrift.hh>
#include "Fertigkeiten_angeboren.hh"
#include "Waffe.hh"
#include "WaffeGrund.hh"
#include "Zauber.hh"
#include "Zauberwerk.hh"
#include "KiDo.hh"
#include "Beruf.hh"


bool Abenteurer::Valid() const
{
  if(Typ.size()!=2) return false;
  return Typ1()->Valid();
}


std::string Abenteurer::STyp() const
{
  if(Typ2()->Name(getWerte().Geschlecht())!="")
   return Typ1()->Name(getWerte().Geschlecht())+"/"+Typ2()->Name(getWerte().Geschlecht());
  else return Typ1()->Name(getWerte().Geschlecht());
  abort(); //never get here
}


const std::string Abenteurer::SErfolgswert(std::string name,const Datenbank &Database) const
{
  pair<int,bool> w=Erfolgswert(name,Database);
  if(w.first==-99) return "";
  if(w.second) return itos(w.first);
  if(!w.second) return "("+itos(w.first)+")";
}

const pair<int,bool> Abenteurer::Erfolgswert(std::string name,const Datenbank &Database) const
{
  for(std::list<MBEmlt>::const_iterator i=list_Fertigkeit.begin();i!=list_Fertigkeit.end();++i)
   {
     if(name==(*i)->Name()) return pair<int,bool>((*i).Erfolgswert(),true); 
   }   
  std::list<st_universell> UF=List_Universell(Database);
  for(std::list<st_universell>::const_iterator i=UF.begin();i!=UF.end();++i)
   {
     if(name==i->mbe->Name()) return pair<int,bool>(i->mbe.Erfolgswert(),false); 
   }   
  return pair<int,bool>(-99,false);
}


const std::list<Abenteurer::st_universell> Abenteurer::List_Universell( const Datenbank &Database) const
{
  std::list<st_universell> UF;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Fertigkeit.begin();i!=Database.Fertigkeit.end();++i)
   {
     cH_Fertigkeit f(*i);
     if(f->Ungelernt()!=-99)
     UF.push_back(MBEmlt(*i));
   }
  cH_MidgardBasicElement werfen(&*cH_Waffe("Werfen"));
  UF.push_back(MBEmlt(werfen));
  UF.push_back(getWerte().Ueberleben());
  UF.sort(sort_universell());

  for(std::list<Abenteurer::st_universell>::iterator i=UF.begin();i!=UF.end();++i)
   {
     int iwert=-99;
     if (i->mbe->What()==MidgardBasicElement::FERTIGKEIT)
      {
        cH_Fertigkeit f(i->mbe.getMBE());
        iwert = f->Ungelernt();
        if(f->Name()==getWerte().Ueberleben()->Name()) iwert=6;
        if (!f->Voraussetzung(*this,true))
            {iwert-=2; i->voraussetzung=false;}
      }
     else if (i->mbe->What()==MidgardBasicElement::WAFFE)
      {
        cH_Waffe f(i->mbe.getMBE());
        iwert = 4+getWerte().bo_An();
        if (!f->Voraussetzung(*this,true))
            {iwert=0; i->voraussetzung=false;}
      }
     if (i->mbe.ist_gelernt(List_Fertigkeit()) || i->mbe.ist_gelernt(List_Waffen()))
          i->gelernt=true;
     else // Erfolgswert nur dann setzen, wenn die Fertigkeit NICHT gelernt ist
          i->mbe.setErfolgswert(iwert);
   }
  return UF;
}

void VAbenteurer::push_back()
{ 
   VA.push_back(st_abenteurer()); 
   ai=--VA.end(); 
}


void VAbenteurer::set_Abenteurer(const Abenteurer& A)
{ 
   for(std::list<st_abenteurer>::iterator i=VA.begin();i!=VA.end();++i)
      if(i->abenteurer==A) ai=i;
}


bool VAbenteurer::unsaved_exist()
{ 
   for(std::list<st_abenteurer>::iterator i=VA.begin();i!=VA.end();++i)
       if(!i->gespeichert) return true;
   return false;
}

void VAbenteurer::delete_empty()
{ 
 reloop:
   ai=--VA.end(); 
   for(std::list<st_abenteurer>::iterator i=VA.begin();i!=VA.end();++i)
    { const Grundwerte &W=i->abenteurer.getWerte(); 
      if(i->gespeichert && W.Name_Abenteurer().empty())
        { VA.erase(i); 
          goto reloop;
        } 
    }
}

void Abenteurer::setAngebFert()
{
  List_Fertigkeit_ang().clear();
  List_Fertigkeit_ang()=getWerte().Spezies()->getAngFertigkeiten();
  List_Zauber()=getWerte().Spezies()->getZauber();
  getWerte().resetSinne();
  std::list<pair<std::string,int> > L=getWerte().Spezies()->getSinne();
  for(std::list<pair<std::string,int> >::const_iterator i=L.begin();i!=L.end();++i) 
       getWerte().setSinn(i->first,i->second);
}

bool Abenteurer::setAngebSinnFert(int wurf,const MBEmlt &MBE)
{
  int wert=MBE.Erfolgswert();
  if     ( 1<=wurf && wurf<= 2) getWerte().setSinnCheck("Sehen",wert);    
  else if( 3<=wurf && wurf<= 4) getWerte().setSinnCheck("Hören",wert);    
  else if( 5<=wurf && wurf<= 6) getWerte().setSinnCheck("Riechen",wert);  
  else if( 7<=wurf && wurf<= 8) getWerte().setSinnCheck("Schmecken",wert);
  else if( 9<=wurf && wurf<=10) getWerte().setSinnCheck("Tasten",wert);
  else if(11<=wurf && wurf<=20) getWerte().setSinn("Sehen",wert);    
  else if(21<=wurf && wurf<=30) getWerte().setSinn("Hören",wert);    
  else if(31<=wurf && wurf<=40) getWerte().setSinn("Riechen",wert);  
  else if(41<=wurf && wurf<=50) getWerte().setSinn("Schmecken",wert);
  else if(51<=wurf && wurf<=60) getWerte().setSinn("Tasten",wert);
  else if(61<=wurf && wurf<=65) getWerte().setSinn("Sechster Sinn",wert);
  else { List_Fertigkeit_ang().push_back(MBE); return false;}
  return true;
}




void Abenteurer::speicherstream(ostream &datei,const Datenbank &Database,const Midgard_Optionen *Optionen)
{
   TagStream ts;
   ts.setEncoding("ISO-8859-1");
   
   Tag &data=ts.push_back(Tag("MAGUS-data"));  

// Vielleicht hier eingegebene Ausrüstung speichern wie in anderen Dateien
// oder ganz unten?
   Tag &Preise=data.push_back(Tag("Preise"));
   for (std::list<cH_Preise>::const_iterator i=Database.preise.begin();i!=Database.preise.end();++i)
   {  if ((*i)->ist_eigener_Artikel())
      {  Tag &k=Preise.push_back(Tag("Kaufpreis"));
         k.setAttr("Ware", (*i)->Name());
         k.setAttr_ne("Art", (*i)->Art());
         k.setAttr_ne("Art2", (*i)->Art2());
         k.setAttr("Preis", dtos((*i)->Kosten()));
         k.setAttr("Währung", (*i)->Einheit());
         k.setAttr("Gewicht", dtos((*i)->Gewicht()));
      }
   }
   
   Tag &Abenteurer=data.push_back(Tag("Midgard-Abenteurer"));
   Abenteurer.setIntAttr("Version",10);

   grundwerte_speichern(Abenteurer);
   Tag &Ausruestung=Abenteurer.push_back(Tag("Ausrüstung"));
   Ausruestung.push_back(Tag("Rüstung", getWerte().Ruestung()->Name()));
   if (!getWerte().Ruestung(1)->Name().empty())
     Ausruestung.push_back(Tag("Rüstung2", getWerte().Ruestung(1)->Name()));
   // Waffen Besitz
   for (std::list<WaffeBesitz>::const_iterator i=List_Waffen_besitz().begin();
//   for (std::list<MBEmlt>::const_iterator i=List_Waffen_besitz().begin();
         i!=List_Waffen_besitz().end();++i)
      {  
//         WaffeBesitz WB(*i) ;
         Tag &w=Ausruestung.push_back(Tag("Waffe"));
         w.setIntAttr("Erfolgswert", i->Erfolgswert());
         w.setAttr("Bezeichnung", i->AliasName());
         w.setIntAttr_nn("AngriffVerteidigung_Bonus", i->av_Bonus());
         w.setIntAttr_nn("SchadenLebenspunkte_Bonus", i->sl_Bonus());
         w.setAttr_ne("Region", i->Region());
         if (!i->Magisch().empty()) w.Value(i->Magisch());
      }
   save_ausruestung(Ausruestung, getBesitz().getChildren());
   
   Tag &Fertigkeiten=Abenteurer.push_back(Tag("Fertigkeiten"));

   MidgardBasicElement::saveElementliste(Fertigkeiten,getWerte().Sinne(),getWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Beruf(),getWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Fertigkeit_ang(),getWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Fertigkeit(),getWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Waffen(),getWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Zauber(),getWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Zauberwerk(),getWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Kido(),getWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_WaffenGrund(),getWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Sprache(),getWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Schrift(),getWerte(),getVTyp());

   // Regionen & Ähnliches
  for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
   {  if (!(*i)->Active()) continue;
      Tag &r=Fertigkeiten.push_back(Tag("Region"));
      r.setAttr("Name", (*i)->Name());
      r.setAttr("Region", (*i)->Abkuerzung());
   }
   // Optionen
   std::list<Midgard_Optionen::st_OptionenCheck> LO=const_cast<Midgard_Optionen*>(Optionen)->getOptionenCheck();
   for(std::list<Midgard_Optionen::st_OptionenCheck>::const_iterator i=LO.begin();i!=LO.end();++i)
   {
     // Option, die mit dem C. gespeichert werden müssen
     if(i->index!=Midgard_Optionen::Original && i->index!=Midgard_Optionen::NSC_only) continue; 
     Tag &o=Fertigkeiten.push_back(Tag("Optionen"));
     o.setAttr("Name", i->text);
     o.setBoolAttr("Wert", i->active);
   }
   ts.write(datei);
}


void Abenteurer::grundwerte_speichern(Tag &datei)
{
   Tag &Figur=datei.push_back(Tag("Figur"));
   Figur.setAttr_ne("Name", getWerte().Name_Abenteurer());
   Figur.setAttr_ne("Spieler", getWerte().Name_Spieler());
   Figur.setAttr_ne("Zeitpunkt", getWerte().Version());
   Figur.setIntAttr("Grad", getWerte().Grad());
   
   Tag &Typ=datei.push_back(Tag("Typ"));
   Typ.setAttr_ne("Spezies", getWerte().Spezies()->Name());
   Typ.setAttr_ne("Geschlecht", getWerte().Geschlecht_str());
   Typ.setAttr_ne("Abkürzung", Typ1()->Short());
   Typ.setAttr_ne("Abkürzung2", Typ2()->Short());
   Typ.setAttr_ne("Spezialgebiet", getWerte().Spezialgebiet()->Name());
   Typ.setAttr_ne("Spezialisierung", getWerte().Spezialisierung());
   Typ.setAttr_ne("Überleben",getWerte().Ueberleben()->Name());
   Typ.setAttr_ne("Muttersprache",Muttersprache());
   Typ.setAttr("Stadt_Land", getWerte().Stadt_Land_str());
   Typ.setAttr("Hand", getWerte().Hand());
   
   Tag &BE=datei.push_back(Tag("Basiseigenschaften"));
   BE.setIntAttr("St", getWerte().St());
   BE.setIntAttr("Gw", getWerte().Gw());
   BE.setIntAttr("Gs", getWerte().Gs());
   BE.setIntAttr("Ko", getWerte().Ko());
   BE.setIntAttr("In", getWerte().In());
   BE.setIntAttr("Zt", getWerte().Zt());

   Tag &aE=datei.push_back(Tag("abgeleiteteEigenschaften"));
   aE.setIntAttr("Au", getWerte().Au());
   aE.setIntAttr("pA", getWerte().pA());
   aE.setIntAttr("Wk", getWerte().Wk());
   aE.setIntAttr("Sb", getWerte().Sb());
   aE.setIntAttr("B", getWerte().B());
   aE.setIntAttr_nn("GG", getWerte().GG());
   aE.setIntAttr_nn("SG", getWerte().SG());

   Tag &Ew=datei.push_back(Tag("Erfolgswerte"));
   Ew.setIntAttr("Abwehr", getWerte().Abwehr_wert());
   Ew.setIntAttr("Zaubern", getWerte().Zaubern_wert());
   Ew.setIntAttr("ZauberResistenz", getWerte().Resistenz());

   Tag &Gesundheit=datei.push_back(Tag("Gesundheit")); // schlechter Name ?
   Gesundheit.setIntAttr("LP", getWerte().LP());
   Gesundheit.setIntAttr("AP", getWerte().AP());

   Tag &Beschreibung=datei.push_back(Tag("Beschreibung")); // soziale?
   Beschreibung.setIntAttr("Alter", getWerte().Alter());
   Beschreibung.setAttr("Gestalt", getWerte().Gestalt());
   Beschreibung.setIntAttr("Gewicht", getWerte().Gewicht());
   Beschreibung.setIntAttr("Größe", getWerte().Groesse());
   Beschreibung.setAttr_ne("Stand", getWerte().Stand());
   Beschreibung.setAttr_ne("Bezeichnung", getWerte().Bezeichnung());
   Beschreibung.setAttr_ne("Merkmale", getWerte().Merkmale());
   Beschreibung.setAttr_ne("Herkunft", getWerte().Herkunft()->Name());
   Beschreibung.setAttr_ne("Glaube", getWerte().Glaube());

   Tag &Verm=datei.push_back(Tag("Vermögen"));
   Verm.setIntAttr_nn("GS", getWerte().Gold());
   Verm.setIntAttr_nn("SS", getWerte().Silber());
   Verm.setIntAttr_nn("KS", getWerte().Kupfer());

   Tag &Steigern=datei.push_back(Tag("Steigern"));
   Steigern.setIntAttr_nn("GFP", getWerte().GFP());
   Steigern.setIntAttr_nn("AEP", getWerte().AEP());
   Steigern.setIntAttr_nn("KEP", getWerte().KEP());
   Steigern.setIntAttr_nn("ZEP", getWerte().ZEP());
   if (getWerte().get_Steigern_EP_Prozent()!=50)
      Steigern.setIntAttr("EPproGFP", getWerte().get_Steigern_EP_Prozent());
   if (getWerte().get_Grad_Basiswerte()!=getWerte().Grad())
      Steigern.setIntAttr("Basiswerte", getWerte().get_Grad_Basiswerte());
   if (getWerte().Steigertage())
      Steigern.setAttr("benötigte_Tage", dtos(getWerte().Steigertage()));

   Tag &Pp=Steigern.push_back(Tag("Praxispunkte"));
   Pp.setIntAttr_nn("Abwehr", getWerte().AbwehrPP());
   Pp.setIntAttr_nn("Zaubern", getWerte().ZaubernPP());
   Pp.setIntAttr_nn("Spezial", getWerte().SpezialPP());
   Pp.setIntAttr_nn("Resistenz", getWerte().ResistenzPP());
   
   Tag &Text=datei.push_back(Tag("Text",getWerte().Beschreibung()));
   Text.setIntAttr_nn("Größe", getWerte().BeschreibungPixSize());
   Text.setAttr_ne("Bild", getWerte().BeschreibungPix());
}

void Abenteurer::save_ausruestung(Tag &datei,const list<AusruestungBaum> &AB)
{  
  for(AusruestungBaum::const_iterator i=AB.begin();i!=AB.end();++i)
   {  Tag &Ggs=datei.push_back(Tag("Gegenstand"));
      Ggs.setAttr("Bezeichnung", i->getAusruestung().Name());
      Ggs.setAttr("Besonderheit", i->getAusruestung().Material());
      if (i->getAusruestung().Sichtbar()) 
         Ggs.setBoolAttr("sichtbar", i->getAusruestung().Sichtbar());
      if (!i->empty())
         save_ausruestung(Ggs, i->getChildren());
   }
}

const std::string Abenteurer::Beruf() const
{
 if(list_Beruf.empty()) return "";
 return (*(list_Beruf.begin()))->Name();
 abort(); //never get here
}

///////////////////////////////////////////////////////////////////////////////

bool Abenteurer::xml_import_stream(istream& datei, Datenbank &Database,
   Midgard_Optionen *Optionen,midgard_CG *hauptfenster)
{
   reset();
   TagStream ts(datei);
   const Tag *data=0; // &ts.getContent();
   const Tag *top=ts.find("Midgard-Charakter");    
   if (!top) 
   {  data=ts.find("MidgardCG-data");        
      if (!data) data=ts.find("MAGUS-data");
      if (data) 
      {  top=data->find("Midgard-Charakter");
         if (!top) top=data->find("Midgard-Abenteurer");
      }
   }

  if (!top)
   {//  hauptfenster->InfoFenster->AppendShow("(Abenteurer in) Datei "//'"+Latin2Screen(datei)
    //  " nicht gefunden.");
      return false;
   }
   const int xml_version=top->getIntAttr("Version");
/*
   if (xml_version<3 || xml_version>10)
   {         hauptfenster->InfoFenster->AppendShow("XML Version "+itos(xml_version)
          +" wird noch nicht unterstützt");
   }
*/
   if (data)
   {  const Tag *Preise=data->find("Preise");
      if (Preise)
      {  FOR_EACH_CONST_TAG_OF(i,*Preise,"Kaufpreis")
         {  std::string name=i->getAttr("Ware");
         
            std::list<cH_Preise>::iterator iter;
            while ((iter=std::find(Database.preise.begin(),Database.preise.end(),name))
            		!=Database.preise.end())
            {  iter=Database.preise.erase(iter);
            }
            
            Preise::saveArtikel(i->getAttr("Art"),i->getAttr("Art2"),name,
            		i->getFloatAttr("Preis"),i->getAttr("Währung"),
            		i->getFloatAttr("Gewicht"));
            Database.preise.push_back(cH_Preise(name));
         }
      }
   }

   
   const Tag *Figur=top->find("Figur");
   const Tag *Typ=top->find("Typ");
   const Tag *Basiseigenschaften=top->find("Basiseigenschaften");
   const Tag *abgeleiteteEigenschaften=top->find("abgeleiteteEigenschaften");
   const Tag *Erfolgswerte=top->find("Erfolgswerte");
   const Tag *Resistenzen=top->find("Resistenzen");
   const Tag *Gesundheit=top->find("Gesundheit");
   const Tag *Beschreibung=top->find("Beschreibung");
   const Tag *Vermoegen=top->find("Vermoegen");
       if (!Vermoegen) Vermoegen=top->find("Vermögen");
   const Tag *Ruestung1=top->find("Ruestung");
       if (!Ruestung1) Ruestung1=top->find("Rüstung");
   const Tag *Ausruestung=top->find("Ausrüstung");
       if (!Ausruestung) Ausruestung=top->find("Fertigkeiten");
       if (!Ruestung1) Ruestung1=Ausruestung->find("Rüstung");
   const Tag *Ruestung2=Ausruestung->find("Rüstung2");
   const Tag *Fertigkeiten=top->find("Fertigkeiten");
   const Tag *Steigern=top->find("Steigern");
   const Tag *Praxispunkte=Steigern?Steigern->find("Praxispunkte"):0;

   getWerte().setBasiswerte(Basiseigenschaften->getIntAttr("St"),
   	Basiseigenschaften->getIntAttr("Gw",abgeleiteteEigenschaften->getIntAttr("RW")),
   	Basiseigenschaften->getIntAttr("Gs",Basiseigenschaften->getIntAttr("Ge")),
   	Basiseigenschaften->getIntAttr("Ko"),
   	Basiseigenschaften->getIntAttr("In"),
   	Basiseigenschaften->getIntAttr("Zt"));
   getWerte().setAu(abgeleiteteEigenschaften->getIntAttr("Au"));
   getWerte().setpA(abgeleiteteEigenschaften->getIntAttr("pA"));
   getWerte().setSb(abgeleiteteEigenschaften->getIntAttr("Sb"));
   getWerte().setWk(abgeleiteteEigenschaften->getIntAttr("Wk"));
   getWerte().setB(abgeleiteteEigenschaften->getIntAttr("B"));
   getWerte().setLP(Gesundheit->getIntAttr("LP"));
   getWerte().setAP(Gesundheit->getIntAttr("AP"));
   getWerte().setZaubern_wert(Erfolgswerte->getIntAttr("Zaubern"));
   getWerte().setAbwehr_wert(Erfolgswerte->getIntAttr("Abwehr"));
   getWerte().setResistenz(Erfolgswerte->getIntAttr("ZauberResistenz",
  	!Resistenzen?0:Resistenzen->getIntAttr("Zauber",Resistenzen->getIntAttr("Resistenz",Resistenzen->getIntAttr("psy")))));
   if (Praxispunkte)
   {  getWerte().setZaubernPP(Praxispunkte->getIntAttr("Zaubern"));
      getWerte().setSpezialPP(Praxispunkte->getIntAttr("Spezial"));
      getWerte().setAbwehrPP(Praxispunkte->getIntAttr("Abwehr"));
      getWerte().setResistenzPP(Praxispunkte->getIntAttr("Resistenz"));    }
   else
   {  getWerte().setZaubernPP(0);
      getWerte().setAbwehrPP(0);
      getWerte().setSpezialPP(0);
      getWerte().setResistenzPP(0);
   }
   getWerte().setHand(Typ->getAttr("Hand"));
   getWerte().setGewicht(Beschreibung->getIntAttr("Gewicht"));
   getWerte().setGroesse(Beschreibung->getIntAttr("Größe"));
   getWerte().setGrad(Figur->getIntAttr("Grad"));
   getWerte().setStand(Beschreibung->getAttr("Stand"));

   getWerte().setAlter(Beschreibung->getIntAttr("Alter")); 
   getWerte().setGeschlecht(Typ->getAttr("Geschlecht","m"));
   std::string spezialgebiet=Typ->getAttr("Spezialgebiet");
   if(spezialgebiet!="") 
     { 
       cH_Spezialgebiet S(spezialgebiet);
       getWerte().setSpezialgebiet(S);
     }
   std::string ueberleben=Typ->getAttr("Überleben");
   if(ueberleben!="") 
     { 
       MBEmlt M(&*cH_Fertigkeit(ueberleben));
       getWerte().setUeberleben(M);
     }
   setMuttersprache(Typ->getAttr("Muttersprache"));
   getWerte().setSpezialisierung(Typ->getAttr("Spezialisierung"));
   getWerte().setBezeichnung(Beschreibung->getAttr("Bezeichnung"));
   getWerte().setMerkmale(Beschreibung->getAttr("Merkmale"));
   getWerte().setHerkunft(cH_Land(Beschreibung->getAttr("Herkunft"),true));
   getWerte().setGlaube(Beschreibung->getAttr("Glaube"));
   getWerte().setNamen(Figur->getAttr("Name"),Figur->getAttr("Spieler"),Figur->getAttr("Zeitpunkt"));
   getWerte().setGFP(Steigern ? Steigern->getIntAttr("GFP", top->getInt("GFP")) : top->getInt("GFP"));
   getWerte().setSteigertage(Steigern ? Steigern->getFloatAttr("benötigte_Tage", top->getInt("benötigte_Tage")) : top->getInt("benötigte_Tage"));
   getWerte().setGG(abgeleiteteEigenschaften->getIntAttr("GG"));    
   getWerte().setSG(abgeleiteteEigenschaften->getIntAttr("SG"));
   const Tag *Text=top->find("Text");
   if (!Text) Text=top; // to avoid testing below
   getWerte().setBeschreibung(Text->Value()); 
   getWerte().setBeschreibungPix(top->getString("TextPix",Text->getAttr("Bild"))); 
   getWerte().setBeschreibungPixSize(top->getInt("TextPixSize",Text->getIntAttr("Größe")));
   if (Vermoegen)
      getWerte().setGeld(Vermoegen->getIntAttr("GS"),Vermoegen->getIntAttr("SS"),Vermoegen->getIntAttr("KS"));
//   getWerte().clearRuestung();
   if (Ruestung1) getWerte().setRuestung1(Ruestung1->Value(),true);
   else getWerte().setRuestung1("OR",true);
   if (Ruestung2) getWerte().setRuestung2(Ruestung2->Value(),true);
   else getWerte().setRuestung2("OR",true);
   getWerte().setSpezies(cH_Spezies(Typ->getAttr("Spezies","Mensch"),true));
   if (Steigern)       getWerte().setEP(Steigern->getIntAttr("AEP"),Steigern->getIntAttr("KEP"),Steigern->getIntAttr("ZEP"));
   else
      getWerte().setEP(0,0,0);
   getWerte().setStadtLand(Typ->getAttr("Stadt_Land","Stadt"));
   if (Steigern) getWerte().set_Grad_Anstieg(Steigern->getIntAttr("EPproGFP",50)
      	,Steigern->getIntAttr("Basiswerte",getWerte().Grad()));
   else getWerte().set_Grad_Anstieg(50,getWerte().Grad());

//   this->Typ1()=cH_Typen(Typ->getAttr("Abkürzung"),true);
   setTyp1(cH_Typen(Typ->getAttr("Abkürzung"),true));

   { std::string s = Typ->getAttr("Abkürzung2");
     if(s!="") //this->Typ2=cH_Typen(s,true);
         setTyp2(cH_Typen(Typ->getAttr("Abkürzung2"),true));
   }

   load_fertigkeiten(Fertigkeiten,Ausruestung,xml_version,Database,Optionen,hauptfenster);
   load_ausruestung(Ausruestung,&(getBesitz()));
   return true;
}

void Abenteurer::load_ausruestung(const Tag *tag, AusruestungBaum *AB)
{  FOR_EACH_CONST_TAG_OF(i,*tag,"Gegenstand")
   {  cH_Preise(i->getAttr("Bezeichnung"),true);       AusruestungBaum *A = &AB->push_back(
   	Ausruestung(i->getAttr("Bezeichnung"),i->getAttr("Besonderheit")
   					,i->getBoolAttr("sichtbar")));
      A->setParent(AB);
      load_ausruestung(&*i,A);
   }
}

void Abenteurer::load_fertigkeiten(const Tag *tag, const Tag *waffen_b, int xml_version,Datenbank &Database,Midgard_Optionen *Optionen,midgard_CG *hauptfenster)
{

    for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();
    			i!=Database.Regionen.end();++i)
    {  Region::setActive(Database.Regionen,(*i),false);
    }
    FOR_EACH_CONST_TAG(i,*tag)
    {
      const std::string sart=i->Type();
      if(sart=="Sinn")
        {
         getWerte().setSinn(i->getAttr("Bezeichnung"),i->getIntAttr("Wert"));
        }
      else if(sart=="Beruf")
        {
         cH_MidgardBasicElement beruf(&*cH_Beruf(i->getAttr("Bezeichnung"),true));
         MBEmlt B(beruf);
         B.setErfolgswert(i->getIntAttr("Wert"));
         List_Beruf().push_back(B);
        }
      else if(sart=="ang-Fertigkeit" || sart=="ang.Fertigkeit")
       {
         cH_MidgardBasicElement fert_an(&*cH_Fertigkeit_angeborene(i->getAttr("Bezeichnung"),true));
         MBEmlt F(fert_an);
         F.setErfolgswert(i->getIntAttr("Wert"));
         List_Fertigkeit_ang().push_back(F);
       }    
      else if(sart=="Fertigkeit")
       {
         cH_MidgardBasicElement fert(&*cH_Fertigkeit(i->getAttr("Bezeichnung"),true));
         MBEmlt F(fert);
         F.setErfolgswert(i->getIntAttr("Wert"));
         F.setPraxispunkte(i->getIntAttr("Praxispunkte"));
         if(cH_Fertigkeit(fert)->ZusatzEnum(getVTyp()))
         {  fert=new Fertigkeit(*cH_Fertigkeit(fert));
            if(fert->Name()=="Landeskunde") cH_Land(i->getAttr("Zusatz"),true);
            if(fert->Name()=="Scharfschießen") cH_Waffe(i->getAttr("Zusatz"),true);
            F.setZusatz(i->getAttr("Zusatz"));
         }
         List_Fertigkeit().push_back(F);
       }    
      else if(sart=="Waffe")
        {
         cH_MidgardBasicElement waffe(&*cH_Waffe(i->getAttr("Bezeichnung"),true));
         MBEmlt W(waffe);
         W.setErfolgswert(i->getIntAttr("Wert"));
         W.setPraxispunkte(i->getIntAttr("Praxispunkte"));
         List_Waffen().push_back(W);
        }
#if 0 // andere Liste       
      if(sart=="Besitz_W")
#endif
      else if(sart=="Zauber")
        {
         cH_MidgardBasicElement zauber(&*cH_Zauber(i->getAttr("Bezeichnung"),true));
         MBEmlt Z(zauber);
         if(zauber->ZusatzEnum(getVTyp()))
          { zauber=new Zauber(*cH_Zauber(zauber));
            Z.setZusatz(i->getAttr("Zusatz"));
          }
         List_Zauber().push_back(Z);
        }
      else if(sart=="Zauberwerk")
        {
          cH_MidgardBasicElement zauberwerk(&*cH_Zauberwerk(i->getAttr("Bezeichnung"),
                      i->getAttr("Art"),i->getAttr("Stufe"),true));
          MBEmlt Z(zauberwerk);
          List_Zauberwerk().push_back(Z);
        }
      else if(sart=="KiDo")
        {
          cH_MidgardBasicElement kido(&*cH_KiDo(i->getAttr("Bezeichnung"),true));
          MBEmlt K(kido);
          List_Kido().push_back(K) ;
        }
      else if(sart=="Grundkenntnis")
        {  std::string bez=i->getAttr("Bezeichnung");
           if (bez=="ESchwert") bez="Einhandschwert";
           else if (bez=="ZSchwert") bez="Zweihandschwert";
           else if (bez=="ESchlagwaffe") bez="Einhandschlagwaffe";
           else if (bez=="ZSchlagwaffe") bez="Zweihandschlagwaffe";
           else if (bez=="Schilde") bez="Schild";
           cH_MidgardBasicElement grund(&*cH_WaffeGrund(bez,true));
           MBEmlt G(grund);
           List_WaffenGrund().push_back(G);
        }
      else if(sart=="Sprache")
        {
         cH_MidgardBasicElement sprache(&*cH_Sprache(i->getAttr("Bezeichnung"),true));
         MBEmlt S(sprache);
         int wert=i->getIntAttr("Wert");
         if (xml_version<8)          {  switch (wert)
            {  case 1: wert=4; break;
               case 2: wert=6; break;
               case 3: wert=10; break;
               case 4: wert=13; break;
            }
         }
         S.setErfolgswert(wert);
         S.setPraxispunkte(i->getIntAttr("Praxispunkte"));
         List_Sprache().push_back(S);
        }
      else if(sart=="Urschrift") 
        {
         cH_MidgardBasicElement schrift(&*cH_Schrift(i->getAttr("Bezeichnung"),true));
         MBEmlt S(schrift);
         int wert=i->getIntAttr("Wert");
         if (xml_version<8 && !wert) wert=12;
         S.setErfolgswert(wert);
         S.setPraxispunkte(i->getIntAttr("Praxispunkte"));
         List_Schrift().push_back(S);
        }
      else if(sart=="Optionen")
        {
         try{
           Optionen->setOptionCheck(i->getAttr("Name"),i->getBoolAttr("Wert"),i->getBoolAttr("Page"));
         }
         catch (const NotFound &e)
         {}
        }
      else if(sart=="Region")
        {
         try
         {  cH_Region R(i->getAttr("Name",i->getAttr("Region")));
            Region::setActive(Database.Regionen,R,true);
            hauptfenster->set_region_statusbar(R->Pic(),true);
         }
         catch (const NotFound &e)
         {}
        }
    } 
    FOR_EACH_CONST_TAG_OF(i,*waffen_b,"Waffe")
    {   std::string wn = Database.Waffe_from_Alias[i->getAttr("Bezeichnung")];
        if (wn=="") wn=i->getAttr("Bezeichnung"); 
         WaffeBesitz WB(cH_Waffe(wn,true),
                        i->getAttr("Bezeichnung"),
                        i->getIntAttr("AngriffVerteidigung_Bonus"),
                        i->getIntAttr("SchadenLebenspunkte_Bonus"),
                        i->Value(),
                        i->getAttr("Region"));
        List_Waffen_besitz().push_back(WB);
    }
}



void Abenteurer::move_element(std::list<MBEmlt>& von,
                                       std::list<MBEmlt>& nach,
                                       const MBEmlt& MBE)
{
 for (std::list<MBEmlt>::iterator i=von.begin();i!= von.end();++i)
  {
    if(*i==MBE)
        { 
          i->setErfolgswert(MBE.Erfolgswert());
          nach.splice(nach.begin(),von,i);
          break; 
        }
/*
   if((*i)->What()==ZAUBERWERK)
    {
      if ( (*i)->Name()==MBE->Name() && 
           cH_Zauberwerk(*i)->Art()==cH_Zauberwerk(MBE)->Art() && 
           (*i)->Stufe()==MBE->Stufe() ) 
        { nach.splice(nach.begin(),von,i);break; }
    }
   else
    {
      if ((*i)->Name()==MBE->Name()) 
        { 
          i->setErfolgswert(MBE.Erfolgswert());
          nach.splice(nach.begin(),von,i);
          break; 
        }
    }
*/
  }
}
