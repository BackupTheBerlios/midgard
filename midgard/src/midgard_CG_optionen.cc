// $Id: midgard_CG_optionen.cc,v 1.125 2003/09/08 14:36:40 christof Exp $
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
#include <Misc/TagStream.h>
#include <xml.h>
#include <Misc/Trace.h>

#if 0
void midgard_CG::OptionenExecute_setzen_from_menu(Magus_Optionen::OptionenExecuteIndex index)
{
 ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
 MOptionen->OptionenExecute_setzen_from_menu(index);
}


void midgard_CG::Ober_element_activate(gpointer gp,Magus_Optionen::OberIndex index)
{
 ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
  getOptionen()->Ober_setzen_from_menu(index);
}

void midgard_CG::checkbutton_original(bool active)
{
 ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
  if(active) 
    { table_steigern->togglebutton_alle_zauber->set_sensitive(false); 
      MOptionen->setAllHausregeln(false);
      show_Hausregeln_active();
      eventbox_Original_Midgard->show();
    }      
  else 
    { table_steigern->togglebutton_alle_zauber->set_sensitive(true); 
      eventbox_Original_Midgard->hide();
    }      
//  menu_init();
}
#endif

void midgard_CG::lernschema_sensitive(bool active)
{
 ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
assert(active);
#warning hier fehlts
#if 0
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
#endif   
}

#if 0
void midgard_CG::show_Menueleiste(bool b)
{
 ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
  if(b) handlebox_menu->show();
  else  handlebox_menu->hide();
}

void midgard_CG::show_Knopfleiste(bool b)
{
 ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
  if(b) griff_toolbar_top->show();
  else  griff_toolbar_top->hide();
}

void midgard_CG::show_Statusleiste(bool b)
{
 ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
  if(b) handlebox_status->show();
  else  handlebox_status->hide();
}

void midgard_CG::show_Icons(bool i)
{
 ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
 bool b=MOptionen->OberCheck(Magus_Optionen::Beschriftungen).active;
 if     ( b && i) toolbar_top->set_toolbar_style(Gtk::TOOLBAR_BOTH);
 else if( b &&!i) toolbar_top->set_toolbar_style(Gtk::TOOLBAR_TEXT);
 else if(!b && i) toolbar_top->set_toolbar_style(Gtk::TOOLBAR_ICONS);
 else if(!b &&!i) toolbar_top->hide();
}

void midgard_CG::show_Beschriftungen(bool b)
{
 ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
 bool i=MOptionen->OberCheck(Magus_Optionen::Icons).active;
 if     ( b && i) toolbar_top->set_toolbar_style(Gtk::TOOLBAR_BOTH);
 else if( b &&!i) toolbar_top->set_toolbar_style(Gtk::TOOLBAR_TEXT);
 else if(!b && i) toolbar_top->set_toolbar_style(Gtk::TOOLBAR_ICONS);
 else if(!b &&!i) toolbar_top->hide();
}

void midgard_CG::show_NSC_active(bool b)
{
 ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
  if(b) eventbox_NSC_aktiv->show();
  else  eventbox_NSC_aktiv->hide();
}

void midgard_CG::show_Hausregeln_active()
{
 ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
  frame_haus_status->remove();
  Gtk::HBox *hb=manage(new class Gtk::HBox(false, 0));
  for(std::list<Magus_Optionen::st_Haus>::const_iterator i=MOptionen->getHausregeln().begin();i!=MOptionen->getHausregeln().end();++i)
   {
     if(!i->active) continue;
     Gtk::Image *p=manage(new Gtk::Image(i->bild));
     hb->pack_start(*p);
     if(i->active) p->show();
   }
  hb->show();
  frame_haus_status->add(*hb);
}

void midgard_CG::show_wizard_active(bool b)
{
 ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
  if(b) {eventbox_wizard_aktiv->show(); label_wizard->show();}
  else  {eventbox_wizard_aktiv->hide(); label_wizard->hide();}
}


void midgard_CG::on_checkbutton_Regionen_menu_(Gtk::CheckMenuItem *menu_item,cH_Region region)
{
 ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
  if(menu_item->get_active()) region->setActive(true);
  else region->setActive(false);
  on_checkbutton_Regionen_menu_(0,region);
}


void midgard_CG::on_checkbutton_Regionen_menu(gpointer gp,cH_Region region)
{
 ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
 table_grundwerte->fill_typauswahl();
 if(notebook_main->get_current_page()==PAGE_STEIGERN)
    table_steigern->load_for_page(table_steigern->notebook_lernen->get_current_page());
 else if(notebook_main->get_current_page()==PAGE_AUSRUESTUNG)
    table_ausruestung->fill_new_preise();

 for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
  {
   if(!(*i)->Offiziell() && (*i)->Active()) 
     { 
//       pixmap_logo->hide();
       eventbox_Original_Midgard->hide();
       break;
     }
  }
// menu_init();
 set_region_statusbar(region->Pic(),region->Active());
}
#endif

#if 0
void midgard_CG::Schummeln()
{
  if(schummeln)
   {
     MOptionen->set_Original(true,Magus_Optionen::Original);
     MOptionen->OptionenExecute_setzen_from_menu(Magus_Optionen::LernschemaSensitive);
     table_steigern->steigern_mit_EP_bool=false;
     MOptionen->set_Original(true,Optionen::NSC_only);
     table_grundwerte->edit_werte=true;
   }
  else
   {
     MOptionen->set_Original(false,Magus_Optionen::Original);
     table_steigern->steigern_mit_EP_bool=true;
     MOptionen->set_Original(false,Optionen::NSC_only);
     table_grundwerte->edit_werte=false;
   }
}
#endif
