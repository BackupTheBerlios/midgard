// generated 2002/2/14 8:49:01 CET by thoma@Tiger.
// using glademm V0.6.2c_cvs
//
// newer (non customized) versions of this file go to Wizard_window.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "Wizard_window.hh"


#include "midgard_CG.hh"

Wizard_window::esteps &operator++(Wizard_window::esteps &a)
{  
   a= Wizard_window::esteps(int(a)+1);
   if(a==Wizard_window::MAXSTEPS) a=Wizard_window::esteps(int(Wizard_window::MAXSTEPS)-1);
   return a;
}

Wizard_window::Wizard_window(midgard_CG* h)
: hauptfenster(h), actual_step(START)
{
  fill_vecwiz();
}


void Wizard_window::next_step()
{
  evaluate_step(++actual_step);
}
void Wizard_window::same_step()
{
  evaluate_step(actual_step);
}
void Wizard_window::restart()
{
 actual_step=START;
 evaluate_step(actual_step);
}


void Wizard_window::evaluate_step(esteps step)
{
  assert(vecwiz.size()>(size_t)(step));
  vector<cH_Typen> Typ=hauptfenster->getVTyp();
  if(step==SPEZIALWAFFE&&(!Typ[0]->Spezialwaffe()&&!Typ[1]->Spezialwaffe()))
    next_step();
  if(step==SPEZIALGEBIET&&(!Typ[0]->Spezialgebiet()&&!Typ[1]->Spezialgebiet()))
    next_step();
  hauptfenster->notebook_main->set_page(vecwiz[step].page);
  hauptfenster->set_status(vecwiz[step].text);

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


void Wizard_window::fill_vecwiz()
{
   //START
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Dieser Wizard hilft einen neuen Abenteurer zu erzeugen.\n"
                          "'Weiter' führt jeweils den nächsten Schritt aus.",
                          "Neuanfang",
                          &midgard_CG::wizard_do_nothing));
   //SPEZIES
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Spezies auswählen (oder mit 'Weiter' 'Mensch' wählen.)",
                          "Spezies",
                          &midgard_CG::wizard_do_something));
   //GRUNDWERTE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Eigenschaften würfeln",
                          "Grundeigenschaften",
                          &midgard_CG::wizard_do_something));
   //GESCHLECHT
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Geschlecht wählen (oder mit 'Weiter' 'männlich' wählen.)",
                          "Geschlecht",
                          &midgard_CG::wizard_do_something));
   //TYP
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Abenteurertyp wählen (oder angezeigten Typ übernehmen.)",
                          "Typ",
                          &midgard_CG::wizard_do_something));
   //STADTLAND
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Stadt oder Land wählen (oder mit 'Weiter' 'Stadt' wählen.)",
                          "Stadt/Land",
                          &midgard_CG::wizard_do_something));
   //ABGELEITETEWERTE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Abgeleitete Werte würfeln",
                          "abgeleitete Werte",
                          &midgard_CG::wizard_do_something));
   //HERKUNFT
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Herkunftsland wählen",
                          "Herkunftsland",
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
                          "Jetzt Fertigkeiten, Waffen und ev. Zauber in beliebiger\n"
                          " Reinfolge lernen (anklicken) bis alle Lernpunkte \n"
                          " verbraucht sind und anschließen 'Weiter' drücken.",
                          "Lernschema",
                          &midgard_CG::wizard_do_something));
   //BERUF
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Fertigkeit auswählen, die aufgrund der Berufswahl\n"
                          " gelernt werden kann (anschließend 'Weiter' drücken.",
                          "Beruf",
                          &midgard_CG::wizard_do_something));
   //SPEZIALWAFFE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Spezialwaffe wählen (anklicken)",
                          "Spezialwaffe",
                          &midgard_CG::wizard_do_something));
   //SPEZIAGEBIET
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Magier sollten eine Spezialgebiet wählen",
                          "Spezialgebiet",
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
                          "Rüstung",
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


void Wizard_window::on_button_wizard_weiter_clicked()
{   
  next_step();
}

void Wizard_window::on_button_wizard_skip_clicked()
{   
}

void Wizard_window::on_button_wizard_wiederholen_clicked()
{   
  same_step();
}

void Wizard_window::on_button_close_wizard_clicked()
{   
  hauptfenster->on_button_close_wizard_clicked();
  destroy();
}

gint Wizard_window::on_Wizard_window_delete_event(GdkEventAny* event)
{
 hauptfenster->on_button_close_wizard_clicked();
 return 0;
}

void Wizard_window::on_togglebutton_wizard_start_toggled()
{
 bool b;
 if(togglebutton_wizard_start->get_active()) b=true;
 else b=false;
 
 hauptfenster->MOptionen->setOptionCheck("Wizard bei jedem Programmstart zeigen",b);
}
