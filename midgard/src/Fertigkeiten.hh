#ifndef _FERTIGKEITEN_HH
#  define _FERTIGKEITEN_HH
#include <vector>
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include "class_typen.hh"
#include "class_Ausnahmen.hh"

class Fertigkeit : public HandleContent
{
     std::string name, region, attribut;
     int lernpunkte, anfangswert0, anfangswert, kosten;
     int mutable erfolgswert;
     vector<std::string> standard;
     std::string voraussetzung;
     mutable bool pflicht;
     Ausnahmen ausnahmen;

     void get_Fertigkeit();
     int GrundKosten() const {  return kosten; }
     void set_Standard(const vector<H_Data_typen>& Typ) ;
  public:
     Fertigkeit(const std::string& n,const vector<H_Data_typen>& Typ,const Ausnahmen& a,int l,bool p)
      :name(n),lernpunkte(l),erfolgswert(0),pflicht(p) {get_Fertigkeit(); set_Standard(Typ);}

     std::string Name() const {return name;}
     std::string Attribut() const {return attribut;}
     std::string Region() const {return region;}
     std::string Standard__() const { return standard[0]+' '+standard[1];}
     const vector<std::string>& Standard() const {return standard;}
     int Lernpunkte() const {return lernpunkte;}
     int Anfangswert0() const {return anfangswert0;}
     int Anfangswert() const {return anfangswert;}
     int Kosten() const {return (int)(Standard_Faktor()*GrundKosten());};
     double Standard_Faktor() const;
     int Erfolgswert() const {return erfolgswert;};
     std::string Voraussetzung() const {return voraussetzung;}
     std::string Pflicht() const {if (pflicht) return "*"; return "";}

     void set_Erfolgswert(int e) const {erfolgswert=e;}
};

class cH_Fertigkeit : public Handle<const Fertigkeit>
{
   struct st_index {std::string name; vector<H_Data_typen> Typ; int lernpunkte;
      bool operator == (const st_index& b) const
         {return (name==b.name && Typ[0]->Short() == b.Typ[0]->Short() && lernpunkte==b.lernpunkte);}
      bool operator <  (const st_index& b) const
         { return name < b.name ||
             (name==b.name && Typ[0]->Short()<b.Typ[0]->Short()) ||
             (name==b.name && Typ[0]->Short()==b.Typ[0]->Short() &&
               lernpunkte<b.lernpunkte ); }
      st_index(std::string n, vector<H_Data_typen> T,int l):name(n),Typ(T),lernpunkte(l){}
      st_index(){}
      };

    typedef CacheStatic<st_index,cH_Fertigkeit> cache_t;
    static cache_t cache;
    cH_Fertigkeit(Fertigkeit *s) : Handle<const Fertigkeit>(s) {};
    friend class std::map<st_index,cH_Fertigkeit>;
    cH_Fertigkeit(){};
 public:
    cH_Fertigkeit(const std::string& n,const vector<H_Data_typen>& Typ,
      const Ausnahmen& a,int l=0,bool b=false);
};

class Fertigkeiten_sort_name 
{ public : bool operator() (cH_Fertigkeit x, cH_Fertigkeit y) const
      { return x->Name() < y->Name();}};
class Fertigkeiten_sort_wert 
{ public : bool operator() (cH_Fertigkeit x, cH_Fertigkeit y) const
      { return x->Erfolgswert() < y->Erfolgswert();}};

#endif
