#ifndef _CLASS_ZAUBER_HH
#  define _CLASS_ZAUBER_HH

#include <Aux/EntryValueEmptyInt.h> 
#include <Aux/EntryValueIntString.h>

class Data_zauber : public RowDataBase
{
     std::string ap, name;
     int erfolgswert;
     std::string  art, stufe, zauberdauer, reichweite,
       wirkungsziel, wirkungsbereich, wirkungsdauer, ursprung,
       material, agens, prozess, reagens, beschreibung; 
     int kosten,lernpunkte;

 public:
      Data_zauber (const std::string& n, const std::string& a, int k,int l)
         :ap(a),name(n),erfolgswert(0),kosten(k),lernpunkte(l) {}
//      Data_zauber (const std::string& n, const std::string& u, int k)
//         :name(n),erfolgswert(0),ursprung(u),kosten(k),lernpunkte(0) {}
      Data_zauber (const std::string& n, const std::string& s, const std::string& u, int k)
         :name(n),erfolgswert(0),stufe(s),ursprung(u),kosten(k),lernpunkte(0) {}
      Data_zauber(const std::string& s,const std::string& n, const std::string& u, int k,
           const std::string& a)
        :name(n),erfolgswert(0),art(a),stufe(s),ursprung(u),kosten(k),lernpunkte(0) {}

      Data_zauber (const std::string& n, int e)
         :name(n),erfolgswert(e),kosten(0) {}
      Data_zauber (const std::string& n)
         :name(n),erfolgswert(0),kosten(0) {}
/*
      Data_zauber (const std::string& a1, const std::string& n, int er, const std::string& a,
            const std::string& s,
            const std::string& zd, const std::string& r, const std::string& zi,
            const std::string& ber, const std::string& wd, const std::string& u,
            const std::string& mat, const std::string& age, const std::string& pro,
            const std::string& rea, const std::string& bes, int ko)
      : ap(a1), name(n), erfolgswert(er), art(a), stufe(s), zauberdauer(zd),
         reichweite(r),
         wirkungsziel(zi), wirkungsbereich(ber), wirkungsdauer(wd),
         ursprung(u), material(mat), agens(age), prozess(pro), reagens(rea),
         beschreibung(bes), kosten(ko) {};
*/
   enum Spalten_A {NAMEa,STUFEa,URSPRUNGa,KOSTENa} ;
   enum Spalten_N {NAMEn,STUFEn,URSPRUNGn,KOSTENn,ARTn};
   virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const
 { 
//   if (!strcmp(reinterpret_cast<const char*>(gp),"alte_zauber"))
   if (reinterpret_cast<int>(gp)=='A')
      switch (seqnr) {
         case NAMEa : return cH_EntryValueIntString(name);
         case STUFEa : return cH_EntryValueIntString(stufe);
         case URSPRUNGa : return cH_EntryValueIntString(ursprung);
         case KOSTENa : return cH_EntryValueEmptyInt(kosten);
        }
   else if (reinterpret_cast<int>(gp)=='N')
      switch (seqnr) {
         case STUFEn : return cH_EntryValueIntString(stufe);
         case NAMEn : return cH_EntryValueIntString(name);
         case URSPRUNGn : return cH_EntryValueIntString(ursprung);
         case KOSTENn : return cH_EntryValueEmptyInt(kosten);
         case ARTn : return cH_EntryValueIntString(art);
        }
   return cH_EntryValueIntString("?");
 }
 std::string Ap() const { return ap;}
 std::string Name() const {  return name; }
 int Erfolgswert() const {return erfolgswert; }
 std::string Art() const { return art;}
 std::string Stufe() const {  return stufe; }
 std::string Zauberdauer() const { return zauberdauer;}
 std::string Reichweite() const {return reichweite;}
 std::string Wirkungsziel() const {return wirkungsziel;}
 std::string Wirkungsdauer() const {return wirkungsdauer;}
 std::string Wirkungsbereich() const {return wirkungsbereich;}
 std::string Ursprung() const {return ursprung;}
 std::string Material() const { return material;} 
 std::string Agens() const { return agens;}
 std::string Prozess() const { return prozess;}
 std::string Reagens() const { return reagens;}
 std::string Beschreibung() const { return beschreibung;}
 int Kosten() const {  return kosten; }
 int Lernpunkte() const {  return lernpunkte; }

 void set_Ap(const std::string& s)  {ap=s;}
 void set_Name(const std::string& s)  { name=s ;}
 void set_Erfolgswert(int s) { erfolgswert=s ;}
 void set_Art(const std::string& s)  {art=s;}
 void set_Stufe(const std::string& s)  { stufe=s ;}
 void set_Zauberdauer(const std::string& s)  {zauberdauer=s;}
 void set_Reichweite(const std::string& s)  { reichweite=s;}
 void set_Wirkungsziel(const std::string& s)  { wirkungsziel=s;}
 void set_Wirkungsdauer(const std::string& s)  { wirkungsdauer=s;}
 void set_Wirkungsbereich(const std::string& s)  { wirkungsbereich=s;}
 void set_Ursprung(const std::string& s)  { ursprung=s;}
 void set_Material(const std::string& s)  {material=s;} 
 void set_Agens(const std::string& s)  {agens=s;}
 void set_Prozess(const std::string& s)  {prozess=s;}
 void set_Reagens(const std::string& s)  {reagens=s;}
 void set_Beschreibung(const std::string& s)  {beschreibung=s;}
 void set_Kosten(int i)  { kosten=i; }

};


