#ifndef _CLASS_ZAUBER_HH
#  define _CLASS_ZAUBER_HH

#include <Aux/EntryValueEmptyInt.h> 
#include <Aux/EntryValueIntString.h>

class Data_zauber : public RowDataBase
{
     std::string ap, name;
//     int erfolgswert;
     std::string  standard, stufe,//art, zauberdauer, reichweite,
//       wirkungsziel, wirkungsbereich, wirkungsdauer, 
ursprung;
//       material, agens, prozess, reagens, beschreibung; 
     int kosten;//,lernpunkte;

 public:
//      Data_zauber (const std::string& n, const std::string& a, int k,int l)
//         :ap(a),name(n),erfolgswert(0),kosten(k),lernpunkte(l) {}
      Data_zauber(const std::string& n,const std::string& s, 
            const std::string& u, int k, const std::string& st)
        :name(n),standard(st),stufe(s),ursprung(u),kosten(k) {}
/*
      Data_zauber (const std::string& n, int e)
         :name(n),erfolgswert(e),kosten(0) {}
      Data_zauber (const std::string& n)
         :name(n),erfolgswert(0),kosten(0) {}
*/
   enum Spalten_A {NAMEa,STUFEa,URSPRUNGa,KOSTENa} ;
   enum Spalten_N {NAMEn,STUFEn,URSPRUNGn,KOSTENn,STANDARDn};
   virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const
 { 
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
         case STANDARDn : return cH_EntryValueIntString(standard);
        }
   return cH_EntryValueIntString("?");
 }
 std::string Name() const {  return name; }
 std::string Standard() const { return standard;}
 std::string Stufe() const {  return stufe; }
 std::string Ursprung() const {return ursprung;}
 int Kosten() const {  return kosten; }
};


class cH_Data_zauber : public Handle<const Data_zauber>
{
//protected:
// H_Data_zauber() {}
public:
 cH_Data_zauber(const Data_zauber *r) : Handle<const Data_zauber>(r){}
};


///////////////////////////////////////////////////////////////////////////
class Data_zaubermittel : public RowDataBase
{
   std::string stufe, name,art;
   int kosten;
   std::string preis, zeitaufwand;   

 public:
   Data_zaubermittel(const std::string& s, const std::string& n, const std::string& a, int k) : stufe(s),name(n),art(a),kosten(k){}
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
};


class cH_Data_zaubermittel : public Handle<const Data_zaubermittel>
{
protected:
 cH_Data_zaubermittel() {}
public:
 cH_Data_zaubermittel(const Data_zaubermittel *r) : Handle<const Data_zaubermittel>(r){}
};

#endif
