#ifndef _PFLICHT_HH
#  define _PFLICHT_HH
#include <string>
#include <vector>
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include "class_typen.hh"


class Pflicht : public HandleContent
{
      struct pf{std::string pflicht;std::string verboten; 
                int lernpunkte; int erfolgswert; std::string spielbeginn;
         pf(std::string p,std::string v,int l, int e, std::string s)
            :pflicht(p),verboten(v),lernpunkte(l),erfolgswert(e),spielbeginn(s){}
         };
      vector<pf> vec_pflicht;

   public:
      Pflicht(const std::string& spezies,const vector<H_Data_typen>& Typ) ;

      enum LE {LERNPUNKTE,ERFOLGSWERT};

//      std::string Name() const {return name;}
//      int Lernpunkte() const {return lernpunkte;} 
//      int Erfolgswert() const {return erfolgswert;} 

      int istPflicht(const std::string& s,LE le) const ;
      bool istVerboten(const std::string& s,bool spielbeginn=false) const;
         
};

class cH_Pflicht : public Handle<const Pflicht>
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

    typedef CacheStatic<st_index,cH_Pflicht> cache_t;
    static cache_t cache;
    cH_Pflicht() {};
    cH_Pflicht(Pflicht *s) : Handle<const Pflicht>(s) {};
    friend class std::map<st_index,cH_Pflicht>;
 public:
    cH_Pflicht(const std::string& spezies,const vector<H_Data_typen>& Typ);
};
#endif
