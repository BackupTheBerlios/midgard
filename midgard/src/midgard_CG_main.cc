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
#include <gtk--/main.h>
#include "Window_hilfe.hh"
#include <unistd.h>


void midgard_CG::set_status(const std::string &s,bool autoclean)
{
  label_status->set_text(s);
  if(autoclean)
     connection_status=Gtk::Main::timeout.connect(slot(this,&midgard_CG::timeout_status),7000);
}

gint midgard_CG::timeout_status()
{
  label_status->set_text("");
  return 0;
}

void midgard_CG::on_button_hilfe_clicked()
{
  manage(new Window_hilfe()); 
}

void midgard_CG::on_button_html_hilfe_clicked()
{
  std::string pfad="file://"+with_path("index.html",false,false);
  std::string s =MOptionen->getString(Midgard_Optionen::html_viewer)+" \""+pfad+"\""
#ifndef __MINGW32__  
							  " &"
#endif  
							  	;
  system(s.c_str());
}

void midgard_CG::on_button_info_clicked()
{
  notebook_main->set_page(PAGE_INFO);
}


gint midgard_CG::on_eventbox_MCG_button_press_event(GdkEventButton *event) 
{ 
   if (event->button == 3) 
   {  menu_kontext->popup(event->button,event->time);
      return true;
   }
   return false;
}

gint midgard_CG::on_button_menu_button_release_event(GdkEventButton *event)
{
  menu_kontext->popup(event->button,event->time);
  return true;
}
 


void midgard_CG::load_for_mainpage(guint pagenr)
{
 if(pagenr==PAGE_GRUNDWERTE)
  {
    table_grundwerte->init(this);
  }
 else if(pagenr==PAGE_LERNEN)
  {
   if(wizard && wizard->ActualStep()==Wizard::LERNSCHEMA_SEITE) 
         wizard->next_step(Wizard::LERNSCHEMA_SEITE);
   table_lernschema->init(this);
//   show_gelerntes();
  }
 else if(pagenr==PAGE_STEIGERN)
  {
    table_steigern->init(this);
  }
 else if(pagenr==PAGE_BESCHREIBUNG)
   {
     table_beschreibung->init(this);
   }
 else if(pagenr==PAGE_AUSRUESTUNG)
    table_ausruestung->init(this);
 else if(pagenr==PAGE_NEWS)
   {
    show_undo_tree();
    fill_AbenteurerListe();
   }
 else if(pagenr==PAGE_ZUFALL)
   {
     table_zufall->init(this);
   }
}


void midgard_CG::menu_geschichte_selected()
{
 notebook_main->set_page(PAGE_NEWS);
}

void midgard_CG::menu_einstellungen_aendern()
{
 notebook_main->set_page(PAGE_OPTIONEN);
}


void midgard_CG::on_notebook_main_switch_page(Gtk::Notebook_Helpers::Page *page,guint pagenr)
{
 if (!in_dtor) load_for_mainpage(pagenr);
}


gint midgard_CG::on_eventbox_ausruestung_button_release_event(GdkEventButton *event)
{ notebook_main->set_page(PAGE_AUSRUESTUNG); return false;}
gint midgard_CG::on_eventbox_optionen_button_release_event(GdkEventButton *event)
{ notebook_main->set_page(PAGE_OPTIONEN); return false;}
gint midgard_CG::on_eventbox_zufall_button_release_event(GdkEventButton *event)
{ notebook_main->set_page(PAGE_ZUFALL); return false;}
gint midgard_CG::on_eventbox_beschreibung_button_release_event(GdkEventButton *event)
{ notebook_main->set_page(PAGE_BESCHREIBUNG); return false;}
gint midgard_CG::on_eventbox_steigern_button_release_event(GdkEventButton *event)
{ notebook_main->set_page(PAGE_STEIGERN); return false;}
gint midgard_CG::on_eventbox_lernen_button_release_event(GdkEventButton *event)
{ notebook_main->set_page(PAGE_LERNEN); return false;}
gint midgard_CG::on_eventbox_grundwerte_button_release_event(GdkEventButton *event)
{ notebook_main->set_page(PAGE_GRUNDWERTE); return false;}
gint midgard_CG::on_eventbox_credits_button_release_event(GdkEventButton *event)
{ notebook_main->set_page(PAGE_INFO); return false;}
gint midgard_CG::on_eventbox_geschichte_button_release_event(GdkEventButton *event)
{ notebook_main->set_page(PAGE_NEWS); return false;}



void midgard_CG::on_schliessen_CG_clicked()
{
  std::string filename="magus_optionen.xml";
  if(access(filename.c_str(),W_OK)) 
      filename=magus_verzeichnis+"magus_optionen.xml";

  MOptionen->save_options(filename,InfoFenster);
  if(Char.unsaved_exist())
   {
     notebook_main->set_page(PAGE_NEWS);
     set_status("Es existieren nichtgespeicherte Abenteurer",false);
     InfoFenster->AppendShow("Es existieren nichtgespeicherte Abenteurer,\n soll das Programm trotzdem beendet werden?",WindowInfo::Exit_ohne_speichern);
     return;
   }
  on_button_quit_confirm_clicked();
}

void midgard_CG::on_button_quit_confirm_clicked()
{
  connection_status.disconnect();
  Gtk::Main::instance()->quit();
}

gint midgard_CG::on_midgard_CG_delete_event(GdkEventAny* event)
{
  on_schliessen_CG_clicked();
  return true;
}

