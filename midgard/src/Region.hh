#ifndef REGIONCLASS
#define REGIONCLASS
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include <vector>
#include <string>
#include <gtk--/progressbar.h>
class cH_Region;

class Region  : public HandleContent
{
   std::string name,abkuerzung,file,url,maintainer,version; 
   mutable bool active;

  public:
//   Region() {};
   Region(const std::string& n);

   std::string Name() const   {return name; }
   bool Active() const {return active; }
   void setActive(bool a) const {active=a; }
   std::string Abkuerzung() const {return abkuerzung;}
   std::string File() const {return file;}
   std::string Url() const {return url;}
   std::string Maintainer() const {return maintainer;}
   std::string Version() const {return version;}

   bool operator==(const Region& b) const {return Name()==b.Name();}

   static bool setActive(const std::vector<cH_Region>& LR,const cH_Region& R,bool active);
};

class cH_Region : public Handle<const Region>
{
    typedef CacheStatic<std::string,cH_Region> cache_t;
    static cache_t cache;
    friend class std::map<std::string,cH_Region>;
    cH_Region(){};
  public:
   cH_Region(Region *s) : Handle<const Region>(s) {};
//   cH_Region() {*this=new Region();}
   cH_Region(const std::string& name);

};

class Regionen_All
{
   std::vector<cH_Region> list_All;
  public:
   Regionen_All(Gtk::ProgressBar *progressbar);
   std::vector<cH_Region> get_All() const {return list_All;}
};

#endif
