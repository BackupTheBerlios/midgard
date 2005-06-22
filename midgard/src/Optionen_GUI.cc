// $Id: Optionen_GUI.cc,v 1.11 2005/06/22 13:51:20 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2005 Christof Petig
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
#include <bool_properties.hh>
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

// unnötig ...
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
      case Optionen::ZauberBeschreibungDrucken: return MagusImage("Zauber-trans-50.xpm");
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

#include "midgard_CG.hh"
#include "customize_toolbars.h"
#include "Windows_Linux.hh"
#include <libmagus/Ausgabe.hh>
//#include <libmagusicons/magusicons.h>

void midgard_CG::customize_view(gpointer x)
{ if (!x 
    || Programmoptionen->OberCheck(Magus_Optionen::Customize_Icons).active.matches(x) 
    || Programmoptionen->OberCheck(Magus_Optionen::Customize_Text).active.matches(x)
    || Programmoptionen->OberCheck(Magus_Optionen::Customize_Tab).active.matches(x))
  { Gtk::CustomizeToolbars(notebook_main,
      Programmoptionen->OberCheck(Magus_Optionen::Customize_Icons).active,
      Programmoptionen->OberCheck(Magus_Optionen::Customize_Text).active,
      Programmoptionen->OberCheck(Magus_Optionen::Customize_Tab).active);
    Gtk::CustomizeToolbars(toolbar_top,
      Programmoptionen->OberCheck(Magus_Optionen::Customize_Icons).active,
      Programmoptionen->OberCheck(Magus_Optionen::Customize_Text).active,
      Programmoptionen->OberCheck(Magus_Optionen::Customize_Tab).active);
  }
}

void midgard_CG::connect_options()
{ Programmoptionen->OberCheck(Magus_Optionen::Customize_Icons).active.signal_changed()
    .connect(SigC::slot(*this,&midgard_CG::customize_view));
  Programmoptionen->OberCheck(Magus_Optionen::Customize_Text).active.signal_changed()
    .connect(SigC::slot(*this,&midgard_CG::customize_view));
  Programmoptionen->OberCheck(Magus_Optionen::Customize_Tab).active.signal_changed()
    .connect(SigC::slot(*this,&midgard_CG::customize_view));
  customize_view(0);
  Gtk::AssociateVisibility(handlebox_status,Programmoptionen->OberCheck(Magus_Optionen::Status).active);
  Gtk::AssociateVisibility(main_menubar,Programmoptionen->OberCheck(Magus_Optionen::Menueleiste).active);
  Gtk::AssociateVisibility(toolbar_top,Programmoptionen->OberCheck(Magus_Optionen::Knopfleiste).active);
}

void midgard_CG::Ober_setzen_from_menu(gpointer x,Magus_Optionen::OberIndex index)
{
  customize_view(x);
  for(std::list<Magus_Optionen::st_Ober>::iterator i=Programmoptionen->getOber().begin();i!=Programmoptionen->getOber().end();++i)
   {
     if(i->index==index) 
      { 
#if 0      
        if     (index==Magus_Optionen::Bilder) show_Pics(i->active);
        else if(index==Magus_Optionen::Menueleiste) show_Menueleiste(i->active);
        else if(index==Magus_Optionen::Knopfleiste) show_Knopfleiste(i->active);
        else if(index==Magus_Optionen::Status) show_Statusleiste(i->active);
        else if(index==Magus_Optionen::Icons) 
         { if(!i->active && !Programmoptionen->OberCheck(Magus_Optionen::Beschriftungen).active)
            {
              Ausgabe(Ausgabe::Error,"Beschriftungen und Icons dürfen nicht gleichzeitig nicht angewählt sein.");
//              i->active=true;
            }
           else 
              show_Icons(i->active);
         }
        else if(index==Magus_Optionen::Beschriftungen) 
         { if(!i->active && !Programmoptionen->OberCheck(Magus_Optionen::Icons).active)
            {
              Ausgabe(Ausgabe::Error,"Beschriftungen und Icons dürfen nicht gleichzeitig nicht angewählt sein.");
//              i->active=true;
            }
           else 
              show_Beschriftungen(i->active);
         }
#endif        
//        if(index==Magus_Optionen::AutoShrink) autoshrink(i->active);
        if(index==Magus_Optionen::NoInfoFenster) ;
        else if(index==Magus_Optionen::BegruessungsFenster) ;
        else if(index==Magus_Optionen::Customize_Icons
        	|| index==Magus_Optionen::Customize_Text
        	|| index==Magus_Optionen::Customize_Tab)
         {
           Gtk::CustomizeToolbars(notebook_main,
                     Programmoptionen->OberCheck(Magus_Optionen::Customize_Icons).active,
                     Programmoptionen->OberCheck(Magus_Optionen::Customize_Text).active,
                     Programmoptionen->OberCheck(Magus_Optionen::Customize_Tab).active);
           Gtk::CustomizeToolbars(toolbar_top,
                     Programmoptionen->OberCheck(Magus_Optionen::Customize_Icons).active,
                     Programmoptionen->OberCheck(Magus_Optionen::Customize_Text).active,
                     Programmoptionen->OberCheck(Magus_Optionen::Customize_Tab).active);
         }
//        menu_init();
        return;
      }
   }
}   
