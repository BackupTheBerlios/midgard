// $Id: midgard_CG_optionen.cc,v 1.67 2002/03/16 16:55:44 thoma Exp $
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

void midgard_CG::Optionen_setzen_from_menu(OptionenIndex index)
{
  if(!fire_enabled) return;
  fire_enabled=false;
  for(list<st_Optionen>::iterator i=list_Optionen.begin();i!=list_Optionen.end();++i)
   {
     if(i->index!=index) continue;
     i->active = i->checkmenuitem->get_active();
     if(i->index==Original) { checkbutton_original(i->active); cerr << "NEUAUFBA\n";menu_init();}
     if(i->index==showPics) Pics(i->active);
     if(i->index==gw_wuerfeln) show_gw_wuerfeln(i->active);
   }
  fire_enabled=true;
}

void midgard_CG::OptionenM_setzen_from_menu(OptionenIndex index)
{
  if(index==LernschemaSensitive) lernschema_sensitive(true);
  if(index==WizardStarten) wizard_starten_clicked();
  if(index==LernschemaZusaetzeLoeschen) {list_FertigkeitZusaetze.clear(); 
                                         on_lernliste_wahl_toggled();}
  if(index==show_InfoWindow) InfoFenster->show();
}

void midgard_CG::Hausregeln_setzen_from_menu(HausIndex index)
{
  for(list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
   {
     if(i->index!=index) continue;
     i->active = i->menu->get_active();
   }
}

void midgard_CG::pdfViewer_setzen_from_menu(pdfViewerIndex index)
{
  for(list<st_pdfViewer>::iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   {
     if(i->index!=index) continue;
     i->active = i->radio_menu_item->get_active();
   }
}


void midgard_CG::checkbutton_original(bool active)
{
  if(active) 
    { togglebutton_alle_zauber->set_sensitive(false); 
      
      if(haus_menuitem)
       {
         setAllHausregeln(false);
         if(haus_menuitem) haus_menuitem->set_sensitive(false);
       }
      pixmap_logo->show();
//      pixmap_original_tux->hide();
    }      
  else 
    { togglebutton_alle_zauber->set_sensitive(true); 
      pixmap_logo->hide();
      pixmap_original_tux->show();
      if(haus_menuitem) haus_menuitem->set_sensitive(true);
    }      
}


void midgard_CG::lernschema_sensitive(bool active)
{
//   button_beschreibung->set_sensitive(true);
   frame_steigern->set_sensitive(true);
   frame_lernschema->set_sensitive(true);
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
    pixmap_dfr3->show();
    pixmap_kurai->show();
    table_gradsteigern_lang->show();
    button_steigern_kurz->hide();
  }
 else
  {
    pixmap_dfr4->hide();
    pixmap_dfr3->hide();
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

 on_radiobutton_mann_toggled(); // zum Neuaufbau des Typmenüs
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


/////////////////////
midgard_CG::st_Optionen midgard_CG::OptionenCheck(OptionenIndex oi)
{
 for(std::list<st_Optionen>::const_iterator i=list_Optionen.begin();i!=list_Optionen.end();++i)
   if(i->index==oi) return *i;
 assert(!"OptionenCheck: nicht gefunden");
 abort();
}
midgard_CG::st_Haus midgard_CG::HausregelCheck(HausIndex hi)
{
 for(std::list<st_Haus>::const_iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
   if(i->index==hi) return *i;
 assert(!"HausregelCheck: nicht gefunden");
 abort();
}
midgard_CG::st_pdfViewer midgard_CG::pdfViewerCheck(pdfViewerIndex pi)
{
 for(std::list<st_pdfViewer>::const_iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   if(i->index==pi) return *i;
 assert(!"pdfViewer: nicht gefunden");
 abort();
}


void midgard_CG::setOption(std::string os,bool b)
{
 for(std::list<st_Optionen>::iterator i=list_Optionen.begin();i!=list_Optionen.end();++i)
   if(i->text==os) { i->active=b; return; }
 throw NotFound();
}

void midgard_CG::setHausregeln(std::string hs,bool b)
{
  for(list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
      if(i->text==hs)  {i->active=b; return;}
 throw NotFound();
}

void midgard_CG::setAllHausregeln(bool b)
{
  for(list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
     i->active=b;
}

void midgard_CG::setpdfViewer(std::string is,bool b)
{
  for(list<st_pdfViewer>::iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   {
     if(i->text==is) i->active=b;
     else i->active=!b;
   }
}


////////////////

void midgard_CG::save_options()
{
  ofstream datei("midgard_optionen.xml");
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
 for(std::list<st_Optionen>::iterator i=list_Optionen.begin();i!=list_Optionen.end();++i)
   {
     datei << "  <Optionen";
     write_string_attrib(datei, "Name" ,i->text);
     write_bool_attrib_force(datei, "Wert", i->active);
     datei << "/>\n";
   }
  for(list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
   {
     datei << "  <Hausregel";
     write_string_attrib(datei, "Name" ,i->text);
     write_bool_attrib_force(datei, "Wert", i->active);
     datei << "/>\n";
   }
  for(list<st_pdfViewer>::iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   {
     if(!i->active) continue;
     datei << "  <pdfViewer";
     write_string_attrib(datei, "pdfViewer" ,i->text);
     write_bool_attrib(datei, "Wert", i->active);
     datei << "/>\n";
   }
 datei << "</MAGUS-optionen>\n";
}

void midgard_CG::load_options()
{ ifstream f("midgard_optionen.xml");
  if (!f.good()) cout << "Cannot open " << "midgard_optionen.xml" << '\n';
  TagStream ts(f);
  const Tag *data=ts.find("MAGUS-optionen");
  if(!data)    
    { cout << "Optionen konnten nicht geladen werden";
      ts.debug();
      return;
    }
  FOR_EACH_CONST_TAG_OF(i,*data,"Optionen")
     setOption(i->getAttr("Name"),i->getBoolAttr("Wert"));
  FOR_EACH_CONST_TAG_OF(i,*data,"Hausregel")
     setHausregeln(i->getAttr("Name"),i->getBoolAttr("Wert"));
  FOR_EACH_CONST_TAG_OF(i,*data,"pdfViewer")
     setpdfViewer(i->getAttr("Name"),i->getBoolAttr("Wert"));
}

