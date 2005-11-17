// $Id: Midgard_Info.cc,v 1.90 2005/11/17 07:25:31 christof Exp $
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

#include "config.h"
#include "Midgard_Info.hh"
#include "midgard_CG.hh"
#include <gtkmm/main.h>
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);
#include <libmagus/Ausgabe.hh>
// to redefine VERSION
#include "config.h"
#include <libmagus/Datenbank.hh>
#include <libmagus/magus_paths.h>
#include <libmagus/LaTeX_drucken.hh>

Midgard_Info::Midgard_Info(GlademmData *data) : Midgard_Info_glade(data)
{
   versionsnummer->set_text("Version: "+(std::string)VERSION
   		+"\n\"Spirit of Sargon\""); // Hommage to Andr� (my first SL)
   set_Regionen(Datenbank.Regionen);
}


void Midgard_Info::set_Regionen(const std::vector<cH_Region>& Regionen)
{
  frame_regionen->remove();
  Gtk::Table *_tab=manage(new Gtk::Table(1,1,false));
  int row=0;
  for(std::vector<cH_Region>::const_iterator i=Regionen.begin();i!=Regionen.end();++i)
   {
     Gtk::Label *_lcopy=manage (new Gtk::Label((*i)->Copyright(),0,0));
     Gtk::Label *_lname=manage (new Gtk::Label((*i)->Titel(),0,0));
     Gtk::Image *_image=manage (new Gtk::Image(RegionenPic::PicModel((*i)->Pic())));
     _tab->attach(*_image,0,1,row,row+1,Gtk::AttachOptions(0),Gtk::AttachOptions(0),0,0);
     _tab->attach(*_lname,1,2,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
     _tab->attach(*_lcopy,2,3,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
     _lcopy->show();
     _lname->show();
     _image->show();
     ++row;
   }
  std::string illutxt2="Abenteurergruppe (DFR3) von Josef Ochmann\ncopyright 1985";
  Gtk::Label *_li2=manage (new Gtk::Label(illutxt2,0,0));
  Gtk::Image *_pi2=manage(new Gtk::Image(MagusImage("Dfr3-50.xpm")));
  _li2->set_justify(Gtk::JUSTIFY_LEFT);
  _tab->attach(*_pi2,0,1,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  _tab->attach(*_li2,1,3,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  _li2->show();
  _pi2->show();
  ++row;

  std::string illutxt3="Kan Thai Krieger von Hank Wolf\ncopyright 1992";
  Gtk::Label *_li3=manage (new Gtk::Label(illutxt3,0,0));
  Gtk::Image *_pi3=manage(new Gtk::Image(MagusImage("Kurai-50.xpm")));
  _li3->set_justify(Gtk::JUSTIFY_LEFT);
  _tab->attach(*_pi3,0,1,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  _tab->attach(*_li3,1,3,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  _li3->show();
  _pi3->show();
  ++row;

  std::string illutxt="Alle anderen Illustrationen von Werner Öckl\ncopyright 2000-2001";
  Gtk::Label *_li=manage (new Gtk::Label(illutxt,0,0));
  Gtk::Image *_pi=manage(new Gtk::Image(MagusImage("pdolch_.xpm")));
  _li->set_justify(Gtk::JUSTIFY_LEFT);
  _tab->attach(*_pi,0,1,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  _tab->attach(*_li,1,3,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  _li->show();
  _pi->show();
  ++row;

  std::string copytxt="MIDGARD ist Copyright 1981-2005 by\nVerlag für F&SF-Spiele, Stelzenberg";
  Gtk::Label *_lc=manage (new Gtk::Label(copytxt,0,0));
  Gtk::Image *_pc=manage(new Gtk::Image(MagusImage("Money-50.xpm")));
  _lc->set_justify(Gtk::JUSTIFY_LEFT);
  _tab->attach(*_pc,0,1,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  _tab->attach(*_lc,1,3,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  _lc->show();
  _pc->show();
  ++row;

  std::string copytxt2="Sämtliche Daten und Bilder wurden mit freundlicher\nErlaubnis des VFSF entnommen, copyright 1980-2001 by Verlag\n für F&SF-Spiele, Stelzenberg";
  Gtk::Label *_lc2=manage (new Gtk::Label(copytxt2,0,0));
  Gtk::Image *_pc2=manage(new Gtk::Image(MagusImage("Money-50.xpm")));
  _lc2->set_justify(Gtk::JUSTIFY_LEFT);
  _tab->attach(*_pc2,0,1,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  _tab->attach(*_lc2,1,3,row,row+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
  _lc2->show();
  _pc2->show();
  ++row;

  _tab->set_col_spacings(10);
  frame_regionen->add(*_tab);
  _tab->show();
}

std::string Midgard_Info::umbruch(std::string s)
{
 s.replace(s.find("-"),1,"\n");
 return s;
}


void Midgard_Info::lizenz_anzeigen()
{ std::string license=magus_paths::with_path("LICENSE.pdf",false,true);
  LaTeX_drucken::DisplayPDF(license);
//Ausgabe(Ausgabe::Error,"hier müsste jetzt die GPL hin");
}
