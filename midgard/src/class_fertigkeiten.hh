#ifndef _CLASS_FERT_HH
#  define _CLASS_FERT_HH

#include <Aux/EntryValueEmptyInt.h>
#include <Aux/EntryValueIntString.h>



class Data_fert : public RowDataBase
{
   std::string name;
   int wert, lernkosten, steigern, reduzieren, verlernen;
   std::string standard, voraussetzungen;
 public:
   Data_fert(const string& n, int w) : name(n),wert(w){} // NUR FÜR ANGEBORENE
   Data_fert(const std::string& n, int w,int s,int r,int v )
      :name(n),wert(w),steigern(s),reduzieren(r),verlernen(v) {}
   Data_fert(const std::string& n, int w,int l,const std::string& a, const std::string& v )
      :name(n),wert(w),lernkosten(l),standard(a),voraussetzungen(v) {}   

   enum Spalten_A {NAMEa,WERTa,STEIGERN,REDUZIEREN,VERLERNEN} ;
   enum Spalten_N {NAMEn,WERTn,LERNKOSTEN,ART,VORAUSSETZUNGEN};

   virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const
    { 
      if (reinterpret_cast<int>(gp)=='A')
       switch((Spalten_A)seqnr) {
         case NAMEa : return cH_EntryValueIntString(name);
         case WERTa : return cH_EntryValueEmptyInt(wert); 
         case STEIGERN : return cH_EntryValueEmptyInt(steigern);
         case REDUZIEREN : return cH_EntryValueEmptyInt(reduzieren);
         case VERLERNEN : return cH_EntryValueEmptyInt(verlernen); 
        }
      if (reinterpret_cast<int>(gp)=='N')
       switch ((Spalten_N)seqnr) {
         case NAMEn : return cH_EntryValueIntString(name);
         case WERTn : return cH_EntryValueEmptyInt(wert); 
         case LERNKOSTEN : return cH_EntryValueEmptyInt(lernkosten);
         case ART : return cH_EntryValueIntString(standard);
         case VORAUSSETZUNGEN : return cH_EntryValueIntString(voraussetzungen);
        }
      return cH_EntryValueIntString("?");
    }
 std::string Name() const {  return name; }
 std::string Standard() const {  return standard; }
 int  Erfolgswert() const {  return wert; }  
 int  Lernkosten() const {  return lernkosten; }
 int  Steigern() const {  return steigern; }
 int  Reduzieren() const {  return reduzieren; }
 int  Verlernen() const {  return verlernen; }  
 std::string  Voraussetzung() const {  return voraussetzungen; }
};

class H_Data_fert : public Handle<Data_fert>
{
//protected:
// H_Data_fert() {}
public:
 H_Data_fert(Data_fert *r) : Handle<Data_fert>(r) {}
};


#endif
