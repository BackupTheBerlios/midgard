/* $Id: clist.cc,v 1.3 2001/01/12 12:36:36 christof Exp $ */
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

#include <gtk--/clist.h>
#include <gtk--/window.h>
#include <gtk--/main.h>
#include <iostream.h>

class testwindow : public Gtk::Window
{
        Gtk::CList *liste;
        /*   Gtk::ScrolledWindow listwin; */
    public:
    	void show_hide_col(int column)
    	{  liste->set_column_visibility(column,false);
//    	   liste->refresh();
    	   return;
    	}
        testwindow()
        {
            const gchar *title[5]={ "eins","zwei","drei","vier","fnf" };
            const gchar *line[5]={ "1","2","3","4","5" };
            liste = new Gtk::CList(5,title);
            add(*liste);
            for (int i=0;i<5;i++)
            {
                liste->set_column_width(i,40);
            }
            liste->append(line);
            liste->show();
            liste->column_titles_active();
            liste->click_column.connect(SigC::slot(this,&testwindow::show_hide_col));
        }
        gint delete_event_impl(GdkEventAny *)
        {
            Gtk::Main::instance()->quit();
            return 0;
        }
};


int main( int argc, char **argv )
{
    Gtk::Main m(argc, argv );
    testwindow w;

    w.set_usize( 220,200 );
    w.show();

    m.run();
    return 0;
}
