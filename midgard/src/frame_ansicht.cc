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
#include "frame_ansicht.hh"

#include<list>
#include "Optionen.hh"
#include "midgard_CG.hh"
#include <bool_CheckButton.hh>


void frame_ansicht::set_Hauptfenster(midgard_CG *h)
{
 hauptfenster=h;
}

/*
static void wert_changed(gpointer gp)
{ 
  std::cout << "OPTIONEN: WC: "<<  *(bool*)(gp)<<'\n';
} 
*/

void frame_ansicht::init()
{
 assert(hauptfenster);
 Gtk::Table *table=manage(new Gtk::Table(1,1,false));  
 std::list<Magus_Optionen::st_Ober> &L=Programmoptionen->getOber();
 int count=0;
 for(std::list<Magus_Optionen::st_Ober>::iterator i=L.begin();i!=L.end();++i)
  {
   if(!i->show) continue;
   bool_CheckButton *cb = manage(new bool_CheckButton(i->active,i->text));
//   i->active.signal_changed().connect(SigC::bind(SigC::slot(*hauptfenster,&midgard_CG::Ober_setzen_from_menu),i->index));
//i->active.signal_changed().connect(SigC::slot(&wert_changed));
   table->attach(*cb,0,1,count,count+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
   ++count;
  }
 add(*table);
 show_all(); 
}

#if 0
void frame_ansicht::element_activate(gpointer gp,Magus_Optionen::OberIndex index)
{
  hauptfenster->Ober_setzen_from_menu(index);
}   
#endif
