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

#ifndef _DATA_PREISE_HH
#  define _DATA_PREISE_HH

#include "table_ausruestung.hh"
#include <Misc/itos.h>
#include <Misc/EntryValueEmptyInt.h>
#include <Misc/EntryValueFixed.h>
#include "dtos1.h"

class Data_NewPreis : public RowDataBase
{
      cH_Preise ware;
      double kosten;
      mutable std::map<table_ausruestung::e_spalten,PreiseNewMod::st_preismod> M;
  public:
     Data_NewPreis(const cH_Preise P) : ware(P),kosten(P->Kosten()) {}
     Data_NewPreis(const cH_Preise P,const std::map<table_ausruestung::e_spalten,PreiseNewMod::st_preismod> &m) 
         : ware(P),kosten(P->Kosten()),M(m) 
         {
           for(std::map<table_ausruestung::e_spalten,PreiseNewMod::st_preismod>::const_iterator i=M.begin();i!=M.end();++i)
                kosten*=i->second.preis_faktor;
         }
      
     enum spalten {ART,ART2,NAME,V_FARBE,V_MATERIAL,V_STAND,GEWICHT,KOSTEN};
     
     virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const 
      {
        std::map<table_ausruestung::e_spalten,PreiseNewMod::st_preismod> M_=
            const_cast<std::map<table_ausruestung::e_spalten,PreiseNewMod::st_preismod>&>(M);
        switch(spalten(seqnr)) {
           case ART: return cH_EntryValueIntString(ware->Art());
           case ART2: return cH_EntryValueIntString(ware->Art2());
           case NAME: return cH_EntryValueIntString(ware->Name());
           case GEWICHT: return cH_EntryValueIntString(dtos(ware->Gewicht()));
           case V_STAND: return cH_EntryValueIntString(M_[table_ausruestung::Stand].spezifikation);
           case V_MATERIAL: return cH_EntryValueIntString(M_[table_ausruestung::Material].spezifikation);
           case V_FARBE: return cH_EntryValueIntString(M_[table_ausruestung::Farbe].spezifikation);
           case KOSTEN: return cH_EntryValueIntString(dtos(kosten)+" "+ware->Einheit());
         }
        return cH_EntryValueIntString();
      }
   cH_Preise Ware() const {return ware;}
   double Kosten() const {return kosten;}
   std::map<table_ausruestung::e_spalten,PreiseNewMod::st_preismod> &
         getMod() const {return M;}

};
class cH_Data_NewPreis : public Handle<const Data_NewPreis>
{
public:
 cH_Data_NewPreis(const Data_NewPreis *r) : Handle<const Data_NewPreis>(r) {}
};

#endif
