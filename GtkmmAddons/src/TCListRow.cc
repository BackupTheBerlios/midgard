// $Id: TCListRow.cc,v 1.12 2002/03/20 07:49:18 christof Exp $
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
#include <iterator>

void TCListRow::set_expanding_column(gint col)
{
    int lineno=-1;
    if (root.expanded)
    {
        lineno=get_lineno();
        if (expanding_column!=-1 && lineno!=-1)
        {
            gint col=expanding_column;
            expanding_column=-1;
            redraw_column_imp(lineno,col);
        }
        if (root.trace) std::cout << "set_expanding_column(" << col << ") on line "<< lineno<<"\n";
    }
    else
    {
        if (root.trace) std::cout << "set_expanding_column(" << col << ") on "<< *this<<"\n";
    }
    expanding_column=col;
    if (root.expanded && lineno!=-1) redraw_column_imp(lineno,expanding_column);
}

void TCListRow::expansion_redraw_imp(gint lineno)
{  // std::cerr << "expansion_redraw_imp() called\n";
    if (!root.expanded) return;
    if (lineno==unspecified_lineno) lineno=get_lineno();
    redraw_column_imp(lineno,expanding_column);
}

void TCListRow::redraw_column_imp(gint lineno,gint colno)
{
    if (lineno==-1||colno==-1||!root.expanded) return;
    if (colno==expanding_column)
    {
        const int spacing=8;
        const Picture2 *p= expanded ? root.getMinus() : root.getPlus();
        root.set_pixtext(lineno,expanding_column,columns[expanding_column].c_str(),
                         spacing,p->pmap(),p->mask());
    }
    else if ((unsigned int)colno>=pics.size() || !pics[colno])
    {
        root.set_text(lineno,colno,columns[colno].c_str());
    }
    else
    {
        const int spacing=8;
        root.set_pixtext(lineno,colno,columns[colno].c_str(),
                         spacing,pics[colno]->pmap(),pics[colno]->mask());
    }
}

void TCListRow::redraw_pics_imp(gint lineno)
{
    if (lineno==unspecified_lineno) lineno=get_lineno();
    if (lineno==-1||!root.expanded) return;
    if (expanding_column) redraw_column_imp(lineno,expanding_column);
    for (guint i=0;i<pics.size();i++)
    {
        if ((int)i==expanding_column || !pics[i]) continue;
        redraw_column_imp(lineno,i);
    }
}

void TCListRow::expand()
{
    if (expanded) return;
    expanded=true;
    if (!root.expanded) return;
    root.freeze();
    expand_imp();
    root.thaw();
#ifdef DEBUG
    if (root.trace) std::cout << "expand " << *this;
#endif
}

void TCListRow::expand_imp()
{
    if (!root.expanded) return;
    int lineno=get_lineno();
    if (lineno==-1) return;
    redraw_column_imp(lineno,expanding_column);
    lineno++;
    // expand direct children
    for (iterator i=begin();i!=end();i++)
    {
        const std::vector <std::string> &v=(*i).get_columns();

        root.insert_row(lineno,v);
        root.set_row_data(lineno,&*i);
        (*i).redraw_pics_imp(lineno);
        lineno++;
    }
    // now expand grandchildren
    for (iterator i=begin();i!=end();i++)
    {
        if ((*i).expanded) (*i).expand_imp();
    }
}

void TCListRow::collapse()
{
    if (!expanded) return;
    expanded=false;
    if (!root.expanded) return;
    root.freeze();
    collapse_imp();
    root.thaw();
}

void TCListRow::collapse_imp()
{
    if (!root.expanded) return;
    for (iterator i=begin();i!=end();i++)
    {
        (*i).remove_imp();
    }
    redraw_column_imp(get_lineno(),expanding_column);
}

void TCListRow::remove_imp()
{
    if (!root.expanded) return;
    int lineno=get_lineno();

#ifdef DEBUG
    if (root.trace) std::cout << "remove:\n" << *this;
#endif
    if (lineno!=-1)
    {
        root.remove_row(lineno);
        // remove children
        if (expanded) for (iterator i=begin();i!=end();i++)
            {
                (*i).remove_imp();
            }
    }
}

