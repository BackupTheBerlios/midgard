#ifndef SCHRIFTCLASS
#define SCHRIFTCLASS
#include "MidgardBasicElement.hh"
#include "class_typen.hh"
#include "Ausnahmen.hh"
#include "Fertigkeiten.hh"

class Schrift : public MidgardBasicElement
{
     std::string name, art_der_schrift, region;
     int kosten;
//     map<std::string,std::string> map_typ;
//     cH_Fertigkeit *fertigkeit;

     void get_Schrift();
//     void get_map_typ();
     int Grundkosten() const {return kosten;}
  
  public:
   Schrift(const std::string& n) : name(n)
      { get_Schrift();get_map_typ(); 
//        fertigkeit = new Fertigkeit("Lesen/Schreiben");
      }
//   map<std::string,std::string> get_MapTyp() const {return map_typ;}
   enum MBEE What() const {return MidgardBasicElement::SCHRIFT;}
   std::string What_str() const {return "Urschrift";}

   std::string Name() const   {return name; }
   std::string Region() const {return region;}
   std::string Art_der_Schrift() const   {return art_der_schrift; }
//   int Erfolgswert(const vector<H_Data_typen>& Typ,const Grundwerte& Werte,const Ausnahmen& ausnahmen) const;
//   void set_Erfolgswert(int e) const {erfolgswert=e;}
//   void add_Erfolgswert(int e) const {erfolgswert+=e;}

   int Kosten(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const
        { cH_Fertigkeit F("Lesen/Schreiben");
             return  (int)(F->Standard_Faktor(Typ,ausnahmen) * kosten) ; }
};

class cH_Schrift : public Handle<const Schrift>
{
    typedef CacheStatic<std::string,cH_Schrift> cache_t;
    static cache_t cache;
    cH_Schrift(Schrift *s) : Handle<const Schrift>(s) {};
    friend class std::map<std::string,cH_Schrift>;
    cH_Schrift(){};
  public:
   cH_Schrift(const std::string& name);

   cH_Schrift(const cH_MidgardBasicElement &x) : Handle<const Schrift>
      (dynamic_cast<const Schrift *>(&*x)){}
/*
   class sort {
      public:
         enum esort {NAME,ERFOLGSWERT};
      private: 
         esort es;
      public:
         sort(enum esort _es):es(_es) {}
         bool operator() (cH_Schrift x,cH_Schrift y) const
           { switch(es) {
               case(NAME) : return x->Name() < y->Name()  ;
               case(ERFOLGSWERT): return x->Erfolgswert() < y->Erfolgswert();
           }}
    };
*/
};

class Schriften_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   Schriften_All(Gtk::Label *label);
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};

#endif
