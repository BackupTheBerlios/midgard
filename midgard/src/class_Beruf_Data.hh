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

#include <Aux/EntryValueIntString.h>
#include <rowdata.h>
class Beruf_Data : public RowDataBase
{
      int kat;
      std::string beruf,fert;
      bool gelernte_fertigkeit;

      std::string kat_to_str(const int kat) const
         { if (kat==1) return "I";
           else if (kat==2) return "II";
           else if (kat==3) return "III";
           else if (kat==4) return "IV";
           else return "?";
         }

   public:
      Beruf_Data(const int _kat,
                 const std::string &_beruf,
                 const std::string &_fert,
                 const bool _gelernte_fertigkeit)  
         :kat(_kat),beruf(_beruf),fert(_fert),
            gelernte_fertigkeit(_gelernte_fertigkeit) {}
         
      enum spalten{BERUF,GELERNT,FERT,KAT};
      
      virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const
       {
         switch(spalten(seqnr))
          {
            case KAT: return cH_EntryValueIntString(kat_to_str(kat));
            case BERUF: return cH_EntryValueIntString(beruf);
            case FERT: return cH_EntryValueIntString(fert);
            case GELERNT: {
               if(gelernte_fertigkeit) return cH_EntryValueIntString("*");
               else return cH_EntryValueIntString("");
             }
          }
        return cH_EntryValueIntString("?");
       }
      int Kat() const {return kat;}
      std::string Beruf() const {return beruf;}
      std::string Fert() const {return fert;}
      bool Gelernt() const {return gelernte_fertigkeit;}
};
class cH_Beruf_Data : public Handle<const Beruf_Data>
{
protected:
 cH_Beruf_Data() {}
 public:
  cH_Beruf_Data(const Beruf_Data *r) : Handle<const Beruf_Data>(r){}
};
  