class H_Data_zauber : public Handle<Data_zauber>
{
protected:
 H_Data_zauber() {}
public:
 H_Data_zauber(Data_zauber *r) : Handle<Data_zauber>(r){}
};

class Data_zauber_sort_name
{ public: bool operator() (H_Data_zauber x,H_Data_zauber y) const
   {return x->Name() < y->Name(); }};
class Data_zauber_sort_stufe
{ public: bool operator() (H_Data_zauber x,H_Data_zauber y) const
   {return x->Stufe()<y->Stufe(); }};
//class Data_zauber_sort_art
//{ public: bool operator() (H_Data_zauber x,H_Data_zauber y) const
//   {return x->Art()<y->Art(); }};
class Data_zauber_sort_ursprung
{ public: bool operator() (H_Data_zauber x,H_Data_zauber y) const
   {return x->Ursprung()<y->Ursprung(); }};


///////////////////////////////////////////////////////////////////////////
class Data_zaubermittel : public RowDataBase
{
   std::string stufe, name,art;
   int kosten;
   std::string preis, zeitaufwand;   

 public:
   Data_zaubermittel(const std::string& s, const std::string& n, const std::string& a, int k) : stufe(s),name(n),art(a),kosten(k){}
   Data_zaubermittel(const std::string& n)        : name(n),kosten(0){}
   Data_zaubermittel(const std::string& s,const std::string& n)  : stufe(s),name(n),kosten(0){}
   Data_zaubermittel(const std::string& s,const std::string& n, const std::string& a,int k,const std::string& p, const std::string& z)
      :stufe(s),name(n),art(a),kosten(k),preis(p),zeitaufwand(z) {}

   enum Spalten_A {STUFEa,NAMEa,ARTa,KOSTENa} ;
   enum Spalten_N {STUFEn,NAMEn,ARTn,KOSTENn,PREISn,ZEITAUFWANDn};
   virtual const cH_EntryValue Value(guint seqnr,gpointer g) const
   {
   if (reinterpret_cast<int>(g)=='A')
      switch (seqnr) {
         case STUFEa : return cH_EntryValueIntString(stufe);
         case NAMEa : return cH_EntryValueIntString(name);
         case ARTa : return cH_EntryValueIntString(art); 
         case KOSTENa : return cH_EntryValueEmptyInt(kosten);
        }
   else if (reinterpret_cast<int>(g)=='N')
      switch (seqnr) {
         case STUFEn : return cH_EntryValueIntString(stufe);
         case NAMEn : return cH_EntryValueIntString(name);
         case ARTn : return cH_EntryValueIntString(art); 
         case KOSTENn : return cH_EntryValueEmptyInt(kosten);
         case PREISn : return cH_EntryValueIntString(preis);
         case ZEITAUFWANDn : return cH_EntryValueIntString(zeitaufwand);
        }
   return cH_EntryValueIntString("?");
   }

 std::string Stufe() const {  return stufe; }
 std::string Name() const {  return name; }
 std::string Art() const { return art;}
 int Kosten() const {  return kosten; }
 std::string Preis() const { return preis;}
 std::string Zeitaufwand() const { return zeitaufwand;}

 void set_Name(const std::string& s)  { name=s ;}
 void set_Art(const std::string& s)  {art=s;}
 void set_Stufe(const std::string& s)  { stufe=s ;}
 void set_Kosten(int s)  { kosten=s ;}
 void set_Preis(const std::string& s)  {preis=s;}
 void set_Zeitaufwand(const std::string& s)  {zeitaufwand=s;}

};


class H_Data_zaubermittel : public Handle<Data_zaubermittel>
{
protected:
 H_Data_zaubermittel() {}
public:
 H_Data_zaubermittel(Data_zaubermittel *r) : Handle<Data_zaubermittel>(r){}
};

class Data_zaubermittel_sort_name
{ public: bool operator() (H_Data_zaubermittel x,H_Data_zaubermittel y) const
   {return x->Name() < y->Name(); }};
class Data_zaubermittel_sort_stufe
{ public: bool operator() (H_Data_zaubermittel x,H_Data_zaubermittel y) const
   {return x->Stufe()<y->Stufe(); }};
class Data_zaubermittel_sort_art
{ public: bool operator() (H_Data_zaubermittel x,H_Data_zaubermittel y) const
   {return x->Art()<y->Art(); }};

#endif




