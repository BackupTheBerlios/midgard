/*  Gtk--addons: a collection of gtk-- addons
 *  Copyright (C) 2002 Adolf Petig GmbH & Co. KG, written by Christof Petig
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

// $Id: SelectMatching.h,v 1.2 2002/05/16 14:41:46 christof Exp $

#include <gtk--/menu.h>
#include <gtk--/clist.h>
#include <gtk--/optionmenu.h>
#include <gtk--/menuitem.h>

namespace Gtk
{
namespace Menu_Helpers
{

// returns true on match
template <class T>
 bool SelectMatching(Gtk::OptionMenu &om, const T &val)
{  Gtk::Menu *m=om.get_menu();
   guint index=0;
   for (MenuList::const_iterator i=m->items().begin();i!=m->items().end();++i,++index)
      if ((*i)->get_user_data()==val)
      {  om.set_history(index);
         return true;
      }
   return false;
}

}

namespace CList_Helpers
{

// returns true on match
template <class T>
 bool SelectMatching(Gtk::CList &cl, const T &val)
{  for (RowList::iterator i=cl->rows().begin();i!=cl->rows().end();++i)
      if (i->get_data()==val)
      {  i->select();
         return true;
      }
   return false;
}

}
}
