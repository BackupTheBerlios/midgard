// $Id: customize_toolbars.cc,v 1.4 2002/05/09 17:13:51 christof Exp $
/*  Midgard Roleplaying Character Generator
 *  Copyright (C) 2001-2002 Christof Petig
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

#include "customize_toolbars.h"
#include <gtk--/toolbar.h>
#include <gtk--/label.h>
#include <gtk--/table.h>
#include <gtk--/pixmap.h>
#include <gtk--/button.h>
#include <gtk--/box.h>
#include <typeinfo>
// bin + container sind schon dabei

void Gtk::CustomizeToolbars(Gtk::Widget *w, bool show_icons, bool show_text)
{  if (Gtk::Button::isA(w))
   {  Gtk::Widget *child=dynamic_cast<Gtk::Bin*>(w)->get_child();
      if (Gtk::HBox::isA(child))
      {  Gtk::Box_Helpers::BoxList &ch=dynamic_cast<Gtk::Box*>(w)->children();
         Gtk::Box_Helpers::BoxList::iterator i=ch.begin(),j=i;
         if (i!=ch.end() && ++j!=ch.end())
         {  if (Gtk::Pixmap::isA((*i)->get_widget()) && Gtk::Label::isA((*j)->get_widget()))
            {  if (show_icons) (*i)->get_widget()->show();
               else (*i)->get_widget()->hide();
               if (show_text) (*j)->get_widget()->show();
               else (*j)->get_widget()->hide();
            }
         }
      }
   }
   else if (Gtk::Toolbar::isA(w))
   {  Gtk::Toolbar *tb=dynamic_cast<Gtk::Toolbar*>(w);
      tb->set_style(show_icons ? (show_text?GTK_TOOLBAR_BOTH:GTK_TOOLBAR_ICONS)
      		:GTK_TOOLBAR_TEXT);
      // recurse ?
   }
   else if (Gtk::Bin::isA(w))
   {  Gtk::Widget *child=dynamic_cast<Gtk::Bin*>(w)->get_child();
      CustomizeToolbars(child,show_icons,show_text);
   }
   else if (Gtk::Table::isA(w))
   {  Gtk::Table_Helpers::TableList &ch=dynamic_cast<Gtk::Table*>(w)->children();
      for (Gtk::Table_Helpers::TableList::const_iterator i=ch.begin();
      		i!=ch.end();++i)
         CustomizeToolbars(*i,show_icons,show_text);
   }
   else if (Gtk::Container::isA(w))
   {  // und nun ?
      cout << typeid(*w).name() << '\n';
   }
}
