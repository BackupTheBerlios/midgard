#ifndef ZAUBERWERKCLASS
#define ZAUBERWERKCLASS
#include <string>
#include <list>
#include <map>
#include <vector>
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include "class_Grundwerte.hh"
#include "class_typen.hh"
class cH_Zauberwerk;

class Zauberwerk : public HandleContent
{
   std::string stufe, name,art;
   int kosten;
   std::string preis, zeitaufwand,region; 
   vector<std::string> Standard(const vector<H_Data_typen>& Typ) const ;   

   map<std::string,std::string> map_typ;

   void get_Zauberwerk();
   void get_map_typ();
   int GrundKosten() const {  return kosten; }
 public: 
   Zauberwerk(const std::string& n) 
      : name(n) {get_Zauberwerk();get_map_typ();} 

   bool ist_lernbar(const vector<H_Data_typen>& Typ) const;
   bool ist_gelernt(const std::list<cH_Zauberwerk>& L) const;

   std::string Name() const {  return name; }
   std::string Standard__(const vector<H_Data_typen>& Typ) const;
   std::string Art() const 
      { if (art=="AZ") return "Alchimistisches Zaubermittel";
        if (art=="PZ") return "Zaubermittel";
        return art; }
   std::string Stufe() const {  return stufe; }
   int iStufe() const {  if (Stufe()=="gro�") return 6; else return atoi(Stufe().c_str()); }
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


class Zauberwerk_All
{
   std::list<cH_Zauberwerk> list_All;
  public:
   Zauberwerk_All();
   std::list<cH_Zauberwerk> get_All() const {return list_All;}
};




#endif
