#ifndef _WAFFE_HH
#  define _WAFFE_HH
//#include <vector>
//#include <list>
#include "MidgardBasicElement.hh"
#include "Typen.hh"
#include "Grundwerte.hh"
//#include "itos.h"
#include <gtk--/progressbar.h>

class cH_Waffe;
class H_WaffeBesitz;

class Waffe : public MidgardBasicElement
{
   protected:
     Waffe():name("xxx"){}
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
     int lernpunkte, anfangswert;//, kosten;
     int schaden_bonus;
     bool pflicht;
     list<st_alias> list_alias;
//     map<std::string,std::string> map_alias_waffe;

     void get_Waffe();
     void get_Alias();
     int St() const {return st;}
     int Ge() const {return ge;}
  public:
     Waffe(const std::string& n,int l=0,bool p=false)
      :name(n),lernpunkte(l),pflicht(p)
     {get_Waffe(); get_Alias(); get_map_typ();EP_steigern("Waffen"); }

     enum MBEE What() const {return MidgardBasicElement::WAFFE;}
     std::string What_str() const {return "Waffe";}

     std::string Name() const {return name;}
     const list<st_alias>& Alias() const {return list_alias;}     
     std::string Grundkenntnis() const {return grundkenntnisse;}
     std::string Region(const std::string& name) const ;

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
     int Erfolgswert() const {return erfolgswert;};
     std::string Voraussetzung() const {return voraussetzung;}
     std::string Pflicht() const {if (pflicht) return "*"; return "";}
     bool Verteidigung() const {if(Art()=="Verteidigung") return true; else return false;}

     bool SG_Voraussetzung(const Grundwerte& Werte) const;
     bool Grundkenntnis_vorhanden(const std::list<cH_MidgardBasicElement>&) const;
     int Maxwert(const vector<cH_Typen>& Typ) const;

//     static std::string get_waffe_from_alias(const std::string& waffe);
     static std::map<std::string,std::string> fill_map_alias_waffe();
     static std::string Waffe::get_Verteidigungswaffe(int ohne_waffe,
         const std::list<cH_MidgardBasicElement>& list_Waffen,
         const std::list<H_WaffeBesitz>& list_Waffen_besitz,
         const vector<cH_Typen>& Typ,
         const Grundwerte& Werte);
};

class cH_Waffe : public Handle<const Waffe>
{
   struct st_index {std::string name; int lernpunkte;
      bool operator == (const st_index& b) const
         {return (name==b.name && lernpunkte==b.lernpunkte);}
      bool operator <  (const st_index& b) const
         { return name < b.name ||
             (name==b.name && lernpunkte<b.lernpunkte ); }
      st_index(std::string n, int l)
         :name(n),lernpunkte(l){}
      st_index(){}
      };
    typedef CacheStatic<st_index,cH_Waffe> cache_t;
    static cache_t cache;
    cH_Waffe() {};
    cH_Waffe(Waffe *s) : Handle<const Waffe>(s) {};
    friend class std::map<st_index,cH_Waffe>;
 public:
    cH_Waffe(const std::string& n,int l=0,bool b=false);

    cH_Waffe(const cH_MidgardBasicElement &x) : Handle<const Waffe>
      (dynamic_cast<const Waffe *>(&*x)){}


   class sort {
      public:  
         enum esort {NAME,ERFOLGSWERT};
      private:
         esort es;
      public:
         sort(enum esort _es):es(_es) {}
         bool operator() (cH_Waffe x,cH_Waffe y) const
           { switch(es) {
               case(NAME) : return x->Name() < y->Name()  ;
               case(ERFOLGSWERT): return x->Erfolgswert() < y->Erfolgswert();
           }}
    };
};

class Waffe_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   Waffe_All(Gtk::ProgressBar *progressbar);
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
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
