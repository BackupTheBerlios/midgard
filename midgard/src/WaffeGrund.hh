#ifndef _WAFFEGRUND_HH
#  define _WAFFEGRUND_HH
#include <vector>
#include <list>
#include "MidgardBasicElement.hh"
#include "Typen.hh"
//#include "Ausnahmen.hh"
#include <gtk--/progressbar.h>

class cH_WaffeGrund;

class WaffeGrund : public MidgardBasicElement
{
     void get_WaffeGrund();
  public:
     WaffeGrund(const std::string& n)
       :MidgardBasicElement(n)  {get_WaffeGrund();get_map_typ();}

     enum MBEE What() const {return MidgardBasicElement::WAFFEGRUND;}
     std::string What_str() const {return "Grundkenntnis";}
     int MaxErfolgswert(const Grundwerte& w,const vector<cH_Typen>& Typ) const 
         {return 0;} //wg. virtueller Funktion
};

class cH_WaffeGrund : public Handle<const WaffeGrund>
{
    typedef CacheStatic<std::string,cH_WaffeGrund> cache_t;
    static cache_t cache;
    cH_WaffeGrund() {};
    cH_WaffeGrund(WaffeGrund *s) : Handle<const WaffeGrund>(s) {};
    friend class std::map<std::string,cH_WaffeGrund>;
 public:
    cH_WaffeGrund(const std::string& n);

    cH_WaffeGrund(const cH_MidgardBasicElement &x) : Handle<const WaffeGrund>
      (dynamic_cast<const WaffeGrund *>(&*x)){}   
};
  
  
class WaffeGrund_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   WaffeGrund_All(Gtk::ProgressBar *progressbar);
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};

#endif
