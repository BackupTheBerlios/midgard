#ifndef _WAFFE_HH
#  define _WAFFE_HH
#include <vector>
#include <list>
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include "class_typen.hh"
#include "Grundwerte.hh"
#include "itos.h"
class cH_Waffe;
class H_WaffeBesitz;

class Waffe : public HandleContent
{
   protected:
     Waffe(){}
   public:
     struct st_alias { std::string name; std::string region; 
         std::string schaden;int schaden_bonus; int angriffs_mod;
      st_alias( std::string n,std::string r,std::string s,int b, int a)
        :name(n),region(r),schaden(s),schaden_bonus(b),angriffs_mod(a){}
      };
   private:
     std::string name, grundkenntnisse, art, art2;
     std::string schaden;
     std::string angriffsrangmod, wm_abwehr_leicht, wm_abwehr_schwer,
         voraussetzung;
     std::string region;
     int schwierigkeit, st,ge,reichweite_0,reichweite_n,
         reichweite_m,reichweite_f;
     int lernpunkte, anfangswert, kosten;
     int mutable erfolgswert;
     int schaden_bonus;
     vector<std::string> standard;
     bool pflicht;
     list<st_alias> list_alias;
     vector<H_Data_typen> Typ;     

     void get_Waffe();
     void get_Alias();
     int GrundKosten() const { return kosten; }
     void set_Standard(const vector<H_Data_typen>& Typ) ;
     int St() const {return st;}
     int Ge() const {return ge;}
  public:
     Waffe(const std::string& n,const vector<H_Data_typen>& _Typ,
           int l=0,bool p=false)
      :name(n),lernpunkte(l),pflicht(p),Typ(_Typ)
     {get_Waffe(); get_Alias(); set_Standard(Typ);}

     std::string Name() const {return name;}
     const list<st_alias>& Alias() const {return list_alias;}     
     std::string Grundkenntnis() const {return grundkenntnisse;}
     std::string Region(const std::string& name) const ;
     std::string Standard__() const { return standard[0]+' '+standard[1];}
     const vector<std::string>& Standard() const {return standard;}

     std::string Art() const {return art;}
     std::string Art2() const {return art2;}
     std::string Schaden(const std::string& name) const;
     int Schaden_Bonus(const std::string& name) const;
     std::string Angriffsrangmod() const {return angriffsrangmod;}
     std::string WM_Abwehr() const;
     int WM_Angriff(const std::string& name) const;
     std::string Reichweite() const ;

     int Lernpunkte() const {return lernpunkte;}
     int Anfangswert() const {return anfangswert;}
     int Kosten() const {return (int)(Standard_Faktor()*GrundKosten());};
     double Standard_Faktor() const;
     int Erfolgswert() const {return erfolgswert;};
     std::string Voraussetzung() const {return voraussetzung;}
     std::string Pflicht() const {if (pflicht) return "*"; return "";}
     bool Verteidigung() const {if(Art()=="Verteidigung") return true; else return false;}

     void set_Erfolgswert(int e) const {erfolgswert=e;}
     bool SG_Voraussetzung(const Grundwerte& Werte) const;
     int Maxwert() const;

     static std::string get_waffe_from_alias(const std::string& waffe);
     static std::string Waffe::get_Verteidigungswaffe(int ohne_waffe,
         const std::list<cH_Waffe>& list_Waffen,
         const std::list<H_WaffeBesitz>& list_Waffen_besitz,
         const vector<H_Data_typen>& Typ,
         const Grundwerte& Werte);
};

class cH_Waffe : public Handle<const Waffe>
{
   struct st_index {std::string name; vector<H_Data_typen> Typ;int lernpunkte;
      bool operator == (const st_index& b) const
         {return (name==b.name && Typ[0]->Short() == b.Typ[0]->Short() && 
            lernpunkte==b.lernpunkte);}
      bool operator <  (const st_index& b) const
         { return name < b.name ||
             (name==b.name && Typ[0]->Short()<b.Typ[0]->Short()) ||
             (name==b.name && Typ[0]->Short()==b.Typ[0]->Short() && lernpunkte<b.lernpunkte ); }
      st_index(std::string n, const vector<H_Data_typen>& T,int l)
         :name(n),Typ(T),lernpunkte(l){}
      st_index(){}
      };
    typedef CacheStatic<st_index,cH_Waffe> cache_t;
    static cache_t cache;
    cH_Waffe() {};
    cH_Waffe(Waffe *s) : Handle<const Waffe>(s) {};
    friend class std::map<st_index,cH_Waffe>;
 public:
    cH_Waffe(const std::string& n,const vector<H_Data_typen>& Typ,
      int l=0,bool b=false);
};
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

class WaffeBesitz : public Waffe
{
     cH_Waffe waffe;
     std::string name,region;
     int av_bonus,sl_bonus;
     std::string magisch;
//     bool magisch;

  public:
     WaffeBesitz(const cH_Waffe& w, std::string b,
                  std::string r,int a,int s, std::string m)
      :waffe(w),name(b),region(r),av_bonus(a),sl_bonus(s),magisch(m) 
         {}
//      {if (magisch_text!="") magisch=true; else magisch=false;}
     
     cH_Waffe Waffe() const {return waffe;}
     std::string Name() const {return name;}
     std::string Region() const {return region;}
     int av_Bonus() const {return av_bonus;}
     int sl_Bonus() const {return sl_bonus;}
     std::string Bonus() const;
     std::string Magisch() const {return magisch;}
     std::string Schaden(const Grundwerte& Werte,const std::string& name) const;
      
//     bool Magisch() const {return magisch;}

     void set_av_Bonus(int a) {av_bonus=a;}
     void set_sl_Bonus(int a) {sl_bonus=a;}
     void set_Magisch(std::string a) {magisch=a;}
};

class H_WaffeBesitz : public Handle<WaffeBesitz>
{
 public:
    H_WaffeBesitz() {}
    H_WaffeBesitz(WaffeBesitz *s) : Handle<WaffeBesitz>(s) {}

    bool operator == (const H_WaffeBesitz& b) const
      {return (*this)->Name()==b->Name() && (*this)->Region() == b->Region() &&
              (*this)->av_Bonus()==b->av_Bonus() && (*this)->sl_Bonus()==b->sl_Bonus() &&
               (*this)->Magisch()==b->Magisch(); }
};

  
class Waffen_sort_name
{ public : bool operator() (cH_Waffe x, cH_Waffe y) const
      { return x->Name() < y->Name();}};
class Waffen_sort_wert
{ public : bool operator() (cH_Waffe x, cH_Waffe y) const
      { return x->Erfolgswert() > y->Erfolgswert();}}; 
class WaffenBesitz_sort_magbonus
{ public : bool operator() (H_WaffeBesitz x, H_WaffeBesitz y) const
      { return x->av_Bonus() > y->av_Bonus()  || 
              (x->av_Bonus() == y->av_Bonus() && x->sl_Bonus() > y->sl_Bonus())||
              (x->av_Bonus() == y->av_Bonus() && x->sl_Bonus()== y->sl_Bonus() &&
               x->Magisch() > y->Magisch() );}}; 
class WaffenBesitz_sort_name
{ public : bool operator() (H_WaffeBesitz x, H_WaffeBesitz y) const
      { return x->Name() < y->Name();}};

#endif
