#ifndef _CLASS_FERT_HH
#  define _CLASS_FERT_HH

#include <Aux/EntryValueEmptyInt.h>
#include <Aux/EntryValueIntString.h>
#include <MidgardBasicElement.hh>
#include <MidgardBasicTree.hh>
#include <Typen.hh>
#include <Ausnahmen.hh>
#include <Sprache.hh>
#include <Fertigkeiten.hh>
#include <Schrift.hh>
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

   virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const
    { 
      MidgardBasicTree::variante Variante = 
               MidgardBasicTree::variante(reinterpret_cast<int>(gp));
      if (Variante==MidgardBasicTree::LONG_ALT)
       switch((Spalten_LONG_ALT)seqnr) {
         case NAMEa : 
           {
             if(MBE->What()==MidgardBasicElement::FERTIGKEIT)
                return cH_EntryValueIntString(MBE->Name()+" "+cH_Fertigkeit(MBE)->Zusatz());
             else
                return cH_EntryValueIntString(MBE->Name());
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
         case LERNKOSTEN : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
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
         case HOHOa_K    : return cH_EntryValueIntString(cH_KiDo(MBE)->Hoho());
         case NAMEa_K    : return cH_EntryValueIntString(cH_KiDo(MBE)->Name_D());
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
         case KOSTENn_Z : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
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
 const cH_MidgardBasicElement &getMBE() const {return MBE;}

};

class H_Data_SimpleTree : public Handle<Data_SimpleTree>
{
//protected:
// H_Data_SimpleTree() {}
public:
 H_Data_SimpleTree(Data_SimpleTree *r) : Handle<Data_SimpleTree>(r) {}
};


#endif
