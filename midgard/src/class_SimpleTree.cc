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
#include <Schrift.hh>
#include "Waffe.hh"
#include "KiDo.hh"
#include "Zauber.hh"
#include "Zauberwerk.hh"

const cH_EntryValue Data_SimpleTree::Value(guint seqnr,gpointer gp) const
    { 
      MidgardBasicTree::variante Variante = 
               MidgardBasicTree::variante(reinterpret_cast<int>(gp));
      if (Variante==MidgardBasicTree::GELERNTES)
       switch((Spalten_GELERNTES)seqnr) {
         case ARTgg : return cH_EntryValueIntString(MBE->What_str()); 
         case NAMEgg : 
           {
             return cH_EntryValueIntString(MBE->Name()+" "+MBE->Zusatz());
/*
             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
                return cH_EntryValueIntString(MBE->Name()+" "+cH_Fertigkeit(MBE)->Zusatz());
             else
                return cH_EntryValueIntString(MBE->Name());
*/
           }
         case WERTgg : 
           {
             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
                return cH_EntryValueEmptyInt(cH_Fertigkeit(MBE)->FErfolgswert(Werte)); 
             else
                return cH_EntryValueEmptyInt(MBE->Erfolgswert());
           }
         case LERNPUNKTEgg : return cH_EntryValueEmptyInt(MBE->Lernpunkte()); 
        }
      if (Variante==MidgardBasicTree::LERNSCHEMA)
       switch((Spalten_LERNSCHEMA)seqnr) {
         case LERNPUNKTEg : return cH_EntryValueIntString(MBE->Lernpunkte()); 
         case PFLICHTg : 
            { if ( MBE->What()==MidgardBasicElement::FERTIGKEIT)
                       return cH_EntryValueIntString(cH_Fertigkeit(MBE)->Pflicht_str()); 
              if ( MBE->What()==MidgardBasicElement::WAFFE)
                    return cH_EntryValueIntString(cH_Waffe(MBE)->Grundkenntnis()); 
            }
         case NAMEg : 
           {
             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
                return cH_EntryValueIntString(MBE->Name()+" "+cH_Fertigkeit(MBE)->Zusatz());
             else
                return cH_EntryValueIntString(MBE->Name());
           }
         case WERTg : 
           {
             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
                return cH_EntryValueEmptyInt(cH_Fertigkeit(MBE)->FErfolgswert(Werte)); 
             else if(MBE->What()==MidgardBasicElement::WAFFE)
                return cH_EntryValueIntString(MBE->Erfolgswert());
             else if(MBE->What()==MidgardBasicElement::ZAUBER)
                return cH_EntryValueIntString(cH_Zauber(MBE)->Ap());
           }
         case EIGENSCHAFTg : 
            { if ( MBE->What()==MidgardBasicElement::FERTIGKEIT)
                       return cH_EntryValueIntString(cH_Fertigkeit(MBE)->Attribut()); 
            }
         case VORAUSSETZUNGg :
           {  
            if ( MBE->What()==MidgardBasicElement::WAFFE)
               return cH_EntryValueIntString(cH_Waffe(MBE)->Voraussetzung()); 
            if ( MBE->What()==MidgardBasicElement::FERTIGKEIT)
               return cH_EntryValueIntString(cH_Fertigkeit(MBE)->Voraussetzung()); 
           }
         case KOSTENg : 
            if ( MBE->What()==MidgardBasicElement::WAFFE)
               return cH_EntryValueIntString(cH_Waffe(MBE)->Schwierigkeit_str()); 
           /* else*/ return cH_EntryValueIntString(MBE->Kosten(Typ,ausnahmen)); 
        }
      if (Variante==MidgardBasicTree::LONG_ALT)
       switch((Spalten_LONG_ALT)seqnr) {
         case NAMEa : 
           {
//             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
             return cH_EntryValueIntString(MBE->Name()+" "+MBE->Zusatz());
//             else
//                return cH_EntryValueIntString(MBE->Name());
           }
         case WERTa : 
           {
             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
                return cH_EntryValueEmptyInt(cH_Fertigkeit(MBE)->FErfolgswert(Werte)); 
             else
                return cH_EntryValueIntString(MBE->Erfolgswert());
           }
         case PPa : return cH_EntryValueEmptyInt(MBE->Praxispunkte()); 
         case STANDARDa : return cH_EntryValueIntString(MBE->Standard__(Typ,ausnahmen));
         case STEIGERN : return cH_EntryValueEmptyInt(MBE->Steigern(Typ,ausnahmen));
         case REDUZIEREN : return cH_EntryValueEmptyInt(MBE->Reduzieren(Typ,ausnahmen));
         case VERLERNEN : return cH_EntryValueEmptyInt(MBE->Verlernen(Typ,ausnahmen)); 
        }
      if (Variante==MidgardBasicTree::LONG_NEU)
       switch ((Spalten_LONG_NEU)seqnr) {
         case NAMEn : 
           {
             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
                return cH_EntryValueIntString(MBE->Name()+" "+cH_Fertigkeit(MBE)->Zusatz());
             else
                return cH_EntryValueIntString(MBE->Name());
           }
         case WERTn : 
           {
             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
                return cH_EntryValueEmptyInt(cH_Fertigkeit(MBE)->FErfolgswert(Werte)); 
             else
                return cH_EntryValueIntString(MBE->Erfolgswert());
           }
         case LERNKOSTEN : 
          {
             if(MBE->What()==MidgardBasicElement::WAFFE)
                return cH_EntryValueEmptyInt(0);//MBE->Steigern(Typ,ausnahmen)); 
             else
                return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
          }
         case ART : return cH_EntryValueIntString(MBE->Standard__(Typ,ausnahmen));
         case VORAUSSETZUNGEN : 
           {
             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
               return cH_EntryValueIntString(cH_Fertigkeit(MBE)->Voraussetzung());
             else if(MBE->What()==MidgardBasicElement::WAFFE)
               return cH_EntryValueIntString(cH_Waffe(MBE)->Voraussetzung());
             else
               return cH_EntryValueIntString("");
           }
        }
      if (Variante==MidgardBasicTree::SPRACHE_NEU)
       switch ((Spalten_SPRACHE_NEU)seqnr) {
         case NAMEsn    : return cH_EntryValueIntString(MBE->Name());
         case SCHRIFTsn : return cH_EntryValueIntString(cH_Sprache(MBE)->Schriften()); 
         case LERNKOSTENsn : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
        }
      if (Variante==MidgardBasicTree::SCHRIFT_ALT)
       switch((Spalten_SCHRIFT_ALT)seqnr) {
         case NAMEsa : return cH_EntryValueIntString(MBE->Name());
         case ARTsa : return cH_EntryValueIntString(cH_Schrift(MBE)->Art_der_Schrift());
         case WERTsa : return cH_EntryValueIntString(MBE->Erfolgswert());
         case PPsa : return cH_EntryValueEmptyInt(MBE->Praxispunkte()); 
         case STANDARDsa : return cH_EntryValueIntString(MBE->Standard__(Typ,ausnahmen));
         case STEIGERNs : return cH_EntryValueEmptyInt(MBE->Steigern(Typ,ausnahmen));
         case REDUZIERENs : return cH_EntryValueEmptyInt(MBE->Reduzieren(Typ,ausnahmen));
         case VERLERNENs : return cH_EntryValueEmptyInt(MBE->Verlernen(Typ,ausnahmen)); 
        }
      if (Variante==MidgardBasicTree::SCHRIFT_NEU)
       switch ((Spalten_SCHRIFT_NEU)seqnr) {
         case NAMErsn    : return cH_EntryValueIntString(MBE->Name());
         case ARTrsn     : return cH_EntryValueIntString(cH_Schrift(MBE)->Art_der_Schrift());
         case KOSTENn_SC : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
        }
      if (Variante==MidgardBasicTree::KIDO)
        switch ((Spalten_KIDO)seqnr) {
         case HOHOa_K    : return cH_EntryValueIntString(cH_KiDo(MBE)->HoHo());
         case NAMEa_K    : return cH_EntryValueIntString(cH_KiDo(MBE)->Deutsch());
         case STUFEa_K   : return cH_EntryValueIntString(cH_KiDo(MBE)->Stufe());
         case APa_K      : return cH_EntryValueEmptyInt(cH_KiDo(MBE)->Ap());
         case KOSTENa_K  : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
         case STILa_K    : return cH_EntryValueIntString(cH_KiDo(MBE)->Stil()); 
        }
      if (Variante==MidgardBasicTree::WAFFEGRUND)
       switch((Spalten_WAFFEGRUND)seqnr) {
         case NAMEa_G : return cH_EntryValueIntString(MBE->Name());
         case STANDARDa_G : return cH_EntryValueIntString(MBE->Standard__(Typ,ausnahmen));
         case KOSTEN_G : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen)); 
        }
      if (Variante==MidgardBasicTree::ZAUBER)
      switch ((Spalten_ZAUBER)seqnr) {
         case STUFEn_Z : return cH_EntryValueIntString(cH_Zauber(MBE)->Stufe());
         case NAMEn_Z : return cH_EntryValueIntString(MBE->Name());
         case URSPRUNGn_Z : return cH_EntryValueIntString(cH_Zauber(MBE)->Ursprung());
         case KOSTENn_Z : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen)*cH_Zauber(MBE)->SpruchrolleFaktor());
         case STANDARDn_Z : return cH_EntryValueIntString(MBE->Standard__(Typ,ausnahmen));
        }
      if (Variante==MidgardBasicTree::ZAUBERWERK)
      switch ((Spalten_ZAUBERWERK)seqnr) {
         case STUFEn_ZW : return cH_EntryValueIntString(cH_Zauberwerk(MBE)->Stufe());
         case NAMEn_ZW : return cH_EntryValueIntString(MBE->Name());  
         case ARTn_ZW : return cH_EntryValueIntString(cH_Zauberwerk(MBE)->Art());    
         case KOSTENn_ZW : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
         case PREISn_ZW : return cH_EntryValueIntString(cH_Zauberwerk(MBE)->Preis()); 
         case ZEITAUFWANDn_ZW : return cH_EntryValueIntString(cH_Zauberwerk(MBE)->Zeitaufwand());
        }
