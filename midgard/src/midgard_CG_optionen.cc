// $Id: midgard_CG_optionen.cc,v 1.53 2002/02/15 12:13:58 thoma Exp $
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

void midgard_CG::on_checkbutton_optionen_menu(st_Optionen O)
{
  if (O.checkmenuitem->get_active()) O.active=true;
  else O.active=false;
  
  if(O.index==Original) checkbutton_original(O.active);
  if(O.index==showPics) Pics(O.active);
}
void midgard_CG::on_optionen_menu(st_OptionenM O)
{
  if(O.index==LernschemaSensitive) lernschema_sensitive(true);
  if(O.index==WizardStarten) wizard_starten_clicked();
}



void midgard_CG::checkbutton_original(bool active)
{
  if(active) 
    { togglebutton_alle_zauber->set_sensitive(false); 
      
      if(haus_menuitem)
       {
         Hausregeln_setzen(false);
         if(haus_menuitem) haus_menuitem->set_sensitive(false);
       }
      pixmap_logo->show();
    }      
  else 
    { togglebutton_alle_zauber->set_sensitive(true); 
      pixmap_logo->hide();
      if(haus_menuitem) haus_menuitem->set_sensitive(true);
    }      
}


void midgard_CG::lernschema_sensitive(bool active)
{
   button_beschreibung->set_sensitive(true);
   frame_steigern->set_sensitive(true);
   frame_lernschema->set_sensitive(true);
   button_lernpunkte->set_sensitive(true);
   togglebutton_lernpunkte_edit->set_sensitive(true);
   button_geld_waffen->set_sensitive(true);
   button_ruestung->set_sensitive(true);   
   button_angeborene_fert->show();
   

//   hbox_beruf->set_sensitive(true);
//   table_beruf->set_sensitive(true);
//   hbox_fertigkeit->set_sensitive(true);
//   table_fertigkeit->set_sensitive(true);
//   hbox_waffen->set_sensitive(true);
//   table_waffen->set_sensitive(true);
//   hbox_zauber->set_sensitive(true); 
//   table_magier_lernen->set_sensitive(true);     
//   hbox_kido->set_sensitive(true);
//   table_kido_lernen->set_sensitive(true);

//   button_fertigkeiten->set_sensitive(true);
   button_kido_auswahl->set_sensitive(true);
//   table_lernschema_buttons->set_sensitive(true);
}


void midgard_CG::Pics(bool b)
{
 if(b)
  {
    pixmap_dfr4->show();
    pixmap_dfr3->show();
    pixmap_Wald->show();
    pixmap_kurai->show();
    table_gradsteigern_lang->show();
    button_steigern_kurz->hide();
  }
 else
  {
    pixmap_dfr4->hide();
    pixmap_dfr3->hide();
    pixmap_Wald->hide();
    pixmap_kurai->hide();
    table_gradsteigern_lang->hide();
    button_steigern_kurz->show();
  }
}

      

void midgard_CG::on_checkbutton_Regionen_menu(Gtk::CheckMenuItem *menu_item,cH_Region region)
{
 if(menu_item->get_active()) region->setActive(true);
 else region->setActive(false);

 on_radiobutton_mann_toggled(); // zum Neuaufbau des Typmenüs
 if(notebook_main->get_current_page_num()==PAGE_STEIGERN)
    load_for_page(notebook_lernen->get_current_page_num());

 pixmap_logo->show();
 for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
  {
   if(!(*i)->Offiziell() && (*i)->Active()) 
     { pixmap_logo->hide();
       break;
     }
  }
}

midgard_CG::st_Optionen midgard_CG::OptionenCheck(OptionenIndex oi)
{
 for(std::list<st_Optionen>::const_iterator i=list_Optionen.begin();i!=list_Optionen.end();++i)
   if(i->index==oi) return *i;
 assert(!"OptionenCheck: nicht gefunden");
 abort();
}
midgard_CG::st_Optionen midgard_CG::OptionenCheck(std::string os)
{
 for(std::list<st_Optionen>::const_iterator i=list_Optionen.begin();i!=list_Optionen.end();++i)
   if(i->text==os) return *i;
 throw NotFound();
}

void midgard_CG::setOption(OptionenIndex oi,bool b)
{
 for(std::list<st_Optionen>::iterator i=list_Optionen.begin();i!=list_Optionen.end();++i)
   if(i->index==oi)  i->active=b;
}


midgard_CG::st_Haus midgard_CG::HausregelCheck(HausIndex hi)
{
 for(std::list<st_Haus>::const_iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
   if(i->index==hi) return *i;
 assert(!"HausregelCheck: nicht gefunden");
 abort();
}


void midgard_CG::Hausregeln_setzen_from_menu()
{
  for(list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
     i->active = i->menu->get_active();
}

void midgard_CG::Hausregeln_setzen(bool b)
{
  for(list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
   {
     i->active = b;
     i->menu->set_active(b);
   }
}

void midgard_CG::regnot(const std::string& sadd)
{
//  manage(new WindowInfo(sadd));
 InfoFenster->AppendShow(sadd);
}


void midgard_CG::save_options()
{
  ofstream datei("./midgard_optionen.xml");
  if (!datei.good())
   { 
    InfoFenster->AppendShow("Ich kann die Optionen nicht speichern");
    return;
   }
 datei << "<?xml";
 write_string_attrib(datei, "version", "1.0");
 write_string_attrib(datei, "encoding", TagStream::host_encoding);
 datei << "?>\n\n";
 datei << "<MAGUS-optionen>\n";
 datei << "  <Optionen";
 for(std::list<st_Optionen>::iterator i=list_Optionen.begin();i!=list_Optionen.end();++i)
   {
     write_string_attrib(datei, "Name" ,i->text);
     write_bool_attrib(datei, "Wert", i->active);
   }
 datei << "/>\n";
 datei << "</MAGUS-optionen>\n";
}

void midgard_CG::load_options()
{
  TagStream ts("./midgard_optionen.xml");
  const Tag *data=ts.find("MAGUS-optionen");
  if(!data)    
    { InfoFenster->AppendShow("Optionen konnten nicht geladen werden");
      return;
    }
 data=ts.find("Optionen");                          
 for(std::list<st_Optionen>::iterator i=list_Optionen.begin();i!=list_Optionen.end();++i)
   {
     i->active=data->getBoolAttr(i->text,false);     
   }
}

