/*  Copyright (C) 2001 Malte Thoma
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
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "midgard_CG.hh"
#include <Misc/Trace.h>


void midgard_CG::on_neuer_charakter()
{
   ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
   on_neuer_charakter_clicked();
   on_wizard_starten_activate();
}

void midgard_CG::on_neuer_charakter_clicked()
{
   ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
   on_wizard_beenden_activate();
   Programmoptionen.WerteEingebenModel()=true;
   Char.push_back(); // ??? vielleicht nicht immer eine gute Idee?
   if(Char.empty()) Char.push_back();
#if 0   
   table_lernschema->label_lernschma_titel->set_text("");
   frame_steigern->set_sensitive(false); // das wirkt nicht ?
   frame_lernschema->set_sensitive(false);
   table_lernschema->togglebutton_lernpunkte_edit->set_active(false);

   table_lernschema->button_lernpunkte->set_sensitive(false);
   table_lernschema->togglebutton_lernpunkte_edit->set_sensitive(false);
   label_wizard->hide();

   table_lernschema->edit_lernpunkte(false);
   table_lernschema->frame_lernschema_zusatz->hide();

   table_lernschema->button_sensitive(false);
   table_lernschema->togglebutton_spezialwaffe->hide();
      
   table_lernschema->lernpunkte.clear();
   table_lernschema->list_FertigkeitZusaetze.clear();
   for(std::vector<cH_Region>::const_iterator i=Datenbank.Regionen.begin();i!=Datenbank.Regionen.end();++i)
     {
      (*i)->setActive(false);
      set_region_statusbar((*i)->Pic(),false);
     }
  table_steigern->neuer_charakter();
  notebook_main->set_current_page(PAGE_GRUNDWERTE);
  table_grundwerte->neuer_charakter();
#endif  
}
