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
}


void Wizard::next_step(esteps e)
{
  actual_step=++e;
  evaluate_step(actual_step);
}

/*
void Wizard::next_step()
{
  evaluate_step(++actual_step);
}
*/
/*
void Wizard::same_step()
{
  evaluate_step(actual_step);
}
*/

void Wizard::restart()
{
 actual_step=START;
 evaluate_step(++actual_step);
}


void Wizard::evaluate_step(esteps step)
{
  assert(vecwiz.size()>(size_t)(step));
  vector<cH_Typen> Typ=hauptfenster->getVTyp();
//cout << step<<' '<<SPEZIALWAFFE<<' '<<SPEZIALGEBIET<<'\n';
  if(step==SPEZIALWAFFE&&(!Typ[0]->Spezialwaffe()&&!Typ[1]->Spezialwaffe()))
{
cout << "Automatisch weiter \n";
    next_step(SPEZIALGEBIET);
}
  if(step==SPEZIALGEBIET&&(!Typ[0]->Spezialgebiet()&&!Typ[1]->Spezialgebiet()))
    next_step(SPEICHERN);
//cout << "AA "<<vecwiz[step].page<<'\n';
  hauptfenster->notebook_main->set_page(vecwiz[step].page);
//cout << "BB "<<vecwiz[step].page<<'\n';
  hauptfenster->set_wizard(vecwiz[step].text);
  hauptfenster->wizard_do_something();

/*
  Gtk::OStream os(LogWinWizard->get_list());
  os << vecwiz[step].text<<'\n';
  os.flush();
  LogWinWizard->scroll();
  (hauptfenster->*(vecwiz[step].callback))();
  static_cast<Gtk::Label*>(button_wiz_weiter->get_child())->set_text("Weiter:\n"+vecwiz[step+1].kurz);
  static_cast<Gtk::Label*>(button_wiz_wiederholen->get_child())->set_text("Wiederholen:\n"+vecwiz[step].kurz);
*/
  // button_wiz_skip
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
                          "Spezies ausw�hlen (oder Eigenschaften w�rfeln)",
                          "Spezies",
                          &midgard_CG::wizard_do_something));
   //GRUNDWERTE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Eigenschaften w�rfeln",
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
   //HERKUNFT
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Herkunftsland w�hlen",
                          "Herkunftsland",
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
   //SPEZIALWAFFE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Spezialwaffe w�hlen (anklicken)",
                          "Spezialwaffe",
                          &midgard_CG::wizard_do_something));
   //SPEZIAGEBIET
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Magier sollten eine Spezialgebiet w�hlen",
                          "Spezialgebiet",
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


