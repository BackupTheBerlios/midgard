#ifndef CLASS_SPEZ_
#define CLASS_SPEZ_

#include<string>
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include <vector>
#include <string>
#include <gtk--/progressbar.h>


class Spezialgebiet : public HandleContent
{
   std::string typ;
   int nr;
   std::string name;
   std::string spezial;
   std::string spezial2;

public:
   Spezialgebiet(const std::string& _name);
   Spezialgebiet() : nr(0) {}

   std::string Typ() const {return typ;}   
   std::string Name() const {return name;}   
   std::string Spezial() const {return spezial;}   
   std::string Spezial2() const {return spezial2;}   
   
};

class cH_Spezialgebiet : public Handle<const Spezialgebiet>    
{
    typedef CacheStatic<std::string,cH_Spezialgebiet> cache_t;
    static cache_t cache;
//    cH_Spezialgebiet(Spezialgebiet *s) : Handle<const Spezialgebiet>(s) {};
    friend class std::map<std::string,cH_Spezialgebiet>;
///    cH_Typen(){};
  public:
   cH_Spezialgebiet() {*this=new Spezialgebiet();}
   cH_Spezialgebiet(const std::string& name);
   cH_Spezialgebiet(const Spezialgebiet *s) : Handle<const Spezialgebiet>(s) {};

   static bool is_cached(const std::string s);
};
 
class Spezialgebiet_All
{
      std::vector<cH_Spezialgebiet> list_All;
   public:
      Spezialgebiet_All(Gtk::ProgressBar *progressbar);
      std::vector<cH_Spezialgebiet> get_All() const {return list_All;}
};
  
#endif
