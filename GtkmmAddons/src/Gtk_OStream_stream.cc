// $Id: Gtk_OStream_stream.cc,v 1.4 2002/01/21 17:16:59 christof Exp $
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

#define CLIST_COLUMNS 20

void Gtk::OStream::flush_stream(gpointer user_data,GtkDestroyNotify d)
{
    put(0);
    std::ostrstream::flush();
    (*handler_data.stream.os) << str();
    handler_data.stream.os->flush();
    freeze(0);
    seekp(0,std::ios::beg);
};
