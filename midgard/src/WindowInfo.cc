// $Id: WindowInfo.cc,v 1.65 2003/11/11 08:10:25 christof Exp $
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
#include <Gtk_OStream.h>
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

void WindowInfo::AppendShow(const std::string& s)
{ 
  Gtk::OStream os(LogWin->get_view());
  os << s <<'\n';
  os.flush();
  Flush();
}

void WindowInfo::Flush()
{
//  Gtk::OStream os(LogWin->get_view());
//  os.flush();
  LogWin->scroll();

  if(!Programmoptionen.OberCheck(Magus_Optionen::NoInfoFenster).active)
     show();
/*
      des = Gtk::Main::signal_timeout().connect(slot(this,&WindowInfo::timeout),4000);
*/
}


gint WindowInfo::timeout() 
{ 
   hide();
   return 0; 
}

void WindowInfo::on_button_erase_clicked()
{
  LogWin->get_store()->clear();
}
