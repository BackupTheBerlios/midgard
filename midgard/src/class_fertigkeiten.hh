#ifndef _CLASS_FERT_HH
#  define _CLASS_FERT_HH

#include <Aux/EntryValueEmptyInt.h>
#include <Aux/EntryValueIntString.h>



class Data_fert : public RowDataBase
{
   std::string name;
   int wert, lernkosten, steigern, reduzieren, verlernen;
   std::string art, voraussetzungen, attribut, pflicht;
   int lernpunkte;
 public:
   Data_fert(const std::string& n, int w) : name(n),wert(w),lernkosten(0),steigern(0),reduzieren(0),verlernen(0),lernpunkte(0) {}
   Data_fert(const std::string& n, int w, const std::string& a) : name(n),wert(w),lernkosten(0),steigern(0),reduzieren(0),verlernen(0),attribut(a),lernpunkte(0) {}
   Data_fert(const std::string& n, int w,int s,int r,int v )
      :name(n),wert(w),lernkosten(0),steigern(s),reduzieren(r),verlernen(v),lernpunkte(0) {}
   Data_fert(const std::string& n, int w,int l,const std::string& a, const std::string& v )
      :name(n),wert(w),lernkosten(l),steigern(0),reduzieren(0),verlernen(0),art(a),voraussetzungen(v),lernpunkte(0) {}   
   Data_fert(const std::string &n,int w,int fp, const std::string& v, const std::string& a,const std::string &p, int L)
      :name(n),wert(w),lernkosten(fp),steigern(0),reduzieren(0),verlernen(0),voraussetzungen(v),attribut(a),pflicht(p),lernpunkte(L) {}   


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
         case ART : return cH_EntryValueIntString(art);
         case VORAUSSETZUNGEN : return cH_EntryValueIntString(voraussetzungen);
        }
      return cH_EntryValueIntString("?");
    }
 std::string Name() const {  return name; }
 int  Erfolgswert() const {  return wert; }  
// cH_EntryValue  Empty_Erfolgswert() const {  return cH_EntryValueEmptyInt(wert); }  
 int  Lernkosten() const {  return lernkosten; }
 int  Steigern() const {  return steigern; }
 int  Reduzieren() const {  return reduzieren; }
 int  Verlernen() const {  return verlernen; }  
 std::string  Attribut() const {  return attribut; }
// std::string  Art() const {  return art; }
 std::string  Voraussetzung() const {  return voraussetzungen; }
 std::string  Pflicht() const {  return pflicht; }
 int  Lernpunkte() const {  return lernpunkte; }

 void set_Erfolgswert(int i) {wert=i;}
 void set_Lernpunkte(int i) {lernpunkte=i;}

/*
 // Prädikate
//  Data_fert_sort_name(const Data_fert& d) : name(d.Name()) {}
      bool operator == (const Data_fert& b) const
         {return Name()==b.Name();}
      bool operator < (const Data_fert& b) const
         {return Name()<b.Name();}
*/
};

class H_Data_fert : public Handle<Data_fert>
{
protected:
// Data_fert *rc;
 H_Data_fert() {}
public:
 H_Data_fert(Data_fert *r) : Handle<Data_fert>(r) {}//,rc(r){}
/*
   bool operator == (const Data_fert& b) const
         {return rc->Name()==b.Name();}
   bool operator < (const Data_fert& b) const
         {return rc->Name()<b.Name();}
*/
};


class Data_fert_sort_name 
{ public : bool operator() (H_Data_fert x, H_Data_fert y) const
      { return x->Name() < y->Name();}};
class Data_fert_sort_wert 
{ public : bool operator() (H_Data_fert x, H_Data_fert y) const
      { return x->Erfolgswert() < y->Erfolgswert();}};

#endif
