// $Id: TCList_ct.h,v 1.4 2002/03/20 07:49:18 christof Exp $
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

#ifndef GTK_TCLIST_CT_H
#define GTK_TCLIST_CT_H
#include <gtk--/ctree.h>
#include <vector>
#include <string>
#include <iterator>
#include <iostream>
#include <cassert>
#include <Picture2.h>
#include <gtk/gtkfeatures.h>

class TCListRow_ct;
class TCList_ct;

class TCListRow_ct_baseiterator : std::bidirectional_iterator<TCListRow_ct,ptrdiff_t>
{
    protected:
        typedef TCListRow_ct T;
        std::vector <T *> &current_vector;
        unsigned int current_index;

    public:
        typedef TCListRow_ct_baseiterator iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        TCListRow_ct_baseiterator(std::vector<T*> &v,int i)
                : current_vector(v), current_index(i)
    {}
        TCListRow_ct_baseiterator(const iterator &i)
                : current_vector(i.current_vector),
                current_index(i.current_index)
    {}
    private:
        iterator operator=(const iterator &i) // existiert nicht !!!
        {
            std::cerr << "TCList_ct::iterator::operator=(const iterator &) aufgerufen\n";
            abort();
        }
    public:
        bool operator==(const iterator &i) const
        {  return &i.current_vector==&current_vector
                      && i.current_index==current_index;
        }
        bool operator!=(const iterator &i) const
        {  return &i.current_vector!=&current_vector
                      || i.current_index!=current_index;
        }
        friend std::ostream &operator<<(std::ostream &o,const TCListRow_ct_baseiterator &it);
};

class TCListRow_ct_constiterator : public TCListRow_ct_baseiterator
{
    public:
        typedef TCListRow_ct_constiterator iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        TCListRow_ct_constiterator(const std::vector<T*> &v,int i)
                : TCListRow_ct_baseiterator((std::vector<T*>&)v,i)
    {}
        TCListRow_ct_constiterator(const TCListRow_ct_baseiterator &i)
                : TCListRow_ct_baseiterator(i)
    {}

        const T &operator*() const
        {
#ifdef BE_CAREFUL
            assert(current_index<current_vector.size());
#endif
            return *(current_vector[current_index]);
        }
        operator std::vector<T*>::const_iterator() const
        {  return current_vector.begin()+current_index;
        }
        iterator operator++(int)
        {
            iterator tmp=*this;
            current_index++;
            return tmp;
        }
        iterator &operator++()
        {
            current_index++;
            return *this;
        }
        iterator operator--(int)
        {
            iterator tmp=*this;
#ifdef BE_CAREFUL
            assert(current_index>0);
#endif
            current_index--;
            return tmp;
        }
        iterator &operator--()
        {
#ifdef BE_CAREFUL
            assert(current_index>0);
#endif
            current_index--;
            return *this;
        }
};

class TCListRow_ct_iterator : public TCListRow_ct_baseiterator
{
        TCList_ct *root;
        TCListRow_ct *row; // this is the parent (if available)

        friend class TCList_ct;
        friend class TCListRow_ct;
    public:
        typedef TCListRow_ct_iterator iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        TCListRow_ct_iterator(std::vector<T*> &v,int i,TCList_ct *rt)
                : TCListRow_ct_baseiterator(v,i), root(rt), row(0)
	{}
        TCListRow_ct_iterator(std::vector<T*> &v,int i,TCList_ct *rt,TCListRow_ct *rw)
                : TCListRow_ct_baseiterator(v,i), root(rt), row(rw)
	{}
        TCListRow_ct_iterator(const iterator &i)
                : TCListRow_ct_baseiterator((TCListRow_ct_baseiterator)i),
                root(i.root), row(i.row)
	{}

        T &operator*()
        {
#ifdef BE_CAREFUL
            assert(current_index<current_vector.size());
#endif
            return *(current_vector[current_index]);
        }
        operator std::vector<T*>::iterator()
        {
            return current_vector.begin()+current_index;
        }
        /// remove the corresponding pointer from the array
        void erase();
#if 0        
        {
#ifdef BE_CAREFUL
            //	   assert(current_index>=0);
            assert(current_index<current_vector.size());
#endif
            current_vector.erase(std::vector<T*>::iterator(*this));
        }
#endif        
        iterator operator++(int)
        {
            iterator tmp=*this;
            current_index++;
            return tmp;
        }
        iterator &operator++()
        {
            current_index++;
            return *this;
        }
        iterator operator--(int)
        {
            iterator tmp=*this;
#ifdef BE_CAREFUL
            assert(current_index>0);
#endif
            current_index--;
            return tmp;
        }
        iterator &operator--()
        {
#ifdef BE_CAREFUL
            assert(current_index>0);
#endif
            current_index--;
            return *this;
        }
        bool operator!=(const TCListRow_ct_constiterator &i) const
        {  return (TCListRow_ct_baseiterator)*this != (TCListRow_ct_baseiterator)i;
        }
};

