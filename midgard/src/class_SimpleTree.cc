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

#include "class_SimpleTree.hh"
#include <Misc/EntryValueEmptyInt.h>
#include <Misc/EntryValueIntString.h>
#include <Misc/EntryValueIntGermanString.h>
#include <MidgardBasicTree.hh>
#include <Sprache.hh>
#include <Fertigkeiten.hh>
#include <Fertigkeiten_angeboren.hh>
#include <Schrift.hh>
#include "Waffe.hh"
#include "KiDo.hh"
#include "Zauber.hh"
#include "Zauberwerk.hh"
#include "midgard_CG.hh"
#include <Misc/itos.h>

const cH_EntryValue Data_SimpleTree::retEV(const WEV &what) const
{
  switch (what) {
//      case FName: return cH_EntryValueIntString((*MBE)->Name()+" "+(*MBE).Zusatz());
      case FName: return cH_EntryValueIntGermanString((*MBE)->Name()+" "+(*MBE).Zusatz());
      case FErfolgswert: { if((*MBE).What()==MidgardBasicElement::FERTIGKEIT)
                               return cH_EntryValueEmptyInt((*MBE)->FErfolgswert(*abenteurer,MBE)); 
                           else return cH_EntryValueEmptyInt((*MBE).Erfolgswert()); }
      case FWurf: {cH_Fertigkeit_angeborene F((*MBE).getMBE()); return cH_EntryValueIntString(itos(F->Min())+"-"+itos(F->Max()));}
      case FWhat:  return cH_EntryValueIntString((*MBE).What_str());
      case FLernpunkte: return cH_EntryValueEmptyInt((*MBE).Lernpunkte());
      case FLernpunkte0: return cH_EntryValueIntString((*MBE).Lernpunkte());
      case FLernart: return cH_EntryValueIntString((*MBE).LernArt());
      case FPflicht: return cH_EntryValueIntString((*MBE).Pflicht_str());
      case FGrundkenntnis: return cH_EntryValueIntString(cH_Waffe((*MBE).getMBE())->Grundkenntnis());
      case FErfolgswerBonus: { int AB = cH_Fertigkeit((*MBE).getMBE())->AttributBonus(*abenteurer);
                               const int EW=(*MBE)->FErfolgswert(*abenteurer,MBE);
                               if(!AB) return cH_EntryValueEmptyInt(EW);
                               else { std::string s=itos(EW-AB)+"+"+itos(AB);
                                      return cH_EntryValueIntString(s); } }
      case FZauberAP: return cH_EntryValueIntString(cH_Zauber((*MBE).getMBE())->Ap());
      case FAttribut: return cH_EntryValueIntString(cH_Fertigkeit((*MBE).getMBE())->Attribut());
      case FVoraussetung: return cH_EntryValueIntString((*MBE)->Voraussetzung());
      case FSchwierigkeit: return cH_EntryValueIntString(cH_Waffe((*MBE).getMBE())->Schwierigkeit_str());
      case FKosten: return cH_EntryValueEmptyInt((*MBE)->Kosten(*abenteurer));
      case FStandard: return cH_EntryValueIntString((*MBE)->Standard__(*abenteurer));
      case FGelernt: if ((*MBE).Gelernt()) return cH_EntryValueIntString("*"); 
                     else return cH_EntryValue();
      case FPraxispunkt: return cH_EntryValueEmptyInt((*MBE).Praxispunkte());
      case FSteigern: return cH_EntryValueEmptyInt((*MBE).Steigern(*abenteurer));
      case FReduzieren: return cH_EntryValueEmptyInt((*MBE).Reduzieren(*abenteurer));
      case FVerlernen: return cH_EntryValueEmptyInt((*MBE).Verlernen(*abenteurer));
      case FRegion: return cH_EntryValueIntString((*MBE)->RegionString());
      case FUrsprung: return cH_EntryValueIntString(cH_Zauber((*MBE).getMBE())->Ursprung());
      case FArtderSchrift: return cH_EntryValueIntString(cH_Schrift((*MBE).getMBE())->Art_der_Schrift());
   }
 return cH_EntryValue();
}



