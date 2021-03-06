// $Id: Data_waffenbesitz.hh,v 1.13 2005/11/01 23:55:34 christof Exp $
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

#ifndef _WINDOW_DATA_WAFFENBESITZ_HH
#  define _WINDOW_DATA_WAFFENBESITZ_HH

//#include <list>
//#include <string>
#include <Misc/EntryValueIntString.h>
#include <Waffe.hh>

#include "MidgardBasicElement.hh"
#include "midgard_CG.hh"
#include <libmagus/Datenbank.hh>

class Data_waffenbesitz :  public RowDataBase
{
      H_WaffeBesitz waffe;
      const midgard_CG *hauptfenster;
  public:
      Data_waffenbesitz(const H_WaffeBesitz& w,const midgard_CG *h)
         : waffe(w), hauptfenster(h) {}

      enum SPALTEN_A {NAME_A,SCHADEN_A,REGION,MAGBONUS,MAGTEXT};
      virtual cH_EntryValue Value(guint seqnr,gpointer gp) const
       {
          switch(seqnr) {
            case NAME_A : return cH_EntryValueIntString(waffe->AliasName());
            case SCHADEN_A : return cH_EntryValueIntString(waffe->Schaden(hauptfenster->getAben(),waffe->AliasName()));
            case REGION : return cH_EntryValueIntString(Regionen_All::
               getRegionfromAbk(Datenbank.Regionen,
               waffe->Waffe()->Region(waffe->AliasName()))->Name());
            case MAGBONUS : return cH_EntryValueIntString(waffe->Bonus());
            case MAGTEXT : return cH_EntryValueIntString(waffe->Magisch());
           }
         return cH_EntryValue();
       }
      H_WaffeBesitz get_Waffe() const {return waffe;}
};

class cH_Data_waffenbesitz : public Handle<const Data_waffenbesitz>
{
protected:
 cH_Data_waffenbesitz() {}
public:
 cH_Data_waffenbesitz(const Data_waffenbesitz *r) : Handle<const Data_waffenbesitz>(r){}
};

#endif

