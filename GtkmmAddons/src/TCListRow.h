// $Id: TCListRow.h,v 1.9 2002/06/28 07:15:06 christof Exp $
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

#ifndef GTK_TCLISTROW_H
#define GTK_TCLISTROW_H
#include <vector>
#include <string>
#include <iterator>
#include <iostream>
#include <algo.h>

class TCListRow;

#ifndef GTK_TCLIST_H
#  include "TCList.h"
#endif

class TCListRow : public TCListRow_API
{private:
        friend class TCList;
        friend class iterator;

        TCList &root;
        std::vector <std::string> columns;
        std::vector <const Picture2 *> pics;
        gpointer user_data;
        Gdk_Color color;
        bool color_set;
        static const int unspecified_lineno=-2;

        /// ??? is called by parent->show() !!!
        void expand_imp();
        void collapse_imp();
        void redraw_column_imp(gint lineno,gint colno);
        void redraw_pics_imp(gint lineno=unspecified_lineno);
        /// do not use too extensively, use redraw_column_imp where possible
        void expansion_redraw_imp(gint lineno=unspecified_lineno);
        void remove_imp();
        /// for a very fast insertion of the whole list
        void append_imp();
        void select_row_imp(gint,gint,GdkEventButton*);

        virtual void delete_imp()
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
        
        TCListRow(TCList &_root) : root(_root), color_set(false)
        {}

//        void construct(iterator next,const std::vector <const std::string> &cols,gint exp_column=-1,bool expand=false);
        void construct(iterator next,const std::vector <std::string> &cols,gint exp_column=-1,bool expand=false);
        void construct(iterator next,const char **cols,gint exp_column=-1,bool expand=false);

    public:
        virtual TCListRow *push_back(const Gtk::SArray &text,gint exp_column=-1,bool expand=false);
        virtual TCListRow *insert(iterator i,const Gtk::SArray &text,gint exp_column=-1,bool expand=false);

        virtual ~TCListRow()
        {
            delete_imp();
#ifdef DEBUG
            std::cout << this << " dtor end\n";
#endif
        }
        /// return iterator to first child
        virtual iterator begin()
        {
            return TCList::iterator(children,0,&root,this);
        }
        /// return past the end iterator
        virtual iterator end()
        {
            return TCList::iterator(children,children.size(),&root,this);
        }
        /// return iterator to first child
        virtual const_iterator begin() const
	{  return TCList::const_iterator(children,0); }
        /// return past the end iterator
        virtual const_iterator end() const
	{  return TCList::const_iterator(children,children.size()); }

        /// specify the expanding column (the one with the (+)-sign)
        virtual void set_expanding_column(gint col);
        /// return line number within Gtk_CList (or -1 if not expanded)
        gint get_lineno() const
	{  return root.find_row_from_data((gpointer)this); }
        /// not implemented. should return number of lines of this subtree
//        gint get_num_rows() const;
        /// add an hook for your data
        virtual void set_user_data(gpointer x)
        {
            user_data=x;
        }
        /// return your data
	virtual gpointer get_user_data() const
        {  return user_data;
        }
        /// expand this subtree
        virtual void expand();
        /// collapse this subtree
        virtual void collapse();

        /// return contents (text) of this node
        const std::vector <std::string> &get_columns() const
	{  return columns; }

        /// reparent children to parent
        void reparent_children(TCListRow_API &newparent);
        /// reparent us to a new parent
        void reparent(TCListRow_API &ourparent, TCListRow_API &newparent);

        /// find iterator to child
        iterator find(const TCListRow &value)
        {
            return std::find(begin(),end(),value);
        }
        /// visible_size of this subtree
        int visible_size() const;

	void set_text(guint column, const std::string &text);
        /// relabel column
        void relabel(int column, const std::string &text)
        {   set_text(column,text);
        }
        void relabel(int column, gchar *text)
        {
            set_text(column,(const std::string)text);
        }
        const std::string get_text(guint column) const
        {   return columns[column];
        }

        bool operator==(const TCListRow &value) const { return this==&value; }

        /** For performance reasons cloning Pictures is not done.
            You really need a picture _ONCE_? You're kidding! */
        void setPicture(int column,const Picture2 *pic)
        {
            while (pics.size()<=(unsigned int)column) pics.push_back(0);
            pics[column]=pic;
            if (root.expanded) redraw_column_imp(get_lineno(),column);
        }
        
        void set_color(const Gdk_Color &col);

        friend std::ostream &operator<<(std::ostream &out,const TCListRow &lr);
};

/// debug contents of this node
std::ostream &operator<<(std::ostream &out,const TCListRow &lr);
std::ostream &shl_rec(std::ostream &o, const TCListRow::const_iterator &b, const TCListRow::const_iterator &e);

#endif
