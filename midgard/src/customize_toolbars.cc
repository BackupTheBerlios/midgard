// $Id: customize_toolbars.cc,v 1.17 2002/10/24 07:21:01 christof Exp $
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
#include <gtk--/notebook.h>
#include <gtk--/eventbox.h>
#include <typeinfo>
// bin + container sind schon dabei

static bool hasOnlyPixmaps(Gtk::Box *w)
{  Gtk::Box_Helpers::BoxList &ch2=dynamic_cast<Gtk::Box*>(w)->children();
   Gtk::Box_Helpers::BoxList::iterator i2=ch2.begin();
   if (i2==ch2.end()) return false;
   for (;i2!=ch2.end();++i2)
   {  if (!(*i2)->get_widget() || !Gtk::Pixmap::isA((*i2)->get_widget())) 
         return false;
   }
   return true;
}

static void CustomizeBox(Gtk::Widget *child, bool show_icons, bool tab_text)
{  Gtk::Box_Helpers::BoxList &ch=dynamic_cast<Gtk::Box*>(child)->children();
   Gtk::Box_Helpers::BoxList::iterator i=ch.begin(),j=i;
   
   if (i!=ch.end() && ++j!=ch.end() && (*i)->get_widget() && (*j)->get_widget())
   {  Gtk::Widget *w1=(*i)->get_widget();
      Gtk::Widget *w2=(*j)->get_widget();
      
      if (Gtk::Pixmap::isA(w1) && Gtk::Label::isA(w2))
      {  if (show_icons) w1->show();
         else w1->hide();
         if (tab_text) w2->show();
         else w2->hide();
      }
      else if (Gtk::Label::isA(w1) && Gtk::Pixmap::isA(w2))
      {  if (show_icons) w2->show();
         else w2->hide();
         if (tab_text) w1->show();
         else w1->hide();
      }
      else if (Gtk::Box::isA(w1) && Gtk::Label::isA(w2))
      {  if (hasOnlyPixmaps(dynamic_cast<Gtk::Box*>(w1))) 
         {  if (show_icons) w1->show();
            else w1->hide();
            if (tab_text) w2->show();
            else w2->hide();
         }
      }
   }
}

static void CustomizeTab(Gtk::Widget *w, bool show_icons, bool tab_text)
{  if (Gtk::EventBox::isA(w)) w=dynamic_cast<Gtk::Bin*>(w)->get_child();
   if (w && Gtk::Box::isA(w)) CustomizeBox(w,show_icons,tab_text);
}

static void CustomizeButton(Gtk::Widget *w, bool show_icons, bool show_text)
{  Gtk::Widget *child=dynamic_cast<Gtk::Bin*>(w)->get_child();
   if (child && Gtk::Box::isA(child)) CustomizeBox(child,show_icons,show_text);
}

void Gtk::CustomizeToolbars(Gtk::Widget *w, bool show_icons, bool show_text, bool tab_text)
{  // std::cout << '+' << typeid(*w).name() << '-' << w->get_name() << '\n';
   if (!show_icons && !show_text) show_text=true;
   if (!show_icons && !tab_text) tab_text=true;
   if (Gtk::Button::isA(w))
   {  CustomizeButton(w, show_icons, show_text);
   }
   else if (Gtk::Toolbar::isA(w))
   {  Gtk::Toolbar *tb=dynamic_cast<Gtk::Toolbar*>(w);
      tb->set_style(show_icons ? (show_text?GTK_TOOLBAR_BOTH:GTK_TOOLBAR_ICONS)
      		:GTK_TOOLBAR_TEXT);
      // recurse ?
   }
   else if (Gtk::Bin::isA(w))
   {  Gtk::Widget *child=dynamic_cast<Gtk::Bin*>(w)->get_child();
      if (child) CustomizeToolbars(child,show_icons,show_text,tab_text);
   }
   else if (Gtk::Table::isA(w))
   {  
#if 0   // a bug in gtkmm-1.2
      Gtk::Table_Helpers::TableList &ch=dynamic_cast<Gtk::Table*>(w)->children();
      for (Gtk::Table_Helpers::TableList::const_iterator i=ch.begin();
      		i!=ch.end();++i)
         CustomizeToolbars(*i,show_icons,show_text,tab_text);
#endif
      // G_ListWrap<GtkTableChild*>
      for (GList *std::list=GTK_TABLE(w->gtkobj())->children;std::list;
      		std::list=list->next)
      {  CustomizeToolbars(Gtk::wrap(((GtkTableChild*)(std::list->data))->widget),
      		show_icons,show_text,tab_text);
      }
   }
   else if (Gtk::Notebook::isA(w))
   {  Gtk::Notebook_Helpers::PageList &ch=dynamic_cast<Gtk::Notebook*>(w)->pages();
      for (Gtk::Notebook_Helpers::PageList::const_iterator i=ch.begin();
      		i!=ch.end();++i)
      {  CustomizeToolbars((*i)->get_child(),show_icons,show_text,tab_text);
         CustomizeTab((*i)->get_tab(),show_icons,tab_text);
      }
   }
   else if (Gtk::Container::isA(w))
   {  // und nun ?
//      std::cout << typeid(*w).name() << '\n';
   }
}
