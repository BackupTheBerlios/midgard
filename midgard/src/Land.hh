#ifndef LANDCLASS
#define LANDCLASS
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include <vector>
#include <string>
#include <gtk--/progressbar.h>

class Land  : public HandleContent
{
   std::string name; 
   std::string kontinent;
   vector<std::string> vec_sprache;

  public:
   Land() {};
   Land(const std::string& n);

   std::string Name() const   {return name; }
   std::string Kontinent() const {return kontinent;}
   vector<std::string> Sprachen() const {return vec_sprache;}
};

class cH_Land : public Handle<const Land>
{
    typedef CacheStatic<std::string,cH_Land> cache_t;
    static cache_t cache;
    cH_Land(Land *s) : Handle<const Land>(s) {};
    friend class std::map<std::string,cH_Land>;
//    cH_Land(){};
  public:
   cH_Land() {*this=new Land();}
   cH_Land(const std::string& name);

};

class Laender_All
{
   std::vector<cH_Land> list_All;
  public:
   Laender_All(Gtk::ProgressBar *progressbar);
   std::vector<cH_Land> get_All() const {return list_All;}
};

#endif
