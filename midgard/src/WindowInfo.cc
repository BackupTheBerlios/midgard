// $Id: WindowInfo.cc,v 1.32 2002/04/08 14:05:38 thoma Exp $
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
  if(Modus==Autoclean) des.disconnect();
  MBE=0;
  hide();
}

void WindowInfo::on_button_bestaetigen_clicked()
{
 if(MBE)
  {
    if     (Modus==ZaubernLernen) hauptfenster->kaempfer_lernt_zaubern(*MBE);
    else if(Modus==PraxisPunkte)  hauptfenster->PraxisPunkt_to_AEP(*MBE);
  }
 else
  { cerr << "MBE existiert nicht\n";}
 MBE=0;
 hide();
}

WindowInfo::WindowInfo(midgard_CG* h)
: mystream(0), hauptfenster(h)
{
   if (mystream) delete mystream;
   Gtk::OStream *mystream = new Gtk::OStream(LogWin->get_list());
   ((Gtk::OStream*)mystream)->flushed.connect(SigC::slot(LogWin,&logwin::scroll));

/*
   if(autoclean)
    {
      des = Gtk::Main::timeout.connect(slot(this,&WindowInfo::timeout),4000);
      button_info_ok->hide();
    }
*/
  hide();
  MBE=0;
}

void WindowInfo::AppendShow(const std::string& s, emodus modus)
{ 
  Modus=modus;
  Gtk::OStream os(LogWin->get_list());
  os << s <<'\n';
  Flush();
}

void WindowInfo::AppendShow(const std::string& s, emodus modus,cH_MidgardBasicElement& _MBE)
{
  MBE=&_MBE;
  AppendShow(s,modus); 
}

void WindowInfo::AppendShow(int i, emodus modus)
{
  Modus=modus;
  Flush();
}
void WindowInfo::AppendShow(int i, emodus modus, cH_MidgardBasicElement& _MBE)
{
  MBE=&_MBE;
  AppendShow(i,modus);
}

void WindowInfo::Flush()
{
  Gtk::OStream os(LogWin->get_list());
  os.flush();
  LogWin->scroll();

  show();
  if (Modus==None || Modus==Autoclean) bestaetigen(false) ;
  else bestaetigen(true);

/*
  if(Modus==Autoclean)
    {
      des = Gtk::Main::timeout.connect(slot(this,&WindowInfo::timeout),4000);
//      button_info_ok->hide();
    }
*/
}

void WindowInfo::bestaetigen(bool b)
{
  if(b)
   {
     table_bestaetigen->show();
     table_schliessen->hide();
   }
  else
   {
     table_bestaetigen->hide();
     table_schliessen->show();
   }
}


gint WindowInfo::timeout() 
{ 
   hide();
   MBE=0;
   return 0; 
}

void WindowInfo::on_button_erase_clicked()
{
  LogWin->get_list()->items().clear(); 
}