std::ostream &operator<<(std::ostream &out,const TCListRow &lr)
{
    out << "TCListRow @" << &lr << " " << (lr.expanded?"":"!") << "exp";
    out << " exp_col=" << lr.expanding_column << " " << lr.children.size();
    out << " children: ";
    for (int i=0;i<lr.root.get_number_of_columns();i++)
    {
        out << "\"" << lr.columns[i] << "\" ";
    }
    out << "\n";
#ifdef DEBUG
    for (TCListRow::const_iterator i=lr.begin();i!=lr.end();i++)
        out << "\t" << *i;
#endif
    return out;
}

void TCListRow::reparent_children(TCListRow_API &newparent)
{   // we collapse us (delete children in CList) and the new parent
    // to detach our node from the CList
    
    if (root.trace) std::cout << "reparent " << size() << " children from @" << this << " to @" 
    		<< &newparent << " (" << newparent.size() << " children)\n";
    collapse();
    // note that we do not change expanded by collapse_imp
    if (root.expanded && newparent.expanded) newparent.collapse_imp();
    
    // now insert the children pointers at the new position
    // should be right after us
    std::vector<TCListRow*>::iterator after_us_or_at_end
    		=::find(newparent.children.begin(),newparent.children.end(),this);
    // if it points to us increment
    if (after_us_or_at_end!=newparent.children.end()) ++after_us_or_at_end;
    insert_iterator<std::vector<TCListRow*> > ii(newparent.children,after_us_or_at_end);
    // I wish I had move
    copy(children.begin(),children.end(),ii);
    // delete it at the old position
    children.erase(children.begin(),children.end());
    if (root.trace) std::cout << "now parent has " << newparent.size() << " children\n";
    
    if (root.expanded && newparent.expanded) newparent.expand_imp();
    // we do not need to expand us since we don't have any children any longer
}

void TCListRow::reparent(TCListRow_API &ourparent, TCListRow_API &newparent)
{   // we collapse us (delete children in CList) and the new parent
    // to detach our node from the CList

    if (root.trace) 
       std::cout << "reparent us @" << this << " from @" << &ourparent 
       		<< " (" << ourparent.size() << " children) to @" 
    		<< &newparent << " (" << newparent.size() << " children)\n";
    
    // note that we do not change expanded by using collapse_imp
    if (root.expanded && ourparent.expanded) ourparent.collapse_imp();
    if (&ourparent!=&newparent && root.expanded && newparent.expanded) newparent.collapse_imp();
    
    newparent.children.push_back(this);
    std::vector<TCListRow*>::iterator iterator4us
    		=::find(ourparent.children.begin(),ourparent.children.end(),this);
    assert(iterator4us!=ourparent.children.end());
    ourparent.children.erase(iterator4us);
    
    if (root.trace) 
       std::cout << "now new parent has " << newparent.size() << " children\n"
                 << "now our old parent has " << ourparent.size() << " children\n";
    
    if (root.expanded && newparent.expanded) newparent.expand_imp();
    if (&ourparent!=&newparent && root.expanded && ourparent.expanded) ourparent.expand_imp();
}

int TCListRow::visible_size() const
{  if (!root.expanded) return 0;
    int res=1;
    if (expanded)
    {
        for (const_iterator i=begin();i!=end();i++)
            res+=(*i).expanded ? (*i).visible_size() : 1;
        // this '?:' avoids one depth of recursion
    }
    return res;
}

void TCListRow::set_text(guint column,const std::string &text)
{  // if (column>root.get_number_of_columns()) return;
    columns[column]=text; // hmmm
    if (!root.expanded) return;
    gint lineno=get_lineno();
    if (lineno==-1) return;
    redraw_column_imp(lineno,column);
}

