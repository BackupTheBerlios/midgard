// $Id: Abenteurer.cc,v 1.31 2004/12/22 08:10:30 christof Exp $            
/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
 *  Copyright (C) 2003-2004 Christof Petig
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
#include <Misc/TagStream.h>
#include "Preise.hh"
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
#include <Misc/Trace.h>
#include "magustrace.h"
#include "Datenbank.hh"
#include "Ausgabe.hh"


#include <Magus_Optionen.hh>
Abenteurer::Abenteurer(bool initialize) : Grundwerte(initialize)
{
   for(Magus_Optionen::regionen_t::const_iterator i=Programmoptionen->standard_regionen.begin();i!=Programmoptionen->standard_regionen.end();++i) 
      regionen[i->first] = i->second;
}


bool Abenteurer::Valid() const
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
  if(getVTyp().size()!=2) return false;
  return Typ1()->Valid();
}


const std::string Abenteurer::LastSavedAt() const
{
  tm *t=localtime(&last_saved_time);
  return itos(t->tm_mday) +"."+ itos(t->tm_mon) +"."+ itos(1900+t->tm_year);
}




std::string Grundwerte::STyp() const
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
  if(Typ2()->Name(Geschlecht())!="")
   return Typ1()->Name(Geschlecht())+"/"+Typ2()->Name(Geschlecht());
  else return Typ1()->Name(Geschlecht());
  abort(); //never get here
}


const std::string Abenteurer::SErfolgswert(std::string name) const
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
  std::pair<int,bool> w=Erfolgswert(name);
  if(w.first==-99) return "";
  if(w.second) return itos(w.first);
  else return "("+itos(w.first)+")";
}

const std::pair<int,bool> Abenteurer::Erfolgswert(std::string name) const
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
  for(std::list<MBEmlt>::const_iterator i=list_Fertigkeit.begin();i!=list_Fertigkeit.end();++i)
   {
     if(name==(*(*i))->Name()) return std::pair<int,bool>((*i)->Erfolgswert(),true); 
   }   
  std::list<st_universell> UF=List_Universell();
  for(std::list<st_universell>::const_iterator i=UF.begin();i!=UF.end();++i)
   {
     if(name==(*i->mbe)->Name()) return std::pair<int,bool>(i->mbe->Erfolgswert(),false); 
   }   
  return std::pair<int,bool>(-99,false);
}


const std::list<Abenteurer::st_universell> Abenteurer::List_Universell() const
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
  std::list<st_universell> UF;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=Datenbank.Fertigkeit.begin();i!=Datenbank.Fertigkeit.end();++i)
   {
     cH_Fertigkeit f(*i);
     if(f->Ungelernt(*this)!=-99)
     UF.push_back(MBEmlt(*i));
   }
  cH_MidgardBasicElement werfen(&*cH_Waffe("Werfen"));
  UF.push_back(MBEmlt(werfen));
  UF.push_back(Ueberleben());
  UF.sort(sort_universell());

  for(std::list<Abenteurer::st_universell>::iterator i=UF.begin();i!=UF.end();++i)
   {
     int iwert=-99;
     if ((*i->mbe)->What()==MidgardBasicElement::FERTIGKEIT)
      {
        cH_Fertigkeit f(i->mbe->getMBE());
        iwert = f->Ungelernt(*this);
        if(f->Name()==(*(Ueberleben()))->Name()) iwert=6;
        if (!f->Voraussetzung(*this,true))
            {iwert-=2; i->voraussetzung=false;}
      }
     else if ((*i->mbe)->What()==MidgardBasicElement::WAFFE)
      {
        cH_Waffe f((*i->mbe).getMBE());
        iwert = 4+bo_An();
        if (!f->Voraussetzung(*this,true))
            {iwert=0; i->voraussetzung=false;}
      }
     if ((*i->mbe).ist_gelernt(List_Fertigkeit()) || (*i->mbe).ist_gelernt(List_Waffen()))
          i->gelernt=true;
     else // Erfolgswert nur dann setzen, wenn die Fertigkeit NICHT gelernt ist
          (*i->mbe).setErfolgswert(iwert);
   }
  return UF;
}

bool Grundwerte::is_mage() const 
{  
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
   if(getVTyp().size()!=2) return false;
   if(Typ1()->is_mage() || Typ2()->is_mage()) return true;
   else return false;
}



void Abenteurer::setAngebFert()
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
  List_Fertigkeit_ang().clear();
  List_Fertigkeit_ang()=Spezies()->getAngFertigkeiten();
  List_Zauber()=Spezies()->getZauber();
  resetSinne();
  std::list<std::pair<std::string,int> > L=Spezies()->getSinne();
  for(std::list<std::pair<std::string,int> >::const_iterator i=L.begin();i!=L.end();++i) 
       setSinn(i->first,i->second);
}

