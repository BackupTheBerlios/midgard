#ifndef _CLASS_KIDO_HH
#  define _CLASS_KIDO_HH

#include <Aux/EntryValueEmptyInt.h> 
#include <Aux/EntryValueIntString.h>

class Data_kido : public RowDataBase
{  
   std::string hoho,name,stufe;
   int ap,kosten;
   std::string stil, effekt;  
 public:
   Data_kido(const std::string& h,const std::string& n,const std::string& s1,int a,
        int k,const std::string& s)
       : hoho(h),name(n),stufe(s1),ap(a),kosten(k),stil(s) {}
   Data_kido(const std::string& h) : hoho(h),ap(0),kosten(0) {}

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
 std::string Effekt() const {  return effekt; }

 void set_Kosten(int i) {  kosten=i; }
 void set_Name(const std::string& s)  {  name=s; }
 void set_Stufe(const std::string& s)  {  stufe=s; }
 void set_Ap(int i) {   ap=i; }
 void set_Stil(const std::string& s) { stil=s; }
 void set_Effekt(const std::string& s) { effekt=s; }
}; 


class H_Data_kido : public Handle<Data_kido>
{
protected:
 H_Data_kido() {}
public:
 H_Data_kido(Data_kido *r) : Handle<Data_kido>(r){}
};

class Data_kido_sort_hoho
{ public: bool operator() (H_Data_kido x,H_Data_kido y) const
   {return x->Hoho() < y->Hoho(); }};
class Data_kido_sort_name
{ public: bool operator() (H_Data_kido x,H_Data_kido y) const
   {return x->Name() < y->Name(); }};
class Data_kido_sort_stufe
{ public: bool operator() (H_Data_kido x,H_Data_kido y) const
   {return x->Stufe() < y->Stufe(); }};
class Data_kido_sort_ap
{ public: bool operator() (H_Data_kido x,H_Data_kido y) const
   {return x->Ap() < y->Ap(); }};
class Data_kido_sort_stil
{ public: bool operator() (H_Data_kido x,H_Data_kido y) const
   {return x->Stil() < y->Stil(); }};


#endif