#if 0
void TCListRow::construct(iterator next,const std::vector <const std::string> &cols, gint exp_column, bool expand)
{
    std::vector <std::string> adaptor;
    for (std::vector <const std::string>::const_iterator i=cols.begin();i!=cols.end();++i)
        adaptor.push_back(*i);
    construct(next,adaptor,exp_column,expand);
}
#endif

void TCListRow::construct(iterator next,const char **cols, gint exp_column, bool expand)
{
    std::vector <std::string> adaptor;
    for (int i=0; i<root.get_number_of_columns(); ++i)
        adaptor.push_back(cols[i]);
    construct(next,adaptor,exp_column,expand);
}

void TCListRow::construct(iterator next,const std::vector <std::string> &cols, gint exp_column, bool expand)
{
    expanded=expand;
    expanding_column=exp_column;
    columns=cols;
    user_data=0;

    bool is_end = next.current_index >= next.current_vector->size();

    // next.current_vector.insert(next, this); see below !

    if (root.trace) std::cout << root << '\n';
    if (root.trace)
        std::cout << "adding line {" << *this << "} to {@"<< next.row
        << "} before #"<< next.current_index << (is_end?" end":"") << "\n";
    if (root.expanded)
    {   gint newline;

        if (!is_end)
        {
            newline = (*next).get_lineno();
            if (newline != -1) 
            {  root.insert_row(newline, cols);
               if (root.trace) std::cout << "inserting as #" << newline << '\n';
            }
            else
            {  if (root.trace)
               	  std::cout << "when next node is not visible, we shouldn't be visible either\n";
            }
        }
        else // insert at end (perhaps at end of current)
        {   if (next.row) // we know our parent
            {   if (next.row->empty())
                {   newline=next.row->get_lineno();
                    if (newline!=-1) newline++;
                }
                else
                {   newline=next.row->children.back()->get_lineno();
                    if (newline!=-1) newline+=next.row->children.back()->visible_size();
                }
                if (newline!=-1 && next.row->expanded) 
                {   root.insert_row(newline, cols);
                    if (root.trace) std::cout << "inserting as #" << newline << '\n';
                }
                else
                   if (root.trace)
                      std::cout << "not inserting: newline=" << newline 
                      	<< (next.row->expanded?" next expanded":" next not expanded") << '\n';
            }
            else // fall back, real appending
                {newline = root.append(cols);
		 if (root.trace) std::cerr << "at end & no parent\n";
		}
        }

        if (newline != -1)
        {
            root.set_row_data(newline, this);
            redraw_pics_imp(newline);
        }
    }
    else if (root.trace) std::cout << "root not expanded\n";
    // this invalidates our iterator so do this last!
    next.current_vector->insert(next, this);
    if (root.trace) std::cout << "CList holds " << root.rows().size() << " lines\n";
}

TCListRow *TCListRow::push_back(const Gtk::SArray &text,gint exp_column,bool expand)
{  TCListRow *res=new TCListRow(root);
   res->construct(end(),(const char **)text,exp_column,expand);
   return res;
}

TCListRow *TCList::push_back(const Gtk::SArray &text,gint exp_column,bool expand)
{  TCListRow *res=new TCListRow(*this);
   res->construct(end(),(const char **)text,exp_column,expand);
   return res;
}

TCListRow *TCListRow::insert(TCListRow_API::iterator i,const Gtk::SArray &text,gint exp_column,bool expand)
{  TCListRow *res=new TCListRow(root);
   res->construct(i,(const char **)text,exp_column,expand);
   return res;
}

TCListRow *TCList::insert(TCListRow_API::iterator i,const Gtk::SArray &text,gint exp_column,bool expand)
{  TCListRow *res=new TCListRow(*this);
   res->construct(i,(const char **)text,exp_column,expand);
   return res;
}

void TCListRow::append_imp()
{
    if (!root.expanded) return;

    gint lineno=root.append(columns);
    root.set_row_data(lineno,this);
    redraw_pics_imp(lineno);

    if (expanded) for (iterator i=begin();i!=end();++i)
        {
            (*i).append_imp();
        }
}