bool Abenteurer::setAngebSinnFert(int wurf,const MBEmlt &MBE)
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
  int wert=MBE->Erfolgswert();
  if     ( 1<=wurf && wurf<= 2) setSinnCheck("Sehen",wert);    
  else if( 3<=wurf && wurf<= 4) setSinnCheck("Hören",wert);    
  else if( 5<=wurf && wurf<= 6) setSinnCheck("Riechen",wert);  
  else if( 7<=wurf && wurf<= 8) setSinnCheck("Schmecken",wert);
  else if( 9<=wurf && wurf<=10) setSinnCheck("Tasten",wert);
  else if(11<=wurf && wurf<=20) setSinn("Sehen",wert);    
  else if(21<=wurf && wurf<=30) setSinn("Hören",wert);    
  else if(31<=wurf && wurf<=40) setSinn("Riechen",wert);  
  else if(41<=wurf && wurf<=50) setSinn("Schmecken",wert);
  else if(51<=wurf && wurf<=60) setSinn("Tasten",wert);
  else if(61<=wurf && wurf<=65) setSinn("Sechster Sinn",wert);
  else { List_Fertigkeit_ang().push_back(MBE); return false;}
  return true;
}




void Abenteurer::speicherstream(std::ostream &datei) const
{  speichern(datei);
}

void Abenteurer::speichern(std::ostream &datei) const
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
   TagStream ts;
   ts.setEncoding("UTF-8");
   
   Tag &data=ts.push_back(Tag("MAGUS-data"));  

   Tag &Abenteurer=data.push_back(Tag("Midgard-Abenteurer"));
   Abenteurer.setIntAttr("Version",10);

   grundwerte_speichern(Abenteurer);
   Tag &Ausruestung=Abenteurer.push_back(Tag("Ausrüstung"));
   Ausruestung.push_back(Tag("Rüstung", Ruestung()->Name()));
   if (!Ruestung(1)->Name().empty())
     Ausruestung.push_back(Tag("Rüstung2", Ruestung(1)->Name()));
   // Waffen Besitz
   for (std::list<H_WaffeBesitz>::const_iterator i=List_Waffen_besitz().begin();
//   for (std::list<MBEmlt>::const_iterator i=List_Waffen_besitz().begin();
         i!=List_Waffen_besitz().end();++i)
      {  
//         WaffeBesitz WB(*i) ;
         Tag &w=Ausruestung.push_back(Tag("Waffe"));
         w.setIntAttr("Erfolgswert", (*i)->Erfolgswert());
         w.setAttr("Bezeichnung", (*i)->AliasName());
         w.setIntAttr_nn("AngriffVerteidigung_Bonus", (*i)->av_Bonus());
         w.setIntAttr_nn("SchadenLebenspunkte_Bonus", (*i)->sl_Bonus());
         w.setAttr_ne("Region", (*i)->Region());
         if (!(*i)->Magisch().empty()) w.Value((*i)->Magisch());
      }
   save_ausruestung(Ausruestung, getBesitz().getChildren());
   
   Tag &Fertigkeiten=Abenteurer.push_back(Tag("Fertigkeiten"));

   MidgardBasicElement::saveElementliste(Fertigkeiten,Sinne(),*this,getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Beruf(),*this,getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Fertigkeit_ang(),*this,getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Fertigkeit(),*this,getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Waffen(),*this,getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Zauber(),*this,getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Zauberwerk(),*this,getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Kido(),*this,getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_WaffenGrund(),*this,getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Sprache(),*this,getVTyp());
   MidgardBasicElement::saveElementliste(Fertigkeiten,List_Schrift(),*this,getVTyp());
   // Zauber, die von Spruchrolle gelernt wurden
   for(std::list<std::string>::const_iterator i= list_Gelernt_von_Spruchrolle.begin();i!=list_Gelernt_von_Spruchrolle.end();++i)
      Abenteurer.push_back(Tag("Von Spruchrolle gelernt",*i));

   // Regionen & Optionen
   Tag &Opt=Abenteurer.push_back(Tag("Optionen"));
  for(std::map<cH_Region,Model_copyable<bool> >::const_iterator i=regionen.begin();i!=regionen.end();++i)
   {  if (!i->second.Value()) continue;
      Tag &r=Opt.push_back(Tag("Region"));
      r.setAttr("Name", i->first->Name());
      r.setAttr("Region", i->first->Abkuerzung());
   }
   // Optionen
   const std::list<Optionen::st_OptionenCheck> &LO=optionen.getOptionenCheck();
   for(std::list<Optionen::st_OptionenCheck>::const_iterator i=LO.begin();i!=LO.end();++i)
   {
     // Option, die mit dem C. gespeichert werden müssen
     Tag &o=Opt.push_back(Tag("CheckOptions"));
     o.setAttr("Name", i->text);
     o.setBoolAttr("Wert", i->active);
   }
   const std::list<Optionen::st_Haus> &LH=optionen.getHausregeln();
   for(std::list<Optionen::st_Haus>::const_iterator i=LH.begin();i!=LH.end();++i)
   {
     Tag &o=Opt.push_back(Tag("Hausregeln"));
     o.setAttr("Name", i->text);
     o.setBoolAttr("Wert", i->active);
   }
   ts.write(datei);
   const_cast<class Abenteurer*>(this)->last_saved_time= time(0);
}


