/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

#ifndef _DATA_PROTOTYP_HH
#  define _DATA_PROTOTY_HH

#include <Misc/itos.h>
#include <Misc/EntryValueEmptyInt.h>
//#include <Misc/EntryValueFixed.h>
//#include "dtos1.h"

class Data_Prototyp : public RowDataBase
{
      cH_Prototyp2 ptyp;
      Prototyp2::st_protolisten st_ptyp;
      std::string art;

  public:
     Data_Prototyp(const cH_Prototyp2 t,std::string a,Prototyp2::st_protolisten s) 
      : ptyp(t),st_ptyp(s),art(a) {}
      
     enum spalten {PROTOTYP,ART,NAME,FAKTOR};
     
     virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const 
      {
        switch(spalten(seqnr)) {
           case ART: return cH_EntryValueIntString(art);
           case NAME: return cH_EntryValueIntString(st_ptyp.name);
           case FAKTOR: return cH_EntryValueIntString(dtos(st_ptyp.fac));
           case PROTOTYP: return cH_EntryValueIntString(ptyp->Name());
         }
        return cH_EntryValueIntString();
      }
   cH_Prototyp2 getPrototyp() const {return ptyp;}
//   double getFaktor() const {return st_ptyp.fac;}
};
class cH_Data_Prototyp : public Handle<const Data_Prototyp>
{
public:
 cH_Data_Prototyp(const Data_Prototyp *r) : Handle<const Data_Prototyp>(r) {}
};

#endif
