#ifndef ZAUBERCLASS
#define ZAUBERCLASS
#include <string>
#include <list>
#include <vector>
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include "class_Grundwerte.hh"
#include "class_typen.hh"

class Zauber : public HandleContent
{
   std::string ap, name;
   mutable int erfolgswert;
   mutable std::string  standard, standard2;
   std::string  art, stufe, zauberdauer, reichweite,
      wirkungsziel, wirkungsbereich, wirkungsdauer, ursprung,
      material, agens, prozess, reagens, beschreibung,spruchrolle,
      zauberart,p_element,s_element,region; 
   mutable int kosten,lernpunkte;
      

   void get_Zauber();
 public: 
   Zauber(const std::string& n) : name(n) {get_Zauber();} 

   void set_Kosten(int k) const {kosten=k;}
   void set_Standard(const std::string& s ) const {standard=s;}
   void set_Standard2(const std::string& s ) const {standard2=s;}
   void set_Erfolgswert(int e) const {erfolgswert=e;}
   void set_Lernpunkte(int l) const {lernpunkte=l;}


   std::string Ap() const { return ap;}
   std::string Name() const {  return name; }
   int Erfolgswert() const {return erfolgswert; }
   std::string Standard__() const { return standard+' '+standard2;}
   std::string Art() const { return art;}
   std::string Stufe() const {  return stufe; }
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
   std::string Standard() const {return standard;}
   std::string Standard2() const {return standard2;}
   std::string Region() const {return region;}
   int Kosten() const {  return kosten; }
   int Lernpunkte() const {  return lernpunkte; }
   std::string Spruchrolle() const {return spruchrolle; }
   double get_Faktor(const vector<Data_typen>& Typen,const Grundwerte& Werte) const;

};

class cH_Zauber : public const_Handle<Zauber>
{
    typedef CacheStatic<std::string,cH_Zauber> cache_t;
    static cache_t cache;
    cH_Zauber(Zauber *s) : const_Handle<Zauber>(s) {};
    friend class std::map<std::string,cH_Zauber>;
    cH_Zauber(){};
 public:
    cH_Zauber(const std::string& name);
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


#endif