void Abenteurer::grundwerte_speichern(Tag &datei) const
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
   Tag &Figur=datei.push_back(Tag("Figur"));
   Figur.setAttr_ne("Name", Name_Abenteurer());
   Figur.setAttr_ne("Spieler", Name_Spieler());
   Figur.setAttr_ne("Zeitpunkt", Version());
   Figur.setIntAttr("Grad", Grad());
   
   Tag &Typ=datei.push_back(Tag("Typ"));
   Typ.setAttr_ne("Spezies", Spezies()->Name());
   Typ.setAttr_ne("Geschlecht", Geschlecht_str());
   Typ.setAttr_ne("Abkürzung", Typ1()->Short());
   Typ.setAttr_ne("Abkürzung2", Typ2()->Short());
   Typ.setAttr_ne("Spezialgebiet", Spezialgebiet()->Name());
   Typ.setAttr_ne("Spezialisierung", Spezialisierung());
   Typ.setAttr_ne("Überleben",(*Ueberleben())->Name());
   Typ.setAttr_ne("Muttersprache",Muttersprache());
   Typ.setAttr("Stadt_Land", Stadt_Land_str());
   Typ.setAttr("Hand", Hand());
   
   Tag &BE=datei.push_back(Tag("Basiseigenschaften"));
   BE.setIntAttr("St", St());
   BE.setIntAttr("Gw", Gw());
   BE.setIntAttr("Gs", Gs());
   BE.setIntAttr("Ko", Ko());
   BE.setIntAttr("In", In());
   BE.setIntAttr("Zt", Zt());

   Tag &aE=datei.push_back(Tag("abgeleiteteEigenschaften"));
   aE.setIntAttr("Au", Au());
   aE.setIntAttr("pA", pA());
   aE.setIntAttr("Wk", Wk());
   aE.setIntAttr("Sb", Sb());
   aE.setIntAttr("B", B());
   aE.setIntAttr_nn("GG", GG());
   aE.setIntAttr_nn("SG", SG());

   Tag &Ew=datei.push_back(Tag("Erfolgswerte"));
   Ew.setIntAttr("Abwehr", Abwehr_wert());
   Ew.setIntAttr("Zaubern", Zaubern_wert());
   Ew.setIntAttr("ZauberResistenz", Resistenz());

   Tag &Gesundheit=datei.push_back(Tag("Gesundheit")); // schlechter Name ?
   Gesundheit.setIntAttr("LP", LP());
   Gesundheit.setIntAttr("AP", AP());

   Tag &Beschreibung=datei.push_back(Tag("Beschreibung")); // soziale?
   Beschreibung.setIntAttr("Alter", Alter());
   Beschreibung.setAttr("Gestalt", Gestalt());
   Beschreibung.setIntAttr("Gewicht", Gewicht());
   Beschreibung.setIntAttr("Größe", Groesse());
   Beschreibung.setAttr_ne("Stand", Stand());
   Beschreibung.setAttr_ne("Bezeichnung", Bezeichnung());
   Beschreibung.setAttr_ne("Merkmale", Merkmale());
   Beschreibung.setAttr_ne("Herkunft", Herkunft()->Name());
   Beschreibung.setAttr_ne("Glaube", Glaube());

   Tag &Verm=datei.push_back(Tag("Vermögen"));
   Verm.setIntAttr_nn("GS", Gold());
   Verm.setIntAttr_nn("SS", Silber());
   Verm.setIntAttr_nn("KS", Kupfer());

   Tag &Steigern=datei.push_back(Tag("Steigern"));
   Steigern.setIntAttr_nn("GFP", GFP());
   Steigern.setIntAttr_nn("AEP", AEP());
   Steigern.setIntAttr_nn("KEP", KEP());
   Steigern.setIntAttr_nn("ZEP", ZEP());
   if (get_Steigern_EP_Prozent()!=50)
      Steigern.setIntAttr("EPproGFP", get_Steigern_EP_Prozent());
   if (get_Grad_Basiswerte()!=Grad())
      Steigern.setIntAttr("Basiswerte", get_Grad_Basiswerte());
   if (Steigertage())
      Steigern.setAttr("benötigte_Tage", dtos(Steigertage()));

   Tag &Pp=Steigern.push_back(Tag("Praxispunkte"));
   Pp.setIntAttr_nn("Abwehr", AbwehrPP());
   Pp.setIntAttr_nn("Zaubern", ZaubernPP());
   Pp.setIntAttr_nn("Spezial", SpezialPP());
   Pp.setIntAttr_nn("Resistenz", ResistenzPP());
   
   Tag &Text=datei.push_back(Tag("Text",this->Beschreibung()));
   Text.setIntAttr_nn("Größe", BeschreibungPixSize());
   Text.setAttr_ne("Bild", BeschreibungPix());
}

