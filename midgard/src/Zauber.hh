#ifndef ZAUBERCLASS
#define ZAUBERCLASS
#include <string>
#include <list>
#include <vector>
#include <Aux/Handles.h>
#include "MidgardBasicElement.hh"
#include <Aux/CacheStatic.h>
#include "class_typen.hh"
#include "class_Ausnahmen.hh"
class cH_Zauber;

//class Zauber : public HandleContent
class Zauber : public MidgardBasicElement
{
   std::string ap, name;
   int erfolgswert;
   std::string  art, stufe, zauberdauer, reichweite,
      wirkungsziel, wirkungsbereich, wirkungsdauer, ursprung,
      material, agens, prozess, reagens, beschreibung,spruchrolle,
      zauberart,p_element,s_element,region; 
   int kosten;
   int lernpunkte;
//   Ausnahmen ausnahmen;

   map<std::string,std::string> map_typ;

   void get_Zauber();
   void get_map_typ();
   int GrundKosten() const {  return kosten; }
   vector<std::string> Standard(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const ;   
 public: 
   Zauber(const std::string& n,int l=0) 
      : name(n),lernpunkte(l){get_Zauber();get_map_typ();} 


   std::string What() const {return "Zauber";}

   std::string Ap() const { return ap;}
   std::string Name() const {  return name; }
   bool ist_lernbar(const vector<H_Data_typen>& Typ) const;
   bool ist_gelernt(const std::list<cH_Zauber>& L) const;

   std::string Standard__(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const; 
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
   int Kosten(const vector<H_Data_typen>& Typ,const Ausnahmen& ausnahmen) const;
   int Kosten_eBe(const std::string& pe,const std::string& se) const;
   int Lernpunkte() const {  return lernpunkte; }
   bool Spruchrolle() const 
      { if (spruchrolle=="nicht") return false; 
        else return true; }
   int Erfolgswert(const vector<H_Data_typen>& Typ,const Grundwerte& Werte,const Ausnahmen& ausnahmen) const;
   int get_spezial_zauber_for_magier(const Grundwerte& Werte) const;

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
//   cH_MidgardBasicElement operator cH_MidgardBasicElement() const {return cH_MidgardBasicElement(&*this);}
};


class Zauber_sort_name
{ public: bool operator() (cH_Zauber x,cH_Zauber y) const
   {return x->Name() < y->Name(); }};
class Zauber_sort_stufe
{ public: bool operator() (cH_Zauber x,cH_Zauber y) const
   {return x->Stufe()<y->Stufe(); }};
//class Data_zauber_sort_art
//{ public: bool operator() (cH_Data_zauber x,cH_Data_zauber y) const
//   {return x->Art()<y->Art(); }};
class Zauber_sort_ursprung
{ public: bool operator() (cH_Zauber x,cH_Zauber y) const
   {return x->Ursprung()<y->Ursprung(); }};


class Zauber_All
{
   std::list<cH_Zauber> list_All;
//   void fill_list();
  public:
   Zauber_All();// {fill_list();} 
   std::list<cH_Zauber> get_All() const {return list_All;}
};

#endif
