/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, U
 */

#include "Wizard.hh"
#include "midgard_CG.hh"

Wizard::esteps operator++(Wizard::esteps a)
{  
   a= Wizard::esteps(int(a)+1);
   return a;
}

Wizard::Wizard(midgard_CG* h)
: hauptfenster(h), actual_step(SPEZIES)
{
  fill_vecwiz();
}

void Wizard::next_step()
{
  evaluate_step(++actual_step);
}
void Wizard::same_step()
{
  evaluate_step(actual_step);
}
void Wizard::restart()
{
 actual_step=SPEZIES;
 evaluate_step(actual_step);
}


void Wizard::evaluate_step(esteps step)
{
  assert(vecwiz.size()>(size_t)(step));
  
  hauptfenster->notebook_main->set_page(vecwiz[step].page);
  Gtk::OStream os(hauptfenster->LogWinWizard->get_list());
  os << vecwiz[step].text<<'\n';
  os.flush();
  hauptfenster->LogWinWizard->scroll();
  (hauptfenster->*(vecwiz[step].callback))();
}


void Wizard::fill_vecwiz()
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
}
