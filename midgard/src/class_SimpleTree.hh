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

#ifndef _CLASS_FERT_HH
#  define _CLASS_FERT_HH

#include <MidgardBasicElement.hh>
#include <Typen.hh>
#include <Ausnahmen.hh>
#include <rowdata.h>

class Data_SimpleTree : public RowDataBase
{
   cH_MidgardBasicElement MBE;
   vector<cH_Typen> Typ;
   Ausnahmen ausnahmen;
   Grundwerte Werte;
 public:
   Data_SimpleTree(const cH_MidgardBasicElement& _MBE,const vector<cH_Typen>& _Typ, 
         const Ausnahmen& _ausnahmen,const Grundwerte &_Werte) 
   : MBE(_MBE),Typ(_Typ),ausnahmen(_ausnahmen),Werte(_Werte) {}

   enum Spalten_LONG_ALT {NAMEa,WERTa,PPa,STANDARDa,STEIGERN,REDUZIEREN,VERLERNEN} ;
   enum Spalten_LONG_NEU {NAMEn,WERTn,LERNKOSTEN,ART,VORAUSSETZUNGEN};
   enum Spalten_WAFFEGRUND {NAMEa_G,STANDARDa_G,KOSTEN_G};
   enum Spalten_SPRACHE_NEU {NAMEsn,SCHRIFTsn,LERNKOSTENsn};
   enum Spalten_SCHRIFT_ALT {NAMEsa,ARTsa,WERTsa,PPsa,STANDARDsa,STEIGERNs,REDUZIERENs,VERLERNENs} ;
   enum Spalten_SCHRIFT_NEU {NAMErsn,ARTrsn,KOSTENn_SC};
   enum Spalten_KIDO {HOHOa_K,NAMEa_K,STUFEa_K,APa_K,KOSTENa_K,STILa_K,} ;
   enum Spalten_ZAUBER {NAMEn_Z,STUFEn_Z,URSPRUNGn_Z,KOSTENn_Z,STANDARDn_Z};
   enum Spalten_ZAUBERWERK {STUFEn_ZW,NAMEn_ZW,ARTn_ZW,KOSTENn_ZW,PREISn_ZW,ZEITAUFWANDn_ZW};

   virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const;
 const cH_MidgardBasicElement &getMBE() const {return MBE;}

};

class H_Data_SimpleTree : public Handle<Data_SimpleTree>
{
public:
 H_Data_SimpleTree(Data_SimpleTree *r) : Handle<Data_SimpleTree>(r) {}
};


#endif
