#ifndef _WAFFEGRUND_HH
#  define _WAFFEGRUND_HH
#include <vector>
#include <list>
#include "MidgardBasicElement.hh"
#include "class_typen.hh"
#include "Ausnahmen.hh"
#include <gtk--/progressbar.h>

class cH_WaffeGrund;

class WaffeGrund : public MidgardBasicElement
{
     std::string name,region;
//     int kosten;

     void get_WaffeGrund();
//     int GrundKosten() const { return kosten; }
//     vector<std::string> Standard() const;
  public:
     WaffeGrund(const std::string& n)
       :name(n)  {get_WaffeGrund();get_map_typ();}

     enum MBEE What() const {return MidgardBasicElement::WAFFEGRUND;}
     std::string What_str() const {return "Grundkenntnis";}
      

     std::string Name() const {return name;}
     std::string Region() const {return region;}
//     int Kosten(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const 
//         {return (int)(Standard_Faktor(Typ,ausnahmen)*GrundKosten());};
//     double Standard_Faktor(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const;
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
