// $Id: Gtk_OStream.h,v 1.8 2002/09/24 15:17:31 christof Exp $
/*  Gtk--addons: a collection of gtk-- addons
    Copyright (C) 1998-2002  Adolf Petig GmbH. & Co. KG
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
#include <callbackbuf.h> 

namespace Gtk {
class OptionMenu;
class Label;
class Menu;
class TreeView;
};

// 2do: 

namespace Gtk {

class OStreamBase : public std::ostream
{protected:
	typedef void (OStream::*flush_cbt)(gpointer user_data,GtkDestroyNotify d);
        typedef void (OStream::*close_cbt)();
        typedef streamsize (OStream::*data_cbt)(const char*,streamsize);
        typedef void (OStream::*line_cbt)(const std::string &line);
        flush_cbt flush_impl;
        close_cbt close_impl;
        data_cbt data_impl;
        line_cbt line_impl;
        
        std::string data;
//        std::ios::openmode mode; // is this interesting ?
        SigC::Signal0<void> flushed;
public:
	OStreamBase(flush_cbt f,close_cbt c=0, data_cbt d=0,line_cbt=0);
	OStreamBase(line_cbt l);
	OStreamBase(data_cbt d);
        ~OStreamBase(void);
        // this routine does the hard work
        void flush(gpointer user_data=0,GtkDestroyNotify d=0);
        
        SigC::Signal0<void> &signal_flushed() { return flushed; }
};

class OStream : public OStreamBase
{       // specific information
        struct data_stream { std::ostream *os; };
        struct data_optionmenu { Gtk::OptionMenu *widget; Gtk::Menu *menu; };
        struct data_label { Label *widget; };
        struct data_treeview { Gtk::TreeView *view; };
        union
        {  	struct data_stream stream;
                struct data_optionmenu optionmenu;
                struct data_label label;
                struct data_treeview treeview;
        } handler_data;

        streamsize default_data(const char *,streamsize);
        void erase_OptionMenu(openmode m);
        void erase_Label(openmode m);
        void erase_TreeView(openmode m);
        streamsize data_stream(const char *,streamsize);
        streamsize data_Label(const char *,streamsize);
//        void flush_stream(gpointer user_data,GtkDestroyNotify d);
        void flush_OptionMenu(gpointer user_data,GtkDestroyNotify d);
        void flush_Label(gpointer user_data,GtkDestroyNotify d);
        void flush_TreeView(gpointer user_data,GtkDestroyNotify d);
        void close_OptionMenu();
    public:
        // add your own post flushing functionality (e.g. scrolling)

        OStream() : OStreamBase(&OStream::data_stream)
        {   handler_data.stream.os=&std::cout;
        }
        OStream(std::ostream *stream) : OStreamBase(&OStream::data_stream)
        {   handler_data.stream.os=stream;
        }
	OStream(Gtk::TreeView *tv,openmode mode=(std::ios::out|std::ios::trunc))
		: OStreamBase(&OStream::flush_TreeView)
	{   handler_data.treeview.view=tv;
	    erase_TreeView(mode);
	}
        OStream(Gtk::OptionMenu *o,openmode mode=(std::ios::out|std::ios::trunc)) throw()
                : OStreamBase(&OStream::flush_OptionMenu, &OStream::close_OptionMenu)
        {   handler_data.optionmenu.widget=o;
            erase_OptionMenu(mode);
        }
        OStream(Gtk::Label *l,openmode mode=(std::ios::out|std::ios::trunc)) throw()
                : OStreamBase(&OStream::data_Label)
        {   handler_data.label.widget=l;
            erase_Label(mode)
        }
};

};

#endif
