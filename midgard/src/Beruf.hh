#ifndef _BERUF_HH
#  define _BERUF_HH

#include <gtk--/progressbar.h>
#include "MidgardBasicElement.hh"


class Beruf : public MidgardBasicElement
{
      std::string name, region; 
      int lernpunkte;
      vector<std::string> stand;
      vector<std::string> vorteile;
      struct st_Voraussetzung {int st;int gw;int gs;int ko;int in;int zt;int au;int pa;
                           int sb;std::string geschlecht;std::string typ;
         st_Voraussetzung()
            : st(0),gw(0),gs(0),ko(0),in(0),zt(0),au(0),pa(0),sb(0) {} 
         st_Voraussetzung(int _st,int _gw,int _gs,int _ko,int _in,int _zt,int _au,
                       int _pa, int _sb,std::string _geschlecht,
                       std::string _typ)
            : st(_st),gw(_gw),gs(_gs),ko(_ko),in(_in),zt(_zt),au(_au),pa(_pa),
              sb(_sb),geschlecht(_geschlecht),typ(_typ) {} };
     st_Voraussetzung voraussetzung; 

     void get_Beruf();      
  public:
      Beruf() {}
      Beruf(std::string n) : name(n)
          {get_Beruf();}

     enum MBEE What() const {return MidgardBasicElement::BERUF;}
     std::string What_str() const {return "Beruf";}

     std::string Name() const {return name;}
     std::string Region() const {return region;}
     int Lernpunkte() const {return lernpunkte;}

     bool Voraussetzungen(const Grundwerte& Werte,const vector<cH_Typen>& Typ) const;
     std::vector<string> Vorteile() const {return vorteile;}
     std::string Beruf::get_Vorteile() const;

};


class cH_Beruf : public Handle<const Beruf>
{
    typedef CacheStatic<std::string,cH_Beruf> cache_t;
    static cache_t cache;
    cH_Beruf(Beruf *s) : Handle<const Beruf>(s) {};
    friend class std::map<std::string,cH_Beruf>;
    cH_Beruf(){};
 public:
    cH_Beruf(const std::string& n);

    cH_Beruf(const cH_MidgardBasicElement &x) : Handle<const Beruf>
      (dynamic_cast<const Beruf *>(&*x)){}
};

class Beruf_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   Beruf_All(Gtk::ProgressBar *progressbar);
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};

#endif
