// $Id: Gtk_OStream_list.cc,v 1.5 2002/01/21 17:16:59 christof Exp $
/*  Gtk--addons: a collection of gtk-- addons
    Copyright (C) 1998  Adolf Petig GmbH. & Co. KG
    Developed by Christof Petig <christof.petig@wtal.de>
 
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.
 
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.
 
    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "Gtk_OStream.h"
#include <gtk--/list.h>
#include <gtk--/listitem.h>
#include <cstring>

void Gtk::OStream::flush_List(gpointer user_data,GtkDestroyNotify d)
{
    put(0);
    std::ostrstream::flush();
    char *linebuf=str();

    // if (mode&std::ios::trunc) delete existing lines
    const char *nextline=linebuf;
    Gtk::ListItem *item;
    for (char *nl=strchr(nextline,'\n');nl;nextline=nl+1,nl=strchr(nextline,'\n'))
    {
        nl[0]=0;
        item=manage(new Gtk::ListItem(nextline));
        item->show();
        handler_data.list.widget->add(*item);
        if (user_data) 
        {  item->set_user_data(user_data);
           item->set_data_full("user_data",user_data,d);
        }
    }
    if (nextline[0])
    {
        item=manage(new Gtk::ListItem(nextline));
        assert(Gtk::List::isA(handler_data.list.widget));
        item->show();
        handler_data.list.widget->add(*item);
        if (user_data) 
        {  item->set_user_data(user_data);
           item->set_data_full("user_data",user_data,d);
        }
    }
    freeze(0); // we don't need the buffer any more
    seekp(0,std::ios::beg);
}
