// $Id: Gtk_OStream.cc,v 1.3 2002/12/18 09:00:39 christof Exp $
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
#include <cassert>

Gtk::OStreamBase::OStreamBase(line_cbt l,close_cbt c)
	: flush_impl(0), close_impl(c), data_cbt(&OStream::default_data),
		line_impl(l)
{
}

Gtk::OStreamBase::OStreamBase(data_cbt d)
	: flush_impl(0), close_impl(0), data_cbt(d), line_impl(0)
{
}

#if 0
Gtk::OStreamBase::OStreamBase(flush_cbt f,close_cbt c, data_cbt d, line_cbt l)
	   : flush_impl(f), close_impl(c), data_impl(d), line_impl(l)
{  if (!data_impl) data_impl=&OStream::default_data;
}
#endif

std::ios::streamsize OStream::default_data(const char *s,streamsize n)
{  data.append(s,n);
   if (line_impl && memchr(s,'\n',n))
   {  std::string::size_type end=data.find('\n');
      (*line_impl)(data.substr(0,end);
      data.erase(0,end!=std::string::npos?end+1:end);
   }
   return n;
}

Gtk::OStreamBase::~OStreamBase(void)
{   flush();
    if (close_impl) (this->*close_impl)();
}

void Gtk::OStreamBase::flush(gpointer _user_data=0,GtkDestroyNotify d=0)
{  if (_user_data || d)
   {  user_data=_user_data; notify=d; }

   if (flush_impl) (this->*flush_impl)();
   else if (line_impl && data_impl==&OStream::default_data && !data.empty())
      (*line_impl)(data);
   flushed();
}
