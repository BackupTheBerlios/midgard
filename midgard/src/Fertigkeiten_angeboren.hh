#ifndef _FERTIGKEITEN_A_HH
#  define _FERTIGKEITEN_A_HH
#include <list>
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include "class_typen.hh"
#include "class_Ausnahmen.hh"

class Fertigkeit_angeborene : public HandleContent
{
     std::string name;
     int erfolgswert;
     int min,max;

     void get_Fertigkeit();
  public:
     Fertigkeit_angeborene(const std::string& n) : name(n) {get_Fertigkeit();}
     Fertigkeit_angeborene(const std::string& n,int w) 
         : name(n),erfolgswert(w),min(0),max(0) {}

     std::string Name() const {return name;}
     int Erfolgswert() const {return erfolgswert;};
     int Min() const {return min;}
     int Max() const {return max;}
//     std::string Voraussetzung() const {return voraussetzung;}
};

class cH_Fertigkeit_angeborene : public Handle<const Fertigkeit_angeborene>
{
    typedef CacheStatic<std::string,cH_Fertigkeit_angeborene> cache_t;
    static cache_t cache;
//    cH_Fertigkeit_angeborene(Fertigkeit_angeborene *s) : Handle<const Fertigkeit_angeborene>(s) {};
    friend class std::map<std::string,cH_Fertigkeit_angeborene>;
    cH_Fertigkeit_angeborene(){};
 public:
    cH_Fertigkeit_angeborene(const std::string& n);
    cH_Fertigkeit_angeborene(Fertigkeit_angeborene *r) : Handle<const Fertigkeit_angeborene>(r){}
};

class Fertigkeiten_angeborene_All 
{
   std::list<cH_Fertigkeit_angeborene> list_All;
   void fill_list();
  public : 
   Fertigkeiten_angeborene_All() {fill_list();}
   std::list<cH_Fertigkeit_angeborene> get_All() const {return list_All;}
};

#endif
