// $Id: Midgard_Undo.hh,v 1.1 2002/04/12 08:25:11 thoma Exp $
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

#ifndef _MIDGARD_UNDO_HH
#  define _MIDGARD_UNDO_HH

#include <vector>
#include <string>

class Midgard_Undo
{
  public:
     struct st_undo{int count;std::string text;std::string speicher;
            st_undo():count(0){}
            st_undo(int c,std::string t,std::string s)
                   : count(c),text(t),speicher(s) {} };
  private:
     vector<st_undo> VU;
     unsigned int count;
     void clear(unsigned int c) {VU.resize(c);}

  public:
    Midgard_Undo():count(0) {}

    void clear() {VU.clear();}
    vector<st_undo> get_V() {return VU;}
    void push_back(std::string text,std::string speicher);
     
    std::string get_last() {return get(--count);}
    std::string get_next() {return get(++count);};
    std::string get(unsigned int c);
};

#include <Aux/EntryValueIntString.h>   
#include <rowdata.h>

class Data_Undo : public RowDataBase
{
     Midgard_Undo::st_undo U;
   public:
     Data_Undo(Midgard_Undo::st_undo u) : U(u) {}
     
     enum spalten{NR,BEZ};
     virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const
      {
        switch(spalten(seqnr))
         {
           case NR:  return cH_EntryValueIntString(U.count);
           case BEZ: return cH_EntryValueIntString(U.text);
         }
        return cH_EntryValueIntString();
      }
   int getIndex() const {return U.count;}
};

class cH_Data_Undo : public Handle<const Data_Undo>
{
 protected:
  cH_Data_Undo() {}
 public:
  cH_Data_Undo(const Data_Undo *r) : Handle<const Data_Undo>(r){}
};

#endif
