#ifndef _CLASS_FERT_HH
#  define _CLASS_FERT_HH

#include <Aux/EntryValueEmptyInt.h>
#include <Aux/EntryValueIntString.h>

class Data_fert : public RowDataBase
{
   string name;
   int wert, lernkosten, steigern, reduzieren, verlernen;
   string art, voraussetzungen, attribut, pflicht;
   int lernpunkte;
 public:
   Data_fert(const string& n, int w) : name(n),wert(w),lernkosten(0),steigern(0),reduzieren(0),verlernen(0),lernpunkte(0) {}
   Data_fert(const string& n, int w, const string& a) : name(n),wert(w),lernkosten(0),steigern(0),reduzieren(0),verlernen(0),attribut(a),lernpunkte(0) {}
   Data_fert(const string& n, int w,int s,int r,int v )
      :name(n),wert(w),lernkosten(0),steigern(s),reduzieren(r),verlernen(v),lernpunkte(0) {}
   Data_fert(const string& n, int w,int l,const string& a, const string& v )
      :name(n),wert(w),lernkosten(l),steigern(0),reduzieren(0),verlernen(0),art(a),voraussetzungen(v),lernpunkte(0) {}   
   Data_fert(const string &n,int w,int fp, const string& v, const string& a,const string &p, int L)
      :name(n),wert(w),lernkosten(fp),steigern(0),reduzieren(0),verlernen(0),voraussetzungen(v),attribut(a),pflicht(p),lernpunkte(L) {}   


   virtual const cH_EntryValue Value(int seqnr,gpointer gp) const
    { 
      if (reinterpret_cast<int>(gp)=='A')
       switch (seqnr) {
         case 0 : return cH_EntryValueIntString(name);
         case 1 : return cH_EntryValueEmptyInt(wert); 
         case 2 : return cH_EntryValueEmptyInt(steigern);
         case 3 : return cH_EntryValueEmptyInt(reduzieren);
         case 4 : return cH_EntryValueEmptyInt(verlernen); 
        }
      if (reinterpret_cast<int>(gp)=='N')
       switch (seqnr) {
         case 0 : return cH_EntryValueIntString(name);
         case 1 : return cH_EntryValueEmptyInt(wert); 
         case 2 : return cH_EntryValueEmptyInt(lernkosten);
         case 3 : return cH_EntryValueIntString(art);
         case 4 : return cH_EntryValueIntString(voraussetzungen);
        }
      return cH_EntryValueIntString("?");
    }
 string Name() const {  return name; }
 int  Erfolgswert() const {  return wert; }  
// cH_EntryValue  Empty_Erfolgswert() const {  return cH_EntryValueEmptyInt(wert); }  
 int  Lernkosten() const {  return lernkosten; }
 int  Steigern() const {  return steigern; }
 int  Reduzieren() const {  return reduzieren; }
 int  Verlernen() const {  return verlernen; }  
 string  Attribut() const {  return attribut; }
// string  Art() const {  return art; }
 string  Voraussetzung() const {  return voraussetzungen; }
 string  Pflicht() const {  return pflicht; }
 int  Lernpunkte() const {  return lernpunkte; }

 void set_Erfolgswert(int i) {wert=i;}
 void set_Lernpunkte(int i) {lernpunkte=i;}
};

class H_Data_fert : public Handle<Data_fert>
{
protected:
 H_Data_fert() {}
public:
 H_Data_fert(Data_fert *r) : Handle<Data_fert>(r){}
};


#endif