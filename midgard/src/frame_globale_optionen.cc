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
#include "frame_globale_optionen.hh"

#include<list>
#include "Optionen_GUI.hh"
#include "midgard_CG.hh"
#include <gtkmm/separator.h>
#include <int_SpinButton.hh>
#include <bool_CheckButton.hh>
#if MPC_SIGC_VERSION > 0x120
#  include <sigc++/bind.h>
#endif

void frame_globale_optionen::set_Hauptfenster(midgard_CG *h)
{
 hauptfenster=h;
}


void frame_globale_optionen::init()
{
 assert(hauptfenster);
// assert(hauptfenster->getOptionen());
 Gtk::Table *table=manage(new Gtk::Table(1,1,false));
 int count=0;
 std::list<Magus_Optionen::st_OptionenCheck> &L=Programmoptionen->getOptionenCheck();
 for(std::list<Magus_Optionen::st_OptionenCheck>::iterator i=L.begin();i!=L.end();++i)
  {
   bool_CheckButton *cb = manage(new bool_CheckButton(i->active,i->text));
   i->active.signal_changed().connect(SigC::bind(SigC::slot(*this,&frame_globale_optionen::element_activate_C),i->index));
   Gtk::Table *t=manage(new Gtk::Table(1,1,false));
   t->attach(*cb,0,1,0,1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
   if(i->wert!=midgard_CG::NOPAGE) 
    {
      int min=midgard_CG::PAGE_INFO;
      int max=midgard_CG::PAGE_ZUFALL;
      int_SpinButton *spin=Gtk::manage(new int_SpinButton(i->wert, min, max));
      i->active.signal_changed().connect(SigC::bind(SigC::slot(*this,&frame_globale_optionen::element_show_or_hide),spin,&(i->wert)));
      t->attach(*spin,1,2,0,1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
    }
   else if(Optionen_GUI::Check_bild(i->index))
    {
      Gtk::Image *_o=Gtk::manage(new Gtk::Image(Optionen_GUI::Check_bild(i->index)));
      t->attach(*_o,1,2,0,1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
    }
   table->attach(*t,0,1,count,count+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
   ++count;
  } 
 Gtk::HSeparator *hseparator = manage(new class Gtk::HSeparator());
 table->attach(*hseparator, 0, 1, count, count+1, Gtk::FILL, Gtk::AttachOptions(0), 0, 0);
 ++count;

#if 0
 std::list<Optionen::st_OptionenCheck> &L2=hauptfenster->getAben().getOptionen().getOptionenCheck();
 for(std::list<Optionen::st_OptionenCheck>::iterator i=L2.begin();i!=L2.end();++i)
  {
   bool_CheckButton *cb = manage(new bool_CheckButton(hauptfenster->getChar().proxies.checks[i->index],i->text));
#warning undosave muesste angehaengt werden
//   i->active.signal_changed().connect(SigC::bind(SigC::slot(*this,&frame_globale_optionen::element_activate_C),i->index));
   Gtk::Table *t=manage(new Gtk::Table(1,1,false));
   t->attach(*cb,0,1,0,1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
   if(Optionen_GUI::Check_bild(i->index))
    {
      Gtk::Image *_o=Gtk::manage(new Gtk::Image(Optionen_GUI::Check_bild(i->index)));
      t->attach(*_o,1,2,0,1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
    }
   table->attach(*t,0,1,count,count+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
   ++count;
  } 
 Gtk::Label *label = Gtk::manage(new class Gtk::Label("Hausregeln"));
 table->attach(*label, 0, 1, count, count+1, Gtk::AttachOptions(0), Gtk::AttachOptions(0), 0, 0);
 ++count;
 std::list<Optionen::st_Haus> &L3=hauptfenster->getAben().getOptionen().getHausregeln();
 for(std::list<Optionen::st_Haus>::iterator i=L3.begin();i!=L3.end();++i)
  {
   bool_CheckButton *cb = manage(new bool_CheckButton(hauptfenster->getChar().proxies.hausregeln[i->index],i->text));
   i->active.signal_changed().connect(SigC::bind(SigC::slot(*this,&frame_globale_optionen::element_activate_H),i->index));

   Gtk::Table *t=manage(new Gtk::Table(1,1,false));
   t->attach(*cb,0,1,0,1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
   if(Optionen_GUI::Haus_bild(i->index))
     {
        Gtk::Image *_o=Gtk::manage(new Gtk::Image(Optionen_GUI::Haus_bild(i->index)));
        t->attach(*_o,1,2,0,1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
     }
   table->attach(*t,0,1,count,count+1,Gtk::FILL,Gtk::AttachOptions(0),0,0);
   ++count;
  } 
#endif
 add(*table);
 show_all();
}

void frame_globale_optionen::element_show_or_hide(gpointer gp,Gtk::Widget *widget,Model<int> *wert)
{
  if(*static_cast<bool*>(gp)) widget->show();
  else { 
      widget->hide();
      *wert=-1;
   }
}

#warning sollte noch weg
void frame_globale_optionen::element_activate_C(gpointer gp,Magus_Optionen::OptionenCheckIndex index)
{
//  hauptfenster->getAben().getOptionen().OptionenCheck_setzen_from_menu(index);
#if 0
  if(index==Magus_Optionen::Original)
   {
    if(hauptfenster->getAben().getOptionen().OptionenCheck(index).active)
       hauptfenster->getAben().getOptionen().setAllHausregeln(false);
   }
#endif
}

#if 0
void frame_globale_optionen::element_activate_H(gpointer gp,Optionen::HausIndex index)
{
//  hauptfenster->getAben().getOptionen().Hausregeln_setzen_from_menu(index);
}
#endif
