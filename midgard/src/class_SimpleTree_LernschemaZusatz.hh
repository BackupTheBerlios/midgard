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

#ifndef _CLASS_SIMPLELERN_HH
#  define _CLASS_SIMPLELERN_HH

#include <rowdata.h>   
#include "Land.hh"
#include <Aux/EntryValueIntString.h>
#include "MidgardBasicElement.hh"

class Data_Herkunft : public RowDataBase
{
      cH_Land Land;

   public:
      Data_Herkunft(const cH_Land l)
         : Land(l) {}

      enum Spalten {LAND,KONTINENT,SPRACHEN};
      virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const
        {
         switch((Spalten)seqnr) 
           {
            case LAND      : return cH_EntryValueIntString(Land->Name());
            case KONTINENT : return cH_EntryValueIntString(Land->Kontinent());
            case SPRACHEN  : 
              { std::string s;
                vector<std::string> VS=Land->Sprachen();
                for(vector<std::string>::const_iterator i=VS.begin();i!=VS.end();++i)
                  s+= *i + " ";
                return cH_EntryValueIntString(s);
              }
           }
          return cH_EntryValueIntString();
        }
      cH_Land getLand() const {return Land;}
};

class cH_Data_Herkunft : public Handle<Data_Herkunft>
{
public:
 cH_Data_Herkunft(Data_Herkunft *r) : Handle<Data_Herkunft>(r) {}
};

////////////////////////////////////////////////////////////////
class Data_Zusatz : public RowDataBase
{
      MidgardBasicElement_mutable MBE;
      std::string zusatz;

   public:
      Data_Zusatz(const MidgardBasicElement_mutable &mbe,std::string z)
         : MBE(mbe),zusatz(z) {}

      enum Spalten {NAME};
      virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const
        {
         switch((Spalten)seqnr) 
           {
            case NAME : return cH_EntryValueIntString(zusatz);
            default : return cH_EntryValueIntString("");
           }
          return cH_EntryValueIntString();
        }
      const MidgardBasicElement_mutable &getMBE() const {return MBE;}
      std::string getZusatz() const {return zusatz;}
};

class cH_Data_Zusatz : public Handle<Data_Zusatz>
{
public:
 cH_Data_Zusatz(Data_Zusatz *r) : Handle<Data_Zusatz>(r) {}
};


  
#endif