void Abenteurer::save_ausruestung(Tag &datei,const std::list<AusruestungBaum> &AB) const
{  
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
  for(AusruestungBaum::const_iterator i=AB.begin();i!=AB.end();++i)
   {  Tag &Ggs=datei.push_back(Tag("Gegenstand"));
      if (i->getAusruestung().Anzahl()!=1)
        Ggs.setIntAttr("Anzahl", i->getAusruestung().Anzahl());
      Ggs.setAttr("Bezeichnung", i->getAusruestung().Name());
      if (!i->getAusruestung().Beschreibung().empty())
        Ggs.setAttr("Beschreibung", i->getAusruestung().Beschreibung());
      if (!i->getAusruestung().Region().empty())
        Ggs.setAttr("Region", i->getAusruestung().Region());
      if (i->getAusruestung().Gewicht()!=0.0)
        Ggs.setFloatAttr("Gewicht", i->getAusruestung().Gewicht());
      if (i->getAusruestung().RuestungOhneGewicht())
        Ggs.setBoolAttr("RüstungOhneGewicht",i->getAusruestung().RuestungOhneGewicht());
      if (!i->getAusruestung().Material().empty())
        Ggs.setAttr("Besonderheit", i->getAusruestung().Material());
      if (i->getAusruestung().Sichtbar()) 
         Ggs.setBoolAttr("sichtbar", i->getAusruestung().Sichtbar());
      if (!i->empty())
         save_ausruestung(Ggs, i->getChildren());
   }
}

const std::string Abenteurer::Beruf() const
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
 if(list_Beruf.empty()) return "";
 return (*(*(list_Beruf.begin())))->Name();
 abort(); //never get here
}

///////////////////////////////////////////////////////////////////////////////

bool Abenteurer::xml_import_stream(std::istream& datei)
{  return laden(datei);
}

