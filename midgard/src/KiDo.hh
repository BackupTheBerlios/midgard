#ifndef KIDOCLASS
#define KIDOCLASS
#include "MidgardBasicElement.hh"
#include "class_typen.hh"
#include "Ausnahmen.hh"
#include "Fertigkeiten.hh"
#include <gtk--/label.h>

class KiDo : public MidgardBasicElement
{
   std::string hoho,name,stufe;
   int ap,kosten;
   std::string stil, effekt;

//   map<std::string,std::string> map_typ; 

   void get_KiDo();
//   void get_map_typ();
//   int GrundKosten() const {  return kosten; }
//   void set_Standard(const vector<H_Data_typen>& Typ) ;
//   const vector<H_Data_typen> Typ;
//   const Ausnahmen ausnahmen;
 public:
   KiDo(const std::string& n)
     :hoho(n) {get_KiDo();get_map_typ();}

// map<std::string,std::string> get_MapTyp() const {return map_typ;}
 enum MBEE What() const {return MidgardBasicElement::KIDO;}
 std::string What_str() const {return "KiDo";}

 std::string Hoho() const {  return hoho; }
 std::string Name()  const {  return hoho; }
 int Kosten(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const 
         { cH_Fertigkeit F("KiDo");
                      return  (int)(F->Standard_Faktor(Typ,ausnahmen) * kosten) ; }
 std::string Name_D()  const {  return name; }
 std::string Stufe() const {  return stufe; }
 int Ap() const {  return ap; }
 std::string Stil() const {  return stil; }
 std::string Effekt() const {  return effekt; }
// std::string Region() const { return "K";}
// int Erfolgswert()

 static int get_erfolgswert_kido(const std::list<cH_MidgardBasicElement>& L);
 static std::map<std::string,int> maxkidostil(const std::list<cH_MidgardBasicElement>& list_Kido);

};

class cH_KiDo : public Handle<const KiDo>
{
    typedef CacheStatic<std::string,cH_KiDo> cache_t;
    static cache_t cache;
    cH_KiDo(KiDo *s) : Handle<const KiDo>(s) {};
    friend class std::map<std::string,cH_KiDo>;
    cH_KiDo(){};
 public:
    cH_KiDo(const std::string& name);
    cH_KiDo(const cH_MidgardBasicElement &x) : Handle<const KiDo>
      (dynamic_cast<const KiDo *>(&*x)){}


 class sort {
      public:
         enum esort {HOHO,NAME,STUFE,AP,STIL};
      private: 
         esort es;
      public:
         sort(enum esort _es):es(_es) {}
         bool operator() (cH_KiDo x,cH_KiDo y) const
           { switch(es) {
               case(HOHO) : return x->Hoho() < y->Hoho()  ;
               case(NAME) : return x->Name() < y->Name()  ;
               case(STUFE): return x->Stufe() < y->Stufe();
               case(AP)   : return x->Ap() < y->Ap() ;
               case(STIL) : return x->Stil() < y->Stil() ;
           }}
    };
};

class KiDo_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   KiDo_All(Gtk::Label *label);
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};



 
#endif