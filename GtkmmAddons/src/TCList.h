// $Id: TCList.h,v 1.11 2001/10/26 08:29:59 christof Exp $
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

#ifndef GTK_TCLIST_H
#define GTK_TCLIST_H
#include <gtk--/clist.h>
#include <vector>
#include <string>
#include <iterator>
#include <iostream>
#include <cassert>
#include <Picture2.h>
#include <gtk/gtkfeatures.h>

#include <TCList_iterator.h>

class TCListRow_API
{protected:
        std::vector <TCListRow *> children;
        bool expanded;
        gint expanding_column;
        
        virtual void expand_imp()=0; // show children in list, do not touch expanded
        virtual void collapse_imp()=0; // hide children from list, do not touch expanded
        friend class TCListRow;
	friend class TCList;
	friend class TCListRow_iterator;

public:
        typedef TCListRow_iterator iterator;
        typedef TCListRow_constiterator const_iterator;
        typedef TCListRow_iterator::reverse_iterator reverse_iterator;

        virtual TCListRow *push_back(const Gtk::SArray &text,gint exp_column=-1,bool expand=false)=0;
        virtual TCListRow *insert(iterator i,const Gtk::SArray &text,gint exp_column=-1,bool expand=false)=0;
        
        virtual iterator begin()=0;
        virtual iterator end()=0;
        virtual const_iterator begin() const=0;
        virtual const_iterator end() const=0;
        /// number of children
        int size() const
        {  return children.size(); }
        /// whether this Node has no children
        bool empty() const
	{  return children.empty(); }
	virtual void set_user_data(gpointer x) = 0;
	virtual gpointer get_user_data() const = 0;
        /// reparent children to parent
        virtual void reparent_children(TCListRow_API &newparent)=0;
        /// reparent us (and our children) to a new parent
        virtual void reparent(TCListRow_API &ourparent, TCListRow_API &newparent)=0;
        
        /// expand this (sub)tree
        virtual void expand()
        {  if (expanded) return;
           expanded=true;
           expand_imp();
        }
        /// collapse this (sub)tree
        virtual void collapse()
        {  if (!expanded) return;
           collapse_imp();
           expanded=false;
        }
        void expand(bool e)
        {  if (e) expand();
           else collapse();
        }
        bool is_expanded() const {  return expanded; }
        /// flip expansion of this subtree
        virtual void toggle_expansion()
        {  if (expanded) collapse();
	   else expand();
        }
        
        /// return the expanding column
        virtual gint get_expanding_column() const
	{  return expanding_column; }
        /// specify the expanding column (the one with the (+)-sign)
        virtual void set_expanding_column(gint col)
        {  expanding_column=col; }
	
protected: // to make gcc happy	
	virtual ~TCListRow_API() {}
};

class TCList : public Gtk::CList, public TCListRow_API
{
    public:
        SigC::Signal1<void,gpointer> delete_user;

    private:
        gint number_of_columns;
        static Picture2 *_defaultminus,*_defaultplus;
        const Picture2 *minus,*plus;
        bool trace;

        void select_row_imp(gint,gint,GdkEvent*);

        friend class TCListRow;
        friend class iterator;

        void collapse_imp();
        void expand_imp();
    public:
        /// construct a new TCList with titles
        TCList(const std::vector <std::string> title);
        /// construct a new TCList with titles
        TCList(gint columns,const gchar **title=0);

        /// dtor
        ~TCList()
        {
#ifdef DEBUG
            if (trace) std::cout << "TCList dtor called\n";
#endif
            erase(begin(),end());
        }

        /// return iterator to first child
        iterator begin()
        {  return iterator(children,0,this);
        }
        /// return past the end iterator
        iterator end()
        {  return iterator(children,children.size(),this);
        }
        /// return iterator to first child
        const_iterator begin() const
        {  return const_iterator(children,0); }
        /// return past the end iterator
        const_iterator end() const
        {  return const_iterator(children,children.size()); }

        /// return (maximum) number of columns on this CList
        gint get_number_of_columns()
        {
            return number_of_columns;
        }

        // Könnte ein statisches Member werden ...
        /// erase a line/subtree
        void erase(iterator position);
        /// erase a range of lines/subtrees
        void erase(iterator first, iterator last);

        /// detach from clist (erases clist)
        void detach_from_clist()
        {  collapse(); }
        /// attach to clist (clist should be empty)
        void attach_to_clist()
        {  expand(); }

        /// set and get Pictures
        const Picture2 *getPlus();
        const Picture2 *getMinus();
        void setPlus(const Picture2 *p)
        {
            plus=p;
        }
        void setMinus(const Picture2 *p)
        {
            minus=p;
        }
        void Trace(bool t)
        {
            trace=t;
        }

        friend std::ostream &operator<<(std::ostream &o,const TCList &tcl);

        virtual TCListRow *push_back(const Gtk::SArray &text,gint exp_column=-1,bool expand=false);
        virtual TCListRow *insert(iterator i,const Gtk::SArray &text,gint exp_column=-1,bool expand=false);
        
    	void set_user_data(gpointer x) {
	    	Gtk::CList::set_user_data(x);
    		}
    		
    	gpointer get_user_data() const {
	    	return (Gtk::CList::get_user_data());
    		}            		
        /// reparent children to parent
        virtual void reparent_children(TCListRow_API &newparent) 
        {}
        virtual void reparent(TCListRow_API &ourparent, TCListRow_API &newparent) 
        {}
        
        void clear()
        {  erase(begin(),end());
           // Gtk::CList::clear();
        }
};

std::ostream &operator<<(std::ostream &o,const std::vector<TCListRow*> &v);
std::ostream &operator<<(std::ostream &o,const TCList &tcl);

#ifndef GTK_TCLISTROW_H
#include "TCListRow.h"
#endif

#endif