bool Abenteurer::laden(std::istream& datei)
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
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
   Tag leer("");
       if (!Ausruestung) Ausruestung=&leer; // last Ressort
       if (!Ruestung1) Ruestung1=Ausruestung->find("Rüstung");
   const Tag *Ruestung2=Ausruestung->find("Rüstung2");
   const Tag *Fertigkeiten=top->find("Fertigkeiten");
   const Tag *Opt=top->find("Optionen");
   const Tag *Steigern=top->find("Steigern");
   const Tag *Praxispunkte=Steigern?Steigern->find("Praxispunkte"):0;

   setBasiswerte(Basiseigenschaften->getIntAttr("St"),
   	Basiseigenschaften->getIntAttr("Gw",abgeleiteteEigenschaften->getIntAttr("RW")),
   	Basiseigenschaften->getIntAttr("Gs",Basiseigenschaften->getIntAttr("Ge")),
   	Basiseigenschaften->getIntAttr("Ko"),
   	Basiseigenschaften->getIntAttr("In"),
   	Basiseigenschaften->getIntAttr("Zt"));
   setAu(abgeleiteteEigenschaften->getIntAttr("Au"));
   setpA(abgeleiteteEigenschaften->getIntAttr("pA"));
   setSb(abgeleiteteEigenschaften->getIntAttr("Sb"));
   setWk(abgeleiteteEigenschaften->getIntAttr("Wk"));
   setB(abgeleiteteEigenschaften->getIntAttr("B"));
   setLP(Gesundheit->getIntAttr("LP"));
   setAP(Gesundheit->getIntAttr("AP"));
   setZaubern_wert(Erfolgswerte->getIntAttr("Zaubern"));
   setAbwehr_wert(Erfolgswerte->getIntAttr("Abwehr"));
   setResistenz(Erfolgswerte->getIntAttr("ZauberResistenz",
  	!Resistenzen?0:Resistenzen->getIntAttr("Zauber",Resistenzen->getIntAttr("Resistenz",Resistenzen->getIntAttr("psy")))));
   if (Praxispunkte)
   {  setZaubernPP(Praxispunkte->getIntAttr("Zaubern"));
      setSpezialPP(Praxispunkte->getIntAttr("Spezial"));
      setAbwehrPP(Praxispunkte->getIntAttr("Abwehr"));
      setResistenzPP(Praxispunkte->getIntAttr("Resistenz"));    }
   else
   {  setZaubernPP(0);
      setAbwehrPP(0);
      setSpezialPP(0);
      setResistenzPP(0);
   }
   setHand(Typ->getAttr("Hand"));
   setGewicht(Beschreibung->getIntAttr("Gewicht"));
   setGroesse(Beschreibung->getIntAttr("Größe"));
   setGrad(Figur->getIntAttr("Grad"));
   setStand(Beschreibung->getAttr("Stand"));

   setAlter(Beschreibung->getIntAttr("Alter")); 
   setGeschlecht(Typ->getAttr("Geschlecht","m"));
   std::string spezialgebiet=Typ->getAttr("Spezialgebiet");
   if(spezialgebiet!="") 
     { 
       cH_Spezialgebiet S(spezialgebiet);
       setSpezialgebiet(S);
     }
   std::string ueberleben=Typ->getAttr("Überleben");
   if(ueberleben!="") 
     { 
       MBEmlt M(&*cH_Fertigkeit(ueberleben,true));
       setUeberleben(M);
     }
   setMuttersprache(Typ->getAttr("Muttersprache"));
   setSpezialisierung(Typ->getAttr("Spezialisierung"));
   setBezeichnung(Beschreibung->getAttr("Bezeichnung"));
   setMerkmale(Beschreibung->getAttr("Merkmale"));
   setHerkunft(cH_Land(Beschreibung->getAttr("Herkunft"),true));
   setGlaube(Beschreibung->getAttr("Glaube"));
   setNamen(Figur->getAttr("Name"),Figur->getAttr("Spieler"),Figur->getAttr("Zeitpunkt"));
   setGFP(Steigern ? Steigern->getIntAttr("GFP", top->getInt("GFP")) : top->getInt("GFP"));
   setSteigertage(Steigern ? Steigern->getFloatAttr("benötigte_Tage", top->getInt("benötigte_Tage")) : top->getInt("benötigte_Tage"));
   setGG(abgeleiteteEigenschaften->getIntAttr("GG"));    
   setSG(abgeleiteteEigenschaften->getIntAttr("SG"));
   const Tag *Text=top->find("Text");
   if (!Text) Text=top; // to avoid testing below
   setBeschreibung(Text->Value()); 
   setBeschreibungPix(top->getString("TextPix",Text->getAttr("Bild"))); 
   setBeschreibungPixSize(top->getInt("TextPixSize",Text->getIntAttr("Größe")));
   if (Vermoegen)
      setGeld(Vermoegen->getIntAttr("GS"),Vermoegen->getIntAttr("SS"),Vermoegen->getIntAttr("KS"));
//   clearRuestung();
   if (Ruestung1) setRuestung1(Ruestung1->Value(),true);
   else setRuestung1("OR",true);
   if (Ruestung2) setRuestung2(Ruestung2->Value(),true);
   else setRuestung2("OR",true);
   setSpezies(cH_Spezies(Typ->getAttr("Spezies","Mensch"),true));
   if (Steigern)       setEP(Steigern->getIntAttr("AEP"),Steigern->getIntAttr("KEP"),Steigern->getIntAttr("ZEP"));
   else
      setEP(0,0,0);
   setStadtLand(Typ->getAttr("Stadt_Land","Stadt"));
   if (Steigern) 
   { int fpanteil2=Steigern->getIntAttr("EPproGFP",50);
     fpanteil=fpanteil2;
     goldanteil=100-fpanteil2;
     set_Grad_Basiswerte(Steigern->getIntAttr("Basiswerte",Grad()));
   }
   else 
   { fpanteil=goldanteil=50;
     set_Grad_Basiswerte(Grad());
   }

