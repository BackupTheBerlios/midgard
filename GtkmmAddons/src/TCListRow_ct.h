// $Id: TCListRow_ct.h,v 1.5 2002/03/20 07:49:18 christof Exp $
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

#ifndef GTK_TCLISTROW_CT_H
#define GTK_TCLISTROW_CT_H
#include <vector>
#include <string>
#include <iterator>
#include <iostream>
#include <algo.h>

class TCListRow_ct;

#ifndef GTK_TCLIST_H
#  include "TCList_ct.h"
#endif

class TCListRow_ct : public TCListRow_ct_API
{
    private:
        friend class TCList_ct;
        friend class iterator;

        TCList_ct &root;
        TCListRow_ct *parent;
        Gtk::CTree::Row item;
        gpointer user_data;

	static void DestroyNotify(gpointer data);
	void _erase(const TCListRow_ct *ct);

        TCListRow_ct(TCList_ct &r) : root(r)
        {}

public:        	
        virtual TCListRow_ct *push_back(const Gtk::SArray &text,gint exp_column=-1,bool expand=false)
        {  return insert(end(),text,exp_column,expand); }
        virtual TCListRow_ct *insert(iterator i,const Gtk::SArray &text,gint exp_column=-1,bool expand=false);

        virtual ~TCListRow_ct()
        {
//            delete_imp();
#ifdef DEBUG
            std::cout << this << " dtor end\n";
#endif
        }
        /// return iterator to first child
        iterator begin()
        {
            return TCList_ct::iterator(children,0,&root,this);
        }
        /// return past the end iterator
        iterator end()
        {
            return TCList_ct::iterator(children,children.size(),&root,this);
        }
        /// return iterator to first child
        const_iterator begin() const
    {  return TCList_ct::const_iterator(children,0); }
        /// return past the end iterator
        const_iterator end() const
    {  return TCList_ct::const_iterator(children,children.size()); }
        /// whether this Node has no children
        bool empty() const
    {  return children.empty(); }
        /// number of children
        int size() const
    {  return children.size(); }

        /// specify the expanding column (the one with the (+)-sign)
        void set_expanding_column(gint col)
        {  expanding_column=col; }
        /// return the expanding column
        gint get_expanding_column() const
    {  return expanding_column; }

        /// add an hook for your data
        void set_user_data(gpointer x)
        {   user_data=x;
        }
        /// return your data
        gpointer get_user_data() const
        {  return user_data;
        }
        /// expand this subtree
        void expand()
        {  item.expand();
        }
        /// collapse this subtree
        void collapse()
        {  item.collapse();
        }
        /// flip expansion of this subtree
        void toggle_expansion()
        {  item.toggle_expansion(); }
        
        /// return contents (text) of this node
        const std::vector <std::string> &get_columns() const;

        /// reparent children to parent (waaaaas bitte???)
        void reparent_children(TCListRow_ct &newparent);

        /// find iterator to child
        iterator find(const TCListRow_ct &value)
        {
            return ::find(begin(),end(),value);
        }

        /// visible_size of this subtree
        int visible_size() const;

        /// relabel column
        void set_text(guint column, const std::string &text);
        const std::string get_text(guint column) const;

        bool operator==(const TCListRow_ct &value) const { return this==&value; }

        /** For performance reasons cloning Pictures is not done.
            You really need a picture _ONCE_? You're kidding! */
        void setPicture(int column,const Picture2 &pic);

        friend std::ostream &operator<<(std::ostream &out,const TCListRow_ct &lr);
};

/// debug contents of this node
std::ostream &operator<<(std::ostream &out,const TCListRow_ct &lr);
std::ostream &shl_rec(std::ostream &o, const TCListRow_ct::const_iterator &b, const TCListRow_ct::const_iterator &e);

#endif
