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
#include <SelectMatching.h>

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
         if (!top) top=data->find("Midgard-Abenteurer");       }
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
   const Tag *Vermoegen=top->find("Vermoegen");    if (!Vermoegen) Vermoegen=top->find("Vermögen");    const Tag *Ruestung=top->find("Ruestung");    if (!Ruestung) Ruestung=top->find("Rüstung");    const Tag *Ausruestung=top->find("Ausrüstung");    if (!Ausruestung) Ausruestung=top->find("Fertigkeiten");    if (!Ruestung) Ruestung=Ausruestung->find("Rüstung");    const Tag *Fertigkeiten=top->find("Fertigkeiten");
   const Tag *Steigern=top->find("Steigern");
   const Tag *Praxispunkte=Steigern?Steigern->find("Praxispunkte"):0;

   Werte.setBasiswerte(Basiseigenschaften->getIntAttr("St"),
   	Basiseigenschaften->getIntAttr("Gw",abgeleiteteEigenschaften->getIntAttr("RW")),
   	Basiseigenschaften->getIntAttr("Gs",Basiseigenschaften->getIntAttr("Ge")),
   	Basiseigenschaften->getIntAttr("Ko"),
   	Basiseigenschaften->getIntAttr("In"),
   	Basiseigenschaften->getIntAttr("Zt"));
   Werte.setAu(abgeleiteteEigenschaften->getIntAttr("Au"));
   Werte.setpA(abgeleiteteEigenschaften->getIntAttr("pA"));
   Werte.setSb(abgeleiteteEigenschaften->getIntAttr("Sb"));
   Werte.setWk(abgeleiteteEigenschaften->getIntAttr("Wk"));
   Werte.setB(abgeleiteteEigenschaften->getIntAttr("B"));
   Werte.setLP(Gesundheit->getIntAttr("LP"));
   Werte.setAP(Gesundheit->getIntAttr("AP"));
   Werte.setZaubern_wert(Erfolgswerte->getIntAttr("Zaubern"));
   Werte.setAbwehr_wert(Erfolgswerte->getIntAttr("Abwehr"));
   Werte.setResistenz(Erfolgswerte->getIntAttr("ZauberResistenz",
  	!Resistenzen?0:Resistenzen->getIntAttr("Zauber",Resistenzen->getIntAttr("Resistenz",Resistenzen->getIntAttr("psy")))));
   if (Praxispunkte)
   {  Werte.setZaubernPP(Praxispunkte->getIntAttr("Zaubern"));
      Werte.setSpezialPP(Praxispunkte->getIntAttr("Spezial"));
      Werte.setAbwehrPP(Praxispunkte->getIntAttr("Abwehr"));
      Werte.setResistenzPP(Praxispunkte->getIntAttr("Resistenz"));    }
   else
   {  Werte.setZaubernPP(0);
      Werte.setAbwehrPP(0);
      Werte.setSpezialPP(0);
      Werte.setResistenzPP(0);
   }
   Werte.setHand(Typ->getAttr("Hand"));
   Werte.setGewicht(Beschreibung->getIntAttr("Gewicht"));
   Werte.setGroesse(Beschreibung->getIntAttr("Größe"));
   Werte.setGrad(Figur->getIntAttr("Grad"));
   Werte.setStand(Beschreibung->getAttr("Stand"));

   Werte.setAlter(Beschreibung->getIntAttr("Alter")); 
   Werte.setGeschlecht(Typ->getAttr("Geschlecht","m"));
   std::string spezialgebiet=Typ->getAttr("Spezialgebiet");
   if(spezialgebiet!="") 
     { 
       cH_Spezialgebiet S(spezialgebiet);
       Werte.setSpezialgebiet(S);
     }
   Werte.setSpezialisierung(Typ->getAttr("Spezialisierung"));
   Werte.setBezeichnung(Beschreibung->getAttr("Bezeichnung"));
   Werte.setHerkunft(cH_Land(Beschreibung->getAttr("Herkunft"),true));
   Werte.setGlaube(Beschreibung->getAttr("Glaube"));
   Werte.setNamen(Figur->getAttr("Name"),Figur->getAttr("Spieler"),Figur->getAttr("Zeitpunkt"));
   Werte.setGFP(Steigern ? Steigern->getIntAttr("GFP", top->getInt("GFP")) : top->getInt("GFP"));
   Werte.setSteigertage(Steigern ? Steigern->getFloatAttr("benötigte_Tage", top->getInt("benötigte_Tage")) : top->getInt("benötigte_Tage"));
   Werte.setGG(abgeleiteteEigenschaften->getIntAttr("GG"));    
   Werte.setSG(abgeleiteteEigenschaften->getIntAttr("SG"));
   Werte.setBeschreibung(top->getString("Text")); 
   Werte.setBeschreibungPix(top->getString("TextPix")); 
   Werte.setBeschreibungPixSize(atoi(top->getString("TextPixSize").c_str())); 
   Werte.setGeld(Vermoegen->getIntAttr("GS"),Vermoegen->getIntAttr("SS"),Vermoegen->getIntAttr("KS"));
   if (Ruestung) Werte.setRuestung(cH_Ruestung(Ruestung->Value(),true));
   else Werte.setRuestung(cH_Ruestung("OR",true));
   Werte.setSpezies(cH_Spezies(Typ->getAttr("Spezies","Mensch"),true));
   if (Steigern)       Werte.setEP(Steigern->getIntAttr("AEP"),Steigern->getIntAttr("KEP"),Steigern->getIntAttr("ZEP"));
   else
      Werte.setEP(0,0,0);
   Werte.setStadt_Land(Typ->getAttr("Stadt_Land","Stadt"));
   if(Werte.Stadt_Land()=="Stadt") radiobutton_stadt->set_active(true);
   if(Werte.Stadt_Land()=="Land")  radiobutton_land->set_active(true);
   if (Steigern)
      Database.GradAnstieg.set_Grad_Anstieg(Steigern->getIntAttr("EPproGFP",50)
      	,Steigern->getIntAttr("Basiswerte",Werte.Grad()));
   else Database.GradAnstieg.set_Grad_Anstieg(50,Werte.Grad());

      this->Typ[0]=cH_Typen(Typ->getAttr("Abkürzung"),true);

   { std::string s = Typ->getAttr("Abkürzung2");
     if(s!="") this->Typ[1]=cH_Typen(s,true);
   }

   load_fertigkeiten(Fertigkeiten,Ausruestung,xml_version);
   Typ_Geschlecht_Spezies_setzen();
   load_ausruestung(Ausruestung,&besitz);
   