const cH_EntryValue Data_SimpleTree::Value(guint seqnr,gpointer gp) const
{ 
      MidgardBasicTree::variante Variante = 
               MidgardBasicTree::variante(reinterpret_cast<int>(gp));
      if (Variante==MidgardBasicTree::ANGEBFERT)
       switch((Spalten_ANGEBFERT)seqnr) {
         case WURFaf  : return retEV(FWurf);
         case NAMEaf  : return retEV(FName);
         case WERTaf  : return retEV(FErfolgswert);
        }
      else if (Variante==MidgardBasicTree::GELERNTES)
       switch((Spalten_GELERNTES)seqnr) {
         case ARTgg  : return retEV(FWhat);
         case NAMEgg : return retEV(FName);
         case WERTgg : return retEV(FErfolgswert);
         case LERNPUNKTEgg : return retEV(FLernpunkte); 
         case LERNARTgg : return retEV(FLernart); }
      else if (Variante==MidgardBasicTree::LERNSCHEMA)
       switch((Spalten_LERNSCHEMA)seqnr) {
         case LERNPUNKTEg : return retEV(FLernpunkte0);
         case PFLICHTg : { if ( (*MBE).What()==MidgardBasicElement::FERTIGKEIT)
                                return retEV(FPflicht); 
                           if ( (*MBE).What()==MidgardBasicElement::WAFFE)
                                return retEV(FGrundkenntnis);}
         case NAMEg : return retEV(FName);
         case WERTg : 
             if((*MBE).What()==MidgardBasicElement::FERTIGKEIT) return retEV(FErfolgswerBonus);
             else if((*MBE).What()==MidgardBasicElement::WAFFE) return retEV(FErfolgswert);
             else if((*MBE).What()==MidgardBasicElement::ZAUBER)return retEV(FZauberAP);
         case EIGENSCHAFTg : 
             if ( (*MBE).What()==MidgardBasicElement::FERTIGKEIT) return retEV(FAttribut);
         case VORAUSSETZUNGg : return retEV(FVoraussetung);
         case KOSTENg : 
            if ( (*MBE).What()==MidgardBasicElement::WAFFE) return retEV(FSchwierigkeit);
            return  retEV(FKosten);
         case ARTg : return retEV(FStandard);
         case GELERNTg : return retEV(FGelernt);
        }
      else if (Variante==MidgardBasicTree::LONG_ALT_ || 
               Variante==MidgardBasicTree::SPRACHEN_ALT ||
               Variante==MidgardBasicTree::WAFFE_ALT )
       switch((Spalten_LONG_ALT)seqnr) {
         case NAMEa :  return retEV(FName);
         case WERTa :  return retEV(FErfolgswert);
         case PPa : return retEV(FPraxispunkt);
         case STANDARDa : return retEV(FStandard);
         case STEIGERN : return retEV(FSteigern);
         case REDUZIEREN : return retEV(FReduzieren);
         case VERLERNEN : return retEV(FVerlernen);
         case REGIONa : return retEV(FRegion);
        }
      else if (Variante==MidgardBasicTree::LONG_NEU)
       switch ((Spalten_LONG_NEU)seqnr) {
         case NAMEn : return retEV(FName);
         case WERTn : return retEV(FErfolgswert);
         case LERNKOSTEN : return retEV(FKosten);
         case ART : return retEV(FStandard);
         case VORAUSSETZUNGEN : return retEV(FVoraussetung);
         case REGIONn : return retEV(FRegion);
        }
      else if (Variante==MidgardBasicTree::LONG_NEU_WAFFE)
       switch ((Spalten_LONG_NEU_WAFFE)seqnr) {
         case NAMEnw : return retEV(FName);
         case ARTw : return retEV(FStandard);
         case VORAUSSETZUNGENw : return retEV(FVoraussetung);
         case REGIONnw : return retEV(FRegion);
        }
      else if (Variante==MidgardBasicTree::SPRACHE_NEU)
       switch ((Spalten_SPRACHE_NEU)seqnr) {
         case NAMEsn    : return retEV(FName);
         case SCHRIFTsn : return cH_EntryValueIntString(cH_Sprache((*MBE).getMBE())->Schriften()); 
         case LERNKOSTENsn : return retEV(FKosten);
         case REGIONsn : return retEV(FRegion);
        }
      else if (Variante==MidgardBasicTree::SCHRIFT_ALT)
       switch((Spalten_SCHRIFT_ALT)seqnr) {
         case NAMEsa : return retEV(FName);
         case ARTsa : return retEV(FArtderSchrift);
         case WERTsa : return retEV(FErfolgswert);
         case PPsa : return retEV(FPraxispunkt);
         case STANDARDsa : return retEV(FStandard);
         case STEIGERNs : return retEV(FSteigern);
         case REDUZIERENs :  return retEV(FReduzieren);
         case VERLERNENs :  return retEV(FVerlernen);
         case REGIONsa : return retEV(FRegion);
        }
      else if (Variante==MidgardBasicTree::SCHRIFT_NEU)
       switch ((Spalten_SCHRIFT_NEU)seqnr) {
         case NAMErsn    : return retEV(FName);
         case ARTrsn     : return retEV(FArtderSchrift);
         case KOSTENn_SC : return retEV(FKosten);
         case REGIONrsn  : return retEV(FRegion);
        }
      else if (Variante==MidgardBasicTree::KIDO_ALT || Variante==MidgardBasicTree::KIDO_NEU)
       {cH_KiDo k((*MBE).getMBE());
        switch ((Spalten_KIDO)seqnr) {
         case HOHOa_K    : return cH_EntryValueIntString(k->HoHo());
         case NAMEa_K    : return cH_EntryValueIntString(k->Deutsch());
         case STUFEa_K   : return cH_EntryValueIntString(k->Stufe());
         case APa_K      : return cH_EntryValueEmptyInt(k->Ap());
         case KOSTENa_K  : return retEV(FKosten);
         case STILa_K    : return cH_EntryValueIntString(k->Stil()); 
        }}
      else if (Variante==MidgardBasicTree::WAFFEGRUND_NEU || Variante==MidgardBasicTree::WAFFEGRUND_ALT)
       switch((Spalten_WAFFEGRUND)seqnr) {
         case NAMEa_G : return retEV(FName);
         case STANDARDa_G : return retEV(FStandard);
         case KOSTEN_G : return retEV(FKosten);
         case REGION_G : return retEV(FRegion);
        }
      else if (Variante==MidgardBasicTree::ZAUBER_NEU || Variante==MidgardBasicTree::ZAUBER_ALT )
       { cH_Zauber z((*MBE).getMBE());
       switch ((Spalten_ZAUBER)seqnr) {
         case STUFEn_Z : return cH_EntryValueIntString(z->Stufe());
         case NAMEn_Z : return retEV(FName);
         case URSPRUNGn_Z : return cH_EntryValueIntString(z->Ursprung());
         case KOSTENn_Z : return retEV(FKosten);
         case STANDARDn_Z : return  retEV(FStandard);
         case REGIONn_Z : return retEV(FRegion);
        }}
      else if (Variante==MidgardBasicTree::ZAUBERWERK_NEU || Variante==MidgardBasicTree::ZAUBERWERK_ALT)
       {cH_Zauberwerk z((*MBE).getMBE());
        switch ((Spalten_ZAUBERWERK)seqnr) {
         case STUFEn_ZW : return cH_EntryValueIntString(z->Stufe());
         case NAMEn_ZW : return retEV(FName);
         case ARTn_ZW : return cH_EntryValueIntString(z->Art());    
         case KOSTENn_ZW : return retEV(FKosten);
         case PREISn_ZW : return cH_EntryValueIntString(z->Preis()); 
         case ZEITAUFWANDn_ZW : return cH_EntryValueIntString(z->Zeitaufwand());
         case REGIONn_ZW : return retEV(FRegion);
        }}
      else if (Variante==MidgardBasicTree::WAFFE_LERNSCHEMA)
       {
        cH_Waffe w((*MBE).getMBE());
        switch ((Spalten_WAFFE_LERNSCHEMA)seqnr) {
         case NAME_WL    : return retEV(FName);
         case GRUND_WL   : return retEV(FGrundkenntnis);
         case ART_WL     : return cH_EntryValueIntString(w->Art2());
         case SCHADEN_WL : return cH_EntryValueIntString(w->Schaden(w->Name())+"+"+itos(w->Schaden_Bonus(w->Name())));
        }  
       }
      return cH_EntryValue();
}


void Data_SimpleTree::redisplay(SimpleTree *tree) const
{
  tree->redisplay(this,Data_SimpleTree::WERTa);
  tree->redisplay(this,Data_SimpleTree::PPa);
  tree->redisplay(this,Data_SimpleTree::STEIGERN);
  tree->redisplay(this,Data_SimpleTree::REDUZIEREN);
  tree->redisplay(this,Data_SimpleTree::VERLERNEN);
}
