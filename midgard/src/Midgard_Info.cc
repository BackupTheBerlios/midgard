// $Id: Midgard_Info.cc,v 1.63 2002/02/06 11:33:11 thoma Exp $
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
#include <gtk--/main.h>

void Midgard_Info::on_button_close_clicked()
{   
//  if(hauptfenster) hauptfenster->show();
  destroy();
}

Midgard_Info::Midgard_Info(bool selfclean)
{
   versionsnummer->set_text("Version: "+(std::string)VERSION);
   while(Gtk::Main::events_pending()) Gtk::Main::iteration() ;
   if (selfclean) 
    { 
      button_close->set_sensitive(false);
      frame_datenbank->show();
//      if (hauptfenster) hauptfenster->hide();
    }
   else
    {
      frame_datenbank->hide();
    }
}


#include "../pixmaps/pdolch_.xpm"
#include "../pixmaps/Money-50.xpm"

void Midgard_Info::set_Regionen(const std::vector<cH_Region>& Regionen)
{
  frame_regionen->remove();
  Gtk::Table *_tab=manage(new Gtk::Table(0,0,false));
  int row=0;
  for(std::vector<cH_Region>::const_iterator i=Regionen.begin();i!=Regionen.end();++i)
   {
     Gtk::Label *_lcopy=manage (new Gtk::Label((*i)->Copyright(),0,0));
     Gtk::Label *_lname=manage (new Gtk::Label((*i)->Name(),0,0));
     _tab->attach(*RegionenPic::Pic((*i)->Pic()),0,1,row,row+1,0,0,0,0);
     _tab->attach(*_lname,1,2,row,row+1,GTK_FILL,0,0,0);
     _tab->attach(*_lcopy,2,3,row,row+1,GTK_FILL,0,0,0);
     ++row;
   }
  std::string illutxt2="Abenteurergruppe (DFR3) von Josef Ochmann\ncopyright 1985 by Verlag für F&SF-Spiele,\nVerwendung mit freundlicher Genehmigung des VFSF";
  Gtk::Label *_li2=manage (new Gtk::Label(illutxt2,0,0));
  Gtk::Pixmap *_pi2=manage(new Gtk::Pixmap(pdolch__xpm));
  _li2->set_justify(GTK_JUSTIFY_LEFT);
  _tab->attach(*_pi2,0,1,row,row+1,GTK_FILL,0,0,0);
  _tab->attach(*_li2,1,3,row,row+1,GTK_FILL,0,0,0);
  ++row;

  std::string illutxt3="Kan Thai Krieger von Hank Wolf\ncopyright 1992 by Verlag für F&SF-Spiele,\nVerwendung mit freundlicher Genehmigung des VFSF";
  Gtk::Label *_li3=manage (new Gtk::Label(illutxt3,0,0));
  Gtk::Pixmap *_pi3=manage(new Gtk::Pixmap(pdolch__xpm));
  _li3->set_justify(GTK_JUSTIFY_LEFT);
  _tab->attach(*_pi3,0,1,row,row+1,GTK_FILL,0,0,0);
  _tab->attach(*_li3,1,3,row,row+1,GTK_FILL,0,0,0);
  ++row;

  std::string illutxt="Alle anderen Illustrationen von Werner Öckl\ncopyright 2000-2001 by Verlag für F&SF-Spiele,\nVerwendung mit freundlicher Genehmigung des VFSF";
  Gtk::Label *_li=manage (new Gtk::Label(illutxt,0,0));
  Gtk::Pixmap *_pi=manage(new Gtk::Pixmap(pdolch__xpm));
  _li->set_justify(GTK_JUSTIFY_LEFT);
  _tab->attach(*_pi,0,1,row,row+1,GTK_FILL,0,0,0);
  _tab->attach(*_li,1,3,row,row+1,GTK_FILL,0,0,0);
  ++row;

  std::string copytxt="MIDGARD ist Copyright 1981-2001 by\nVerlag für F&SF-Spiele, Stelzenberg";
  Gtk::Label *_lc=manage (new Gtk::Label(copytxt,0,0));
  Gtk::Pixmap *_pc=manage(new Gtk::Pixmap(Money_50_xpm));
  _lc->set_justify(GTK_JUSTIFY_LEFT);
  _tab->attach(*_pc,0,1,row,row+1,GTK_FILL,0,0,0);
  _tab->attach(*_lc,1,3,row,row+1,GTK_FILL,0,0,0);
  ++row;

  std::string copytxt2="Sämtliche Daten wurden mit freundlicher\nErlaubnis des VFSF entnommen, copyright 1980-2001 by Verlag\n für F&SF-Spiele, Stelzenberg";
  Gtk::Label *_lc2=manage (new Gtk::Label(copytxt2,0,0));
  Gtk::Pixmap *_pc2=manage(new Gtk::Pixmap(Money_50_xpm));
  _lc2->set_justify(GTK_JUSTIFY_LEFT);
  _tab->attach(*_pc2,0,1,row,row+1,GTK_FILL,0,0,0);
  _tab->attach(*_lc2,1,3,row,row+1,GTK_FILL,0,0,0);
  ++row;

  _tab->set_col_spacings(10);
  _tab->show_all();
  frame_regionen->add(*_tab);
}
