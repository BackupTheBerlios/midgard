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
  Gtk::OStream os(LogWinWizard->get_list());
  os << vecwiz[step].text<<'\n';
  os.flush();
  LogWinWizard->scroll();
  (hauptfenster->*(vecwiz[step].callback))();
}


void Wizard_window::fill_vecwiz()
{
   //START
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Dieser Wizard hilft einen neuen Abenteurer zu erzeugen.\n"
                          "'Weiter' f�hrt jeweils den n�chsten Schritt aus.",
                          &midgard_CG::wizard_do_nothing));
   //SPEZIES
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Spezies ausw�hlen (oder mit 'Weiter' 'Mensch' w�hlen.)",
                          &midgard_CG::wizard_do_something));
   //GRUNDWERTE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Eigenschaften w�rfeln",
                          &midgard_CG::wizard_do_something));
   //GESCHLECHT
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Geschlecht w�hlen (oder mit 'Weiter' 'm�nnlich' w�hlen.)",
                          &midgard_CG::wizard_do_something));
   //TYP
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Abenteurertyp w�hlen (oder mit 'Weiter' 'Assassine' w�hlen.)",
                          &midgard_CG::wizard_do_something));
   //STADTLAND
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Stadt oder Land w�hlen (oder mit 'Weiter' 'Stadt' w�hlen.)",
                          &midgard_CG::wizard_do_something));
   //ABGELEITETEWERTE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Abgeleitete Werte w�rfeln",
                          &midgard_CG::wizard_do_something));
   //HERKUNFT
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Herkunftsland w�hlen",
                          &midgard_CG::wizard_do_something));
   //ANGEBORENEFERTIGKEITEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Angeborenen Fertigkeiten w�rfeln",
                          &midgard_CG::wizard_do_something));
   //LERNPUNKTE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Lernpunkte w�rfeln",
                          &midgard_CG::wizard_do_something));
   //WAEHLEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Jetzt Fertigkeiten, Waffen und ev. Zauber in beliebiger\n"
                          " Reinfolge lernen (anklicken) bis alle Lernpunkte \n"
                          " verbraucht sind und anschlie�en 'Weiter' dr�cken.",
                          &midgard_CG::wizard_do_something));
   //BERUF
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Fertigkeit ausw�hlen, die aufgrund der Berufswahl\n"
                          " gelernt werden kann (anschlie�end 'Weiter' dr�cken.",
                          &midgard_CG::wizard_do_something));
   //SPEZIALWAFFE
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Spezialwaffe w�hlen (anklicken)",
                          &midgard_CG::wizard_do_something));
   //SPEZIAGEBIET
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Magier sollten eine Spezialgebiet w�hlen",
                          &midgard_CG::wizard_do_something));
   //GELD
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Geld ausw�rfeln",
                          &midgard_CG::wizard_do_something));
   //WAFFEN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Waffen ausw�rfeln",
                          &midgard_CG::wizard_do_something));
   //RUESTUNG
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "R�stung ausw�rfeln",
                          &midgard_CG::wizard_do_something));
   //SPEICHERN
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Speichern",
                          &midgard_CG::wizard_do_something));
   //FERTIG
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Fertig",
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
 
 hauptfenster->setOption("Wizard bei jedem Programmstart zeigen",b);
}
