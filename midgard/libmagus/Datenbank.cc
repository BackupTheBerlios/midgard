// $Id: Datenbank.cc,v 1.13 2003/05/26 06:23:35 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include "Datenbank.hh"

#include <MidgardBasicElement.hh>
#include <vector>
#include <string>
//#include <gtkmm/main.h>
#include "Grundwerte.hh"
#include "Land.hh"   
//#include "Pflicht.hh"
#include "Spezies.hh"
#include "Typen.hh"
#include "Grad_anstieg.hh"
#include "Lernschema.hh"
#include "Beruf.hh" 
#include "Preise.hh"
#include "Ausruestung.hh"
//#include "class_lernpunkte.hh"
#include "Zauber.hh"
#include "Zauberwerk.hh"  
#include "Fertigkeiten.hh"
#include "Waffe.hh"
#include "WaffeGrund.hh"
#include "KiDo.hh"    
#include "Region.hh"  
#include "Ruestung.hh"
#include "Fertigkeiten_angeboren.hh"
//#include "Midgard_Info.hh"
#include "Sprache.hh"
#include "Schrift.hh"
#include "magus_paths.h"
#include <Misc/inbetween.h>
#include "xml.h"

Datenbank::Datenbank() : tag_eigene_artikel("MAGUS-data")
{
}

void Datenbank::load_list(const Tag &t)
{  FOR_EACH_CONST_TAG(j,t)
   {  if (j->Type()=="Zauber")
         FOR_EACH_CONST_TAG(k,*j) Zauber_All::load(Zauber,*k);
      else if (j->Type()=="Zauberwerke")
         FOR_EACH_CONST_TAG(k,*j) Zauberwerk_All::load(Zauberwerk,*k);
      else if (j->Type()=="Fertigkeiten")
         FOR_EACH_CONST_TAG(k,*j) Fertigkeiten_All::load(Fertigkeit,*k);
      else if (j->Type()=="Berufe")
         FOR_EACH_CONST_TAG(k,*j) Beruf_All::load(Beruf,*k);
      else if (j->Type()=="Waffen")
         FOR_EACH_CONST_TAG(k,*j) Waffe_All::load(Waffe,*k);
      else if (j->Type()=="Waffen-Grundkenntnisse")
         FOR_EACH_CONST_TAG(k,*j) WaffeGrund_All::load(Waffe,*k);
      else if (j->Type()=="Kido-Fertigkeiten")
         FOR_EACH_CONST_TAG(k,*j) KiDo_All::load(Kido,*k);
      else if (j->Type()=="Sprachen")
         FOR_EACH_CONST_TAG(k,*j) Sprachen_All::load(Sprache,*k);
      else if (j->Type()=="Schriften")
         FOR_EACH_CONST_TAG(k,*j) Schriften_All::load(Schrift,*k);
      else if (j->Type()=="Waffen-Grundkenntnisse")
         FOR_EACH_CONST_TAG(k,*j) WaffeGrund_All::load(WaffeGrund,*k);
      else if (j->Type()=="angeboreneFertigkeiten")
         FOR_EACH_CONST_TAG(k,*j) Fertigkeiten_angeborene_All::load(Fertigkeit_ang,*k);
      else if (j->Type()=="Rüstungen")
         FOR_EACH_CONST_TAG(k,*j) Ruestung_All::load(Ruestung,*k);
      else if (j->Type()=="Typen")
         FOR_EACH_CONST_TAG(k,*j) Typen_All::load(Typen,*k);
      else if (j->Type()=="SpeziesListe")
         FOR_EACH_CONST_TAG(k,*j) Spezies_All::load(Spezies,*k);
      else if (j->Type()=="Gradanstieg")
         FOR_EACH_CONST_TAG_OF(k,*j,"Grad") GradAnstieg.load(*k);
      else if (j->Type()=="Länder")
         FOR_EACH_CONST_TAG(k,*j) // Kontinent
            FOR_EACH_CONST_TAG_OF(l,*k,"Land")
               Laender_All::load(Laender,k->getAttr("Name"),*l);
      else if (j->Type()=="Spezialgebiete")
         FOR_EACH_CONST_TAG_OF(k,*j,"Spezialgebiet") 
            Spezialgebiet_All::load(Spezialgebiet,*k);
      else if (j->Type()=="KI")
      {  FOR_EACH_CONST_TAG_OF(k,*j,"Prototyp2") 
            Prototyp2_All::load(prototyp2,*k);
         FOR_EACH_CONST_TAG_OF(k,*j,"Prototyp") 
            Prototyp_All::load(prototyp,*k);
      }
      else if (j->Type()=="PreiseNeuMod")
         FOR_EACH_CONST_TAG(k,*j) PreiseNewMod_All::load(preisenewmod,*k);
      else if (in<std::string>(j->Type(),"Preise","PreiseNeu"))
         FOR_EACH_CONST_TAG(k,*j) Preise_All::load(preise,*k);
      else if (j->Type()=="Waffen-Steigern")
         FOR_EACH_CONST_TAG(k,*j) 
           MidgardBasicElement::load_waffen_steigern_nach_schwierigkeit(*k);
      else if (j->Type()=="SteigernKosten")
         FOR_EACH_CONST_TAG(k,*j) 
           MidgardBasicElement::load_steigern_kosten(*k);
      else if (j->Type()=="verwendbareEP")
         FOR_EACH_CONST_TAG(k,*j) 
            Fertigkeit::EP_steigern(k->getAttr("Fertigkeit"),Fertigkeit::EP_steigern_load(*k));
   }
}

void Datenbank::load(SigC::Slot1<void,double> progress,SigC::Slot1<void,const std::string&> meldungen)
{
    xml_init(progress,meldungen,*this);
    Regionen = Regionen_All().get_All();
//    MI->set_Regionen(Regionen);
//    Laender = Laender_All().get_All();
//    Ruestung = Ruestung_All().get_All();
    lernschema = Lernschema(true);
//    Beruf = Beruf_All().get_All();
//    Fertigkeit_ang = Fertigkeiten_angeborene_All().get_All();
//    Fertigkeit = Fertigkeiten_All().get_All();
//    WaffeGrund = WaffeGrund_All().get_All();
//    Waffe = Waffe_All().get_All();
//    Zauber = Zauber_All().get_All();
//    Zauberwerk = Zauberwerk_All().get_All();
//    Kido = KiDo_All().get_All();
//    Sprache = Sprachen_All().get_All();
//    Schrift = Schriften_All().get_All();
//    Spezies = Spezies_All().get_All();
//    Typen = Typen_All().get_All();
//    GradAnstieg = Grad_anstieg(true);
//    Spezialgebiet = Spezialgebiet_All().get_All();
//    preise = Preise_All(magus_paths::with_path("magus_preise.xml",false,true),tag_eigene_artikel).get_All();
//    preisenewmod = PreiseNewMod_All().get_All();
//    prototyp = Prototyp_All().get_All();
//    prototyp2 = Prototyp2_All().get_All();
//    MI->database_hide();  // can't do this yet
//    Waffe_from_Alias = Waffe::fill_map_alias_waffe();
   GradAnstieg.init_after_load();
}

