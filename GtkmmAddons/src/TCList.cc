// $Id: TCList.cc,v 1.8 2001/11/15 15:19:10 christof Exp $
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

#include "TCList.h"

TCList::TCList(const std::vector <std::string> title)
        : Gtk::CList(title.size()), number_of_columns(title.size()),
          minus(0), plus(0), trace(false)
{   expanded=true; // detached(false),
    for (guint i=0;i<title.size();i++)
        set_column_title(i,title[i].c_str());
    column_titles_show();
    select_row.connect(SigC::slot(this,&TCList::select_row_imp));
}

TCList::TCList(gint numcol, const gchar**title)
        : Gtk::CList(numcol,title), number_of_columns(numcol),
          minus(0), plus(0), trace(false)
{   expanded=true; // detached(false),
    select_row.connect(SigC::slot(this,&TCList::select_row_imp));
}

void TCList::select_row_imp(gint _row,gint column,GdkEvent *event)
{  TCListRow *child=(TCListRow*)get_row_data(_row);
    if (column!=-1 && column==child->get_expanding_column())
    {
        child->toggle_expansion();
        row(_row).unselect();
    }
}

void TCList::erase(iterator position)
{
#ifdef DEBUG
    if (trace) std::cout << "erase " << position << "\n";
#endif
    TCListRow &item=*position;
#ifdef DEBUG
    if (trace)
    {
        std::cout.flush();
        std::cout << "lineno ";
        std::cout << item;
        std::cout.flush();
    }
#endif
    gint lineno=item.get_lineno();
#ifdef DEBUG
    if (trace) std::cout << lineno << "\n";
#endif
    if (lineno!=-1)
    {
        remove_row(lineno);
    }
    position.erase();
    delete &item;
#ifdef DEBUG
    if (trace)
    {
        std::cout << "leaving erase " << position << "\n";
        std::cout.flush();
    }
#endif
}

void TCList::erase(iterator b,iterator e)
{  // ein reverse_iterator geht nicht, da man einen rev_it nicht in einen
    // iterator wandeln kann !!! und reverse_iterator keine get_index()
    // Methode hat

    // this is like a reverse iteration ...
    // horrible !!! any big change within iterators will break this routine !!!
    if (b==e) return;
    iterator act=e;
    do erase(--act); while(act!=b);
}

std::ostream &operator<<(std::ostream &o,const TCListRow_baseiterator &it)
{
    o << (void*)&it.current_vector << ":" << it.current_index
    << "/" << it.current_vector->size();
#ifdef DEBUG
    o << " [" << (*it.current_vector) << "]";
#endif
    return o;
}

std::ostream &operator<<(std::ostream &o,const std::vector<TCListRow*> &v)
{
    int x=0;
    for (std::vector<TCListRow*>::const_iterator i=v.begin();
            i!=v.end();i++)
    {
        o << x++ << "'";
        o << *i << " ";
    }
#ifdef DEBUG
    o.flush();
#endif
    return o;
}

void TCList::collapse_imp() // detach_from_clist()
{   if (trace) std::cout << "collapsing/detaching (old state " << expanded << ")\n";
    freeze();
    while(get_row_data(0)!=0)
        remove_row(0);
    thaw();
}

void TCList::expand_imp() // attach_to_clist()
{   if (trace) std::cout << "expanding/attaching (old state " << expanded << ") " << size() <<" children\n";
    freeze();
    for (iterator i=begin();i!=end();++i)
        (*i).append_imp();
    thaw();
}

#include "red_plus.xpm"
Picture2 *TCList::_defaultplus;

const Picture2 *TCList::getPlus()
{
    if (!plus)
    {
        if (!_defaultplus)
        {
            _defaultplus=new Picture2(red_plus);
        }
        plus=_defaultplus;
    }
    return plus;
}

#include "green_minus.xpm"
Picture2 *TCList::_defaultminus;

const Picture2 *TCList::getMinus()
{
    if (!minus)
    {
        if (!_defaultminus)
        {   _defaultminus=new Picture2(green_minus);
        }
        minus=_defaultminus;
    }
    return minus;
}

std::ostream &shl_rec(std::ostream &o, const TCListRow::const_iterator &b, const TCListRow::const_iterator &e)
{
    int x=0;
    for (TCListRow::const_iterator i=b;
            i!=e;i++)
    {
        o << x++ << "'";
        o << &*i << "{";
        shl_rec(o,(*i).begin(),(*i).end());
        o << "} ";
    }
    return o;
}

std::ostream &operator << (std::ostream &o, const TCList &tcl)
{
    int x=0;
    for (TCListRow::const_iterator i=tcl.begin();i!=tcl.end();i++)
    {
        o << x++ << "'";
        o << *i << " ";
    }
    return shl_rec(o,tcl.begin(),tcl.end());
}

TCListRow_iterator::TCListRow_iterator(TCListRow_API *parent,TCListRow *tclr)
	: TCListRow_baseiterator(parent->children,0), root(&tclr->root), row(tclr)
{  for (std::vector<TCListRow*>::const_iterator i=current_vector->begin();
		i!=current_vector->end();++i,++current_index)
      if ((*i)==tclr) return;
}
