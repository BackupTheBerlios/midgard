// $Id: midgard_CG_optionen.cc,v 1.114 2002/11/28 17:56:57 thoma Exp $
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
#include <xml.h>
#include <Misc/Trace.h>


void midgard_CG::set_info(const std::string& sadd)
{
 ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
 InfoFenster->AppendShow(sadd);
}

void midgard_CG::OptionenExecute_setzen_from_menu(Midgard_Optionen::OptionenExecuteIndex index)
{
 ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
 MOptionen->OptionenExecute_setzen_from_menu(index);
}


void midgard_CG::Ober_element_activate(gpointer gp,Midgard_Optionen::OberIndex index)
{
 ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
  getOptionen()->Ober_setzen_from_menu(index);
}

void midgard_CG::checkbutton_original(bool active)
{
 ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
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

void midgard_CG::lernschema_sensitive(bool active)
{
 ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
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
 ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
 InfoFenster->show_pic(b);
 if(b)
  {
    table_grundwerte->pixmap_dfr4->show();
//    pixmap_dfr3->show();
    table_lernschema->scrolledwindow_dfr3->show(); 
    table_steigern->pixmap_kurai->show();
  }
 else
  {
    table_grundwerte->pixmap_dfr4->hide();
//    pixmap_dfr3->hide();
    table_lernschema->scrolledwindow_dfr3->hide(); 
    table_steigern->pixmap_kurai->hide();
  }
}

void midgard_CG::show_Menueleiste(bool b)
{
 ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
  if(b) handlebox_menu->show();
  else  handlebox_menu->hide();
}

void midgard_CG::show_Knopfleiste(bool b)
{
 ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
  if(b) griff_toolbar_top->show();
  else  griff_toolbar_top->hide();
}

void midgard_CG::show_Statusleiste(bool b)
{
 ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
  if(b) handlebox_status->show();
  else  handlebox_status->hide();
}

void midgard_CG::show_Icons(bool i)
{
 ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
 bool b=MOptionen->OberCheck(Midgard_Optionen::Beschriftungen).active;
 if     ( b && i) toolbar_top->set_style(GTK_TOOLBAR_BOTH);
 else if( b &&!i) toolbar_top->set_style(GTK_TOOLBAR_TEXT);
 else if(!b && i) toolbar_top->set_style(GTK_TOOLBAR_ICONS);
 else if(!b &&!i) toolbar_top->hide();
}

void midgard_CG::show_Beschriftungen(bool b)
{
 ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
 bool i=MOptionen->OberCheck(Midgard_Optionen::Icons).active;
 if     ( b && i) toolbar_top->set_style(GTK_TOOLBAR_BOTH);
 else if( b &&!i) toolbar_top->set_style(GTK_TOOLBAR_TEXT);
 else if(!b && i) toolbar_top->set_style(GTK_TOOLBAR_ICONS);
 else if(!b &&!i) toolbar_top->hide();
}

void midgard_CG::show_3_Tasten_Maus(bool b)
{
 ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
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
 ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
  if(b) eventbox_NSC_aktiv->show();
  else  eventbox_NSC_aktiv->hide();
}

void midgard_CG::show_Hausregeln_active()
{
 ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
  frame_haus_status->remove();
  Gtk::HBox *hb=manage(new class Gtk::HBox(false, 0));
  for(std::list<Midgard_Optionen::st_Haus>::const_iterator i=MOptionen->getHausregeln().begin();i!=MOptionen->getHausregeln().end();++i)
   {
     if(!i->active) continue;
     Gtk::Pixmap *p=manage(new Gtk::Pixmap(i->bild));     
     hb->pack_start(*p);
     if(i->active) p->show();
   }
  hb->show();
  frame_haus_status->add(*hb);
}

void midgard_CG::show_wizard_active(bool b)
{
 ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
  if(b) {eventbox_wizard_aktiv->show(); label_wizard->show();}
  else  {eventbox_wizard_aktiv->hide(); label_wizard->hide();}
}


void midgard_CG::on_checkbutton_Regionen_menu_(Gtk::CheckMenuItem *menu_item,cH_Region region)
{
 ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
  if(menu_item->get_active()) region->setActive(true);
  else region->setActive(false);
  on_checkbutton_Regionen_menu_(0,region);
}


void midgard_CG::on_checkbutton_Regionen_menu(gpointer gp,cH_Region region)
{
 ManuProC::Trace _t(ManuProC::Tracer::Auftrag,__FUNCTION__);
 table_grundwerte->fill_typauswahl();
 if(notebook_main->get_current_page_num()==PAGE_STEIGERN)
    table_steigern->load_for_page(table_steigern->notebook_lernen->get_current_page_num());
 else if(notebook_main->get_current_page_num()==PAGE_AUSRUESTUNG)
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

void midgard_CG::Schummeln()
{
  if(schummeln)
   {
     MOptionen->set_Original(false,Midgard_Optionen::Original);
     MOptionen->OptionenExecute_setzen_from_menu(Midgard_Optionen::LernschemaSensitive);
     table_steigern->steigern_mit_EP_bool=false;
     set_Original(false,Midgard_Optionen::NSC_only);
   }
  else
   {
   }
}
