#ifndef _CLASS_WAFFEN_HH
#  define _CLASS_WAFFEN_HH

#include <Aux/EntryValueEmptyInt.h>
#include <Aux/EntryValueIntString.h>

class Data_waffen : public RowDataBase
{
   string name,alias,region;
   int av_bonus, sl_bonus;
   string magisch;
   int erfolgswert, lernkosten, steigern, reduzieren, verlernen,lernpunkte;
   string grundkenntnisse, voraussetzung;

 public:
   Data_waffen() 
      : av_bonus(0),sl_bonus(0),erfolgswert(0), lernkosten(0), steigern(0), reduzieren(0), verlernen(0),lernpunkte(0)  {}
   Data_waffen(const string& n) 
      : name(n),av_bonus(0),sl_bonus(0),erfolgswert(0), lernkosten(0), steigern(0), reduzieren(0), verlernen(0),lernpunkte(0) {}
   Data_waffen(const string& n, int w, const string& v) 
      : name(n),av_bonus(0),sl_bonus(0),erfolgswert(w),lernkosten(0), steigern(0), reduzieren(0), verlernen(0),lernpunkte(0),voraussetzung(v) {}
   Data_waffen(string n, string na, string r,int a, int s, string m)
      : name(n), alias(na), region(r),av_bonus(a),sl_bonus(s),magisch(m),erfolgswert(0), lernkosten(0), steigern(0), reduzieren(0), verlernen(0),lernpunkte(0) {} 
   Data_waffen(const string &n,int w, int l, const string& g, const string& v)
      : name(n),av_bonus(0),sl_bonus(0),erfolgswert(w),lernpunkte(l), grundkenntnisse(g), voraussetzung(v) {}
   Data_waffen(const string& n, int w,int s,int r)
      :name(n),av_bonus(0),sl_bonus(0),erfolgswert(w),lernkosten(0),steigern(s),reduzieren(r),verlernen(0),lernpunkte(0) {}


   virtual const cH_EntryValue Value(int seqnr,gpointer gp) const
    { 
      if (reinterpret_cast<int>(gp)=='A')
       switch (seqnr) {
         case 0 : return cH_EntryValueIntString(name);
         case 1 : return cH_EntryValueEmptyInt(erfolgswert); 
         case 2 : return cH_EntryValueEmptyInt(steigern);
         case 3 : return cH_EntryValueEmptyInt(reduzieren);
        }
      if (reinterpret_cast<int>(gp)=='N')
       switch (seqnr) {
         case 0 : return cH_EntryValueIntString(name);
         case 1 : return cH_EntryValueEmptyInt(erfolgswert); 
         case 2 : return cH_EntryValueIntString(voraussetzung);
        }
      return cH_EntryValueIntString("?");
    }
 string Name() const {  return name; }
 string Region() const {return region;}
 string Magisch() const {return magisch;}
 string Alias() const {return alias;}
 int  Erfolgswert() const {  return erfolgswert; }  
 int  Lernkosten() const {  return lernkosten; }
 int  Steigern() const {  return steigern; }
 int  Reduzieren() const {  return reduzieren; }
 int  Verlernen() const {  return verlernen; }  
// string  Attribut() const {  return attribut; }
// string  Art() const {  return art; }
 string  Voraussetzung() const {  return voraussetzung; }
// string  Pflicht() const {  return pflicht; }
 int  Lernpunkte() const {  return lernpunkte; }
 string Grundkenntnisse() const {return grundkenntnisse; }
 int av_Bonus() const {return av_bonus;}
 int sl_Bonus() const {return sl_bonus;}

 void set_Erfolgswert(int i) {erfolgswert=i;}
 void set_Lernpunkte(int i)  {lernpunkte=i;}
 void set_av_Bonus(int i)  {av_bonus=i;}
 void set_sl_Bonus(int i) {sl_bonus=i;}
 void set_Magisch(const string& s)  {magisch=s;}
};

class H_Data_waffen : public Handle<Data_waffen>
{
protected:
 H_Data_waffen() {}
public:
 H_Data_waffen(Data_waffen *r) : Handle<Data_waffen>(r){}
};


#endif