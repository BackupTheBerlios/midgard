// $Id: Undo.hh,v 1.1 2003/09/01 06:48:57 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef _LIBMIDGARD_UNDO_HH
#  define _LIBMIDGARD_UNDO_HH

#include <vector>
#include <string>

class Midgard_Undo
{
  public:
     struct st_undo{int count;std::string text;std::string speicher;
            st_undo():count(0){}
            st_undo(int c,std::string t,std::string s)
                   : count(c),text(t),speicher(s) {} };
     typedef std::vector<st_undo>::const_iterator const_iterator;
  private:
     std::vector<st_undo> VU;
     unsigned int count;
     void clear(unsigned c) {VU.resize(c);}

  public:
    Midgard_Undo():count() {}

    void clear() {VU.clear();}
    const std::vector<st_undo> &get_V() const {return VU;}
    void push_back(const std::string &text,const std::string &speicher);
    const_iterator begin() const { return VU.begin(); }
    const_iterator end() const { return VU.end(); }
    const_iterator current_iter() const { return VU.begin()+count; }
     
    std::string get_last();
    std::string get_next();
    std::string get(unsigned c);
};

#endif
