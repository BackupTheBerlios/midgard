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
#include <cstring>

void midgard_CG::set_wizard(std::string s)
{
  label_wizard->show();
  label_wizard->set_text(s);
}



void midgard_CG::wizard_do_something()
{
  if(!wizard) return;
  Wizard::esteps e=wizard->ActualStep();

  if(e==Wizard::FERTIG)
      { on_wizard_beenden_activate();}

  if(e==Wizard::HERKUNFT)
      { table_lernschema->on_herkunftsland_clicked();}

  if(e==Wizard::SPEZIALWAFFE)
      {  table_lernschema->togglebutton_spezialwaffe->set_active(true);}

  if(e==Wizard::NAMEN)
      { table_grundwerte->togglebutton_edit_werte->set_active(true);
//        table_grundwerte->entry_nameC->grab_focus();
      }

  if(e==Wizard::SPEICHERN) xml_export_auswahl();

}

void midgard_CG::on_neuer_abenteurer_mit_wizard_activate()
{
  on_neuer_charakter_clicked();
  on_wizard_starten_activate();
}

void midgard_CG::on_wizard_starten_activate()
{
 on_neuer_charakter_clicked();
 wizard = new Wizard(this);
 wizard->restart();
}

void midgard_CG::on_wizard_beenden_activate()
{
 if(wizard) delete(wizard);
 label_wizard->hide();
 wizard=0;
}

