#ifndef _CLASS_ZAUBER_HH
#  define _CLASS_ZAUBER_HH

#include <Aux/EntryValueEmptyInt.h> 
#include <Aux/EntryValueIntString.h>

class Data_zauber : public RowDataBase
{
     string ap, name;
     int erfolgswert;
     string  art, stufe, zauberdauer, reichweite,
       wirkungsziel, wirkungsbereich, wirkungsdauer, ursprung,
       material, agens, prozess, reagens, beschreibung; 
     int kosten,lernpunkte;

 public:
      Data_zauber (const string& n, const string& a, int k,int l)
         :ap(a),name(n),erfolgswert(0),kosten(k),lernpunkte(l) {}
      Data_zauber (const string& n, const string& u, int k)
         :name(n),erfolgswert(0),ursprung(u),kosten(k),lernpunkte(0) {}
      Data_zauber(const string& s,const string& n, const string& u, int k,
           const string& a)
        :name(n),erfolgswert(0),art(a),stufe(s),ursprung(u),kosten(k),lernpunkte(0) {}

      Data_zauber (const string& n, int e)
         :name(n),erfolgswert(e),kosten(0) {}
      Data_zauber (const string& n)
         :name(n),erfolgswert(0),kosten(0) {}
/*
      Data_zauber (const string& a1, const string& n, int er, const string& a,
            const string& s,
            const string& zd, const string& r, const string& zi,
            const string& ber, const string& wd, const string& u,
            const string& mat, const string& age, const string& pro,
            const string& rea, const string& bes, int ko)
      : ap(a1), name(n), erfolgswert(er), art(a), stufe(s), zauberdauer(zd),
         reichweite(r),
         wirkungsziel(zi), wirkungsbereich(ber), wirkungsdauer(wd),
         ursprung(u), material(mat), agens(age), prozess(pro), reagens(rea),
         beschreibung(bes), kosten(ko) {};
*/
   virtual const cH_EntryValue Value(int seqnr,gpointer gp) const
 { 
//   if (!strcmp(reinterpret_cast<const char*>(gp),"alte_zauber"))
   if (reinterpret_cast<int>(gp)=='A')
      switch (seqnr) {
         case 0 : return cH_EntryValueIntString(name);
         case 1 : return cH_EntryValueIntString(ursprung);
         case 2 : return cH_EntryValueEmptyInt(kosten);
        }
   else if (reinterpret_cast<int>(gp)=='N')
      switch (seqnr) {
         case 0 : return cH_EntryValueIntString(stufe);
         case 1 : return cH_EntryValueIntString(name);
         case 2 : return cH_EntryValueIntString(ursprung);
         case 3 : return cH_EntryValueEmptyInt(kosten);
         case 4 : return cH_EntryValueIntString(art);
        }
   return cH_EntryValueIntString("?");
 }
 string Ap() const { return ap;}
 string Name() const {  return name; }
 int Erfolgswert() const {return erfolgswert; }
 string Art() const { return art;}
 string Stufe() const {  return stufe; }
 string Zauberdauer() const { return zauberdauer;}
 string Reichweite() const {return reichweite;}
 string Wirkungsziel() const {return wirkungsziel;}
 string Wirkungsdauer() const {return wirkungsdauer;}
 string Wirkungsbereich() const {return wirkungsbereich;}
 string Ursprung() const {return ursprung;}
 string Material() const { return material;} 
 string Agens() const { return agens;}
 string Prozess() const { return prozess;}
 string Reagens() const { return reagens;}
 string Beschreibung() const { return beschreibung;}
 int Kosten() const {  return kosten; }
 int Lernpunkte() const {  return lernpunkte; }

 void set_Ap(const string& s)  {ap=s;}
 void set_Name(const string& s)  { name=s ;}
 void set_Erfolgswert(int s) { erfolgswert=s ;}
 void set_Art(const string& s)  {art=s;}
 void set_Stufe(const string& s)  { stufe=s ;}
 void set_Zauberdauer(const string& s)  {zauberdauer=s;}
 void set_Reichweite(const string& s)  { reichweite=s;}
 void set_Wirkungsziel(const string& s)  { wirkungsziel=s;}
 void set_Wirkungsdauer(const string& s)  { wirkungsdauer=s;}
 void set_Wirkungsbereich(const string& s)  { wirkungsbereich=s;}
 void set_Ursprung(const string& s)  { ursprung=s;}
 void set_Material(const string& s)  {material=s;} 
 void set_Agens(const string& s)  {agens=s;}
 void set_Prozess(const string& s)  {prozess=s;}
 void set_Reagens(const string& s)  {reagens=s;}
 void set_Beschreibung(const string& s)  {beschreibung=s;}
 void set_Kosten(int i)  { kosten=i; }

};


class H_Data_zauber : public Handle<Data_zauber>
{
protected:
 H_Data_zauber() {}
public:
 H_Data_zauber(Data_zauber *r) : Handle<Data_zauber>(r){}
};

///////////////////////////////////////////////////////////////////////////
class Data_zaubermittel : public RowDataBase
{
   string stufe, name,art;
   int kosten;
   string preis, zeitaufwand;   

 public:
   Data_zaubermittel(const string& s, const string& n, const string& a, int k) : stufe(s),name(n),art(a),kosten(k){}
   Data_zaubermittel(const string& n)        : name(n),kosten(0){}
   Data_zaubermittel(const string& s,const string& n)  : stufe(s),name(n),kosten(0){}
   Data_zaubermittel(const string& s,const string& n, const string& a,int k,const string& p, const string& z)
      :stufe(s),name(n),art(a),kosten(k),preis(p),zeitaufwand(z) {}

   virtual const cH_EntryValue Value(int seqnr,gpointer g) const
   {
   if (reinterpret_cast<int>(g)=='A')
      switch (seqnr) {
         case 0 : return cH_EntryValueIntString(stufe);
         case 1 : return cH_EntryValueIntString(name);
         case 2 : return cH_EntryValueIntString(art); 
         case 3 : return cH_EntryValueEmptyInt(kosten);
        }
   else if (reinterpret_cast<int>(g)=='N')
      switch (seqnr) {
         case 0 : return cH_EntryValueIntString(stufe);
         case 1 : return cH_EntryValueIntString(name);
         case 2 : return cH_EntryValueIntString(art); 
         case 3 : return cH_EntryValueEmptyInt(kosten);
         case 4 : return cH_EntryValueIntString(preis);
         case 5 : return cH_EntryValueIntString(zeitaufwand);
        }
   return cH_EntryValueIntString("?");
   }

 string Stufe() const {  return stufe; }
 string Name() const {  return name; }
 string Art() const { return art;}
 int Kosten() const {  return kosten; }
 string Preis() const { return preis;}
 string Zeitaufwand() const { return zeitaufwand;}

 void set_Name(const string& s)  { name=s ;}
 void set_Art(const string& s)  {art=s;}
 void set_Stufe(const string& s)  { stufe=s ;}
 void set_Kosten(int s)  { kosten=s ;}
 void set_Preis(const string& s)  {preis=s;}
 void set_Zeitaufwand(const string& s)  {zeitaufwand=s;}

};


class H_Data_zaubermittel : public Handle<Data_zaubermittel>
{
protected:
 H_Data_zaubermittel() {}
public:
 H_Data_zaubermittel(Data_zaubermittel *r) : Handle<Data_zaubermittel>(r){}
};

#endif




