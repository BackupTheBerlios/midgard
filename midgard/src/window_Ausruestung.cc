/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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
#include "window_Ausruestung.hh"
#include <Gtk_OStream.h>


window_Ausruestung::window_Ausruestung(const Datenbank& dat)
: Database(dat)
{
  fill_optionmenu_art();
  optionmenu_art->get_menu()->deactivate.connect(SigC::slot(static_cast<class window_Ausruestung*>(this), &window_Ausruestung::opt_art));
  fill_optionmenu_typ();
  optionmenu_typ->get_menu()->deactivate.connect(SigC::slot(static_cast<class window_Ausruestung*>(this), &window_Ausruestung::opt_typ));
}



void window_Ausruestung::on_clist_preisliste_select_row(gint row, gint column, GdkEvent *event)
{
}

void window_Ausruestung::fill_preisliste()
{
  cH_PreiseMod art=static_cast<PreiseMod*>(optionmenu_art->get_menu()->get_active()->get_user_data());
  PreiseMod::st_vec *modi=static_cast<PreiseMod::st_vec*>(optionmenu_typ->get_menu()->get_active()->get_user_data());
  Gtk::OStream os(clist_preisliste);
  for(std::list<cH_Preise>::const_iterator i=Database.preise.begin();i!=Database.preise.end();++i)
   {
     if(art->Art()==(*i)->Art())
      os << (*i)->Name() 
         << (*i)->Kosten()
         << (*i)->Einheit()
         <<'\n';
   }  
}


void window_Ausruestung::opt_art()
{
  fill_optionmenu_typ();
  optionmenu_typ->get_menu()->deactivate.connect(SigC::slot(static_cast<class window_Ausruestung*>(this), &window_Ausruestung::opt_typ));
}

void window_Ausruestung::fill_optionmenu_art()
{
  Gtk::OStream os(optionmenu_art);
  for(std::list<cH_PreiseMod>::iterator i=Database.preisemod.begin();i!=Database.preisemod.end();++i)
   {
     os << (*i)->Art();
     os.flush((*i)->ref(),&HandleContent::unref);
   }  
}


void window_Ausruestung::opt_typ()
{
  fill_preisliste();
}

void window_Ausruestung::fill_optionmenu_typ()
{
  cH_PreiseMod art=static_cast<PreiseMod*>(optionmenu_art->get_menu()->get_active()->get_user_data());
  Gtk::OStream os(optionmenu_typ);
  for(std::vector<PreiseMod::st_vec>::const_iterator i=art->getVec().begin();i!=art->getVec().end();++i)
   {
     os << i->typ;
     os.flush((gpointer)&*i);
   }  
}


void window_Ausruestung::on_button_druck_clicked()
{
}


void window_Ausruestung::on_button_close_clicked()
{   
  destroy();
}
