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
: hauptfenster(h), actual_step(SPEZIES)
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
 actual_step=SPEZIES;
 evaluate_step(actual_step);
}


void Wizard_window::evaluate_step(esteps step)
{
  assert(vecwiz.size()>(size_t)(step));
  
  hauptfenster->notebook_main->set_page(vecwiz[step].page);
  Gtk::OStream os(LogWinWizard->get_list());
  os << vecwiz[step].text<<'\n';
  os.flush();
  LogWinWizard->scroll();
  (hauptfenster->*(vecwiz[step].callback))();
}


void Wizard_window::fill_vecwiz()
{
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Spezies auswählen",
                          &midgard_CG::wizard_do_something));
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Grundwerte würfeln",
                          &midgard_CG::wizard_do_something));
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Geschlecht wählen",
                          &midgard_CG::wizard_do_something));
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Abenteurertyp wählen",
                          &midgard_CG::wizard_do_something));
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Stadt oder Land wählen",
                          &midgard_CG::wizard_do_something));
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_GRUNDWERTE,
                          "Abgeleitete Werte würfeln",
                          &midgard_CG::wizard_do_something));
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Herkunftsland wählen",
                          &midgard_CG::wizard_do_something));
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Für die angeborenen Fertigkeiten würfeln",
                          &midgard_CG::wizard_do_something));
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Lernpunkte würfeln",
                          &midgard_CG::wizard_do_something));
   vecwiz.push_back(st_wiz(midgard_CG::PAGE_LERNEN,
                          "Fertig",
                          &midgard_CG::wizard_do_nothing));
}


void Wizard_window::on_button_wizard_weiter_clicked()
{   
  next_step();
//  hauptfenster->on_button_wizard_weiter_clicked();
}

void Wizard_window::on_button_wizard_wiederholen_clicked()
{   
  same_step();
// hauptfenster->on_button_wizard_wiederholen_clicked();
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


