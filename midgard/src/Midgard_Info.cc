// $Id: Midgard_Info.cc,v 1.74 2003/04/24 14:23:43 christof Exp $
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
#include "Midgard_Info.hh"
#include "midgard_CG.hh"
#include <gtkmm/main.h>
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

void Midgard_Info::database_hide()
{   
  frame_datenbank->hide();
}

Midgard_Info::Midgard_Info(GlademmData *data) : Midgard_Info_glade(data)
{
   versionsnummer->set_text("Version: "+(std::string)VERSION);
   while(Gtk::Main::events_pending()) Gtk::Main::iteration() ;
   frame_datenbank->show();

}


#include "../pixmaps/pdolch_.xpm"
#include "../pixmaps/Money-50.xpm"
#include "../pixmaps/Kurai-50.xpm"

void Midgard_Info::set_Regionen(const std::vector<cH_Region>& Regionen)
{
  frame_regionen->remove();
  Gtk::Table *_tab=manage(new Gtk::Table(0,0,false));
  int row=0;
  Midgard_Optionen::IconIndex II=Midgard_Optionen::Self;//=hauptfenster->MOptionen->getIconIndex();
  for(std::vector<cH_Region>::const_iterator i=Regionen.begin();i!=Regionen.end();++i)
   {
     Gtk::Label *_lcopy=manage (new Gtk::Label((*i)->Copyright(),0,0));
     Gtk::Label *_lname=manage (new Gtk::Label((*i)->Titel(),0,0));
     _tab->attach(*RegionenPic::Pic((*i)->Pic(),II),0,1,row,row+1,Gtk::AttachOptions(0),Gtk::AttachOptions(0),0,0);
     _tab->attach(*_lname,1,2,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
     _tab->attach(*_lcopy,2,3,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
     ++row;
   }
  std::string illutxt2="Abenteurergruppe (DFR3) von Josef Ochmann\ncopyright 1985";
  Gtk::Label *_li2=manage (new Gtk::Label(illutxt2,0,0));
  Gtk::Image *_pi2=manage(new Gtk::Image(MagusImage("Dfr3-50.xpm")));
  _li2->set_justify(Gtk::JUSTIFY_LEFT);
  _tab->attach(*_pi2,0,1,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  _tab->attach(*_li2,1,3,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  ++row;

  std::string illutxt3="Kan Thai Krieger von Hank Wolf\ncopyright 1992";
  Gtk::Label *_li3=manage (new Gtk::Label(illutxt3,0,0));
  Gtk::Image *_pi3=manage(new Gtk::Image(MagusImage("Kurai-50.xpm")));
  _li3->set_justify(Gtk::JUSTIFY_LEFT);
  _tab->attach(*_pi3,0,1,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  _tab->attach(*_li3,1,3,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  ++row;

  std::string illutxt="Alle anderen Illustrationen von Werner Öckl\ncopyright 2000-2001";
  Gtk::Label *_li=manage (new Gtk::Label(illutxt,0,0));
  Gtk::Image *_pi=manage(new Gtk::Image(MagusImage("pdolch_.xpm")));
  _li->set_justify(Gtk::JUSTIFY_LEFT);
  _tab->attach(*_pi,0,1,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  _tab->attach(*_li,1,3,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  ++row;

  std::string copytxt="MIDGARD ist Copyright 1981-2001 by\nVerlag für F&SF-Spiele, Stelzenberg";
  Gtk::Label *_lc=manage (new Gtk::Label(copytxt,0,0));
  Gtk::Image *_pc=manage(new Gtk::Image(MagusImage("Money-50.xpm")));
  _lc->set_justify(Gtk::JUSTIFY_LEFT);
  _tab->attach(*_pc,0,1,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  _tab->attach(*_lc,1,3,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  ++row;

  std::string copytxt2="Sämtliche Daten und Bilder wurden mit freundlicher\nErlaubnis des VFSF entnommen, copyright 1980-2001 by Verlag\n für F&SF-Spiele, Stelzenberg";
  Gtk::Label *_lc2=manage (new Gtk::Label(copytxt2,0,0));
  Gtk::Image *_pc2=manage(new Gtk::Image(MagusImage("Money-50.xpm")));
  _lc2->set_justify(Gtk::JUSTIFY_LEFT);
  _tab->attach(*_pc2,0,1,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  _tab->attach(*_lc2,1,3,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  ++row;

  _tab->set_col_spacings(10);
  _tab->show_all();
  frame_regionen->add(*_tab);
}

std::string Midgard_Info::umbruch(std::string s)
{
 s.replace(s.find("-"),1,"\n");
 return s;
}

