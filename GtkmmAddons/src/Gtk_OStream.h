// $Id: Gtk_OStream.h,v 1.6 2001/12/19 10:58:15 christof Exp $
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
#include <iostream.h> // <iostream> for newer compilers
#include <strstream.h> // <strstream> for newer compilers
// <sstream> for upcoming compilers ;-)
#include <gtk--/menu.h>

namespace Gtk {
class List;
class OptionMenu;
class CList;
class Label;
};

class ostream;
#include <gtk--/combo.h>

#if (defined (__GNUC__) && __GNUC__ == 2 && __GNUC_MINOR__ < 8)
#define throw(away...)
#endif

// 2do: option-menu, Button, ... (everything which has Text on it)
// option-menu fertig MAT

namespace Gtk {

class OStream : public ostrstream
{
    private:
        void (OStream::*flush_impl)(gpointer user_data,GtkDestroyNotify d);
        void (OStream::*close_impl)();

        // append/overwrite (not yet implemented)
        int mode;

        // specific information
        struct data_clist { CList *widget;
                gint row,column; 
                bool freeze; };
        struct data_stream { ostream *os; };
        struct data_list { Gtk::List *widget; };
        struct data_optionmenu { Gtk::OptionMenu *widget; 
                Gtk::Menu *menu; };
        struct data_label { Label *widget; };
        union
        {  struct data_clist clist;
                struct data_stream stream;
                struct data_list list;
                struct data_optionmenu optionmenu;
                struct data_label label;
        } handler_data;

        void erase_OptionMenu();
        void flush_stream(gpointer user_data,GtkDestroyNotify d);
        void flush_CList(gpointer user_data,GtkDestroyNotify d);
        void flush_List(gpointer user_data,GtkDestroyNotify d);
        void flush_OptionMenu(gpointer user_data,GtkDestroyNotify d);
        void flush_Label(gpointer user_data,GtkDestroyNotify d);
        void close_OptionMenu();
    public:
        // add your own post flushing functionality (e.g. scrolling)
        SigC::Signal0<void> flushed;

        OStream()
                : flush_impl(&OStream::flush_stream), close_impl(0),
                        mode(ios::out)
        {
            handler_data.stream.os=&cout;
        }
        OStream(ostream *stream)
                : flush_impl(&OStream::flush_stream), close_impl(0),
                        mode(ios::out)
        {
            handler_data.stream.os=stream;
        }
        OStream(CList *cl,int _mode=(ios::out|ios::app), bool freeze=true) throw()
                : flush_impl(&OStream::flush_CList), close_impl(0),
                        mode(_mode)
        {
            handler_data.clist.widget=cl;
            handler_data.clist.row=handler_data.clist.column=-1;
            handler_data.clist.freeze=freeze;
        }
        OStream(CList *cl,gint _row,int _mode=(ios::out|ios::trunc), bool freeze=true)
        throw()
                : flush_impl(&OStream::flush_CList), close_impl(0),
                        mode(_mode)
        {
            handler_data.clist.widget=cl;
            handler_data.clist.row=_row;
            handler_data.clist.column=-1;
            handler_data.clist.freeze=freeze;
        }
        OStream(CList *cl,gint _row,gint _column,int _mode=(ios::out|ios::trunc), bool freeze=true)
        throw()
                : flush_impl(&OStream::flush_CList), close_impl(0),
                        mode(_mode)
        {
            handler_data.clist.widget=cl;
            handler_data.clist.row=_row;
            handler_data.clist.column=_column;
            handler_data.clist.freeze=freeze;
        }
        OStream(Gtk::List *l,int _mode=(ios::out|ios::app)) throw()
                : flush_impl(&OStream::flush_List), close_impl(0),
                        mode(_mode)
        {
            handler_data.list.widget=l;
        }
        OStream(Gtk::OptionMenu *o,int _mode=(ios::out|ios::trunc)) throw()
                : flush_impl(&OStream::flush_OptionMenu), 
                  close_impl(&OStream::close_OptionMenu),
                        mode(_mode)
        {   handler_data.optionmenu.widget=o;
            erase_OptionMenu();
        }
        OStream(Gtk::Combo *c,int _mode=(ios::out|ios::app)) throw()
                : flush_impl(&OStream::flush_List), close_impl(0),
                        mode(_mode)
        {
            handler_data.list.widget=c->get_list();
        }
        OStream(Label *l,int _mode=(ios::out|ios::trunc)) throw()
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
