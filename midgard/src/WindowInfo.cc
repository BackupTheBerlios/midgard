// $Id: WindowInfo.cc,v 1.34 2002/04/10 15:58:49 thoma Exp $
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
#include "Fertigkeiten.hh"
#include "../pixmaps/Excl-32.xpm"
#include <gtk--/button.h>
#include <gtk--/table.h>   
#include <gtk--/label.h>
#include <gtk--/box.h>
#include <Aux/itos.h>

void WindowInfo::on_button_info_ok_clicked()
{   
  if(Modus==Autoclean) des.disconnect();
  hide();
}

void WindowInfo::on_button_bestaetigen_clicked()
{
 if      (Modus==ZaubernLernen)   hauptfenster->kaempfer_lernt_zaubern(MBE);
 else assert(!"never get here");
// else if (Modus==PraxisPunkteMBE) hauptfenster->PraxisPunkt_to_AEP(MBE);
}


void WindowInfo::on_button_auswahl_clicked(int connect)
{
 assert(Modus==PraxisPunkteMBE);
  if       (connect==1) on_button_info_ok_clicked();
  else if  (connect==2) hauptfenster->PraxisPunkt_to_AEP(MBE,true,false);
  else if  (connect==3) hauptfenster->PraxisPunkt_to_AEP(MBE,false,false);
  else if  (connect==4) hauptfenster->PraxisPunkt_to_AEP(MBE,true,true);
  else if  (connect==5) hauptfenster->PraxisPunkt_to_AEP(MBE,false,true);
  frame_auswahl->remove();
  hide();
}


WindowInfo::WindowInfo(midgard_CG* h)
: mystream(0), hauptfenster(h), MBE(new Fertigkeit(*cH_Fertigkeit("",true)))
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
  MBE=_MBE;
  AppendShow(s,modus); 
}

void WindowInfo::Flush()
{
  Gtk::OStream os(LogWin->get_list());
  os.flush();
  LogWin->scroll();

  show();
  if (Modus==None || Modus==Autoclean) bestaetigen(false) ;
  else if (Modus==PraxisPunkteMBE) auswahl();
  else bestaetigen(true);

/*
  if(Modus==Autoclean)
    {
      des = Gtk::Main::timeout.connect(slot(this,&WindowInfo::timeout),4000);
//      button_info_ok->hide();
    }
*/
}


void WindowInfo::auswahl()
{
  table_bestaetigen->hide();
  table_schliessen->hide();
  Gtk::Table *table_auswahl = manage(new class Gtk::Table(1, 5, true));
  for(int i=0;i<5;++i)
   {
     Gtk::Pixmap *p = manage(new class Gtk::Pixmap(Excl_32_xpm));
     Gtk::Label  *l = manage(new class Gtk::Label(itos(i+1)+"."));
     Gtk::Button *b = auswahl_button(p,l,i+1);
     table_auswahl->attach(*b, i, i+1, 0, 1, GTK_FILL, 0, 0, 0);
   }
  table_auswahl->show_all();
  frame_auswahl->add(*table_auswahl);
}

Gtk::Button* WindowInfo::auswahl_button(Gtk::Pixmap *p,Gtk::Label *l,int connect)
{
  p->set_alignment(0.5, 0.5);
  p->set_padding(0.5, 0.5);
  l->set_alignment(0.5, 0.5);
  l->set_padding(0, 0);
  Gtk::HBox *hbox = manage(new class Gtk::HBox(false, 0));
  Gtk::Button *button = manage(new class Gtk::Button()); 
  hbox->pack_start(*p);
  hbox->pack_start(*l);
  button->set_flags(GTK_CAN_FOCUS);
  button->add(*hbox);
  button->clicked.connect(SigC::bind(SigC::slot(static_cast<class WindowInfo*>(this), &WindowInfo::on_button_auswahl_clicked),connect));
  return button;
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
   return 0; 
}

void WindowInfo::on_button_erase_clicked()
{
  LogWin->get_list()->items().clear(); 
}

