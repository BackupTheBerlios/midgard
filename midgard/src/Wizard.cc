// generated 2002/2/14 8:49:01 CET by thoma@Tiger.
// using glademm V0.6.2c_cvs
//
// newer (non customized) versions of this file go to Wizard.cc_new

// This file is for your program, I won't touch it again!

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
  hauptfenster->notebook_main->set_page(vecwiz[step].page);
  hauptfenster->set_wizard(vecwiz[step].text);
  hauptfenster->wizard_do_something();

}


void Wizard::fill_vecwiz()
{
   //START
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Dieser Wizard hilft einen neuen Abenteurer zu erzeugen.\n"
                          "'Weiter' f�hrt jeweils den n�chsten Schritt aus.",
                          "Neuanfang",
                          &midgard_CG::wizard_do_something));
   //SPEZIES
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Spezies ausw�hlen (oder Eigenschaften auf eine der drei Arten w�rfeln)",
                          "Spezies",
                          &midgard_CG::wizard_do_something));
   //GRUNDWERTE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Eigenschaften auf eine der drei Arten w�rfeln (ACHTUNG: F�r Nichtmenschen ist nur die Standardmethode implementiert)",
                          "Eigenschaften",
                          &midgard_CG::wizard_do_something));
   //GESCHLECHT
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Geschlecht w�hlen (oder Abenteuertyp ausw�hlen).)",
                          "Geschlecht",
                          &midgard_CG::wizard_do_something));
   //TYP
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Abenteurertyp w�hlen",
                          "Typ",
                          &midgard_CG::wizard_do_something));
   //STADTLAND
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Stadt oder Land w�hlen (oder abgeleitete Werte w�hlen)",
                          "Stadt/Land",
                          &midgard_CG::wizard_do_something));
   //ABGELEITETEWERTE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Abgeleitete Werte w�rfeln",
                          "abgeleitete Werte",
                          &midgard_CG::wizard_do_something));
   //LERNSCHEMA_SEITE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Auf die 'Lernschema'-Seite umbl�ttern",
                          "Umbl�ttern",
                          &midgard_CG::wizard_do_something));
   //HERKUNFT
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Herkunftsland w�hlen",
                          "Herkunftsland",
                          &midgard_CG::wizard_do_something));
   //UEBERLEBEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "In welchem Gel�ndetyp wird '�berleben' als universelle Fertigkeit beherrscht?",
                          "�berleben",
                          &midgard_CG::wizard_do_something));
   //ANGEBORENEFERTIGKEITEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Angeborenen Fertigkeiten w�rfeln",
                          "angeb. Fertigk.",
                          &midgard_CG::wizard_do_something));
   //LERNPUNKTE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Lernpunkte w�rfeln",
                          "Lernpunkte",
                          &midgard_CG::wizard_do_something));
   //WAEHLEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Jetzt Fertigkeiten, Waffen und ev. Zauber in beliebiger"
                          " Reinfolge lernen (anklicken) bis alle Lernpunkte"
                          " verbraucht sind und anschlie�en den Beruf w�hlen.",
                          "Lernschema",
                          &midgard_CG::wizard_do_something));
   //BERUF1
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Fertigkeit ausw�hlen, die aufgrund der Berufswahl"
                          " gelernt werden kann, danach das Geld ausw�rfeln.",
                          "Beruf1",
                          &midgard_CG::wizard_do_something));
   //BERUF
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Berufsfertigkeit aus Liste w�hlen",
                          "Beruf",
                          &midgard_CG::wizard_do_something));
   //GELD
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Geld ausw�rfeln",
                          "Geld",
                          &midgard_CG::wizard_do_something));
   //WAFFEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Waffen ausw�rfeln",
                          "Waffen",
                          &midgard_CG::wizard_do_something));
   //RUESTUNG
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "R�stung ausw�rfeln",
                          "R�stung",
                          &midgard_CG::wizard_do_something));
   //AUSRUESTUNG
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Ausr�stung ausw�rfeln",
                          "Ausr�stung",
                          &midgard_CG::wizard_do_something));
   //SPEZIALWAFFE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Spezialwaffe w�hlen (anklicken)",
                          "Spezialwaffe",
                          &midgard_CG::wizard_do_something));
   //SPEZIAGEBIET
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Magier sollten ein Spezialgebiet w�hlen (das kann aber auch sp�ter geschehen)",
                          "Spezialgebiet",
                          &midgard_CG::wizard_do_something));
   //NAMEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Namen vergeben (Eingabe mit 'Enter' abschlie�en)",
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


