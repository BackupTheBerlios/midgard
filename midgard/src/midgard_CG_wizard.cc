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

#include "midgard_CG.hh"

void midgard_CG::wizard_do_nothing()
{
}

void midgard_CG::wizard_do_something()
{
  Wizard::esteps e=wizard.ActualStep();
cout << e<<'\n';
  switch (e) {
      case Wizard::GRUNDWERTE : grundwerte_wuerfeln(); break;
      case Wizard::ABGELEITETEWERTE : on_abge_werte_setzen_clicked(); break;
      case Wizard::HERKUNFT : on_herkunftsland_clicked(); break;
      case Wizard::ANGEBORENEFERTIGKEITEN : on_angeborene_fertigkeit_clicked(); break;
      case Wizard::LERNPUNKTE : on_lernpunkte_wuerfeln_clicked(); break;
      default: cout << "nicht automaitisch\n";break;
   }
}


void midgard_CG::on_button_wizard_wiederholen_clicked()
{
  wizard.same_step();  
}

void midgard_CG::on_button_wizard_weiter_clicked()
{
  wizard.next_step();  
}

void midgard_CG::wizard_starten_clicked()
{
 table_wizard->show();
 wizard.restart();
}

