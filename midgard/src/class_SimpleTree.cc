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
          { cH_Fertigkeit_angeborene F(MBE.getMBE());
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
                return cH_EntryValueEmptyInt(MBE->FErfolgswert(hauptfenster->getChar().getAbenteurer(),MBE)); 
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
                    return cH_EntryValueIntString(cH_Waffe(MBE.getMBE())->Grundkenntnis()); 
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
               { int AB = cH_Fertigkeit(MBE.getMBE())->AttributBonus(hauptfenster->getWerte());
                 const int EW=MBE->FErfolgswert(hauptfenster->getChar().getAbenteurer(),MBE);
                 if(!AB) return cH_EntryValueEmptyInt(EW); 
                 else { std::string s=itos(EW-AB)+"+"+itos(AB); 
                   return cH_EntryValueIntString(s);
                  }
               }
             else if(MBE->What()==MidgardBasicElement::WAFFE)
                return cH_EntryValueIntString(MBE.Erfolgswert());
             else if(MBE->What()==MidgardBasicElement::ZAUBER)
                return cH_EntryValueIntString(cH_Zauber(MBE.getMBE())->Ap());
           }
         case EIGENSCHAFTg : 
            { if ( MBE->What()==MidgardBasicElement::FERTIGKEIT)
               {
                std::string s=cH_Fertigkeit(MBE.getMBE())->Attribut();
                return cH_EntryValueIntString(s); 
               }
            }
         case VORAUSSETZUNGg : return cH_EntryValueIntString(MBE->Voraussetzung());
         case KOSTENg : 
            if ( MBE->What()==MidgardBasicElement::WAFFE)
               return cH_EntryValueIntString(cH_Waffe(MBE.getMBE())->Schwierigkeit_str()); 
           /* else*/ return cH_EntryValueEmptyInt(MBE->Kosten(hauptfenster->getChar().getAbenteurer())); 
         case ARTg : 
            return cH_EntryValueIntString(MBE->Standard__(hauptfenster->getChar().getAbenteurer())); 
         case GELERNTg : 
            if (MBE.Gelernt()) return cH_EntryValueIntString("*"); 
            else return cH_EntryValueIntString("");
        }
      else if (Variante==MidgardBasicTree::LONG_ALT_ || 
               Variante==MidgardBasicTree::SPRACHEN_ALT ||
               Variante==MidgardBasicTree::WAFFE_ALT )
       switch((Spalten_LONG_ALT)seqnr) {
         case NAMEa : 
           {
             return cH_EntryValueIntString(MBE->Name()+" "+MBE.Zusatz());
           }
         case WERTa : 
           {
             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
                return cH_EntryValueEmptyInt(MBE->FErfolgswert(hauptfenster->getChar().getAbenteurer(),MBE)); 
             else
                return cH_EntryValueIntString(MBE.Erfolgswert());
           }
         case PPa : return cH_EntryValueEmptyInt(MBE.Praxispunkte()); 
         case STANDARDa : return cH_EntryValueIntString(MBE->Standard__(hauptfenster->getChar().getAbenteurer()));
         case STEIGERN : return cH_EntryValueEmptyInt(MBE.Steigern(hauptfenster->getChar().getAbenteurer()));
         case REDUZIEREN : return cH_EntryValueEmptyInt(MBE.Reduzieren(hauptfenster->getChar().getAbenteurer()));
         case VERLERNEN : return cH_EntryValueEmptyInt(MBE.Verlernen(hauptfenster->getChar().getAbenteurer())); 
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
                return cH_EntryValueEmptyInt(MBE->FErfolgswert(hauptfenster->getChar().getAbenteurer(),MBE)); 
             else
                return cH_EntryValueIntString(MBE.Erfolgswert());
           }
         case LERNKOSTEN : return cH_EntryValueEmptyInt(MBE->Kosten(hauptfenster->getChar().getAbenteurer()));
         case ART : return cH_EntryValueIntString(MBE->Standard__(hauptfenster->getChar().getAbenteurer()));
         case VORAUSSETZUNGEN : return cH_EntryValueIntString(MBE->Voraussetzung());
         case REGIONn : return cH_EntryValueIntString(MBE->RegionString(hauptfenster->getCDatabase())); 
        }
      else if (Variante==MidgardBasicTree::LONG_NEU_WAFFE)
       switch ((Spalten_LONG_NEU_WAFFE)seqnr) {
         case NAMEnw : return cH_EntryValueIntString(MBE->Name());
         case ARTw : return cH_EntryValueIntString(MBE->Standard__(hauptfenster->getChar().getAbenteurer()));
         case VORAUSSETZUNGENw : return cH_EntryValueIntString(MBE->Voraussetzung());
         case REGIONnw : return cH_EntryValueIntString(MBE->RegionString(hauptfenster->getCDatabase())); 
        }
      else if (Variante==MidgardBasicTree::SPRACHE_NEU)
       switch ((Spalten_SPRACHE_NEU)seqnr) {
         case NAMEsn    : return cH_EntryValueIntString(MBE->Name());
         case SCHRIFTsn : return cH_EntryValueIntString(cH_Sprache(MBE.getMBE())->Schriften()); 
         case LERNKOSTENsn : return cH_EntryValueEmptyInt(MBE->Kosten(hauptfenster->getChar().getAbenteurer()));
         case REGIONsn : return cH_EntryValueIntString(MBE->RegionString(hauptfenster->getCDatabase())); 
        }
      else if (Variante==MidgardBasicTree::SCHRIFT_ALT)
       switch((Spalten_SCHRIFT_ALT)seqnr) {
         case NAMEsa : return cH_EntryValueIntString(MBE->Name());
         case ARTsa : return cH_EntryValueIntString(cH_Schrift(MBE.getMBE())->Art_der_Schrift());
         case WERTsa : return cH_EntryValueIntString(MBE.Erfolgswert());
         case PPsa : return cH_EntryValueEmptyInt(MBE.Praxispunkte()); 
         case STANDARDsa : return cH_EntryValueIntString(MBE->Standard__(hauptfenster->getChar().getAbenteurer()));
         case STEIGERNs : return cH_EntryValueEmptyInt(MBE.Steigern(hauptfenster->getChar().getAbenteurer()));
         case REDUZIERENs : return cH_EntryValueEmptyInt(MBE.Reduzieren(hauptfenster->getChar().getAbenteurer()));
         case VERLERNENs : return cH_EntryValueEmptyInt(MBE.Verlernen(hauptfenster->getChar().getAbenteurer())); 
         case REGIONsa : return cH_EntryValueIntString(MBE->RegionString(hauptfenster->getCDatabase())); 
        }
      else if (Variante==MidgardBasicTree::SCHRIFT_NEU)
       switch ((Spalten_SCHRIFT_NEU)seqnr) {
         case NAMErsn    : return cH_EntryValueIntString(MBE->Name());
         case ARTrsn     : return cH_EntryValueIntString(cH_Schrift(MBE.getMBE())->Art_der_Schrift());
         case KOSTENn_SC : return cH_EntryValueEmptyInt(MBE->Kosten(hauptfenster->getChar().getAbenteurer()));
         case REGIONrsn  : return cH_EntryValueIntString(MBE->RegionString(hauptfenster->getCDatabase())); 
        }
      else if (Variante==MidgardBasicTree::KIDO_ALT || Variante==MidgardBasicTree::KIDO_NEU)
       {cH_KiDo k(MBE.getMBE());
        switch ((Spalten_KIDO)seqnr) {
         case HOHOa_K    : return cH_EntryValueIntString(k->HoHo());
         case NAMEa_K    : return cH_EntryValueIntString(k->Deutsch());
         case STUFEa_K   : return cH_EntryValueIntString(k->Stufe());
         case APa_K      : return cH_EntryValueEmptyInt(k->Ap());
         case KOSTENa_K  : return cH_EntryValueEmptyInt(MBE->Kosten(hauptfenster->getChar().getAbenteurer()));
         case STILa_K    : return cH_EntryValueIntString(k->Stil()); 
        }}
      else if (Variante==MidgardBasicTree::WAFFEGRUND_NEU || Variante==MidgardBasicTree::WAFFEGRUND_ALT)
       switch((Spalten_WAFFEGRUND)seqnr) {
         case NAMEa_G : return cH_EntryValueIntString(MBE->Name());
         case STANDARDa_G : return cH_EntryValueIntString(MBE->Standard__(hauptfenster->getChar().getAbenteurer()));
         case KOSTEN_G : return cH_EntryValueEmptyInt(MBE->Kosten(hauptfenster->getChar().getAbenteurer())); 
         case REGION_G : return cH_EntryValueIntString(MBE->RegionString(hauptfenster->getCDatabase())); 
        }
      else if (Variante==MidgardBasicTree::ZAUBER_NEU || Variante==MidgardBasicTree::ZAUBER_ALT )
       { cH_Zauber z(MBE.getMBE());
       switch ((Spalten_ZAUBER)seqnr) {
         case STUFEn_Z : return cH_EntryValueIntString(z->Stufe());
         case NAMEn_Z : return cH_EntryValueIntString(MBE->Name());
         case URSPRUNGn_Z : return cH_EntryValueIntString(z->Ursprung());
         case KOSTENn_Z : return cH_EntryValueEmptyInt(MBE->Kosten(hauptfenster->getChar().getAbenteurer())*cH_Zauber(MBE.getMBE())->SpruchrolleFaktor());
         case STANDARDn_Z : return cH_EntryValueIntString(MBE->Standard__(hauptfenster->getChar().getAbenteurer()));
         case REGIONn_Z : return cH_EntryValueIntString(MBE->RegionString(hauptfenster->getCDatabase())); 
        }}
      else if (Variante==MidgardBasicTree::ZAUBERWERK_NEU || Variante==MidgardBasicTree::ZAUBERWERK_ALT)
       {cH_Zauberwerk z(MBE.getMBE());
        switch ((Spalten_ZAUBERWERK)seqnr) {
         case STUFEn_ZW : return cH_EntryValueIntString(z->Stufe());
         case NAMEn_ZW : return cH_EntryValueIntString(MBE->Name());  
         case ARTn_ZW : return cH_EntryValueIntString(z->Art());    
         case KOSTENn_ZW : return cH_EntryValueEmptyInt(MBE->Kosten(hauptfenster->getChar().getAbenteurer()));
         case PREISn_ZW : return cH_EntryValueIntString(z->Preis()); 
         case ZEITAUFWANDn_ZW : return cH_EntryValueIntString(z->Zeitaufwand());
         case REGIONn_ZW : return cH_EntryValueIntString(MBE->RegionString(hauptfenster->getCDatabase())); 
        }}
      else if (Variante==MidgardBasicTree::WAFFE_LERNSCHEMA)
       {
        cH_Waffe w(MBE.getMBE());
        switch ((Spalten_WAFFE_LERNSCHEMA)seqnr) {
         case NAME_WL    : return cH_EntryValueIntString(MBE->Name());
         case GRUND_WL   : return cH_EntryValueIntString(w->Grundkenntnis());
         case ART_WL     : return cH_EntryValueIntString(w->Art2());
         case SCHADEN_WL : return cH_EntryValueIntString(w->Schaden(w->Name())+"+"+itos(w->Schaden_Bonus(w->Name())));
        }  
       }
      return cH_EntryValueIntString("?");
}
