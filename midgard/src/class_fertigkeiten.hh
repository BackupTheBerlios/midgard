#ifndef _CLASS_FERT_HH
#  define _CLASS_FERT_HH

#include <Aux/EntryValueEmptyInt.h>
#include <Aux/EntryValueIntString.h>
#include <MidgardBasicElement.hh>
#include <Typen.hh>
#include <Ausnahmen.hh>
#include <Sprache.hh>
#include <Schrift.hh>

class Data_fert : public RowDataBase
{
   cH_MidgardBasicElement MBE;
   vector<cH_Typen> Typ;
   Ausnahmen ausnahmen;
 public:
   Data_fert(const cH_MidgardBasicElement& _MBE,const vector<cH_Typen>& _Typ, 
         const Ausnahmen& _ausnahmen) 
   : MBE(_MBE),Typ(_Typ),ausnahmen(_ausnahmen) {}

   enum Spalten_FA {NAMEa,WERTa,STEIGERN,REDUZIEREN,VERLERNEN} ;
   enum Spalten_WA {NAMEa_W,WERTa_W,STEIGERN_W,REDUZIEREN_W} ;
   enum Spalten_FN {NAMEn,WERTn,LERNKOSTEN,ART,VORAUSSETZUNGEN};
   enum Spalten_WN {NAMEn_W,WERTn_W,VORAUSSETZUNGEN_W};
   enum Spalten_GA {NAMEa_G};
   enum Spalten_GN {NAMEn_G,KOSTEN_G};
   enum Spalten_ZA {NAMEa_Z,STUFEa_Z,URSPRUNGa_Z,KOSTENa_Z} ;
   enum Spalten_ZN {NAMEn_Z,STUFEn_Z,URSPRUNGn_Z,KOSTENn_Z,STANDARDn_Z};
   enum Spalten_ZWA{STUFEa_ZW,NAMEa_ZW,ARTa_ZW,KOSTENa_ZW} ;
   enum Spalten_ZWN{STUFEn_ZW,NAMEn_ZW,ARTn_ZW,KOSTENn_ZW,PREISn_ZW,ZEITAUFWANDn_ZW};
   enum Spalten_KA {HOHOa_K,NAMEa_K,STUFEa_K,APa_K,KOSTENa_K,STILa_K,} ;
   enum Spalten_SPA{NAMEa_SP,WERTa_SP,STEIGERN_SP,REDUZIEREN_SP,VERLERNEN_SP} ;
   enum Spalten_SPN{NAMEn_SP,URSCHRIFT_SP,KOSTEN_SP} ;
   enum Spalten_SCA {NAMEa_SC,WERTa_SC,KOSTENa_SC} ;


   virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const
    { 
      string name = (char*)(gp);
      if (name=="FA")
       switch((Spalten_FA)seqnr) {
         case NAMEa : return cH_EntryValueIntString(MBE->Name());
         case WERTa : return cH_EntryValueEmptyInt(MBE->Erfolgswert()); 
         case STEIGERN : return cH_EntryValueEmptyInt(MBE->Steigern(Typ,ausnahmen));
         case REDUZIEREN : return cH_EntryValueEmptyInt(MBE->Reduzieren(Typ,ausnahmen));
         case VERLERNEN : return cH_EntryValueEmptyInt(MBE->Verlernen(Typ,ausnahmen)); 
        }
      if (name=="FN")
       switch ((Spalten_FN)seqnr) {
         case NAMEn : return cH_EntryValueIntString(MBE->Name());
         case WERTn : return cH_EntryValueEmptyInt(MBE->Erfolgswert()); 
         case LERNKOSTEN : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
         case ART : return cH_EntryValueIntString(MBE->Standard__(Typ,ausnahmen));
         case VORAUSSETZUNGEN : return cH_EntryValueIntString(cH_Fertigkeit(MBE)->Voraussetzung());
        }
      if (name=="WA")
       switch((Spalten_WA)seqnr) {
         case NAMEa_W : return cH_EntryValueIntString(MBE->Name());
         case WERTa_W : return cH_EntryValueEmptyInt(MBE->Erfolgswert()); 
         case STEIGERN_W : return cH_EntryValueEmptyInt(MBE->Steigern(Typ,ausnahmen));
         case REDUZIEREN_W : return cH_EntryValueEmptyInt(MBE->Reduzieren(Typ,ausnahmen));
        }
      if (name=="WN")
       switch ((Spalten_WN)seqnr) {
         case NAMEn_W : return cH_EntryValueIntString(MBE->Name());
         case WERTn_W : return cH_EntryValueEmptyInt(MBE->Erfolgswert()); 
         case VORAUSSETZUNGEN_W : return cH_EntryValueIntString(cH_Waffe(MBE)->Voraussetzung());
        }
      if (name=="GA")
       switch((Spalten_GA)seqnr) {
         case NAMEa_G : return cH_EntryValueIntString(MBE->Name());
        }
      if (name=="GN")
       switch ((Spalten_GN)seqnr) {
         case NAMEn_G : return cH_EntryValueIntString(MBE->Name());
         case KOSTEN_G : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen)); 
        }
      if (name=="ZA")
       switch ((Spalten_ZA)seqnr) {
         case NAMEa_Z : return cH_EntryValueIntString(MBE->Name());
         case STUFEa_Z : return cH_EntryValueIntString(cH_Zauber(MBE)->Stufe());
         case URSPRUNGa_Z : return cH_EntryValueIntString(cH_Zauber(MBE)->Ursprung());
         case KOSTENa_Z : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
        }
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
      if (name=="KA")
        switch (seqnr) {
         case HOHOa_K    : return cH_EntryValueIntString(cH_KiDo(MBE)->Hoho());
         case NAMEa_K    : return cH_EntryValueIntString(cH_KiDo(MBE)->Name_D());
         case STUFEa_K   : return cH_EntryValueIntString(cH_KiDo(MBE)->Stufe());
         case APa_K      : return cH_EntryValueEmptyInt(cH_KiDo(MBE)->Ap());
         case KOSTENa_K  : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
         case STILa_K    : return cH_EntryValueIntString(cH_KiDo(MBE)->Stil()); 
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
         case STEIGERN_SP : return cH_EntryValueEmptyInt(MBE->Steigern(Typ,ausnahmen));
         case REDUZIEREN_SP : return cH_EntryValueEmptyInt(MBE->Reduzieren(Typ,ausnahmen));
         case VERLERNEN_SP : return cH_EntryValueEmptyInt(MBE->Verlernen(Typ,ausnahmen));
        }
     if (name=="SPN")
      switch (seqnr) {
         case NAMEn_SP : return cH_EntryValueIntString(MBE->Name());
         case URSCHRIFT_SP : return cH_EntryValueIntString(cH_Sprache(MBE)->Urschrift());
         case KOSTEN_SP : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
        }
     if (name=="SCA")
      switch (seqnr) {
         case NAMEa_SC : return cH_EntryValueIntString(MBE->Name());
         case WERTa_SC : return cH_EntryValueIntString(cH_Schrift(MBE)->Art_der_Schrift());
         case KOSTENa_SC : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
        }
     if (name=="SCN")
      switch (seqnr) {
         case NAMEa_SC : return cH_EntryValueIntString(MBE->Name());
         case WERTa_SC : return cH_EntryValueIntString(cH_Schrift(MBE)->Art_der_Schrift());
         case KOSTENa_SC : return cH_EntryValueEmptyInt(MBE->Kosten(Typ,ausnahmen));
        }
      return cH_EntryValueIntString("?");
    }
 cH_MidgardBasicElement getMBE() const {return MBE;}

};

class H_Data_fert : public Handle<Data_fert>
{
//protected:
// H_Data_fert() {}
public:
 H_Data_fert(Data_fert *r) : Handle<Data_fert>(r) {}
};


#endif
