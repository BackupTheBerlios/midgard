// $Id: Gtk_OStream.cc,v 1.1 2002/12/17 10:15:06 christof Exp $
/*  Gtk--addons: a collection of gtk-- addons
    Copyright (C) 2002  Adolf Petig GmbH. & Co. KG
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

void Gtk::OStreamBase::OStreamBase(flush_cbt f,close_cbt c, data_cbt d)
	   : flush_impl(f), close_impl(c), data_impl(d), mode(std::ios::out)
{  if (!data_impl) data_impl=&OStream::default_data;
}

std::ios::streamsize OStream::default_data(const char *s,streamsize n)
{  data.append(s,n);
   return n;
}
