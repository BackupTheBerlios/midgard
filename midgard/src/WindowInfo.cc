// $Id: WindowInfo.cc,v 1.25 2002/02/08 15:20:26 thoma Exp $
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

// generated 2001/2/27 13:32:15 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to WindowInfo.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "WindowInfo.hh"
#include <gtk--/main.h>
#include "midgard_CG.hh"

void WindowInfo::on_button_info_ok_clicked()
{   
 if(autoclean) des.disconnect();
// destroy();
  hide();
}

WindowInfo::WindowInfo()
: mystream(0)
{
//   infotext->set_text(s.c_str());

   if (mystream) delete mystream;
   Gtk::OStream *mystream = new Gtk::OStream(LogWin->get_list());
   ((Gtk::OStream*)mystream)->flushed.connect(SigC::slot(LogWin,&logwin::scroll));

   if(autoclean)
    {
      des = Gtk::Main::timeout.connect(slot(this,&WindowInfo::timeout),4000);
//      button_info_ok->hide();
    }
  hide();
}

void WindowInfo::AppendShow(const std::string& s,bool autoclean)
{
  (*mystream) << s;
  Flush(autoclean);
}

void WindowInfo::AppendShow(int i,bool autoclean)
{
  (*mystream) << i;
  Flush(autoclean);
}

void WindowInfo::Flush(bool autoclean)
{
  (*mystream).flush();
  show();
  if(autoclean)
    {
      des = Gtk::Main::timeout.connect(slot(this,&WindowInfo::timeout),4000);
//      button_info_ok->hide();
    }
}


gint WindowInfo::timeout() 
{ 
//   destroy();
   hide();
   return 0; 
}

