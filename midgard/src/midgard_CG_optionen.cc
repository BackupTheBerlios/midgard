// $Id: midgard_CG_optionen.cc,v 1.75 2002/04/19 07:51:27 thoma Exp $
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

void midgard_CG::regnot(const std::string& sadd)
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
}



void midgard_CG::checkbutton_original(bool active)
{
  if(active) 
    { togglebutton_alle_zauber->set_sensitive(false); 
      MOptionen->setAllHausregeln(false);
      pixmap_logo->show();
    }      
  else 
    { togglebutton_alle_zauber->set_sensitive(true); 
      pixmap_logo->hide();
    }      
  menu_init();
}


void midgard_CG::lernschema_sensitive(bool active)
{
//   button_beschreibung->set_sensitive(true);
   frame_steigern->set_sensitive(true);
   frame_lernschema->set_sensitive(true);
   button_herkunft->set_sensitive(true);
   button_lernpunkte->set_sensitive(true);
   togglebutton_lernpunkte_edit->set_sensitive(true);
   button_lernschema_geld->set_sensitive(true);
   button_lernschema_waffen->set_sensitive(true);
   button_ruestung->set_sensitive(true);   
   button_angeborene_fert->show();
   button_kido_auswahl->set_sensitive(true);
   button_angeborene_fert->set_sensitive(true);
   table_berufswahl->set_sensitive(true);
}


void midgard_CG::Pics(bool b)
{
 if(b)
  {
    pixmap_dfr4->show();
//    pixmap_dfr3->show();
    scrolledwindow_dfr3->show(); 
    pixmap_kurai->show();
    table_gradsteigern_lang->show();
    button_steigern_kurz->hide();
  }
 else
  {
    pixmap_dfr4->hide();
//    pixmap_dfr3->hide();
    scrolledwindow_dfr3->hide(); 
    pixmap_kurai->hide();
    table_gradsteigern_lang->hide();
    button_steigern_kurz->show();
  }
}

void midgard_CG::show_gw_wuerfeln(bool b)
{
  if(b) vbox_gw_wuerfeln->hide();
  else vbox_gw_wuerfeln->show();
}

void midgard_CG::on_checkbutton_Regionen_menu(Gtk::CheckMenuItem *menu_item,cH_Region region)
{
 if(menu_item->get_active()) region->setActive(true);
 else region->setActive(false);

 on_radiobutton_mann_toggled(); // zum Neuaufbau des Typmen�s
 if(notebook_main->get_current_page_num()==PAGE_STEIGERN)
    load_for_page(notebook_lernen->get_current_page_num());

// pixmap_logo->show();
 for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
  {
   if(!(*i)->Offiziell() && (*i)->Active()) 
     { 
//       checkbutton_original(false);
       pixmap_logo->hide();
       break;
     }
  }
}
