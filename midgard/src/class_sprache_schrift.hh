#ifndef _CLASS_SPRACHE_HH
#  define _CLASS_SPRACHE_HH

#include <Aux/EntryValueEmptyInt.h> 
#include <Aux/EntryValueIntString.h>

class Data_sprache : public RowDataBase
{
     std::string name, urschrift;
     int wert, steigern,reduzieren,verlernen, kosten;

 public:
     Data_sprache(const std::string& n,const std::string& s,int w,int k)
       :name(n),urschrift(s),wert(w),steigern(0),reduzieren(0),verlernen(0),kosten(k) {}
     Data_sprache(const std::string& n,int w, int s, int r, int v)
       :name(n),wert(w),steigern(s),reduzieren(r),verlernen(v),kosten(0) {}


   virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const
    { 
     if (reinterpret_cast<int>(gp)=='A')
      switch (seqnr) {
         case 0 : return cH_EntryValueIntString(name);
         case 1 : return cH_EntryValueEmptyInt(wert);
         case 2 : return cH_EntryValueEmptyInt(steigern);
         case 3 : return cH_EntryValueEmptyInt(reduzieren);
         case 4 : return cH_EntryValueEmptyInt(verlernen);
        }
     else if (reinterpret_cast<int>(gp)=='N')
      switch (seqnr) {
         case 0 : return cH_EntryValueIntString(name);
         case 1 : return cH_EntryValueIntString(urschrift);
         case 2 : return cH_EntryValueEmptyInt(kosten);
        }
     return cH_EntryValueIntString("?");
    }
 std::string Name() const {  return name; }
 std::string Urschrift() const {  return urschrift; }
 int Wert() const {  return wert; }   
 int Steigern() const {  return steigern; }
 int Reduzieren() const {  return reduzieren; }
 int Verlernen() const {  return verlernen; }  
 int Kosten() const {  return kosten; }

 void set_Wert(int i) {wert=i;}
 void set_Urschrift(const std::string& s) { urschrift=s; }
};


class H_Data_sprache : public Handle<Data_sprache>
{
protected:
 H_Data_sprache() {}
public:
 H_Data_sprache(Data_sprache *r) : Handle<Data_sprache>(r){}
};

///////////////////////////////////////////////////////////////////////////
class Data_schrift : public RowDataBase
{  
   std::string urschrift,art;
   int kosten;
 public:
   Data_schrift(const std::string& u,const std::string& a, int k)
       :urschrift(u),art(a),kosten(k) {}
   Data_schrift(const std::string& u,const std::string& a)
       :urschrift(u),art(a),kosten(0) {}


   virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const
    { 
     if (reinterpret_cast<int>(gp)=='A')
      switch (seqnr) {
         case 0 : return cH_EntryValueIntString(urschrift);
         case 1 : return cH_EntryValueIntString(art);
         case 2 : return cH_EntryValueEmptyInt(kosten);
        }
     else if (reinterpret_cast<int>(gp)=='N')
      switch (seqnr) {
         case 0 : return cH_EntryValueIntString(urschrift);
         case 1 : return cH_EntryValueIntString(art);
         case 2 : return cH_EntryValueEmptyInt(kosten);
        }
     return cH_EntryValueIntString("?");
    }
 std::string Urschrift() const {  return urschrift; }
 std::string Art() const {  return art; }
 int Kosten() const {  return kosten; }
}; 
class H_Data_schrift : public Handle<Data_schrift>
{
protected:
 H_Data_schrift() {}
public:
 H_Data_schrift(Data_schrift *r) : Handle<Data_schrift>(r){}
};



#endif