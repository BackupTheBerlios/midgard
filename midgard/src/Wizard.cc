
#include "config.h"
#include "Wizard.hh"


#include "midgard_CG.hh"

Wizard::esteps &operator++(Wizard::esteps &a)
{  
   a= Wizard::esteps(int(a)+1);
   if(a==Wizard::MAXSTEPS) a=Wizard::esteps(int(Wizard::MAXSTEPS)-1);
   return a;
}

Wizard::Wizard(midgard_CG* h)
: hauptfenster(h), actual_step(START)
{
  fill_vecwiz();
  hauptfenster->show_wizard_active(true);
}


void Wizard::next_step(esteps e)
{
  actual_step=++e;
  evaluate_step(actual_step);
}

void Wizard::restart()
{
 actual_step=START;
 evaluate_step(++actual_step);
}


void Wizard::evaluate_step(esteps step)
{
  assert(vecwiz.size()>(size_t)(step));
//  std::vector<cH_Typen> Typ=hauptfenster->getVTyp();
//cout <<"evaluate_step " <<step<<' '<<LERNSCHEMA_SEITE<<' '<<SPEZIALWAFFE<<' '<<SPEZIALGEBIET<<'\n';
//  if(step==LERNSCHEMA_SEITE) { next_step(LERNSCHEMA_SEITE); return;}

  if(step==SPEZIALWAFFE&&(!hauptfenster->getChar()->Typ1()->Spezialwaffe()&&!hauptfenster->getChar()->Typ2()->Spezialwaffe()))
   {
     next_step(SPEZIALWAFFE);
     return;
   }
  if(step==SPEZIALGEBIET&&(!hauptfenster->getChar()->Typ1()->Spezialgebiet()&&!hauptfenster->getChar()->Typ2()->Spezialgebiet()))
   {
     next_step(SPEZIALGEBIET);
     return;
   }
  hauptfenster->notebook_main->set_current_page(vecwiz[step].page);
  hauptfenster->set_wizard(vecwiz[step].text);
  hauptfenster->wizard_do_something();

}


void Wizard::fill_vecwiz()
{
   //START
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Dieser Wizard hilft einen neuen Abenteurer zu erzeugen.\n"
                          "'Weiter' führt jeweils den nächsten Schritt aus.",
                          "Neuanfang",
                          &midgard_CG::wizard_do_something));
   //SPEZIES
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Spezies auswählen (oder Eigenschaften auf eine der drei Arten würfeln)",
                          "Spezies",
                          &midgard_CG::wizard_do_something));
   //GRUNDWERTE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Eigenschaften auf eine der drei Arten würfeln (ACHTUNG: Für Nichtmenschen ist nur die Standardmethode implementiert)",
                          "Eigenschaften",
                          &midgard_CG::wizard_do_something));
   //GESCHLECHT
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Geschlecht wählen (oder Abenteuertyp auswählen).)",
                          "Geschlecht",
                          &midgard_CG::wizard_do_something));
   //TYP
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Abenteurertyp wählen",
                          "Typ",
                          &midgard_CG::wizard_do_something));
   //STADTLAND
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Stadt oder Land wählen (oder abgeleitete Werte wählen)",
                          "Stadt/Land",
                          &midgard_CG::wizard_do_something));
   //ABGELEITETEWERTE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Abgeleitete Werte wärfeln",
                          "abgeleitete Werte",
                          &midgard_CG::wizard_do_something));
   //LERNSCHEMA_SEITE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Auf die 'Lernschema'-Seite umblättern",
                          "Umblättern",
                          &midgard_CG::wizard_do_something));
   //HERKUNFT
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Herkunftsland wählen",
                          "Herkunftsland",
                          &midgard_CG::wizard_do_something));
   //UEBERLEBEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "In welchem Geländetyp wird 'überleben' als universelle Fertigkeit beherrscht?",
                          "Überleben",
                          &midgard_CG::wizard_do_something));
   //ANGEBORENEFERTIGKEITEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Angeborenen Fertigkeiten würfeln",
                          "angeb. Fertigk.",
                          &midgard_CG::wizard_do_something));
   //LERNPUNKTE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Lernpunkte würfeln",
                          "Lernpunkte",
                          &midgard_CG::wizard_do_something));
   //WAEHLEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Jetzt Fertigkeiten, Waffen und ev. Zauber in beliebiger"
                          " Reinfolge lernen (anklicken) bis alle Lernpunkte"
                          " verbraucht sind und anschließen den Beruf wählen.",
                          "Lernschema",
                          &midgard_CG::wizard_do_something));
   //BERUF1
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Fertigkeit auswählen, die aufgrund der Berufswahl"
                          " gelernt werden kann, danach das Geld auswürfeln.",
                          "Beruf1",
                          &midgard_CG::wizard_do_something));
   //BERUF
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Berufsfertigkeit aus Liste wählen",
                          "Beruf",
                          &midgard_CG::wizard_do_something));
   //GELD
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Geld auswürfeln",
                          "Geld",
                          &midgard_CG::wizard_do_something));
   //WAFFEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Waffen auswürfeln",
                          "Waffen",
                          &midgard_CG::wizard_do_something));
   //RUESTUNG
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Rüstung auswürfeln",
                          "R�üstung",
                          &midgard_CG::wizard_do_something));
   //AUSRUESTUNG
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Ausrüstung auswürfeln",
                          "Ausrüstung",
                          &midgard_CG::wizard_do_something));
   //SPEZIALWAFFE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Spezialwaffe wählen (anklicken)",
                          "Spezialwaffe",
                          &midgard_CG::wizard_do_something));
   //SPEZIAGEBIET
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Magier sollten ein Spezialgebiet wählen (das kann aber auch später geschehen)",
                          "Spezialgebiet",
                          &midgard_CG::wizard_do_something));
   //NAMEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Namen vergeben (Eingabe mit 'Enter' abschließen)",
                          "Namen",
                          &midgard_CG::wizard_do_something));
   //SPEICHERN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Speichern",
                          "Speichern",
                          &midgard_CG::wizard_do_something));
   //FERTIG
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Fertig",
                          "",
                          &midgard_CG::wizard_do_something));
}


