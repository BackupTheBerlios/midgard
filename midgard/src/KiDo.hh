#ifndef KIDOCLASS
#define KIDOCLASS
//#include <string>
//#include <list>
//#include <vector>
//#include <Aux/Handles.h>
//#include <Aux/CacheStatic.h>
#include "MidgardBasicElement.hh"
//#include "class_Grundwerte.hh"
#include "class_typen.hh"
#include "class_Ausnahmen.hh"
#include "Fertigkeiten.hh"

//class KiDo : public HandleContent
class KiDo : public MidgardBasicElement
{
   std::string hoho,name,stufe;
   int ap,kosten;
   std::string stil, effekt;

   map<std::string,std::string> map_typ; 

   void get_KiDo();
   void get_map_typ();
//   int GrundKosten() const {  return kosten; }
//   void set_Standard(const vector<H_Data_typen>& Typ) ;
//   const vector<H_Data_typen> Typ;
//   const Ausnahmen ausnahmen;
 public:
//   KiDo(const std::string& n,const vector<H_Data_typen>& T,const Ausnahmen& a)
//     :hoho(n),Typ(T),ausnahmen(a) {get_KiDo();get_map_typ();}
   KiDo(const std::string& n)
     :hoho(n) {get_KiDo();get_map_typ();}

 map<std::string,std::string> get_MapTyp() const {return map_typ;}
 enum MBEE What() const {return MidgardBasicElement::KIDO;}
 std::string What_str() const {return "KiDo";}

 std::string Hoho() const {  return hoho; }
 std::string Name()  const {  return hoho; }
 int Kosten(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const 
         { cH_Fertigkeit F("KiDo",Typ,ausnahmen);
                      return  (int)(F->Standard_Faktor() * kosten) ; }
 std::string Name_D()  const {  return name; }
 std::string Stufe() const {  return stufe; }
 int Ap() const {  return ap; }
 std::string Stil() const {  return stil; }
 std::string Effekt() const {  return effekt; }
// std::string Region() const { return "K";}
// int Erfolgswert()

 static int get_erfolgswert_kido(const std::list<cH_Fertigkeit>& L);
};

class cH_KiDo : public Handle<const KiDo>
{
/*
   struct st_index {std::string name; vector<H_Data_typen> Typ;
      bool operator == (const st_index& b) const
         {return (name==b.name && Typ[0]->Short() == b.Typ[0]->Short());}
      bool operator <  (const st_index& b) const
         { return name < b.name ||
             (name==b.name && Typ[0]->Short()<b.Typ[0]->Short());}
      st_index(std::string n, vector<H_Data_typen> T):name(n),Typ(T){}
      st_index(){}
      };
*/    
//    typedef CacheStatic<st_index,cH_KiDo> cache_t;
    typedef CacheStatic<std::string,cH_KiDo> cache_t;
    static cache_t cache;
    cH_KiDo(KiDo *s) : Handle<const KiDo>(s) {};
//    friend class std::map<st_index,cH_KiDo>;
    friend class std::map<std::string,cH_KiDo>;
    cH_KiDo(){};
 public:
//    cH_KiDo(const std::string& name,const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen);
    cH_KiDo(const std::string& name);

    cH_KiDo(const cH_MidgardBasicElement &x) : Handle<const KiDo>
      (dynamic_cast<const KiDo *>(&*x)){}
};

class KiDo_sort_hoho
{ public: bool operator() (cH_KiDo x,cH_KiDo y) const
   {return x->Hoho() < y->Hoho(); }};
class KiDo_sort_name
{ public: bool operator() (cH_KiDo x,cH_KiDo y) const
   {return x->Name() < y->Name(); }};
class KiDo_sort_stufe
{ public: bool operator() (cH_KiDo x,cH_KiDo y) const
   {return x->Stufe() < y->Stufe(); }};
class KiDo_sort_ap
{ public: bool operator() (cH_KiDo x,cH_KiDo y) const
   {return x->Ap() < y->Ap(); }};
class KiDo_sort_stil
{ public: bool operator() (cH_KiDo x,cH_KiDo y) const
   {return x->Stil() < y->Stil(); }};


class KiDo_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   KiDo_All();
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};



 
#endif