// $Id: customize_toolbars.cc,v 1.28 2003/04/30 07:50:26 christof Exp $
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
#include <gtkmm/toolbar.h>
#include <gtkmm/label.h>
#include <gtkmm/table.h>
#include <gtkmm/image.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/notebook.h>
#include <gtkmm/eventbox.h>
#include <typeinfo>
// bin + container sind schon dabei
#include <iostream>
#include <ChoiceButton.h>

static bool hasOnlyPixmaps(Gtk::Box *w)
{  Gtk::Box_Helpers::BoxList &ch2=dynamic_cast<Gtk::Box*>(w)->children();
   Gtk::Box_Helpers::BoxList::iterator i2=ch2.begin();
   if (i2==ch2.end()) return false;
   for (;i2!=ch2.end();++i2)
   {  if (!(*i2).get_widget() || !dynamic_cast<Gtk::Image*>((*i2).get_widget())) 
         return false;
   }
   return true;
}

static void CustomizeBox(Gtk::Widget *child, bool show_icons, bool tab_text)
{  Gtk::Box_Helpers::BoxList &ch=dynamic_cast<Gtk::Box*>(child)->children();
   Gtk::Box_Helpers::BoxList::iterator i=ch.begin(),j=i;
   
   if (i!=ch.end() && ++j!=ch.end() && (*i).get_widget() && (*j).get_widget())
   {  Gtk::Widget *w1=(*i).get_widget();
      Gtk::Widget *w2=(*j).get_widget();
      
      if (dynamic_cast<Gtk::Image*>(w1) && dynamic_cast<Gtk::Label*>(w2))
      {  if (show_icons) w1->show();
         else w1->hide();
         if (tab_text) w2->show();
         else w2->hide();
      }
      else if (dynamic_cast<Gtk::Label*>(w1) && dynamic_cast<Gtk::Image*>(w2))
      {  if (show_icons) w2->show();
         else w2->hide();
         if (tab_text) w1->show();
         else w1->hide();
      }
      else if (dynamic_cast<Gtk::Box*>(w1) && dynamic_cast<Gtk::Label*>(w2))
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
{  if (dynamic_cast<Gtk::EventBox*>(w)) w=dynamic_cast<Gtk::Bin*>(w)->get_child();
   if (w && dynamic_cast<Gtk::Box*>(w)) CustomizeBox(w,show_icons,tab_text);
}

static void CustomizeButton(Gtk::Widget *w, bool show_icons, bool show_text)
{  Gtk::Widget *child=dynamic_cast<Gtk::Bin*>(w)->get_child();
   if (child && dynamic_cast<Gtk::Box*>(child)) CustomizeBox(child,show_icons,show_text);
}

void Gtk::CustomizeToolbars(Gtk::Widget *w, bool show_icons, bool show_text, bool tab_text)
{  // std::cout << '+' << typeid(*w).name() << '-' << w->get_name() << '\n';
   if (!show_icons && !show_text) show_text=true;
   if (!show_icons && !tab_text) tab_text=true;
   if (dynamic_cast<ManuProC::ChoiceButton*>(w))
   {  dynamic_cast<ManuProC::ChoiceButton*>(w)->set_style(show_icons,show_text);
   }
   else if (dynamic_cast<Gtk::Button*>(w))
   {  CustomizeButton(w, show_icons, show_text);
   }
   else if (dynamic_cast<Gtk::Toolbar*>(w))
   {  Gtk::Toolbar *tb=dynamic_cast<Gtk::Toolbar*>(w);
      tb->set_toolbar_style(show_icons ? (show_text?Gtk::TOOLBAR_BOTH:Gtk::TOOLBAR_ICONS)
      		:Gtk::TOOLBAR_TEXT);
      for (Gtk::Toolbar_Helpers::ToolList::iterator i=tb->tools().begin();i!=tb->tools().end();++i)
      {  if (i->get_type()==TOOLBAR_CHILD_WIDGET)
         {  CustomizeToolbars(i->get_widget(),show_icons,show_text,tab_text);
         }
      }
   }
   else if (dynamic_cast<Gtk::Bin*>(w))
   {  Gtk::Widget *child=dynamic_cast<Gtk::Bin*>(w)->get_child();
      if (child) CustomizeToolbars(child,show_icons,show_text,tab_text);
   }
   else if (dynamic_cast<Gtk::Table*>(w))
   {  
      Gtk::Table_Helpers::TableList &ch=dynamic_cast<Gtk::Table*>(w)->children();
      for (Gtk::Table_Helpers::TableList::const_iterator i=ch.begin();
      		i!=ch.end();++i)
         CustomizeToolbars((*i).get_widget(),show_icons,show_text,tab_text);
   }
   else if (dynamic_cast<Gtk::Notebook*>(w))
   {  Gtk::Notebook_Helpers::PageList &ch=dynamic_cast<Gtk::Notebook*>(w)->pages();
      Gtk::Notebook_Helpers::PageIterator e=ch.end();
      for (Gtk::Notebook_Helpers::PageIterator i=ch.begin();
      		i!=e;++i)
      {  CustomizeToolbars((*i).get_child(),show_icons,show_text,tab_text);
         CustomizeTab((*i).get_tab_label(),show_icons,tab_text);
      }
   }
   else if (dynamic_cast<Gtk::Container*>(w))
   {  // und nun ?
//      std::cout << typeid(*w).name() << '\n';
   }
}

// bail out once a widget is hidden

bool Gtk::rec_hide(Gtk::Widget *w)
{  if (!w) { std::cout << "NULL pointer\n"; return false; }
   if (!w->is_visible()) return false;
   // std::cout << '+' << typeid(*w).name() << '-' << w->get_name() << '\n';
   if (dynamic_cast<Gtk::Bin*>(w))
   {  Gtk::Widget *child=dynamic_cast<Gtk::Bin*>(w)->get_child();
      std::cout << " child of " << w->get_name() << '\n';
      if (!dynamic_cast<Gtk::Widget*>(child)) { w->hide(); return false; }
      if (child->is_visible() && rec_hide(child)) 
            return true;
   }
   else if (dynamic_cast<Gtk::Table*>(w))
   {  
      Gtk::Table_Helpers::TableList &ch=dynamic_cast<Gtk::Table*>(w)->children();
      for (Gtk::Table_Helpers::TableList::const_iterator i=ch.begin();
      		i!=ch.end();++i)
      {  if ((*i).get_widget()->is_visible() && rec_hide((*i).get_widget()))
            return true;
      }
   }
   else if (dynamic_cast<Gtk::Notebook*>(w))
   {  Gtk::Notebook_Helpers::PageList &ch=dynamic_cast<Gtk::Notebook*>(w)->pages();
      Gtk::Notebook_Helpers::PageIterator e=ch.end();
      for (Gtk::Notebook_Helpers::PageIterator i=ch.begin();
      		i!=e;++i)
      {  if ((*i).get_child()->is_visible() && rec_hide((*i).get_child()))
            return true;
      }
   }
   else if (dynamic_cast<Gtk::Container*>(w))
   {  // und nun ?
      // z.B. Paned
      std::cout << typeid(*w).name() << '\n';
   }
   std::cout << "hiding " << w->get_name() << '\n';
   w->hide();
   return true;
}
