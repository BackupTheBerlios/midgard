// $Id: Gtk_OStream.h,v 1.8 2002/09/24 15:17:31 christof Exp $
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

#ifndef GTKMM_OSTREAM_H
#define GTKMM_OSTREAM_H
#include <iostream> // <iostream> for newer compilers
#include <strstream> // <strstream> for newer compilers
// <sstream> for upcoming compilers ;-)
#include <gtkmm/menu.h>

namespace Gtk {
class OptionMenu;
class Label;
};

// 2do: option-menu, Button, ... (everything which has Text on it)
// option-menu fertig MAT

namespace Gtk {

class OStream : public std::ostrstream
{
    private:
        void (OStream::*flush_impl)(gpointer user_data,GtkDestroyNotify d);
        void (OStream::*close_impl)();

        // append/overwrite (not yet implemented)
        int mode;

        // specific information
        struct data_stream { std::ostream *os; };
        struct data_optionmenu { Gtk::OptionMenu *widget; 
                Gtk::Menu *menu; };
        struct data_label { Label *widget; };
        union
        {  
                struct data_stream stream;
                struct data_optionmenu optionmenu;
                struct data_label label;
        } handler_data;

        void erase_OptionMenu();
        void flush_stream(gpointer user_data,GtkDestroyNotify d);
        void flush_OptionMenu(gpointer user_data,GtkDestroyNotify d);
        void flush_Label(gpointer user_data,GtkDestroyNotify d);
        void close_OptionMenu();
    public:
        // add your own post flushing functionality (e.g. scrolling)
        SigC::Signal0<void> flushed;

        OStream()
                : flush_impl(&OStream::flush_stream), close_impl(0),
                        mode(std::ios::out)
        {
            handler_data.stream.os=&std::cout;
        }
        OStream(std::ostream *stream)
                : flush_impl(&OStream::flush_stream), close_impl(0),
                        mode(std::ios::out)
        {
            handler_data.stream.os=stream;
        }
        OStream(Gtk::OptionMenu *o,int _mode=(std::ios::out|std::ios::trunc)) throw()
                : flush_impl(&OStream::flush_OptionMenu), 
                  close_impl(&OStream::close_OptionMenu),
                        mode(_mode)
        {   handler_data.optionmenu.widget=o;
            erase_OptionMenu();
        }
        OStream(Label *l,int _mode=(std::ios::out|std::ios::trunc)) throw()
                : flush_impl(&OStream::flush_Label), close_impl(0),
                        mode(_mode)
        {
            handler_data.label.widget=l;
        }
        ~OStream(void)
        {
            flush();
            if (close_impl) (this->*close_impl)();
        }
        // this routine does the hard work
        void flush(gpointer user_data=0,GtkDestroyNotify d=0)
        {
            (this->*flush_impl)(user_data,d);
            flushed();
        }
};

};

#endif
