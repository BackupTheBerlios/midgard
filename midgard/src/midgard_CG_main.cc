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
#include <glibmm/main.h>
#include <unistd.h>
#include "Windows_Linux.hh"
#include "MagusDialog.hh"
#include <libmagus/Ausgabe.hh>
#include <libmagus/magus_paths.h>
#include <Misc/itos.h>

// Vielleicht Anzahl an Sekunden einstellbar?
void midgard_CG::set_status(const std::string &s,bool autoclean)
{ connection_status.disconnect();
  label_status->set_text(s);
  if(autoclean)
     connection_status=Glib::signal_timeout().connect(SigC::slot(*this,&midgard_CG::timeout_status),7000);
}

bool midgard_CG::timeout_status()
{
  label_status->set_text("");
  return false;
}

void midgard_CG::on_button_html_hilfe_clicked()
{
  std::string pfad="file://"+magus_paths::with_path("index.html",false,false);
  std::string s =Programmoptionen.getString(Magus_Optionen::html_viewer).Value()+" \""+pfad+"\"";
  if (!WinLux::CreateProcess(s))
     Ausgabe(Ausgabe::Error,s+" funktioniert nicht");
}

void midgard_CG::on_button_info_clicked()
{  notebook_main->set_current_page(PAGE_INFO);
}

bool midgard_CG::on_eventbox_MCG_button_press_event(GdkEventButton *event) 
{ 
   if (event->button == 3) 
   {  menu_kontext->popup(event->button,event->time);
      return true;
   }
   return false;
}

/*
#include <Misc/itos.h>
void show_window(Gdk_Window &W)
{
 gint b,h,x,y;
 W.get_size(b,h);
 W.get_position(x,y);
 std::cout << "Position: x="<<itos(x)<<"  y="<<itos(y)<<" Br.="
 <<itos(b)<<"  Hö.="<<itos(h)<<'\n';
}
*/

void midgard_CG::on_button_menu()
{
/*
Gtk::HandleBox *HB=table_steigern->handlebox_steigern_1;
std::cout <<"HB: "<< HB->is_child_detached()<<' '<<HB->is_float_window_mapped()<<' '
<<HB->is_in_drag()<<' '<<HB->shrinks_on_detach()<<'\n';

Gdk_Window W1=HB->get_window();
Gdk_Window W2=HB->get_bin_window();
Gdk_Window W3=HB->get_float_window();
std::cout << "get_window()\t"; show_window(W1);
std::cout << "get_bin_window()\t"; show_window(W2);
std::cout << "get_float_window()\t"; show_window(W3);
*/
  menu_kontext->popup(2,0); // Gdk::CURRENT_TIME);
}
 
void midgard_CG::menu_geschichte_selected()
{
 notebook_main->set_current_page(PAGE_NEWS);
}

void midgard_CG::menu_einstellungen_aendern()
{
 notebook_main->set_current_page(PAGE_OPTIONEN);
}

void midgard_CG::on_anleitung_menu_activate()
{
  on_button_html_hilfe_clicked();
}

void midgard_CG::on_info_credits_menu_activate()
{
 notebook_main->set_current_page(PAGE_INFO);
}

void midgard_CG::on_news_menu_activate()
{
 notebook_main->set_current_page(PAGE_NEWS);
}



void midgard_CG::on_notebook_main_switch_page(GtkNotebookPage *page,guint pagenr)
{
 getChar().signal_anderer_abenteurer()();
 if(pagenr==PAGE_LERNEN)
  {getChar().getWizard().done(Wizard::LERNSCHEMA_SEITE,getAben());
  }
}


bool midgard_CG::on_eventbox_ausruestung_button_release_event(GdkEventButton *event)
{ notebook_main->set_current_page(PAGE_AUSRUESTUNG); return false;}
bool midgard_CG::on_eventbox_optionen_button_release_event(GdkEventButton *event)
{ notebook_main->set_current_page(PAGE_OPTIONEN); return false;}
bool midgard_CG::on_eventbox_zufall_button_release_event(GdkEventButton *event)
{ notebook_main->set_current_page(PAGE_ZUFALL); return false;}
bool midgard_CG::on_eventbox_beschreibung_button_release_event(GdkEventButton *event)
{ notebook_main->set_current_page(PAGE_BESCHREIBUNG); return false;}
bool midgard_CG::on_eventbox_steigern_button_release_event(GdkEventButton *event)
{ notebook_main->set_current_page(PAGE_STEIGERN); return false;}
bool midgard_CG::on_eventbox_lernen_button_release_event(GdkEventButton *event)
{ notebook_main->set_current_page(PAGE_LERNEN); return false;}
bool midgard_CG::on_eventbox_grundwerte_button_release_event(GdkEventButton *event)
{ notebook_main->set_current_page(PAGE_GRUNDWERTE); return false;}
bool midgard_CG::on_eventbox_credits_button_release_event(GdkEventButton *event)
{ notebook_main->set_current_page(PAGE_INFO); return false;}
bool midgard_CG::on_eventbox_geschichte_button_release_event(GdkEventButton *event)
{ notebook_main->set_current_page(PAGE_NEWS); return false;}

void midgard_CG::on_schlie__en1_activate()
{  button_schliessen->grab_focus(); // Fokuswechsel erzwingen (wegen ungenommener Änderungen)
   if (getChar()->gespeichert())
   {loeschen:
      AbenteurerAuswahl::Chars.erase(getChar().actualIterator());
      if (AbenteurerAuswahl::Chars.empty()) on_schliessen_CG_clicked();
      else aktiver.setAbenteurer(AbenteurerAuswahl::Chars.begin());
   }
   else
   {  MagusDialog d(this);
      d.set_text("Sollen die Änderungen an '"+getAben().Name_Abenteurer()+"' verworfen werden?");
      d.set_yes_no("Änderungen verwerfen","Nicht schließen");
      int result=d.run();
      if (result==Gtk::RESPONSE_OK) goto loeschen; 
   }
}

// das ist hier eigentlich beenden
void midgard_CG::on_schliessen_CG_clicked()
{
  while (!AbenteurerAuswahl::Chars.empty())
  {  VAbenteurer::iterator i=getChar().actualIterator();
     on_schlie__en1_activate();
     if (AbenteurerAuswahl::Chars.empty()) break;
     if (getChar().actualIterator()==i) return; // Abbruch
  }

  std::string filename="magus_optionen.xml";
  if(access(filename.c_str(),W_OK)) 
      filename=magus_paths::MagusVerzeichnis()+"magus_optionen.xml";
  Programmoptionen.save_options(filename);
  Gtk::Main::instance()->quit();
}

bool midgard_CG::on_midgard_CG_delete_event(GdkEventAny* event)
{
  on_schliessen_CG_clicked();
  return true;
}

void midgard_CG::on_exportieren_ranas_pdf_dokumente_activate()
{
  Ausgabe(Ausgabe::Error,"Noch nicht implementiert");
}

