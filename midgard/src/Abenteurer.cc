// $Id: Abenteurer.cc,v 1.3 2002/05/30 17:30:52 thoma Exp $            
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
#include "export_common.h"
#include "TagStream.hh"
#include "Preise.hh"
#include "midgard_CG.hh"
#include <Aux/itos.h>
#include <Sprache.hh>
#include <Schrift.hh>
#include "Fertigkeiten_angeboren.hh"
#include "Waffe.hh"
#include "WaffeGrund.hh"
#include "Zauber.hh"
#include "Zauberwerk.hh"
#include "KiDo.hh"
#include "Beruf.hh"


void VAbenteurer::push_back(Abenteurer A)
{ 
   VA.push_back(st_abenteurer(A,true)); 
   ai=VA.end()-1; 
}


void VAbenteurer::set_Abenteurer(const Abenteurer& A)
{ 
   for(std::vector<st_abenteurer>::iterator i=VA.begin();i!=VA.end();++i)
      if(i->abenteurer==A) ai=i;
}


bool VAbenteurer::unsaved_exist()
{ 
   for(std::vector<st_abenteurer>::iterator i=VA.begin();i!=VA.end();++i)
       if(!i->gespeichert) return true;
   return false;
}
                                             

///////////////////////////////////////////////////////////////////
#ifdef __MINGW__
std::string utf82iso(const std::string &s);
std::string iso2utf8(const std::string &s);
# define Latin2Screen(x) iso2utf8(x)
# define Internal2Latin(x) utf82iso(x)
#else
# define Latin2Screen(x) (x)
# define Internal2Latin(x) (x)
#endif

