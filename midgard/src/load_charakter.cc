/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include "midgard_CG.hh"
#include <Aux/itos.h>

#include "TagStream.hh"
#include "WindowInfo.hh"
#include "xml_fileselection.hh"
#include <Sprache.hh>
#include <Schrift.hh>
#include "Fertigkeiten_angeboren.hh"
#include "Waffe.hh"
#include "WaffeGrund.hh"
#include "Zauber.hh"
#include "Zauberwerk.hh"
#include "KiDo.hh"
#include "Beruf.hh"
//#include <SelectMatching.h>

#ifdef __MINGW__
std::string utf82iso(const std::string &s);
std::string iso2utf8(const std::string &s);
# define Latin2Screen(x) iso2utf8(x)
# define Internal2Latin(x) utf82iso(x)
#else
# define Latin2Screen(x) (x)
# define Internal2Latin(x) (x)
#endif

 
gint midgard_CG::on_laden_release_event(GdkEventButton *ev)
{
  xml_import_auswahl();
  return false;
}

void midgard_CG::xml_import_auswahl()
{
#ifndef __MINGW32__
  manage 
#else
  delete
#endif
  (new xml_fileselection(this,xml_fileselection::Load));
}


void midgard_CG::xml_import(const std::string& datei)
{
   ifstream fi(datei.c_str());
   xml_import_stream(fi);
   filename=datei;
}

void midgard_CG::xml_import_stream(istream& datei)
{
   on_neuer_charakter_clicked();
   frame_steigern->set_sensitive(true);

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
   {              InfoFenster->AppendShow("(Abenteurer in) Datei "//'"+Latin2Screen(datei)
                   " nicht gefunden.");
      return;
   }
   
   const int xml_version=top->getIntAttr("Version");
   if (xml_version<3 || xml_version>10)
   {         InfoFenster->AppendShow("XML Version "+itos(xml_version)
          +" wird noch nicht unterstützt");
   }

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
   if(getWerte().Stadt_Land()=="Stadt") table_grundwerte->radiobutton_stadt->set_active(true);
   if(getWerte().Stadt_Land()=="Land")  table_grundwerte->radiobutton_land->set_active(true);
   if (Steigern) getWerte().set_Grad_Anstieg(Steigern->getIntAttr("EPproGFP",50)
      	,Steigern->getIntAttr("Basiswerte",getWerte().Grad()));
   else getWerte().set_Grad_Anstieg(50,getWerte().Grad());

//   this->Char.Typ1()=cH_Typen(Typ->getAttr("Abkürzung"),true);
   Char.setTyp1(cH_Typen(Typ->getAttr("Abkürzung"),true));

   { std::string s = Typ->getAttr("Abkürzung2");
     if(s!="") //this->Char.Typ2=cH_Typen(s,true);
         Char.setTyp2(cH_Typen(Typ->getAttr("Abkürzung2"),true));
   }

   load_fertigkeiten(Fertigkeiten,Ausruestung,xml_version);
   load_ausruestung(Ausruestung,&(Char.getBesitz()));
   
   set_title(getWerte().Name_Abenteurer());
   load_for_mainpage(notebook_main->get_current_page_num());
   insert_into_CharList(Char);
}

void midgard_CG::load_ausruestung(const Tag *tag, AusruestungBaum *AB)
{  FOR_EACH_CONST_TAG_OF(i,*tag,"Gegenstand")
   {  cH_Preise(i->getAttr("Bezeichnung"),true);       AusruestungBaum *A = &AB->push_back(
   	Ausruestung(i->getAttr("Bezeichnung"),i->getAttr("Besonderheit")
   					,i->getBoolAttr("sichtbar")));
      A->setParent(AB);
      load_ausruestung(&*i,A);
   }
}

