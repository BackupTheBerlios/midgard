#ifndef _WAFFE_HH
#  define _WAFFE_HH
#include "MidgardBasicElement.hh"
#include "Typen.hh"
#include "Grundwerte.hh"
#include <gtk--/progressbar.h>

class cH_Waffe;
//class H_WaffeBesitz;

class Waffe : public MidgardBasicElement
{
   protected:
     Waffe():MidgardBasicElement("xxx"){} //wg. WaffeBesitz :-(
   public:
     struct st_alias { std::string name; std::string region; 
         std::string schaden;int schaden_bonus; int angriffs_mod;
      st_alias( std::string n,std::string r,std::string s,int b, int a)
        :name(n),region(r),schaden(s),schaden_bonus(b),angriffs_mod(a){}
      };
   private:
     std::string grundkenntnisse, art, art2;
     std::string schaden;
     std::string waffenrang, wm_abwehr_leicht, wm_abwehr_schwer,
         voraussetzung;
//     std::string region;
     int schwierigkeit,st,gw,gs,reichweite_0,reichweite_n,
         reichweite_m,reichweite_f;
     int lern_land,lern_stadt, anfangswert;
     int schaden_bonus;
//     bool pflicht;
     list<st_alias> list_alias;

     void get_Waffe();
     void get_Alias();
     int St() const {return st;}
     int Gw() const {return gw;}
     int Gs() const {return gs;}
  public:
     Waffe(const std::string& n)
      :MidgardBasicElement(n),lern_land(0),lern_stadt(0)
     {get_Waffe(); get_Alias(); get_map_typ();get_Steigern_Kosten_map();
      EP_steigern("Waffen"); }

     enum MBEE What() const {return MidgardBasicElement::WAFFE;}
     std::string What_str() const {return "Waffe";}

//     std::string Name() const {return name;}
     const list<st_alias>& Alias() const {return list_alias;}     
     std::string Grundkenntnis() const {return grundkenntnisse;}
     std::string Region(const std::string& name) const ;
     int LernLand() const {return lern_land;}
     int LernStadt() const {return lern_stadt;}

     std::string Art() const {return art;}
     std::string Art2() const {return art2;}
     std::string Schaden(const std::string& name) const;
     int Schaden_Bonus(const std::string& name) const;
     std::string Waffenrang() const {return waffenrang;}
     std::string WM_Abwehr() const;
     int WM_Angriff(const std::string& name) const;
     std::string Reichweite() const ;

     int Schwierigkeit() const {return schwierigkeit;}
     int Anfangswert() const {return anfangswert;}
     std::string Voraussetzung() const {return voraussetzung;}
     bool Verteidigung() const {if(Art()=="Verteidigung") return true; else return false;}

     bool SG_Voraussetzung(const Grundwerte& Werte) const;
     bool Grundkenntnis_vorhanden(const std::list<cH_MidgardBasicElement>&) const;
     int Maxwert(const vector<cH_Typen>& Typ) const;
     int MaxErfolgswert(const Grundwerte& w,const vector<cH_Typen>& Typ) const; 


     static std::map<std::string,std::string> fill_map_alias_waffe(Gtk::ProgressBar *progressbar);
     static std::string Waffe::get_Verteidigungswaffe(int ohne_waffe,
         const std::list<cH_MidgardBasicElement>& list_Waffen,
         const std::list<cH_MidgardBasicElement>& list_Waffen_besitz,
         const vector<cH_Typen>& Typ,
         const Grundwerte& Werte);

};

class cH_Waffe : public Handle<const Waffe>
{
    typedef CacheStatic<std::string,cH_Waffe> cache_t;
    static cache_t cache;
    cH_Waffe() {};
    cH_Waffe(Waffe *s) : Handle<const Waffe>(s) {};
    friend class std::map<std::string,cH_Waffe>;
 public:
    cH_Waffe(const std::string& n);

    cH_Waffe(const cH_MidgardBasicElement &x) : Handle<const Waffe>
      (dynamic_cast<const Waffe *>(&*x)){}

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
     mutable int av_bonus,sl_bonus;
     mutable std::string magisch;
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

     void set_av_Bonus(int a) const {av_bonus=a;}
     void set_sl_Bonus(int a) const {sl_bonus=a;}
     void set_Magisch(std::string a) const {magisch=a;}
};

class cH_WaffeBesitz : public Handle<const WaffeBesitz>
{
 public:
    cH_WaffeBesitz() {}
    cH_WaffeBesitz(WaffeBesitz *s) : Handle<const WaffeBesitz>(s) {}

    cH_WaffeBesitz(const cH_MidgardBasicElement &x) : Handle<const WaffeBesitz>
      (dynamic_cast<const WaffeBesitz *>(&*x)){}


    bool operator == (const cH_WaffeBesitz& b) const
      {return (*this)->Name()==b->Name() && (*this)->Region() == b->Region() &&
              (*this)->av_Bonus()==b->av_Bonus() && (*this)->sl_Bonus()==b->sl_Bonus() &&
               (*this)->Magisch()==b->Magisch(); }

};

class WaffenBesitz_sort_magbonus
{ public : bool operator() (cH_WaffeBesitz x, cH_WaffeBesitz y) const
      { return x->av_Bonus() > y->av_Bonus()  || 
              (x->av_Bonus() == y->av_Bonus() && x->sl_Bonus() > y->sl_Bonus())||
              (x->av_Bonus() == y->av_Bonus() && x->sl_Bonus()== y->sl_Bonus() &&
               x->Magisch() > y->Magisch() );}}; 
class WaffenBesitz_sort_name
{ public : bool operator() (cH_WaffeBesitz x, cH_WaffeBesitz y) const
      { return x->Name() < y->Name();}};

#endif
