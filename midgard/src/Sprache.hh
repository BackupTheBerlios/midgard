#ifndef SPRACHECLASS
#define SPRACHECLASS
#include "MidgardBasicElement.hh"
#include "Typen.hh"
#include "Ausnahmen.hh"
#include "Fertigkeiten.hh"
#include <gtk--/progressbar.h>

class Sprache : public MidgardBasicElement
{
     vector<std::string> VSchrift;
     bool alte_sprache,minderheit,maxwert;
     vector<int> V_sprachgruppe;

     void get_Sprache();
     int Grundkosten() const {return kosten;}
  
  public:
   Sprache(const std::string& n) : MidgardBasicElement(n)
      {get_Sprache();get_map_typ();get_Steigern_Kosten_map();
         EP_steigern("Sprache");}
   enum MBEE What() const {return MidgardBasicElement::SPRACHE;}
   std::string What_str() const {return "Sprache";}

   std::string Schriften() const;
   const vector<std::string> &Schrift() const  {return VSchrift; }
   const vector<pair<std::string,int> > SchriftWert(const  std::list<cH_MidgardBasicElement>& list_Schrift) const ; 

   bool Alte_Sprache() const {return alte_sprache;}    
   bool Minderheit() const {return minderheit;}    
   int MaxErfolgswert(const Grundwerte& w,const vector<cH_Typen>& Typ) const;
   int Kosten(const vector<cH_Typen>& Typ,const Ausnahmen& ausnahmen) const;
   vector<int> getVSprachgruppe() const {return V_sprachgruppe;}
   bool Sprachgruppe(const list<cH_MidgardBasicElement>& MBE) const;
};

class cH_Sprache : public Handle<const Sprache>
{
    typedef CacheStatic<std::string,cH_Sprache> cache_t;
    static cache_t cache;
    cH_Sprache(Sprache *s) : Handle<const Sprache>(s) {};
    friend class std::map<std::string,cH_Sprache>;
    cH_Sprache(){};
  public:
   cH_Sprache(const std::string& name);

   cH_Sprache(const cH_MidgardBasicElement &x) : Handle<const Sprache>
      (dynamic_cast<const Sprache *>(&*x)){}

/*
   class sort {
      public:
         enum esort {NAME,ERFOLGSWERT};
      private: 
         esort es;
      public:
         sort(enum esort _es):es(_es) {}
         bool operator() (cH_Sprache x,cH_Sprache y) const
           { switch(es) {
               case(NAME) : return x->Name() < y->Name()  ;
               case(ERFOLGSWERT): return x->Erfolgswert() < y->Erfolgswert();
           }}
    };
*/
};

class Sprachen_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   Sprachen_All(Gtk::ProgressBar *progressbar);
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};

#endif
