// $Id: midgard_CG_undo.cc,v 1.23 2004/05/07 06:17:29 christof Exp $
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

#include "midgard_CG.hh"
#include <sstream>
#include <libmagus/Ausgabe.hh>
#if MPC_SIGC_VERSION > 0x120
#  include <sigc++/bind.h>
#endif
#include <gtk/gtkmenu.h>

void midgard_CG::on_button_redo_clicked()
{
  VAbenteurer::Item::const_iterator i=getChar()->getUndo();
  ++i;
  if (i!=getChar()->end()) getChar()->setUndo(i);
}


void midgard_CG::on_button_undo_clicked()
{
  VAbenteurer::Item::const_iterator i=getChar()->getUndo();
  if (i!=getChar()->begin()) 
  {  --i; 
     getChar()->setUndo(i);
  }
}

static void PosCalc(GtkMenu *menu,gint *x,gint *y,gboolean *push_in,gpointer user_data)
{  (*y)+=4;
   (*push_in)=true;
}

void midgard_CG::on_undo_secondpressed(int mbutton)
{  VAbenteurer::Item::const_iterator i=getChar()->getUndo();
   unsigned count=0;
   if (undo_menu) delete undo_menu;
   undo_menu=new Gtk::Menu();
   while (i!=getChar()->begin())
   {  --i; 
      Gtk::MenuItem *mi=manage(new Gtk::MenuItem(i->text));
      undo_menu->add(*mi);
      mi->show();
      mi->signal_activate().connect(SigC::bind(SigC::slot(
      		*(getChar().operator->()),
      		&VAbenteurer::Item::setUndo),i));
      ++count;
      if (count==10) break;
   }
   gtk_menu_popup(undo_menu->gobj(),0,0,&PosCalc,0,0,0);
}

void midgard_CG::on_redo_secondpressed(int mbutton)
{  VAbenteurer::Item::const_iterator i=getChar()->getUndo();
   unsigned count=0;
   if (undo_menu) delete undo_menu;
   undo_menu=new Gtk::Menu();
   ++i;
   while (i!=getChar()->end())
   {  Gtk::MenuItem *mi=manage(new Gtk::MenuItem(i->text));
      undo_menu->add(*mi);
      mi->show();
      mi->signal_activate().connect(SigC::bind(SigC::slot(
      		*getChar().operator->(),
      		&VAbenteurer::Item::setUndo),i));
      ++count;
      if (count==10) break;
      ++i;
   }
   gtk_menu_popup(undo_menu->gobj(),0,0,&PosCalc,0,0,0);
}