void midgard_CG::load_fertigkeiten(const Tag *tag, const Tag *waffen_b, int xml_version)
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
         Char.List_Beruf().push_back(beruf);
        }
      else if(sart=="ang-Fertigkeit" || sart=="ang.Fertigkeit")
       {
         cH_MidgardBasicElement fert_an(&*cH_Fertigkeit_angeborene(i->getAttr("Bezeichnung"),true));
         cH_Fertigkeit_angeborene(fert_an)->setErfolgswert(i->getIntAttr("Wert"));
         Char.List_Fertigkeit_ang().push_back(fert_an);
       }    
      else if(sart=="Fertigkeit")
       {
         cH_MidgardBasicElement fert(&*cH_Fertigkeit(i->getAttr("Bezeichnung"),true));
         fert->setErfolgswert(i->getIntAttr("Wert"));
         fert->setPraxispunkte(i->getIntAttr("Praxispunkte"));
         if(cH_Fertigkeit(fert)->ZusatzEnum(Char.getVTyp()))
         {  fert=new Fertigkeit(*cH_Fertigkeit(fert));
            if(fert->Name()=="Landeskunde") cH_Land(i->getAttr("Zusatz"),true);
            if(fert->Name()=="Scharfschießen") cH_Waffe(i->getAttr("Zusatz"),true);
            fert->setZusatz(i->getAttr("Zusatz"));
         }
         Char.List_Fertigkeit().push_back(fert);
//         if      (fert->Name()=="KiDo") kido_bool=true;
//         else 
//         if (fert->Name()=="Zaubern") magie_bool=true;
       }    
      else if(sart=="Waffe")
        {
         cH_MidgardBasicElement waffe(&*cH_Waffe(i->getAttr("Bezeichnung"),true));
         waffe->setErfolgswert(i->getIntAttr("Wert"));
         waffe->setPraxispunkte(i->getIntAttr("Praxispunkte"));
         Char.List_Waffen().push_back(waffe);
        }
#if 0 // andere Liste       
      if(sart=="Besitz_W")
#endif
      else if(sart=="Zauber")
        {
         cH_MidgardBasicElement zauber(&*cH_Zauber(i->getAttr("Bezeichnung"),true));
         if(zauber->ZusatzEnum(Char.getVTyp()))
          { zauber=new Zauber(*cH_Zauber(zauber));
            zauber->setZusatz(i->getAttr("Zusatz"));
          }
         Char.List_Zauber().push_back(zauber);
        }
      else if(sart=="Zauberwerk")
          Char.List_Zauberwerk().push_back(&*cH_Zauberwerk(i->getAttr("Bezeichnung"),
          	i->getAttr("Art"),i->getAttr("Stufe"),true));
      else if(sart=="KiDo")
          Char.List_Kido().push_back(&*cH_KiDo(i->getAttr("Bezeichnung"),true)) ;
      else if(sart=="Grundkenntnis")
          Char.List_WaffenGrund().push_back(&*cH_WaffeGrund(i->getAttr("Bezeichnung"),true));
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
         Char.List_Sprache().push_back(sprache);
        }
      else if(sart=="Urschrift") 
        {
         cH_MidgardBasicElement schrift(&*cH_Schrift(i->getAttr("Bezeichnung"),true));
         int wert=i->getIntAttr("Wert");
         if (xml_version<8 && !wert) wert=12;
         schrift->setErfolgswert(wert);
         schrift->setPraxispunkte(i->getIntAttr("Praxispunkte"));
         Char.List_Schrift().push_back(schrift);
        }
      else if(sart=="Optionen")
        {
         try{
           MOptionen->setOptionCheck(i->getAttr("Name"),i->getBoolAttr("Wert"));
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
        Char.List_Waffen_besitz().push_back(new 
	        WaffeBesitz(cH_Waffe(wn,true),
                        i->getAttr("Bezeichnung"),
                        i->getIntAttr("AngriffVerteidigung_Bonus"),
                        i->getIntAttr("SchadenLebenspunkte_Bonus"),
                        i->Value()));
    }
}

