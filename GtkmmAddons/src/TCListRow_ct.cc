// $Id: TCListRow_ct.cc,v 1.7 2002/01/21 17:16:59 christof Exp $
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
#include <iterator>
#include <cstdio>

//#define NE_OPERATOR_IN_CTREE

#ifndef NE_OPERATOR_IN_CTREE
// missing in stock gtk-- !!!

class myCell : Gtk::CTree::Cell
{public:
	myCell(const Gtk::CTree::Cell &c) : Gtk::CTree::Cell(c) {}
	bool operator!=(const myCell &b) const 
	{ return column_!=b.column_; }
};

static bool operator!=(const Gtk::CTree::Row::const_iterator &a,const Gtk::CTree::Row::const_iterator &b)
{  return myCell(*a)!=*b;
}
#endif

std::ostream &operator<<(std::ostream &out,const TCListRow_ct &lr)
{   out << "TCListRow_ct @" << &lr << " " << (const_cast<Gtk::CTree::Row&>(lr.item).is_expanded()?"":"!") << "exp";
    out << " exp_col=" << lr.expanding_column << " " << lr.children.size();
    out << " children: ";
    for (Gtk::CTree::Row::const_iterator i=lr.item.begin();i!=lr.item.end();++i)
    {
        out << "\"" << i->get_text() << "\" ";
    }
    out << "\n";
#ifdef DEBUG
    for (TCListRow_ct::const_iterator i=lr.begin();i!=lr.end();i++)
        out << "\t" << *i;
#endif
    return out;
}

#if 0
void TCListRow_ct::reparent_children(TCListRow_ct &newparent)
{
    if (!root.detached) collapse_imp();
    if (!root.detached && newparent.expanded) newparent.collapse_imp();
    back_insert_iterator<std::vector<TCListRow_ct*> > ii(newparent.children);
    copy(children.begin(),children.end(),ii);
    children.erase(children.begin(),children.end());
    if (!root.detached && newparent.expanded) newparent.expand_imp();
}

int TCListRow_ct::visible_size() const
{  if (root.detached) return 0;
    int res=1;
    if (expanded)
    {
        for (const_iterator i=begin();i!=end();i++)
            res+=(*i).expanded ? (*i).visible_size() : 1;
        // this '?:' avoids one depth of recursion
    }
    return res;
}
#endif

void TCListRow_ct::set_text(guint column,const std::string &text)
{  item[column].set_text(text);
}

#if 0
class myRow : public Gtk::CTree::Row
{public:
	myRow(const Gtk::CTree::Row &rw) : Gtk::CTree::Row(rw) {}
	GtkCTree *Tree() const { return tree_; }
	GtkCTreeNode *Node() const { return node_; }
};

std::ostream &operator <<(std::ostream &os,const myRow &mr)
{  return os << '(' << mr.Tree() << ')' << mr.Node();
}
#endif

void TCListRow_ct::construct(Gtk::CTree::RowList rlist,const Gtk::CTree::RowList::iterator &next,const Gtk::CTree::Element &elem, gint exp_column, bool expand)
{  item=*(rlist.insert(next,elem));
   expanding_column=exp_column;
   item.set_data(this,&DestroyNotify);
}

//#define DEFAULT_PICTURES

void TCListRow_ct::construct(Gtk::CTree::RowList rlist,const Gtk::CTree::RowList::iterator &next,const std::vector <std::string> &cols, gint exp_column, bool expand)
{  construct(rlist,next,Gtk::CTree::Element(cols,
#ifndef DEFAULT_PICTURES
		root.getPlus()->pmap(),root.getPlus()->mask(),
		root.getMinus()->pmap(),root.getMinus()->mask(),
#endif		
		false,expand),exp_column,expand);
}

void TCListRow_ct::construct(Gtk::CTree::RowList rlist,const Gtk::CTree::RowList::iterator &next,const char **cols, gint exp_column, bool expand)
{  construct(rlist,next,Gtk::CTree::Element(Gtk::SArray_Helpers::SArray(cols,cols+GTK_CLIST(root.gtkobj())->columns),
#ifndef DEFAULT_PICTURES
		root.getPlus()->pmap(),root.getPlus()->mask(),
		root.getMinus()->pmap(),root.getMinus()->mask(),
#endif		
		false,expand),exp_column,expand);
   // or perhaps root.columns.size()
}

// perhaps blockable for reparenting?
void TCListRow_ct::DestroyNotify(gpointer data)
{  // destroy childen ???
   TCListRow_ct *_this((TCListRow_ct *)data);
   _this->children.clear();
   if (_this->parent) _this->parent->_erase(_this);
   else _this->root._erase(_this);
   _this->root.delete_user(_this->user_data);
}

void TCListRow_ct::_erase(const TCListRow *ch)
{  children_t::iterator i(::find(children.begin(),children.end(),const_cast<TCListRow*>(ch)));
   if (i==children.end()) std::cerr << "TCListRow_ct::_erase error\n";
   else children.erase(i);
}

#if 0        
void TCListRow_ct::delete_imp()
{
#ifdef DEBUG
            std::cout << "delete_imp @" << this << "\n";
#endif
            if (!children.empty()) root.erase(begin(),end());
            root.delete_user(user_data);
#ifdef DEBUG
            std::cout << "!delete_imp@" << this << "\n";
#endif
}
#endif        

#warning kill the old API!
TCListRow_ct *TCListRow_ct::push_back(const Gtk::SArray &text,gint exp_column,bool expand)
{  TCListRow_ct *res=new TCListRow_ct(root);
   res->construct(item.subtree(),item.subtree().end(),(const char **)text,exp_column,expand);
   return res;
}
      
TCListRow_ct *TCList::push_back(const Gtk::SArray &text,gint exp_column,bool expand)
{  TCListRow_ct *res=new TCListRow_ct(*this);
   res->construct(rows(),rows().end(),(const char **)text,exp_column,expand);
   return res;
}
            
            