#ifndef _FERTIGKEITEN_A_HH
#  define _FERTIGKEITEN_A_HH
#include <list>
#include "MidgardBasicElement.hh"
#include <gtk--/progressbar.h>

class Fertigkeit_angeborene : public MidgardBasicElement
{
     int min,max;

     void get_Fertigkeit();
  public:
#ifndef USE_XML  
     Fertigkeit_angeborene(const std::string& n) 
         : MidgardBasicElement(n),min(0),max(0) {get_Fertigkeit();}
     Fertigkeit_angeborene(const std::string& n,int w) 
         : MidgardBasicElement(n),min(0),max(0) {set_Erfolgswert(w);}
#else
     Fertigkeit_angeborene(const Tag *tag) 
         : MidgardBasicElement(tag,tag->getAttr("Name")),min(0),max(0) {get_Fertigkeit();}
#endif         

     enum MBEE What() const {return MidgardBasicElement::FERTIGKEIT_ANG;}
     std::string What_str() const {return "ang.Fertigkeit";}

     int Min() const {return min;}
     int Max() const {return max;}
     int MaxErfolgswert(const Grundwerte& w,const vector<cH_Typen>& Typ) const 
         {return 0;} //wg. virtueller Funktion
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
#ifdef USE_XML    
    cH_Fertigkeit_angeborene(const Tag *tag);
#endif
    cH_Fertigkeit_angeborene(Fertigkeit_angeborene *r) : Handle<const Fertigkeit_angeborene>(r){}

    cH_Fertigkeit_angeborene(const cH_MidgardBasicElement &x) : Handle<const Fertigkeit_angeborene>
      (dynamic_cast<const Fertigkeit_angeborene *>(&*x)){}

};

class Fertigkeiten_angeborene_All 
{
   std::list<cH_MidgardBasicElement> list_All;
  public : 
   Fertigkeiten_angeborene_All(Gtk::ProgressBar *progressbar);
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};

#endif
