/*  MAGuS: Midgard Abenteurer Generieren Und Steigern
 *  Copyright (C) 2002 Malte Thoma
 *  Copyright (C) 2004 Christof Petig
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
#include "frame_icons.hh"

#include "midgard_CG.hh"
#include <bool_CheckButton.hh>
#include <libmagus/Magus_Optionen.hh>

void frame_icons::set_Hauptfenster(midgard_CG *h)
{
 hauptfenster=h;
}

void frame_icons::init() 
{
 assert(hauptfenster);
 Gtk::Table *table=manage(new Gtk::Table(1,1,false));
 std::list<Magus_Optionen::st_Icon> &L=Programmoptionen->getIcon();
 int count=0;
 for(std::list<Magus_Optionen::st_Icon>::iterator i=L.begin();i!=L.end();++i)
  {
    bool_CheckButton *cb = Gtk::manage(new bool_CheckButton(i->active,i->text));
//    i->active.signal_changed().connect(SigC::bind(SigC::slot(*this,&frame_icons::element_activate),i->index));
    table->attach(*cb,0,1,count,count+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
    ++count;
  }
 table->show_all();
 add(*table);
}

#if 0
void frame_icons::element_activate(gpointer gp,Magus_Optionen::IconIndex index)
{
  Programmoptionen->Icon_setzen_from_menu(index);
}
#endif
