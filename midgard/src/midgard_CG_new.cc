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


void midgard_CG::clear_listen()
{
//   Char.reset();
//   table_lernschema->list_FertigkeitZusaetze.clear();
//   list_Fertigkeit_neu.clear();
//   list_Waffen_neu.clear();
//   list_WaffenGrund_neu.clear();
//   list_Kido_neu.clear();
//   list_Sprache_neu.clear();
//   list_Schrift_neu.clear();
//   list_Zauber_neu.clear();
//   list_Zauberwerk_neu.clear();
}

void midgard_CG::clear_gtk()
{
//   table_lernschema->tree_gelerntes->clear();
/*
   alte_fert_tree->clear();
   neue_fert_tree->clear();
   alte_waffen_tree->clear();
   neue_waffen_tree->clear();
   alte_grund_tree->clear();
   neue_grund_tree->clear();
   alte_zauber_tree->clear();
   neue_zauber_tree->clear();
   alte_zaubermittel_tree->clear();
   neue_zaubermittel_tree->clear();
   alte_kido_tree->clear();
   neue_kido_tree->clear();
   alte_sprache_tree->clear();
   neue_sprache_tree->clear();
   alte_schrift_tree->clear();
   neue_schrift_tree->clear();
*/
}

gint midgard_CG::on_neuer_charakter_release_event(GdkEventButton *ev)
{
   on_neuer_charakter_clicked();
   if (ev->button==1)  on_wizard_starten_activate();
   return false;
}

void midgard_CG::on_neuer_charakter_clicked()
{
   if(modify_bool)
     {
       MOptionen->save_options(InfoFenster);
       xml_export_auswahl();
     }               
   filename="";
//   table_grundwerte->neuer_charakter();

   table_lernschema->label_lernschma_titel->set_text("");
   frame_steigern->set_sensitive(false); // das wirkt nicht ?
   frame_lernschema->set_sensitive(false);
   table_lernschema->togglebutton_lernpunkte_edit->set_active(false);
   table_lernschema->button_beruf->set_sensitive(false);

   table_lernschema->button_lernpunkte->set_sensitive(false);
   table_lernschema->togglebutton_lernpunkte_edit->set_sensitive(false);
   table_lernschema->button_lernschema_geld->set_sensitive(false);
   table_lernschema->button_lernschema_waffen->set_sensitive(false);
   table_lernschema->button_ruestung->set_sensitive(false);
   label_wizard->hide();

   table_lernschema->edit_lernpunkte(false);
   table_lernschema->frame_lernschema_zusatz->hide();

   table_lernschema->button_fachkenntnisse->set_sensitive(false);
   table_lernschema->button_allgemeinwissen->set_sensitive(false);
   table_lernschema->button_untyp_fertigkeiten->set_sensitive(false);
   table_lernschema->button_waffen->set_sensitive(false);
   table_lernschema->button_zauber->set_sensitive(false);
   table_lernschema->togglebutton_spezialwaffe->set_active(false);
   table_lernschema->togglebutton_spezialwaffe->hide();
      
//   scrolledwindow_landauswahl->hide();
//   spinbutton_pp_eingeben->hide();
//   vbox_praxispunkte->hide();
/*
   table_gruppe->hide();
   table_artikel->hide();
   togglebutton_gruppe_neu->hide(); // nicht implementiert
*/
//   togglebutton_praxispunkte->set_active(false);

/*
   table_lernschema->vbox_berufsname->hide();
   table_lernschema->button_kido_auswahl->set_sensitive(false);       
   table_lernschema->button_angeborene_fert->set_sensitive(false);
*/

   table_lernschema->lernpunkte.clear();
   for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
      (*i)->setActive(false);

   Char.getWerte().set_Grad_Basiswerte(1);
   table_steigern->neuer_charakter();
//   label_EP->set_text("50%");
//   label_Gold->set_text("50%");

  menu_init();
  notebook_main->set_page(PAGE_GRUNDWERTE);
  table_grundwerte->neuer_charakter();
}
