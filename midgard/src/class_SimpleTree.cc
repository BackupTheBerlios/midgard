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
#include <Aux/EntryValueEmptyInt.h>
#include <Aux/EntryValueIntString.h>
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

const cH_EntryValue Data_SimpleTree::Value(guint seqnr,gpointer gp) const
{ 
      MidgardBasicTree::variante Variante = 
               MidgardBasicTree::variante(reinterpret_cast<int>(gp));
      if (Variante==MidgardBasicTree::ANGEBFERT)
       switch((Spalten_ANGEBFERT)seqnr) {
         case WURFaf  : 
          { cH_Fertigkeit_angeborene F(MBE);
            return cH_EntryValueIntString(itos(F->Min())+"-"+itos(F->Max()));
          }
         case NAMEaf  : return cH_EntryValueIntString(MBE->Name()+" "+MBE.Zusatz());
         case WERTaf  : return cH_EntryValueEmptyInt(MBE.Erfolgswert());
        }
      else if (Variante==MidgardBasicTree::GELERNTES)
       switch((Spalten_GELERNTES)seqnr) {
         case ARTgg  : 
               return cH_EntryValueIntString(MBE->What_str()); 
         case NAMEgg : 
               return cH_EntryValueIntString(MBE->Name()+" "+MBE.Zusatz());
         case WERTgg : 
           {
             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
                return cH_EntryValueEmptyInt(MBE->FErfolgswert(hauptfenster->getCChar().getAbenteurer(),MBE)); 
             else
                return cH_EntryValueEmptyInt(MBE.Erfolgswert());
           }
         case LERNPUNKTEgg : 
            return cH_EntryValueEmptyInt(MBE.Lernpunkte()); 
        }
      else if (Variante==MidgardBasicTree::LERNSCHEMA)
       switch((Spalten_LERNSCHEMA)seqnr) {
         case LERNPUNKTEg : return cH_EntryValueIntString(MBE.Lernpunkte()); 
         case PFLICHTg : 
            { if ( MBE->What()==MidgardBasicElement::FERTIGKEIT)
                       return cH_EntryValueIntString(MBE.Pflicht_str()); 
              if ( MBE->What()==MidgardBasicElement::WAFFE)
                    return cH_EntryValueIntString(cH_Waffe(MBE)->Grundkenntnis()); 
            }
         case NAMEg : 
           {
             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
                return cH_EntryValueIntString(MBE->Name()+" "+MBE.Zusatz());
             else
                return cH_EntryValueIntString(MBE->Name());
           }
         case WERTg : 
           {
             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
               { int AB = cH_Fertigkeit(MBE)->AttributBonus(hauptfenster->getCWerte());
                 const int EW=MBE->FErfolgswert(hauptfenster->getCChar().getAbenteurer(),MBE);
                 if(!AB) return cH_EntryValueEmptyInt(EW); 
                 else { std::string s=itos(EW-AB)+"+"+itos(AB); 
                   return cH_EntryValueIntString(s);
                  }
               }
             else if(MBE->What()==MidgardBasicElement::WAFFE)
                return cH_EntryValueIntString(MBE.Erfolgswert());
             else if(MBE->What()==MidgardBasicElement::ZAUBER)
                return cH_EntryValueIntString(cH_Zauber(MBE)->Ap());
           }
         case EIGENSCHAFTg : 
            { if ( MBE->What()==MidgardBasicElement::FERTIGKEIT)
               {
                std::string s=cH_Fertigkeit(MBE)->Attribut();
//                int ab=cH_Fertigkeit(MBE)->AttributBonus(hauptfenster->getCWerte());
//                if (ab) s+= "(+"+itos(ab)+")";
                return cH_EntryValueIntString(s); 
               }
            }
         case VORAUSSETZUNGg :
           {  
            return cH_EntryValueIntString(MBE->Voraussetzung());
/*
            if ( MBE->What()==MidgardBasicElement::WAFFE)
               return cH_EntryValueIntString(cH_Waffe(MBE)->Voraussetzung()); 
            if ( MBE->What()==MidgardBasicElement::FERTIGKEIT)
               return cH_EntryValueIntString(cH_Fertigkeit(MBE)->Voraussetzung()); 
*/
           }
         case KOSTENg : 
            if ( MBE->What()==MidgardBasicElement::WAFFE)
               return cH_EntryValueIntString(cH_Waffe(MBE)->Schwierigkeit_str()); 
           /* else*/ return cH_EntryValueEmptyInt(MBE->Kosten(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp())); 
         case ARTg : 
            return cH_EntryValueIntString(MBE->Standard__(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp())); 
         case GELERNTg : 
            if (MBE.Gelernt()) return cH_EntryValueIntString("*"); 
            else return cH_EntryValueIntString("");
        }
      else if (Variante==MidgardBasicTree::LONG_ALT)
       switch((Spalten_LONG_ALT)seqnr) {
         case NAMEa : 
           {
//             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
             return cH_EntryValueIntString(MBE->Name()+" "+MBE.Zusatz());
//             else
//                return cH_EntryValueIntString(MBE->Name());
           }
         case WERTa : 
           {
             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
                return cH_EntryValueEmptyInt(MBE->FErfolgswert(hauptfenster->getCChar().getAbenteurer(),MBE)); 
             else
                return cH_EntryValueIntString(MBE.Erfolgswert());
           }
         case PPa : return cH_EntryValueEmptyInt(MBE.Praxispunkte()); 
         case STANDARDa : return cH_EntryValueIntString(MBE->Standard__(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp()));
         case STEIGERN : return cH_EntryValueEmptyInt(MBE.Steigern(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp()));
         case REDUZIEREN : return cH_EntryValueEmptyInt(MBE.Reduzieren(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp()));
         case VERLERNEN : return cH_EntryValueEmptyInt(MBE.Verlernen(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp())); 
         case REGIONa : return cH_EntryValueIntString(MBE->RegionString(hauptfenster->getCDatabase())); 
        }
      else if (Variante==MidgardBasicTree::LONG_NEU)
       switch ((Spalten_LONG_NEU)seqnr) {
         case NAMEn : 
           {
             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
                return cH_EntryValueIntString(MBE->Name()+" "+MBE.Zusatz());
             else
                return cH_EntryValueIntString(MBE->Name());
           }
         case WERTn : 
           {
             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
                return cH_EntryValueEmptyInt(MBE->FErfolgswert(hauptfenster->getCChar().getAbenteurer(),MBE)); 
             else
                return cH_EntryValueIntString(MBE.Erfolgswert());
           }
         case LERNKOSTEN : return cH_EntryValueEmptyInt(MBE->Kosten(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp()));
         case ART : return cH_EntryValueIntString(MBE->Standard__(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp()));
         case VORAUSSETZUNGEN : 
           {
               return cH_EntryValueIntString(MBE->Voraussetzung());
//             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
//               return cH_EntryValueIntString(cH_Fertigkeit(MBE)->Voraussetzung());
//             else
//               return cH_EntryValueIntString("");
           }
         case REGIONn : return cH_EntryValueIntString(MBE->RegionString(hauptfenster->getCDatabase())); 
        }
      else if (Variante==MidgardBasicTree::LONG_NEU_WAFFE)
       switch ((Spalten_LONG_NEU_WAFFE)seqnr) {
         case NAMEnw : return cH_EntryValueIntString(MBE->Name());
         case ARTw : return cH_EntryValueIntString(MBE->Standard__(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp()));
//         case VORAUSSETZUNGENw : return cH_EntryValueIntString(cH_Waffe(MBE)->Voraussetzung());
         case VORAUSSETZUNGENw : return cH_EntryValueIntString(MBE->Voraussetzung());
         case REGIONnw : return cH_EntryValueIntString(MBE->RegionString(hauptfenster->getCDatabase())); 
        }
      else if (Variante==MidgardBasicTree::SPRACHE_NEU)
       switch ((Spalten_SPRACHE_NEU)seqnr) {
         case NAMEsn    : return cH_EntryValueIntString(MBE->Name());
         case SCHRIFTsn : return cH_EntryValueIntString(cH_Sprache(MBE)->Schriften()); 
         case LERNKOSTENsn : return cH_EntryValueEmptyInt(MBE->Kosten(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp()));
        }
      else if (Variante==MidgardBasicTree::SCHRIFT_ALT)
       switch((Spalten_SCHRIFT_ALT)seqnr) {
         case NAMEsa : return cH_EntryValueIntString(MBE->Name());
         case ARTsa : return cH_EntryValueIntString(cH_Schrift(MBE)->Art_der_Schrift());
         case WERTsa : return cH_EntryValueIntString(MBE.Erfolgswert());
         case PPsa : return cH_EntryValueEmptyInt(MBE.Praxispunkte()); 
         case STANDARDsa : return cH_EntryValueIntString(MBE->Standard__(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp()));
         case STEIGERNs : return cH_EntryValueEmptyInt(MBE.Steigern(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp()));
         case REDUZIERENs : return cH_EntryValueEmptyInt(MBE.Reduzieren(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp()));
         case VERLERNENs : return cH_EntryValueEmptyInt(MBE.Verlernen(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp())); 
        }
      else if (Variante==MidgardBasicTree::SCHRIFT_NEU)
       switch ((Spalten_SCHRIFT_NEU)seqnr) {
         case NAMErsn    : return cH_EntryValueIntString(MBE->Name());
         case ARTrsn     : return cH_EntryValueIntString(cH_Schrift(MBE)->Art_der_Schrift());
         case KOSTENn_SC : return cH_EntryValueEmptyInt(MBE->Kosten(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp()));
        }
      else if (Variante==MidgardBasicTree::KIDO)
        switch ((Spalten_KIDO)seqnr) {
         case HOHOa_K    : return cH_EntryValueIntString(cH_KiDo(MBE)->HoHo());
         case NAMEa_K    : return cH_EntryValueIntString(cH_KiDo(MBE)->Deutsch());
         case STUFEa_K   : return cH_EntryValueIntString(cH_KiDo(MBE)->Stufe());
         case APa_K      : return cH_EntryValueEmptyInt(cH_KiDo(MBE)->Ap());
         case KOSTENa_K  : return cH_EntryValueEmptyInt(MBE->Kosten(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp()));
         case STILa_K    : return cH_EntryValueIntString(cH_KiDo(MBE)->Stil()); 
        }
      else if (Variante==MidgardBasicTree::WAFFEGRUND)
       switch((Spalten_WAFFEGRUND)seqnr) {
         case NAMEa_G : return cH_EntryValueIntString(MBE->Name());
         case STANDARDa_G : return cH_EntryValueIntString(MBE->Standard__(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp()));
         case KOSTEN_G : return cH_EntryValueEmptyInt(MBE->Kosten(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp())); 
         case REGION_G : return cH_EntryValueIntString(MBE->RegionString(hauptfenster->getCDatabase())); 
        }
      else if (Variante==MidgardBasicTree::ZAUBER)
      switch ((Spalten_ZAUBER)seqnr) {
         case STUFEn_Z : return cH_EntryValueIntString(cH_Zauber(MBE)->Stufe());
         case NAMEn_Z : return cH_EntryValueIntString(MBE->Name());
         case URSPRUNGn_Z : return cH_EntryValueIntString(cH_Zauber(MBE)->Ursprung());
         case KOSTENn_Z : return cH_EntryValueEmptyInt(MBE->Kosten(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp())*cH_Zauber(MBE)->SpruchrolleFaktor());
         case STANDARDn_Z : return cH_EntryValueIntString(MBE->Standard__(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp()));
         case REGIONn_Z : return cH_EntryValueIntString(MBE->RegionString(hauptfenster->getCDatabase())); 
        }
      else if (Variante==MidgardBasicTree::ZAUBERWERK)
      switch ((Spalten_ZAUBERWERK)seqnr) {
         case STUFEn_ZW : return cH_EntryValueIntString(cH_Zauberwerk(MBE)->Stufe());
         case NAMEn_ZW : return cH_EntryValueIntString(MBE->Name());  
         case ARTn_ZW : return cH_EntryValueIntString(cH_Zauberwerk(MBE)->Art());    
         case KOSTENn_ZW : return cH_EntryValueEmptyInt(MBE->Kosten(hauptfenster->getCWerte(),hauptfenster->getCChar().getVTyp()));
         case PREISn_ZW : return cH_EntryValueIntString(cH_Zauberwerk(MBE)->Preis()); 
         case ZEITAUFWANDn_ZW : return cH_EntryValueIntString(cH_Zauberwerk(MBE)->Zeitaufwand());
         case REGIONn_ZW : return cH_EntryValueIntString(MBE->RegionString(hauptfenster->getCDatabase())); 
        }
      else if (Variante==MidgardBasicTree::WAFFE_LERNSCHEMA)
       {
//        cH_WaffeBesitz wb=cH_WaffeBesitz(MBE);
//        WaffeBesitz wb(MBE);
        cH_Waffe w(MBE);//=wb.Waffe();
        switch ((Spalten_WAFFE_LERNSCHEMA)seqnr) {
         case NAME_WL    : return cH_EntryValueIntString(MBE->Name());
         case GRUND_WL   : return cH_EntryValueIntString(w->Grundkenntnis());
         case ART_WL     : return cH_EntryValueIntString(w->Art2());
         case SCHADEN_WL : return cH_EntryValueIntString(w->Schaden(w->Name())+"+"+itos(w->Schaden_Bonus(w->Name())));
//         case SCHADEN_WL : return cH_EntryValueIntString(wb.Schaden(hauptfenster->getCWerte(),MBE->Name()));
        }  
       }
      return cH_EntryValueIntString("?");
}
