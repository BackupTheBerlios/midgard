#ifndef _WAFFEGRUND_HH
#  define _WAFFEGRUND_HH
#include <vector>
#include <list>
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include "class_typen.hh"
//#include "Grundwerte.hh"
//#include "itos.h"
//class cH_Waffe;
//class H_Waffe;
class cH_WaffeGrund;

class WaffeGrund : public HandleContent
{
     std::string name,region;
     int kosten;
     vector<std::string> standard;

     void get_WaffeGrund();
     int GrundKosten() const { return kosten; }
     void set_Standard(const vector<H_Data_typen>& Typ) ;
  public:
     WaffeGrund(const std::string& n,const vector<H_Data_typen>& Typ)
      :name(n)
     {get_WaffeGrund();set_Standard(Typ);}

     std::string Name() const {return name;}
     std::string Region() const {return region;}
     int Kosten() const {return (int)(Standard_Faktor()*GrundKosten());};
     double Standard_Faktor() const;
     vector<std::string> Standard() const {return standard;}

//     static std::string Is_Grund(const list<cH_WaffeGrund>& L,const std::string& name);
};

class cH_WaffeGrund : public Handle<const WaffeGrund>
{
   struct st_index {std::string name; vector<H_Data_typen> Typ;
      bool operator == (const st_index& b) const
         {return (name==b.name && Typ[0]->Short() == b.Typ[0]->Short());}
      bool operator <  (const st_index& b) const
         { return name < b.name ||
             (name==b.name && Typ[0]->Short()<b.Typ[0]->Short());}
      st_index(std::string n, const vector<H_Data_typen>& T)
         :name(n),Typ(T){}
      st_index(){}
      };
    typedef CacheStatic<st_index,cH_WaffeGrund> cache_t;
    static cache_t cache;
    cH_WaffeGrund() {};
    cH_WaffeGrund(WaffeGrund *s) : Handle<const WaffeGrund>(s) {};
    friend class std::map<st_index,cH_WaffeGrund>;
 public:
    cH_WaffeGrund(const std::string& n,const vector<H_Data_typen>& Typ);
};
  
#endif
