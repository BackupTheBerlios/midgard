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

//#include <MidgardBasicElement.hh>
#include <Waffe.hh>
#include <Typen.hh>
#include <rowdata.h>
class midgard_CG;

class Data_SimpleTree : public RowDataBase
{
 private:
//   MBEmlt MBE;
   WaffeBesitz MBE;
   const midgard_CG *hauptfenster; 
 public:
   Data_SimpleTree(const WaffeBesitz& _MBE, const midgard_CG *h) 
   : MBE(_MBE),hauptfenster(h) {}
   Data_SimpleTree(const MBEmlt& _MBE, const midgard_CG *h) 
   : MBE(_MBE),hauptfenster(h) {}

   enum Spalten_ANGEBFERT  {WURFaf,NAMEaf,WERTaf};
   enum Spalten_GELERNTES  {ARTgg,NAMEgg,WERTgg,LERNPUNKTEgg};
   enum Spalten_LERNSCHEMA {LERNPUNKTEg,PFLICHTg,NAMEg,WERTg,EIGENSCHAFTg,VORAUSSETZUNGg,KOSTENg,ARTg,GELERNTg} ;
   enum Spalten_LONG_ALT {NAMEa,WERTa,PPa,STANDARDa,STEIGERN,REDUZIEREN,VERLERNEN,REGIONa} ;
   enum Spalten_LONG_NEU {NAMEn,WERTn,LERNKOSTEN,ART,VORAUSSETZUNGEN,REGIONn};
   enum Spalten_LONG_NEU_WAFFE {NAMEnw,ARTw,VORAUSSETZUNGENw,REGIONnw};
   enum Spalten_WAFFEGRUND {NAMEa_G,STANDARDa_G,KOSTEN_G,REGION_G};
   enum Spalten_SPRACHE_NEU {NAMEsn,SCHRIFTsn,LERNKOSTENsn,REGIONsn};
   enum Spalten_SCHRIFT_ALT {NAMEsa,ARTsa,WERTsa,PPsa,STANDARDsa,STEIGERNs,REDUZIERENs,VERLERNENs,REGIONsa} ;
   enum Spalten_SCHRIFT_NEU {NAMErsn,ARTrsn,KOSTENn_SC,REGIONrsn};
   enum Spalten_KIDO {HOHOa_K,NAMEa_K,STUFEa_K,APa_K,KOSTENa_K,STILa_K,} ;
   enum Spalten_ZAUBER {NAMEn_Z,STUFEn_Z,URSPRUNGn_Z,KOSTENn_Z,STANDARDn_Z,REGIONn_Z};
   enum Spalten_ZAUBERWERK {NAMEn_ZW,STUFEn_ZW,ARTn_ZW,KOSTENn_ZW,PREISn_ZW,ZEITAUFWANDn_ZW,REGIONn_ZW};
   enum Spalten_WAFFE_LERNSCHEMA {ART_WL,NAME_WL,GRUND_WL,SCHADEN_WL};

   virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const;
   enum WEV {FWhat,FName,FErfolgswert,FErfolgswerBonus,
             FWurf,FLernpunkte,FPflicht,
             FGrundkenntnis,FZauberAP,FAttribut,FVoraussetung,FSchwierigkeit,
             FKosten,FStandard,FGelernt,FPraxispunkt,
             FSteigern,FReduzieren,FVerlernen,FRegion,
             FUrsprung,FArtderSchrift};
   const cH_EntryValue retEV(const WEV &what) const;
   const MBEmlt &getMBE() const {return MBE;}
};

class H_Data_SimpleTree : public Handle<Data_SimpleTree>
{
public:
 H_Data_SimpleTree(Data_SimpleTree *r) : Handle<Data_SimpleTree>(r) {}
};


#endif
