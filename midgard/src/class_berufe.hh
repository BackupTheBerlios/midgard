#ifndef _CLASS_BERUF_HH
#  define _CLASS_BERUF_HH

#include <Aux/EntryValueEmptyInt.h>
#include <Aux/EntryValueIntString.h>

class Data_beruf : public RowDataBase
{
   std::string name;
   int erfolgswert;
   std::string vorteile, voraussetzungen, stand, pflicht;
   int lernpunkte;

 public:
   Data_beruf(const std::string& n, const std::string& v, int e)
      :name(n), erfolgswert(e), vorteile(v) {}
   Data_beruf(const std::string& n,const std::string& v1, const std::string &v2,const std::string &s,int l)
      :name(n), erfolgswert(0), vorteile(v1), voraussetzungen(v2), stand(s), lernpunkte(l) {}

 virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const 
   { return cH_EntryValueIntString("?");}

 std::string Name() const {  return name; }
 int  Erfolgswert() const {  return erfolgswert; }  
 std::string  Vorteile() const {  return vorteile; }
 std::string  Voraussetzung() const {  return voraussetzungen; }
 std::string  Pflicht() const {  return pflicht; }
 int  Lernpunkte() const {  return lernpunkte; }
 std::string Stand() const { return stand; } 

 void set_Erfolgswert(int i) {erfolgswert=i;}
 void set_Lernpunkte(int i) {lernpunkte=i;}
};

class H_Data_beruf : public Handle<Data_beruf>
{
protected:
 H_Data_beruf() {}
public:
 H_Data_beruf(Data_beruf *r) : Handle<Data_beruf>(r){}
};


#endif