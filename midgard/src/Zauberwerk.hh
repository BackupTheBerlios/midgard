#ifndef ZAUBERWERKCLASS
#define ZAUBERWERKCLASS
#include <string>
#include <list>
#include <vector>
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
//#include "class_Grundwerte.hh"
#include "class_typen.hh"

class Zauberwerk : public HandleContent
{
   std::string stufe, name,art;
   int kosten;
   std::string preis, zeitaufwand,region; 
   vector<std::string> standard;      

   void get_Zauberwerk();
   int GrundKosten() const {  return kosten; }
   void set_Standard(const vector<H_Data_typen>& Typ) ;
 public: 
   Zauberwerk(const std::string& n,const vector<H_Data_typen>& Typ) 
      : name(n) {get_Zauberwerk();set_Standard(Typ);} 

   std::string Name() const {  return name; }
   std::string Standard__() const { return standard[0]+' '+standard[1];}
   std::string Art() const 
      { if (art=="AZ") return "Alchimistisches Zaubermittel";
        if (art=="PZ") return "Zaubermittel";
        return art; }
   std::string Stufe() const {  return stufe; }
   int iStufe() const {  if (Stufe()=="groﬂ") return 6; else return atoi(Stufe().c_str()); }
   std::string Zeitaufwand() const { return zeitaufwand;}
//   std::string Beschreibung() const { return beschreibung;}
   const vector<std::string>& Standard() const {return standard;}
   std::string Region() const {return region;}
   int Kosten(const vector<H_Data_typen>& Typ) const;
   std::string Preis() const { return preis; }

//   int Erfolgswert(const vector<H_Data_typen>& Typ,const Grundwerte& Werte) const;
//   int get_spezial_zauber_for_magier(const Grundwerte& Werte) const;

};

class cH_Zauberwerk : public Handle<const Zauberwerk>
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
    
    typedef CacheStatic<st_index,cH_Zauberwerk> cache_t;
    static cache_t cache;
    cH_Zauberwerk(Zauberwerk *s) : Handle<const Zauberwerk>(s) {};
    friend class std::map<st_index,cH_Zauberwerk>;
    cH_Zauberwerk(){};
 public:
    cH_Zauberwerk(const std::string& name,const vector<H_Data_typen>& Typ);
};

class Zauberwerk_sort_name
{ public: bool operator() (cH_Zauberwerk x,cH_Zauberwerk y) const
   {return x->Name() < y->Name(); }};
class Zauberwerk_sort_stufe
{ public: bool operator() (cH_Zauberwerk x,cH_Zauberwerk y) const
   {return x->Stufe()<y->Stufe(); }};
class Zauberwerk_sort_art
{ public: bool operator() (cH_Zauberwerk x,cH_Zauberwerk y) const
   {return x->Art()<y->Art(); }};

#endif
