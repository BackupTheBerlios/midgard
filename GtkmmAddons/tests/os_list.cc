// $Id: os_list.cc,v 1.2 2001/01/12 12:36:36 christof Exp $
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

#include <gtk--/main.h>
#include <gtk--/window.h>
#include <Gtk_OStream.h>

class myWindow : public Gtk::Window
{	Gtk::List l;
public:
	myWindow()
	{	add(l);
		l.show();
		l.set_usize(100,100);
	}
	Gtk::List &List()
	{  return l; }
};

int main(int argc,char **argv)
{  Gtk::Main m(argc, argv );
   myWindow w;
   w.show();
   {  Gtk::OStream os(&w.List());
      os << "test";
   }
   m.run();
   return 0;
}
