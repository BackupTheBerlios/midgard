#ifndef _FERTIGKEITEN_HH
#  define _FERTIGKEITEN_HH
#include "MidgardBasicElement.hh"
//#include <vector>
#include "class_typen.hh"
#include "Ausnahmen.hh"
#include <gtk--/label.h>


class Fertigkeit : public MidgardBasicElement
{
     std::string name, region, attribut;
     int lernpunkte, anfangswert0, anfangswert, kosten;
     int mutable erfolgswert;
//     vector<std::string> standard;
     struct st_Voraussetzung {int st;int ge;int ko;int in;int zt;int au;int pa;
                           int sb;int rw;std::string fert;
         st_Voraussetzung()
            : st(0),ge(0),ko(0),in(0),zt(0),au(0),pa(0),
              sb(0),rw(0) {} 
         st_Voraussetzung(int _st,int _ge,int _ko,int _in,int _zt,int _au,int _pa,
                       int _sb,int _rw,std::string _fert)
            : st(_st),ge(_ge),ko(_ko),in(_in),zt(_zt),au(_au),pa(_pa),
              sb(_sb),rw(_rw),fert(_fert) {} };
     st_Voraussetzung voraussetzung;
     mutable bool pflicht;
     Ausnahmen ausnahmen;
     std::map<int,int> map_erfolgswert_kosten;
//     std::map<std::string,std::string> map_typ;

     void get_Fertigkeit();
//     void get_map_typ();
     void get_Steigern_Kosten_map();
     int GrundKosten() const {  return kosten; }
     vector<std::string> Standard(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const ;

  public:
     Fertigkeit(const std::string& n,int l=0,bool p=false)
      :name(n),lernpunkte(l),erfolgswert(0),pflicht(p) 
      {get_Fertigkeit(); get_map_typ();}

  //   map<std::string,std::string> get_MapTyp() const {return map_typ;}
     enum MBEE What() const {return MidgardBasicElement::FERTIGKEIT;}
     std::string What_str() const {return "Fertigkeit";}


     std::string Name() const {return name;}
     std::string Attribut() const {return attribut;}
     std::string Region() const {return region;}
     int Steigern(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const {return int(Standard_Faktor(Typ,ausnahmen)*get_Steigern_Kosten(Erfolgswert()+1));}
     int Reduzieren(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const {return int(Standard_Faktor(Typ,ausnahmen)*get_Steigern_Kosten(Erfolgswert()-1));}
     int Verlernen(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const {return Kosten(Typ,ausnahmen);}
     std::string Standard__(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const ;
//     const vector<std::string>& Standard() const {return standard;}
     int Lernpunkte() const {return lernpunkte;}
     int Anfangswert0() const {return anfangswert0;}
     int Anfangswert() const {return anfangswert;}
     int Kosten(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const {return (int)(Standard_Faktor(Typ,ausnahmen)*GrundKosten());};
     int get_Steigern_Kosten(int erfolgswert) const;
     double Standard_Faktor(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const;
     int Erfolgswert() const {return erfolgswert;};
     std::string Voraussetzung() const {return voraussetzung.fert;}
     bool Voraussetzungen(const Grundwerte& Werte) const;
     std::string Pflicht() const {if (pflicht) return "*"; return "";}

     void set_Erfolgswert(int e) const {erfolgswert=e;}
     void add_Erfolgswert(int e) const {erfolgswert+=e;}
};

class cH_Fertigkeit : public Handle<const Fertigkeit>
{
   struct st_index {std::string name; int lernpunkte; 
      bool operator == (const st_index& b) const
         {return (name==b.name && lernpunkte==b.lernpunkte);}
      bool operator <  (const st_index& b) const
         { return name < b.name ||
             (name==b.name && lernpunkte<b.lernpunkte ); }
      st_index(std::string n, int l):name(n),lernpunkte(l){}
      st_index(){}
      };

    typedef CacheStatic<st_index,cH_Fertigkeit> cache_t;
    static cache_t cache;
    cH_Fertigkeit(Fertigkeit *s) : Handle<const Fertigkeit>(s) {};
    friend class std::map<st_index,cH_Fertigkeit>;
    cH_Fertigkeit(){};
 public:
    cH_Fertigkeit(const std::string& n,int l=0,bool b=false);

    cH_Fertigkeit(const cH_MidgardBasicElement &x) : Handle<const Fertigkeit>
      (dynamic_cast<const Fertigkeit *>(&*x)){}

   class sort {
      public:
         enum esort {NAME,ERFOLGSWERT};
      private:
         esort es;
      public:
         sort(enum esort _es):es(_es) {}
         bool operator() (cH_Fertigkeit x,cH_Fertigkeit y) const
           { switch(es) {
               case(NAME) : return x->Name() < y->Name()  ;
               case(ERFOLGSWERT): return x->Erfolgswert() < y->Erfolgswert();
           }}
    };
};

class Fertigkeiten_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   Fertigkeiten_All(Gtk::Label *label);
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};

#endif
