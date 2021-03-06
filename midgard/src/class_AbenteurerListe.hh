/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
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
#include <RowDataBase.h>
#include <Abenteurer.hh>

class Data_AbenteurerListe : public RowDataBase
{
      const std::list<VAbenteurer::st_abenteurer>::iterator it;
      const Abenteurer &Char;
      bool saved;

      enum spalten{NAMEA,SAVE,TYP,BEZEICHNUNG,SPEZIES,SPIELER,VER};
   public:
      Data_AbenteurerListe(const VAbenteurer::iterator i) 
         : it(i), Char(it->getAbenteurer()), saved(it->gespeichert()) {}
//      Data_AbenteurerListe(const VAbenteurer::st_abenteurer& c) 
//         : Char(c.abenteurer), saved(c.gespeichert) {}

      virtual cH_EntryValue Value(guint seqnr,gpointer gp) const
       {
         switch(spalten(seqnr))
          {
            case SAVE: 
              { 
                if(saved) return cH_EntryValueIntString("");
                else      return cH_EntryValueIntString("Nein");
              }
            case NAMEA: return cH_EntryValueIntString(Char.Name_Abenteurer());
            case SPIELER: return cH_EntryValueIntString(Char.Name_Spieler());
            case BEZEICHNUNG: return cH_EntryValueIntString(Char.Bezeichnung());
            case SPEZIES: return cH_EntryValueIntString(Char.Spezies()->Name());
            case TYP: {
               std::string s1=Char.Typ1()->Name(Char.Geschlecht());
               std::string s2=Char.Typ2()->Name(Char.Geschlecht());
               if(s2!="") s1+="/"+s2;
               return cH_EntryValueIntString(s1);
              }
            case VER: return cH_EntryValueIntString(Char.Version());
          }
        return cH_EntryValueIntString();
       }
//   Abenteurer &getAbenteurer() const {return const_cast<Abenteurer&>(Char);}
//   const Abenteurer &getAbenteurer() const {return Char;}
     std::list<VAbenteurer::st_abenteurer>::iterator getAbenteurer() const {return it;}

};

class cH_Data_AbenteurerListe : public Handle<const Data_AbenteurerListe>
{
protected:
 cH_Data_AbenteurerListe() {}
 public:
  cH_Data_AbenteurerListe(const Data_AbenteurerListe *r) : Handle<const Data_AbenteurerListe>(r){}
};
  


