#ifndef _CLASS_KIDO_HH
#  define _CLASS_KIDO_HH

#include <Aux/EntryValueEmptyInt.h> 
#include <Aux/EntryValueIntString.h>
#include "rowdata.h"

class Data_kido : public RowDataBase
{  
   std::string hoho,name,stufe;
   int ap,kosten;
   std::string stil, effekt;  
 public:
   Data_kido(const std::string& h,const std::string& n,const std::string& s1,int a,
        int k,const std::string& s)
       : hoho(h),name(n),stufe(s1),ap(a),kosten(k),stil(s) {}

   enum Spalten_A {HOHOa,NAMEa,STUFEa,APa,KOSTENa,STILa,} ;
//   enum Spalten_N {HOHOn,NAMEn,STUFEn,APn,KOSTENn,STILn,} ;

   virtual const cH_EntryValue Value(guint seqnr, gpointer gp) const
    { 
      if (reinterpret_cast<int>(gp)=='A')
      switch (seqnr) {
         case HOHOa    : return cH_EntryValueIntString(hoho);
         case NAMEa    : return cH_EntryValueIntString(name);
         case STUFEa   : return cH_EntryValueIntString(stufe);
         case APa      : return cH_EntryValueEmptyInt(ap);
         case KOSTENa  : return cH_EntryValueEmptyInt(kosten);
         case STILa    : return cH_EntryValueIntString(stil); 
        }
      if (reinterpret_cast<int>(gp)=='N')
      switch (seqnr) {
         case HOHOa    : return cH_EntryValueIntString(hoho);
         case NAMEa    : return cH_EntryValueIntString(name);
         case STUFEa   : return cH_EntryValueIntString(stufe);
         case APa      : return cH_EntryValueEmptyInt(ap);
         case KOSTENa  : return cH_EntryValueEmptyInt(kosten);
         case STILa    : return cH_EntryValueIntString(stil); 
        }
   return cH_EntryValueIntString("?");
 }
 std::string Hoho() const {  return hoho; }
 int Kosten() const {  return kosten; }
 std::string Name()  const {  return name; }
 std::string Stufe() const {  return stufe; }
 int Ap() const {  return ap; }
 std::string Stil() const {  return stil; }
}; 


class cH_Data_kido : public Handle<const Data_kido>
{
//protected:
// H_Data_kido() {}
public:
 cH_Data_kido(const Data_kido *r) : Handle<const Data_kido>(r){}
};


#endif