//   filename=datei;
   load_for_mainpage(notebook_main->get_current_page_num());
}

void midgard_CG::Typ_Geschlecht_Spezies_setzen() 
{  
   if (Werte.Geschlecht()=="w") radiobutton_frau->set_active(true);
   if (Werte.Geschlecht()=="m") radiobutton_mann->set_active(true);

   fill_typauswahl();
   if(!Typ[1]->Short().empty()) fill_typauswahl_2();
   
   if (this->Typ[0]->Spezialwaffe() ||  this->Typ[1]->Spezialwaffe() )
         togglebutton_spezialwaffe->show();
   else {togglebutton_spezialwaffe->hide();
         togglebutton_spezialwaffe->set_active(false); }

   menu_init();
   Gtk::Menu_Helpers::SelectMatching(*optionmenu_spezies,Werte.Spezies());
   show_gtk();
   if(Werte.Spezialgebiet()->Name()!="") 
     { 
       show_magier_spezialgebiet(true);
       Gtk::Menu_Helpers::SelectMatching(*option_magier_spezialgebiet,Werte.Spezialgebiet());
     }
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
         Werte.setSinn(i->getAttr("Bezeichnung"),i->getIntAttr("Wert"));
        }
      else if(sart=="Beruf")
        {
         cH_MidgardBasicElement beruf(&*cH_Beruf(i->getAttr("Bezeichnung"),true));
         cH_Beruf(beruf)->setErfolgswert(i->getIntAttr("Wert"));
         list_Beruf.push_back(beruf);
        }
      else if(sart=="ang-Fertigkeit" || sart=="ang.Fertigkeit")
       {
         cH_MidgardBasicElement fert_an(&*cH_Fertigkeit_angeborene(i->getAttr("Bezeichnung"),true));
         cH_Fertigkeit_angeborene(fert_an)->setErfolgswert(i->getIntAttr("Wert"));
         list_Fertigkeit_ang.push_back(fert_an);
       }    
      else if(sart=="Fertigkeit")
       {
         cH_MidgardBasicElement fert(&*cH_Fertigkeit(i->getAttr("Bezeichnung"),true));
         fert->setErfolgswert(i->getIntAttr("Wert"));
         fert->setPraxispunkte(i->getIntAttr("Praxispunkte"));
         if(cH_Fertigkeit(fert)->ZusatzEnum(Typ))
         {  fert=new Fertigkeit(*cH_Fertigkeit(fert));
            if(fert->Name()=="Landeskunde") cH_Land(i->getAttr("Zusatz"),true);
            if(fert->Name()=="Scharfschießen") cH_Waffe(i->getAttr("Zusatz"),true);
            fert->setZusatz(i->getAttr("Zusatz"));
         }
         list_Fertigkeit.push_back(fert);
//         if      (fert->Name()=="KiDo") kido_bool=true;
//         else 
         if (fert->Name()=="Zaubern") magie_bool=true;
       }    
      else if(sart=="Waffe")
        {
         cH_MidgardBasicElement waffe(&*cH_Waffe(i->getAttr("Bezeichnung"),true));
         waffe->setErfolgswert(i->getIntAttr("Wert"));
         waffe->setPraxispunkte(i->getIntAttr("Praxispunkte"));
         list_Waffen.push_back(waffe);
        }