static inline bool operator!=(const TCListRow_ct_constiterator &i,const TCListRow_ct_iterator &j)
{
    return (TCListRow_ct_baseiterator)j != (TCListRow_ct_baseiterator)i;
}

static inline bool operator!=(const TCListRow_ct_iterator &i,const TCListRow_ct_iterator &j)
{
    return (TCListRow_ct_baseiterator)j != (TCListRow_ct_baseiterator)i;
}

class TCListRow_ct_API
{protected:
        typedef std::vector <TCListRow_ct *> children_t;
        children_t children;
public:
        typedef TCListRow_ct_iterator iterator;
        typedef TCListRow_ct_constiterator const_iterator;
        typedef TCListRow_ct_iterator::reverse_iterator reverse_iterator;

        virtual TCListRow_ct *push_back(const Gtk::SArray &text,gint exp_column=-1,bool expand=false)=0;
        virtual TCListRow_ct *insert(iterator i,const Gtk::SArray &text,gint exp_column=-1,bool expand=false)=0;
        
        /// number of children
        int size() const
        {  return children.size(); }
        /// whether this Node has no children
        bool empty() const
	{  return children.empty(); }
	
        virtual iterator begin()=0;
        virtual iterator end()=0;
        virtual const_iterator begin() const=0;
        virtual const_iterator end() const=0;
	virtual void set_user_data(gpointer x) = 0;
	virtual gpointer get_user_data() const = 0;
	
	/// reparent children to parent
	virtual void reparent_children(TCListRow_ct_API &newparent)=0;
	/// reparent us (and our children) to a new parent
	virtual void reparent(TCListRow_ct_API &ourparent, TCListRow_ct_API &newparent)=0;

        /// expand this (sub)tree
        virtual void expand()=0;
        /// collapse this (sub)tree
        virtual void collapse()=0;
        void expand(bool e)
        {  if (e) expand();
           else collapse();
        }
        bool is_expanded() const;
        /// flip expansion of this subtree
        virtual void toggle_expansion()
        {  if (is_expanded()) collapse();
	   else expand();
        }
        
        /// return the expanding column
        virtual gint get_expanding_column() const
	{  return -1; }
        /// specify the expanding column (the one with the (+)-sign)
        virtual void set_expanding_column(gint col)
        {  }
	
	
protected: // to make gcc happy	
	virtual ~TCListRow_ct_API() {}
};

class TCList_ct : public Gtk::CTree, public TCListRow_ct_API
{
    public:
        SigC::Signal1<void,gpointer> delete_user;

        typedef TCListRow_ct_iterator iterator;
        typedef TCListRow_ct_constiterator const_iterator;
        typedef TCListRow_ct_iterator::reverse_iterator reverse_iterator;
    private:
        static Picture2 *_defaultminus,*_defaultplus;
        const Picture2 *minus,*plus;
        bool trace;

        friend class TCListRow_ct;
        friend class iterator;

        const Picture2 *_getPlus() const;
        const Picture2 *_getMinus() const;
        
        void _erase(const TCListRow_ct *r);

    public:
        /// construct a new TCList_ct with titles
        TCList_ct(const std::vector <std::string> title,int tree_column=0);
        /// construct a new TCList_ct with titles
        TCList_ct(gint columns,const gchar **title=0,int tree_column=0);

        /// dtor
        ~TCList_ct()
        {
#ifdef DEBUG
            if (trace) std::cout << "TCList_ct dtor called\n";
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
            return GTK_CLIST(gtkobj())->columns;
        }

        // Könnte ein statisches Member werden ...
        /// erase a line/subtree
        void erase(iterator position);
        /// erase a range of lines/subtrees
        void erase(iterator first, iterator last);

        /// set and get Pictures
        const Picture2 *getPlus() const
        {  if (!plus) return _getPlus();
           return plus;
        }
        const Picture2 *getMinus() const
        {  if (!minus) return _getMinus();
           return minus;
        }
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

        friend std::ostream &operator<<(std::ostream &o,const TCList_ct &tcl);
	void debug() const;
        virtual TCListRow_ct *push_back(const Gtk::SArray &text,gint exp_column=-1,bool expand=false);
        virtual TCListRow_ct *insert(iterator i, const Gtk::SArray &text,gint exp_column=-1,bool expand=false);
};

std::ostream &operator<<(std::ostream &o,const std::vector<TCListRow_ct*> &v);
std::ostream &operator<<(std::ostream &o,const TCList_ct &tcl);

#ifndef GTK_TCLISTROW_H
#include "TCListRow_ct.h"
#endif

#ifndef GTK_TCLIST_H
typedef TCList_ct TCList;
typedef TCListRow_ct TCListRow;
typedef TCListRow_ct_API TCListRow_API;
#endif

#endif
