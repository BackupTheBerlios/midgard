#ifndef _CLASS_WAFFEN_HH
#  define _CLASS_WAFFEN_HH

#include <Aux/EntryValueEmptyInt.h>
#include <Aux/EntryValueIntString.h>

class Data_waffen : public RowDataBase
{
   std::string name,alias,region;
   int av_bonus, sl_bonus;
   std::string magisch;
   int erfolgswert, lernkosten, steigern, reduzieren, verlernen,lernpunkte;
   std::string grundkenntnisse, voraussetzung;

 public:
   Data_waffen() 
      : av_bonus(0),sl_bonus(0),erfolgswert(0), lernkosten(0), steigern(0), reduzieren(0), verlernen(0),lernpunkte(0)  {}
   Data_waffen(const std::string& n) 
      : name(n),av_bonus(0),sl_bonus(0),erfolgswert(0), lernkosten(0), steigern(0), reduzieren(0), verlernen(0),lernpunkte(0) {}
   Data_waffen(const std::string& n, int w, const std::string& v) 
      : name(n),av_bonus(0),sl_bonus(0),erfolgswert(w),lernkosten(0), steigern(0), reduzieren(0), verlernen(0),lernpunkte(0),voraussetzung(v) {}
   Data_waffen(std::string n, std::string na, std::string r,int a, int s, std::string m)
      : name(n), alias(na), region(r),av_bonus(a),sl_bonus(s),magisch(m),erfolgswert(0), lernkosten(0), steigern(0), reduzieren(0), verlernen(0),lernpunkte(0) {} 
   Data_waffen(const std::string &n,int w, int l, const std::string& g, const std::string& v)
      : name(n),av_bonus(0),sl_bonus(0),erfolgswert(w),lernpunkte(l), grundkenntnisse(g), voraussetzung(v) {}
   Data_waffen(const std::string& n, int w,int s,int r)
      :name(n),av_bonus(0),sl_bonus(0),erfolgswert(w),lernkosten(0),steigern(s),reduzieren(r),verlernen(0),lernpunkte(0) {}

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
 std::string Region() const {return region;}
 std::string Magisch() const {return magisch;}
 std::string Alias() const {return alias;}
 int  Erfolgswert() const {  return erfolgswert; }  
 int  Lernkosten() const {  return lernkosten; }
 int  Steigern() const {  return steigern; }
 int  Reduzieren() const {  return reduzieren; }
 int  Verlernen() const {  return verlernen; }  
// std::string  Attribut() const {  return attribut; }
// std::string  Art() const {  return art; }
 std::string  Voraussetzung() const {  return voraussetzung; }
// std::string  Pflicht() const {  return pflicht; }
 int  Lernpunkte() const {  return lernpunkte; }
 std::string Grundkenntnisse() const {return grundkenntnisse; }
 int av_Bonus() const {return av_bonus;}
 int sl_Bonus() const {return sl_bonus;}

 void set_Erfolgswert(int i) {erfolgswert=i;}
 void set_Lernpunkte(int i)  {lernpunkte=i;}
 void set_av_Bonus(int i)  {av_bonus=i;}
 void set_sl_Bonus(int i) {sl_bonus=i;}
 void set_Magisch(const std::string& s)  {magisch=s;}
};

class H_Data_waffen : public Handle<Data_waffen>
{
protected:
 H_Data_waffen() {}
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

class Data_waffen_sort_name 
{ public : bool operator() (H_Data_waffen x, H_Data_waffen y) const
      { return x->Name() < y->Name();}};
class Data_waffen_sort_wert
{ public : bool operator() (H_Data_waffen x, H_Data_waffen y) const   
      { return x->Erfolgswert() < y->Erfolgswert();}}; 
class Data_waffen_sort_magbonus
{ public : bool operator() (H_Data_waffen x, H_Data_waffen y) const
      { return x->av_Bonus() > y->av_Bonus();}}; 



#endif