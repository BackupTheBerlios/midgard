#ifndef ZAUBERWERKCLASS
#define ZAUBERWERKCLASS
#include "Grundwerte.hh"
#include "MidgardBasicElement.hh"
#include "Typen.hh"
class cH_Zauberwerk;
#include <gtk--/progressbar.h>


class Zauberwerk : public MidgardBasicElement
{
   std::string stufe, art;
   std::string preis, zeitaufwand; 

   enum MBEE What() const {return MidgardBasicElement::ZAUBERWERK;}
   std::string What_str() const {return "Zauberwerk";}
   struct st_vor{std::string voraussetzung; std::string op;
          st_vor(){};
          st_vor(std::string v,std::string o) 
               : voraussetzung(v),op(o){} };
   std::vector<st_vor> vec_vor;
   std::vector<st_vor> vec_vorF;

   void getVoraussetzungen();
   void getVoraussetzungenFert();
   void get_Zauberwerk();
 public: 
   Zauberwerk(const std::string& n,const std::string& a) 
      : MidgardBasicElement(n),art(a) {get_Zauberwerk();get_map_typ();
            getVoraussetzungen();getVoraussetzungenFert();} 

//   std::string Name() const {  return name; }
   std::string Art() const { return art; }
   std::string Stufe() const {  return stufe; }
   int iStufe() const {  if (Stufe()=="groﬂ") return 6; else return atoi(Stufe().c_str()); }
   std::string Zeitaufwand() const { return zeitaufwand;}
//   std::string Region() const {return region;}
   std::string Preis() const { return preis; }

   bool Voraussetzungen(const std::list<cH_MidgardBasicElement>& listZauber) const;
   bool Voraussetzungen_Fertigkeit(const std::list<cH_MidgardBasicElement>& listZauber) const;
   int MaxErfolgswert(const Grundwerte& w,const vector<cH_Typen>& Typ) const 
         {return 0;} //wg. virtueller Funktion
};

class cH_Zauberwerk : public Handle<const Zauberwerk>
{
    struct st_index {std::string name;std::string art;
           st_index(std::string n,std::string a):name(n),art(a){}
           bool operator<(const st_index& b) const {
               return name<b.name || (name==b.name && art<b.art) ;}
            };
    typedef CacheStatic<st_index,cH_Zauberwerk> cache_t;
    static cache_t cache;
    cH_Zauberwerk(Zauberwerk *s) : Handle<const Zauberwerk>(s) {};
    friend class std::map<st_index,cH_Zauberwerk>;
    cH_Zauberwerk(){};
 public:
    cH_Zauberwerk(const std::string& name, const std::string& art);

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
   Zauberwerk_All(Gtk::ProgressBar *progressbar);
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};

#endif
