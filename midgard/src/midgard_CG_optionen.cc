// $Id: midgard_CG_optionen.cc,v 1.101 2002/08/19 06:31:14 thoma Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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
#include "WindowInfo.hh"
#include <fstream>
#include "TagStream.hh"
#include "export_common.h"
#include <xml.h>

void midgard_CG::set_info(const std::string& sadd)
{
 InfoFenster->AppendShow(sadd);
}

void midgard_CG::OptionenExecute_setzen_from_menu(Midgard_Optionen::OptionenExecuteIndex index)
{
 MOptionen->OptionenExecute_setzen_from_menu(index);
}

void midgard_CG::Ober_setzen_from_menu(Gtk::CheckMenuItem *mi,Midgard_Optionen::OberIndex index)
{
 MOptionen->Ober_setzen_from_menu(index,mi->get_active());
 menu_init();
}



void midgard_CG::checkbutton_original(bool active)
{
  if(active) 
    { table_steigern->togglebutton_alle_zauber->set_sensitive(false); 
      MOptionen->setAllHausregeln(false);
      show_Hausregeln_active(false);
      pixmap_logo->show();
    }      
  else 
    { table_steigern->togglebutton_alle_zauber->set_sensitive(true); 
      pixmap_logo->hide();
    }      
  menu_init();
}

void midgard_CG::lernschema_sensitive(bool active)
{
assert(active);
   table_lernschema->frame_lernpunkte->set_sensitive(true);
   frame_steigern->set_sensitive(true);
   frame_lernschema->set_sensitive(true);
   table_lernschema->button_herkunft->set_sensitive(true);
   table_lernschema->button_lernpunkte->set_sensitive(true);
   table_lernschema->togglebutton_lernpunkte_edit->set_sensitive(true);
   table_lernschema->button_lernschema_geld->set_sensitive(true);
   table_lernschema->button_lernschema_waffen->set_sensitive(true);
   table_lernschema->button_ruestung->set_sensitive(true);   
   table_lernschema->button_ausruestung->set_sensitive(true);   
   table_lernschema->button_angeborene_fert->show();
   table_lernschema->button_kido_auswahl->set_sensitive(true);
   table_lernschema->button_angeborene_fert->set_sensitive(true);
   table_lernschema->button_beruf->set_sensitive(true);
}


void midgard_CG::show_Pics(bool b)
{
 InfoFenster->show_pic(b);
 if(b)
  {
    table_grundwerte->pixmap_dfr4->show();
//    pixmap_dfr3->show();
    table_lernschema->scrolledwindow_dfr3->show(); 
    table_steigern->pixmap_kurai->show();
//    table_steigern->table_gradsteigern_lang->show();
//    table_steigern->button_steigern_kurz->hide();
  }
 else
  {
    table_grundwerte->pixmap_dfr4->hide();
//    pixmap_dfr3->hide();
    table_lernschema->scrolledwindow_dfr3->hide(); 
    table_steigern->pixmap_kurai->hide();
//    table_steigern->table_gradsteigern_lang->hide();
//    table_steigern->button_steigern_kurz->show();
  }
}

void midgard_CG::show_Menueleiste(bool b)
{
  if(b) handlebox_menu->show();
  else  handlebox_menu->hide();
}

void midgard_CG::show_Knopfleiste(bool b)
{
  if(b) griff_toolbar_top->show();
  else  griff_toolbar_top->hide();
}

void midgard_CG::show_Statusleiste(bool b)
{
  if(b) handlebox_status->show();
  else  handlebox_status->hide();
}

void midgard_CG::show_Icons(bool i)
{
 bool b=MOptionen->OberCheck(Midgard_Optionen::Beschriftungen).active;
 if     ( b && i) toolbar_top->set_style(GTK_TOOLBAR_BOTH);
 else if( b &&!i) toolbar_top->set_style(GTK_TOOLBAR_TEXT);
 else if(!b && i) toolbar_top->set_style(GTK_TOOLBAR_ICONS);
 else if(!b &&!i) toolbar_top->hide();
}

void midgard_CG::show_Beschriftungen(bool b)
{
 bool i=MOptionen->OberCheck(Midgard_Optionen::Icons).active;
 if     ( b && i) toolbar_top->set_style(GTK_TOOLBAR_BOTH);
 else if( b &&!i) toolbar_top->set_style(GTK_TOOLBAR_TEXT);
 else if(!b && i) toolbar_top->set_style(GTK_TOOLBAR_ICONS);
 else if(!b &&!i) toolbar_top->hide();
}

void midgard_CG::show_3_Tasten_Maus(bool b)
{
  if(b) 
   { table_grundwerte->vbox_gw_wuerfeln->hide();
     _tooltips.set_tip(*(table_grundwerte->button_grundwerte),"Linke Maustaste: 2x für jede Basiseigenschaft würfeln, höheres Ergebnis zählt.\n"
                  "Mittlere Maustaste: 2x würfeln, besseren Wert einer Basiseigenschaftzuweisen das ganze 6x wiederholen.\n"
                  "Rechte Maustaste: 9x würfeln und die besten sechs Ergebnisse frei verteilen.\n"
                  "ACHTUNG: Die Sonderregeln für Nichtmenschen werden nur bei der ersten Variante berücksichtigt.");
     _tooltips.set_tip(*button_main_drucken,"Linke Maustaste: LaTeX Abenteurerblatt drucken (pdf Datei).\n"
                  "Mittlere Maustaste: Charakterbeschreibung drucken.\n"
                  "Rechte Maustaste: Ausrüstung drucken.");
   }
  else 
   { table_grundwerte->vbox_gw_wuerfeln->show();
     _tooltips.set_tip(*(table_grundwerte->button_grundwerte),"Basiseigenschaft auswürfeln\n"
                  "ACHTUNG: Die Sonderregeln für Nichtmenschen werden nur bei der ersten Variante berücksichtigt.\n");
     _tooltips.set_tip(*button_main_drucken,"Linke Maustaste: LaTeX Abenteurerblatt drucken (pdf Datei).\n"
                  "Rechte Maustaste: Ausrüstung drucken.");
   }
}

void midgard_CG::show_NSC_active(bool b)
{
  if(b) eventbox_NSC_aktiv->show();
  else  eventbox_NSC_aktiv->hide();
}

void midgard_CG::show_Hausregeln_active(bool b)
{
  if(b) eventbox_haus_aktiv->show();
  else  eventbox_haus_aktiv->hide();
}

void midgard_CG::show_wizard_active(bool b)
{
  if(b) eventbox_wizard_aktiv->show();
  else  eventbox_wizard_aktiv->hide();
}


void midgard_CG::on_checkbutton_Regionen_menu(Gtk::CheckMenuItem *menu_item,cH_Region region)
{
 if(menu_item->get_active()) region->setActive(true);
 else region->setActive(false);

 table_grundwerte->fill_typauswahl();
 if(notebook_main->get_current_page_num()==PAGE_STEIGERN)
    table_steigern->load_for_page(table_steigern->notebook_lernen->get_current_page_num());

 for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
  {
   if(!(*i)->Offiziell() && (*i)->Active()) 
     { 
       pixmap_logo->hide();
       break;
     }
  }
 menu_init();
 set_region_statusbar(region->Pic(),region->Active());
}
