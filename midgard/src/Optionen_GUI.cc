// $Id: Optionen_GUI.cc,v 1.3 2003/09/08 06:27:52 christof Exp $
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

#include "Optionen_GUI.hh"
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

// unn�tig ...
Glib::RefPtr<Gdk::Pixbuf> Optionen_GUI::Execute_bild(Magus_Optionen::OptionenExecuteIndex i)
{  return Glib::RefPtr<Gdk::Pixbuf>();
}
Glib::RefPtr<Gdk::Pixbuf> Optionen_GUI::Check_bild(Magus_Optionen::OptionenCheckIndex i)
{  return Glib::RefPtr<Gdk::Pixbuf>();
}
	// Abenteurerspezifisch
Glib::RefPtr<Gdk::Pixbuf> Optionen_GUI::Check_bild(Optionen::OptionenCheckIndex i)
{  switch(i)
   {  case Optionen::Original: return MagusImage("midgard_logo_tiny.xpm");
      case Optionen::NSC_only: return MagusImage("NSC-Mode-32.xpm");
      default: return Glib::RefPtr<Gdk::Pixbuf>();
   }
}

Glib::RefPtr<Gdk::Pixbuf> Optionen_GUI::Haus_bild(Optionen::HausIndex i)
{  switch(i)
   {  case Optionen::Gold: return MagusImage("Haus-1-2-1-26.xpm");
      case Optionen::Werte100: return MagusImage("Haus-Super-26.xpm");
      default: return Glib::RefPtr<Gdk::Pixbuf>();
   }
}

#if 0
#include "midgard_CG.hh"
#include "customize_toolbars.h"
#include "Windows_Linux.hh"
#include <libmagusicons/magusicons.h>
//#include <gdkmm.h>

//void Midgard_Optionen::deactivate_Original()
void Midgard_Optionen::set_Original(bool active,OptionenCheckIndex index)
{
  for(std::list<Midgard_Optionen::st_OptionenCheck>::iterator i=list_OptionenCheck.begin();i!=list_OptionenCheck.end();++i)
   {
     if (i->index==index) i->active=active;
   }
}   



void Midgard_Optionen::OptionenCheck_setzen_from_menu(OptionenCheckIndex index)
{
//  if(!hauptfenster->fire_enabled) return;
//  hauptfenster->fire_enabled=false;
  for(std::list<Midgard_Optionen::st_OptionenCheck>::iterator i=list_OptionenCheck.begin();i!=list_OptionenCheck.end();++i)
   {
     if(i->index!=index) continue;
     if     (i->index==Original) hauptfenster->checkbutton_original(i->active);
     else if(i->index==Drei_Tasten_Maus) hauptfenster->show_3_Tasten_Maus(i->active);
     else if(i->index==NSC_only) {hauptfenster->show_NSC_active(i->active);
                                  hauptfenster->table_grundwerte->fill_typauswahl();
                                  hauptfenster->table_grundwerte->fill_typauswahl_2();} // zum Neuaufbau des Typmenüs
     else if(i->index==Wizard_immer_starten) hauptfenster->show_wizard_active(i->active);
     else if(i->index==Notebook_start)  
      { //i->wert=wert;
//        if(!i->spin) return;
//cout << "Option: "<<i->spin<<'\n';
//        if(i->active) i->spin->show();
//        else i->spin->hide();
      }
   }
//  hauptfenster->fire_enabled=true;
}
 
void Midgard_Optionen::OptionenExecute_setzen_from_menu(OptionenExecuteIndex index)
{
  if(index==LernschemaSensitive) hauptfenster->lernschema_sensitive(true);
  if(index==show_InfoWindow) hauptfenster->InfoFenster->Show();
}

void Midgard_Optionen::Hausregeln_setzen_from_menu(HausIndex index)
{
  for(std::list<st_Haus>::iterator i=list_Hausregeln.begin();i!=list_Hausregeln.end();++i)
   {
     if(i->index==index) 
      { 
        if(i->active) set_Original(false,Original);
        hauptfenster->show_Hausregeln_active();
        return;
      }
   }
}   
    
