#ifndef SPRACHECLASS
#define SPRACHECLASS
#include "MidgardBasicElement.hh"
#include "class_typen.hh"
#include "Ausnahmen.hh"
#include "Fertigkeiten.hh"

class Sprache : public MidgardBasicElement
{
     std::string name, land, kontinent, urschrift, region;
     int kosten,maxwert;
     mutable int erfolgswert;
     bool alte_sprache;
//     std::map<std::string,std::string> map_typ;
     cH_Fertigkeit *fertigkeit;

     void get_Sprache();
//     void get_map_typ();
     void get_Fertigkeit();
     int Grundkosten() const {return kosten;}
  
  public:
   Sprache(const std::string& n) : name(n), fertigkeit(0) 
      {get_Sprache();get_map_typ();get_Fertigkeit();}
//   map<std::string,std::string> get_MapTyp() const {return map_typ;}
   enum MBEE What() const {return MidgardBasicElement::SPRACHE;}
   std::string What_str() const {return "Sprache";}

   std::string Name() const   {return name; }
   std::string Region() const {return region;}
   std::string Land() const   {return land; }
   std::string Kontinent() const {return kontinent;}
   std::string Urschrift() const   {return urschrift; }
//   int Erfolgswert(const vector<H_Data_typen>& Typ,const Grundwerte& Werte,const Ausnahmen& ausnahmen) const;
   int Erfolgswert() const {return erfolgswert;}
   void set_Erfolgswert(int e) const { erfolgswert=e; }
   void add_Erfolgswert(int e) const {erfolgswert+=e;}

   bool Alte_Sprache() const {return alte_sprache;}    
   int Maxwert() const {return maxwert;}
   int Kosten(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const
        { cH_Fertigkeit F("Sprache");
               return  (int)(F->Standard_Faktor(Typ,ausnahmen) * kosten) ; }
   int Steigern(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const 
        { cH_Fertigkeit F("Sprache");
          return  (int)(F->Standard_Faktor(Typ,ausnahmen) * F->get_Steigern_Kosten(Erfolgswert()+1));}
   int Reduzieren(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const 
        { cH_Fertigkeit F("Sprache");
          return  (int)(F->Standard_Faktor(Typ,ausnahmen) * F->get_Steigern_Kosten(Erfolgswert()-1));}
   int Verlernen(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const {return Kosten(Typ,ausnahmen);}
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

};

class Sprachen_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   Sprachen_All(Gtk::Label *label);
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};

#endif
