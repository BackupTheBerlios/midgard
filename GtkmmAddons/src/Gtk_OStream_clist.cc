// $Id: Gtk_OStream_clist.cc,v 1.6 2002/01/21 17:16:59 christof Exp $
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
#include <cstring>
#include <gtk--/clist.h>

#define CLIST_COLUMNS 20

void Gtk::OStream::flush_CList(gpointer user_data,GtkDestroyNotify d)
{
    put(0);
    std::ostrstream::flush();
    char *linebuf=str();
    const char *nextline=linebuf;
    const char *columns[CLIST_COLUMNS];

    if (handler_data.clist.row!=-1 && handler_data.clist.column!=-1)
    {   // one column
        handler_data.clist.widget->set_text(handler_data.clist.row,
                                            handler_data.clist.column,linebuf);
        if (user_data)
            handler_data.clist.widget->set_row_data_full(handler_data.clist.row,user_data,d);
    }
    else if (handler_data.clist.row!=-1)
    {   // one row
        if (handler_data.clist.freeze) 
           handler_data.clist.widget->freeze();
        const char *nextcol=nextline;
        int numcol=0;
        for (char *nc=strchr(nextcol,'\t');nc
                ;nextcol=nc+1,nc=strchr(nextcol,'\t'),numcol++)
        {   nc[0]=0;
            handler_data.clist.widget
        	    	->set_text(handler_data.clist.row,numcol,nextcol);
        }
        if (nextcol[0])
        {   handler_data.clist.widget
	            	->set_text(handler_data.clist.row,numcol,nextcol);
        }
        // perhaps clean the rest of the line ???
        if (user_data)
            handler_data.clist.widget
            		->set_row_data_full(handler_data.clist.row,user_data,d);
        if (handler_data.clist.freeze) 
           handler_data.clist.widget->thaw();
    }
    else
    {
        if (handler_data.clist.freeze) 
           handler_data.clist.widget->freeze();
        for (char *nl=strchr(nextline,'\n');nl;nextline=nl+1,nl=strchr(nextline,'\n'))
        {
            nl[0]=0;
            const char *nextcol=nextline;
            int numcol=0;
            for (char *nc=strchr(nextcol,'\t');nc && numcol<CLIST_COLUMNS
                    ;nextcol=nc+1,nc=strchr(nextcol,'\t'),numcol++)
            {
                nc[0]=0;
                columns[numcol]=nextcol;
            }
            if (nextcol[0] && numcol<CLIST_COLUMNS)
            {
                columns[numcol++]=nextcol;
            }
            for (int i=numcol;i<CLIST_COLUMNS;i++) columns[i]="";
            int row=handler_data.clist.widget->append(columns);
            if (user_data) handler_data.clist.widget->set_row_data_full(row,user_data,d);
        }
        if (nextline[0])
        {
            const char *nextcol=nextline;
            int numcol=0;
            for (char *nc=strchr(nextcol,'\t');nc && numcol<CLIST_COLUMNS
                    ;nextcol=nc+1,nc=strchr(nextcol,'\t'),numcol++)
            {
                nc[0]=0;
                columns[numcol]=nextcol;
            }
            if (nextcol[0] && numcol<CLIST_COLUMNS)
            {
                columns[numcol++]=nextcol;
            }
            for (int i=numcol;i<CLIST_COLUMNS;i++) columns[i]="";
            int row=handler_data.clist.widget->append(columns);
            if (user_data) handler_data.clist.widget->set_row_data_full(row,user_data,d);
        }
        if (handler_data.clist.freeze) 
           handler_data.clist.widget->thaw();
    }
    freeze(0); // we don't need the buffer any more
    seekp(0,std::ios::beg);
}
