// $Id: TCList_ct.cc,v 1.2 2001/06/27 07:59:59 christof Exp $
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

#include "TCList_ct.h"

TCList_ct::TCList_ct(const std::vector <std::string> title,int tree_column)
        : Gtk::CTree(title, tree_column),
          minus(0), plus(0), trace(false)
{
   set_line_style(GTK_CTREE_LINES_SOLID); // DOTTED, TABBED
   set_expander_style(GTK_CTREE_EXPANDER_SQUARE); // CIRCULAR
   set_indent(6);
}

TCList_ct::TCList_ct(gint numcol, const gchar**title, int tree_column)
        : Gtk::CTree(Gtk::SArray(title,title+numcol),tree_column),
          minus(0), plus(0), trace(false)
{
   set_line_style(GTK_CTREE_LINES_SOLID); // DOTTED, TABBED
#ifdef DEFAULT_PIXMAPS
   set_expander_style(GTK_CTREE_EXPANDER_SQUARE); // CIRCULAR
#else
   set_expander_style(GTK_CTREE_EXPANDER_NONE);
#endif
   set_indent(6);
}

void TCList_ct::erase(iterator position)
{
#ifdef DEBUG
    if (trace) std::cout << "erase " << position << "\n";
#endif
    rows().remove((*position).item); // hmmm what about deep ones?
}

void TCList_ct::erase(iterator b,iterator e)
{  // ein reverse_iterator geht nicht, da man einen rev_it nicht in einen
    // iterator wandeln kann !!! und reverse_iterator keine get_index()
    // Methode hat

    // this is like a reverse iteration ...
    // horrible !!! any big change within iterators will break this routine !!!
    if (b==e) return;
    iterator act=e;
    do erase(--act); while(act!=b);
}

std::ostream &operator<<(std::ostream &o,const std::vector<TCListRow_ct*> &v)
{
    int x=0;
    for (std::vector<TCListRow_ct*>::const_iterator i=v.begin();
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

#include "red_plus.xpm"
Picture2 *TCList_ct::_defaultplus;

const Picture2 *TCList_ct::_getPlus() const
{  if (!plus)
    {
        if (!_defaultplus)
            const_cast<TCList_ct&>(*this)._defaultplus=new Picture2(red_plus);
        const_cast<TCList_ct&>(*this).plus=_defaultplus;
    }
    return plus;
}

#include "green_minus.xpm"

Picture2 *TCList_ct::_defaultminus;

const Picture2 *TCList_ct::_getMinus() const
{  if (!minus)
    {  if (!_defaultminus)
          const_cast<TCList_ct&>(*this)._defaultminus=new Picture2(green_minus);
        const_cast<TCList_ct&>(*this).minus=_defaultminus;
    }
    return minus;
}

std::ostream &shl_rec(std::ostream &o, const TCListRow_ct::const_iterator &b, const TCListRow_ct::const_iterator &e)
{
    int x=0;
    for (TCListRow_ct::const_iterator i=b;
            i!=e;i++)
    {
        o << x++ << "'";
        o << &*i << "{";
        shl_rec(o,(*i).begin(),(*i).end());
        o << "} ";
    }
    return o;
}

std::ostream &operator << (std::ostream &o, const TCList_ct &tcl)
{
    int x=0;
    for (TCListRow_ct::const_iterator i=tcl.begin();i!=tcl.end();i++)
    {
        o << x++ << "'";
        o << *i << " ";
    }
    return shl_rec(o,tcl.begin(),tcl.end());
}

#ifdef DEBUG
class myRow : public Gtk::CTree::Row
{public:
	myRow(const Gtk::CTree::Row &rw) : Gtk::CTree::Row(rw) {}
	GtkCTree *Tree() const { return tree_; }
	GtkCTreeNode *Node() const { return node_; }
};

void TCList_ct::debug() const
{  std::cout << (void*)(gtkobj()) << ": ";
   for (Gtk::CTree::RowList::const_iterator i=rows().begin();i!=rows().end();++i)
   {  myRow m(*i);
      if (m.Tree()!=gtkobj()) std::cout << '*';
      std::cout << m.Node() << ' ';
   }
   std::cout << '\n';
}
#endif

void TCList_ct::_erase(const TCListRow *ch)
{  children_t::iterator i(::find(children.begin(),children.end(),const_cast<TCListRow*>(ch)));
   if (i==children.end()) std::cerr << "TCList_ct::_erase error\n";
   else children.erase(i);
}
