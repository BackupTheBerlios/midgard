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

#include <Misc/EntryValueIntString.h>
#include <rowdata.h>
#include "Beruf.hh"

class Beruf_Data : public RowDataBase
{
      Beruf::st_vorteil BF;
      std::string beruf;

      std::string kat_to_str(const int kat) const
         { if (kat==1) return "I";
           else if (kat==2) return "II";
           else if (kat==3) return "III";
           else if (kat==4) return "IV";
           else return "?";
         }

   public:
      Beruf_Data(std::string b,Beruf::st_vorteil bf) : BF(bf),beruf(b) {}
        
      enum spalten{BERUF,GELERNT,FERT,WERT,KAT};
      
      virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const
       {
         switch(spalten(seqnr))
          {
            case KAT: return cH_EntryValueIntString(kat_to_str(BF.kat));
            case BERUF: return cH_EntryValueIntString(beruf);
            case FERT: return cH_EntryValueIntString(BF.name);
            case WERT: return cH_EntryValueIntString(BF.wert);
            case GELERNT: {
               if(BF.gelernt) return cH_EntryValueIntString("*");
               else return cH_EntryValueIntString("");
             }
          }
        return cH_EntryValueIntString("?");
       }
      std::string getBeruf() const {return beruf;}
      Beruf::st_vorteil getVorteil() const {return BF;}
};

class cH_Beruf_Data : public Handle<const Beruf_Data>
{
protected:
 cH_Beruf_Data() {}
 public:
  cH_Beruf_Data(const Beruf_Data *r) : Handle<const Beruf_Data>(r){}
};
  