/*
      if (name=="ZA")
       switch ((Spalten_ZA)seqnr) {
         case NAMEa_Z : return cH_EntryValueIntString(MBE->Name());
         case STUFEa_Z : return cH_EntryValueIntString(cH_Zauber(MBE)->Stufe());
         case URSPRUNGa_Z : return cH_EntryValueIntString(cH_Zauber(MBE)->Ursprung());
         case KOSTENa_Z : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
        }
*/
/*
      if (name=="ZN")
      switch ((Spalten_ZN)seqnr) {
         case STUFEn_Z : return cH_EntryValueIntString(cH_Zauber(MBE)->Stufe());
         case NAMEn_Z : return cH_EntryValueIntString(MBE->Name());  
         case URSPRUNGn_Z : return cH_EntryValueIntString(cH_Zauber(MBE)->Ursprung());
         case KOSTENn_Z : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
         case STANDARDn_Z : return cH_EntryValueIntString(MBE->Standard__(Typ,ausnahmen));
        }
      if (name=="ZWA")
        switch (seqnr) {
         case STUFEa_ZW : return cH_EntryValueIntString(cH_Zauberwerk(MBE)->Stufe());
         case NAMEa_ZW : return cH_EntryValueIntString(MBE->Name());  
         case ARTa_ZW : return cH_EntryValueIntString(cH_Zauberwerk(MBE)->Art());    
         case KOSTENa_ZW : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
        }
     if (name=="ZWN")
       switch (seqnr) {
         case STUFEn_ZW : return cH_EntryValueIntString(cH_Zauberwerk(MBE)->Stufe());
         case NAMEn_ZW : return cH_EntryValueIntString(MBE->Name());  
         case ARTn_ZW : return cH_EntryValueIntString(cH_Zauberwerk(MBE)->Art());    
         case KOSTENn_ZW : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
         case PREISn_ZW : return cH_EntryValueIntString(cH_Zauberwerk(MBE)->Preis()); 
         case ZEITAUFWANDn_ZW : return cH_EntryValueIntString(cH_Zauberwerk(MBE)->Zeitaufwand());
        }
      if (name=="KN")
      switch (seqnr) {
         case HOHOa_K    : return cH_EntryValueIntString(cH_KiDo(MBE)->Hoho());
         case NAMEa_K    : return cH_EntryValueIntString(cH_KiDo(MBE)->Name_D());
         case STUFEa_K   : return cH_EntryValueIntString(cH_KiDo(MBE)->Stufe());
         case APa_K      : return cH_EntryValueEmptyInt(cH_KiDo(MBE)->Ap());
         case KOSTENa_K  : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
         case STILa_K    : return cH_EntryValueIntString(cH_KiDo(MBE)->Stil()); 
        }
     if (name=="SPA")
      switch (seqnr) {
         case NAMEa_SP : return cH_EntryValueIntString(MBE->Name());
         case WERTa_SP : return cH_EntryValueEmptyInt(MBE->Erfolgswert());
         case PPa_SP : return cH_EntryValueEmptyInt(MBE->Praxispunkte()); 
         case STEIGERN_SP : return cH_EntryValueEmptyInt(MBE->Steigern(Typ,ausnahmen));
         case REDUZIEREN_SP : return cH_EntryValueEmptyInt(MBE->Reduzieren(Typ,ausnahmen));
         case VERLERNEN_SP : return cH_EntryValueEmptyInt(MBE->Verlernen(Typ,ausnahmen));
        }
     if (name=="SPN")
      switch (seqnr) {
         case NAMEn_SP : return cH_EntryValueIntString(MBE->Name());
         case URSCHRIFT_SP : return cH_EntryValueIntString(cH_Sprache(MBE)->Schriften());
         case KOSTEN_SP : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
        }
     if (name=="SCA")
      switch (seqnr) {
         case NAMEa_SC : return cH_EntryValueIntString(MBE->Name());
         case WERTa_SC : return cH_EntryValueEmptyInt(MBE->Erfolgswert());
//         case ARTa_SC : return cH_EntryValueIntString(cH_Schrift(MBE)->Art_der_Schrift());
         case PPa_SC : return cH_EntryValueEmptyInt(MBE->Praxispunkte()); 
         case STEIGERNa_SC : return cH_EntryValueEmptyInt(MBE->Steigern(Typ,ausnahmen));
         case REDUZIERENa_SC : return cH_EntryValueEmptyInt(MBE->Reduzieren(Typ,ausnahmen));
         case VERLERNENa_SC : return cH_EntryValueEmptyInt(MBE->Verlernen(Typ,ausnahmen));
//         case KOSTENa_SC : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
        }
     if (name=="SCN")
      switch (seqnr) {
         case NAMEn_SC : return cH_EntryValueIntString(MBE->Name());
         case KOSTENn_SC : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
        }
*/
      return cH_EntryValueIntString("?");
    }
