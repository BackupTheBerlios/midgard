// $Id: WindowInfo.cc,v 1.67 2004/02/02 07:27:17 christof Exp $
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

#include "config.h"
#include "WindowInfo.hh"
#include <gtkmm/main.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <Misc/itos.h>
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);
#include <libmagus/Magus_Optionen.hh>

void WindowInfo::on_button_abbrechen_clicked()
{   
  des.disconnect();
  hide();
}

bool WindowInfo::on_WindowInfo_delete_event(GdkEventAny *ev)
{
 on_button_abbrechen_clicked();
 return true; // verhindert das zerstören des Objektes
}

WindowInfo::WindowInfo()
{
  hide();
}

void WindowInfo::AppendShow(const std::string& s,Ausgabe::Level l)
{ Gdk::Color c;
  switch(l)
  {  case Ausgabe::Debug: c.set_rgb_p(.5,.1,.5); break;
     case Ausgabe::Log: c.set_rgb_p(0,1,0); break;
     case Ausgabe::Warning: c.set_rgb_p(.9,.6,0); break;
     case Ausgabe::ActionNeeded: c.set_rgb_p(0,0,0); break;
     case Ausgabe::Error: c.set_rgb_p(1,.2,0); break;
     case Ausgabe::Fatal: c.set_rgb_p(.9,0,.7); break;
  }
  LogWin->append(s,c);
  LogWin->scroll();
  if(!Programmoptionen.OberCheck(Magus_Optionen::NoInfoFenster).active
  		&& l>=Ausgabe::ActionNeeded)
     show();
//  des = Glib::signal_timeout().connect(slot(this,&WindowInfo::timeout),4000);
//  Flush();
}

#if 0
void WindowInfo::Flush()
{
}
#endif

gint WindowInfo::timeout() 
{ 
   hide();
   return 0; 
}

void WindowInfo::on_button_erase_clicked()
{
  LogWin->get_store()->clear();
}