void Abenteurer::speicherstream(ostream &datei,const Datenbank &Database,const Midgard_Optionen *Optionen)
{
   datei << "<?xml";
   write_string_attrib(datei, "version", "1.0");
   write_string_attrib(datei, "encoding", "ISO-8859-1"); // TagStream::host_encoding);
   datei << "?>\n\n";
   datei << "<MAGUS-data>\n";

// Vielleicht hier eingegebene Ausrüstung speichern wie in anderen Dateien
// oder ganz unten?
   datei << " <Preise>\n";
   for (std::list<cH_Preise>::const_iterator i=Database.preise.begin();i!=Database.preise.end();++i)
   {  if ((*i)->ist_eigener_Artikel())
      {  datei << "  <Kaufpreis";
         write_string_attrib(datei, "Ware", Internal2Latin((*i)->Name()));
         write_string_attrib(datei, "Art", Internal2Latin((*i)->Art()));
         write_string_attrib(datei, "Art2", Internal2Latin((*i)->Art2()));
         write_float_attrib(datei, "Preis", (*i)->Kosten());
         write_string_attrib(datei, "Währung", Internal2Latin((*i)->Einheit()));
         write_float_attrib(datei, "Gewicht", (*i)->Gewicht());
         datei << "/>\n";
      }
   }
   datei << " </Preise>\n\n";
   
   datei << " <Midgard-Abenteurer";
   write_int_attrib(datei,"Version",10);
   datei << ">\n";

   grundwerte_speichern(datei);
   datei << Internal2Latin("  <Ausrüstung>\n");
   write_string(datei, Internal2Latin("Rüstung"), getCWerte().Ruestung()->Name(), 4);
   write_string(datei, Internal2Latin("Rüstung2"), getCWerte().Ruestung(1)->Name(), 4);
   // Waffen Besitz
   for (std::list<cH_MidgardBasicElement>::const_iterator i=CList_Waffen_besitz().begin();
         i!=CList_Waffen_besitz().end();++i)
      {  cH_WaffeBesitz WB(*i);
         datei << "    <Waffe";
         write_string_attrib(datei, "Bezeichnung", Internal2Latin(WB->Name()));
         write_int_attrib(datei, "AngriffVerteidigung_Bonus", WB->av_Bonus());
         write_int_attrib(datei, "SchadenLebenspunkte_Bonus", WB->sl_Bonus());
         write_string_attrib(datei, "Region", Internal2Latin(WB->Region()));
         if (WB->Magisch().empty()) datei << "/>\n";
         else datei << '>' << Internal2Latin(WB->Magisch()) << "</Waffe>\n";
      }
   save_ausruestung(datei, getCBesitz().getChildren());
   datei << Internal2Latin("  </Ausrüstung>\n");
   
   datei << "  <Fertigkeiten>\n";   

   MidgardBasicElement::saveElementliste(datei,getCWerte().Sinne(),getCWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(datei,CList_Beruf(),getCWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(datei,CList_Fertigkeit_ang(),getCWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(datei,CList_Fertigkeit(),getCWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(datei,CList_Waffen(),getCWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(datei,CList_Zauber(),getCWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(datei,CList_Zauberwerk(),getCWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(datei,CList_Kido(),getCWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(datei,CList_WaffenGrund(),getCWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(datei,CList_Sprache(),getCWerte(),getVTyp());
   MidgardBasicElement::saveElementliste(datei,CList_Schrift(),getCWerte(),getVTyp());

   // Regionen & Ähnliches
  for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
   {  if (!(*i)->Active()) continue;
      datei << "    <Region";
      write_string_attrib(datei, "Name", Internal2Latin((*i)->Name()));
      write_string_attrib(datei, "Region", Internal2Latin((*i)->Abkuerzung()));
      datei << "/>\n";
   }
   // Optionen
   const std::list<Midgard_Optionen::st_OptionenCheck> LO=Optionen->getOptionenCheck();
   for(std::list<Midgard_Optionen::st_OptionenCheck>::const_iterator i=LO.begin();i!=LO.end();++i)
   {
     // Option, die mit dem C. gespeichert werden müssen
     if(i->index!=Midgard_Optionen::Original && i->index!=Midgard_Optionen::NSC_only) continue; 
     datei << "    <Optionen";
     write_string_attrib(datei, "Name", Internal2Latin(i->text));
     write_bool_attrib_force(datei, "Wert", Internal2Latin(i->active));
     datei << "/>\n";
   }
   datei << "  </Fertigkeiten>\n";   
   datei << " </Midgard-Abenteurer>\n";
   datei << "</MAGUS-data>\n";
}


void Abenteurer::grundwerte_speichern(ostream &datei)
{
   datei << "  <Figur";
   write_string_attrib(datei, "Name", Internal2Latin(getCWerte().Name_Abenteurer()));
   write_string_attrib(datei, "Spieler", Internal2Latin(getCWerte().Name_Spieler()));
   write_string_attrib(datei, "Zeitpunkt", Internal2Latin(getCWerte().Version()));
   write_int_attrib(datei, "Grad", getCWerte().Grad());
   datei << "/>\n";
   datei << "  <Typ";
   write_string_attrib(datei, "Spezies", Internal2Latin(getCWerte().Spezies()->Name()));
   write_string_attrib(datei, "Geschlecht", Internal2Latin(getCWerte().Geschlecht()));
   write_string_attrib(datei, Internal2Latin("Abkürzung"), Internal2Latin(CTyp1()->Short()));
   write_string_attrib(datei, Internal2Latin("Abkürzung2"), Internal2Latin(CTyp2()->Short()));
   write_string_attrib(datei, "Spezialgebiet", Internal2Latin(getCWerte().Spezialgebiet()->Name()));
   write_string_attrib(datei, "Spezialisierung", Internal2Latin(getCWerte().Spezialisierung()));
   write_string_attrib(datei, "Stadt_Land", Internal2Latin(getCWerte().Stadt_Land()));
   write_string_attrib(datei, "Hand", Internal2Latin(getCWerte().Hand()));
   datei << "/>\n";
   datei << "  <Basiseigenschaften";
   write_int_attrib(datei, "St", getCWerte().St());
   write_int_attrib(datei, "Gw", getCWerte().Gw());
   write_int_attrib(datei, "Gs", getCWerte().Gs());
   write_int_attrib(datei, "Ko", getCWerte().Ko());
   write_int_attrib(datei, "In", getCWerte().In());
   write_int_attrib(datei, "Zt", getCWerte().Zt());
   datei << "/>\n";
   datei << "  <abgeleiteteEigenschaften";
   write_int_attrib(datei, "Au", getCWerte().Au());
   write_int_attrib(datei, "pA", getCWerte().pA());
   write_int_attrib(datei, "Wk", getCWerte().Wk());
   write_int_attrib(datei, "Sb", getCWerte().Sb());
   write_int_attrib(datei, "B", getCWerte().B());
//   write_int_attrib(datei, "KAW", getCWerte().St());
//   write_int_attrib(datei, "WLW", getCWerte().St());
   write_int_attrib(datei, "GG", getCWerte().GG());
   write_int_attrib(datei, "SG", getCWerte().SG());
   datei << "/>\n";
   datei << "  <Erfolgswerte";
   write_int_attrib(datei, "Abwehr", getCWerte().Abwehr_wert());
   write_int_attrib(datei, "Zaubern", getCWerte().Zaubern_wert());
   write_int_attrib(datei, "ZauberResistenz", getCWerte().Resistenz());
   datei << "/>\n";
   datei << "  <Gesundheit"; // schlechter Name ?
//   write_int_attrib(datei, "LP_Basis");
   write_int_attrib(datei, "LP", getCWerte().LP());
   write_int_attrib(datei, "AP", getCWerte().AP());
   datei << "/>\n";
   datei << "  <Beschreibung"; // soziale?
   write_int_attrib(datei, "Alter", getCWerte().Alter());
   write_string_attrib(datei, "Gestalt", Internal2Latin(getCWerte().Gestalt()));
   write_int_attrib(datei, "Gewicht", getCWerte().Gewicht());
   write_int_attrib(datei, Internal2Latin("Größe"), getCWerte().Groesse());
   write_string_attrib(datei, "Stand", Internal2Latin(getCWerte().Stand()));
   write_string_attrib(datei, "Bezeichnung", Internal2Latin(getCWerte().Bezeichnung()));
   write_string_attrib(datei, "Herkunft", Internal2Latin(getCWerte().Herkunft()->Name()));
   write_string_attrib(datei, "Glaube", Internal2Latin(getCWerte().Glaube()));
   datei << "/>\n";
   datei << Internal2Latin("  <Vermögen");
   write_int_attrib(datei, "GS", getCWerte().Gold());
   write_int_attrib(datei, "SS", getCWerte().Silber());
   write_int_attrib(datei, "KS", getCWerte().Kupfer());
   datei << "/>\n";
   datei << "  <Steigern";
   write_int_attrib(datei, "GFP", getCWerte().GFP());
   write_int_attrib(datei, "AEP", getCWerte().AEP());
   write_int_attrib(datei, "KEP", getCWerte().KEP());
   write_int_attrib(datei, "ZEP", getCWerte().ZEP());
   write_int_attrib(datei, "EPproGFP", getCWerte().get_Steigern_EP_Prozent(), 50);
   write_int_attrib(datei, "Basiswerte", getCWerte().get_Grad_Basiswerte(), getCWerte().Grad());
   write_float_attrib(datei, Internal2Latin("benötigte_Tage"), getCWerte().Steigertage());
   datei << "><Praxispunkte";
   write_int_attrib(datei, "Abwehr", getCWerte().AbwehrPP());
   write_int_attrib(datei, "Zaubern", getCWerte().ZaubernPP());
   write_int_attrib(datei, "Spezial", getCWerte().SpezialPP());
   write_int_attrib(datei, "Resistenz", getCWerte().ResistenzPP());
   datei << "/></Steigern>\n";
   write_string(datei, "Text", Internal2Latin(getCWerte().Beschreibung()), 2);
   write_string(datei, "TextPix", Internal2Latin(getCWerte().BeschreibungPix()), 2);
   write_string(datei, "TextPixSize", itos(getCWerte().BeschreibungPixSize()), 2);
}

void Abenteurer::save_ausruestung(ostream &datei,const list<AusruestungBaum> &AB, const int indent)
{  
  for(AusruestungBaum::const_iterator i=AB.begin();i!=AB.end();++i)
   {  datei << string(indent,' ') << "<Gegenstand";
      write_string_attrib(datei, "Bezeichnung", Internal2Latin(i->getAusruestung().Name()));
      write_string_attrib(datei, "Besonderheit", Internal2Latin(i->getAusruestung().Material()));
      write_bool_attrib(datei, "sichtbar", i->getAusruestung().Sichtbar());
      if (i->empty()) datei << "/>\n";
      else
      {  datei << ">\n";
         save_ausruestung(datei, i->getChildren(), indent+2);
         datei << string(indent,' ') << "</Gegenstand>\n";
      }
   }
}

///////////////////////////////////////////////////////////////////////////////

void Abenteurer::xml_import_stream(istream& datei, Datenbank &Database,
   Midgard_Optionen *Optionen)
{

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
      return;
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
   getWerte().setSpezialisierung(Typ->getAttr("Spezialisierung"));
   getWerte().setBezeichnung(Beschreibung->getAttr("Bezeichnung"));
   getWerte().setHerkunft(cH_Land(Beschreibung->getAttr("Herkunft"),true));
   getWerte().setGlaube(Beschreibung->getAttr("Glaube"));
   getWerte().setNamen(Figur->getAttr("Name"),Figur->getAttr("Spieler"),Figur->getAttr("Zeitpunkt"));
   getWerte().setGFP(Steigern ? Steigern->getIntAttr("GFP", top->getInt("GFP")) : top->getInt("GFP"));
   getWerte().setSteigertage(Steigern ? Steigern->getFloatAttr("benötigte_Tage", top->getInt("benötigte_Tage")) : top->getInt("benötigte_Tage"));
   getWerte().setGG(abgeleiteteEigenschaften->getIntAttr("GG"));    
   getWerte().setSG(abgeleiteteEigenschaften->getIntAttr("SG"));
   getWerte().setBeschreibung(top->getString("Text")); 
   getWerte().setBeschreibungPix(top->getString("TextPix")); 
   getWerte().setBeschreibungPixSize(atoi(top->getString("TextPixSize").c_str())); 
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
   getWerte().setStadt_Land(Typ->getAttr("Stadt_Land","Stadt"));
   if (Steigern) getWerte().set_Grad_Anstieg(Steigern->getIntAttr("EPproGFP",50)
      	,Steigern->getIntAttr("Basiswerte",getWerte().Grad()));
   else getWerte().set_Grad_Anstieg(50,getWerte().Grad());

//   this->Typ1()=cH_Typen(Typ->getAttr("Abkürzung"),true);
   setTyp1(cH_Typen(Typ->getAttr("Abkürzung"),true));

   { std::string s = Typ->getAttr("Abkürzung2");
     if(s!="") //this->Typ2=cH_Typen(s,true);
         setTyp2(cH_Typen(Typ->getAttr("Abkürzung2"),true));
   }

   load_fertigkeiten(Fertigkeiten,Ausruestung,xml_version,Database,Optionen);
   load_ausruestung(Ausruestung,&(getBesitz()));
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

void Abenteurer::load_fertigkeiten(const Tag *tag, const Tag *waffen_b, int xml_version,Datenbank &Database,Midgard_Optionen *Optionen)
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
         cH_Beruf(beruf)->setErfolgswert(i->getIntAttr("Wert"));
         List_Beruf().push_back(beruf);
        }
      else if(sart=="ang-Fertigkeit" || sart=="ang.Fertigkeit")
       {
         cH_MidgardBasicElement fert_an(&*cH_Fertigkeit_angeborene(i->getAttr("Bezeichnung"),true));
         cH_Fertigkeit_angeborene(fert_an)->setErfolgswert(i->getIntAttr("Wert"));
         List_Fertigkeit_ang().push_back(fert_an);
       }    
      else if(sart=="Fertigkeit")
       {
         cH_MidgardBasicElement fert(&*cH_Fertigkeit(i->getAttr("Bezeichnung"),true));
         fert->setErfolgswert(i->getIntAttr("Wert"));
         fert->setPraxispunkte(i->getIntAttr("Praxispunkte"));
         if(cH_Fertigkeit(fert)->ZusatzEnum(getVTyp()))
         {  fert=new Fertigkeit(*cH_Fertigkeit(fert));
            if(fert->Name()=="Landeskunde") cH_Land(i->getAttr("Zusatz"),true);
            if(fert->Name()=="Scharfschießen") cH_Waffe(i->getAttr("Zusatz"),true);
            fert->setZusatz(i->getAttr("Zusatz"));
         }
         List_Fertigkeit().push_back(fert);
       }    
      else if(sart=="Waffe")
        {
         cH_MidgardBasicElement waffe(&*cH_Waffe(i->getAttr("Bezeichnung"),true));
         waffe->setErfolgswert(i->getIntAttr("Wert"));
         waffe->setPraxispunkte(i->getIntAttr("Praxispunkte"));
         List_Waffen().push_back(waffe);
        }
#if 0 // andere Liste       
      if(sart=="Besitz_W")
#endif
      else if(sart=="Zauber")
        {
         cH_MidgardBasicElement zauber(&*cH_Zauber(i->getAttr("Bezeichnung"),true));
         if(zauber->ZusatzEnum(getVTyp()))
          { zauber=new Zauber(*cH_Zauber(zauber));
            zauber->setZusatz(i->getAttr("Zusatz"));
          }
         List_Zauber().push_back(zauber);
        }
      else if(sart=="Zauberwerk")
          List_Zauberwerk().push_back(&*cH_Zauberwerk(i->getAttr("Bezeichnung"),
          	i->getAttr("Art"),i->getAttr("Stufe"),true));
      else if(sart=="KiDo")
          List_Kido().push_back(&*cH_KiDo(i->getAttr("Bezeichnung"),true)) ;
      else if(sart=="Grundkenntnis")
          List_WaffenGrund().push_back(&*cH_WaffeGrund(i->getAttr("Bezeichnung"),true));
      else if(sart=="Sprache")
        {
         cH_MidgardBasicElement sprache(&*cH_Sprache(i->getAttr("Bezeichnung"),true));
         int wert=i->getIntAttr("Wert");
         if (xml_version<8)          {  switch (wert)
            {  case 1: wert=4; break;
               case 2: wert=6; break;
               case 3: wert=10; break;
               case 4: wert=13; break;
            }
         }
         sprache->setErfolgswert(wert);
         sprache->setPraxispunkte(i->getIntAttr("Praxispunkte"));
         List_Sprache().push_back(sprache);
        }
      else if(sart=="Urschrift") 
        {
         cH_MidgardBasicElement schrift(&*cH_Schrift(i->getAttr("Bezeichnung"),true));
         int wert=i->getIntAttr("Wert");
         if (xml_version<8 && !wert) wert=12;
         schrift->setErfolgswert(wert);
         schrift->setPraxispunkte(i->getIntAttr("Praxispunkte"));
         List_Schrift().push_back(schrift);
        }
      else if(sart=="Optionen")
        {
         try{
           Optionen->setOptionCheck(i->getAttr("Name"),i->getBoolAttr("Wert"));
         }
         catch (const NotFound &e)
         {}
        }
      else if(sart=="Region")
        {
         try
         {  cH_Region R(i->getAttr("Name",i->getAttr("Region")));
            Region::setActive(Database.Regionen,R,true);
         }
         catch (const NotFound &e)
         {}
        }
    } 
    FOR_EACH_CONST_TAG_OF(i,*waffen_b,"Waffe")
    {   std::string wn = Database.Waffe_from_Alias[i->getAttr("Bezeichnung")];
        if (wn=="") wn=i->getAttr("Bezeichnung"); 
        List_Waffen_besitz().push_back(new 
	        WaffeBesitz(cH_Waffe(wn,true),
                        i->getAttr("Bezeichnung"),
                        i->getIntAttr("AngriffVerteidigung_Bonus"),
                        i->getIntAttr("SchadenLebenspunkte_Bonus"),
                        i->Value()));
    }
}

