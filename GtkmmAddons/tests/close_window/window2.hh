/*  Gtk--addons: a collection of gtk-- addons
 *  Copyright (C) 2001 Adolf Petig GmbH & Co. KG, written by Christof Petig
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

// generated 1999/11/19 14:05:29 MET by christof@petig.petig.de
// using glademm V0.5.4a
//
// newer (non customized) versions of this file go to window2.hh_glade

// you might replace
//    class Foo : public Foo_glade { ... };
// by
//    typedef Foo_glade Foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW2_HH
#  include "window2_glade.hh"
#  define _WINDOW2_HH
class window2 : public window2_glade
{   
        
        friend class window2_glade;
        void on_button2_clicked();
        gint on_window2_delete_event(GdkEventAny *ev);
public:
	window2() {}
        ~window2();
};

#endif