//   this->Typ1()=cH_Typen(Typ->getAttr("Abkürzung"),true);
   setTyp1(cH_Typen(Typ->getAttr("Abkürzung"),true));

   { std::string s = Typ->getAttr("Abkürzung2");
     if(s!="") //this->Typ2=cH_Typen(s,true);
         setTyp2(cH_Typen(Typ->getAttr("Abkürzung2"),true));
   }

   load_fertigkeiten(Fertigkeiten,Ausruestung,xml_version);
   load_regionen_optionen(Opt,xml_version);
   getBesitz().clear();
   load_ausruestung(Ausruestung,&(getBesitz()));
   FOR_EACH_CONST_TAG_OF(i,*top,"Von Spruchrolle gelernt")
     list_Gelernt_von_Spruchrolle.push_back(i->Value());
   return true;
}

void Abenteurer::load_ausruestung(const Tag *tag, AusruestungBaum *AB)
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
  FOR_EACH_CONST_TAG_OF(i,*tag,"Gegenstand")
   {  cH_Preise(i->getAttr("Bezeichnung"),true);
      AusruestungBaum *A = &AB->push_back(
      	Ausruestung(i->getIntAttr("Anzahl",1),
      	         i->getAttr("Bezeichnung"),i->getFloatAttr("Gewicht"),
      	         i->getAttr("Besonderheit"),
   					i->getAttr("Region"),i->getBoolAttr("sichtbar"),
   					i->getBoolAttr("RüstungOhneGewicht"),
   					i->getAttr("Beschreibung")));
      A->setParent(AB);
      load_ausruestung(&*i,A);
   }
}

void Abenteurer::load_fertigkeiten(const Tag *tag, const Tag *waffen_b, int xml_version)
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
    FOR_EACH_CONST_TAG(i,*tag)
    {
      const std::string sart=i->Type();
      if(sart=="Sinn")
        {
         setSinn(i->getAttr("Bezeichnung"),i->getIntAttr("Wert"));
        }
      else if(sart=="Beruf")
        {
         cH_MidgardBasicElement beruf(&*cH_Beruf(i->getAttr("Bezeichnung"),true));
         MBEmlt B(beruf);
         B->setErfolgswert(i->getIntAttr("Wert"));
         List_Beruf().push_back(B);
        }
      else if(sart=="ang-Fertigkeit" || sart=="ang.Fertigkeit")
       {
         cH_MidgardBasicElement fert_an(&*cH_Fertigkeit_angeborene(i->getAttr("Bezeichnung"),true));
         MBEmlt F(fert_an);
         F->setErfolgswert(i->getIntAttr("Wert"));
         List_Fertigkeit_ang().push_back(F);
       }    
      else if(sart=="Fertigkeit")
       {
         cH_MidgardBasicElement fert(&*cH_Fertigkeit(i->getAttr("Bezeichnung"),true));
         MBEmlt F(fert);
         F->setErfolgswert(i->getIntAttr("Wert"));
         F->setPraxispunkte(i->getIntAttr("Praxispunkte"));
         if(cH_Fertigkeit(fert)->ZusatzEnum(getVTyp()))
         {  // fert=new Fertigkeit(*cH_Fertigkeit(fert));
            // create Zusatz if not already there
            if(fert->Name()=="Landeskunde") cH_Land(i->getAttr("Zusatz"),true);
            if(fert->Name()=="Scharfschießen") cH_Waffe(i->getAttr("Zusatz"),true);
            F->setZusatz(i->getAttr("Zusatz"));
         }
         List_Fertigkeit().push_back(F);
       }    
      else if(sart=="Waffe")
        {
         cH_MidgardBasicElement waffe(&*cH_Waffe(i->getAttr("Bezeichnung"),true));
         MBEmlt W(waffe);
         W->setErfolgswert(i->getIntAttr("Wert"));
         W->setPraxispunkte(i->getIntAttr("Praxispunkte"));
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
          { // zauber=new Zauber(*cH_Zauber(zauber));
            Z->setZusatz(i->getAttr("Zusatz"));
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
         S->setErfolgswert(wert);
         S->setPraxispunkte(i->getIntAttr("Praxispunkte"));
         List_Sprache().push_back(S);
        }
      else if(sart=="Urschrift") 
        {
         cH_MidgardBasicElement schrift(&*cH_Schrift(i->getAttr("Bezeichnung"),true));
         MBEmlt S(schrift);
         int wert=i->getIntAttr("Wert");
         if (xml_version<8 && !wert) wert=12;
         S->setErfolgswert(wert);
         S->setPraxispunkte(i->getIntAttr("Praxispunkte"));
         List_Schrift().push_back(S);
        }
// demnächst weg (geändert seit 0.8.10)
      else if(sart=="Optionen")
        {
         try{
           optionen.setOptionCheck(i->getAttr("Name"),i->getBoolAttr("Wert"));
         }
         catch (const NotFound &e)
         { Ausgabe(Ausgabe::Error,e);  }
        }
      else if(sart=="Region")
        {
         try
         {  cH_Region R(i->getAttr("Name",i->getAttr("Region")));
            regionen[R]=true;
         }
// bis hier
         catch (const NotFound &e)
         {  Ausgabe(Ausgabe::Error,e);}
        }
    } 
    FOR_EACH_CONST_TAG_OF(i,*waffen_b,"Waffe")
    {   H_WaffeBesitz WB=new WaffeBesitz(Datenbank.WaffeVonBezeichnung(i->getAttr("Bezeichnung")),
                        i->getAttr("Bezeichnung"),
                        i->getIntAttr("AngriffVerteidigung_Bonus"),
                        i->getIntAttr("SchadenLebenspunkte_Bonus"),
                        i->Value(),
                        i->getAttr("Region"));
        List_Waffen_besitz().push_back(WB);
    }
}

