#ifndef SCHRIFTCLASS
#define SCHRIFTCLASS
#include "MidgardBasicElement.hh"
#include "Typen.hh"
#include "Ausnahmen.hh"
#include "Fertigkeiten.hh"
#include <gtk--/progressbar.h>


class Schrift : public MidgardBasicElement
{
     std::string art_der_schrift;
//     int kosten;
    bool alt,kult;

     void get_Schrift();
     int Grundkosten() const {return kosten;}
  
  public:
   Schrift(const std::string& n) : MidgardBasicElement(n)
      { get_Schrift();get_map_typ(); get_Steigern_Kosten_map();
        EP_steigern("Schreiben");
      }
   enum MBEE What() const {return MidgardBasicElement::SCHRIFT;}
   std::string What_str() const {return "Urschrift";}

   std::string Art_der_Schrift() const   {return art_der_schrift; }

   bool Kult() const {return kult;}
   bool Alt() const {return alt;}
   bool kann_Sprache(const std::list<cH_MidgardBasicElement>& sprache) const;
   int Schrift::MaxErfolgswert(const Grundwerte& w,const vector<cH_Typen>& Typ) const;
   int Kosten(const vector<cH_Typen>& Typ,const Ausnahmen& ausnahmen) const
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
   Schriften_All(Gtk::ProgressBar *progressbar);
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};

#endif
