#ifndef _CLASS_KIDO_HH
#  define _CLASS_KIDO_HH

#include <Aux/EntryValueEmptyInt.h> 
#include <Aux/EntryValueIntString.h>

class Data_kido : public RowDataBase
{  
   string hoho,name,stufe;
   int ap,kosten;
   string stil, effekt;  
 public:
   Data_kido(const string& h,const string& n,const string& s1,int a,
        int k,const string& s)
       : hoho(h),name(n),stufe(s1),ap(a),kosten(k),stil(s) {}
   Data_kido(const string& h) : hoho(h),ap(0),kosten(0) {}

   virtual const cH_EntryValue Value(int seqnr, gpointer gp) const
    { 
      if (reinterpret_cast<int>(gp)=='A')
      switch (seqnr) {
         case 0 : return cH_EntryValueIntString(hoho);
         case 1 : return cH_EntryValueIntString(name);
         case 2 : return cH_EntryValueIntString(stufe);
         case 3 : return cH_EntryValueEmptyInt(ap);
         case 4 : return cH_EntryValueEmptyInt(kosten);
         case 5 : return cH_EntryValueIntString(stil); 
        }
      if (reinterpret_cast<int>(gp)=='N')
      switch (seqnr) {
         case 0 : return cH_EntryValueIntString(hoho);
         case 1 : return cH_EntryValueIntString(name);
         case 2 : return cH_EntryValueIntString(stufe);
         case 3 : return cH_EntryValueEmptyInt(ap);
         case 4 : return cH_EntryValueEmptyInt(kosten);
         case 5 : return cH_EntryValueIntString(stil); 
        }
   return cH_EntryValueIntString("?");
 }
 string Hoho() const {  return hoho; }
 int Kosten() const {  return kosten; }
 string Name()  const {  return name; }
 string Stufe() const {  return stufe; }
 int Ap() const {  return ap; }
 string Stil() const {  return stil; }
 string Effekt() const {  return effekt; }

 void set_Kosten(int i) {  kosten=i; }
 void set_Name(const string& s)  {  name=s; }
 void set_Stufe(const string& s)  {  stufe=s; }
 void set_Ap(int i) {   ap=i; }
 void set_Stil(const string& s) { stil=s; }
 void set_Effekt(const string& s) { effekt=s; }
}; 


class H_Data_kido : public Handle<Data_kido>
{
protected:
 H_Data_kido() {}
public:
 H_Data_kido(Data_kido *r) : Handle<Data_kido>(r){}
};
#endif




