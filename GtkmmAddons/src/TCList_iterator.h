/*  Gtk--addons: a collection of gtk-- addons
 *  Copyright (C) 2001 Adolf Petig GmbH & Co. KG, written by Christof Petig
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

// $Id: TCList_iterator.h,v 1.3 2001/11/09 10:38:27 christof Exp $

class TCListRow;
class TCList;
class TCListRow_API;

class TCListRow_baseiterator : std::random_access_iterator<TCListRow,ptrdiff_t>
{
    protected:
        typedef TCListRow T;
        std::vector <T *> *current_vector;
        unsigned int current_index;
        
        // yes this is nonsense but STL requires this
        TCListRow_baseiterator()
        	: current_vector(0), current_index(0)
        {}

    public:
        typedef TCListRow_baseiterator iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        TCListRow_baseiterator(std::vector<T*> &v,int i)
                : current_vector(&v), current_index(i)
    {}

        const iterator &operator+=(ptrdiff_t distance)
        {  current_index+=distance;
           return *this;
        }
        ptrdiff_t operator-(const iterator &b) const
        {  return current_index-b.current_index;
        }

        bool operator==(const iterator &i) const
        {  return i.current_vector==current_vector
                      && i.current_index==current_index;
        }
        bool operator!=(const iterator &i) const
        {  return i.current_vector!=current_vector
                      || i.current_index!=current_index;
        }
        friend std::ostream &operator<<(std::ostream &o,const TCListRow_baseiterator &it);
};

class TCListRow_constiterator : public TCListRow_baseiterator
{
    public:
        typedef TCListRow_constiterator iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        TCListRow_constiterator(const std::vector<T*> &v,int i)
                : TCListRow_baseiterator((std::vector<T*>&)v,i)
    {}
        TCListRow_constiterator(const TCListRow_baseiterator &i)
                : TCListRow_baseiterator(i)
    {}

        const T &operator*() const
        {
#ifdef BE_CAREFUL
            assert(current_index<current_vector->size());
#endif
            return *((*current_vector)[current_index]);
        }
        operator std::vector<T*>::const_iterator() const
        {  return current_vector->begin()+current_index;
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

class TCListRow_iterator : public TCListRow_baseiterator
{
        TCList *root;
        TCListRow *row; // this is the parent (if available)

        friend class TCList;
        friend class TCListRow;
    public:
        typedef TCListRow_iterator iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        TCListRow_iterator(std::vector<T*> &v,int i,TCList *rt)
                : TCListRow_baseiterator(v,i), root(rt), row(0)
	{}
        TCListRow_iterator(std::vector<T*> &v,int i,TCList *rt,TCListRow *rw)
                : TCListRow_baseiterator(v,i), root(rt), row(rw)
	{}
        TCListRow_iterator(const iterator &i)
                : TCListRow_baseiterator((TCListRow_baseiterator)i),
                root(i.root), row(i.row)
	{}
	// needed for STL - I don't like that either
	TCListRow_iterator()
		: root(0), row(0)
	{}
	explicit TCListRow_iterator(TCListRow_API *parent,TCListRow *tclr);

        T &operator*()
        {
#ifdef BE_CAREFUL
            assert(current_index<current_vector->size());
#endif
            return *((*current_vector)[current_index]);
        }
        operator std::vector<T*>::iterator()
        {
            return current_vector->begin()+current_index;
        }
        /// remove the corresponding pointer from the array
        void erase()
        {
#ifdef BE_CAREFUL
            //	   assert(current_index>=0);
            assert(current_index<current_vector->size());
#endif
            current_vector->erase(std::vector<T*>::iterator(*this));
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
        bool operator!=(const TCListRow_constiterator &i) const
        {  return (TCListRow_baseiterator)*this != (TCListRow_baseiterator)i;
        }
};

static inline bool operator!=(const TCListRow_constiterator &i,const TCListRow_iterator &j)
{
    return (TCListRow_baseiterator)j != (TCListRow_baseiterator)i;
}

static inline bool operator!=(const TCListRow_iterator &i,const TCListRow_iterator &j)
{
    return (TCListRow_baseiterator)j != (TCListRow_baseiterator)i;
}