#if 0 // andere Liste       
      if(sart=="Besitz_W")
#endif
      else if(sart=="Zauber")
        {
         cH_MidgardBasicElement zauber(&*cH_Zauber(i->getAttr("Bezeichnung"),true));
         if(zauber->ZusatzEnum(Typ))
          { zauber=new Zauber(*cH_Zauber(zauber));
            zauber->setZusatz(i->getAttr("Zusatz"));
          }
         list_Zauber.push_back(zauber);
        }
      else if(sart=="Zauberwerk")
          list_Zauberwerk.push_back(&*cH_Zauberwerk(i->getAttr("Bezeichnung"),
          	i->getAttr("Art"),i->getAttr("Stufe"),true));
      else if(sart=="KiDo")
          list_Kido.push_back(&*cH_KiDo(i->getAttr("Bezeichnung"),true)) ;
      else if(sart=="Grundkenntnis")
          list_WaffenGrund.push_back(&*cH_WaffeGrund(i->getAttr("Bezeichnung"),true));
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
         list_Sprache.push_back(sprache);
        }
      else if(sart=="Urschrift") 
        {
         cH_MidgardBasicElement schrift(&*cH_Schrift(i->getAttr("Bezeichnung"),true));
         int wert=i->getIntAttr("Wert");
         if (xml_version<8 && !wert) wert=12;
         schrift->setErfolgswert(wert);
         schrift->setPraxispunkte(i->getIntAttr("Praxispunkte"));
         list_Schrift.push_back(schrift);
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
        list_Waffen_besitz.push_back(new 
	        WaffeBesitz(cH_Waffe(wn,true),
                        i->getAttr("Bezeichnung"),
                        i->getIntAttr("AngriffVerteidigung_Bonus"),
                        i->getIntAttr("SchadenLebenspunkte_Bonus"),
                        i->Value()));
    }
}