void Abenteurer::load_regionen_optionen(const Tag *tag, int xml_version)
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
    for(std::map<cH_Region,Model_copyable<bool> >::iterator i=regionen.begin();i!=regionen.end();++i)
      {   i->second=false;  }
    if(!tag) return;
    FOR_EACH_CONST_TAG(i,*tag)
    {
      const std::string sart=i->Type();
      if(sart=="CheckOptions")
        {
         try{
           optionen.setOptionCheck(i->getAttr("Name"),i->getBoolAttr("Wert"));
         }
         catch (const NotFound &e)
         {Ausgabe(Ausgabe::Error,e);}
        }
      else if(sart=="Hausregeln")
        {
         try{
           optionen.setHausregeln(i->getAttr("Name"),i->getBoolAttr("Wert"));
         }
         catch (const NotFound &e)
         {Ausgabe(Ausgabe::Error,e);}
        }
      else if(sart=="Region")
        {
         try
         {  cH_Region R(i->getAttr("Name",i->getAttr("Region")));
            regionen[R]=true;
         }
         catch (const NotFound &e)
         {Ausgabe(Ausgabe::Error,e);}
        }
   }
}


void Abenteurer::move_element(std::list<MBEmlt>& von,
                                       std::list<MBEmlt>& nach,
                                       const MBEmlt& MBE)
{
 ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
 for (std::list<MBEmlt>::iterator i=von.begin();i!= von.end();++i)
  {
    if(*i==MBE)
        { 
          (*i)->setErfolgswert(MBE->Erfolgswert());
          nach.splice(nach.begin(),von,i);
          break; 
        }
  }
}


void Abenteurer::remove_WaffenGrund()
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
reloop:
  for(std::list<MBEmlt>::iterator i=list_WaffenGrund.begin();i!=list_WaffenGrund.end();++i)
   {
     bool remove=true;
     for(std::list<MBEmlt>::const_iterator j=list_Waffen.begin();j!=list_Waffen.end();++j)
      {
        if(cH_Waffe((*j)->getMBE())->Grundkenntnis()==(*(*i))->Name()) 
            {remove=false; break;}
      }
     if(remove) {list_WaffenGrund.remove(*i); goto reloop;}
   }
}

// wozu???
std::list<MBEmlt> &Abenteurer::get_known_list(const MidgardBasicElement::MBEE was)
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
  std::list<MBEmlt> *L ; 
  switch (was) {
     case MidgardBasicElement::FERTIGKEIT: L=&List_Fertigkeit(); break;
     case MidgardBasicElement::WAFFE: L=&List_Waffen(); break;
     case MidgardBasicElement::SPRACHE: L=&List_Sprache(); break;
     case MidgardBasicElement::SCHRIFT: L=&List_Schrift(); break;
     case MidgardBasicElement::WAFFEGRUND: L=&List_WaffenGrund(); break;
     case MidgardBasicElement::ZAUBER: L=&List_Zauber(); break;
     case MidgardBasicElement::ZAUBERWERK:L=&List_Zauberwerk(); break;
     case MidgardBasicElement::KIDO: L=&List_Kido(); break;
     default: assert(!"never get here\n");
   }
 return *L;
}


std::list<MBEmlt> &Abenteurer::get_known_list(const MBEmlt &MBE)
{ ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
  return getList((*MBE).What());
}
 
