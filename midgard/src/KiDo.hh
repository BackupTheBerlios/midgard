#ifndef KIDOCLASS
#define KIDOCLASS
#include <string>
#include <list>
#include <vector>
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
//#include "class_Grundwerte.hh"
#include "class_typen.hh"
#include "class_Ausnahmen.hh"
#include "Fertigkeiten.hh"

class KiDo : public HandleContent
{
   std::string hoho,name,stufe;
   int ap,kosten;
   std::string stil, effekt;

   void get_KiDo();
//   int GrundKosten() const {  return kosten; }
//   void set_Standard(const vector<H_Data_typen>& Typ) ;
   const vector<H_Data_typen> Typ;
   const Ausnahmen ausnahmen;
 public:
   KiDo(const std::string& n,const vector<H_Data_typen>& T,const Ausnahmen& a)
     :hoho(n),Typ(T),ausnahmen(a) {get_KiDo();}

 std::string Hoho() const {  return hoho; }
 int Kosten() const { cH_Fertigkeit F("KiDo",Typ,ausnahmen);
                      return  (int)(F->Standard_Faktor() * kosten) ; }
 std::string Name()  const {  return name; }
 std::string Stufe() const {  return stufe; }
 int Ap() const {  return ap; }
 std::string Stil() const {  return stil; }
 std::string Effekt() const {  return effekt; }


 static int get_erfolgswert_kido(const std::list<cH_Fertigkeit>& L);
};

class cH_KiDo : public Handle<const KiDo>
{
   struct st_index {std::string name; vector<H_Data_typen> Typ;
      bool operator == (const st_index& b) const
         {return (name==b.name && Typ[0]->Short() == b.Typ[0]->Short());}
      bool operator <  (const st_index& b) const
         { return name < b.name ||
             (name==b.name && Typ[0]->Short()<b.Typ[0]->Short());}
      st_index(std::string n, vector<H_Data_typen> T):name(n),Typ(T){}
      st_index(){}
      };
    
    typedef CacheStatic<st_index,cH_KiDo> cache_t;
    static cache_t cache;
    cH_KiDo(KiDo *s) : Handle<const KiDo>(s) {};
    friend class std::map<st_index,cH_KiDo>;
    cH_KiDo(){};
 public:
    cH_KiDo(const std::string& name,const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen);
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

 
#endif