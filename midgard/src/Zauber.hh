#ifndef ZAUBERCLASS
#define ZAUBERCLASS
#include "MidgardBasicElement.hh"
#include "Typen.hh"
#include "Ausnahmen.hh"
class cH_Zauber;
#include <gtk--/progressbar.h>


class Zauber : public MidgardBasicElement
{
   std::string ap, name;
   std::string  art, stufe, zauberdauer, reichweite,
      wirkungsziel, wirkungsbereich, wirkungsdauer, ursprung,
      material, agens, prozess, reagens, beschreibung,spruchrolle,
      zauberart,p_element,s_element,region; 
   int lernpunkte;
//   mutable bool spruchrolle;

   void get_Zauber();
 public: 
   Zauber(const std::string& n,int l=0) 
      : name(n),lernpunkte(l)
   {get_Zauber();get_map_typ();EP_steigern("Zauber");} 

   enum MBEE What() const {return MidgardBasicElement::ZAUBER;}
   std::string What_str() const {return "Zauber";}

   std::string Ap() const { return ap;}
   std::string Name() const {  return name; }

   std::string Art() const { return art;}
   std::string Stufe() const {  return stufe; }
   int iStufe() const {  if (Stufe()=="groﬂ") return 6; else return atoi(Stufe().c_str()); }
   std::string Zauberdauer() const { return zauberdauer;}
   std::string Zauberart() const { return zauberart;}
   std::string Reichweite() const {return reichweite;}   
   std::string Wirkungsziel() const {return wirkungsziel;}
   std::string Wirkungsdauer() const {return wirkungsdauer;}
   std::string Wirkungsbereich() const {return wirkungsbereich;}
   std::string Ursprung() const {return ursprung;}
   std::string Material() const { return material;}
   std::string Agens() const { return agens;}
   std::string Prozess() const { return prozess;}
   std::string Reagens() const { return reagens;}
   std::string Beschreibung() const { return beschreibung;}
   std::string P_Element() const {return p_element;}
   std::string S_Element() const {return s_element;}
   std::string Region() const {return region;}
//   bool Spruchrolle() const {return spruchrolle;}
//   void set_Spruchrolle(bool s) const {spruchrolle=s;}
   int Kosten_eBe(const std::string& pe,const std::string& se) const;
   int Lernpunkte() const {  return lernpunkte; }
   bool Spruchrolle() const 
      { if (spruchrolle=="nicht") return false; 
        else return true; }
   int Erfolgswert_Z(const vector<cH_Typen>& Typ,const Grundwerte& Werte,const Ausnahmen& ausnahmen) const;
   int get_spezial_zauber_for_magier(const Grundwerte& Werte) const;

//   static void set_Spruchrolle(std::list<cH_MidgardBasicElement>&,bool sp) const;
};

class cH_Zauber : public Handle<const Zauber>
{
   struct st_index {std::string name; int lernpunkte;
      bool operator == (const st_index& b) const
         {return (name==b.name  && lernpunkte==b.lernpunkte);}
      bool operator <  (const st_index& b) const
         { return name < b.name || 
             (name==b.name && lernpunkte<b.lernpunkte ); }
      st_index(std::string n,int l):name(n),lernpunkte(l){}
      st_index(){}
      };
    typedef CacheStatic<st_index,cH_Zauber> cache_t;
    static cache_t cache;
    cH_Zauber(Zauber *s) : Handle<const Zauber>(s) {};
    friend class std::map<st_index,cH_Zauber>;
    cH_Zauber(){};
 public:
   cH_Zauber(const std::string& name,int lernpunkte=0) ;

   cH_Zauber(const cH_MidgardBasicElement &x) : Handle<const Zauber> 
      (dynamic_cast<const Zauber *>(&*x)){}

 class sort {
      public:
         enum esort {NAME,STUFE,URSPRUNG};
      private: 
         esort es;
      public:
         sort(enum esort _es):es(_es) {}
         bool operator() (cH_Zauber x,cH_Zauber y) const
           { switch(es) {
               case(NAME) : return x->Name() < y->Name()  ;
               case(STUFE): return x->Stufe() < y->Stufe();
               case(URSPRUNG): return x->Ursprung() < y->Ursprung() ;
           }}
    };

};


class Zauber_All
{
   std::list<cH_MidgardBasicElement> list_All;
  public:
   Zauber_All(Gtk::ProgressBar *progressbar);
   std::list<cH_MidgardBasicElement> get_All() const {return list_All;}
};

#endif