std::list<MBEmlt> &Abenteurer::getList(MidgardBasicElement::MBEE was)
{ switch (was)
  { case MidgardBasicElement::FERTIGKEIT: return List_Fertigkeit();
    case MidgardBasicElement::WAFFE: return List_Waffen();
    case MidgardBasicElement::WAFFEGRUND: return List_WaffenGrund();
    case MidgardBasicElement::ZAUBER: return List_Zauber();
    case MidgardBasicElement::ZAUBERWERK: return List_Zauberwerk();
    case MidgardBasicElement::KIDO: return List_Kido();
    case MidgardBasicElement::SPRACHE: return List_Sprache();
    case MidgardBasicElement::SCHRIFT: return List_Schrift();
    default: assert(!"Abenteurer::getList: invalid arg");
      abort(); // silence gcc
  }
}

std::string Abenteurer::Ruestung_B_Verlust(bool ueberlast_beruecksichtigen) const
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
 std::string s;
 int R0; 
 int R1; 

 bool ew; // Erfolgswerte um zwei reduzieren
 if(ueberlast_beruecksichtigen)
  {
    R0 = Ruestung(0)->B_Verlust(getUeberlast(),*this,ew);
    R1 = Ruestung(1)->B_Verlust(getUeberlast(),*this,ew);
  }
 else
  {
    R0 = Ruestung(0)->B_Verlust(0,*this,ew);
    R1 = Ruestung(1)->B_Verlust(0,*this,ew);
  }

 int b=B();

 if     (R0&&!R1) s="\\scriptsize("+itos(b-R0)+")";
 else if(R1&&!R0) s="\\scriptsize("+itos(b-R1)+")";
 else if(R0&&R1)  s="\\tiny("+itos((b-R0<0)?0:b-R0)+","+itos((b-R1<0)?0:b-R1)+")";

 if(s!="") return "_{"+s+"}";
 return "";
}

bool Abenteurer::getRegion(const cH_Region &r) const
{  regionen_t::const_iterator i=regionen.find(r);
   if (i==regionen.end()) return false;
   return i->second.Value();
}

void Abenteurer::reset()
{  list_Beruf.clear();
             list_Fertigkeit_ang.clear();list_Fertigkeit.clear();
             list_WaffenGrund.clear();list_Waffen.clear();
             list_Waffen_besitz.clear();list_Zauber.clear();
             list_Zauberwerk.clear();list_Kido.clear();
             list_Sprache.clear();list_Schrift.clear(); 
             Grundwerte::reset();
             setStandardAusruestung();
}

#if 0
void Abenteurer::calculate_old_API(e_wie_steigern &wie, Enums::st_bool_steigern &bool_st)
{ wie=Enums::eUnterweisung;
  bool_st.mitEP=fpanteil>0;
  bool_st.HausG1=getOptionen().HausregelCheck(Optionen::Gold).active;
  bool_st.Spruchrolle= wie_steigern==ws_Spruchrolle;
  bool_st.SpruchrolleAuto=true; // ???
  bool_st.hoch_wie_geht=true;
  bool_st.pp_verfallen= wie_steigern_variante==wsv_NurPraxispunkte;
  bool_st.aep_fuellen= wie_steigern_variante==wsv_PraxispunkteFP;
  bool_st.neue_sprache_pp= wie_steigern==ws_Praxispunkte;
  if (wie_steigern==ws_Praxispunkte)
    wie=Enums::ePraxis;
  else if (wie_steigern==ws_Selbststudium)
    wie=Enums::eSelbststudium;
}
#endif

   // true: funktioniert
bool Abenteurer::Steigern(MBEmlt &MBE)
{ return steigere(MBE);
//  return true;
}

#if 0
bool Abenteurer::Erlernen(MBEmlt &MBE)
{ // Erlernen später ...
}
#endif

   // false: Fehlgeschlagen
bool Abenteurer::ReduzierenVerlernen(MBEmlt &MBE, bool &verlernt)
{ verlernt=false;
  if (MBE->Reduzieren(*this))
    reduziere(MBE);
  else if ((*MBE).What()==MidgardBasicElement::WAFFE)
  { // Waffen kann man nicht verlernen
    verlernt=true;
  }
  else if (MBE->Verlernen(*this)) 
  { verlerne(MBE);
    verlernt=true;
  }
  else return false;
  return true;
}

bool Abenteurer::SpruchVonSpruchrolleGelernt(const std::string &zauber)
{ return find(list_Gelernt_von_Spruchrolle.begin(),list_Gelernt_von_Spruchrolle.end(),zauber)!=list_Gelernt_von_Spruchrolle.end() ; }

bool Abenteurer::sort_universell::operator()(const st_universell &x,const st_universell &y) const
{ return (*(x.mbe))->Name() < (*(y.mbe))->Name() ;
}