void Midgard_Optionen::Ober_setzen_from_menu(OberIndex index)
{
  for(std::list<st_Ober>::iterator i=list_Ober.begin();i!=list_Ober.end();++i)
   {
     if(i->index==index) 
      { 
        if     (index==Bilder) hauptfenster->show_Pics(i->active);
        else if(index==AutoShrink) hauptfenster->autoshrink(i->active);
        else if(index==Menueleiste) hauptfenster->show_Menueleiste(i->active);
        else if(index==Knopfleiste) hauptfenster->show_Knopfleiste(i->active);
        else if(index==Status) hauptfenster->show_Statusleiste(i->active);
        else if(index==NoInfoFenster) ;
        else if(index==BegruessungsFenster) ;
        else if(index==Icons) 
         { if(!i->active && !OberCheck(Beschriftungen).active)
            {
              Ausgabe(Ausgabe::Error,"Beschriftungen und Icons dürfen nicht gleichzeitig nicht angewählt sein.");
//              i->active=true;
            }
           else 
              hauptfenster->show_Icons(i->active);
         }
        else if(index==Beschriftungen) 
         { if(!i->active && !OberCheck(Icons).active)
            {
              Ausgabe(Ausgabe::Error,"Beschriftungen und Icons dürfen nicht gleichzeitig nicht angewählt sein.");
//              i->active=true;
            }
           else 
              hauptfenster->show_Beschriftungen(i->active);
         }
        else if(index==Customize_Icons)
         {
           Gtk::CustomizeToolbars(hauptfenster->notebook_main,
                     i->active,OberCheck(Customize_Text).active,
                     OberCheck(Customize_Tab).active);
         }
        else if(index==Customize_Text)
         {
           Gtk::CustomizeToolbars(hauptfenster->notebook_main,
                     OberCheck(Customize_Icons).active,i->active,
                     OberCheck(Customize_Tab).active);
         }
        else if(index==Customize_Tab)
         {
           Gtk::CustomizeToolbars(hauptfenster->notebook_main,
                     OberCheck(Customize_Icons).active,
                     OberCheck(Customize_Text).active,i->active);
         }
//        hauptfenster->menu_init();
        return;
      }
   }
}   

void Midgard_Optionen::Icon_setzen_from_menu(IconIndex index)
{
//  assert(b);
  static bool setbool=true;
  if(setbool==false) return;
  for(std::list<st_Icon>::iterator i=list_Icon.begin();i!=list_Icon.end();++i)
   {
     setbool=false;
     if(i->index!=index) i->active = false;
   }
  hauptfenster->Icons_setzen();
  setbool=true;
}   


    
void Midgard_Optionen::pdfViewer_setzen_from_menu(pdfViewerIndex index)
{
  for(std::list<st_pdfViewer>::iterator i=list_pdfViewer.begin();i!=list_pdfViewer.end();++i)
   {
     if(i->index==index) i->active = true  ;
     else                i->active = false ;
   }
}   

//static void print_it(gpointer x)
//{  std::cout << "changed " << *(int*)x << '\n';
//} 

 
#include <gtk/gtkhandlebox.h>

void detachHB(Gtk::HandleBox &HB,int x,int y,int b,int h)
{
  HB.gobj()->child_detached = true;
  Glib::RefPtr<Gdk::Window> w=HB.get_float_window();
  HB.get_bin_window()->reparent(w,0,0);

//  HB.get_float_window().set_hints(x, y, 50, 50, 0, 0, GDK_HINT_POS); 
//  HB.get_float_window()->set_hints(x, y, 50, 50, 100, 100, GDK_HINT_MAX_SIZE); 
  HB.get_float_window()->move_resize(x,y,b,h);
  HB.get_float_window()->show();
//  HB.gobj()->float_window_mapped = true;
  HB.queue_resize();
}
                                                   
#endif
