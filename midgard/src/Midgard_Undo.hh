// $Id: Midgard_Undo.hh,v 1.9 2005/11/01 23:55:34 christof Exp $
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

#error obsolete file

#ifndef _MIDGARD_UNDO_HH
#  define _MIDGARD_UNDO_HH

#include <libmagus/Undo.hh>

#include <Misc/EntryValueIntString.h>   
#include <RowDataBase.h>

class Data_Undo : public RowDataBase
{
     Midgard_Undo::st_undo U;
   public:
     Data_Undo(Midgard_Undo::st_undo u) : U(u) {}
     
     enum spalten{NR,BEZ};
     virtual cH_EntryValue Value(guint seqnr,gpointer gp) const
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
