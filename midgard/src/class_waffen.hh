#ifndef _CLASS_WAFFEN_HH
#  define _CLASS_WAFFEN_HH

#include <Aux/EntryValueEmptyInt.h>
#include <Aux/EntryValueIntString.h>

class Data_waffen : public RowDataBase
{
   std::string name;
   int erfolgswert;
   int steigern, reduzieren, verlernen;
   std::string voraussetzung;

 public:
   Data_waffen(const std::string& n,int e,const std::string& v)
      : name(n),erfolgswert(e),voraussetzung(v) {}
   Data_waffen(const std::string& n, int w,int s,int r,int v)
      :name(n),erfolgswert(w),steigern(s),reduzieren(r),verlernen(v){}

   enum Spalten_A {NAMEa,WERTa,STEIGERN,REDUZIEREN} ;
   enum Spalten_N {NAMEn,WERTn,VORAUSSETZUNG} ;

   virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const
    { 
      if (reinterpret_cast<int>(gp)=='A')
       switch (seqnr) {
         case NAMEa : return cH_EntryValueIntString(name);
         case WERTa : return cH_EntryValueEmptyInt(erfolgswert); 
         case STEIGERN : return cH_EntryValueEmptyInt(steigern);
         case REDUZIEREN : return cH_EntryValueEmptyInt(reduzieren);
        }
      if (reinterpret_cast<int>(gp)=='N')
       switch (seqnr) {
         case NAMEn : return cH_EntryValueIntString(name);
         case WERTn : return cH_EntryValueEmptyInt(erfolgswert); 
         case VORAUSSETZUNG : return cH_EntryValueIntString(voraussetzung);
        }
      return cH_EntryValueIntString("?");
    }
 std::string Name() const {  return name; }
 int  Erfolgswert() const {  return erfolgswert; }  
 int  Steigern() const {  return steigern; }
 int  Reduzieren() const {  return reduzieren; }
 int  Verlernen() const {  return verlernen; }  
 std::string  Voraussetzung() const {  return voraussetzung; }
};

class H_Data_waffen : public Handle<Data_waffen>
{
public:
 H_Data_waffen(Data_waffen *r) : Handle<Data_waffen>(r){}
};


 
class Data_grund : public RowDataBase
{
   std::string name;
   int kosten;
 public:
   Data_grund(const std::string& n) :name(n),kosten(0) {}
   Data_grund(const std::string& n, int k) :name(n),kosten(k) {}

   virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const
 { 
    if (reinterpret_cast<int>(gp)=='A')
      switch (seqnr) {
         case 0 : return cH_EntryValueIntString(name); }
    if (reinterpret_cast<int>(gp)=='N')
      switch (seqnr) {
         case 0 : return cH_EntryValueIntString(name);
         case 1 : return cH_EntryValueEmptyInt(kosten);
        }
   return cH_EntryValueIntString("?");
  }
 std::string Name() const {  return name; }
 int Kosten() const {  return kosten; }
};

#endif
