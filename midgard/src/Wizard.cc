
#if 0
#include "config.h"
#include "Wizard.hh"
#include "midgard_CG.hh"

namespace Wizard
{  
     struct st_wiz
     {  int page;
        std::string text;
        st_wiz(int p,std::string t)
            : page(p),text(t){}
     };

      static std::vector<st_wiz> vecwiz;
      static void fill_vecwiz();

      void evaluate_step(esteps step);
}


void Wizard::evaluate_step(esteps step)
{
  hauptfenster->wizard_do_something(vecwiz[step].page,vecwiz[step].text);
}


void Wizard::fill_vecwiz()
{  if (!vecwiz.empty()) return;
#error besser resize + []
   // Inaktiv
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
   			  "Wizard inaktiv"));
   //START
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Hier erscheint jeweils der n�chste Schritt f�r einen neuen Abenteurer."));
   //SPEZIES
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Spezies auswählen (oder Eigenschaften auf eine der drei Arten würfeln)"));
   //GRUNDWERTE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Eigenschaften auf eine der drei Arten würfeln (ACHTUNG: Für Nichtmenschen ist nur die Standardmethode implementiert)"));
   //GESCHLECHT
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Geschlecht wählen (oder Abenteuertyp auswählen).)"));
   //TYP
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Abenteurertyp wählen"));
   //STADTLAND
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Stadt oder Land wählen (oder abgeleitete Werte wählen)"));
   //ABGELEITETEWERTE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Abgeleitete Werte wärfeln"));
   //LERNSCHEMA_SEITE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Auf die 'Lernschema'-Seite umblättern"));
   //HERKUNFT
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Herkunftsland wählen"));
   //UEBERLEBEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "In welchem Geländetyp wird 'überleben' als universelle Fertigkeit beherrscht?"));
   //ANGEBORENEFERTIGKEITEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Angeborenen Fertigkeiten würfeln"));
   //LERNPUNKTE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Lernpunkte würfeln"));
   //WAEHLEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Jetzt Fertigkeiten, Waffen und ev. Zauber in beliebiger"
                          " Reinfolge lernen (anklicken) bis alle Lernpunkte"
                          " verbraucht sind und anschließen den Beruf wählen."));
   //BERUF1
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Fertigkeit auswählen, die aufgrund der Berufswahl"
                          " gelernt werden kann, danach das Geld auswürfeln."));
   //BERUF
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Berufsfertigkeit aus Liste wählen"));
   //GELD
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Geld auswürfeln"));
   //WAFFEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Waffen auswürfeln"));
   //RUESTUNG
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Rüstung auswürfeln"));
   //AUSRUESTUNG
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Ausrüstung auswürfeln"));
   //SPEZIALWAFFE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Spezialwaffe wählen (anklicken)"));
   //SPEZIAGEBIET
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Magier sollten ein Spezialgebiet wählen (das kann aber auch später geschehen)"));
   //NAMEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Namen vergeben (Eingabe mit 'Enter' abschließen)"));
   //SPEICHERN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Speichern"));
   //FERTIG
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Fertig"));
   assert(vecwiz.size()==int(FERTIG)+1);
}


#endif