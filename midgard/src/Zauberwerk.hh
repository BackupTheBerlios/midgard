#ifndef ZAUBERWERKCLASS
#define ZAUBERWERKCLASS
#include "class_Grundwerte.hh"
#include "MidgardBasicElement.hh"
#include "class_typen.hh"
class cH_Zauberwerk;
#include <gtk--/label.h>

class Zauberwerk : public MidgardBasicElement
{
   std::string stufe, name,art;
   int kosten;
   std::string preis, zeitaufwand,region; 
   vector<std::string> Standard(const vector<H_Data_typen>& Typ) const ;   

   enum MBEE What() const {return MidgardBasicElement::ZAUBERWERK;}
   std::string What_str() const {return "Zauberwerk";}


   map<std::string,std::string> map_typ;

   void get_Zauberwerk();
   void get_map_typ();
   int GrundKosten() const {  return kosten; }
 public: 
   Zauberwerk(const std::string& n) 
      : name(n) {get_Zauberwerk();get_map_typ();} 

//   bool ist_lernbar(const vector<H_Data_typen>& Typ) const;
//   bool ist_gelernt(const std::list<cH_Zauberwerk>& L) const;
   map<std::string,std::string> get_MapTyp() const {return map_typ;}

   std::string Name() const {  return name; }
   std::string Standard__(const vector<H_Data_typen>& Typ) const;
   std::string Art() const 
      { if (art=="AZ") return "Alchimistisches Zaubermittel";
        if (art=="PZ") return "Zaubermittel";
        return art; }
   std::string Stufe() const {  return stufe; }
   int iStufe() const {  if (Stufe()=="groﬂ") return 6; else return atoi(Stufe().c_str()); }
//   int Erfolgswert() const {return 0;} 
   std::string Zeitaufwand() const { return zeitaufwand;}
//   std::string Beschreibung() const { return beschreibung;}
   std::string Region() const {return region;}
   int Kosten(const vector<H_Data_typen>& Typ) const;
   std::string Preis() const { return preis; }

   static bool zauberwerk_voraussetzung(const std::string& name,const Grundwerte& Werte);
};

class cH_Zauberwerk : public Handle<const Zauberwerk>
{
    typedef CacheStatic<std::string,cH_Zauberwerk> cache_t;
    static cache_t cache;
    cH_Zauberwerk(Zauberwerk *s) : Handle<const Zauberwerk>(s) {};
    friend class std::map<std::string,cH_Zauberwerk>;
    cH_Zauberwerk(){};
 public:
    cH_Zauberwerk(const std::string& name);

    cH_Zauberwerk(const cH_MidgardBasicElement &x) : Handle<const Zauberwerk>
      (dynamic_cast<const Zauberwerk *>(&*x)){}

 class sort {
      public:
         enum esort {NAME,STUFE,ART};
      private:
         esort es;
      public:
         sort(enum esort _es):es(_es) {}
         bool operator() (cH_Zauberwerk x,cH_Zauberwerk y) const
           { switch(es) {
               case(NAME) : return x->Name() < y->Name()  ;
               case(STUFE): return x->Stufe() < y->Stufe();
               case(ART): return x->Art() < y->Art() ;  
           }}
    };

};


class Zauberwerk_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   Zauberwerk_All(Gtk::Label *label);
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};




#endif
